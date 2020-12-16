// needed for lab
// Daniel Hinz
// 11/8/2020

#include <iostream>
#include <vector>
#include <cstdlib>
#include "carFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot {
public:
  CarLot();
  Car *testDriveCar() { return car4sale_; }

  // if a car is bought, requests a new one
  Car *buyCar() {
    Car *bought = cars[cars.size() - 1];
    cout << "Customer has bought the " << *bought;
    return bought;
  }

  Car nextCar() {
    cars.push_back(factories_[rand() % factories_.size()]->requestCar());
    return *cars[cars.size() - 1];
  }

  int lotSize() {
    int i = 0;
    while (i < cars.size())
      ++i;
    return i;
  }

  int getMaxCars() {
    return maxCars;
  }

private:
  Car *car4sale_; // single car for sale at the lot
  vector<CarFactory *> factories_;
  vector<Car*> cars;
  static const int maxCars = 10;
};


CarLot::CarLot() {
  // creates 2 Ford factories and 2 Toyota factories
  factories_.push_back(new FordFactory());
  factories_.push_back(new ToyotaFactory());
  factories_.push_back(new FordFactory());
  factories_.push_back(new ToyotaFactory());

  // gets the first car for sale
  car4sale_ = factories_[rand() % factories_.size()]->requestCar();
}

CarLot *carLotPtr = nullptr; // global pointer instantiation

// Buys car if its the same make/model as requested
bool cusLikesCar(int carNum, Car lotCar, Car prefCar) {
  if (lotCar == prefCar) {
    cout << "The customer likes carNo. " << carNum << ": " << lotCar;
    return true;
  }
  else {
    cout << "The customer does not like carNo. " << carNum << ": " << lotCar;
    return false;
  }
}

int main() {
  srand(time(nullptr));
  CarLot myLot;

  // get a prefered car
  Car preferedCar;
  if (rand() % 2 == 0) preferedCar = Ford();
  else preferedCar = Toyota();

  cout << "Customer requests a " << preferedCar;
  cout << "Customer is now looking at cars..." << endl;

  // search lot for cars
  int carId = 1;
  while (myLot.lotSize() != myLot.getMaxCars()) {
    if (cusLikesCar(carId, myLot.nextCar(), preferedCar)) {
      myLot.buyCar();
      cout << "Customer is satisfied and left" << endl;
      break;
    }
    else
      ++carId;

    // if customer has looked at 10 cars he leaves
    if (myLot.lotSize() >= myLot.getMaxCars())
      cout << "Customer is unsatisfied and left" << endl;
  }

  return 0;
}
