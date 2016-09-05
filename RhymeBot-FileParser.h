#ifndef UNTITLED_FILEPARSER_H
#define UNTITLED_FILEPARSER_H

#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include "RhymeBot.h"
#include "RhymeBot-Sound.h"

using namespace std;

//need to handle multiple pronunciations for some RhymeBot

void pronunciationParser(RhymeBot&, string);
vector<string>& tokenize(string line, string delimiter);

#endif //UNTITLED_FILEPARSER_H
