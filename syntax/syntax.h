#pragma once

#include <string>
#include <vector>

class Syntax {
  private:
    std::string name;
    std::vector<Syntax*> next;

  public:
    Syntax(const std::string& name);
    void addNext(Syntax* syntax);
    const std::vector<Syntax*>& getNext() const;
    const std::string& getName() const;
};
