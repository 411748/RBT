// tree.h

#ifndef TREE_H
#define TREE_H

#include <vector>
#include <cstring>

class Node {
public:
  int key;
  bool color;
  Node* left;
  Node* right;
  Node* parent;
  Node(int key);
};

class RedBlackTree {
private:
  Node* root;
  Node* NIL;
  void fixInsert(Node* node);
  void fixDelete(Node* node);
  void leftRotate(Node* x);
  void rightRotate(Node* y);
  void transplant(Node* u, Node* v);
  Node* minimum(Node* node);
public:
  RedBlackTree();
  ~RedBlackTree();
  void add(int key);
  bool search(int key);
  void remove(int key);
  void print();
  void readFromFile(const char* filename);
  void clearTree(Node* node);

private:
  void printTree(Node* node, int depth);
};

#endif 
