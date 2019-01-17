#include "../Headers/ShortSolution.h"



ShortSolution::ShortSolution()
{
}

ShortSolution::ShortSolution(int numObj, int numClusters)
{
	this->numObj = numObj;
	this->numClusters = numClusters;
	clusters.reserve(numClusters);
	vector <int> a;
	clusters.assign(numClusters, a);
	costClusters.assign(numClusters, 0.0);
	intraCosts.assign(numClusters, 0.0);
	externalCosts.assign(numClusters, 0.0);



	for (size_t i = 0; i < clusters.size(); i++) {
		clusters[i].reserve(numObj);
	}



	objectByCluster.assign(numObj, 0);

}




void ShortSolution::showSolution()
{
	cout << "Para " << clusters.size() << " clusters: " << endl;
	for (int i = 0; i < clusters.size(); i++) {
		cout << "Cluster " << i + 1 << " Contem " << clusters[i].size() << " objetos" << endl;
		for (int j = 0; j < clusters[i].size(); j++) {
			cout << clusters[i][j] << " ";
		}
		cout << endl;
	}
}


ShortSolution::~ShortSolution()
{
	for (auto o : *objects) {
		delete o;
	}

	delete objects;


}

void ShortSolution::addObject(int objectId, int clusterId)
{

	clusters[clusterId].push_back(objectId);
	//objectByCluster[objectId-1] = clusterId;


}







bool ShortSolution::isObjectInCluster(int objId, int clusterId)
{
	bool check = false;

	if (objectByCluster[objId] == clusterId) {
		check = true;
	}


	return check;


}

int ShortSolution::getNumClusters()
{
	return numClusters;
}

int ShortSolution::getNumObjs()
{
	return numObj;
}



vector<vector<int>> ShortSolution::getClusters()
{
	return clusters;
}

void ShortSolution::printGraph()
{

	cout << "Para " << clusters.size() << " clusters: " << endl;
	for (size_t i = 0; i < clusters.size(); i++) {
		cout << "Cluster " << i + 1 << " Contem " << clusters[i].size() << " objetos" << endl;
		for (size_t j = 0; j < clusters[i].size(); j++) {
			cout << clusters[i][j] << " ";
		}
		cout << endl;
	}
}

void ShortSolution::showObjectByCluster() {
	for (vector <int>::iterator it = objectByCluster.begin(); it != objectByCluster.end(); it++) {
		cout << *it << endl;
	}
}

void ShortSolution::setObjectByCluster(vector<int> objectByCluster)
{
	this->objectByCluster = objectByCluster;
}

vector<int> ShortSolution::getObjectByClusters()
{
	return this->objectByCluster;
}

void ShortSolution::setFileName(string name)
{
	this->fileName = name;
}

void ShortSolution::setObjects(vector<Object*> *objs)
{


	this->objects = objs;
}

void ShortSolution::setClusters(vector<vector<int>> clusters)
{
	this->clusters = clusters;
}

void ShortSolution::setLargerEdges(vector<Edge> largerEdges)
{

	this->largerEdges = largerEdges;

}



vector<Object*> *ShortSolution::getObjects()
{
	return this->objects;
}

vector<Edge> ShortSolution::getEdges()
{
	return edges;
}

void ShortSolution::setEdges(vector<Edge> edges)
{
	this->edges = edges;
}

void ShortSolution::calculateCostClusters()
{


	//newCalculateIntraCosts();

	calculateIntraCosts();

	calculateExternalCosts();

	sumCosts = 0.0;

	for (size_t i = 0; i < numClusters; i++) {
		costClusters[i] = intraCosts[i] + externalCosts[i];
		sumCosts += costClusters[i];
	}



	//cout << "costs calculated" << endl;

}

void ShortSolution::calculateIntraCosts()
{


	//Para cada cluster i com k objetos
	for (int i = 0; i < clusters.size(); i++) {
		//Para cada objeto j Node cluster i
		double soma = 0;
		for (int j = 0; j < clusters[i].size(); j++) {
			//Somatorio das distancias do obj j aos outros k-1 objetos do cluster
			// soma += distancia obj j
			for (int k = j; k < clusters[i].size(); k++) {
				if (j != k) {
					//cout << "J: " << j << " K " << k << endl;
					//double a = objects->at(j)->getDistance(k - 1);
					soma += distances[clusters[i][j] - 1][k - 1];
				}
			}
		}
		intraCosts[i] = soma/clusters[i].size();

	//	cout << intraCosts[i]  << endl;
	}
	

	


}

void ShortSolution::newCalculateIntraCosts()
{

	for (int i = 0; i < clusters.size(); i++) {
		//Para cada objeto j Node cluster i
		double max = 0;
		for (int j = 0; j < clusters[i].size(); j++) {
			//Somatorio das distancias do obj j aos outros k-1 objetos do cluster
			// soma += distancia obj j
			for (int k = j; k < clusters[i].size(); k++) {
				if (j != k) {
					if(distances[clusters[i][j] - 1][k - 1] > max)
					     max = distances[clusters[i][j] - 1][k - 1];
				}
			}
		}
		intraCosts[i] = max;
	}
	
	

}

void ShortSolution::calculateExternalCosts()
{



}

vector<double> ShortSolution::getCostClusters()
{
	return costClusters;
}

double ShortSolution::getCost() {
	return sumCosts;

}


void ShortSolution::calculateSilhouette2() {
	vector <double> silhouettes;
	double max;
	for (int n = 1; n <= numObj; n++) {
		int clusterObj = objectByCluster[n - 1];
		//dissimilaridade1
		double a = 0;
		if (clusters[clusterObj].size() == 1)
			a = 0;
		else {
			double sumDists = 0.0;
			for (int i = 0; i < clusters[clusterObj].size(); i++) {
				if ((i + 1) != n)
					sumDists += distances[clusters[clusterObj][i] - 1][n - 1];
					
			}
			a = sumDists / (float)(clusters[clusterObj].size() - 1);
		}
		//dissimilaridade2
		double b = 0;
		int closestCluster = 0;
		double minDist = std::numeric_limits<double>::max();
		for (int i = 1; i <= numObj; i++) {
			double d = 0;
			if (n != i) {
				d = distances[n - 1][i - 1];
				if (d < minDist && objectByCluster[i - 1] != clusterObj) {
					minDist = d;
					closestCluster = objectByCluster[i - 1];
				}
			}
		}

		if (clusters[closestCluster].size() == 1)
			b = 0;
		else {
			double sumDists = 0.0;
			for (int i = 0; i < clusters[closestCluster].size(); i++) {

				if (i != n) {
					sumDists += distances[clusters[closestCluster][i] - 1][n - 1];
				}
			}
			b = sumDists / (float)clusters[closestCluster].size();
		}
		if (a > b)
			max = a;
		else
			max = b;

		double s;
		if (max > 0 || max < 0) {
			s = (b - a) / (max);
		}
		else
			s = 0;

		silhouettes.push_back(s);

	}

	double sum = 0.0;

	for (vector <double>::iterator it = silhouettes.begin(); it != silhouettes.end(); it++) {
		sum += *it;
	}

	Silhouette = sum / numObj;

}


void ShortSolution::calculateSilhouette() {

	vector <double> silhouettes;
	double max;



	for (int n = 1; n <= numObj; n++) {

		int clusterObj = objectByCluster[n - 1];


		//dissimilaridade1
		double a=0;
		if (clusters[clusterObj].size() == 1)
			a = 0;
		else {
			//float m = ((float)1 / (float)(clusters[clusterObj].size()-1));

			double sumDists = 0.0;
			for (int i = 0; i < clusters[clusterObj].size(); i++) {
				if((i+1)!=n)
					sumDists += euclideanDistance(objects->at(clusters[clusterObj][i] - 1), objects->at(n-1)); 
			}
			a = sumDists/(float)(clusters[clusterObj].size()-1);
			//cout << "dist" << sumDists << endl;
		}

		

		//dissimilaridade2
		double b=0;
		int closestCluster = 0;
		double minDist = std::numeric_limits<double>::max();
		for (int i = 1; i <= numObj; i++) {
			double d = 0;
			if (n != i) {
				d = euclideanDistance(objects->at(n-1), objects->at(i-1));
				if (d < minDist && objectByCluster[i - 1] != clusterObj) {
					minDist = d;
					closestCluster = objectByCluster[i - 1];
				}
			}
		}

		//cout << "b 1 " << endl;

		if (clusters[closestCluster].size() == 1)
			b = 0;
		else {
			double m = ((float)1 / (float)clusters[closestCluster].size());

			double sumDists = 0.0;
			
			
			for (int i = 0; i < clusters[closestCluster].size(); i++) {

				if (i != n) {
					sumDists += euclideanDistance(objects->at(clusters[closestCluster][i] - 1), objects->at(n - 1));
				}
	
			}
			
			
			b = sumDists / (float)clusters[closestCluster].size();
		}
			//cout << "b 2 " << endl;


		//	cout << "b 3 " << endl;


		//cout << a << endl;
		//cout << b << endl;
		//cout << "checar se max(a,b)" << endl;
		if (a > b)
			max = a;
		else
			max = b;


		double s;
		if (max > 0 || max < 0) {
			s = (b - a) / (max);
		}
		else
			s = 0;

		//cout << "max" << endl;

		silhouettes.push_back(s);

	//	cout << silhouettes[n-1] << endl;
	}

	double sum = 0.0;

	for (vector <double>::iterator it = silhouettes.begin(); it != silhouettes.end(); it++) {
		sum += *it;
	}

	Silhouette = sum / numObj;

}

double ShortSolution::getSilhouette()
{
	return this->Silhouette;
}


void ShortSolution::copySolution(ShortSolution *newSol) {
	newSol->Silhouette = Silhouette;
	newSol->sumCosts = sumCosts;
	newSol->largerEdges = largerEdges;
	newSol->objects = objects;
	newSol->numObj = numObj;
	newSol->numClusters = numClusters;
	newSol->costClusters = costClusters;
	newSol->externalCosts = externalCosts;
	newSol->intraCosts = intraCosts;
	newSol->clusters = clusters;
	newSol->objectByCluster = objectByCluster;
	newSol->means = means;
	newSol->numAttr = numAttr;
	newSol->distances = distances;
}

void ShortSolution::updateClusters()
{

	vector <Object*> ::iterator it;
	it = objects->begin();
		while (it != objects->end()) {
			int mean = findNearestMean((*it));
			updateObjectCluster((*it)->getId(), mean);
			//solution->addObject((*it)->getId(), mean);
			++it;
		}

		updateAllClusters();
}

int ShortSolution::findNearestMean(struct mean m1, vector <struct mean> *m2) {
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

int ShortSolution::findNearestMean(Object *obj)
{
	// O(n)
	int index = 0;
	int count = 0;
	double minDist = numeric_limits<double>::max();
	for (auto m : *means) {
		double dist = euclideanDistance(&obj->getNormDoubleAttrs(), &m.attrs);
		if (minDist > dist) {
			minDist = dist;
			index = count;
		}
		count++;
	}
	return index;
}

double ShortSolution::euclideanDistance(vector <double> *attrA, vector <double> *attrB)
{
	double dist = 0.0;
	for (int i = 0; i < numAttr; i++) {
		dist += pow((attrA->at(i) - attrB->at(i)), 2);
		
	}

	return sqrt(dist);


}

double ShortSolution::euclideanDistance(Object *a, Object *b)
{
	double dist = 0.0;
	for (int i = 0; i<numAttr; i++)
		dist += pow((a->getNormDoubleAttr(i) - b->getNormDoubleAttr(i)), 2);

	return sqrt(dist);
}

void ShortSolution::updateObjectCluster(int objectId, int clusterId) {
	

	objectByCluster[objectId - 1] = clusterId;
	
}

void ShortSolution::updateAllClusters() {


	vector <int> a;
	clusters.clear();
	clusters.assign(numClusters, a);
	for (size_t i = 0; i < clusters.size(); i++) {
		clusters[i].reserve( numObj );
	}
	int count = 1;
	for (auto o : objectByCluster) {
		addObject(count, o);
		count++;
	}

}

bool ShortSolution::checkViability() {

	
	for (auto c : clusters) {
		if (c.empty())
			return false;
	}

	return true;
	

}