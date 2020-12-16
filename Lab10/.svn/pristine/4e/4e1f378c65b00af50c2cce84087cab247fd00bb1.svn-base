// process header file
// Daniel Hinz
// 11/11/2020

#ifndef PROCESS_H_
#define PROCESS_H_

#include <iostream>
#include <string>

// forward declaration
class state;

// process class
class process {
public:
  process();
  process* clone();

  void admitted();
  void interrupt();
  void exit();
  void eventWait();
  void eventComplete();
  void dispatch();

  void report(std::ostream&);
  void changeState(state *s) { state = s; }
  int  getId() { return id; }

private:
  static int next;
  state *state;
  int id;
};

// state class
class state {
public:
  virtual void admitted(process*) {}
  virtual void interrupt(process*) {}
  virtual void exit(process*) {}
  virtual void eventWait(process*) {}
  virtual void eventComplete(process*) {}
  virtual void dispatch(process*) {}
  virtual void report(std::ostream&) = 0;
};

// different state classes
class New : public state {
public:
  static state* instance() {
    static state* onlyInstance = new New();
    return onlyInstance;
  }

  void admitted(process *p) override;
  void report(std::ostream &out) override { out << "new\n"; }
};

class Ready : public state {
public:
  static state* instance() {
    static state* onlyInstance = new Ready();
    return onlyInstance;
  }

  void dispatch(process *p) override;
  void report(std::ostream &out) override { out << "ready\n"; }
};

class Waiting : public state {
public:
  static state* instance() {
    static state* onlyInstance = new Waiting();
    return onlyInstance;
  }

  void eventComplete(process *p) override;
  void report(std::ostream &out) override { out << "waiting...\n"; }
};

class Running : public state {
public:
  static state* instance() {
    static state* onlyInstance = new Running();
    return onlyInstance;
  }

  void exit(process *p) override;
  void eventWait(process *p) override;
  void interrupt(process *p) override;
  void report(std::ostream &out) override { out << "running\n"; }
};

class Terminated : public state {
public:
  static state* instance() {
    static state* onlyInstance = new Terminated();
    return onlyInstance;
  }

  void report(std::ostream &out) override { out << "terminated\n"; }
};

#endif
