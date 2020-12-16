// demoes hashmap implementation
// Daniel Hinz
// 10/19/2020

#include "hashmap.hpp"
#include <iostream>
#include <string>

using std::cin; using std::cout;
using std::endl; using std::string;

const int size = 20;

int main() {
  hashmap<int, int> myHash;

  // test rehash
  myHash.rehash(size);

  cout << "Rehash..." << endl;  
  myHash.print();

  // test safe insert
  cout << "Testing safe insert..." << endl;
  myHash.insert(pair<int, int>(4, 40));
  myHash.insert(make_pair(6, 60));

  cout << "Your Hashmap is: " << endl;
  myHash.print();

  cout << "rehash2.." << endl;
  myHash.rehash(size);
  myHash.print();

  // test search
  auto x = myHash.find(4);
  if (x != nullptr)
    cout << "4 maps to " << x->second << endl;
  else
    cout << "cannot find 4 in map" << endl;

  // test erase
  cout << endl << "erasing 4..." << endl;
  myHash.erase(4);
  cout << "Your new hashmap is: " << endl;
  myHash.print();

  // test find
  cout << "Searching for 4..." << endl;
  auto x2 = myHash.find(4);
  if (x2 != nullptr)
    cout << endl << "4 maps to " << x2->second << endl;
  else
    cout << "cannot find 4 in map" << endl << endl;

  // test unsafe insert
  cout << "Testing unsafe insert..." << endl;
  myHash[4] = 35;
  myHash[4] = 60;

  cout << "Your new hashmap is: " << endl;
  myHash.print();

  auto x3 = myHash.find(4);
  if (x3 != nullptr)
    cout << "4 maps to " << x3->second << endl;
  else
    cout << "cannot find 4 in map" << endl;

  cout << endl;
  hashmap<int, string> employees;

  // entering entries with indexing operator
  employees[123] = "Mike";
  employees[345] = "Charlie";
  employees[192] = "Joe";
  employees[752] = "Paul";
  employees[328] = "Peter";

  cout << "Your employee hashmap is: " << endl;
  employees.print();

  cout << "Enter new employee number: "; int num; cin >> num;
  cout << "Enter new employee name: "; string name; cin >> name;

  employees[num] = name; // "unsafe" insert

  cout << "Your employees after insert:" << endl;
  employees.print();

  // searching map
  cout << "Enter employee number to look for: "; cin >> num;
  auto it = employees.find(num);
  if (it != nullptr)
    cout << it->first << ":" << it->second << endl;
  else
    cout << "employee not found" << endl;

  // removing from a map
  cout << "Enter employee number to fire: "; cin >> num;
  employees.erase(num);

  cout << "Your updated hashmap is: " << endl;
  employees.print();

  // check if not there
  auto removed = employees.find(num);
  if (removed == nullptr)
    cout << "Employee removed successfully" << endl;

  cout << "Your final hashmap is: " << endl;
  employees.print();

  cout << "All functions working properly" << endl;
  return 0;
}
