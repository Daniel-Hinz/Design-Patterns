// vector and list algorithms with objects in containers
// Daniel Hinz
// 9/10/2018

#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <utility>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move; using std::map;


class Student {
public:
  Student(const Student & org) = default;
  Student(string firstName, string lastName) : firstName_(firstName), lastName_(lastName) {}
  Student(Student && org) : firstName_(move(org.firstName_)), lastName_(move(org.lastName_)) {}
  string print() const { return firstName_ + ' ' + lastName_; }

  friend bool operator== (Student left, Student right) {
    return left.lastName_ == right.lastName_ &&
      left.firstName_ == right.firstName_;
  }

  friend bool operator< (Student left, Student right) {
    return left.lastName_ < right.lastName_ ||
			    (left.lastName_ == right.lastName_ &&
			     left.firstName_ < right.firstName_);
  }

private:
  string firstName_;
  string lastName_;
};

// forward declaration of functions
void readRoster(list<Student>& roster, string fileName);
void printRoster(const map<Student, list<string>> roster);

int main(int argc, char* argv[]) {
  // cout error if no arguments passed
  if (argc <= 1) {
    cout << "Please enter an argument" << endl;
    return 1;
  }

  // map to hold students data
  map <Student, list<string>> finalRoster;

  for (int i = 1; i < argc - 1; ++i) { // argc - 1 to avoid dropouts.txt
    list<Student> studentList;
    readRoster(studentList, argv[i]);

    // get courseName
    string courseName = argv[i];
    courseName = courseName.substr(0, courseName.size()-4);

    // loop thru student list
    for (auto studentName : studentList) {
      auto it = finalRoster.find(studentName);

      // if student is on final roster add class to their list
      if (it != finalRoster.end())
	it->second.push_back(courseName);
      else // else add student to map with course
	finalRoster[studentName].push_back(courseName);
    }
  }
  printRoster(finalRoster);
}

// reading in a file of names into a list of strings
void readRoster(list<Student>& roster, string fileName) {
  ifstream course(fileName);
  string first, last;
  while (course >> first >> last)
    roster.push_back(Student(first, last));
  course.close();
}

// printing a map out
void printRoster(const map<Student, list<string>> roster) {
  cout << "All Students" << endl;
  cout << "first name, last name: courses" << endl;

  // get largest name to output columns in the same place
  size_t maxSpace = 0;
  for (auto i : roster)
    if (i.first.print().size() > maxSpace)
      maxSpace = i.first.print().size();

  for (auto map : roster) {
    // cout spaces to output columns in the same place
    int space = maxSpace - map.first.print().size();
    for (auto i = 0; i < space; ++i)
      cout << " ";

    // print map
    cout << map.first.print() << ": ";
    for (auto i : map.second)
      cout << "\t" << i;
    cout << endl;
  }
}
