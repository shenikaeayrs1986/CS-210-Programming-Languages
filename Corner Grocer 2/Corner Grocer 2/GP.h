#pragma once
#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include <cstdlib>
using namespace std;
class GP
{
public:
	GP();
	GP(string inputFileName, string outputFileName);
	void setInputFileName(string fileName);
	void setOutputFileName(string fileName);
	void readFile();
	void writeFile();
	void printGPMap();
	void printMenu();
	int getMenuOption();
	void executeMenuOption(int choice);
	void searchForItem();
	void run();
	void printGPHistogram();

private:
	map<string, int> gpMap;
	string inputFileName;
	string outputFileName;
};
