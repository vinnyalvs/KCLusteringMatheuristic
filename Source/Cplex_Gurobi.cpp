
#include <iostream>
#include "../Headers/Input.h"
#include "../Headers/ShortSolution.h"
#include "../Headers/Constructive.h"
#include "../Headers/Genetic.h"
#include "../Headers/Utils.h"
#include <time.h>
#include "../Headers/ProblemSolver.h"


using namespace std;

#define type 1
string folderPath = "C:/Users/vinic/Documents/GitHub/Solucoes";
string instance = "/DS2-100p2c1";
int seeds[5] = { 13,17,19,23,29 };


vector<vector<int>> readThiagoSolution(string path,double *S,int *K) {
	ifstream f;
//	cout << path << endl;
	f.open(path);
	string aux;
	double s;
	int k;
	int idCluster, idObj;
	vector<vector<int>> clusters;
	if(f.is_open()) {
		f >> aux >> s;
		*S = s;
		f >> aux >> k;
		*K = k;
		f >> aux >> aux;
		
		for (int i = 0; i < k; i++) {
			vector <int> auxVector;
			clusters.push_back(auxVector);
		}

		while (!f.eof()) {
			f >> idObj;
			f >> aux;
			f >> idCluster;
			clusters[idCluster].push_back(idObj+1); 
		}




	}

	return clusters;

}

void modelFromSolutions() {
	srand(seeds[0]);
	string path;
	int numSoulutions = 10;
	Param p = Param();
	p.fixedNumClusters = false;
	ProblemSolver *pSolver = new ProblemSolver(1);
	pSolver->setParams(p);

	//Carregando informações da Instância
	Input* I = Input::getInstance();
	I->setType(type);
	I->setInputPath("Instancias/DS2" + instance + ".csv");
	I->readObjectInstances();
	I->normEntry();
	I->buildGraph();
	//Para cada solução do Thiago é criada uma solução Minha
	//as Informações de S, K e clusters são retiradas do Thiago
	//Para cada solução é necessário passar os objetos e a matriz de distancias e calcular o valor da função objetivo
	//Por fim a solução nova é add ao vector de soluções que serão usadas no resolvedor
	for (int i = 0; i < numSoulutions; i++) {
		double S; // Silhueta da solução
	    int K; //Num Clusters da solução
		int numObj;
		path = folderPath + instance + "/solucao" + to_string(i+1) + ".csv";
		vector <vector <int>> clusters = readThiagoSolution(path, &S, &K);
		ShortSolution *s = new ShortSolution(I->getNumObjects(),K);
		s->setClusters(clusters);
		s->Silhouette = S;
		s->numAttr = 2;
		s->setObjects(I->getObjects());
		s->distances = I->distances;
		s->calcMeans();
		s->calcFitness(3);
	//	cout << s->fitness << endl;
		pSolver->addSolution(s);
	}

	//cout << sizeof(numSoulutions)*sols.capacity() + sizeof(sols) << endl;

	cout << "Fim Leitura " << endl;
	cout << endl;


	ShortSolution *es = new ShortSolution();
	pSolver->solveProblem();
	cout << "Ps" << endl;
	es->setClusters(pSolver->getClusters());
	es->setObjectByCluster(pSolver->objByCluster);
	es->setObjects(I->getObjects());
	es->distances = I->distances;
	//es->calcRandIndex();
	//cout << es->randIndex << endl;

	Utils b = Utils("Instancias/DS2/" + instance + ".csv");
	b.ShowSolution(es, "../Exact.py", 0);

	cout << es->checkViability() << endl;

	



}

int main(int   argc, char *argv[]) {
	
 
	modelFromSolutions();
/*	// string strings[1] = { "C:/Users/vinic/Desktop/wine1.csv" };
	string strings[1] = { "Instancias/DS2/DS2-500p6c1.csv" };

	// "Instancias/DS1/DS1-gauss9t.txt" 

	Param p = Param();
	p.fixedNumClusters = true;

	int types[1] = { type };
	int Ks[1] = { 6 };
	clock_t tInicio, tDecorrido, tFim;
	int numInstances = 1;
	int numClusters;
	Input* i = Input::getInstance();
	for (int n = 0; n < numInstances; n++) {


		// 1 for Cplex Enviroment -1 for Gurobi Enviroment
		ProblemSolver *pSolver = new ProblemSolver(1);
		pSolver->setParams(p);
		srand(seeds[n]);
		i->setInputPath(strings[0]);


		i->setType(type);
		//i->readWineInput();
		i->readObjectInstances();
		i->normEntry();
		i->buildGraph();
		
		tInicio = clock();
		int numClusters = Ks[0];



		vector <ShortSolution*> sols;
		clock_t um = clock();
		//Gera População Inicial
		for (int j = 0; j < 100; j++) {
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
		es->calcRandIndex();
	    cout << es->randIndex << endl;
		
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





	return 0; */
}


//atoi(argv[2]);


/*ShortSolution *as = new ShortSolution(900, 3);
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