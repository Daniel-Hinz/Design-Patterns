// functions definitions for process.hpp
// Daniel Hinz
// 11/11/2020

#include "process.hpp"

process::process() {
  state = New::instance();
  id = next; ++next;
}

void process::admitted() {
  state->admitted(this);
}

void process::interrupt() {
  state->interrupt(this);
}

void process::exit() {
  state->exit(this);
}

void process::eventWait() {
  state->eventWait(this);
}

void process::eventComplete() {
  state->eventComplete(this);
}

void process::dispatch() {
  state->dispatch(this);
}

process* process::clone() {
  process *p = new process();
  return p;
}

void process::report(std::ostream &out) {
  out << "Process " << id << " is ";
  state->report(out);
}

int process::next = 0;

// state function defintions
void New::admitted(process *p) {
  p->changeState(Ready::instance());
}

void Ready::dispatch(process *p) {
  p->changeState(Running::instance());
}

void Waiting::eventComplete(process *p) {
  p->changeState(Ready::instance());
}

void Running::eventWait(process *p) {
  p->changeState(Waiting::instance());
}

void Running::interrupt(process *p) {
  p->changeState(Ready::instance());
}

void Running::exit(process *p) {
  p->changeState(Terminated::instance());
}
