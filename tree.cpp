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
    cout << root->getValue();
    if (root->getParent() != NULL) {
      cout << " " << root->getParent()->getValue() << endl;
    }
    else {
      cout << endl;
    }
  }
  else {
    cout << root->getValue();
    if (root->getParent() != NULL) {
      cout << " " << root->getParent()->getValue() << endl;
    }
    else {
      cout << endl;
    }
  }
  print(root->getLeft(), tabs + 1);
}
//find the successor node
node* findSuccessor(node* root) {
  if (root->getLeft() == NULL) {
    return root;
  }
  return findSuccessor(root->getLeft());
}
//remove node
void tree::remove(node *root) {
  cout << root->getValue() << " " << root->getColor()  << " " << root->getParent()->getValue() << endl;
  print(head, 0);
  //if node is a double black
  if (root->getColor() == 2) {
    cout << root->getSibling()->getValue() << " " << root->getParent()->getLeft()->getValue() << endl;
    //when double black is root node
    if (root->getParent() == NULL) {
      head->setValue(0);
      head->setParent(NULL);
      
      head->setLeft(NULL);
      head->setColor(0);
      head->setRight(NULL);
      return;
    }
    //if sibling is black and has a red child
    else if (root->getSibling() != NULL && root->getSibling()->getColor() == 0 && root->getSibling()->getRedSon() != NULL){
      //when sibling and sibling's child is left left
      if (isLeft(root->getSibling()) && isLeft(root->getSibling()->getRedSon())) {
	//when root's parent is the top node
	if (root->getGrandparent() == NULL) {
	  head = root->getSibling();
	  head->setParent(NULL);
	  node* right = head->getRight();
	  head->setRight(root->getParent());
	  root->getParent()->setParent(head);
	  head->getLeft()->setColor(0);
	  if (right != NULL) {
	    right->setParent(root->getParent());
	    root->getParent()->setLeft(right);
	  }
	  root->getParent()->setRight(NULL);
	  delete root;
	}
	else {
	  if (isLeft(root->getParent())) {
	    root->getGrandparent()->setLeft(root->getSibling());
	  }
	  else {
	    root->getGrandparent()->setRight(root->getSibling());
	  }
	  root->getSibling()->setParent(root->getGrandparent());
	  node* right= root->getSibling()->getRight();
	  root->getParent()->setParent(root->getSibling());
	  root->getParent()->setLeft(NULL);
	  root->getGrandparent()->setRight(root->getParent());
	  root->getGrandparent()->getLeft()->setColor(0);
	  if (right != NULL) {
	    right->setParent(root->getParent());
	    root->getParent()->setLeft(right);
	  }
	 
	  root->getParent()->setRight(NULL);
	  
	  delete root;
	}
      }
      //when sibling and sibling's child is left right
      else if (isLeft(root->getSibling()) && !isLeft(root->getSibling()->getRedSon())) {
	//reorder the sibling and it's child, then recall the remove function
	node* sibling = root->getSibling();
	root->getParent()->setLeft(sibling->getRedSon());
	sibling->getRedSon()->setLeft(sibling);
	sibling->setParent(sibling->getRedSon());
	sibling->getParent()->setParent(root->getParent());
	sibling->setLeft(NULL);
	sibling->setRight(NULL);
	
	root->getSibling()->setColor(0);
	root->getSibling()->getLeft()->setColor(1);
	remove(root);
      }
      //when sibling and sibling's child is right right
      else if (!isLeft(root->getSibling()) && !isLeft(root->getSibling()->getRedSon())) {
	//when root's parent is the head node
	if (root->getGrandparent() == NULL) {
	  head = root->getSibling();
	  head->setParent(NULL);
	  node* left = head->getLeft();
	  head->setLeft(root->getParent());
	  root->getParent()->setParent(head);
	  head->getRight()->setColor(0);
	  if (left != NULL) {
	    left->setParent(root->getParent());
	    root->getParent()->setRight(left);
	  }
	  root->getParent()->setLeft(NULL);
	  delete root;
	}
	else {
	  if (isLeft(root->getParent())) {
	    root->getGrandparent()->setLeft(root->getSibling());
	  }
	  else {
	    root->getGrandparent()->setRight(root->getSibling());
	  }
	  root->getSibling()->setParent(root->getGrandparent());
	  node* left = root->getSibling()->getLeft();
	  root->getParent()->setParent(root->getSibling());
	  root->getParent()->setRight(NULL);
	  root->getGrandparent()->setLeft(root->getParent());
	  root->getGrandparent()->getRight()->setColor(0);
	  if (left != NULL) {
	    left->setParent(root->getParent());
	    root->getParent()->setRight(left);
	  }
	  root->getParent()->setLeft(NULL);
	  delete root;
	}
      }
      //when sibling and sibling's child is right left
      else if (!isLeft(root->getSibling()) && isLeft(root->getSibling()->getRedSon())) {
	//reorder sibling and it's child, then recall remove
	node* sibling = root->getSibling();
	root->getParent()->setRight(sibling->getRedSon());
	sibling->getRedSon()->setLeft(sibling);
	sibling->setParent(sibling->getRedSon());
	sibling->getParent()->setParent(root->getParent());
	sibling->setRight(NULL);
	sibling->setLeft(NULL);
	
	root->getSibling()->setColor(0);
	root->getSibling()->getRight()->setColor(1);
	remove(root);
      }
    }
    //when root's sibling is black, and has no children
    else if (root->getSibling() != NULL && root->getSibling()->getColor() == 0) {
      cout << "herp" << endl;
      root->getSibling()->setColor(1);
      if (isLeft(root)) {
        root->getParent()->setLeft(NULL);
      }
      else {
        root->getParent()->setRight(NULL);
      }
      if (root->getParent()->getColor() == 1) {
	root->getParent()->setColor(0);
	delete root;
      }
      else {
	node* parent = root->getParent();
	delete root;
	parent->setColor(2);
	remove(parent);
      }
    }
    //when root's sibling is red
    else if (root->getSibling() != NULL && root->getSibling()->getColor() == 1) {
      //if root is on the left
      if (isLeft(root)) {
	//if root's parent is the head node
	if (root->getGrandparent() == NULL) {
	  head = root->getSibling();
	  head->setParent(NULL);
	  node* left = head->getLeft();
	  head->setLeft(root->getParent());
	  root->getParent()->setParent(head);
	  head->setColor(0);
	  root->getParent()->setRight(left);
	  left->setParent(root->getParent());
	  root->getParent()->setLeft(NULL);
	  root->getParent()->setColor(1);
	  delete root;
	}
	else {
	  node* sibling = root->getSibling();
	  sibling->setParent(root->getGrandparent());
	  if (isLeft(root->getParent())) {
	    root->getGrandparent()->setLeft(sibling);
	  }
	  else {
	    root->getGrandparent()->setRight(sibling);
	  }
	  root->getParent()->setParent(sibling);
	  sibling->setColor(0);
	  node* left = sibling->getLeft();
	  sibling->setLeft(root->getParent());
	  root->getParent()->setRight(left);
	  left->setParent(root->getParent());
	  root->getParent()->setLeft(NULL);
	  root->getParent()->setColor(1);
	  delete root;  
	}
      }
      //if root is on the right
      else {
	//if root's parent is the head node
	if (root->getGrandparent() == NULL) {
	  head = root->getSibling();
	  head->setParent(NULL);
	  node* right = head->getRight();
	  head->setRight(root->getParent());
	  root->getParent()->setParent(head);
	  head->setColor(0);
	  root->getParent()->setLeft(right);
	  right->setParent(root->getParent());
	  root->getParent()->setRight(NULL);
	  root->getParent()->setColor(1);
	  delete root;
	}
	else {
	  node* sibling = root->getSibling();
	  sibling->setParent(root->getGrandparent());
	  if (isLeft(root->getParent())) {
	    root->getGrandparent()->setLeft(sibling);
	  }
	  else {
	    root->getGrandparent()->setRight(sibling);
	  }
	  root->getParent()->setParent(sibling);
	  sibling->setColor(0);
	  node* right = sibling->getLeft();
	  sibling->setRight(root->getParent());
	  root->getParent()->setLeft(right);
	  right->setParent(root->getParent());
	  root->getParent()->setRight(NULL);
	  root->getParent()->setColor(1);
	  delete root;
	}
      }
    }
  }
  //if root has both children, replace node with successor and delete successor
  else if (root->getLeft() != NULL && root->getRight() != NULL) {
    node* successor = findSuccessor(root->getRight());
    int value = successor->getValue();

    remove(successor);
    root->setValue(value);
  }
  //if root is red and root and root has no children
  else if (root->getColor() == 1 && root->getLeft() == NULL && root->getRight() == NULL) {
    if (isLeft(root)) {
      root->getParent()->setLeft(NULL);
    }
    else {
      root->getParent()->setRight(NULL);
    }
    delete root;
  }
  //if root has left child, and either it's right child or itself is red
  else if (root->getLeft() != NULL && (root->getColor() == 1 || root->getLeft()->getColor() == 1)) {
    if (root->getParent() == NULL) {
      root->getLeft()->setColor(0);
      head = root->getLeft();
      delete root;
    }
    else {
      if (isLeft(root)) {
	root->getParent()->setLeft(root->getLeft());
      }
      else {
	root->getParent()->setRight(root->getLeft());
      }
      root->getLeft()->setParent(root->getParent());
      root->getLeft()->setColor(0);
      delete root;
    }
  }
  //if root has right child and either its right node or itself is red 
  else if (root->getRight() != NULL && (root->getColor() == 1 || root->getRight()->getColor() == 1)) {
    if (root->getParent() == NULL) {
      root->getRight()->setColor(0);
      head = root->getRight();
      delete root;
    }
    else {
      if (isLeft(root)) {
	root->getParent()->setLeft(root->getRight());
      }
      else {
	root->getParent()->setRight(root->getRight());
      }
      root->getRight()->setParent(root->getParent());
      root->getRight()->setColor(0);
      delete root;
    }
  }
  //else it is a double black case
  //set node's color to be double black, and delete root again
  else {
    root->setColor(2);
    remove(root);
  }
}
//search tree recursively
node* tree::search(int value, node *root) {
  if (root == NULL) {
    return NULL;
  }
  if (root->getValue() == value) {
    return root;
  }
  if (value <= root->getValue()) {
    return search(value, root->getLeft());
  }
  return search(value, root->getRight());
}
