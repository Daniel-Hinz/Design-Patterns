// Singleton Logger
// Daniel Hinz
// 10/28/2020

#include <string>
#include <fstream>
#include <iostream>

using std::string; using std::cout;
using std::ofstream; using std::cin;
using std::endl; using std::getline;

class Logger {
public:
  static Logger* instance(){ static Logger *log; if (log == nullptr) log = new Logger; return log; };
  void report(const string& str)  { fout << str; fout.flush(); };
  ~Logger(){ fout.flush(); fout.close(); };


private:
  ofstream fout;
  Logger(){ fout.open("myTest.txt", std::fstream::out | std::fstream::app); };
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
};

int secondCall() {
  Logger::instance()->report("This is my second call - ");
  return 1;
}

void thirdCallParameter(const string &str) {
  Logger::instance()->report(str);
}

int main() {
  // call report
  Logger::instance()->report("Hello World! - ");

  // call report with function
  secondCall();

  // call report with function parameter
  thirdCallParameter("this call uses a parameter - ");

  // add user input to file
  string sen;
  cout << "Please enter a sentence" << endl;
  getline(cin, sen);

  Logger::instance()->report(sen);

  return 0;
}




