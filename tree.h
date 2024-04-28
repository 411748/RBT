// tree.h

#ifndef TREE_H
#define TREE_H

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
  void leftRotate(Node* x);
  void rightRotate(Node* y);
public:
  RedBlackTree();
  ~RedBlackTree();
  void add(int key);
  void print();
  void readFromFile(const char* filename);
  void clearTree(Node* node);

private:
  void printTree(Node* node, int depth);
  void dfs(Node* node, int depth, std::vector<std::pair<Node*, int>>& nodes);
};

#endif 
