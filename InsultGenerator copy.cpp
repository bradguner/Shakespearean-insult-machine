/*
 * InsultGenerator.cpp
 *
 Created on: Jan 22, 2015
 *      Author: Bradley Guner
 *      OS: Mac OS X
 *      Toolchain: MacOSX GCC
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

#include "InsultGenerator.h"

using namespace std;

FileException::FileException(const string& message) : message(message) {}
string FileException::what() const {return message;}

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& message) : message(message) {}
string NumInsultsOutOfBounds::what() const {return message;}

InsultGenerator::InsultGenerator() : fileSize(0) {}

void InsultGenerator::initialize() {
	fileSize = 0;
	string phrase;
	ifstream inFile("InsultsSource.txt"); //source file
	if (inFile.fail()) {
		throw FileException("File can't be read.");
	}
	string first, second, third;
	while (inFile >> first >> second >> third) {
		firstCol.push_back(first);		//add to back of vector for each column in source file
		secondCol.push_back(second);
		thirdCol.push_back(third);
		fileSize++;
	}
} // end initialize

string InsultGenerator::talkToMe() {
	string insult;
	int first, second, third;

	first = randInt(fileSize);
	second = randInt(fileSize);
	third = randInt(fileSize);
	insult = "Thou " + firstCol.at(first) + " " + secondCol.at(second) + " " + thirdCol.at(third) + "!";

	return insult;
} //end talkToMe

vector<string> InsultGenerator::generate(int insultNum) {
	int max(10000);
	int count(0);
	int num1, num2, num3;
	vector<string> generatedInsults;
	string currentInsult;
	if (insultNum < 1 || insultNum > max)
		throw NumInsultsOutOfBounds("Illegal number of insults!");

	bool boolArray[fileSize][fileSize][fileSize];
	for (num1 = 0; num1 < fileSize; num1++)
		for (num2 = 0; num2 < fileSize; num2++)
			for (num3 = 0; num3 < fileSize; num3++)
				boolArray[num1][num2][num3] = false;
	while (count < insultNum) {
		num1 = randInt(fileSize);
		num2 = randInt(fileSize);
		num3 = randInt(fileSize);
		if (!boolArray[num1][num2][num3]) {
			boolArray[num1][num2][num3] = true;
			count++;
		}
	}
	count = 0;
	for (num1 = 0; num1 < fileSize && count < insultNum; num1++)
		for (num2 = 0; num2 < fileSize && count < insultNum; num2++)
			for (num3 = 0; num3 < fileSize && count < insultNum; num3++)
				if (boolArray[num1][num2][num3]) {
					currentInsult = "Thou " + firstCol.at(num1) + " " + secondCol.at(num2) + " " + thirdCol.at(num3) + "!";
					generatedInsults.push_back(currentInsult);
					count++;
				}
	return generatedInsults;
} //end generate

void InsultGenerator::generateAndSave(string fileName, int insultNum) {
	int count(0);
	int insultLimit(10000);
	if (insultNum < 1 || insultNum > insultLimit)
		throw NumInsultsOutOfBounds("Illegal number of insults!");
	ofstream outFile(fileName.c_str()); //will be file that generated insults are stored into
	vector<string> insultsGenerated;
	if (outFile.fail()) {
		throw FileException("File can't be written.");
	}
	insultsGenerated = generate(insultNum);
	for (string insult : insultsGenerated) { //puts each insult in insultsGenerated vector into outFile
		outFile << insult << endl;
	}
	outFile.close();
} //end generateAndSave


int InsultGenerator::randInt(int limit) {
	return static_cast<int>(1.0 * limit * rand() / RAND_MAX);
} //end randInt
