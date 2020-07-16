#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stack>
#include "VectorOfCrossroads.h"
using namespace std;

class Parser
{
private:
	VectorOfCrossroads CityMap;
	fstream file;
	string currentReadData;

	void Close();
	
	void parseLine();
	void parseInitialCrossroad(unsigned int&);
	string parseTerminalCrossroad(unsigned int&);
	unsigned int parseLength(unsigned int&);

public:
	Parser();
	Parser(VectorOfCrossroads& storage);
	void Open(string fileName);

	VectorOfCrossroads getMap();
};

