/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    /* Your code goes here! */
    ifstream word_list(word_list_fname);
    string line;
	vector<string> words;
	if (word_list.is_open()) {
		while (getline(word_list, line)) {
			if (line.length()>0) {
				words.push_back(line);
			}
        }
    }
	for(auto & eachWord : words)
	{
		string first;
		string second;
		first.append(eachWord.begin()+1,eachWord.end());
		second.append(eachWord.begin(),eachWord.begin()+1);
		second.append(eachWord.begin()+2,eachWord.end());
		if(d.homophones(eachWord, first) && d.homophones(eachWord, second))
		{	
			std::tuple<std::string, std::string, std::string> answer;
			std::get<0>(answer) = eachWord; 
			std::get<1>(answer) = first;
			std::get<2>(answer) = second;
			ret.push_back(answer);
		}			 
	}
	return ret;

}
