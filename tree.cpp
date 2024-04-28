// tree.cpp

#include "tree.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

Node::Node(int key) : key(key), color(false), left(nullptr), right(nullptr), parent(nullptr) {}

RedBlackTree::RedBlackTree() {
  NIL = new Node(0); 
  NIL->color = true;
  root = NIL;
}

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

void RedBlackTree::print() {
  cout << "Tree Formatted With Color And Parent: " << endl;
  printTree(root, 0);
}

void RedBlackTree::readFromFile(const char* filename) {
  ifstream file(filename);
  int num;
  while (file >> num) {
    add(num);
  }
  file.close();
}

void RedBlackTree::clearTree(Node* node) {
  if(node == NIL) return;
  clearTree(node->left);
  clearTree(node->right);
  delete node;
}

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


RedBlackTree::~RedBlackTree() {
  clearTree(root);
}

