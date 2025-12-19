#pragma once

#include <string>
#include "../syntax/syntax.h"

class Word {
  private:
    std::string text;
    std::vector<Syntax*> syntaxes;

  public:
    Word(const std::string& text);
    const std::string& getText() const;
    const std::vector<Syntax*>& getSyntaxes() const;
    void addSyntax(Syntax* syntax);
};
