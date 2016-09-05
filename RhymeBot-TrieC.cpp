#include <iostream>
#include <vector>
#include "RhymeBot-Trie.h"
#include "RhymeBot-Sound.h"
using namespace std;

//REDO THE CLASS
//Code is combined with Abhishek's recitation and google research 

void Trie::addWord(std::string word) {
	if (word.length()>0) {
		++_size;
		std::string subword = word.substr(1, word.size() - 1);
		if (_children[word[word.size()-1]]) {
			_children[word[word.size() - 1]]->addWord(subword);
		}
		else {
			Trie* tmp = new Trie(word.size() == 1);
			tmp->addWord(subword);
			_children[word[word.size() - 1]] = tmp;
		}
	}
}
bool Trie::isWord(std::string word) const {
		if (word.length() == 0) {
			return _isEnd;
		}
		std::string cursub;
		Trie const *tmp = this;
		cursub = word;

		while (cursub.length()>0) {
			if (tmp->_children.find(cursub[cursub.size() - 1]) != tmp->_children.end()) {
				tmp = tmp->_children.find(cursub[cursub.size() - 1])->second;
				cursub = cursub.substr(0, cursub.size() - 2);
			}
			else {
				return false;
			}
		}
		return tmp->isWordEnd();
	}
void Trie::getWords(wordset_t &words, std::string wordSoFar = "") const {
		if (_isEnd) {
			words.insert(wordSoFar);
		}
		for (const auto &it : _children) {
			std::string tmp = wordSoFar + string(1, it.first);
			if (it.second && it.second->isWordEnd()) {
				words.insert(tmp);
			}
			it.second->getWords(words, tmp);
		}
	}

void Trie::getWordsEndingingWith(std::string suffix, wordset_t &words, std::string wordSoFar = "") const {
		if (suffix.size() == 0) {
			getWords(words, wordSoFar);
			return;
		}
		std::string subword = suffix.substr(0, suffix.size() - 1);
		if (_children.find(suffix[suffix.size() - 1]) != _children.end()) {
			Trie *tmp = _children.find(suffix[suffix.size() - 1])->second;
			std::string nwsf = wordSoFar + std::string(1, suffix[suffix.size() - 2]);
			tmp->getWordsEndingingWith(subword, words, nwsf);
		}
	}

