// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Daniel Hinz
// 10/04/2020

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

using std::cin; using std::cout; using std::endl;
using std::string; using namespace std::placeholders;
using std::vector; using std::deque;
using std::remove_copy_if; using std::back_inserter;

// Apples struct
struct Apples {
  double weight;
  string color;

  bool operator<(const Apples& rhs) const { return this->weight < rhs.weight; }
  void operator=(double update)           { this->weight = update; }
  void print    ()                  const { cout << color << ", " << weight << endl; }
};

// used for generate
Apples gen() {
  Apples apple; const double minWeight = 8.; const double maxWeight = 3.;
  apple.weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
  apple.color = rand() % 2 == 1 ? "green" : "red";
  return apple;
  }

int main() {
  srand(time(nullptr));
  
  cout << "Input crate size: ";
  int size = 0;
  cin >> size;

  if (size <= 0) {
    cout << "Please enter a crate size greater than 0" << endl;
    return 1;
  }
  
  vector <Apples> crate(size);
  
  
  // generate() - assign random weight and color to apples in the crate
  generate(crate.begin(), crate.end(), gen);

  cout << "Enter weight to find: ";
  double toFind = 0.0;
  cin >> toFind;

  // count_if() - return num of apples greater than the entered weight
  int cnt = count_if(crate.begin(), crate.end(), [=](Apples apple) { return apple.weight > toFind; });
  cout << "There are " << cnt << " apples heavier than " << toFind << " oz" << endl;

  // find_if() - finds position of each apple greater than the entered weight
  cout << "at positions ";
  auto pos = crate.begin();
  while (pos != crate.end()) {
    pos = find_if(pos, crate.end(), [=](Apples apple) { return apple.weight > toFind; });
    cout << pos - crate.begin() << " ";
    if (pos >= crate.end()) break;
    pos++;
  }

  // max_element() - returns heaviest apple in crate
  auto heaviest = max_element(crate.begin(), crate.end());
  cout << "\nHeaviest apple weighs: " << heaviest->weight << " oz" << endl;

  // accumulate() - get sum of all apples weight
  double sum = accumulate(crate.begin(), crate.end(), 0, [=](double sum, Apples apple) {return sum += apple.weight; });
  cout << "Total apple weight is: " << sum << " oz" << endl;

  // transform() - adds weight to each apple
  cout << "How much should they grow: ";
  double toGrow;
  cin >> toGrow;
  transform(crate.begin(), crate.end(), crate.begin(), [=](Apples apple) {return apple.weight += toGrow; });

  // remove_if() - removes apples that are lower than weight inputted
  cout << "Input minimum acceptable weight: ";
  double minAccept;
  cin >> minAccept;

  auto remove = remove_if(crate.begin(), crate.end(), [=](Apples apple)->bool {return apple.weight < minAccept; });
  crate.erase(remove, crate.end());

  cout << "removed " << size - crate.size() << " elements" << endl;

  // sort() - sorts apples from lightest to heaviest
  sort(crate.begin(), crate.end());

  // remove_copy_if() - moving all red apples from crate to peck
  deque<Apples> peck;
  remove_copy_if(crate.begin(), crate.end(), back_inserter(peck), [=](Apples apple) { return apple.color != "red"; });

  // for_each() - outputs all apples in crate
  cout << "apples in the crate:" << endl;
  for_each(crate.begin(), crate.end(), [=](Apples apple) {apple.print(); });
  cout << endl;

  // for_each() - outputs all apples in peck
  cout << "apples in the peck:" << endl;
  for_each(peck.begin(), peck.end(), [=](Apples apple) {apple.print(); });
}

  
