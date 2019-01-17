#include "../Headers/Genetic.h"
#include <thread>
#include <chrono>



vector <pair <int, int>> Genetic::matchMeansSolutions(ShortSolution * sol1, ShortSolution * sol2, vector <struct mean> *newMeans)
{
	vector <struct mean> *m1 = sol1->means;
	vector <pair <int, int>> matches;
	int count = 0;
	int *aux = new int[sol1->getNumClusters()];
	for (int i = 0; i < sol1->getNumClusters(); i++)
		aux[i] = -1;
	int closestMean = findNearestMean(m1->at(0), sol2->means);
	matches.push_back(make_pair(count, closestMean));
	aux[closestMean] = 1;
	for (auto m : *m1) {
		if (count != 0) {
			int closestMean = findNearestMean(m, sol2->means, aux);
			matches.push_back(make_pair(count, closestMean));
		}
		count++;
		
	}



	return matches;

}

pair <struct mean, struct mean> Genetic::crossMeans(struct mean m1, struct mean m2) {
	//Calcular vetor entre m1 e m2, vamos andar 1/4 do tamanho de vetor na direção a outra mediana
	vector <double> v ;
	pair <struct mean, struct mean> newMeans;
	for (int i = 0; i < numAttr; i++)
		v.push_back(m2.attrs[i] - m1.attrs[i]);

	struct mean newM1;
	for (int i = 0; i < numAttr; i++)
		newM1.attrs.push_back(m1.attrs[i] + 0.25*v[i]);
	newMeans.first = newM1;

	v.clear();
	for (int i = 0; i < numAttr; i++)
		v.push_back(m1.attrs[i] - m2.attrs[i]);

	struct mean newM2;
	for (int i = 0; i < numAttr; i++)
		newM2.attrs.push_back(m1.attrs[i] + 0.25*v[i]);
	newMeans.second = newM2;

	return newMeans;

}

void Genetic::crossover(ShortSolution * sol1, ShortSolution * sol2)
{
	/*The combining crossover combines the two solutions. It
builds the new offsprings centre by centre. For each centre
from the parent individual it finds the nearest centres from
the second parent and generates two new centres randomly
on the line joining the two parent centres.
	*/

	vector <struct mean> *newMeans = new  vector <struct mean> ;
	vector <struct mean> *m1 = sol1->means;
	vector <struct mean> *m2 = sol2->means;
	vector <pair <int, int>> matches = matchMeansSolutions(sol1, sol2, newMeans);
	for (auto match : matches ) {
		pair <struct mean, struct mean> pairMeans = crossMeans(sol1->means->at(match.first ), sol2->means->at(match.second));
		sol1->means->at(match.first) = pairMeans.first;
		sol2->means->at(match.second) = pairMeans.second;
	}
	sol1->updateClusters();
	sol2->updateClusters();
	
}

void Genetic::crossover(ShortSolution * sol1, ShortSolution * sol2, ShortSolution * newSol1, ShortSolution * newSol2)
{
	vector <struct mean> *newMeans = new  vector <struct mean>;
	sol1->copySolution(newSol1);
	sol2->copySolution(newSol2);
	vector <struct mean> *m1 = newSol1->means;
	vector <struct mean> *m2 = newSol2->means;
	vector <pair <int, int>> matches = matchMeansSolutions(newSol1, newSol2, newMeans);
	for (auto match : matches) {
		pair <struct mean, struct mean> pairMeans = crossMeans(newSol1->means->at(match.first), newSol2->means->at(match.second));
		newSol1->means->at(match.first) = pairMeans.first;
		newSol2->means->at(match.second) = pairMeans.second;
	}
	newSol1->updateClusters();
	newSol2->updateClusters();

}

void Genetic::mutation(ShortSolution * sol1)
{

	/*sol1->calculateSilhouette();
	cout << sol1->getSilhouette() << endl; */
	vector <struct mean> *m1 = sol1->means;
	vector <vector<int>> clusters;
	double x, y;
	int rand1 = rand() % m1->size();
	clusters = sol1->getClusters();
	int id = rand() % clusters[rand1].size();
	id = clusters[rand1][id];
	vector <Object*> *objs = sol1->getObjects();
	for (int i = 0; i < numAttr; i++)
		m1->at(rand1).attrs[i] = objs->at(id - 1)->getNormDoubleAttr(i);
	sol1->updateClusters();
	/*
	sol1->calculateSilhouette();
	cout << sol1->getSilhouette() << endl;*/

}

Genetic::Genetic(vector<ShortSolution*>* sols, int maxIterations, vector <ShortSolution*> *newPopulation, int numAttr)
{
	this->numAttr = numAttr;
	double mutationRate = 0.60;
	double crossoverRate = 0.80;
	int numOffspring = solutions->size();


//	cout << "Best Pop Inicial "  << ": " << solutions->at(0)->getSilhouette() << endl;

	rankPopulation(sols);
	eliminate(solutions->size(),0.9, sols);
	
	this->maxInterations = maxIterations;
	int count = 0;
	int rand1, rand2=0;
	while (count < maxInterations) {
		//Pegando 10% melhores
		int newC = 0;
		for (auto s : *solutions) {
			if (newC > (numOffspring*0.1))
				break;
			newPopulation->push_back(s);
			newC++;
		}
		solutions->erase(solutions->begin(), solutions->begin() + (numOffspring*0.1));

		for (int i = 0; i < solutions->size() * 0.5 ; i++) {
			ShortSolution *s = new ShortSolution();
			s->numAttr = numAttr;
			ShortSolution *s2 = new ShortSolution();
			s2->numAttr = numAttr;
			rand1 = rand() % solutions->size();
			rand2 = rand() % solutions->size();
			while(rand1 == rand2)
				rand2 = rand() % solutions->size();
			crossover(solutions->at(rand1), solutions->at(rand2),s,s2);		
			newPopulation->push_back(s);
			newPopulation->push_back(s2);
		}


		

		for (auto p : *newPopulation) {
			int mutationR = rand() % 100;
			if (mutationR >= mutationRate) {
				if (p->checkViability()) {
					mutation(p);
					/*KMeans *alg = new KMeans(p->getNumClusters(), 3, p->getObjects(),numAttr);
					alg->readSolution(p);
					alg->buildClusters();*/
				}
			}
		}


		/*system("cls");
		for (auto s : *solutions) {
			this_thread::sleep_for(chrono::seconds(1));
			cout << s->getSilhouette() << endl;
		}*/

		newRndPop(newPopulation, numOffspring*0.1);


		
		int kb = 0;
		vector <ShortSolution*>::iterator it;
		for (it = newPopulation->begin(); it != newPopulation->end(); ) {
			if ((*it)->checkViability()) {
				
				(*it)->calculateSilhouette();
				//cout << (*it)->getSilhouette() << " " << (*it)->checkViability() << endl;
				it++;
			}
			else {
				kb++;
				it = newPopulation->erase(it);
			}
		}

		cout << kb << " invalidas" << endl;

		//Mato Geracao Anterior
		solutions->clear();

		for (auto p : *newPopulation) {
			//if (p->checkViability()) {
				ShortSolution *n = new ShortSolution();
				n->numAttr = numAttr;
				p->copySolution(n);
				solutions->push_back(n);
			//}
		}


		
		rankPopulation(sols);
		eliminate(solutions->size(), 0.9, sols);
		newPopulation->clear();

		
		/*system("cls");
		int l = 0;
		for (auto s : *solutions) {
			this_thread::sleep_for(chrono::seconds(1));
			cout << s->getSilhouette() << endl;
			l++;
			if (l > 5)
				break;
		}

		cout << solutions->size() << endl;
		*/

	
		cout << "Best Geracao " << count << ": " << solutions->at(0)->getSilhouette() << " Tam: " << solutions->size() << endl;
		this_thread::sleep_for(chrono::seconds(1));

		count++;
	
	}


	newPopulation = solutions;

	
}

void Genetic::eliminate(int posIni, double rate,vector <ShortSolution*> *solutions ) {
	unsigned int tam = solutions->size();
	posIni = posIni * rate;
	solutions->erase(solutions->begin() + tam, solutions->end());
}

void Genetic::rankPopulation(vector <ShortSolution*> *solutions) {
	std::sort(solutions->begin(), solutions->end(), [](const ShortSolution* lhs, const ShortSolution* rhs)
	{
		return lhs->Silhouette > rhs->Silhouette;
	});
}

Genetic::Genetic(vector<ShortSolution>* sols, double  timeLimit)
{
//	solutions = sols;
	this->timeLimit = timeLimit;

}

void Genetic::newRndPop(vector<ShortSolution*>* solutions, int numSolutions) {
	ShortSolution *es;
	solutions->at(0)->copySolution(es);
	for (int j = 0; j < numSolutions; j++) {
		ShortSolution *s;
		Constructive *c = new Constructive(es->getNumObjs(), es->getNumClusters(), es->getObjects(),1,numAttr);
		c->distances = es->distances;
		c->meansClustering();
		s = c->getSolution();
		if (s->checkViability()) {
			solutions->push_back(s);
		}
	}
}



Genetic::~Genetic()
{
}


int Genetic::findNearestMean( struct mean m1, vector <struct mean> *m2) {
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

void Genetic::refine(ShortSolution *newSol) {
	KMeans *alg = new KMeans(newSol->getNumClusters(), 3, newSol->getObjects(),numAttr);
	alg->readSolution(newSol);
	alg->buildClusters();
	delete alg;

}



double Genetic::getValueBestSolution()
{
	return 0.0;
}
