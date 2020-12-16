// figures: class adapter pattern
// Daniel Hinz
// 11/9/2020

#include <iostream>

using std::cout; using std::endl; using std::cin;

// base interface
class Figure {
public:
  virtual void draw() = 0;
  virtual ~Figure() {}
};

// adaptee/implementer
class LegacyRectangle {
public:
  LegacyRectangle(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) :
    topLeftX_(topLeftX), topLeftY_(topLeftY), bottomRightX_(bottomRightX), bottomRightY_(bottomRightY) {}

  void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
    topLeftX_ = topLeftX; topLeftY_ = topLeftY;
    bottomRightX_ = bottomRightX; bottomRightY_ = bottomRightY;
  }

  int getTopLeftX() { return topLeftX_; }
  int getTopLeftY() { return topLeftY_; }
  int getBottomRightX() { return bottomRightX_; }
  int getBottomRightY() { return bottomRightY_; }

  void oldDraw() {
    for (int i = 0; i < bottomRightY_; ++i) {
      for (int j = 0; j < bottomRightX_; ++j)
	if (i >= topLeftY_ && j >= topLeftX_) cout << '*';
	else cout << ' ';
      cout << endl;
    }
  }

  // defining top/left and bottom/right coordinates
private:
  int topLeftX_;
  int topLeftY_;
  int bottomRightX_;
  int bottomRightY_;
};

// adapter uses multiple inheritance to inherit interface and implementation
class SquareAdapter : public Figure, private LegacyRectangle {
public:
  SquareAdapter(int size) : LegacyRectangle(0, 0, size, size) {};
  int size() { return squareSize; }
  void resize(int newSize) {
    squareSize = newSize;
    move(0, 0, squareSize, squareSize);
  }
  void draw() override { oldDraw(); }

private:
  int squareSize;
};


int main() {
  // ask user for size
  cout << "Please enter a size: ";
  int mySize; cin >> mySize;

  // output square before resize
  cout << "\nSquare before resize: " << endl;
  SquareAdapter *square = new SquareAdapter(mySize);
  square->draw();

  // ask user for a new size and resize the square
  cout << "\nPlease enter a new size: ";
  int newSize; cin >> newSize;
  square->resize(newSize);

  // output square after resize
  cout << "\nYour square after resize:" << endl;
  square->draw();

  return 0;
}
