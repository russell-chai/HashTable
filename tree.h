//tree header file
#include "node.h"
#include <iostream>

class tree {//herp
 public:
  tree();
  void insert(int value, node *root);
  void print(node *root, int tabs);
  node* getHead();
  void fix(node* root);
  node* search(int value, node *root);
  void remove(node* root);
 private:
  node* head;
};
