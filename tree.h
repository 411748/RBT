// tree.h

#ifndef TREE_H
#define TREE_H

//includes
#include <vector>
#include <cstring>

//creating class for node inside rbt
class Node {
public:
  int key;
  bool color;
  Node* left;
  Node* right;
  Node* parent;
  Node(int key);
};

//creating class for rbt with funcs
class RedBlackTree {
private: //private things
  Node* root;
  Node* NIL;
  void fixInsert(Node* node);
  void fixDelete(Node* node);
  void leftRotate(Node* x);
  void rightRotate(Node* y);
  void transplant(Node* u, Node* v);
  Node* minimum(Node* node);
public: //public things
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
