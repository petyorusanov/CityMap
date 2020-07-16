#pragma once
#include<iostream>
#include<list>
#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<stack>
using namespace std;

struct NumberOfEnteringStreets
{
	string crossroadName;
	int numberOfStreets;

	NumberOfEnteringStreets(string inserting, int count)
	{
		crossroadName = inserting;
		numberOfStreets = count;
	};
};
struct CrossroadAndLength
{
	string crossroadName;
	int lengthOfStreet;

	CrossroadAndLength(string inserting, int length)
	{
		crossroadName = inserting;
		lengthOfStreet = length;
	};
};
struct Crossroad
{
	string crossroadName;
	list<CrossroadAndLength> adjacentAccessibleCrossroads;
	Crossroad(string inserting) : adjacentAccessibleCrossroads()
	{
		crossroadName = inserting;
	};
	Crossroad& operator=(const Crossroad& other)
	{
		if (this != &other)
		{
			crossroadName = other.crossroadName;
			adjacentAccessibleCrossroads = other.adjacentAccessibleCrossroads;
		}
		return *this;
	};
};
struct Street
{
	string initialCrossroad;
	string terminalCrossroad;

	Street(string first, string second) : initialCrossroad(first), terminalCrossroad(second) {};
};

class VectorOfCrossroads
{
private:
	vector<NumberOfEnteringStreets> TerminalCrossroads;
	vector<Crossroad> InitialCrossroads;

	struct allPathsStorage
	{
		vector<vector<string>> vectorOfPaths;
		vector<vector<string>> vectorOfAlternativePaths;
		void clear() 
		{
			vectorOfPaths.clear();
			vectorOfAlternativePaths.clear();
		};
	} paths;

	bool isCrossroadInserted(string);
	Crossroad* findCrossroad(string);
	unsigned int findIndex(string);
	void allPaths(string, string, bool[], vector<string>&, unsigned int&);
	void allAlternativePaths(list<string>, string, string, bool[], vector<string>&, unsigned int&);
	int findLength(string , string);
	vector<vector<string>> findThreeShortestPaths(int[]);
	vector<vector<string>> findThreeShortestAlternativePaths(int[]);
	bool isBlocked(list<string>, string);

public:
	VectorOfCrossroads();
	~VectorOfCrossroads();

	void addInitialCrossroad(string);
	void addTerminalCrossroad(string, unsigned int);

	bool isEulerian();  //to be private
	bool isStronglyConnected(); // to be private

	//BFS
	bool areCrossroadsLinked(string, string);											//done
	//find all paths and sort them
	vector<vector<string>> threeShortestPaths(string, string);							//done

	vector<vector<string>> threeShortestAlternativePaths(list<string>, string, string); //done
	//BFS without marking the starting crossroad as bypassed
	bool isReturnable(string);															//done
	//isEulerian
	vector<string> touristTour();														//done
	//BFS for all crossroads
	bool isConnected(string);															//done
	vector<Street> blockedStreets();													//done



	void print();
	void printBlockedStreets();
	void printThreeShortestPaths(string, string);
};