#pragma once
#include "ShortSolution.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


using namespace std;

class Utils
{
public:
	string colorTable(int colorIndex);
	void printGraph(ShortSolution *solution);
	void ShowSolution(ShortSolution *solution);
	void ShowSolution(ShortSolution * solution, string fileName);
	void printEdges(ShortSolution *solution);
	string fileName;

	Utils();
	Utils(string fileName);
	~Utils();
private:
	int a;
};


