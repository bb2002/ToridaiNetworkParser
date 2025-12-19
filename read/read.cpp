#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../syntax/syntax.h"
#include "../word/word.h"

Syntax* findSyntax(std::vector<Syntax*>& syntaxes, const std::string& name) {
	for (auto* s : syntaxes) {
		if (s->getName() == name) {
			return s;
		}
	}
	return nullptr;
}

Word* findWord(std::vector<Word*>& words, const std::string& text) {
	for (auto* w : words) {
		if (w->getText() == text) {
			return w;
		}
	}
	return nullptr;
}

std::vector<Syntax*> readSyntax() {
	std::ifstream file("syntax.txt");
	if (!file) {
		std::cerr << "Failed to open syntax.txt" << std::endl;
		exit(0);
	}
	std::vector<Syntax*> syntaxes;
	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) {
			continue;
		}

		std::vector<std::string> parts;
		std::stringstream ss(line);
		std::string token;
		while (std::getline(ss, token, ',')) {
			if (!token.empty()) {
				parts.push_back(token);
			}
		}

		if (parts.size() == 2) {
			Syntax* from = findSyntax(syntaxes, parts[0]);
			if (!from) {
				from = new Syntax(parts[0]);
				syntaxes.push_back(from);
			}

			Syntax* to = findSyntax(syntaxes, parts[1]);
			if (!to) {
				to = new Syntax(parts[1]);
				syntaxes.push_back(to);
			}

			from->addNext(to);
		}
	}

	// std::cout << "=-=-=-=- syntax =-=-=-=-" << std::endl;
	// for (auto* s : syntaxes) {
	// 	std::cout << s->getName() << " ->";
	// 	for (auto* n : s->getNext()) {
	// 		std::cout << ' ' << n->getName();
	// 	}
	// 	std::cout << std::endl;
	// }
	// std::cout << "=-=-=-=-=-=-=-=-" << std::endl;

	return syntaxes;
}

std::vector<Word*> readWord(std::vector<Syntax*>& syntaxes) {
	std::ifstream file("word.txt");
	if (!file) {
		std::cerr << "Failed to open word.txt" << std::endl;
		exit(0);
	}

	std::vector<Word*> words;
	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) {
			continue;
		}

		std::vector<std::string> parts;
		std::stringstream ss(line);
		std::string token;
		while (std::getline(ss, token, ',')) {
			if (!token.empty()) {
				parts.push_back(token);
			}
		}

		if (parts.size() == 2) {
			Syntax* syntax = findSyntax(syntaxes, parts[1]);
			if (syntax == nullptr) {
				continue;
			}

			Word* word = findWord(words, parts[0]);
			if (word == nullptr) {
				word = new Word(parts[0]);
				words.push_back(word);
			}

			word->addSyntax(syntax);
		}
	}

	// std::cout << "=-=-=-=- words =-=-=-=-" << std::endl;
	// for (auto* w : words) {
	// 	std::cout << w->getText() << " ->";
	// 	for (auto* s : w->getSyntaxes()) {
	// 		std::cout << ' ' << s->getName();
	// 	}
	// 	std::cout << std::endl;
	// }
	// std::cout << "=-=-=-=-=-=-=-=-" << std::endl;

	return words;
}