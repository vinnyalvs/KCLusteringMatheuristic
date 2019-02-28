﻿#include "../Headers/ShortSolution.h"



ShortSolution::ShortSolution()
{
	chegueiLa = false;
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
	chegueiLa = false;
	isConsistent = false;


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
	/*for (int i = 0; i < objects->size(); ++i) {
		delete objects->at(i);
	}
	delete objects;*/
	
/*	for (int i = 0; i < numObj; i++) {
		delete distances[i];
	}
	delete []distances;*/




}

void ShortSolution::addObject(int objectId, int clusterId)
{

	clusters[clusterId].push_back(objectId);
	isConsistent = false;

}







bool ShortSolution::isObjectInCluster(int objId, int clusterId)
{
	bool check = false;

	if (objectByCluster[objId] == clusterId) {
		check = true;
	} /*if (getObjCluster(objId) == clusterId) {	84		if (objectByCluster[objId] == clusterId) {
87			check = true;	85			check = true;
88		}*/


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
		costClusters[i] = intraCosts[i] - externalCosts[i];
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
	for (int i = 0; i < numClusters; i++) {
		double b = 0;
		int closestCluster = 0;
		double minDist = std::numeric_limits<double>::max();
		for (int j = 0; j < clusters[i].size(); j++) {
			double d;
			for (int k = 1; k <= numObj; k++) {
				if (clusters[i][j] != k && i != objectByCluster[k-1]) {
					d = distances[j][k];
					if (d < minDist) {
						minDist = d;
						closestCluster = objectByCluster[j];
					}
				}
			}
		}
		externalCosts[i] = minDist;
	}
}

vector<double> ShortSolution::getCostClusters()
{
	return costClusters;
}

double ShortSolution::getCost() {
	return sumCosts;

}

// ATENÇÃO: OBJID JA É O VALOR DO INDEX, NÃO É NECESSÁRIO USAR -1
double ShortSolution::calculateDissimilarityOne(int objId,int clusterId) {
	double a;
	double sumDists = 0.0;

	for (int i = 0; i < clusters[clusterId].size(); i++) {
		if (clusters[clusterId][i] != objId)
			sumDists += distances[clusters[clusterId][i]-1][objId-1];

	}
	a = sumDists / (float)(clusters[clusterId].size() - 1);

	// retorna a soma das distancia do objeto para a lista de objetos.
	return a;
}


double ShortSolution::calculateDissimilarityTwo(int objId, int clusterId) {
	double b = 0.0;
	double sumDists = 0.0;
	for (int i = 0; i < clusters[clusterId].size(); i++) {
			sumDists += distances[clusters[clusterId][i]-1][objId-1];
	}
	b = sumDists / (float)clusters[clusterId].size();
	return b;
}

void ShortSolution::calculateSilhouette3() {
	if (!isConsistent) {
		int objetos_errados = 0; //conta objetos errados.
		double mediaSilhueta = 0.0;//guarda a media da silhueta
		int i, j;
		for (i = 0; i < numObj; i++) //varre cada objeto
		{
			double dissimilarityOne = 0.0;//a(i)
			double dissimilarityTwo = 0.0;//b(i)

			if (clusters[objectByCluster[i]].size() > 1) //se tem mais de um elemento no cluster{
				dissimilarityOne = calculateDissimilarityOne((i+1), objectByCluster[i]);//a(i)
			else
				dissimilarityOne = 0;

			int closestCluster = -1;
			dissimilarityTwo = numeric_limits<double>::max();
			for (j = 0; j < numClusters; j++) {  //calcula dissimilaridade entre todos os outros clusters diferentes deste e escolhe a menor
				if (j != objectByCluster[i]) {
					double auxDouble = calculateDissimilarityTwo((i+1), j);
					if (auxDouble < dissimilarityTwo) {
						dissimilarityTwo = auxDouble; //seleciona menor dissimilaridade e coloca em b(i)
						closestCluster = j;
					}
				}
			}

			/*listaObjetos[i]->afinidade_cluster_atual = dissimilaridade1;
			listaObjetos[i]->afinidade_cluster_mais_prox = dissimilaridade2;
			listaObjetos[i]->id_cluster_desejado = listaObjetos[i]->id_cluster;
			listaObjetos[i]->closestCluster = closestCluster; */

			double denominador = (dissimilarityOne > dissimilarityTwo) ? dissimilarityOne : dissimilarityTwo;
			double silhueta;
			if (denominador != 0)
				silhueta = (dissimilarityTwo - dissimilarityOne) / denominador;
			else
				silhueta = 0;

			/*
			if(dissimilaridade2 < dissimilaridade1) // esta mais bem posicionado no cluster mais proximo.
			{
			(*objetos_errados) = (*objetos_errados) + 1;
			listaObjetos[i] ->id_cluster_desejado = closestCluster ;
			} */

			mediaSilhueta += silhueta;//somatorio de s(i)

		}
		Silhouette = mediaSilhueta / numObj;
		//    printf("Tem %d objetos no cluster errado\nValor Fitness: %f.\n", *objetos_errados, mediaSilhueta);
	}
	isConsistent = true;
}




double ShortSolution::getSilhouette()
{
	return this->Silhouette;
}


void ShortSolution::copySolution(ShortSolution *newSol) {
//	newSol->qqu = qqu;
	newSol->dunnIndex = dunnIndex;
	newSol->dbIndex = dbIndex;
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
		isConsistent = false;
}

double ShortSolution::getDunnIndex()
{
	return dunnIndex;
}

double ShortSolution::getDBIndex()
{
	return dbIndex;
}

void ShortSolution::calculateDBIndex()
{

	double maxR = numeric_limits<double>::min();
	for (int i = 0; i < numClusters; i++) {
		double S_i = calculateClusterDispersion(i);
		for (int j = i + 1; j < numClusters; j++) {
			double S_j = calculateClusterDispersion(j);
			double dist = calculateClusterDistance(i, j);
			double R = (S_i + S_j) / dist;
			if (R > maxR)
				maxR = R;
		}
	}

	dbIndex = maxR / numClusters;

}

void ShortSolution::calcFitness(int fitnessID) {
	switch (fitnessID) {
	case 0:
		calculateSilhouette3();
		break;
	case 1:
		calculateDunnIndex();
		break;
	case 2:
		calculateDBIndex();
		break;
	default:
		calculateDunnIndex();
	}
}

void ShortSolution::calculateDunnIndex()
{
	double minDist = numeric_limits<double>::max();
	for (int i = 0; i < numClusters; i++) {
		for (int j = i + 1; j <numClusters; j++) {
			double dist = calculateClusterDistance(i, j);
			if (minDist > dist)
				minDist = dist;
		}
	}

	double maxDisp = numeric_limits<double>::min();
	for (int i = 0; i < numClusters; i++) {
		double disp = calculateClusterDispersion(i);
		if (disp > maxDisp) {
			maxDisp = disp;
		}
	}
	//cout << "-------------" << endl;
	//cout << maxDisp << endl;
	//cout << minDist << endl;
	dunnIndex = minDist / maxDisp;
	//cout << dunnIndex << endl;
	//cout << "-------------" << endl;
}

double ShortSolution::calculateClusterDispersion(int clusterID)
{
	bool a = false;
	//Para cada objeto j do clusterID
	double max = 0;

	for (int j = 0; j < clusters[clusterID].size(); j++) {
		//la�o das distancias do obj j aos outros k-1 objetos do cluster
		for (int k = j + 1; k < clusters[clusterID].size(); k++) {
			if (distances[clusters[clusterID][j] - 1][k] >= max) {
				max = distances[clusters[clusterID][j] - 1][k];
			}
		}
	}
	return max;
}

double ShortSolution::calculateClusterDistance(int clusterOne, int clusterTwo)
{
	return euclideanDistance(&means[clusterOne].attrs, &means[clusterTwo].attrs);
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

void ShortSolution::tradeCluster(int id, int orgMean)
{
	//Removendo obj do cluster original
	vector <int>::iterator j;
	for (j = clusters[orgMean].begin(); j != clusters[orgMean].end();) {
		if (id == (*j)) {
			j = clusters[orgMean].erase(j);
			break;
		}
		else
			j++;

	}
	//Add obj nos clusters
	vector <Object*> ::iterator it;
	it = objects->begin();
	while (it != objects->end()) {
		if ((*it)->getId() == id) {
			int mean = findNearestMean((*it));
			updateObjectCluster((*it)->getId(), mean);
			addObject((*it)->getId(), mean);
			break;
		}	
		++it;
	}

}

int ShortSolution::findNearestMean(Object *obj)
{
	// O(n)
	int index = 0;
	int count = 0;
	double minDist = numeric_limits<double>::max();
	for (auto m : means) {
		double dist = euclideanDistance(&obj->getNormDoubleAttrs(), &m.attrs);
		if (minDist > dist) {
			minDist = dist;
			index = count;
		}
		count++;
	}
	return index;
}

int ShortSolution::findNearestMean(Object * obj, int orgMean)
{
	// O(n)
	int index = 0;
	int count = 0;
	double minDist = numeric_limits<double>::max();
	for (auto m : means) {
		double dist = euclideanDistance(&obj->getNormDoubleAttrs(), &m.attrs);
		if (minDist > dist && count != orgMean) {
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
	isConsistent = false;
	
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

	int num = 0;
	for (auto c : clusters) {
		num += c.size();
		if (c.empty())
			return false;
	}
	if (num != numObj) {
		return false;
	}


	
	return true;
	
	

}