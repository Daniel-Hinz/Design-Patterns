// demonstrates coffeeShack
// Daniel Hinz
// 11/17/2020

#include "coffeeShack.hpp"

int main() {
  srand(time(nullptr));
  Drink *drink = NULL;

  // take order
  std::cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
  std::string newSize = " "; char size = ' '; std::cin >> size;

  // get size
  switch (size) {
  case 's': drink = new Drink(DrinkType::small); newSize = "small"; break;
  case 'm': drink = new Drink(DrinkType::medium); newSize = "medium"; break;
  case 'l': drink = new Drink(DrinkType::large); newSize = "large"; break;
  }

  // get toppings
  char topping = ' ';
  while (topping != 'n') {
    std::cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? ";
    std::cin >> topping;

    // decorator design pattern
    switch (topping) {
    case 's': drink = new sprinkles(drink); break;
    case 'c': drink = new caramel(drink); break;
    case 'f': drink = new foam(drink); break;
    case 'i': drink = new ice(drink); break;
    case 'n': break;
    }
  }

  // get name
  std::cout << "Can I get your name? ";
  std::string name = " "; std::cin >> name;

  // add customer to queue
  std::queue<customer> customers; customer newCustomer(name);
  customers.push(newCustomer);

  // chain of responsibility design pattern
  Admin *admin = new junior(new senior(new manager));
  int level = 0;

  // if no toppings, junior prepares it
  if (drink->addTopping().empty()) {
    level = 3;
    admin->handleRequest(level);
  }
  // if toppings include foam, manager prepares it
  else if (drink->addTopping().find("foam") != std::string::npos) {
    level = 1;
    admin->handleRequest(level);
  }
  // else senior prepares
  else {
    level = 2;
    admin->handleRequest(level);
  }

  // create map of customers with their drink
  std::map<std::string, std::string> orders;
  std::stringstream ss;

  // convert drink order to a single string
  if (drink->addTopping().empty()) ss << newSize << " coffee" << drink->addTopping();
  else ss << newSize << " coffee with" << drink->addTopping();
  std::string myDrink = ss.str();

  // add customer and drink to map
  orders.insert(std::make_pair(name, myDrink));

  // create barista
  barista bar("Manager");

  // make drink
  while (!customers.empty()) {
    if (rand() % 2 == 0) {
      customers.front().subscribe(&bar);
      bar.generateMessage();
      customers.front().unsubscribe(&bar);
      customers.pop();
    }
    else std::cout << "still waiting..." << std::endl;
  }

  // remove drink
  delete drink;
  
  // customer picks up drink
  for (auto cus : orders) {
    if (cus.first == name) {
      std::cout << "Hello, I am here to pickup a " << cus.second << " for " << cus.first << ".\nThank you. Have a nice day" << std::endl;
    }
    else std::cout << "There isn't an order here for " << cus.second << std::endl; 
  }

  return 0;
}
