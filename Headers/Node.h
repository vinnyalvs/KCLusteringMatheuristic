#pragma once
#include "Edge.h"
#include <vector>

using namespace std;

class Node {
private:
	int id;
	int grau;
	int grauEntrada;
	int grauSaida;
	double pesoX;
	double pesoY;
	vector <Edge> edges;

public:
	int clusterParent;
	Node();
	~Node();
	int getID();
	int getGrau();
	void setID(int id);
	int	 getId();
	void setGrau(int g);
	void setX(double pesoX);
	void setY(double pesoY);
	double getX();
	double getY();



	void setNumEdges(int size);
	void addEdge(int id, double pesoA, int idDest);
	vector <Edge> getEdges();
	void removeEdge(int id);
	double getDistance(int id);
};

