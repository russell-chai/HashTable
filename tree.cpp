/*
CPP file for tree
*/
#include "tree.h"
#include <iostream>

using namespace std;
//tree constructor
tree::tree() {
  head = new node(0, 0, NULL, NULL, NULL);
}
//get the head of the tree
node* tree::getHead() {
  return head;
}
//checks if node is a left child or right child
bool isLeft(node* root) {
  
  if (root->getValue() <= root->getParent()->getValue()) {
    return true;
  }
  return false;
}
//reorder the tree so that the tree follows the rules of red black tree
void tree::fix(node* root) {
  //sets head node to be black
  if (root->getParent() == NULL) {
    root->setColor(0);
  }
  //if parent or grandparent is NULL, then no changes are needed, return
  if (root->getParent() == NULL || root->getGrandparent() == NULL) {
    return;
  }
  //if uncle and parent are red, recolor appropriately, and recursively fix the tree with grandparent as current node
  if (root->getUncle() != NULL && root->getUncle()->getColor() == 1 && root->getParent()->getColor() == 1) {
    root->getParent()->setColor(0);
    root->getUncle()->setColor(0);
    root->getGrandparent()->setColor(1);
    fix(root->getGrandparent());
  }
  else if (root->getParent()->getColor() == 1) {//if parent is red and uncle is NULL or black
    node* greatGrandparent = root->getGrandparent()->getParent();
    node* grandparent = root->getGrandparent();
    //if current node is a left left node, reorder appropriately
    if (isLeft(root) && isLeft(root->getParent())) {

      node* temp = new node(grandparent->getValue(), 1, root->getParent(), root->getParent()->getRight(), root->getUncle());
      if (greatGrandparent == NULL) {
	delete head;
	head = root->getParent();
	head->setParent(NULL);
	head->setRight(temp);
	head->setColor(0);
      }
      else {
	root->getParent()->setParent(greatGrandparent);
	if (isLeft(root->getParent())) {
	  greatGrandparent->setLeft(root->getParent());
	}
	else {
	  greatGrandparent->setRight(root->getParent());
	}
	delete grandparent;
	root->getParent()->setRight(temp);
	root->getParent()->setColor(0);
      }
    }
    //if current node is a left right node, reorder appropriately
    else if (!isLeft(root) && isLeft(root->getParent())) {
      node* temp = new node(grandparent->getValue(), 1, root, root->getRight(), root->getUncle());
      node* left = root->getLeft();
      root->setLeft(root->getParent());
      root->getLeft()->setRight(left);
      root->getLeft()->setParent(root);
      root->setParent(grandparent);
      if (left != NULL) {
	left->setParent(root->getLeft());
      }
      grandparent->setLeft(root);

      root = root->getLeft();
      if (greatGrandparent == NULL) { 

	delete head;
	head = root->getParent();
	head->setParent(NULL);
	head->setRight(temp);
	head->setColor(0);
      }
      else {
	root->getParent()->setParent(greatGrandparent);
	if (isLeft(root->getParent())) {
	  greatGrandparent->setLeft(root->getParent());
	}
	else {
	  greatGrandparent->setRight(root->getParent());
	}
	delete grandparent;
	root->getParent()->setRight(temp);
	root->getParent()->setColor(0);
      }
    }
    //if current node is a right right node, reorder appropriately
    else if (!isLeft(root) && !isLeft(root->getParent())) {
      node *temp = new node(grandparent->getValue(), 1, root->getParent(), root->getUncle(), root->getParent()->getLeft());
      if (greatGrandparent == NULL) {
	delete head;
	head = root->getParent();
	head->setParent(NULL);
	head->setLeft(temp);
	head->setColor(0);
      }
      else {
	root->getParent()->setParent(greatGrandparent);
	if (isLeft(root->getParent())) {
	  greatGrandparent->setLeft(root->getParent());
	}
	else {
	  greatGrandparent->setRight(root->getParent());
	}
	delete grandparent;
	root->getParent()->setLeft(temp);
	root->getParent()->setColor(0);
      }
    }
    //if current node is a right left node, reorder appropriately
    else if (isLeft(root) && !isLeft(root->getParent())) {
      node* temp = new node(grandparent->getValue(), 1, root, root->getUncle(), root->getLeft());
      node* right = root->getRight();
      root->setRight(root->getParent());
      root->getRight()->setLeft(right);
      if (right != NULL) {
	right->setParent(root->getRight());
      }
      root->getRight()->setParent(root);
      root->setParent(grandparent);
      grandparent->setRight(root);

      root = root->getRight();
      if (greatGrandparent == NULL) {
	delete head;
	head = root->getParent();
	head->setParent(NULL);
	head->setLeft(temp);
	head->setColor(0);
      }
      else {
	root->getParent()->setParent(greatGrandparent);
	if (isLeft(root->getParent())) {
	  greatGrandparent->setLeft(root->getParent());
	}
	else {
	  greatGrandparent->setRight(root->getParent());
	}
	delete grandparent;
	root->getParent()->setLeft(temp);
	root->getParent()->setColor(0);
      }
    }
  }
}
//initially insert node as a simple binary search tree, recursively, then call to fix
void tree::insert(int value, node *root) {
  if (root->getValue() == 0) {
    root->setValue(value);
  }
  else if (value <= root->getValue()) {
    if (root->getLeft() == NULL) {
      node* temp = new node(value, 1, root, NULL, NULL);
      root->setLeft(temp);
      fix(root->getLeft());
    }
    else {
      insert(value, root->getLeft());
    }
  }
  else {
    if (root->getRight() == NULL) {
      node* temp = new node(value, 1, root, NULL, NULL);
      root->setRight(temp);
      fix(root->getRight());
    }
    else {
      insert(value, root->getRight());
    }
  }
}
//print tree sideways, recursively
void tree::print(node *root, int tabs) {
  if (root != NULL && root->getValue() == 0) {
    cout << "tree has no nodes" << endl;
  }
  if (root == NULL || root->getValue() == 0) {
    return;
  }
  print(root->getRight(), tabs + 1);
  for (int a = 0; a < tabs; a++) {
    cout << "\t";
  }
  if (root->getColor() == 0) {
    cout << root->getValue() << " B" << endl;
  }
  else {
    cout << root->getValue() << " R" << endl;
  }
  print(root->getLeft(), tabs + 1);
}
//search tree recursively
bool tree::search(int value, node *root) {
  if (root == NULL) {
    return false;
  }
  if (root->getValue() == value) {
    return true;
  }
  if (value <= root->getValue()) {
    return search(value, root->getLeft());
  }
  return search(value, root->getRight());
}
