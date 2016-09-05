#ifndef UNTITLED_RHYMEBOT_H
#define UNTITLED_RHYMEBOT_H

#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include "RhymeBot-Sound.h"

using namespace std;

enum PART_OF_SPEECH{
    ADJECTIVE, ADVERB, NOUN, SENSE, VERB
};

class RhymeBot {

private:
    // all the data structures you want to use

public:
    void insertWithPronunciation(string, vector<Sound>);
	vector<string> remove_ (string);
	vector<vector<Sound> > findPrun(string);
	vector<string> getkRhymes(string,int);
    int rhymingSyllables(string, string);
	multimap<int, string> getAllRhymes(string);
	string findPerfectWord(string);

};



#endif //UNTITLED_RHYMEBOT_H
