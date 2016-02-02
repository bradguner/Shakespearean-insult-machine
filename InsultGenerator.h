/*
 * insultgenerator_11bmg8.h
 *
 *  Created on: Jan 22, 2015
 *      Author: Bradley Guner
 *      OS: Mac OS X
 *      Toolchain: MacOSX GCC
 */
#include <vector>
#include <string>
#include <iostream>
#include <exception>

using namespace std;

class InsultGenerator {
	public:
		InsultGenerator();
		void initialize(); //Loads insults into the program from the input file
		string talkToMe(); //Creates one insult
		vector<string> generate(int insultNum); //Returns supplied value of unique insults
		void generateAndSave(string fileName, int insultNum); //Saves a file of the supplied value of unique insults alphabetically

	private:
		int fileSize; //Length of input file
		vector<string> firstCol; //First column of input file insults
		vector<string> secondCol; //Second column of input file insults
		vector<string> thirdCol; //Third column of input file insults
		int randInt(int limit);
}; //end InsultGenerator

//Thrown if the input file can't be read of if the output file can't be created
class FileException {
	public:
		FileException(const string&);
		string what() const;
	private:
		string message;
}; //end FileException

//Thrown if amount of insults to be made is not between 1 and 10,000
class NumInsultsOutOfBounds {
	public:
		NumInsultsOutOfBounds(const string&);
		string what() const;
	private:
		string message;
}; //end NumInsultsOutOfBounds
