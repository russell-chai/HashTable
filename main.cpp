/*
This program constructs a red black tree
Author: Russell Chai
*/
#include "node.h"
#include "tree.h"
#include <iostream>
#include <cstring>
using namespace std;

int main() {
 
  tree* list = new tree();//tree

  while (true) {
    cout << "input 'insert' to insert value" << endl;
    cout << "input 'print' to print tree" << endl;

    char* input = new char(10);
    cin.getline(input, 10);

    if (strcmp(input, "insert") == 0) {//if input wants insert
      int value;
      cout << "input value" << endl;
      cin >> value;
      cin.ignore();
      list->insert(value, list->getHead());//insert value
    }
    else if (strcmp(input, "print") == 0) {//if input wants insert
      cout << "tree is sideways" << endl;
      list->print(list->getHead(), 0);
    }
    
  }
}
