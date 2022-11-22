// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
std::set<std::string>& wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& store, std::string current);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  // Add your code here
	//for store
	std::set<std::string> empty;
	return wordleHelper(in, floating, dict, empty,"");
}

// Define any helper functions here
std::set<std::string>& wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& store, std::string current)
{
	//base case
	//floating = yellow letters, not in place
	//if the current is fully formed then insert
	if(current.size() == in.size())
	{
		
		//if the current is fully formed then insert
		//checks to make sure real word 
		if (dict.find(current) != dict.end() && floating.size()==0)
		{
			store.insert(current); 
		}
		return store;
	}
	if(in.size()- current.size() < floating.size())
	{
		return store;
	}
	//
	if(in[current.size()] != '-')
	{
		return wordleHelper(in, floating, dict, store, current+in[current.size()]);
	}

	//running through each letter, lowercase
	for(char sign = 'a'; sign <= 'z'; sign++)
	{
		std::string temp2 = floating;
		if(floating.find(sign) != -1)
		{
			temp2.erase(floating.find(sign),1);
		}
		wordleHelper(in, temp2, dict,store,current+sign);
	}
	return store;
}



