// interface for abstract and concrete car factories
// Daniel Hinz
// 11/8/2020

#ifndef CAR_FACTORY_HPP
#define CAR_FACTORY_HPP

#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

// abstract product
class Car {
public:
  std::string getMake() const { return make_; }
  std::string getModel() const { return model_; }

  friend bool operator==(Car &lhs, Car &rhs) {
    if ((lhs.getMake() == rhs.getMake()) && (lhs.getModel() == rhs.getModel()))
      return true;
    else return false;
  }

  friend std::ostream& operator<<(std::ostream& os, const Car& c) {
    os << c.make_ << " " << c.model_ << std::endl;
    return os;
  }

protected:
  std::string make_;  // this car's make
  std::string model_; // this car's model
};

// two concrete products
class Ford : public Car {
public:
  Ford();
};

class Toyota : public Car {
public:
  Toyota();
};

// absract factory
class CarFactory {
public:
  CarFactory(std::string location, int numCarsInProduction) : location_(location), numCarsInProduction_(numCarsInProduction) {}

  Car* requestCar();
  int getNumCarsInProduction() const { return numCarsInProduction_; }
  std::string getLocation() const { return location_; }
  virtual ~CarFactory() {}

protected:
  virtual Car* makeCar() = 0;

private:
  int numCarsInProduction_;
  std::string location_;
};

// two concrete factories
class FordFactory : public CarFactory {
public:
  FordFactory(std::string location = "", int numCarsInProduction = 0) : CarFactory(location, numCarsInProduction) {}
protected:
  Car* makeCar() override;
};

class ToyotaFactory : public CarFactory {
public:
  ToyotaFactory(std::string location = "",
		int numCarsInProduction = 0) :
    CarFactory(location, numCarsInProduction) {}
protected:
  Car* makeCar() override;
};

#endif
