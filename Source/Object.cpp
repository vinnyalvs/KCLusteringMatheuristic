#include "../Headers/Object.h"
Object::Object()
{


}

Object::Object(int id)
{
	this->id = id;

}




Object::~Object()
{
	objByProx.end();
}


double Object::getOrigDoubleAttr(int index)
{
	return origDoubleAttrs[index];
}

int Object::getOrigIntAttr(int index)
{
	return origIntAttrs[index];
}


void Object::setOrigDoubleAttrs(vector <double> origDoubleAttrs)
{
	this->origDoubleAttrs = origDoubleAttrs;
}

void Object::addNewDoubleOrigAttr(double value)
{
	this->origDoubleAttrs.push_back(value);
}

void Object::addNewIntOrigAttr(int value)
{
	this->origIntAttrs.push_back(value);
}

void Object::setOrigDoubleAttr(double origDoubleAttr, int index)
{
	this->origDoubleAttrs[index] = origDoubleAttr;
}

void Object::setOrigIntAttrs(vector <int> origIntAttrs)
{
	this->origIntAttrs = origIntAttrs;
}


double Object::getNormDoubleAttr(int index)
{
	return normDoubleAttrs[index];
}

double Object::getNormIntAttr(int index)
{
	return normIntAttrs[index];
}




void Object::addNewDoubleNormAttr(double value) {
	this->normDoubleAttrs.push_back(value);
}

void Object::addNewIntNormAttr(int value) {
	this->normIntAttrs.push_back(value);
}

void Object::setNormDoubleAttr(double normDoubleAttr, int index)
{
	this->normDoubleAttrs[index] = normDoubleAttr;
}

void Object::setNormDoubleAttrs(vector <double> values)
{
	this->normDoubleAttrs = values;

}






int Object::getId()
{
	return this->id;
}

Object *Object::getObject()
{
	return this;
}

vector<double> Object::getNormDoubleAttrs()
{
	return this->normDoubleAttrs;
}



void Object::addEdge(int id, double pesoA, int idDest)
{
	Edge* a = new Edge(id, pesoA, idDest);
	edges.push_back(*a);
}

vector <Edge> Object::getEdges()
{
	return edges;
}

void Object::removeEdge(int id)
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



double Object::getDistance(int id) {
	for (vector <Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
		//cout << it->getDest() << "-" << id << endl;
		if (it->getDest() == id) {
			return it->getWeightEdge();
		}
	}
	return 0.0;
}


