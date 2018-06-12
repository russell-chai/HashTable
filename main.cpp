#include <iostream>
#include <cstring>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct student {
  char* firstName;
  char* lastName;
  int ID;
  double GPA;
};
struct node {
  student* student;
  node* next;
};
int getHash(int number, int size) {
  int address = 0;
  while (number != 0) {
    address *= 13;
    address += (number % 10);
    address %= size;

    number /= 10;
  }
  address *= 13;
  return address % size;
}
int getSize(node* start) {
  int n = 0;
  while(start->student != NULL) {
    n++;
    start = start->next;
  }
  return n;
}
void addNode(node** students, student* temp, int size) {
  int hash = getHash(temp->ID, size);
  bool leave = false;
  node* current = students[hash];
  while(current->student != NULL) {
    if (current->student->ID == temp->ID) {
      cout << "ID already used" << endl;
      leave = true;
      break;
    }
    current = current->next;
  }
  if (leave) {
    return;
  }
     
  while (getSize(students[getHash(temp->ID, size)]) == 3) {
    node* newStudents[size * 2];

    for (int a = 0; a < size* 2; a++) {
      newStudents[a] = NULL;
    }
    for (int a = 0; a < size; a++) {
      node* current = students[a];
      while (current->student != NULL) {
	node* tempNew = new node();
	tempNew->student = current->student;
	tempNew->next = NULL;
	if (newStudents[getHash(current->student->ID, size * 2)] == NULL) {
	  newStudents[getHash(current->student->ID, size * 2)] = tempNew;
	}
	else {
	  node* tempCurrent = newStudents[getHash(current->student->ID, size * 2)];
	  while (tempCurrent->next != NULL) {
	    tempCurrent = tempCurrent->next;
	  }
	  tempCurrent->next = tempNew;
	}
      }
    }
    size *= 2;
    
    students = newStudents;
  }
  if (students[getHash(temp->ID, size)]->student == NULL) {
    node* add = new node();
    add->student = temp;
    add->next = NULL;
    students[getHash(temp->ID, size)] = add;
  }
  else {
    node* current = students[getHash(temp->ID, size)];
    while (current->next->student != NULL) {
      current = current->next;
    }
    node* add = new node();
    add->student = temp;
    add->next = NULL;
    current->next = add;
  }
}
int main() {
  srand(time(NULL));
  
  int size = 100;

  node *studentArray[size];
  
  for (int a = 0; a < size; a++) {
    node* temp = new node();
    temp->student = NULL;
    temp->next = NULL;
    studentArray[a] = temp;
  }
  node** students = studentArray;
  
  cout << "input list of first name file" << endl;
  char* firstNameFile = new char(30);
  cin.getline(firstNameFile, 30);
  ifstream firstName(firstNameFile);
  
  cout << "input list of last name file" << endl;
  char* lastNameFile = new char(30);
  cin.getline(lastNameFile, 30);
  ifstream lastName(lastNameFile);

  vector<char*> firstNames;
  vector<char*> lastNames;

  while(!firstName.eof()) {
    char* tempName = new char(30);
    firstName.getline(tempName, 30);
    firstNames.push_back(tempName);
  }
  while(!lastName.eof()) {
    char* tempName = new char(30);
    lastName.getline(tempName, 30);
    lastNames.push_back(tempName);
  }
  
  while (true) {
    cout << "'a' to add student(s)" << endl;
    cout << "'p' to print all the students out" << endl;
    cout << "'d' to delete a student" << endl;
    cout << "'q' to quit" << endl;

    char input;
    cin >> input;
    cin.ignore();

    
    if (input == 'a') {
      cout << "add by random student generater? (y/n)" << endl;
      char yesRSG;
      cin >> yesRSG;
      cin.ignore();
      if (yesRSG == 'y') {
	cout << "input first name file" << endl;
	char* firstNameFile = new char(30);
	cin.getline(firstNameFile, 30);
	cout << "input last name file" << endl;
	char* lastNameFile = new char(30);
	cin.getline(lastNameFile, 30);

	ifstream firstName(firstNameFile);
	ifstream lastName(lastNameFile);
	
	cout << "input number of students you would like to generate" << endl;
	int n;
	cin >> n;
	cin.ignore();

	
	while (n != 0) {
	  student *temp = new student();
	  
	}
      }
      else if (yesRSG == 'n') {
	cout << "input student's first name" << endl;
	char* firstName = new char(30);
	cin.getline(firstName, 30);

	cout << "input student's last name" << endl;
	char* lastName = new char(30);
	cin.getline(lastName, 30);

	cout << "input student's GPA" << endl;
	double GPA;
	cin >> GPA;
	cin.ignore();
	
	cout << "input student's ID" << endl;
	int ID;
	cin >> ID;
	cin.ignore();

	student* temp = new student();
	
	temp->firstName = firstName;
	temp->lastName = lastName;
	temp->GPA = GPA;
	temp->ID = ID;
	
	addNode(students, temp, size);
      }
    }
    else if (input == 'p') {
      for (int a = 0; a < size; a++) {
	node* temp = students[a];
	while(temp->student != NULL) {
	  cout << temp->student->firstName << " " << temp->student->lastName << endl;
	  cout << "GPA: " << temp->student->GPA << endl;
	  cout << "ID: " << temp->student->ID << endl;
	  temp = temp->next;
	}
	
      }
    }
    else if (input == 'd') {
      
    }
    else if (input == 'q') {

    }
  }
}
