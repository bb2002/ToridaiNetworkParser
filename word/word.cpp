#include "word.h"

Word::Word(const std::string& text) : text(text) {}

const std::string& Word::getText() const {
  return text;
}

const std::vector<Syntax*>& Word::getSyntaxes() const {
  return syntaxes;
}

void Word::addSyntax(Syntax* syntax) {
  if (!syntax) {
    return;
  }
  for (auto* s : syntaxes) {
    if (s == syntax) {
      return;
    }
  }
  syntaxes.push_back(syntax);
}
