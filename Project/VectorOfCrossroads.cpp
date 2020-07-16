#include "VectorOfCrossroads.h"

bool VectorOfCrossroads::isCrossroadInserted(string givenCrossroad)
{
	for (auto x : TerminalCrossroads)
	{
		if (!givenCrossroad.compare(x.crossroadName))
		{
			return true;
		}
	}
	return false;
}

Crossroad* VectorOfCrossroads::findCrossroad(string givenName)
{
	unsigned int length = InitialCrossroads.size();
	for (unsigned int i = 0; i < length; i++)
	{
		if (!givenName.compare(InitialCrossroads[i].crossroadName))
		{
			return &InitialCrossroads[i];
		}
	}
	return nullptr;
}

unsigned int VectorOfCrossroads::findIndex(string cross)
{
	unsigned int length = TerminalCrossroads.size();
	unsigned int i = 0;
	bool flag = false;
	while (i < length && !flag)
	{
		if (!cross.compare(TerminalCrossroads[i].crossroadName))
		{
			flag = true;
		}
		i++;
	}
	return --i;
}

void VectorOfCrossroads::allPaths(string firstCrossroad, string secondCrossroad, bool visited[], vector<string>& path, unsigned int& path_index)
{
	unsigned int index = findIndex(firstCrossroad);
	visited[index] = true;
	path.resize(TerminalCrossroads.size());
	path[path_index] = firstCrossroad;
	path_index++;
	if (!firstCrossroad.compare(secondCrossroad))
	{
		while (!path.empty() && path.back().compare(secondCrossroad))
		{
			path.pop_back();
		}
		paths.vectorOfPaths.push_back(path);
	}
	else
	{
		list<CrossroadAndLength>::iterator iter;
		Crossroad* init = findCrossroad(firstCrossroad);
		if (init != nullptr)
		{
			for (iter = init->adjacentAccessibleCrossroads.begin(); iter != init->adjacentAccessibleCrossroads.end(); ++iter)
			{
				unsigned int i = findIndex(iter->crossroadName);
				if (!visited[i])
				{
					allPaths(iter->crossroadName, secondCrossroad, visited, path, path_index);
				}
				/*if (!path.empty())
				{
					path.pop_back();
				}*/
			}
		}
	}
	path_index--;
	if (!path.empty())
	{
		path.pop_back();
	}
	visited[index] = false;
}

void VectorOfCrossroads::allAlternativePaths(list<string> blocked, string firstCrossroad, string secondCrossroad, bool visited[], vector<string>& path, unsigned int& path_index)
{
	if (isBlocked(blocked, firstCrossroad) || isBlocked(blocked, secondCrossroad))
	{
		return;
	}
	
	unsigned int index = findIndex(firstCrossroad);
	visited[index] = true;
	path.resize(TerminalCrossroads.size());
	path[path_index] = firstCrossroad;
	path_index++;
	if (!firstCrossroad.compare(secondCrossroad))
	{
		while (!path.empty() && path.back().compare(secondCrossroad))
		{
			path.pop_back();
		}
		paths.vectorOfAlternativePaths.push_back(path);
	}
	else
	{
		list<CrossroadAndLength>::iterator iter;
		Crossroad* init = findCrossroad(firstCrossroad);
		if (init != nullptr)
		{
			for (iter = init->adjacentAccessibleCrossroads.begin(); iter != init->adjacentAccessibleCrossroads.end(); ++iter)
			{
				unsigned int i = findIndex(iter->crossroadName);
				if (!visited[i])
				{
					allAlternativePaths(blocked, iter->crossroadName, secondCrossroad, visited, path, path_index);
				}
				/*if (!path.empty() && !isBlocked(blocked, iter->crossroadName))
				{
					path.pop_back();
				}*/
			}
		}
	}
	path_index--;
	if (!path.empty())
	{
		path.pop_back();
	}
	visited[index] = false;
}

int VectorOfCrossroads::findLength(string firstCrossroad, string secondCrossroad)
{
	auto first = findCrossroad(firstCrossroad);
	list<CrossroadAndLength>::iterator iter;
	for (iter = first->adjacentAccessibleCrossroads.begin(); iter != first->adjacentAccessibleCrossroads.end(); iter++)
	{
		if (!iter->crossroadName.compare(secondCrossroad))
		{
			return iter->lengthOfStreet;
		}
	}
	return 0;
}

vector<vector<string>> VectorOfCrossroads::findThreeShortestPaths(int lengths[])
{
	vector<vector<string>> result;
	unsigned int n = paths.vectorOfPaths.size();
	int* temp = new int[n];
	for (unsigned int i = 0; i < n; i++)
	{
		temp[i] = lengths[i];
	}
	sort(lengths, lengths + n);
	for (unsigned int i = 0; i < 3; i++)
	{
		unsigned int j = 0;
		while (lengths[i] != temp[j])
		{
			j++;
		}
		result.push_back(paths.vectorOfPaths.at(j));
	}
	paths.vectorOfPaths.clear();
	return result;
}

vector<vector<string>> VectorOfCrossroads::findThreeShortestAlternativePaths(int lengths[])
{
	vector<vector<string>> result;
	unsigned int n = paths.vectorOfAlternativePaths.size();
	int* temp = new int[n];
	for (unsigned int i = 0; i < n; i++)
	{
		temp[i] = lengths[i];
	}
	sort(lengths, lengths + n);
	for (unsigned int i = 0; i < 3; i++)
	{
		unsigned int j = 0;
		while (lengths[i] != temp[j])
		{
			j++;
		}
		result.push_back(paths.vectorOfAlternativePaths[j]);
	}
	paths.vectorOfAlternativePaths.clear();
	return result;
}

bool VectorOfCrossroads::isBlocked(list<string> blocked, string crossroad)
{
	list<string>::iterator iter;
	for (iter = blocked.begin(); iter != blocked.end(); iter++)
	{
		if (!iter->compare(crossroad))
		{
			return true;
		}
	}
	return false;
}

bool VectorOfCrossroads::isEulerian()
{
	if (!isStronglyConnected())
	{
		return false;
	}
	vector<unsigned int> power;
	unsigned int size = TerminalCrossroads.size();
	power.resize(size);
	for (unsigned int i = 0; i < size; i++)
	{
		power[i] = 0;
		if (findCrossroad(TerminalCrossroads[i].crossroadName) != nullptr)
		{
			power[i] = findCrossroad(TerminalCrossroads[i].crossroadName)->adjacentAccessibleCrossroads.size();
		}
		if (power[i] != TerminalCrossroads[i].numberOfStreets)
		{
			return false;
		}
	}
	return true;
}

bool VectorOfCrossroads::isStronglyConnected()
{
	unsigned int size = TerminalCrossroads.size();
	unsigned int crossroadInit;
	for (unsigned int i = 0; i < size; i++)
	{
		crossroadInit = 0;
		if (findCrossroad(TerminalCrossroads[i].crossroadName) != nullptr)
		{
			crossroadInit = findCrossroad(TerminalCrossroads[i].crossroadName)->adjacentAccessibleCrossroads.size();
		}
		if (TerminalCrossroads[i].numberOfStreets >= 1 || crossroadInit >= 1)
		{
			if (!isConnected(TerminalCrossroads[i].crossroadName))
			{
				return false;
			}
		}
	}
	return true;
}

VectorOfCrossroads::VectorOfCrossroads() : TerminalCrossroads(), InitialCrossroads()
{
}

VectorOfCrossroads::~VectorOfCrossroads()
{
}

void VectorOfCrossroads::addInitialCrossroad(string givenCrossroad)
{
	if (!isCrossroadInserted(givenCrossroad))
	{
		NumberOfEnteringStreets temp(givenCrossroad, 0);
		TerminalCrossroads.push_back(temp);
	}
	Crossroad temp(givenCrossroad);
	InitialCrossroads.push_back(temp);
}

void VectorOfCrossroads::addTerminalCrossroad(string givenCrossroad, unsigned int givenLength)
{
	if (!isCrossroadInserted(givenCrossroad))
	{
		NumberOfEnteringStreets pair(givenCrossroad, 1);
		TerminalCrossroads.push_back(pair);
	}
	else
	{
		unsigned int i = 0;
		bool flag = false;
		while (i < TerminalCrossroads.size() && !flag)
		{
			if (!givenCrossroad.compare(TerminalCrossroads[i].crossroadName))
			{
				TerminalCrossroads[i].numberOfStreets++;
				flag = true;
			}
			i++;
		}
	}
	CrossroadAndLength temp(givenCrossroad, givenLength);
	InitialCrossroads.back().adjacentAccessibleCrossroads.push_back(temp);
}

bool VectorOfCrossroads::areCrossroadsLinked(string firstCrossroad, string secondCrossroad)
{
	if (!firstCrossroad.compare(secondCrossroad))
	{
		return true;
	}

	const unsigned int numberOfCrossroads = TerminalCrossroads.size();
	bool* visited = new bool[numberOfCrossroads];
	for (unsigned int i = 0; i < numberOfCrossroads; i++)
	{
		visited[i] = false;
	}

	list<NumberOfEnteringStreets> queue;

	unsigned int length = TerminalCrossroads.size();
	unsigned int i = 0;
	unsigned int index = findIndex(firstCrossroad);
	visited[index] = true;
	queue.push_back(TerminalCrossroads[index]);

	list<CrossroadAndLength>::iterator iter;

	NumberOfEnteringStreets temp("viktor", 0);

	while (!queue.empty())
	{
		temp = queue.front();
		queue.pop_front();
		index = findIndex(temp.crossroadName);
		Crossroad* init = findCrossroad(TerminalCrossroads[index].crossroadName);
		if (init != nullptr)
		{
			for (iter = init->adjacentAccessibleCrossroads.begin(); iter != init->adjacentAccessibleCrossroads.end(); ++iter)
			{
				if (!iter->crossroadName.compare(secondCrossroad))
				{
					return true;
				}
				length = TerminalCrossroads.size();
				i = 0;
				bool flag = false;
				while (i < length && !flag)
				{
					if (!iter->crossroadName.compare(TerminalCrossroads[i].crossroadName))
					{
						flag = true;
					}
					i++;
				}
				unsigned int j = --i;
				if (!visited[j])
				{
					visited[j] = true;
					temp = TerminalCrossroads[j];
					queue.push_back(temp);
				}
			}
		}
	}

	return false;
}

vector<vector<string>> VectorOfCrossroads::threeShortestPaths(string firstCrossroad, string secondCrossroad)
{
	const unsigned int numberOfCrossroads = TerminalCrossroads.size();
	bool* visited = new bool[numberOfCrossroads];

	vector<string> path;
	path.resize(numberOfCrossroads);

	unsigned int path_index = 0;
	for (unsigned int i = 0; i < numberOfCrossroads; i++)
	{
		visited[i] = false;
	}

	allPaths(firstCrossroad, secondCrossroad, visited, path, path_index);

	//define vector/list of lengths of all paths
	unsigned int numberOfPaths = paths.vectorOfPaths.size();
	if (numberOfPaths <= 3)
	{
		return paths.vectorOfPaths;
	}
	int* lengths = new int[numberOfPaths];

	for (unsigned int i = 0; i < numberOfPaths; i++)
	{
		auto curr = paths.vectorOfPaths.at(i);
		unsigned int j = 0;
		unsigned int size = curr.size();
		lengths[i] = 0;
		while (j < size - 1 && findCrossroad(curr.at(j + 1)) != nullptr)
		{
			auto currCrossroad = findCrossroad(curr.at(j));
			auto nextCrossroad = findCrossroad(curr.at(j + 1));

			lengths[i] += findLength(currCrossroad->crossroadName, nextCrossroad->crossroadName);
			j++;
		}
	}
	return findThreeShortestPaths(lengths);
}

vector<vector<string>> VectorOfCrossroads::threeShortestAlternativePaths(list<string> blockedCrossroads, string firstCrossroad, string secondCrossroad)
{
	const unsigned int numberOfCrossroads = TerminalCrossroads.size();
	bool* visited = new bool[numberOfCrossroads];

	vector<string> path;
	path.resize(numberOfCrossroads);

	unsigned int path_index = 0;
	for (unsigned int i = 0; i < numberOfCrossroads; i++)
	{
		visited[i] = false;
	}

	allAlternativePaths(blockedCrossroads, firstCrossroad, secondCrossroad, visited, path, path_index);

	//define vector/list of lengths of all paths
	unsigned int numberOfPaths = paths.vectorOfAlternativePaths.size();
	if (numberOfPaths <= 3)
	{
		return paths.vectorOfAlternativePaths;
	}
	int* lengths = new int[numberOfPaths];

	for (unsigned int i = 0; i < numberOfPaths; i++)
	{
		auto curr = paths.vectorOfAlternativePaths.at(i);
		unsigned int j = 0;
		unsigned int size = curr.size();
		lengths[i] = 0;
		while (j < size - 1 && findCrossroad(curr.at(j + 1)) != nullptr)
		{
			auto currCrossroad = findCrossroad(curr.at(j));
			auto nextCrossroad = findCrossroad(curr.at(j + 1));

			lengths[i] += findLength(currCrossroad->crossroadName, nextCrossroad->crossroadName);
			j++;
		}
	}
	return findThreeShortestAlternativePaths(lengths);
}

bool VectorOfCrossroads::isReturnable(string crossroad)
{
	const unsigned int numberOfCrossroads = TerminalCrossroads.size();
	bool* visited = new bool[numberOfCrossroads];
	for (unsigned int i = 0; i < numberOfCrossroads; i++)
	{
		visited[i] = false;
	}

	list<NumberOfEnteringStreets> queue;

	unsigned int length = TerminalCrossroads.size();
	unsigned int i = 0;
	bool flag = false;
	while (i < length && !flag)
	{
		if (!crossroad.compare(TerminalCrossroads[i].crossroadName))
		{
			flag = true;
		}
		i++;
	}
	int index = --i;
	visited[index] = true;
	queue.push_back(TerminalCrossroads[index]);

	list<CrossroadAndLength>::iterator iter;

	NumberOfEnteringStreets temp("viktor", 0);

	while (!queue.empty())
	{
		temp = queue.front();
		queue.pop_front();
		index = findIndex(temp.crossroadName);
		Crossroad* init = findCrossroad(TerminalCrossroads[index].crossroadName);
		if (init != nullptr)
		{
			for (iter = init->adjacentAccessibleCrossroads.begin(); iter != init->adjacentAccessibleCrossroads.end(); ++iter)
			{
				if (!iter->crossroadName.compare(crossroad))
				{
					return true;
				}
				length = TerminalCrossroads.size();
				i = 0;
				bool flag = false;
				while (i < length && !flag)
				{
					if (!iter->crossroadName.compare(TerminalCrossroads[i].crossroadName))
					{
						flag = true;
					}
					i++;
				}
				int j = --i;
				if (!visited[j])
				{
					visited[j] = true;
					temp = TerminalCrossroads[j];
					queue.push_back(temp);
				}
			}
		}
	}

	return false;
}

vector<string> VectorOfCrossroads::touristTour()
{
	if (isEulerian())
	{
		auto adj = InitialCrossroads;

		unordered_map<unsigned int, unsigned int> crossCount; //
		unsigned int size = InitialCrossroads.size();
		for (unsigned int i = 0; i < size; i++)
		{
			crossCount[i] = adj[i].adjacentAccessibleCrossroads.size(); //
		}

		if (size == 0)
		{
			return vector<string>();
		}

		stack<int> currPath;

		vector<string> circuit;

		currPath.push(0);
		unsigned int curr_v = 0;

		while (!currPath.empty())
		{
			if (crossCount[curr_v])
			{
				currPath.push(curr_v);

				unsigned int next_v = findIndex(adj[curr_v].adjacentAccessibleCrossroads.back().crossroadName);

				crossCount[curr_v]--;
				adj[curr_v].adjacentAccessibleCrossroads.pop_back();

				curr_v = next_v;
			}

			else
			{
				circuit.push_back(adj[curr_v].crossroadName);

				curr_v = currPath.top();
				currPath.pop();
			}
		}
		vector<string> finalCircuit;

		size = circuit.size();
		finalCircuit.resize(size);
		for (int i = size - 1; i >= 0; i--)
		{
			finalCircuit[size - i - 1] = circuit[i];
		}
		return finalCircuit;
	}
	return vector<string>();
}

bool VectorOfCrossroads::isConnected(string initialCross)
{
	for (auto terminalCross : TerminalCrossroads)
	{
		if (!areCrossroadsLinked(initialCross, terminalCross.crossroadName))
		{
			return false;
		}
	}
	return true;
}

vector<Street> VectorOfCrossroads::blockedStreets()
{
	vector<Street> allBlocked;
	for (auto currInitial : InitialCrossroads)
	{
		for (auto currTerminal : currInitial.adjacentAccessibleCrossroads)
		{
			if (findCrossroad(currTerminal.crossroadName) == nullptr)
			{
				Street blocked(currInitial.crossroadName, currTerminal.crossroadName);
				allBlocked.push_back(blocked);
			}
		}
	}
	return allBlocked;
}

void VectorOfCrossroads::print()
{
	unsigned int length = InitialCrossroads.size();
	unsigned int length2 = TerminalCrossroads.size();

	for (unsigned int i = 0; i < length; i++)
	{
		cout << InitialCrossroads[i].crossroadName << " ";
		list<CrossroadAndLength>::iterator iter;
		for (iter = InitialCrossroads[i].adjacentAccessibleCrossroads.begin(); iter != InitialCrossroads[i].adjacentAccessibleCrossroads.end(); ++iter)
		{
			cout << iter->crossroadName << " ";
			cout << iter->lengthOfStreet << " ";
		}
		cout << endl;
	}
	cout << "\nKolko ulici zavyrshvat v dadeno krystovishte" << endl;
	for (unsigned int j = 0; j < length2; j++)
	{
		cout << TerminalCrossroads[j].crossroadName << " ";
		cout << TerminalCrossroads[j].numberOfStreets << endl;
	}
}

void VectorOfCrossroads::printBlockedStreets()
{
	cout << endl << "Blocked Streets:" << endl;
	unsigned int length = blockedStreets().size();
	vector<Street> temp(blockedStreets());
	for (unsigned int i = 0; i < length; i++)
	{
		cout << temp[i].initialCrossroad << " ";
		cout << temp[i].terminalCrossroad << endl;
	}
}

void VectorOfCrossroads::printThreeShortestPaths(string first, string second)
{
	vector<vector<string>> result = threeShortestPaths(first, second);
	cout << endl << "Shortest paths:" << endl;
	unsigned int numberOfPaths = result.size();
	for (unsigned int i = 0; i < numberOfPaths; i++)
	{
		cout << "\n" << i << ":\n";
		unsigned int n = result.at(i).size();
		for (unsigned int j = 0; j < n; j++)
		{
			cout << result.at(i).at(j) << " ";
		}
		cout << endl;
	}



	list<string> myList = { "C" };
	vector<vector<string>> result2 = threeShortestAlternativePaths(myList, first, second);
	cout << endl << "Shortest alternative paths:" << endl;
	unsigned int numberOfPaths2 = result2.size();
	for (unsigned int i = 0; i < numberOfPaths2; i++)
	{
		/*cout << "\n" << i << ":\n";
		unsigned int j = 0;
		while (result2.at(i).at(j) != string())
		{
			cout << result2.at(i).at(j) << " ";
			j++;
		}
		cout << endl;*/

		cout << "\n" << i << ":\n";
		unsigned int n = result2.at(i).size();
		for (unsigned int j = 0; j < n; j++)
		{
			cout << result2.at(i).at(j) << " ";
		}
		cout << endl;
	}

	paths.clear();
}
