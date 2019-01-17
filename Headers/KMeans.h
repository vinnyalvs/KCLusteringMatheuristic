#pragma once
#include "Object.h";
#include <limits>
#include "ShortSolution.h"
#include <cstdlib> 
class KMeansCluster {
private:
	int idCluster;
	vector <Object*> objects;
public:
	void addObject(Object *obj);
	void removeObject(Object *obj);
	
};
class KMeans
{
public:
	KMeans(int k, int maxInterations, vector<Object*>* objects, int numAttr);
	double euclideanDistance(Object *a, Object *b);

	void readSolution(ShortSolution * s);
	void buildClusters();
	double euclideanDistance(vector<double>* attrA, vector<double>* attrB);
	void setmaximaX(double value);
	void setmaximaY(double value);
	void setminimaX(double value);
	void setminimaY(double value);
	void showInfo();
	ShortSolution * saveShortSolution();
	int findNearestMean(mean m1, vector<struct mean>* m2);
	int findNearestMean(Object *obj);
	~KMeans();
private:
	int k; //num of clusters;
	int valuesTotal, objectsTotal, maxInterations;
	vector <int> clusters;
	vector <Object*> *objects;
	vector <Object> means;
	double maximaX,maximaY;
	double minimaX,minimaY;
	ShortSolution *solution;
	int numAttr;
};

