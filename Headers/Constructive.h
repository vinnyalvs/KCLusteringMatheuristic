#pragma once


#include "Object.h";
#include "ShortSolution.h"
#include <ctime>
#include <algorithm>

using namespace std;

class Constructive
{
public:
	Constructive(int numVertex, int numClusters, vector <Object*> *objects, int type);
	Constructive(int numVertex, int numClusters, vector<Object*>* objects, int type, int seed);
	void Initialize();
	~Constructive();


	double euclideanDistance(double xa, double ya, double xb, double yb);
	double euclideanDistance(Object * a, Object * b);

	void sortEdges();

	vector <Edge> getCandidatesEdges();


	void randomMSTClustering();
	void meansClustering();

	int findMean(unsigned int id);

	int findNearestMean(unsigned int id);

	//vector <Node> getGraph();
	vector <vector<int>> getClusters();
	vector <int> getObjByCluster();

	void setRandomParameter(double alpha);


	void setCandidatesEdges(vector <Edge> edges);

	ShortSolution * getSolution();

	double **distances;
	


private:
	vector <struct mean> means;

	vector <Object*> *objects;

	vector <double> clustersCosts;
	vector <double> finalCosts;
	

	int numObjs;
	int numClusters;

	double rndParameter;
	int numConvexComponents;

	vector <Edge> candidatesEdges;
	vector <Edge> largerEdges;

	vector <Edge> edgesInSolution;

	vector <struct element> elements;

	vector <struct cluster> structClusters;

	vector <vector<int>> clusters;

	vector <int> objByCluster;

	vector <int> parents;

	ShortSolution *solution;

	vector <Object*> graph;

	int seed;

	int type;

	void unionSETs(int idX, int idY);
	int find(int id);

	int numAttr;

};

struct element {
	int parent;
	int rank;
};

struct cluster {
	vector <int> objsId;
	int idCluster;
	int idClusterInSolution;
};

