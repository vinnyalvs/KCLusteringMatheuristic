// MSTClusteringV2.cpp : Defines the entry point for the console application.
//


#include "../Headers/Input.h"
#include "../Headers/Utils.h"
#include "../Headers/Constructive.h"


int main()
{
	Input* i = Input::getInstance();
	int type = 1;
	i->setInputPath("matrixO.txt");
	i->setType(type);
	i->readObjectInstances();
	i->normEntry();


	int numClusters = 3;

	Constructive c = Constructive(i->getNumObjects(),numClusters,i->getObjects(), type);
	
	c.buildGraph();
	//c.buildClusters();
	c.setRandomParameter(0.7);
	
	for (int i = 0; i < 2005; i++) {
		c.buildClustersRandom();
		c.getSolution()->showSolution();
		c.getSolution()->calculateSilhouette();
		cout << c.getSolution()->getSilhouette() << endl;
		//c.getSolution()->calculateCostClusters();
		//cout << c.getSolution()->getCost() << endl;
	}


		





	Utils u = Utils();
	//u.printGraph(c.getSolution());
	//u.ShowSolution(c.getSolution());
	
	cout << rand() % 5 << endl;;
	cout << "a" << endl;
	//sol->printGraph();
//	sol->showSolution();
	


	
	//u.printGraph(sol);
	//u.printEdges(sol);

    return 0;
}

