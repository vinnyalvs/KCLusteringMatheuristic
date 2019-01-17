#include "../Headers/Edge.h"

Edge::Edge(int iD_Node, double pesoA, int idDest)
{
	this->dest = idDest;  // No de destino 
	this->src = iD_Node; // No de origem
	pesoAresta = pesoA;
}

Edge::~Edge()
{
}

double Edge::getWeightEdge()
{
	return this->pesoAresta;
}

int Edge::getDest()
{
	return this->dest;
}

int Edge::getSrc()
{
	return this->src;
}



void Edge::setWeightEdge(double peso)
{
	this->pesoAresta = peso;
}