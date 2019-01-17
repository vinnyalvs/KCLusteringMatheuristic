#include "../Headers/ProblemSolver.h"

enum {
	EXATO, 
	FRAC
};



ProblemSolver::ProblemSolver(int solver)
{

	this->solver = solver;
	this->env = new Environment(solver);
	cout << "Alo" << endl;
	this->mProblem =  MasterProblem(0, solver,env);
	
}



void ProblemSolver::setEnvironment(Environment *env)
{
	this->env = env;
}

Environment * ProblemSolver::getEnvironment()
{
	return env;
}

void ProblemSolver::setSolver(int solver)
{
	this->solver = solver;
}

void ProblemSolver::addSolution(ShortSolution * solution)
{
	solutions.push_back(solution);
}

/*void ProblemSolver::findBestSolution()
{
	double bestMetric=0.0;
	for (vector <ShortSolution*>::iterator it = solutions.begin(); it != solutions.end(); ++it) {
		if ((*it)->getSilhouette() > bestMetric ) {
			bestMetric = (*it)->getSilhouette();
			bestSolution = *it;
			bestSolutionId = (*it)->getId();
		}
	}
}*/

ShortSolution *ProblemSolver::getBestSolution()
{
	return bestSolution;
}

int ProblemSolver::getBestSolutionId()
{
	return bestSolutionId;
}

void ProblemSolver::setParams(Param p)
{
	this->p = p;
}

void ProblemSolver::solveProblem()
{
	// build Master Problem
	//mProblem.setEnvironment(env);
	mProblem.setSolutions(solutions);
	mProblem.buildMasterProblem();


	const int numClusters = solutions[0]->getNumClusters();
	int numObjs = solutions[0]->getNumObjs();

	objByCluster.assign(numObjs, 0);
	
	clusters = mProblem.getClusters();

	for (int i = 0; i < clusters.size(); i++) {
		for (int j = 0; j < clusters[i].size(); j++) {
			objByCluster[clusters[i][j] - 1] = i;
		}
	}

	cout << "a" << endl;

	//Column Generation



}

vector<vector<int>> ProblemSolver::getClusters()
{
	 return clusters ;
}

ProblemSolver::~ProblemSolver()
{
	delete env;
}

