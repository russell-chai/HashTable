#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

struct node {
  char* name;
  vector<node*> connectTo;
  vector<int> weights;
};
int ifContains(node* from, node* find) {
  for (int a = 0; a < from->connectTo.size(); a++) {
    if (from->connectTo[a] == find) {
      return a;
    }
  }
  return -1;
}
void print(vector<node*> allNodes) {
  cout << "adjacency matrix" << endl;
  cout << "\t";
  for (int a = 0; a < allNodes.size(); a++) {
    cout << allNodes[a]->name << "\t";
  }
  cout << endl;
  for (int a = 0; a < allNodes.size(); a++) {
    cout << allNodes[a]->name << "\t";
    for (int b = 0; b < allNodes.size(); b++) {

      if (ifContains(allNodes[a], allNodes[b]) != -1) {
	cout << allNodes[a]->weights[ifContains(allNodes[a], allNodes[b])] << "\t";
      }
      else {
	cout << "_" << "\t";
      }
    }
    cout << endl;
  }
}
node* getNode(char* label, vector<node*> allNodes) {
  for (int a = 0; a < allNodes.size(); a++) {
    if (strcmp(allNodes[a]->name, label) == 0) {
      return allNodes[a];
    }
  }
  return NULL;
}
int main() {
  vector<node*> allNodes;

  while(true) {
    char* input = new char(20);
    
    cout << "input 'an' to add node" << endl;
    cout << "input 'ae' to add edge" << endl;
    cout << "input 'rn' to remove node" << endl;
    cout << "input 're' to remove edge" << endl;
    cout << "input 'spath' to find shortest path" << endl;
    cout << "input 'quit' to quit" << endl;

    cin.getline(input, 20);
    if (strcmp(input, "an") == 0) {
      cout << "input node's name" << endl;
      node* temp = new node();
      temp->name = new char(60);
      cin.getline(temp->name, 60);
      allNodes.push_back(temp);
      print(allNodes);
    }
    else if (strcmp(input, "ae") == 0) {
      cout << "input first node's label" << endl;
      char* first = new char(60);
      cin.getline(first, 60);
      cout << "input second node's label" << endl;
      char* second = new char(60);
      cin.getline(second, 60);

      node* firstNode = getNode(first, allNodes);
      node* secondNode = getNode(second, allNodes);
      if(firstNode == NULL || secondNode == NULL) {
	cout << "error: node(s) not found" << endl;
	continue;
      }
      cout << "input edge weight" << endl;
      int weight;
      cin >> weight;
      cin.ignore();
      
      firstNode->connectTo.push_back(secondNode);
      firstNode->weights.push_back(weight);
      print(allNodes);
    }
    else if (strcmp(input, "rn") == 0) {
      cout << "input the label of the node to remove" << endl;
      char* label = new char(60);
      cin.getline(label, 60);
      node* toDelete = getNode(label, allNodes);
      if (toDelete == NULL) {
	cout << "error: node not found" << endl;
	continue;
      }
      for (int a = 0; a < allNodes.size(); a++) {
	int index = ifContains(allNodes[a], toDelete);
	if (index != -1) {
	  allNodes[a]->connectTo.erase(allNodes[a]->connectTo.begin() + index);
	  allNodes[a]->weights.erase(allNodes[a]->weights.begin() + index);
	}
      }

      for (int a = 0; a < allNodes.size(); a++) {
	if (allNodes[a] == toDelete) {
	  allNodes.erase(allNodes.begin() + a);
	  delete toDelete;
	}
      }
      print(allNodes);
    }
    else if (strcmp(input, "re") == 0) {
      cout << "input first node's label" << endl;
      char* first = new char(60);
      cin.getline(first, 60);
      cout << "input second node's label" << endl;
      char* second = new char(60);
      cin.getline(second, 60);

      node* firstNode = getNode(first, allNodes);
      node* secondNode = getNode(second, allNodes);
      if (firstNode == NULL || secondNode == NULL) {
	cout << "error: node(s) not found" << endl;
	continue;
      }

      int index = ifContains(firstNode, secondNode);
      if (index == -1) {
	cout << "error: nodes are not connected" << endl;
	continue;
      }

      firstNode->connectTo.erase(firstNode->connectTo.begin() + index);
      firstNode->weights.erase(firstNode->weights.begin() + index);
      print(allNodes);
    }
    else if (strcmp(input, "spath") == 0) {
      cout << "input first node's label" << endl;
      char* first = new char(60);
      cin.getline(first, 60);
      cout << "input second node's label" << endl;
      char* second = new char(60);
      cin.getline(second, 60);

      node* firstNode = getNode(first, allNodes);
      node* secondNode = getNode(second, allNodes);
      if (firstNode == NULL || secondNode == NULL) {
	////////////////
      }
    }
    else if (strcmp(input, "quit") == 0) {
      break;
    }
  }
}
