#include "../Headers/Genetic.h"
#include <thread>
#include <chrono>




void Genetic::crossover(ShortSolution * sol1, ShortSolution * sol2, ShortSolution * newSol1, ShortSolution * newSol2)
{
	// Seleciona um cluster e procura cluster mais pr�ximo do outro indiv�duo, 
	//troca os clusters, depois � necess�rio garantir a consist�ncia da solu��o

	vector <struct mean> *newMeans = new  vector <struct mean>;
	sol1->copySolution(newSol1);
	sol2->copySolution(newSol2);
	vector <struct mean> m1 = newSol1->means;
	int selMean = rand() % m1.size();
	vector <struct mean> m2 = newSol2->means;
	int nearestMean = findNearestMean(m1.at(selMean), m2);

	vector <int> cluster1 = newSol1->clusters[selMean];
	vector <int> cluster2 = newSol2->clusters[nearestMean];

	newSol1->clusters[selMean] = cluster2;
	newSol2->clusters[nearestMean] = cluster1;

	set<int> hs;

	// inserir os elementos do cluster trocado na hash table
	for (int i = 0; i < newSol1->clusters[selMean].size(); i++)
		hs.insert(newSol1->clusters[selMean][i]);

	for (int i = 0; i < newSol1->getNumClusters(); i++) {
		//	for (int j = 0; j < newSol1->clusters[i].size(); j++)
		vector <int>::iterator j;
		if (i != selMean) {
			for (j = newSol1->clusters[i].begin(); j != newSol1->clusters[i].end();) {
				// Se elemento esta presente na hs, removo ele do cluster correspondente
				if (hs.find(*(j)) != hs.end())
					j = newSol1->clusters[i].erase(j);
				else
					j++;
			}
		}
	}

	//Colocar novamente os objetos da base de dados que n�o estam clusterizados devido a troca dos clusters 
	//Comparar SelMean com Cluster 1



	unordered_set <int> s;
	for (int i = 0; i < newSol1->clusters[selMean].size(); i++)
		s.insert(newSol1->clusters[selMean][i]);

	// Colocar todos elementos do cluster original que n�o est�o na tabela hash  

	for (int i = 0; i < cluster1.size(); i++)
		if (s.find(cluster1[i]) == s.end())
			newSol1->tradeCluster(cluster1[i], selMean);



	// Mesmo de cima s� que para a newSol2

	set<int> hs2;

	// inserir os elementos do cluster trocado na hash table
	for (int i = 0; i < newSol2->clusters[nearestMean].size(); i++)
		hs2.insert(newSol2->clusters[nearestMean][i]);

	for (int i = 0; i < newSol2->getNumClusters(); i++) {
		//	for (int j = 0; j < newSol1->clusters[i].size(); j++)
		vector <int>::iterator j;
		if (i != nearestMean) {
			for (j = newSol2->clusters[i].begin(); j != newSol2->clusters[i].end();) {
				// Se elemento esta presente na hs, removo ele do cluster correspondente
				if (hs2.find(*(j)) != hs2.end())
					j = newSol2->clusters[i].erase(j);
				else
					j++;
			}
		}
	}


	unordered_set <int> k;
	for (int i = 0; i < newSol2->clusters[nearestMean].size(); i++)
		k.insert(newSol2->clusters[nearestMean][i]);

	// Colocar todos elementos do cluster original que n�o est�o na tabela hash  

	for (int i = 0; i < cluster2.size(); i++)
		if (k.find(cluster2[i]) == k.end())
			newSol2->tradeCluster(cluster2[i], nearestMean);


	// --- Fim  --- 

	//Atualiza Centroides, para cada dimens�o, percorre cada cluster somando o attr N de cada objeto, 
	//ap�s percorrer todos obj K do cluster i � calculada a m�dia da dimens�o N do cluster i
	double mediaN = 0;
	double media = 0;

	for (int n = 0; n < numAttr; n++) {
		for (int i = 0; i < numClusters; i++) {
			media = 0;
			if (newSol1->clusters[i].empty()) {
				newSol1->chegueiLa = true;
			}
			else {
				for (int k = 0; k < newSol1->clusters[i].size(); k++) {
					int id = newSol1->clusters[i][k];
					media += objects->at(id - 1)->getNormDoubleAttr(n);
				}
				mediaN = media / newSol1->clusters[i].size();
				newSol1->means[i].attrs[n] = mediaN;
			}
			media = 0;
			if (newSol2->clusters[i].empty()) {
				newSol2->chegueiLa = true;
			}
			else {
				for (int j = 0; j < newSol2->clusters[i].size(); j++) {
					int id = newSol2->clusters[i][j];
					media += objects->at(id - 1)->getNormDoubleAttr(n);
				}
				mediaN = media / newSol2->clusters[i].size();
				newSol2->means[i].attrs[n] = mediaN;
			}
		}
	}




}


bool Genetic::areMeansEqual(struct mean m1, struct mean m2) {

	if (euclideanDistance(&m1.attrs, &m2.attrs) == 0) // Dois means est�o s�o iguais se est�o na mesma pos
		return false;
	else
		return true;
}

Genetic::Genetic(int numGenerations, int numAttr, int numClusters, int numObjs, int mutationRate, int crossoverRate, int numOffspring, double crossDist, double bestDist) {
	this->numAttr = numAttr;
	this->maxInterations = numGenerations;
	this->numClusters = numClusters;
	this->numObjs = numObjs;
	this->crossoverRate = crossoverRate;
	this->mutationRate = mutationRate;
	this->numOffspring = numOffspring;
	this->crossDist = crossDist;
	this->bestDist = bestDist;
}

void Genetic::start(vector<ShortSolution*>* sols, vector <Object*> *objects, double **distances) {
	clock_t tInicio, tFim, tDecorrido, tInicio2;
	this->objects = objects;
	vector <ShortSolution*> *newPopulation = new vector <ShortSolution*>;




	rankPopulation(sols);

	int count = 0, crossCount1 = 0, crossCount2 = 0, crossCount = 0;
	int rand1, rand2 = 0;

	//Enquanto n�o est� na gera��o Final
	double lastBest;
	int countBest = 0;
	while (count < maxInterations) {

		tInicio = clock();


		//Cruzamento

		calcRelFitness(sols); // Calcula a aptid�o relativa de cada indiv�duo para fazer roleta
		tInicio2 = clock();
		crossCount1 = 0;
		crossCount2 = 0;
		int kc = 0;

		//Pegando 10% melhores
		int newC = 0;
		for (int s = 0; s < sols->size(); s++) {
			if (newC < (numOffspring*0.1)) {
				newPopulation->push_back(sols->at(s));
				newC++;
			}



		}


		while ((crossCount1 + crossCount2) <= numOffspring * crossDist) {

			ShortSolution *s = new ShortSolution();
			s->numAttr = numAttr;
			ShortSolution *s2 = new ShortSolution();
			s2->numAttr = numAttr;

			//roulette

			rand1 = roulette();
			rand2 = roulette();

			while (rand1 == rand2)
				rand2 = roulette();
			int a = (rand() % 100);
			if (a <= crossoverRate) {
				crossover(sols->at(rand1), sols->at(rand2), s, s2);

				int mutationR = rand() % 100;
				if (mutationR <= mutationRate)
					//mutation(s);
				//Checando se ap�s a muta��o houve um aborto espont�neo
				if (s->checkViability() && !(s->chegueiLa)) {
					newPopulation->push_back(s);
					crossCount1++;
				}
				else
					kc++;
				mutationR = rand() % 100;
				if (mutationR <= mutationRate)
					//mutation(s2);
				if (s2->checkViability() && !(s2->chegueiLa)) {
					newPopulation->push_back(s2);
					crossCount2++;
				}
				else
					kc++;

			}

		}

		//Mato Geracao Anterior
		sols->clear();
		vector<ShortSolution*>().swap(*sols);



		  //Popula��o Aleat�ria, gera 10% da prole
		tInicio2 = clock();
		for (int k = 0; k < numOffspring*bestDist; k++) {
			ShortSolution *s;
			Constructive *c = new Constructive(numObjs, numClusters, objects, 1, numAttr);
			c->distances = distances;
			c->meansClustering();
			s = c->getSolution();
			newPopulation->push_back(s);
		} 


		vector <ShortSolution*>::iterator it;
		for (it = newPopulation->begin(); it != newPopulation->end(); ) {
			(*it)->calculateDunnIndex();
			it++;
			/*if ((*it)->checkViability()) {
				//	(*it)->calculateSilhouette3();
				(*it)->calculateDunnIndex();
				it++;
			}
			else {
				//kb++;
				it = newPopulation->erase(it);
			}*/
		}


		fitness.clear();

		for (auto p : *newPopulation) {
			//if (p->checkViability()) {
			ShortSolution *n = new ShortSolution();
			n->numAttr = numAttr;
			p->copySolution(n);
			sols->push_back(n);
			//}
		}



		rankPopulation(sols);
		newPopulation->clear();
		vector<ShortSolution*>().swap(*newPopulation);


		//cout << "Best Geracao " << count << ": " << sols->at(0)->getSilhouette() << " Tam: " << sols->size() << endl;
		cout << "Best Geracao " << count << ": " << sols->at(0)->getDunnIndex() << " Tam: " << sols->size() << endl;
		//if (lastBest == sols->at(0)->getSilhouette()) {
		if (lastBest == sols->at(0)->getDunnIndex()) {
			countBest++;
		}
		else {
			countBest = 0;
		}
		tFim = clock();
		tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC));
		if (countBest >= 50)
			break;




		count++;
		// lastBest = sols->at(0)->getSilhouette();
		lastBest = sols->at(0)->getDunnIndex();

	}



}



void Genetic::eliminate(int posIni, double rate, vector <ShortSolution*> *solutions) {
	unsigned int tam = solutions->size();
	//posIni = posIni * rate;
	tam = tam * rate;
	solutions->erase(solutions->begin() + tam, solutions->end());
}

void Genetic::rankPopulation(vector <ShortSolution*> *solutions) {
	std::sort(solutions->begin(), solutions->end(), [](const ShortSolution* lhs, const ShortSolution* rhs)
	{
		return lhs->dunnIndex > rhs->dunnIndex;
		//return lhs->Silhouette > rhs->Silhouette;
	});
}

void Genetic::calcRelFitness(vector <ShortSolution*> *solutions) {
	double sum = 0, aux = 0;
	double relFitness = 0;

	for (auto s : *solutions) {
		//sum += s->getSilhouette();
		sum += s->getDunnIndex();
	}
	for (auto s : *solutions) {
		//relFitness = (s->getSilhouette() / sum) * 100;
		relFitness = (s->getDunnIndex() / sum) * 100;
		aux += relFitness;
		fitness.push_back(aux);
	}



}
int Genetic::roulette() {

	double selFitness;
	selFitness = rand() % 100;
	int count = 0;
	for (auto f : fitness) {
		if (selFitness <= f) {
			break;
		}
		count++;
	}

	return count;



}

void Genetic::mutation(ShortSolution * sol1)
{


	sol1->calculateCostClusters();
	vector <double> dispersion = sol1->getCostClusters();
	vector <double> orgDispersion = sol1->getCostClusters();
	sort(dispersion.begin(), dispersion.end());
	double sum = 0, aux = 0;
	double relFitness = 0;
	int cut = (ceil)(dispersion.size() * 0.4);
	int selDispersedCluster = rand() % cut;
	//cout << cut << endl;
	//cout << dispersion.size() << endl;
	int count = -1;
	for (auto f : orgDispersion) {
		count++;
		if (dispersion[selDispersedCluster] == f) {
			break;
		}
	}
	//cout << selDispersedCluster << endl;

	vector <int> selCluster = sol1->clusters[count];
	double maxDist = numeric_limits<double>::min();
	int mostDistObj;
	for (auto obj : selCluster) {
		vector <double> attr = objects->at(obj - 1)->getNormDoubleAttrs();
		double dist = euclideanDistance(&attr, &sol1->means[count].attrs);
		if (dist > maxDist) {
			mostDistObj = obj;
		}
	}
	//system("cls");
	//int newMean = sol1->findNearestMean(objects->at(mostDistObj));

	sol1->tradeCluster(mostDistObj, count);


	//int id = sol1->clusters[count];



}

void Genetic::newRndPop(vector<ShortSolution*>* solutions, int numSolutions) {
	ShortSolution *es;
	solutions->at(0)->copySolution(es);
	for (int j = 0; j < numSolutions; j++) {
		ShortSolution *s;
		Constructive *c = new Constructive(es->getNumObjs(), es->getNumClusters(), es->getObjects(), 1, numAttr);
		c->distances = es->distances;
		c->meansClustering();
		s = c->getSolution();
		if (s->checkViability()) {
			solutions->push_back(s);
		}
	}

	// delete c
}



Genetic::~Genetic()
{
}


int Genetic::findNearestMean(struct mean m1, vector <struct mean> m2) {
	int index = 0;
	int count = 0;
	double minDist = numeric_limits<double>::max();
	for (auto mean : m2) {
		double dist = euclideanDistance(&m1.attrs, &mean.attrs);
		if (minDist > dist && dist != 0) {
			minDist = dist;
			index = count;
		}
		count++;
	}
	return index;
}



int Genetic::findNearestMean(mean m1, vector<struct mean>* m2, int * aux)
{
	int index = 0;
	int count = 0;
	double minDist = numeric_limits<double>::max();

	for (auto mean : *m2) {

		double dist = euclideanDistance(&m1.attrs, &mean.attrs);
		if (minDist > dist) {
			if (aux[count] != 1) {
				minDist = dist;
				index = count;
				aux[index] = 1;
			}
		}
		count++;
	}
	return index;
}


double Genetic::euclideanDistance(vector <double> *attrA, vector <double> *attrB)
{


	double dist = 0.0;
	for (int i = 0; i < numAttr; i++) {
		dist += pow((attrA->at(i) - attrB->at(i)), 2);
	}

	return sqrt(dist);


}



double Genetic::getValueBestSolution()
{
	return 0.0;
}