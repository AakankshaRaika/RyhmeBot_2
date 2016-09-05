#include "RhymeBot-FileParser.h"

using namespace std;

void pronunciationParser(RhymeBot& rhymeBot, string filename){

    ifstream dataFile;
    dataFile.open(filename);

    string line;
    while(!dataFile.eof()) {
        getline(dataFile, line);
        if(line.size() == 0 || !isalpha(line.at(0))){
            continue;
        }

        vector<string> parts = tokenize(line," ");
        string word = parts.at(0);

        vector<Sound> pronounce;

        for(vector<string>::iterator it = parts.begin()+1; it < parts.end(); it++){
            if((*it) != "") {
                Sound thisSound = Sound::getSound(*it);
                pronounce.push_back(thisSound);
            }
        }

        if(word.find_first_of("(") != string::npos){
            word = word.substr(0,word.find_first_of("("));
        }

        transform(word.begin(), word.end(), word.begin(), ::tolower);
        rhymeBot.insertWithPronunciation(word, pronounce);

    }
}


vector<string>& tokenize(string line, string delimiter){
    vector<string>* allSplits = new vector<string>;
    string lineCopy = line;
    while(lineCopy.size() != 0){
        int location = lineCopy.find(delimiter);
        if(location == string::npos){
            allSplits->push_back(lineCopy);
            break;
        }
        allSplits->push_back(lineCopy.substr(0, location));
        lineCopy.erase(0,location + delimiter.size());
    }
    return *allSplits;
}


