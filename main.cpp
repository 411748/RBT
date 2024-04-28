//main.cpp
#include <iostream>
#include "tree.h"
#include <cstring>

using namespace std;

int main() {
  RedBlackTree tree;
  tree.add(3);
  tree.add(5);
  tree.add(2);
  tree.add(6);
  tree.add(8);
  tree.print();
  return 0;
}
