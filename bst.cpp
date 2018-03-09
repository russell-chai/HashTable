/*
Russell Chai
This program creates a binary search tree containing integers
 */
#include <iostream>
#include <cstring>

using namespace std;

struct treeNode {
  treeNode *left;
  treeNode *right;
  treeNode *parent;
  int value;
};

//insert number into tree
void insert(treeNode *root, int value) {
  //if there are no nodes in tree, change 0 to input value
  if (root->value == 0) {
    root->value = value;
    return;
  }
  //if input value is greater than the current node's value...
  if (root->value < value) {
    //if no right node, input node at right
    if (root->right == NULL) {
      treeNode *right = new treeNode();
      right->value = value;
      right->left = NULL;
      right->right = NULL;
      right->parent = root;
      
      root->right = right;
      return;
    }
    //else traverse to the right of the tree
    insert(root->right, value);
  }
  //if input value is less than or equal to current node's value...
  else {
    //if no left node, input node at left
    if (root->left == NULL) {
      treeNode *left = new treeNode();
      left->value = value;
      left->left = NULL;
      left->right = NULL;
      left->parent = root;
      root->left = left;
      return;
    }
    //else traverse to the left of the tree
    insert(root->left, value);
  }
  
}
//find node with value
treeNode* findNode(treeNode *root, int value) {
  if (root == NULL || root->value == value) {
    return root;
  }

  if (root->value > value) {
    return findNode(root->left, value);
  }
  return findNode(root->right, value);
  
}
//used to find the smallest node on the right side of tree
treeNode* findSuccessor(treeNode *root) {
  if (root->left == NULL) {
    return root;
  }
  
  return findSuccessor(root->left);
}
//remove node
void removeNode(treeNode* &toDelete) {
  //if node to remove has no children...
  if (toDelete->left == NULL && toDelete->right == NULL) {
    //if node to remove is a parent, set the node to null
    if (toDelete->parent == NULL) {
      toDelete->value = 0;
      return;
    }
    //if node to remove is on the left side of tree..
    if (toDelete->value <= toDelete->parent->value) {
      toDelete->parent->left = NULL; //have parent's left side point to null
    }
    //if node to remove is on the right side of tree..
    else {
      toDelete->parent->right = NULL;//have parent's right side point to null
    }
    delete toDelete;
    toDelete = NULL;
  }
  //if node to remove has one child
  else if (toDelete->left == NULL || toDelete->right == NULL) {
    //if the child is on the right
    if (toDelete->left == NULL) {
      treeNode *temp = toDelete->right;
      if (toDelete->parent == NULL) { //if node to delete is root node
	//transfer all of child's node data to root node and delete child node
	toDelete->value = temp->value;
	toDelete->right = temp->right;
	toDelete->left = temp->left;
	delete temp;
      }
      else {
	//delete to delete and have to delete's child new paret point to to deletes parent
	treeNode *newParent = toDelete->parent;
	delete toDelete;
	if (temp->value <= newParent->value) {
	  newParent->left = temp;
	}
	else {
	  newParent->right = temp;
	}
	temp->parent = newParent;
      }
    }
    //essentially everything above except the child is on the left
    else {
      treeNode *temp = toDelete->left;
      if (toDelete->parent == NULL) {
	toDelete->value = temp->value;
	toDelete->right = temp->right;
	toDelete->left = temp->left;
	delete temp;
      }
      else {
	treeNode *newParent = toDelete->parent;
	delete toDelete;
	if (temp->value <= newParent->value) {
	  newParent->left = temp;
	}
	else {
	  newParent->right = temp;
	}
	temp->parent = newParent;
      }
    }
  }
  //if to delete has two children
  else {
    //replace the node's value with the smallest node on the right side of tree
    treeNode *successor = findSuccessor(toDelete->right);
    int value = successor->value;
    
    removeNode(successor);
    toDelete->value = value;
  }
 
}
//print out tree
void print(treeNode* root, int tabs) {
  if (root->value == 0) {
    cout << "tree has no nodes" << endl;
  }
  if (root == NULL || root->value == 0) {
    return;
  }
  print(root->right, tabs + 1);
  for (int a = 0; a < tabs; a++) {
    cout << "\t";
  }
  cout << root->value << endl;
  print(root->left, tabs + 1);
}

int main() {
  treeNode *root = new treeNode();
  root->left = NULL;
  root->right = NULL;
  root->parent = NULL;
  root->value = 0;
  
  while(true) {
    char *input = new char(10);
    cout << "input 'insert' to insert node" << endl;
    cout << "input 'remove' to remove node" << endl;
    cout << "input 'print' to print tree" << endl;
    cout << "input 'quit' to quit" << endl;

    cin.getline(input, 10);
    //if input asks to insert
    if (strcmp(input, "insert") == 0) {
      int value;
      cout << "input value" << endl;
      cin >> value;
      cin.ignore();
      insert(root, value);
    }
    //if input asks to remove node
    if (strcmp(input, "remove") == 0) {
      int value;
      cout << "input value to delete" << endl;
      cin >> value;
      cin.ignore();
      treeNode *toDelete = findNode(root, value); //use findNode() to remove node
      removeNode(toDelete);
    }
    //if input calls to print tree
    if (strcmp(input, "print") == 0) {
      cout << "tree is sideways" << endl;
      print(root, 0);
    }
    //quit
    if (strcmp(input, "quit") == 0) {
      return 0;
    }
  }
}
