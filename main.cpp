/*
This program constructs a red black tree
Author: Russell Chai
*/
#include "node.h"
#include "tree.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

int main() {
 
  tree* list = new tree();//tree
 
  while (true) {
    char* input = new char(20);
    cout << "'input' to manual input" << endl;
    cout << "'read' to read from file" << endl;
    cout << "'print' to print out tree" << endl;
    cout << "'search' to check if a number is the tree" << endl;
    cout << "'remove' to remove node from tree" << endl;
    cout << "'quit' to quit" << endl;
    cin.getline(input, 20);
    if (strcmp(input, "input") == 0){ //manually input values
      int number;
      cin >> number;
      cin.ignore();
      list->insert(number, list->getHead());
    }
    if (strcmp(input, "read") == 0) { //read numbers in by file
      cout << "input file name" << endl;
      char* fileName = new char(200);

      cin.getline(fileName, 200);
      ifstream fin(fileName);

      int current = 0;
      //splits inputs by commas
      while (!fin.eof()) {
	char digit;
        fin >> digit;
        if (digit == ',') {
	  list->insert(current, list->getHead());
          cout << "tree (sideways)" << endl;
          list->print(list->getHead(), 0);
          current = 0;
        }
        else {
	  current *= 10;
          current += (digit - '0');
        }
      }
      current /= 10;
      cout << "tree (sideways)" << endl;
      list->insert(current, list->getHead());
      list->print(list->getHead(), 0);
    }
    if (strcmp(input, "search") == 0) {
      cout << "input value to search" << endl;
      int value;
      cin >> value;
      cin.ignore();
      if (list->search(value, list->getHead()) != NULL) {
	cout << value << " in tree" << endl;
      }
      else {
	cout << value << " not in tree" << endl;
      }
    }
    if (strcmp(input, "remove") == 0) {
      cout << "input value to delete" << endl;
      int value;
      cin >> value;
      cin.ignore();
      if (list->search(value, list->getHead()) != NULL) {
	list->remove(list->search(value, list->getHead()));
      }
      else {
	cout << value << " not in tree" << endl;
      }
    }
    if (strcmp(input, "print") == 0) { //print out tree
      list->print(list->getHead(), 0);
    }
    if (strcmp(input, "quit") == 0) { //quit
      return 0;
    }
  }
}
