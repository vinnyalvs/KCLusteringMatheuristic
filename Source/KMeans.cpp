#include "../Headers/KMeans.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>



KMeans::KMeans(int k, int maxInterations, vector <Object*> *objects,int numAttr) {
	this->k = k;
	this->maxInterations = maxInterations;
	this->objects = objects;
	this->numAttr = numAttr;
}

double KMeans::euclideanDistance(Object *a, Object *b)
{
	double dist=0.0;
	for (int i = 0; i < numAttr; i++) {

		dist += pow((a->getNormDoubleAttr(i) - b->getNormDoubleAttr(i)),2);
	}
	return sqrt(dist);
}
	
	
void KMeans::readSolution(ShortSolution *s) {
	this->solution = s;


}

void KMeans::buildClusters() {

	int i = 0;
	vector <Object*> ::iterator it;
	it = objects->begin();
	//solution->calculateSilhouette();
	ShortSolution *newSol = new ShortSolution(solution->getNumObjs(), solution->getNumClusters());
	solution->copySolution(newSol);
	// for each object find nearest centroid
	//Quadratic O(n²)
	//Aloca cada objeto apra um mean 
	for (; i < maxInterations; i++) {
		//test convergence
		if (i != 0) {
			while (it != objects->end()) {
				int mean = findNearestMean((*it));
				newSol->updateObjectCluster((*it)->getId(), mean);
				++it;
			}
			newSol->updateAllClusters();
		}
		
		//update each centroid for each object assign to it in previous step
		//Quadratic O(n²)

		for (int j = 0; j < k; j++) {
			double mediaX = 0;
			double mediaY = 0;
			int count = 0;
			double media=0;
			vector <Object*> ::iterator it;
			vector <int> objByCluster = newSol->getObjectByClusters();

			it = objects->begin();
			//0 and 1 are dimensions
			while (it != objects->end()) {
				media = 0;
				if (objByCluster[(*it)->getId() - 1] == j) 
					for (int n = 0; n < numAttr; n++) {
						media += (*it)->getNormDoubleAttr(n);
						mediaX = media / newSol->clusters[j].size();
						newSol->means->at(j).attrs[n] = mediaX;
			    }
				++it;
			}

		}
	
	}
	newSol->calculateSilhouette2();
	int count = 0;
	if (newSol->getSilhouette() > solution->getSilhouette() && newSol->checkViability()) {
		newSol->copySolution(solution);
		//cout << "K Means Melhorou Sol" << endl;
		count = 0;
		//cout << "KMeans:" << newSol->getSilhouette() << endl;

	}

	
}

double KMeans::euclideanDistance(vector <double> *attrA, vector <double> *attrB)
{

	double dist = 0.0;
	for (int i = 0; i<numAttr; i++)
		dist += pow((attrA->at(i) - attrB->at(i)), 2);

	return sqrt(dist);


}

int KMeans::findNearestMean(struct mean m1, vector <struct mean> *m2) {
	int index = 0;
	int count = 0;
	double minDist = numeric_limits<double>::max();
	for (auto mean : *m2) {
		double dist = euclideanDistance(&m1.attrs, &mean.attrs);
		if (minDist > dist) {
			minDist = dist;
			index = count;
		}
		count++;
	}
	return index;
}

int KMeans::findNearestMean(Object *obj)
{
	// O(n)
	int index = 0;
	int count = 0;
	double minDist = numeric_limits<double>::max();
	for (auto m : *solution->means) {
		double dist = euclideanDistance(&obj->getNormDoubleAttrs() , &m.attrs );
		if (minDist > dist) {
			minDist = dist;
			index = count;
		}
		count++;
	}
	return index;
}


KMeans::~KMeans()
{
	/*for (auto o : *objects) {
		delete o;
	}
	delete objects;*/
}

void KMeans::setmaximaX(double value)
{
	this->maximaX = value;
}

void KMeans::setmaximaY(double value)
{
	this->maximaY = value;
}

void KMeans::setminimaX(double value)
{
	this->minimaX = value;
}

void KMeans::setminimaY(double value)
{
	this->minimaY = value;
}



void KMeans::showInfo()
{
	vector <Object*> ::iterator it;
	it = objects->begin();
	while (it != objects->end()) {
		//cout << "Obj " << (*it)->getId() << " Cluster:" << (*it)->clusterId << endl;
		++it;
	}

}

ShortSolution * KMeans::saveShortSolution()
{
	ShortSolution *s = new ShortSolution(objects->size(),k);
	vector <Object*> ::iterator it;
	it = objects->begin();
	int i = 0;
	while (it != objects->end()) {
	//	s->addObject((*it)->getId(), (*it)->id ;
		++it;
		i++;
	}
	return s;

}


void KMeansCluster::addObject(Object * obj)
{

	objects.push_back(obj);
}

void KMeansCluster::removeObject(Object * obj)
{
	objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
}
