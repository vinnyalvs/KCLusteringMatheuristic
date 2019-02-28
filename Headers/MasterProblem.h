#pragma once
#include "OptCplex.h"
#include "OptGurobi.h"
#include "Environment.h"
#include "ShortSolution.h"
#include "Utils.h"
#include <cmath>
#include <string>
class MasterProblem
{
public:
	MasterProblem(int id,int solver,Environment *env);
	MasterProblem();
	void buildMasterProblem();

	void setEnvironment(Environment *env);
	void setSolutions(vector <ShortSolution*> solutions);

	vector <vector<int>> getClusters();

	void setParams(Param p);
	~MasterProblem();
private:
	int id;
	int solver; // if 1 use cplex, -1 use gurobi
	vector<vector<int>> clusters;
	Model* model;
	vector <ShortSolution*> solutions;
	ShortSolution *bestSolution;

	 int numClusters;
	Environment *env;
	Param param;
	vector <vector<int>> clustersExactMethod;


};

