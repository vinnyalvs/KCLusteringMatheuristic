#pragma once

#include <vector>
#include <iostream>
#include "Object.h"
#include <limits>

using namespace std;
class ShortSolution
{
public:
	ShortSolution();
	ShortSolution(int numObj, int numClusters);
	void showSolution();
	~ShortSolution();

	void addObject(int objectId, int clusterId);

	int getId();

	void setId(int id);



	bool isObjectInCluster(int objId, int clusterId);

	int getNumClusters();

	int getNumObjs();

	vector <vector<int>> getClusters();
	void printGraph();

	void showObjectByCluster();

	void setObjectByCluster(vector <int> objectByCluster);

	vector <int> getObjectByClusters();


	void setFileName(string name);

	void setObjects(vector <Object*> *objs);

	void setClusters(vector <vector<int>> clusters);

	void setLargerEdges(vector <Edge> largerEdges);
	

	vector <Object*> *getObjects();

	vector <Edge> getEdges();

	void setEdges(vector <Edge> edges);

	void calculateCostClusters();

	void calculateIntraCosts();

	void newCalculateIntraCosts();

	void calculateExternalCosts();

	vector <double> getCostClusters();

	double getCost();

	void calculateSilhouette2();

	void calculateSilhouette();

	double getSilhouette();

	double euclideanDistance(Object * a, Object * b);

	double euclideanDistance(double xa, double ya, double xb, double yb);

	void copySolution(ShortSolution * newSol);

	int findNearestMean(Object * obj);

	double euclideanDistance(vector<double>* attrA, vector<double>* attrB);

	void updateObjectCluster(int objectId, int clusterId);

	void updateAllClusters();

	bool checkViability();

	vector <struct mean> *means;


	void updateClusters();

	int findNearestMean(mean m1, vector<struct mean>* m2);

	bool operator < (ShortSolution cmp1)
	{

		if (cmp1.getSilhouette() < getSilhouette() )
		{
			return true;
		}

		return false;
	}
	vector <vector<int>> clusters;
	vector <int> objectByCluster; // for each object i have the clusters which it belongs

	
	double **distances;

	double Silhouette;

	int numAttr;
private:
	
	

	 //for each cluster i have a subgroup of objects in it

	vector <double> intraCosts;

	vector <double> externalCosts;

	vector <double> costClusters;


	int numObj;

	int numClusters;


	vector <Object*> *objects;

	vector <Edge> edges;
	vector <Edge> largerEdges;

	string fileName;
	
	double sumCosts; //cost of solution

	

};

struct mean {
	unsigned int id;
	vector <double> attrs;
};


