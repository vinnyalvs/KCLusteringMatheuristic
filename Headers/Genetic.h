#pragma once

#include "Object.h";
#include "Constructive.h"
#include "ShortSolution.h"
#include <cstdlib> 
#include <limits>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <set>


class Genetic
{
private:


	void crossover(ShortSolution * sol1, ShortSolution * sol2, ShortSolution *newSol1, ShortSolution *newSol2);
	bool areMeansEqual(mean m1, mean m2);
	void eliminate(int posIni, double rate, vector<ShortSolution*>* solutions);
	int roulette();
	void newRndPop(vector<ShortSolution*>* solutions, int numSolutions);
	int findNearestMean(mean m1, vector<struct mean> m2);
	int findNearestMean(mean m1, vector<struct mean>* m2, int *aux);
	void rankPopulation(vector<ShortSolution*>* solutions);
	void calcRelFitness(vector<ShortSolution*>* solutions);
	double euclideanDistance(vector<double>* attrA, vector<double>* attrB);

	void refine(ShortSolution * newSol);

	void mutation(ShortSolution *sol1);

	
	
	vector <ShortSolution*> *newSols;
	
	int maxInterations;
	int timeLimit;
	int numAttr;
	int mutationRate;
	int crossoverRate;
	int numOffspring;
	double crossDist;
	double bestDist;
	bool isMaxProb; //falso significa que o problema não é de maximização
	int fitType; //qual metodo de fitness utilizar
	int type;
	int numClusters;
	int numObjs;
	double **distances;
	vector <double> fitness;
	vector <Object*> *objects;

public:
	void start(vector<ShortSolution*>* sols, vector<Object*>* objects, double ** distances);
	Genetic(int numGenerations, int numAttr, int numClusters, int numObjs, int mutationRate, int crossoverRate, int numOffspring, double crossDist, double bestDist, bool isMaxProb, int fitType);
	Genetic(vector<ShortSolution*>* sols, int maxIterations, vector<ShortSolution*>* newPopulation, int numAttr, int numClusters, int numObjs, vector<Object*>* objects, double **distances);


	~Genetic();

	
	double getValueBestSolution();

	ShortSolution *MySol;
};

