// sorting oranges
// converting vectors to multimaps
// Daniel Hinz
// 10/01/2020

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string; using std::multimap;
using std::vector; using std::pair;

enum class Variety { orange, pear, apple };
vector<string> colors = { "red", "green", "yellow" };

int main() {
  srand(time(nullptr));
  multimap<Variety, string> tree;

  int size = rand() % 100 + 1;

  int i = 0;
  while (i < size) {
    tree.insert(pair<Variety, string> (static_cast<Variety>(rand() % 3), colors[rand() % 3]));
    ++i;
  }

  cout << "Colors of the oranges: ";
  for (auto it = tree.lower_bound(Variety(0)); it != tree.upper_bound(Variety(0)); ++it)
    cout << it->second << ", ";
  cout << endl;
}
