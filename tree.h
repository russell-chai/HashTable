//tree header file
#include "node.h"
#include <iostream>

class tree {
 public:
  tree();
  void insert(int value, node *root);
  void print(node *root, int tabs);
  node* getHead();
  void fix(node* root);
  bool search(int value, node *root);
 private:
  node* head;
};
