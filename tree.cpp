// tree.cpp

#include "tree.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

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

}

void RedBlackTree::leftRotate(Node* x) {
  
}

void RedBlackTree::rightRotate(Node* y) {
  
}

void RedBlackTree::print() {
  cout << "Tree Formatted With Color And Parent: " << endl;
  printTree(root, 0);
}

void RedBlackTree::readFromFile(const char* filename) {
  
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
  cout << node->key << std::endl;
  printTree(node->left, depth + 1);
}

RedBlackTree::~RedBlackTree() {
  clearTree(root);
}

