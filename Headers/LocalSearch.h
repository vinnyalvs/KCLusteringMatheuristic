#pragma once
#include "ShortSolution.h"
#include <vector>
class LocalSearch
{
public:
	LocalSearch(ShortSolution *sol, int numMaxIt);
	~LocalSearch();

	void beginLocalSearch();

	void generateSolutions();

	ShortSolution *getBestSol();

private:
	int numMaxIt;
	double bestValue;
	ShortSolution *bestSol;
	std::vector <ShortSolution> solutions;
	ShortSolution *initialSol;

};

