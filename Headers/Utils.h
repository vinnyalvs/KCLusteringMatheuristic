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
	void ShowSolution(ShortSolution * solution, string fileName, double s);
	void printEdges(ShortSolution *solution);
	void writeSolution(ShortSolution * solution);
	string fileName;

	int mutationCount;


	Utils();
	Utils(string fileName);
	~Utils();
private:
	int a;
};


