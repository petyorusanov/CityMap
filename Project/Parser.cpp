#include "Parser.h"

Parser::Parser() : file(), currentReadData(), CityMap()
{

}

Parser::Parser(VectorOfCrossroads& storage) : file(), currentReadData(), CityMap(storage)
{

}

void Parser::Open(string fileName)
{
	file.open(fileName, ios::in);
	while (!file.eof())
	{
		getline(file, currentReadData);
		parseLine();
	}
	Close();
}

void Parser::Close()
{
	file.close();
}

void Parser::parseLine()
{
	unsigned int curr_index = 0;
	unsigned int size = currentReadData.size();
	parseInitialCrossroad(curr_index);
	while (curr_index < size)
	{
		curr_index++;
		string crossroad = parseTerminalCrossroad(curr_index);
		curr_index++;
		unsigned int length = parseLength(curr_index);
		CityMap.addTerminalCrossroad(crossroad, length);
	}
}

void Parser::parseInitialCrossroad(unsigned int& index)
{
	string crossroad;
	unsigned int size = currentReadData.size();
	while (index < size && currentReadData.at(index) != ' ')
	{
		crossroad.push_back(currentReadData.at(index));
		index++;
	}
	CityMap.addInitialCrossroad(crossroad);
}

string Parser::parseTerminalCrossroad(unsigned int& index)
{
	string crossroad;
	while (currentReadData.at(index) != ' ')
	{
		crossroad.push_back(currentReadData.at(index));
		index++;
	}
	return crossroad;
}

unsigned int Parser::parseLength(unsigned int& index)
{
	string crossroad;
	unsigned int size = currentReadData.size();
	while (index < size && currentReadData.at(index) != ' ')
	{
		crossroad.push_back(currentReadData.at(index));
		index++;
	}
	return stoi(crossroad);
}

VectorOfCrossroads Parser::getMap()
{
	return CityMap;
}

