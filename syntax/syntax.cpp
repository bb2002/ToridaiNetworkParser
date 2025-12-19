#include "syntax.h"

Syntax::Syntax(const std::string& name) : name(name) {}

void Syntax::addNext(Syntax* syntax) {
  next.push_back(syntax);
}

const std::vector<Syntax*>& Syntax::getNext() const {
  return next;
}

const std::string& Syntax::getName() const {
  return name;
}