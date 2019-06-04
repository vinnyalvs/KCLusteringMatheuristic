#pragma once

#include "Opt.h";
#include "Environment.h"
#include "ShortSolution.h"
#include "MasterProblem.h"
class ProblemSolver
{

private:
	int solver;
	Environment *env;
	MasterProblem mProblem;
	vector <ShortSolution*> solutions;
	ShortSolution *bestSolution;
	int bestSolutionId;
	Param p;

	vector <vector <int>> clusters;



public:
	ProblemSolver(int solver);
	void setEnvironment(Environment *env);
	Environment *getEnvironment();
	void setSolver(int solver);
	void addSolution(ShortSolution *solution);
	//void findBestSolution();
	ShortSolution *getBestSolution();
	int getBestSolutionId();
	void setParams(Param p);
	void solveProblem();






	vector <vector <int>> getClusters();
	vector<int> objByCluster;

	~ProblemSolver();
};

