// demonstrates prototype scheduler
// Daniel Hinz
// 11/11/2020

#include <queue>
#include <ctime>
#include <algorithm>
#include "process.hpp"

// scheduler class
class scheduler {
public:
  scheduler() { prototype = new process(); }
  void run();
  void report(std::ostream& out);

private:
  process* prototype;
  std::deque<process*> allProcesses;
  std::queue<process*> readyQueue;
  std::queue<process*> waitingQueue;
};

// reports status of each process
void scheduler::report(std::ostream &out) {
  if (allProcesses.empty()) {
    out << "All Processes have been terminated!" << std::endl;
    return;
  }
  out << "Report:" << std::endl;
  for (process *p : allProcesses)
    p->report(out);
  out << "_______________________\n" << std::endl;
}

// runs 4 processes
void scheduler::run() {
  srand(time(nullptr));

  // create 4 processes and add to readyQueue
  for (int i = 0; i < 4; ++i) {
    process *tmp = prototype->clone();
    tmp->admitted();
    readyQueue.push(tmp);
    allProcesses.push_back(tmp);
  }

  // run processes until terminated
  while (!readyQueue.empty() || !waitingQueue.empty()) {

    // check if waiting processes are done waiting
    if (!waitingQueue.empty() && (rand() % 2) == 0) {
      process *p = waitingQueue.front();
      waitingQueue.pop();
      p->eventComplete();
      std::cout << "Process " << p->getId() << " is finished waiting" << std::endl;
      readyQueue.push(p);// if process finished waiting, add to end of readyQueue
    }

    // if readyQueue empty, continue waiting for processes
    if (readyQueue.empty())
      continue;

    // dispatch first process in readyQueue
    process *p = readyQueue.front();
    readyQueue.pop();
    p->dispatch();
    p->report(std::cout);

    // from running position, either wait(0), interrupt(1), or exit(2)
    int pos = rand() % 3;
    std::cout << "Process " << p->getId() << " ";

    // if pos = 0 then wait
    if (pos == 0) {
      std::cout << "is waiting..." << std::endl;
      p->eventWait();
      waitingQueue.push(p);
    }

    //if pos = 1 then interrupt
    else if (pos == 1) {
      std::cout << "was interrupted" << std::endl;
      p->interrupt();
      readyQueue.push(p); // move process to the end of readyQueue
    }
    // else terminate
    else {
      std::cout << "exited" << std::endl;
      auto exit = std::find(allProcesses.begin(), allProcesses.end(), p);
      allProcesses.erase(exit);
      delete p;
    }

    // report at the end
    std::cout << "_______________________\n" << std::endl;
    report(std::cout);
  }
}

int main() {
  scheduler s1;
  s1.run();
  return 0;
}
