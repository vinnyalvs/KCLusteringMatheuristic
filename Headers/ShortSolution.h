#pragma once

#include <vector>
#include <iostream>
#include "Object.h"
#include <limits>

using namespace std;
class ShortSolution
{
public:
	bool chegueiLa;
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

	void calcRandIndex();

	double calculateDissimilarityOne(int objId, int clusterId);

	double calculateDissimilarityTwo(int objId, int clusterId);




	double getSilhouette();

	double euclideanDistance(Object * a, Object * b);

	double euclideanDistance(double xa, double ya, double xb, double yb);

	void copySolution(ShortSolution * newSol);

	int findNearestMean(Object * obj);
	int findNearestMean(Object * obj, int orgMean); //Acha o mais pr�ximo EXCETO o org mean

	double euclideanDistance(vector<double>* attrA, vector<double>* attrB);

	void updateObjectCluster(int objectId, int clusterId);

	void updateAllClusters();

	bool checkViability();

	vector <struct mean> means;


	void updateClusters();

	int findNearestMean(mean m1, vector<struct mean>* m2);

	

	void calcMeans();

	vector <vector<int>> clusters;
    vector <int> objectByCluster; // for each object i have the clusters which it belongs


	double **distances;
	int getObjCluster(int objID);
	double Silhouette;

	int numAttr;

	void tradeCluster(int id, int orgMean);

	bool isConsistent;

	double getDunnIndex();
	double getDBIndex();
	void calculateDBIndex();
	void calcFitness(int FitnessID);
	double getMaxDisp();
	double getMaxDistAmongAllClusters();
	void calcAdaptDunnIndex();
	void calculateDunnIndex();
	double calculateClusterDispersion(int clusterID);
	double calculateClusterDistance(int clusterOne, int clusterTwo);
	double calculateClusterDistance(int clusterOne, int clusterTwo, int objOne, int objTwo);
	void calculateSilhouette3();
	double dunnIndex;
	double dbIndex;
	double fitness;
	double randIndex;

	vector <double> externalDists;
	vector <double> dispersions;
	vector <double> costClusters;
	int numClusters;
	int numObj;
private:



	//for each cluster i have a subgroup of objects in it









	vector <Object*> *objects;

	vector <Edge> edges;
	vector <Edge> largerEdges;

	string fileName;

	double sumCosts; //cost of solution



};

struct mean {
	unsigned int id;
	bool consistent;
	vector <double> attrs;
};

