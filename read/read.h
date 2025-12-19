#pragma once

#include <vector>
#include "../syntax/syntax.h"
#include "../word/word.h"

std::vector<Syntax*> readSyntax();

std::vector<Word*> readWord(std::vector<Syntax*>& syntaxes);

Word* findWord(std::vector<Word*>& words, const std::string& text);

Syntax* findSyntax(std::vector<Syntax*>& syntaxes, const std::string& name);