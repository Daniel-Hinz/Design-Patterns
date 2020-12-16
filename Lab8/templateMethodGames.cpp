// Games, Template Method example
// Daniel Hinz
// 10/29/2020

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

// template for any game where players take turns to make moves and there is a winner
class Game {
public:
  Game() :playersCount_(0), movesCount_(0), playerWon_(noWinner) {}

  // template method
  void playGame(const int playersCount = 0) {
    playersCount_ = playersCount;
    movesCount_ = 0;

    initializeGame();

    for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_) {
      makeMove(i);
      if (i == playersCount_ - 1)
	++movesCount_;
    }

    printWinner();
  }

  virtual ~Game() {}

protected:
  virtual void initializeGame() = 0;
  virtual void makeMove(int player) = 0;
  virtual void printWinner() = 0;
  virtual bool endOfGame() { return playerWon_ != noWinner; }
  static const int noWinner = -1;

  int playersCount_;
  int movesCount_;
  int playerWon_;
};

class Dice : public Game {
public:
  void initializeGame() {
    playersCount_ = numPlayers;
  }

  void makeMove(int player) {
    char rollAgain = ' '; int compRollAgain = 0;
    while (movesCount_ < maxMoves) {

      // if both players skip, game over
      if (rollAgain == 'n' && compRollAgain == 1) {
	cout << "Computer also skipped" << endl;
	break;
      }

      // computer roll dice
      int total = 0;
      if (movesCount_ == 0 || compRollAgain == 0) { // roll on first round or if comp generates 0
	cout << "Computer rolled:";
	for (int i = 0; i < 5; ++i) {
	  int roll = rand() % 6 + 1;
	  cout << " " << roll;
	  total += roll;
	}
      } else cout << "Computer skipped";  // else skip

      // output computers highest score
      if (total > compHigh) { compHigh = total; cout << ", computers highest score = " << compHigh << endl; }
      else cout << ", computers highest score = " << compHigh << endl;

      // you roll dice
      int myTotal = 0;
      if (rollAgain == 'y' || movesCount_ == 0) {  // roll on first round or if user enters y
	cout << "You rolled:";
	for (int i = 0; i < 5; ++i) {
	  int myRoll = rand() % 6 + 1;
	  cout << " " << myRoll;
	  myTotal += myRoll;
	}
      } else cout << "You skipped";  // else skip

      // output users highest score
      if (myTotal > myHigh) { myHigh = myTotal; cout << ", your highest score = " << myHigh << endl; }
      else cout << ", your highest score = " << myHigh << endl;

      // prevents asking the user if they want to roll again on third round
      if (movesCount_ == 2)
	break;

      // determine if computer will roll again
      compRollAgain = rand() % 2;

      // ask user if they want to roll again
      cout << "Roll again? [y/n] ";
      cin >> rollAgain;

      ++movesCount_;
    }

    // get winner
    if (compHigh > myHigh) playerWon_ = comp;
    else playerWon_ = me;
  }

  void printWinner() {
    if (playerWon_ == me) cout << "The user wins!" << endl;
    else cout << "The computer wins!" << endl;
  }

private:
  static const int numPlayers = 2;
  static const int maxMoves   = 3;

  static const int me   = 0;
  static const int comp = 1;

  int compHigh = 0;
  int myHigh   = 0;
};

int main() {
  srand(time(nullptr));
  Game* gp = nullptr;

  gp = new Dice;
  gp->playGame();
  delete gp;
}
