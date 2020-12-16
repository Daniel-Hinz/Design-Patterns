// vector and list algorithms with objects in containers
// Daniel Hinz
// 9/25/2020

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
using std::move;


class Student {
public:
  // constructors
  Student(const Student & org) = default;
  Student(string firstName, string lastName) : firstName_(firstName), lastName_(lastName) {}
  Student(Student && org) : firstName_(move(org.firstName_)), lastName_(move(org.lastName_)) {}

  // print functions
  string print() const { return firstName_ + ' ' + lastName_; }
  void printCourses() {
    for (auto i : classList)
      cout << "\t" << i;
  }

  // add course
  void addCourse(string courseName) { classList.push_back(courseName); }

  // needed for unique() and for remove()
  friend bool operator== (Student left, Student right) {
    return left.lastName_ == right.lastName_ && left.firstName_ == right.firstName_;
  }
  // needed for sort()
  friend bool operator< (Student left, Student right) {
    return left.lastName_ < right.lastName_ || (left.lastName_ == right.lastName_ && left.firstName_ < right.firstName_);
  }
private:
  string firstName_;
  string lastName_;
  list<string> classList;
};

// forward declaration of functions
void readRoster(list<Student>& roster, string fileName);
void printRoster(list<Student>& roster, int maxSpace);

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    cout << "Please enter an argument" << endl;
    return 1;
  }

  vector<list<Student>> finalRoster;

  for (int i = 1; i < argc - 1; ++i) {
    list<Student> roster;
    readRoster(roster, argv[i]);

    // get courseName
    string courseName = argv[i];
    courseName = courseName.substr(0, courseName.size() - 4);

    // get each students name
    for (Student studentName : roster) {
      bool studentExists = false;

      // if student is already on final roster add his course
      for (list<Student> &student : finalRoster) {
	if (student.front() == studentName) {
	  studentExists = true;
	  student.front().addCourse(courseName);
	  break;
	}
      }
      // else add student and his course
      if (studentExists == false) {
	list<Student> studentList;
	studentName.addCourse(courseName);
	studentList.push_back(studentName);
	finalRoster.push_back(move(studentList));
      }
    }
  }
  
  // get largest name size to output table columns neatly
  size_t maxSpace = 0;
  for (auto studentList : finalRoster) {
    for (auto student : studentList) {
      if (student.print().size() > maxSpace)
	maxSpace = student.print().size();
    }
  }

  // output final roster
  cout << "All Students" << endl;
  cout << "first name, last name: courses" << endl;
  for (auto studentList : finalRoster)
    printRoster(studentList, maxSpace);
}

void readRoster(list<Student>& roster, string fileName) {
  ifstream course(fileName);
  string first, last;
  while (course >> first >> last)
    roster.push_back(Student(first, last));
  course.close();
}

// printing a list out
void printRoster(list<Student>& roster, int maxSpace) {
  for (auto& student : roster) {
    int space = maxSpace - student.print().size();
    for (int i = 0; i < space; ++i)
      cout << " ";
    cout << student.print() << ": ";
    student.printCourses();
    cout << endl;
  }
}
