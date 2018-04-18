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

  cout << "input file name" << endl;
  char* fileName = new char(200);

  cin.getline(fileName, 10);
  ifstream fin(fileName);

  int current = 0;
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
