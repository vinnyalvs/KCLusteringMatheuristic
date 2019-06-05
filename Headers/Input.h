#pragma once
#include "Object.h"
#include <vector>
#include <iostream>
using namespace std;



class Input
{
public:
	~Input();

	static Input* getInstance();

	void addObject(Object *object);

	void readWineInput();

	void readObjectInstances();

	void readThiagoSolutions(string folderPath, int numFiles);

	void normEntry();

	void readNormEntry();

	double getMaxDoubleAttr(int index);

	double getMaxNormDoubleAttr(int index);

	double getMinDoubleAttr(int index);

	double getMinNormDoubleAttr(int index);



	int getMaxIntAttr(int index);

	int getMaxNormIntAttr(int index);

	int getMinIntAttr(int index);

	int getMinNormIntAttr(int index);


	vector <Object*>  *getObjects();

	int getNumObjects();

	void setInputPath(string path);

	void saveNormEntry();

	void setType(int type);

	void buildGraph();

	double euclideanDistance(Object * a, Object * b);


	double **distances;



	int numAttr;
private:
	Input();

	int numObjs;

	static Input *instance;

	vector <Object*> *objects;
	

	vector <double> simiByMetric;

	string inputPath;

	string normInputPath;

	int type;

	

};

