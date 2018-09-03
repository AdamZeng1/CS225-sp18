/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
	ifstream word_list(filename);
	string line;
	if (word_list.is_open()) {
		while (getline(word_list, line)) {
			//std::map<std::string, std::vector<std::string>>::iterator iter = dict.find(line.sort());
			//if (iter != dict.end()) {
				string line_sort = line;
				std::sort(line_sort.begin(), line_sort.end());
				dict[line_sort].push_back(line);
			//}
		}
	}

}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
	for (auto & word : words) {
		string word_sort = word;
		std::sort(word_sort.begin(), word_sort.end());
		dict[word_sort].push_back(word);
	}
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
	string word_sort = word;
	std::sort(word_sort.begin(), word_sort.end());
	if (dict.find(word_sort) == dict.end())
	{
		return vector<string>();
	}
    return dict.at(word_sort);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
	vector<vector<string>> out;
	for (auto & line : dict) {
		if (line.second.size() >= 2) {
			out.push_back(line.second);
		}
	}
    return out;

}
