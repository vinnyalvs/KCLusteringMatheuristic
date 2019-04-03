
#include <iostream>
#include "../Headers/Input.h"
#include "../Headers/ShortSolution.h"
#include "../Headers/Constructive.h"
#include "../Headers/Genetic.h"
#include "../Headers/Utils.h"
#include <time.h>
#include "../Headers/ProblemSolver.h"


using namespace std;


int main(int   argc, char *argv[]) {
	clock_t tInicio, tFim, tDecorrido;
	const int numSolutions = 1000;

	int seeds[5] = { 13,17,19,23,29 };

	double alphas[10] = { 0.7,0.3,0.25 ,0.3 ,0.2 ,0.5 ,0.2 ,0.3 ,0.2 ,0.9 };


	int type; // 1  float , 2  Int		  

	// string strings[1] = { "C:/Users/vinic/Desktop/wine1.csv" };
	string strings[1] = { "Instancias/DS2/DS2-300p3c.csv" };

	// "Instancias/DS1/DS1-gauss9t.txt" 

	Param p = Param();
	p.fixedNumClusters = true;

	int types[1] = { 1 };
	int Ks[1] = { 3 };

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

	/*	
		ShortSolution *as = new ShortSolution(900, 3);
		ifstream fs;
		string a = "Instancias/DS1/a.csv";
		fs.open(a);
		int ggh = 0;
		int q, o;
		string virg;
		cout << "tensao" << endl;
		while (ggh < 900) {
		fs >> o;
		fs >> virg;
		fs >> q;
		as->addObject(o, q);
		as->updateObjectCluster(o, q);
		ggh++;
		}

		as->setObjects(i->getObjects());
		as->distances = i->distances;
		as->calculateSilhouette3();
		cout << as->getSilhouette() << endl;

		Utils us = Utils(strings[0]);
		us.ShowSolution(as,"AGBest.py",0); */


		vector <ShortSolution*> sols;
		clock_t um = clock();
		//Gera População Inicial
		for (int j = 0; j < numSolutions; j++) {
			ShortSolution *s;
			Constructive *c = new Constructive(i->getNumObjects(), numClusters, i->getObjects(), type, i->numAttr);
			c->distances = i->distances;
			c->meansClustering();
			s = c->getSolution();
			//s->calculateSilhouette3();
			//cout << s->getSilhouette() << endl;
			s->calcFitness(3);
		//	pSolver->addSolution(s);
			if (s->checkViability()) {
				sols.push_back(s);
			}
		}
		//Utils us = Utils(strings[0]);
		//us.printGraph(sols.at(0));
		cout << "Tempo: " << ((clock() - um) / (CLOCKS_PER_SEC)) << endl;
		cout << "GENETIC --------------------------------" << endl;
		vector <ShortSolution*> *newPopulation = new vector <ShortSolution*>;
		



		/**/
		clock_t tInicio2 = clock();
		//numGen , numAttr, numClusters, numObjs, taxa de mutação, taxa de cruzamento, num Prole, distribuição da prole cruzamento, distribuição da prole que é da elite gen anterior
		//Genetic *G = new Genetic(500, i->numAttr, numClusters, i->getNumObjects(), 10, 90, 100, 0.8, 0.1,true,3);
		//G->start(&sols, i->getObjects(), i->distances);

		//Genetic *G = new Genetic(&sols, 30, newPopulation,i->numAttr,numClusters, i->getNumObjects(),i->getObjects(),i->distances);

		for (auto sol : sols) {
			sol->distances = i->distances;
			sol->calculateCostClusters();
		//	sol->calcFitness(3);
			if (sol->checkViability())
				pSolver->addSolution(sol);
		}

		cout.precision(3);
		cout << "Max" << " " << sols.at(0)->fitness << endl; 
		cout << "Viabilidade: " << endl;
		if (sols.at(0)->checkViability())
			cout << "A Solucao e Viavel" << endl;
		else
			cout << "A Solucao e Inviavel" << endl;

		//Utils b = Utils(strings[n]);
		//b.ShowSolution(sols.at(0), "AGBest.py", sols.at(0)->fitness);
		//b.printGraph(sols.at(0));
		//b.writeSolution(sols.at(index));

	//	sols.at(0)->calcRandIndex();
	//	cout << sols.at(0)->randIndex << endl;

		tFim = clock();
		tDecorrido = ((tFim - tInicio2) / (CLOCKS_PER_SEC));
		cout << "Tempo: " << tDecorrido << endl;

		cout << "Fim Teste " << n << endl;
		cout << endl;
		ShortSolution *es = new ShortSolution(i->getNumObjects(), numClusters);
		pSolver->solveProblem();
		cout << "Ps" << endl;
		es->setClusters(pSolver->getClusters());
		es->setObjectByCluster(pSolver->objByCluster);
		es->setObjects(i->getObjects());
		es->distances = i->distances;
	//	es->calcRandIndex();
		//cout << es->randIndex << endl;
		
		Utils b = Utils(strings[n]);
		b.ShowSolution(es, "AGBest.py",0);

		cout << es->checkViability() << endl;


		delete pSolver; 
		int tam = sols.size();
		for (int i = 0; i < tam; i++) {
			delete sols[i];
		}
		delete newPopulation;


	}
	cout << endl;
	cout << "Fim da Aplicacao" << endl;





	return 0;
}
