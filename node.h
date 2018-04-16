//node header file

//node header guard
#ifndef NODE_H
#define NODE_H

class node {
  //node's public functions
 public:
  node(int newValue, int newColor, node* newParent, node* newLeft, node* newRight);

  void setValue(int newValue);
  void setColor(int newColor);
  void setParent(node* parent);
  void setRight(node* right);
  void setLeft(node* left);

  int getValue();
  int getColor();
  node* getParent();
  node* getLeft();
  node* getRight();
  node* getGrandparent();
  node* getUncle();

  //node's private variables
 private:
  node* left;
  node* right;
  node* parent;
  int color;
  int value;
};

#endif /* NODE_H */
