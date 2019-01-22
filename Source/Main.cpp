
#include <iostream>
#include "../Headers/Input.h"
#include "../Headers/KMeans.h"
#include "../Headers/ShortSolution.h"
#include "../Headers/Constructive.h"
#include "../Headers/Genetic.h"
#include "../Headers/Utils.h"
#include <time.h>
#include "../Headers/ProblemSolver.h"

using namespace std;


int main(int   argc, char *argv[]) {


	clock_t tInicio, tFim, tDecorrido;
	const int numSolutions = 2000;

	int seeds[5] = { 13,17,19,23,29 };

	double alphas[10] = { 0.7,0.3,0.25 ,0.3 ,0.2 ,0.5 ,0.2 ,0.3 ,0.2 ,0.9 };


	int type; // 1  float , 2  Int		  

	//string strings[1] = { "C:/Users/vinic/Desktop/wine1.csv" };
	string strings[1] = { "C:/Users/HAL/Documents/GitHub/GeneticKClustering/KClustering/Instancias/DS2/DS2-300p3c.csv" };



	Param p = Param();
	p.fixedNumClusters = true;



	int types[3] = { 1 };
	int Ks[8] = { 3 };

	int numInstances = 1;
	int numClusters;
	Input* i = Input::getInstance();
	for (int n = 0; n < numInstances; n++) {
		// 1 for Cplex Enviroment -1 for Gurobi Enviroment
		ProblemSolver *pSolver = new ProblemSolver(1);
		pSolver->setParams(p);
		srand(seeds[n]);
		i->setInputPath(strings[0]);
		type = types[0];

		i->setType(type);
		//i->readWineInput();
		i->readObjectInstances();
		i->normEntry();
		i->buildGraph();

		tInicio = clock();
		int numClusters = Ks[0];
		//atoi(argv[2]);

		vector <ShortSolution*> sols;

		//Gera População Inicial
		for (int j = 0; j < numSolutions; j++) {
			ShortSolution *s;
			Constructive *c = new Constructive(i->getNumObjects(), numClusters, i->getObjects(), type, i->numAttr);
			c->distances = i->distances;
			int alfaSel = rand() % 10;
			c->setRandomParameter(alphas[alfaSel]);
			c->meansClustering();
			s = c->getSolution();
			s->calculateSilhouette2();
			if (s->checkViability()) {
				sols.push_back(s);
				pSolver->addSolution(s);

			}
		}
		cout << "GENETIC --------------------------------" << endl;
		vector <ShortSolution*> *newPopulation = new vector <ShortSolution*>;
		ShortSolution *es = new ShortSolution(i->getNumObjects(), numClusters);
		//Genetic *G = new Genetic(&sols, 20, newPopulation,i->numAttr);
		es->setObjects(i->getObjects());

		//system("cls");
		double maxS = numeric_limits<double>::min();
		int count = 0;
		int index = 0;
		cout << endl;
		for (auto sol : sols) {
			sol->distances = i->distances;
			sol->calculateCostClusters();
			//pSolver->addSolution(sol);
			if (sol->getSilhouette() > maxS) {
				index = count;
				maxS = sol->getSilhouette();
			}
			count++;
		}
		cout << index << endl;
		cout.precision(3);
		cout << "Max" << " " << sols.at(index)->getSilhouette() << endl;
		cout << "Viabilidade: " << endl;
		if (sols.at(index)->checkViability())
			cout << "A Solucao e Viavel" << endl;
		else
			cout << "A Solucao e Inviavel" << endl;

		//Utils b = Utils("Instancias/DS2/DS2-500p6c1.csv");
		//b.ShowSolution(sols.at(index),"AGBest.py");



		tFim = clock();
		tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC));

		cout << "Tempo: " << tDecorrido << endl;
		cout << "Fim Teste " << n << endl;
		cout << endl;

		pSolver->solveProblem();
		cout << "Ps" << endl;
		es->setClusters(pSolver->getClusters());
		es->setObjectByCluster(pSolver->objByCluster);
		es->distances = i->distances;
		es->calculateSilhouette2();
		cout << es->getSilhouette() << endl;
		Utils u = Utils(strings[n]);
		u.ShowSolution(es);

		cout << es->checkViability() << endl;


		delete pSolver;

		/*for (auto s : sols)
		delete s;
		delete es;*/

	}
	cout << endl;
	cout << "Fim da Aplicacao" << endl;





	return 0;
}
