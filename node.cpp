/*
Node CPP file
*/
#include "node.h"
#include <iostream>
//node constructor
node::node(int newValue, int newColor, node* newParent, node* newLeft, node* newRight) {
  value = newValue;
  color = newColor;
  parent = newParent;
  left = newLeft;
  right = newRight;
}
//sets node's value
void node::setValue(int newValue) {
  value = newValue;
}
//sets node's color
void node::setColor(int newColor) {
  color = newColor;
}
//sets node's parent
void node::setParent(node *newParent) {
  parent = newParent;
}
//sets node's left child
void node::setLeft(node *newLeft) {
  left = newLeft;
}
//sets node's right child
void node::setRight(node * newRight) {
  right = newRight;
}
//return node's value
int node::getValue() {
  return value;
}
//return node's color
int node::getColor() {
  return color;
}
//return node's parent
node* node::getParent() {
  return parent;
}
//return node's left child
node* node::getLeft() {
  return left;
}
//return node's right child
node* node::getRight() {
  return right;
}
//return node's parent's parent; its grandparent
node* node::getGrandparent() {
  return parent->getParent();
}
//return node's grandparent's other child; it's uncle
node* node::getUncle() {
  if (parent->getValue() > getGrandparent()->getValue()) {
    return getGrandparent()->getLeft();
  }
  return getGrandparent()->getRight();
}
//return node's sibling
node* node::getSibling() {
  if (value <= parent->getValue()) {
    return parent->getRight();
  }
  return parent->getLeft();
}
node* node::getRedSon() {
  if (value <= parent->getValue()) {
    if (left != NULL && left->getColor() == 1) {
      return left;
    }
    if (right != NULL && right->getColor() == 1) {
      return right;
    }
    return NULL;
  }
  else {
    if (right != NULL && right->getColor() == 1) {
      return right;
    }
    if (left != NULL && left->getColor() == 1) {
      return left;
    }
    return NULL;
  }
}
