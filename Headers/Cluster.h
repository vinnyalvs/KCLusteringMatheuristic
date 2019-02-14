#pragma once
#include "Object.h"
class Cluster
{
public:
	/**
	Cluster constructor
	@param int id cluster id
	@return none
	*/
	Cluster(int id);
	~Cluster();
	/**
	Add on object to cluster
	@param Object object
	@return none
	*/
	void addObject(Object *obj);
	/**
	get cluster id
	@param none
	@return int clusterId
	*/
	int getId();
	/**
	get number of objects in cluster
	@param none
	@return int numObjects
	*/
	int getNumObjects();
	/**
	get the degree of clustering
	@param none
	@return int Degree
	*/
	double getDegree();
	/**
	remove obj form the cluster
	@param int if, object id
	@return bool result, true if the obj was in the cluster and removed, false if it wasn't
	*/
	bool removeObject(int id);

	double getCost();

	vector <Object*> getObjects();
private:
	int id;
	int numObjects;
	vector <Object*> objects;
	double degree;
	double cost;

};

