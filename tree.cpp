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
  
}

void RedBlackTree::fixInsert(Node* node) {

}

void RedBlackTree::leftRotate(Node* x) {
  
}

void RedBlackTree::rightRotate(Node* y) {
  
}

void RedBlackTree::print() {
   
}

void RedBlackTree::readFromFile(const char* filename) {
  
}

void RedBlackTree::clearTree(Node* node) {
  
}

void RedBlackTree::printTree(Node* node, int depth) {
       
}

void RedBlackTree::dfs(Node* node, int depth, std::vector<std::pair<Node*, int>>& nodes) {
       
}

RedBlackTree::~RedBlackTree() {
  clearTree(root);
}
