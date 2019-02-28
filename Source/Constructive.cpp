
#include "../Headers/Constructive.h"
#include <list>


Constructive::Constructive(int numVertex, int numClusters, vector <Object*> *objects, int type, int numAttr)
{

	this->objects = objects;
	this->numObjs = numVertex;
	this->numClusters = numClusters;
	this->numAttr = numAttr;
}


void Constructive::Initialize() {
	//Inicializo os clusters
	//1
	solution = new ShortSolution(this->numObjs, numClusters);
	solution->setObjects(objects);
	solution->numAttr = numAttr;

	vector <int> a;
	clusters.clear();
	clusters.assign(numClusters, a);
	for (size_t i = 0; i < clusters.size(); i++) {
		clusters[i].reserve(numObjs);
	}

	//2

	cluster n;
	structClusters.clear();
	for (int i = 0; i < numClusters; i++) {
		n.idCluster = 0;
		n.idClusterInSolution = i;
		structClusters.push_back(n);
	}

	//Inicializo os subconjuntos
	element newSet;
	elements.clear();
	for (int i = 1; i <= numObjs; ++i)
	{
		newSet.parent = i;
		newSet.rank = 0;
		elements.push_back(newSet);
	}

	objByCluster.clear();
	//Dizendo no vetor objByCluster, que cada no inicialmente é um cluster
	for (int i = 1; i <= numObjs; i++) {
		objByCluster.push_back(i);
	}

	edgesInSolution.clear();

	this->type = type;
	solution->setLargerEdges(largerEdges);
}

Constructive::~Constructive()
{
	delete solution;
	for (auto o : *objects) {
		delete o;
	}

	delete objects;
}



void Constructive::sortEdges()
{
	sort(candidatesEdges.begin(), candidatesEdges.end());
	largerEdges = candidatesEdges;
	reverse(largerEdges.begin(), largerEdges.end());
}

vector<Edge> Constructive::getCandidatesEdges()
{
	return candidatesEdges;
}


void Constructive::randomMSTClustering()
{
	vector <int> clusterByObj;
	vector <int> clusterId;
	Initialize();
	solution->setEdges(candidatesEdges);
	numConvexComponents = objects->size();
	int numVertex = objects->size();
	int numEdges = candidatesEdges.size();
	list <Edge> auxCandidatesEdges;
	int j = 0;

	clusterId.clear();
	clusterId.resize(numVertex + 1, -1);

	for (j = 0; j < numEdges; j++)
		auxCandidatesEdges.push_back(candidatesEdges[j]);

	int count = 0;
	while (numConvexComponents > numClusters) {
		j = rand() % (int)(auxCandidatesEdges.size() * rndParameter);
		list <Edge>::iterator it = (auxCandidatesEdges.begin());
		for (int i = 0; i < j; i++)
			it++;
		int parentSrc = find(it->getSrc());
		int parentDest = find(it->getDest());
		if (parentSrc != parentDest) {
			unionSETs(it->getSrc(), it->getDest());
			edgesInSolution.push_back(*it);
		}
		count++;
		auxCandidatesEdges.erase(it);
	}

	for (int i = 0; i < numObjs; i++) {
		objByCluster[i] = find(i + 1);
	}

	int clusterIndex = 0; // Contador para os ids dos objetos
	int obj = 0;

	for (vector <int>::iterator c = objByCluster.begin(); c != objByCluster.end(); c++, obj++) {

		if (clusterId[*c] == -1) {
			clusterId[*c] = clusterIndex;
			structClusters[clusterIndex].idCluster = clusterIndex;
			clusterIndex++;
		}

		solution->addObject(obj + 1, clusterId[*c]);
		clusterByObj.push_back(clusterId[*c]);
	}

	solution->setObjectByCluster(clusterByObj);

}

void Constructive::meansClustering()
{

	vector <int> clusterByObj;
	vector <int> clusterId;
	Initialize();
	solution->setEdges(candidatesEdges);

	//means.assign(numClusters, 0);
	int count = 0;

	while( count < numClusters ) {
		mean m;
		unsigned int id = rand() % numObjs + 1;
		m.id = id;
		for (int k = 0; k < numAttr; k++) {
			m.attrs.push_back(objects->at(id - 1)->getNormDoubleAttr(k));
		}
		bool br = false;
		for (auto sortedId  : means) {
			if (objects->at(id - 1)->getId() == sortedId.id) {
				br = true;
			}
		}
		if (!br) {
			means.push_back(m);
			count++;
		}
	}
	
	for (auto obj : *objects) {
		int clusterID = findNearestMean(obj->getId());
		objByCluster[obj->getId() - 1] = clusterID;
		solution->addObject(obj->getId(), clusterID);
	}
	solution->distances = distances;
	solution->setObjectByCluster(objByCluster);
	solution->means = means;
	double mediaN = 0;
	double media = 0;

	for (int n = 0; n < numAttr; n++) {
		for (int i = 0; i < numClusters; i++) {
			media = 0;
			for (int k = 0; k < solution->clusters[i].size(); k++) {
				int id = solution->clusters[i][k];
				media += objects->at(id - 1)->getNormDoubleAttr(n);
			}
			mediaN = media / solution->clusters[i].size();
			solution->means[i].attrs[n] = mediaN;
		}
	} 

	
	
	
}

int Constructive::findMean(unsigned int id) {

	int mean1=0, mean2=0; // mean1 e o mais proximo, mean2 e o segundo mais proximo
	int chosed = rand() % 99;
	int count = 0;
	double minDist = numeric_limits<double>::max();
	double minDist2;
	for (auto mean : means) {
		double dist = distances[id - 1][mean.id - 1];
		if (minDist > dist) {
			minDist2 = minDist;
			mean2 = mean1;
			minDist = dist;
			mean1 = count;
		}
		count++;
	
	}
	minDist = (1 - minDist) * 100;
	int w1 = minDist;
	minDist2 = (1 - minDist2) * 100;
	int w2 = 100 - minDist;


	if (chosed < w1) {
		return mean1;
	} else {	//if (chosed <= (w1 + w2)) {
		return mean2;
	}
	
}

int Constructive::findNearestMean(unsigned int id)
{
	// O(2*n)

	int index = 0;
	int count = 0;
	double minDist = distances[id - 1][means[0].id - 1];
	for (auto mean : means) {
		double dist = distances[id - 1][mean.id - 1];
		if (minDist > dist) {
			minDist = dist;
			index = count;
		}
		count++;
	}
	return index;
}

vector<vector<int>> Constructive::getClusters()
{
	return clusters;
}

vector<int> Constructive::getObjByCluster()
{
	return objByCluster;
}

void Constructive::setRandomParameter(double alpha)
{
	this->rndParameter = alpha;
}

void Constructive::setCandidatesEdges(vector<Edge> edges)
{
	this->candidatesEdges = edges;
}

ShortSolution  *Constructive::getSolution()
{
	return solution;
}

void Constructive::unionSETs(int idX, int idY)
{


	int xroot = find(idX);
	int yroot = find(idY);
	numConvexComponents--;
	if (elements[xroot - 1].rank < elements[yroot - 1].rank) {
		elements[xroot - 1].parent = yroot;
		

	}
	else if (elements[xroot - 1].rank > elements[yroot - 1].rank) {
		elements[yroot - 1].parent = xroot;
		
	}
	else
	{
		elements[yroot - 1].parent = xroot;
		
		elements[xroot - 1].rank++;

	}
}

int Constructive::find(int id)
{
	if (elements[id - 1].parent != id)
		elements[id - 1].parent = find(elements[id - 1].parent);

	return elements[id - 1].parent;
}