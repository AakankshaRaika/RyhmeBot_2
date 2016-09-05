#ifndef UNTITLED_TRIE_H
#define UNTITLED_TRIE_H

#include <iostream>
#include <vector>
#include "RhymeBot.h"
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <chrono>


//Code from a recitation session by Abhishak.
using namespace std;
namespace sc = std::chrono;

typedef std::set<std::string> wordset_t;

class Trie;

typedef std::map<char, Trie*> child_map_t;

class Node {
public:
	Node() { mContent ; mMarker = false; }
	~Node() {}
	Sound content() { return mContent; }
	void setContent(Sound c) { mContent = c; }
	bool wordMarker() { return mMarker; }
	void setWordMarker() { mMarker = true; }
	Node* findChild(Sound c);
	void appendChild(Node* child) { mChildren.push_back(child); }
	vector<Node*> children() {  return mChildren; }

private:
	Sound mContent;
	bool mMarker;
	vector<Node*> mChildren;
};

class Trie {
public:
	Trie(bool end = false) :_size(0), _isEnd(end) {}
	~Trie() {
		for (auto &it : _children) {
			delete it.second;
		}
	}
	void addWord(std::string word);

	bool isWord(std::string word) const;

	void getWords(wordset_t & words, std::string wordSoFar) const;

	void getWordsEndingingWith(std::string prefix, wordset_t & words, std::string wordSoFar) const;

private:
	Node* root;
	child_map_t _children;
	size_t _size;
	bool _isEnd;
	bool isWordEnd() const {
		return _isEnd;
	}
};


#endif //UNTITLED_TRIE_H