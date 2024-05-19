// tree.cpp

//includes
#include "tree.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

Node::Node(int key) : key(key), color(false), left(nullptr), right(nullptr), parent(nullptr) {}
//constructor
RedBlackTree::RedBlackTree() {
  NIL = new Node(0); 
  NIL->color = true;
  root = NIL;
}
//function to add a node to rbt that also checks for if needing to change colors
void RedBlackTree::add(int key) {
  Node* new_node = new Node(key);
  new_node->left = NIL;
  new_node->right = NIL;
  new_node->color = false; 
  Node* parent = nullptr;
  Node* current = root;
  while (current != NIL) {
    parent = current;
    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
    
  new_node->parent = parent;
  if (parent == nullptr)
    root = new_node;
  else if (key < parent->key)
    parent->left = new_node;
  else
    parent->right = new_node;

  fixInsert(new_node);
}
//function to search for a node inside rbt (returns true or false)
bool RedBlackTree::search(int key) {
  Node* current = root;
  while (current != NIL && current->key != key) {
    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  return current != NIL;
}

//function to remove a node from rbt, also will change colors and change orientation of rbt 
void RedBlackTree::remove(int key) {
  Node* z = root;
  while (z != NIL) {
    if (z->key == key)
      break;
    if (z->key < key)
      z = z->right;
    else
      z = z->left;
  }

  if (z == NIL)
    return; // Key not found

  Node* y = z;
  Node* x;
  bool yOriginalColor = y->color;

  if (z->left == NIL) {
    x = z->right;
    transplant(z, z->right);
  } else if (z->right == NIL) {
    x = z->left;
    transplant(z, z->left);
  } else {
    y = minimum(z->right);
    yOriginalColor = y->color;
    x = y->right;
    if (y->parent == z)
      x->parent = y;
    else {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }

  if (yOriginalColor)
    fixDelete(x);
}
//func used in delete to change oritientaytion 
void RedBlackTree::transplant(Node* u, Node* v) {
  if (u->parent == nullptr)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  v->parent = u->parent;
}
//func used for delete
Node* RedBlackTree::minimum(Node* node) {
  while (node->left != NIL)
    node = node->left;
  return node;
}
//func used to fix rbt after delete
void RedBlackTree::fixDelete(Node* x) {
  while (x != root && x->color) {
    if (x == x->parent->left) {
      Node* w = x->parent->right;
      if (!w->color) {
        w->color = true;
        x->parent->color = false;
        leftRotate(x->parent);
        w = x->parent->right;
      }
      if (w->left->color && w->right->color) {
        w->color = false;
        x = x->parent;
      } else {
        if (w->right->color) {
          w->left->color = true;
          w->color = false;
          rightRotate(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = true;
        w->right->color = true;
        leftRotate(x->parent);
        x = root;
      }
    } else {
      Node* w = x->parent->left;
      if (!w->color) {
        w->color = true;
        x->parent->color = false;
        rightRotate(x->parent);
        w = x->parent->left;
      }
      if (w->left->color && w->right->color) {
        w->color = false;
        x = x->parent;
      } else {
        if (w->left->color) {
          w->right->color = true;
          w->color = false;
          leftRotate(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = true;
        w->left->color = true;
        rightRotate(x->parent);
        x = root;
      }
    }
  }
  x->color = true;
}
//func used to change rbt after adding
void RedBlackTree::fixInsert(Node* node) {
  while (node != root && !(node->parent == nullptr) && !node->parent->color) {
    if (node->parent == node->parent->parent->left) {
      Node* uncle = node->parent->parent->right;
      if (!(uncle == nullptr) && !uncle->color) {
	node->parent->color = true;
        uncle->color = true;
        node->parent->parent->color = false;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
	  node = node->parent;
          leftRotate(node);
        }
        node->parent->color = true;
        node->parent->parent->color = false;
        rightRotate(node->parent->parent);
      }
    } else {
      Node* uncle = node->parent->parent->left;
      if (!(uncle == nullptr) && !uncle->color) {
	node->parent->color = true;
        uncle->color = true;
        node->parent->parent->color = false;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
	  node = node->parent;
          rightRotate(node);
        }
        node->parent->color = true;
        node->parent->parent->color = false;
        leftRotate(node->parent->parent);
      }
    }
  }
  root->color = true;
}
//func used to rotate the tree left
void RedBlackTree::leftRotate(Node* x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left != NIL)
    y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == nullptr)
    root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}
//func used to rotate the tree right
void RedBlackTree::rightRotate(Node* y) {
  Node* x = y->left;
  y->left = x->right;
  if (x->right != NIL)
    x->right->parent = y;
  x->parent = y->parent;
  if (y->parent == nullptr)
    root = x;
  else if (y == y->parent->right)
    y->parent->right = x;
  else
    y->parent->left = x;
  x->right = y;
  y->parent = x;
}
//func used to print tree
void RedBlackTree::print() {
  cout << "Tree Formatted With Color And Parent: " << endl;
  printTree(root, 0);
}
//func used to add from file
void RedBlackTree::readFromFile(const char* filename) {
  ifstream file(filename);
  int num;
  while (file >> num) {
    add(num);
  }
  file.close();
}
//func made if needing to cleartree
void RedBlackTree::clearTree(Node* node) {
  if(node == NIL) return;
  clearTree(node->left);
  clearTree(node->right);
  delete node;
}
//main func for pritning tree
void RedBlackTree::printTree(Node* node, int depth) {
  if (node == NIL) {
    return;
  }
  printTree(node->right, depth + 1);
  for (int i = 0; i < depth; ++i) {
    cout << "\t";
  }
  cout << node->key;
  cout << " (";
  if (node->color)
    cout << "Black";
  else
    cout << "Red";
    cout << ") Parent: ";
  if (node->parent != nullptr) {
    cout << node->parent->key;
  } else {
    cout << "NIL";
  }
  cout << endl;
  printTree(node->left, depth + 1);
}

//destructor
RedBlackTree::~RedBlackTree() {
  clearTree(root);
}

