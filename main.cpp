#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "read/read.h"
#include "syntax/syntax.h"
#include "word/word.h"

static std::string centerPad(const std::string& s, int width) {
  if ((int)s.size() >= width) {
    return s.substr(0, width);
  }
  int total = width - (int)s.size();
  int left = total / 2;
  int right = total - left;
  return std::string(left, ' ') + s + std::string(right, ' ');
}

void printLine(std::vector<std::string>& line1,
               std::vector<std::string>& line2,
               std::vector<std::string>& line3) {
  for (const auto& cell : line1) {
      std::cout << centerPad(cell, 9);
    }
    std::cout << std::endl;
    for (const auto& cell : line2) {
      std::cout << centerPad(cell, 9);
    }
    std::cout << std::endl;
    for (const auto& cell : line3) {
      std::cout << centerPad(cell, 9);
    }
    std::cout << std::endl;
}

int main() {
  std::vector<Syntax*> syntaxes = readSyntax();
  std::vector<Word*> words = readWord(syntaxes);

  std::cout << "Input: ";
  std::string line;
  std::getline(std::cin, line);
  if (!line.empty() && line.back() == '.') {
    line.pop_back();
  }

  std::vector<std::string> parts;
  std::stringstream ss(line);
  std::string token;
  while (std::getline(ss, token, ' ')) {
    if (!token.empty()) {
      parts.push_back(token);
    }
  }

  std::vector<std::string> line1;
  std::vector<std::string> line2;
  std::vector<std::string> line3;
  line1.push_back("");
  line2.push_back("|");
  line3.push_back("start");
  for (size_t i = 0; i < parts.size(); ++i) {
    printLine(line1, line2, line3);

    Word* currentWord = findWord(words, parts[i]);
    if (currentWord == nullptr) {
      std::cout << parts[i] << " not found in dictionary." << std::endl;
      exit(0);
    }

    std::vector<Syntax*> beforeSyntaxes;
    const auto& currentSyntaxes = currentWord->getSyntaxes();

    if (i > 0) {
      Word* prevWord = findWord(words, parts[i - 1]);
      if (prevWord) {
        beforeSyntaxes = prevWord->getSyntaxes();
      }
    } else {
      Syntax* startSyntax = findSyntax(syntaxes, "start");
      if (startSyntax) {
        beforeSyntaxes.push_back(startSyntax);
      }
    }

    bool hasAny = false;
    Syntax* matchedSyntax = nullptr;
    for (auto* cs : currentSyntaxes) {
      for (auto* bs : beforeSyntaxes) {
        for (auto* nextSyntax : bs->getNext()) {
          if (nextSyntax == cs) {
            hasAny = true;
            matchedSyntax = cs;
            break;
          }
        }
        if (hasAny) break;
      }
      if (hasAny) break;
    }

    if (hasAny) {
      line1.push_back(parts[i]);
      line2.push_back("|");
      line3.push_back(matchedSyntax->getName());
    } else {
      line1.push_back("");
      line2.push_back("INVALID");
      line3.push_back("");
      printLine(line1, line2, line3);
      exit(0);
    }
  }

  std::string lastPart = parts.back();
  Word* lastWord = findWord(words, lastPart);
  std::vector<Syntax*> allowedNextSyntaxes;
  if (lastWord) {
    const auto& lastSyntaxes = lastWord->getSyntaxes();
    for (auto* ls : lastSyntaxes) {
      for (auto* nextSyntax : ls->getNext()) {
        allowedNextSyntaxes.push_back(nextSyntax);
      }
    }
  }

  bool hasEndSyntax = false;
  for (auto* ans : allowedNextSyntaxes) {
    if (ans->getName() == "end") {
      hasEndSyntax = true;
      break;
    }
  }

  if (hasEndSyntax) {
    line1.push_back(".");
    line2.push_back("|");
    line3.push_back("end");
  } else {
    line1.push_back("");
    line2.push_back("INVALID");
    line3.push_back("");
  }
  printLine(line1, line2, line3);
}

