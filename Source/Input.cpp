#include "../Headers/Input.h"
#include <fstream>
#include <iostream>


using namespace std;

Input::Input()
{

	

}


Input::~Input()
{

	for (int i = 0; i < numObjs; ++i) {

		delete[] distances[i];
	}
	delete[] objects;
	delete[] distances;

}

Input* Input::instance = 0;

Input * Input::getInstance()
{
	if (instance == 0)
	{
		instance = new Input();

	}

	return instance;
}

void Input::addObject(Object *object)
{
	this->objects->push_back(object);
}

void Input::readWineInput() {
	this->numAttr = 13;
	string file = inputPath;
	this->numObjs = 178;
	int typeClass;
	char comma;
	ifstream f;
	double dblAttr;
	vector <Object*> *objects = new vector <Object*>;
	this->objects = objects;
	int i = 0;
	
	f.open(file);
	if (f.is_open()) {
		for(int countObj=0; countObj<numObjs ; countObj++) {
			this->objects->push_back(new Object(countObj + 1));
			f >> typeClass;
			f >> comma; 
			i = 0;
			while (i < numAttr) {
				f >> dblAttr;
				if(i<12)
					f >> comma;
				objects->at(countObj)->addNewDoubleOrigAttr(dblAttr);
				i++;
			}
		}
		cout << "Leitura do arquivo concluida." << endl;
	}
	else {
		cerr << "Nao foi possivel abrir arquivo!" << endl;
	}
	f.close();
	this->objects = objects;
}

void Input::readObjectInstances()
{
	this->numAttr = 2;
	string file = inputPath;
	int m = 0;
	int n = 0;
	char comma;
	ifstream f;
	int index;
	double x, y;
	int ix, iy;
	vector <Object*> *objects = new vector <Object*>;
	vector <Object> *test = new vector <Object>;
	vector <double> attrs;
	int i = 0;
	f.open(file);
	if (f.is_open()) {
		f >> m;
		f >> comma;
		f >> n;
		for (int j = 0; j < m; j++)
			test->push_back(Object(j + 1));
		for (int j = 0; j < m; j++)
			objects->push_back(new Object(j + 1));
		
		while (i < m) {
			f >> index;
			f >> comma;
			if (type == 1) {
				f >> x;
				f >> comma;
				f >> y;
				test->at(index - 1).addNewDoubleOrigAttr(x);
				test->at(index - 1).addNewDoubleOrigAttr(y);
				objects->at(index - 1)->addNewDoubleOrigAttr(x);
				objects->at(index - 1)->addNewDoubleOrigAttr(y);
			}
			else if (type == 2) {
				f >> ix;
				f >> comma;
				f >> iy;
				objects->at(index - 1)->addNewIntOrigAttr(ix);
				objects->at(index - 1)->addNewIntOrigAttr(iy);
			}
			i++;
		}
		cout << "Leitura do arquivo concluida. Num Obj: " << m << endl;
	}
	else {
		cerr << "Nao foi possivel abrir arquivo!" << endl;
	}
	f.close();
	this->objects = objects;
}

void Input::normEntry()
{


	double *normAttrs = new double[numAttr];
	if (type == 1) { // type double
		double *minDoubleAttrs = new double[numAttr], *maxDoubleAttrs = new double[numAttr];

		for (int i = 0; i < numAttr; i++) {
			minDoubleAttrs[i] = getMinDoubleAttr(i);
			maxDoubleAttrs[i] = getMaxDoubleAttr(i);
		}

		for (std::vector<Object*>::iterator it = objects->begin(); it != objects->end(); ++it) {
			for (int d = 0; d < numAttr; d++) {
				normAttrs[d] = (((*it)->getOrigDoubleAttr(d) - minDoubleAttrs[d]) / (maxDoubleAttrs[d] - minDoubleAttrs[d]));
				(*it)->addNewDoubleNormAttr(normAttrs[d]);
			}
		}
		cout << "Entry normalized" << endl;
	}
	else if (type == 2) {
		int *minIntAttrs = new int[numAttr], *maxIntAttrs = new int[numAttr];
		for (int i = 0; i < numAttr; i++) {
			minIntAttrs[i] = getMinIntAttr(i);
			maxIntAttrs[i] = getMaxIntAttr(i);

		}
		for (std::vector<Object*>::iterator it = objects->begin(); it != objects->end(); ++it) {
			for (int d = 0; d < numAttr; d++) {
				normAttrs[d] = ((double)((*it)->getOrigIntAttr(d) - minIntAttrs[d]) / (double)(maxIntAttrs[d] - minIntAttrs[d]));
				(*it)->addNewDoubleNormAttr(normAttrs[d]);
			}
		}
		cout << "Entry normalized" << endl;
	}
}




double Input::getMaxDoubleAttr(int index)
{
	
	double maxAttr = objects->at(0)->getOrigDoubleAttr(index);
	vector <Object*>::iterator it;
	for (it = objects->begin(); it != objects->end(); ++it) {
		if (maxAttr < (*it)->getOrigDoubleAttr(index)) {
			maxAttr = (*it)->getOrigDoubleAttr(index);
		}
	}
	return maxAttr;
}

double Input::getMaxNormDoubleAttr(int index)
{
	
	double maxAttr = objects->at(0)->getNormDoubleAttr(index);
	vector <Object*>::iterator it;
	for (it = objects->begin(); it != objects->end(); ++it) {
		if (maxAttr < (*it)->getNormDoubleAttr(index)) {
			maxAttr = (*it)->getNormDoubleAttr(index);
		}
	}
	return maxAttr;
}





double Input::getMinNormDoubleAttr(int index)
{
	
	double minAttr = objects->at(0)->getNormDoubleAttr(index);
	vector <Object*>::iterator it;
	for (it = objects->begin(); it != objects->end(); ++it) {
		if (minAttr > (*it)->getNormDoubleAttr(index)) {
			minAttr = (*it)->getNormDoubleAttr(index);
		}
	}
	return minAttr;
}

int Input::getMaxIntAttr(int index)
{
	int maxAttr = objects->at(0)->getOrigIntAttr(index);
	vector <Object*>::iterator it;
	for (it = objects->begin(); it != objects->end(); ++it) {
		if (maxAttr < (*it)->getOrigIntAttr(index)) {
			maxAttr = (*it)->getOrigIntAttr(index);
		}
	}
	return maxAttr;
}

int Input::getMaxNormIntAttr(int index)
{
	int maxAttr = objects->at(0)->getOrigIntAttr(index);
	vector <Object*>::iterator it;
	for (it = objects->begin(); it != objects->end(); ++it) {
		if (maxAttr < (*it)->getNormIntAttr(index)) {
			maxAttr = (*it)->getNormIntAttr(index);
		}
	}
	return maxAttr;
}

double Input::getMinDoubleAttr(int index)
{
	cout << index << endl;
	double minAttr = objects->at(0)->getOrigDoubleAttr(index);
	vector <Object*>::iterator it;
	for (it = objects->begin(); it != objects->end(); ++it) {
		if (minAttr > (*it)->getOrigDoubleAttr(index)) {
			minAttr = (*it)->getOrigDoubleAttr(index);
		}
	}
	return minAttr;
}


int Input::getMinIntAttr(int index)
{
	int minAttr = objects->at(0)->getOrigIntAttr(index);
	vector <Object*>::iterator it;
	for (it = objects->begin(); it != objects->end(); ++it) {
		if (minAttr > (*it)->getOrigIntAttr(index)) {
			minAttr = (*it)->getOrigIntAttr(index);
		}
	}
	return minAttr;
}

int Input::getMinNormIntAttr(int index)
{
	int minAttr = objects->at(0)->getOrigIntAttr(index);
	vector <Object*>::iterator it;
	for (it = objects->begin(); it != objects->end(); ++it) {
		if (minAttr > (*it)->getNormIntAttr(index)) {
			minAttr = (*it)->getNormIntAttr(index);
		}
	}
	return minAttr;
}



vector<Object*>* Input::getObjects()
{
	return objects;
}

int Input::getNumObjects()
{
	return this->objects->size();
}

void Input::setInputPath(string path)
{
	this->inputPath = path;
	string tempPath = inputPath;
	tempPath.pop_back();
	tempPath.pop_back();
	tempPath.pop_back();
	tempPath.pop_back();
	tempPath += "Norm.txt";
	normInputPath = tempPath;
}

void Input::saveNormEntry()
{
	system("cls");
	ofstream a;

	string filePath = normInputPath;


	cout << filePath.c_str();

	a.open(filePath);

	int numObjs = objects->size();
	int numAttrs = 2;  // BAD CODE 

	a << numObjs;
	a << ",";
	a << numAttrs;
	a << "\n";


	for (std::vector<Object*>::iterator it = objects->begin(); it != objects->end(); ++it)
		a << (*it)->getId() << "," << (*it)->getNormDoubleAttr(0) << "," << (*it)->getNormDoubleAttr(1) << "\n" << endl;
	


	a.close();


}

void Input::setType(int type)
{
	this->type = type;
}


void Input::buildGraph()
{
	numObjs = objects->size();
	distances = new double*[numObjs];
	for (int i = 0; i < numObjs; ++i) {
		distances[i] = new double[numObjs];
	}

	for (int i = 0; i < numObjs; i++) {
		for (int j = 0; j < numObjs; j++) {
			if (i != j) {
				distances[i][j] = euclideanDistance(objects->at(i), objects->at(j));
			}
			else
				distances[i][j] = 0;
		}
	}




}


double Input::euclideanDistance(Object *a, Object *b)
{
	double dist = 0.0;
	for (int i = 0; i<numAttr; i++)
		dist += pow((a->getNormDoubleAttr(i) - b->getNormDoubleAttr(i)), 2);

	return sqrt(dist);
}