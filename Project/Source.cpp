#include<iostream>
#include<string>
#include "VectorOfCrossroads.h"
#include "Parser.h"
using namespace std;

void Test1()
{
	VectorOfCrossroads myVector;
	string str1("A");
	string str2("B");
	string str3("C");
	string str4("D");
	string str5("E");
	string str6("F");
	string str7("G");
	myVector.addInitialCrossroad(str1);
	myVector.addTerminalCrossroad(str2, 10);
	//myVector.addTerminalCrossroad(str3, 1);//
	myVector.addInitialCrossroad(str2);
	myVector.addTerminalCrossroad(str3, 5);
	myVector.addTerminalCrossroad(str4, 8);
	myVector.addTerminalCrossroad(str5, 50);
	myVector.addInitialCrossroad(str3);
	//myVector.addTerminalCrossroad(str4, 1);//
	myVector.addTerminalCrossroad(str5, 4);
	//myVector.addTerminalCrossroad(str7, 1);////
	myVector.addInitialCrossroad(str4);
	myVector.addTerminalCrossroad(str2, 10);
	//myVector.addTerminalCrossroad(str5, 1);//
	myVector.addInitialCrossroad(str5);
	myVector.addTerminalCrossroad(str2, 10);
	myVector.addTerminalCrossroad(str6, 7);
	myVector.addInitialCrossroad(str6);
	myVector.addTerminalCrossroad(str1, 15);
	//myVector.addTerminalCrossroad(str7, 1);

	myVector.print();

	cout << endl << "are E and D linked:";
	cout << endl << myVector.areCrossroadsLinked("E", "D") << endl;

	cout << endl << "IsEulerian:" << endl;
	cout << myVector.isEulerian() << endl;

	myVector.printBlockedStreets();

	cout << endl << "isConnected from E?" << endl;
	cout << myVector.isConnected("E") << endl;

	cout << endl << "Cycle exists from E to E:" << endl;
	cout << myVector.isReturnable("E") << endl;

	myVector.printThreeShortestPaths("A", "E");

	myVector.printThreeShortestPaths("A", "G");//

	myVector.printThreeShortestPaths("A", "A");//

	auto cycle = myVector.touristTour();
	cout << "\nTourist tour : " << endl;
	for (auto cross : cycle)
	{
		cout << cross << " ";
	}
	cout << endl;
}

void Test2(VectorOfCrossroads& myVector)
{
	myVector.print();

	cout << endl << "are E and D linked:";
	cout << endl << myVector.areCrossroadsLinked("E", "D") << endl;

	cout << endl << "IsEulerian:" << endl;
	cout << myVector.isEulerian() << endl;

	myVector.printBlockedStreets();

	cout << endl << "isConnected from E?" << endl;
	cout << myVector.isConnected("E") << endl;

	cout << endl << "Cycle exists from E to E:" << endl;
	cout << myVector.isReturnable("E") << endl;

	myVector.printThreeShortestPaths("A", "E");

	myVector.printThreeShortestPaths("A", "G");//

	myVector.printThreeShortestPaths("A", "A");//

	auto cycle = myVector.touristTour();
	cout << "\nTourist tour : " << endl;
	for (auto cross : cycle)
	{
		cout << cross << " ";
	}
	cout << endl;
}

void TestParser()
{
	VectorOfCrossroads myMap;
	Parser fileReader;
	//fileReader.assignMap(myMap);
	fileReader.Open("file2.txt");
	myMap = fileReader.getMap();
	Test2(myMap);
}

int main()
{
	//Test1();

	TestParser();

	system("pause");
	return 0;
}