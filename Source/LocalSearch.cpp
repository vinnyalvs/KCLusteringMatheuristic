
#include "../Headers/LocalSearch.h"




LocalSearch::LocalSearch(ShortSolution *sol, int numMaxIt)
{
	this->initialSol = sol;
	this->numMaxIt = numMaxIt;
	
}

LocalSearch::~LocalSearch()
{
}

void LocalSearch::beginLocalSearch()
{
	cout << "LS iniciada" << endl;
	int i=0;
	this->bestSol = initialSol;
	while (i < numMaxIt) {
		generateSolutions();
		for (vector <ShortSolution>::iterator it = solutions.begin(); it != solutions.end(); it++) {
			if (bestSol->getCost() > it->getCost()) {
				bestSol = &*(it);
			}
		}
		i++;
	}

	cout << "Cost Best Sol: " << bestSol->getCost() << endl;
	bestSol->showSolution();
}

void LocalSearch::generateSolutions()
{
	int numElents4Swap = 5;
	int countSolutions = 10;
	int  mediaInt  = 0;
	double mediaD = 0.0;

	vector <Edge> edges = initialSol->getEdges();

	int limiar = edges.size()  / 2;

	int numElementsToRemove = 20;

	int index;

	vector <Object*> objects;
	objects = initialSol->getObjects();
	srand(time(NULL));

	while (countSolutions > 0) {
		ShortSolution *s = bestSol;
		vector <vector<int>> clusters = s->getClusters();
		for (size_t i = 0; i <clusters.size() ; i++) {
			mediaInt += clusters[i].size();
		}
		mediaInt = mediaInt/clusters.size();

		for (int a = 0; a <clusters.size(); a++) {
			int k = rand() % clusters.size();
			if (clusters[k].size() < mediaInt - numElementsToRemove) {
				index = k;
				break;
			}
			
		}


		for (size_t i = 0; i < numElementsToRemove; i++) {
			int j = index;
			int k = 0;
			while (true) {
				j = rand() % clusters.size();
				k = rand() % clusters[j].size();
				if (j != index && clusters[j].size() != 1) { break; }
				
			}
			if (objects[clusters[index][0]]->getDistance(clusters[j][k] - 1) < edges[limiar].getWeightEdge()) {
				clusters[index].push_back(clusters[j][k]);
				clusters[j].erase(clusters[j].begin() + k);

			}
			
			
		}

		ShortSolution *newSol = new ShortSolution(objects.size(), clusters.size());
		newSol->setObjects(objects);
		newSol->setEdges(edges);
		newSol->setClusters(clusters);
		newSol->calculateCostClusters();
		solutions.push_back(*newSol);

		countSolutions--;
	}

	

}

ShortSolution *LocalSearch::getBestSol()
{
	return this->bestSol;
}
