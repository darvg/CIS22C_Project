//============================================================================
// Name        : Recipe_DataStructure.cpp
// Author      : Khang V. Tran
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

# include <iostream>
# include <fstream>
# include <string>
# include <algorithm>
# include <vector>
# include <sstream>

using namespace std;

# include "Recipe.h"
# include "BST.h"

void readAndStore(ifstream& fin, string& nonKeys,BST<Recipe>& bst);
// This function read in data from the text file
// and create Recipe object
void readAndAppend(ifstream& fin, string& str);
// Read in a file and append every single word
// separated by a space into a string
void getKeysFromString(string field, string nonKeys, vector<string>& keys);

void setKeysForObject(Recipe& recipe, string& nonKeys);

void printStringVector(ostream& out, vector<string> v);
// print out a string vector
// all element are separated with a space

/*
void	 readAndPushBackVector(ifstream& fin, vector<string>& v);
// read in data from a text file and store it in a vector
// this function is meant for appending Non-Key-Word vector
void printStringVector(ostream& out, vector<string>& v);
// print out a string vector
// all element are separated with a space
*/


int main() {
	BST<Recipe> bst;

	// open database and check
	ifstream fin1;
	fin1.open("database.txt");
	if (fin1.fail())
	{
		cout << "Fail to open input file" << endl;
		exit(-1);
	}

	ifstream fin2;
	fin2.open("non_key_words.txt");
	if (fin2.fail())
	{
		cout << "Fail to open non_key_words file" << endl;
		exit(-1);
	}

	string nonKeys = "";
	readAndAppend(fin2, nonKeys);
	cout << (nonKeys) << endl;;
	cout << endl << "**************************************************************" << endl;

/*
	vector<string> nonKeyWords;
	readAndPushBackVector(fin2, nonKeyWords);
	printStringVector(cout, nonKeyWords);
	cout << endl << "**************************************************************" << endl;
*/




	readAndStore(fin1, nonKeys, bst);
	bst.inOrderPrint(cout);






	// close the file openning
	fin1.close();
	fin2.close();
	return 0;
}





void readAndStore(ifstream& fin, string& nonKeys,BST<Recipe>& bst)
{
	string name, category, flavor, buf;
	string ingredients = "";
	string direction = "";
	unsigned time, difficulty;
	vector<string> keys;

	int count = 0;
	while (getline(fin, name))
	{
		count++;
		//cout << count << "." << endl;

		getline(fin, category);
		getline(fin, flavor);

		// read and concatenate ingredients until hitting a #
		do
		{
			getline(fin, buf);
			if (buf.find("#") == std::string::npos) ingredients += buf;
		} while(buf.find("#") == std::string::npos);

		getline(fin, buf);
		time = stoi(buf);

		getline(fin, buf);
		difficulty = stoi(buf);

		// read and concatenate to direction until hitting a #
		do
		{
			getline(fin, buf);
			if (buf.find("#") == std::string::npos) direction += buf;
		} while(buf.find("#") == std::string::npos);

		// get the blankspace
		getline(fin, buf);

		// create the keys vector


		// Create the recipe object
		Recipe recipe(name, category, flavor, ingredients, time, difficulty, direction);
		setKeysForObject(recipe, nonKeys);
		printStringVector(cout, recipe.get_keys());
		cout << endl << "**************************************************************" << endl;


		// Insert the object into the
		bst.insert(recipe);


		// reset Ingredients and Direction for the next recipe to be read in
		ingredients = "";
		direction = "";
	}

}

void readAndAppend(ifstream& fin, string& str)
{
	string buf;
	while (fin >> buf) str += " " + buf;
}

void getKeysFromString(string field, string nonKeys, vector<string>& keys)
{
	istringstream iss(field);
	while(iss)
	{
		string word;
		iss >> word;
		if (nonKeys.find(word) == std::string::npos) keys.push_back(word);
	}
}

void setKeysForObject(Recipe& recipe, string& nonKeys)
{
	vector<string> keys;
	getKeysFromString(recipe.get_name(), nonKeys, keys);
	getKeysFromString(recipe.get_category(), nonKeys, keys);
	getKeysFromString(recipe.get_flavor(), nonKeys, keys);
	getKeysFromString(recipe.get_ingredients(), nonKeys, keys);
	getKeysFromString(recipe.get_direction(), nonKeys, keys);
	recipe.set_keys(keys);
	//printStringVector(cout, keys);
}



void printStringVector(ostream& out, vector<string> v)
{
	for (int i = 0; i < v.size(); i++) out << v[i] << " ";
	out << endl;
}

