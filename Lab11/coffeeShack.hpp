// class declarations for coffeeShack
// Daniel Hinz
// 11/22/2020

#ifndef  COFFEE_SHACK_H_
#define COFFEE_SHACK_H_

#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <cstdlib>
#include <ctime>

enum class DrinkType { small, medium, large };

// default drink class
class Drink {
public:
  Drink(DrinkType size = DrinkType::small) : size_(size){}
  virtual double getPrice()        const { return (size_ == DrinkType::small) ? 1.00 : (size_ == DrinkType::medium) ? 2.00 : 3.00; }
  virtual std::string addTopping() const { return std::string(); }

private:
  int price_;
  DrinkType size_;
};

// sprinkles decorator class
class sprinkles : public Drink {
public:
  sprinkles(const Drink* drink) : drink_(drink) {}
  double getPrice()        const { return drink_->getPrice() + .50; }
  std::string addTopping() const { return drink_->addTopping() + " sprinkles"; }

private:
  const Drink *drink_;
};

// caramel decorator class
class caramel : public Drink {
public:
  caramel(const Drink* drink) : drink_(drink) {}
  double getPrice()        const { return drink_->getPrice() + .20; }
  std::string addTopping() const { return drink_->addTopping() + " caramel"; }

private:
  const Drink *drink_;
};

// foam decorator class
class foam : public Drink {
public:
  foam(const Drink* drink) : drink_(drink) {}
  double getPrice()        const { return drink_->getPrice() + .40; }
  std::string addTopping() const { return drink_->addTopping() + " foam"; }

private:
  const Drink *drink_;
};

// ice decorator class
class ice : public Drink {
public:
  ice(const Drink* drink) : drink_(drink) {}
  double getPrice()        const { return drink_->getPrice() + .10; }
  std::string addTopping() const { return drink_->addTopping() + " ice"; }

private:
  const Drink *drink_;
};

// forward declaration
class customer;
class barista;

// coffeeShack class
class coffeeShack {
public:
  static void registerCustomer  (barista* b, customer* c) { customers_[b].insert(c); }
  static void deregisterCustomer(barista* b, customer* c) { customers_[b].erase(c); };
  static void handleMessage     (barista* b);

private:
  static std::map<barista*, std::set<customer*>> customers_;
};

// initialization of the map
std::map<barista*, std::set<customer*>> coffeeShack::customers_;

// customer class
class customer {
public:
  customer(const std::string &name) : name_(name) {}
  std::string getName() const { return name_; }

  void subscribe(barista *b) { coffeeShack::registerCustomer(b, this); }
  void unsubscribe(barista *b) { coffeeShack::deregisterCustomer(b, this); }
  void handleMessage(barista*) { std::cout << name_ << ", your drink is ready." << std::endl; }

private:
  std::string name_;
};

// barista class
class barista {
public:
  barista(const std::string &name) : name_(name) {}
  std::string getName() const { return name_; }
  void generateMessage() { coffeeShack::handleMessage(this); }

private:
  std::string name_;
};

// handleMessage class definition
void coffeeShack::handleMessage(barista* b) {
  for (auto i : customers_[b]) i->handleMessage(b);
}

// admin class for part 3
class Admin {
public:
  Admin(Admin *successor = nullptr) : successor_(successor) {}
  virtual void handleRequest(int amount) {
    if (successor_ != nullptr) successor_->handleRequest(amount);
  }
private:
  Admin *successor_;
};

// manager class
class manager : public Admin {
public:
  manager(Admin *successor = nullptr) : Admin(successor) {}
  void handleRequest(int level) override {
    if (level == 1) std::cout << "A manager is preparing your drink. " << std::endl;
    else Admin::handleRequest(level);
  }
};

// senior class
class senior : public Admin {
public:
  senior(Admin *successor = nullptr) : Admin(successor) {}
  void handleRequest(int level) override {
    if (level == 2) std::cout << "A senior barista is preparing your drink. " << std::endl;
    else Admin::handleRequest(level);
  }
};

// junior class
class junior : public Admin {
public:
  junior(Admin *successor = nullptr) : Admin(successor) {}
  void handleRequest(int level) override {
    if (level == 3) std::cout << "A junior barista is preparing your drink. " << std::endl;
    else Admin::handleRequest(level);
  }
};

#endif // !COFFEE_SHACK_H_
