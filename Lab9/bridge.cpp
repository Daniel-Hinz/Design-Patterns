// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Daniel Hinz
// 11/8/2020

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill {
public:
  Fill(char fillChar, char border) : fillChar_(fillChar), border_(border) {}
  virtual char getBorder() = 0;
  virtual char getInternal() = 0;
  virtual ~Fill() {}

protected:
  char fillChar_;
  char border_;
};

// concrete body
class Hollow : public Fill {
public:
  Hollow(char fillChar) : Fill(' ', fillChar) {}
  char getBorder() override { return border_; }
  char getInternal() override { return ' '; }
  ~Hollow() {}
};

// another concrete body
class Filled : public Fill {
public:
  Filled(char fillChar) :Fill(fillChar, fillChar) {}
  char getBorder() override { return fillChar_; }
  char getInternal() override { return fillChar_; }
  ~Filled() {}
};

// abstract handle
class Figure {
public:
  Figure(int size, Fill* fill) : size_(size), fill_(fill) {}
  virtual void draw() = 0;
  virtual ~Figure() {}
  void changeFill(const Fill* fill) { fill_ = const_cast<Fill*>(fill); }

protected:
  int size_;
  Fill *fill_;
};

// concrete handle
class Square : public Figure {
public:
  Square(int size, Fill* fill) : Figure(size, fill) {}
  void draw() override;
};


void Square::draw() {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j)
      if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
	cout << fill_->getBorder();
      else
	cout << fill_->getInternal();
    cout << endl;
  }
}

// enhancedFilled class
class enhancedFilled : public Fill {
public:
  enhancedFilled(char fillChar, char border) : Fill(fillChar, border) {}
  char getBorder() override { return border_; }
  char getInternal() override { return fillChar_; }
  ~enhancedFilled() {}
};

int main() {
  // ask user for parameters
  cout << "Filled or hollow? [f/h] ";
  char ifFilled; cin >> ifFilled;
  cout << "Enter character: ";
  char fchar; cin >> fchar;
  cout << "Enter size: "; int size; cin >> size;

  // output figure before changeFill
  cout << endl << "Figure before changeFill():" << endl;
  Figure *changeFill = new Square(size, ifFilled == 'f' ?
				  static_cast<Fill*>(new Filled(fchar)) :
				  static_cast<Fill*>(new Hollow(fchar)));
  changeFill->draw();

  // change figures depending on prev input
  Fill *newFig = (ifFilled == 'f') ? newFig = new Hollow(fchar) : new Filled(fchar);

  // output figure after changeFill
  cout << endl << "Figure after changeFill():" << endl;
  changeFill->changeFill(newFig);
  changeFill->draw();

  // output hollow figure
  cout << "\nOutput hollow figure:" << endl;
  Figure *hollow = new Square(6, new Hollow('h'));
  hollow->draw();

  // output filled figure
  cout << "\nOutput filled figure:" << endl;
  Figure *filled = new Square(6, new Filled('f'));
  filled->draw();

  // output enhanced figure
  cout << "\nOutput enhanced figure:" << endl;
  Figure *enhancedFill = new Square(6, new enhancedFilled('i','b'));
  enhancedFill->draw();
}
