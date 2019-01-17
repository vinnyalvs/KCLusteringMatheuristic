#pragma once

#include "Object.h";
#include "Constructive.h"
#include "ShortSolution.h"
#include "KMeans.h"
#include <cstdlib> 
#include <limits>
#include <utility>
#include <algorithm>


class Genetic
{
private:
	vector <pair <int, int>> matchMeansSolutions(ShortSolution *sol1, ShortSolution *sol2, vector <struct mean> *newMeans);
	pair<struct mean, struct mean> crossMeans(mean m1, mean m2);
	void crossover(ShortSolution * sol1, ShortSolution * sol2);
	void crossover(ShortSolution * sol1, ShortSolution * sol2, ShortSolution *newSol1, ShortSolution *newSol2);
	void mutation(ShortSolution *sol1);
	
	vector <ShortSolution*> *solutions;
	vector <ShortSolution*> *newSols;
	int maxInterations;
	int timeLimit;
	int numAttr;

	int type;
	int numClusters;
	int numObj;


public:
	Genetic(vector<ShortSolution*>* sols, int maxIterations, vector<ShortSolution*>* newPopulation,int numAttr);
	void eliminate(int posIni, double rate, vector<ShortSolution*>* solutions);
	Genetic(vector<ShortSolution>* sols, double timeLimit);
	void newRndPop(vector<ShortSolution*>* solutions, int numSolutions);
	~Genetic();

	int findNearestMean(mean m1, vector<struct mean>* m2);
	int findNearestMean(mean m1, vector<struct mean>* m2, int *aux);
	void rankPopulation(vector<ShortSolution*>* solutions);
	double euclideanDistance(vector<double>* attrA, vector<double>* attrB);

	void refine(ShortSolution * newSol);


	
	double getValueBestSolution();
};

