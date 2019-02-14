#include "stdafx.h"
#include "Cluster.h"


Cluster::Cluster(int id)
{
	this->id = id;
	this->numObjects = 0;

}


Cluster::~Cluster()
{
	this->objects.end();
}

void Cluster::addObject(Object * obj)
{
	numObjects++;
	this->objects.push_back(obj);
	
}



int Cluster::getId()
{
	return id;
}

int Cluster::getNumObjects()
{
	return numObjects;
}

double Cluster::getDegree()
{
	return degree;
}

bool Cluster::removeObject(int id)
{
	vector<Object*>::iterator it;
	int count = 0;
	bool removed=false;
	for (it = objects.begin(); it != objects.end(); it++) {
		count++;
		if ((*it)->getId() == id) {
			objects.erase(objects.begin() + count);
			removed = true;
		}
	}
	return removed;
	
}

double Cluster::getCost()
{
	return this->cost;
}

vector<Object*> Cluster::getObjects()
{
	return objects;
}
