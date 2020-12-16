// vector and list algorithms
// Daniel Hinz
// 9/21/2020

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move; using std::find;

// forward declaration of functions
void readRoster(list<string>& roster, string fileName);
void printStudents(const vector<list<string>>& studentEntries_);

int main(int argc, char* argv[]) {

  if (argc <= 1) {
    cout << "Please enter an argument " << endl;
    return 1;
  }

  vector<list<string>> finalRoster;

  // get each student in each file - argc-1 to not include dropouts
  for (int i = 1; i < argc - 1; ++i) {
    list<string> studentCourses;
    readRoster(studentCourses, argv[i]);

    // get courseName
    string courseName = argv[i];
    courseName = courseName.substr(0, courseName.size() - 4);

    // if student is already in finalRoster, add the course to his list
    for (const auto studentName : studentCourses) {
      bool studentExists = false;

      for (auto &student : finalRoster) {
	if (studentName == student.front()) {
	  studentExists = true;
	  student.push_back(courseName);
	  break;
	}
      }
      // else add student to finalRoster
      if (studentExists == false) {
	list<string> student;
	student.push_back(studentName);
	student.push_back(courseName);
	finalRoster.push_back(move(student));
      }
    }
  }
  // print final roster
  printStudents(finalRoster);
}

// reading in a file of names into a list of strings
void readRoster(list<string>& roster, string fileName) {
  ifstream course(fileName);
  string first, last;
  while (course >> first >> last)
    roster.push_back(move(first + ' ' + last));
  course.close();
}

// function to print finalRoster
void printStudents(const vector<list<string>>& roster) {
  cout << "All Students" << endl;
  cout << "first name, last name: courses" << endl;

  // get largest name
  size_t nameSize = 0;
  for (auto &list : roster) {
    if (list.front().size() > nameSize)
      nameSize = list.front().size();
  }

  // output courses
  for (const auto &list : roster) {
    int space = nameSize - list.front().size();// space variable used to output courses starting from the same spot
    for (int i = 0; i < space; ++i)
      cout << " ";
    for (const auto &str : list) {
      if (str == list.front())
	cout << str << ":" << "\t";
      else
	cout << str << "\t";
    }
    cout << endl;
  }
}
