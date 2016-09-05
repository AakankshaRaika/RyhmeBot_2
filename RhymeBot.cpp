#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include <unordered_set>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "RhymeBot.h"
#include "RhymeBot-FileParser.h"
#include "RhymeBot-Trie.h"

map<string, vector<Sound> > mySoundMap;
map<string, multimap<int, string> > myRhymeMap;
multimap<int, string> myRhymePhraseMap;
std::multimap<int, string>::reverse_iterator rit;
std::map<string, vector<Sound>>::iterator it;
vector<Sound> phrasePrun;
vector<Sound> phrase2Prun;
vector<Sound> currentPhrasePrun;
vector<string> phraseVectors;
vector<string> phraseMyVectors;

void RhymeBot::insertWithPronunciation(string phrase, vector<Sound> pronunciation) {
	mySoundMap.insert(std::pair<string, vector<Sound> > (phrase , pronunciation));
	phraseVectors.push_back(phrase);
}

vector<string> RhymeBot::remove_(string phrase) {
	vector<string> myPhraseVector;
	int index = 0;
	int index2 = 0;
	string temp = phrase;
	for (int i = 0; i < phrase.size();i++) {
cout << temp << endl;
		myPhraseVector.push_back(phrase.substr(index2, phrase.find_first_of('_')));
		temp = phrase.substr(phrase.find_first_of('_') + 1, phrase.size() - 1);
cout << temp << endl;
		if (temp.find_first_of('_') != true) {
			myPhraseVector.push_back(temp);
			break;
		}
	}
cout << "WORKING FINE" << endl;
	return myPhraseVector;
}
vector<vector<Sound>> RhymeBot::findPrun(string phrase) {
	vector<vector<Sound>> thePhrase;
	vector<string> phraseMyVectorsLocal =remove_(phrase);
	string word = "";
	Sound mysound;
std::cout << phraseMyVectorsLocal.size() << endl;
	for (int i = 0; i < phraseMyVectorsLocal.size(); i++) {
		word = phraseMyVectorsLocal.at(i);
		it = mySoundMap.find(word);
cout << word << endl;//given coorect values
         if (it != mySoundMap.end()) {
			 cout << "in the found loop" << endl;
	        phrase2Prun = mySoundMap[word];
	        thePhrase.push_back(phrase2Prun);
	        cout << phrase2Prun.size() << endl;
            }
	}
	return thePhrase;
}


//COUNTING RHYMING SYLLABLES BETWEEN 2 PHRASES //trie will do this for me
int RhymeBot::rhymingSyllables(string phrase1, string phrase2) {
	int numOfRhymingSyllables = 0;
	vector<vector<Sound>> ph1 = findPrun(phrase1);//vector of prun of phrase1 for some reason not taking prun in 
	vector<vector<Sound>> ph2 = findPrun(phrase2);//vector of prun of phrase2 for some reason not taking prun in
	
	int i = ph1.size() - 1;
	int j = ph2.size() - 1;

	while((i >= 0) && (j >= 0)) {
		vector<Sound> ph11 = ph1.at(i);
		int ii = ph11.size() - 1;
		vector<Sound> ph22 = ph2.at(i);
		int jj = ph22.size() - 1;
			if (ph11.at(ii) == ph22.at(jj)) {
				numOfRhymingSyllables++;
			}
			if (phrasePrun.at(i) != phrase2Prun.at(j)) {
				return numOfRhymingSyllables;
			}
			i--;
			j--;
		}
		
	return numOfRhymingSyllables;
}


multimap<int,string> RhymeBot::getAllRhymes(string phrase) {
	multimap<int, string> myRhymePhraseMapLocal ;
	for (unsigned int j = 0; j < phraseVectors.size(); j++) {
		string myPhrase = phraseVectors.at(j);
		int rhymeNum = rhymingSyllables(phrase, myPhrase);
		if (rhymeNum >= 1) {
			myRhymePhraseMap.insert(std::pair<int, string>(rhymeNum,myPhrase));
		}
	}
	myRhymePhraseMapLocal = myRhymePhraseMap;
	myRhymeMap.insert(std::pair<string , multimap<int, string> >(phrase, myRhymePhraseMap));
	return myRhymePhraseMapLocal ;
//I WANT TO ADD THIS TO A TRIE IN THE BASES OF NUMBER OF RHYMES AND TAKE THE FIRST CHILD AS BEST RHYME
}

//GIVE ME K RHYMES FOR THE PHRASE I WANT TO USE A TRIE 
//SOMETHING IS WROOOONG WITH THIS DOESNT LOOK RIGHT
vector<string> RhymeBot::getkRhymes(string phrase ,int k) {
	vector<string> rhymingPhrases;
	myRhymePhraseMap = getAllRhymes(phrase);
	int i = 0;
	for (rit = myRhymePhraseMap.rbegin(); rit != myRhymePhraseMap.rend() && i < k; ++rit) {
		rhymingPhrases.push_back(rit->second);
		cout << rit->second << endl;
		i++;
	}
	//delete &myRhymePhraseMap;
	return rhymingPhrases;
}

string RhymeBot::findPerfectWord(string phrase) {
	vector<string> myphrase = getkRhymes(phrase, 1);
	string my = myphrase.at(0);
	cout << my << endl;
	return my;
}



//--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//RUN.CPP//



//CALL THE INSERT FUNCTION HERE TO MAKE UR MAPS 

//
bool rhymingSyllablesCase(string word1, string word2, int expected, RhymeBot& rhymeBot) {
	int computed = rhymeBot.rhymingSyllables(word1, word2);
	if (computed != expected) {
		cout << "Computed \'" << word1 << "\" and \"" << word2 << "\" to rhyme " << computed << " syllables" << endl;
		cout << "Expected: " << expected << endl;
		return false;
	}
	return true;
}

bool kRhymesCase(string word, int k, vector<string> expected, RhymeBot &rhymeBot) {
	vector<string> computed = rhymeBot.getkRhymes(word,k);
	if (computed != expected) {
		cout << "KRhymeCase Failed" << endl;
		return false;
	}
	return true;
}

void rhymingSyllablesTest(RhymeBot& rhymeBot) {
	bool testPassed = true;
	int expected;
	string word1;
	string word2;
	word1 = "ZIPPERER";
	word2 = "ZIPPER";
	expected = 1;
    rhymingSyllablesCase(word1,word2, expected, rhymeBot);
}

void kRhymesTests(RhymeBot& rhymeBot) {
	bool testPassed = true;
	vector<string> expected;
	string word;
	word = "fragmented_blowfish";
	expected.at(0) = "manned blowfish";
	expected.at(1) = "cocky blowfish";
	expected.at(2) = "theatrical blowfish";
	expected.at(3) = "obnoxious blowfish";
	testPassed &= kRhymesCase(word, 4, expected, rhymeBot);
}



int main(int argc, char* argv[]){

	time_t start, end;
	time(&start);
    
	RhymeBot rhymeBot;
    Sound::init();
    string dictionaryFile = "cmudict-0.7b";

    pronunciationParser(rhymeBot, dictionaryFile);
    rhymingSyllablesTest(rhymeBot);
	kRhymesTests(rhymeBot);
	delete &myRhymePhraseMap;
	time(&end);
	double dif = difftime(end, start);
	printf("Elasped time is %.2lf seconds.", dif);
	//system("pause");//REMOVE THE LINE BEFORE SUBMITTING
    return 0;
}

