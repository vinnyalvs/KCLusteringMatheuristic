#include "../Headers/Node.h"

Node::Node()
{
}

Node::~Node()
{
}

int Node::getID()
{
	return this->id;
}

int Node::getGrau()
{
	return this->grau;
}

void Node::setID(int id)
{
	this->id = id;
}

int Node::getId()
{
	return this->id;
}

void Node::setGrau(int g)
{
	this->grau = g;
}


void Node::setX(double pesoX)
{
	this->pesoX = pesoX;
}

void Node::setY(double pesoY)
{
	this->pesoY = pesoY;
}

double Node::getX()
{
	return pesoX;
}

double Node::getY()
{
	return pesoY;
}

void Node::setNumEdges(int size)
{
	edges.reserve(size);
}

void Node::addEdge(int id, double pesoA, int idDest)
{
	Edge* a = new Edge(id, pesoA, idDest);
	if (id == id)
		grau += 2;
	else
		grau += 1;
	edges.push_back(*a);
}

vector <Edge> Node::getEdges()
{
	return edges;
}

void Node::removeEdge(int id)
{

	int count = 0;
	for (vector <Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
		//cout << it->getDest() << "-" << id << endl;
		if (it->getDest() == id) {
			break;
		}
		count++;
	}
	edges.erase(edges.begin() + count);
}



double Node::getDistance(int id) {
	for (vector <Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
		//cout << it->getDest() << "-" << id << endl;
		if (it->getDest() == id) {
			return it->getWeightEdge();
		}
	}
	return 0.0;
}
