#pragma once
#include <vector>
#include "Edge.h"
using namespace std;
class Object
{
public:
	int objClass;
	Object();
	/**
	object constructor.
	@param  int id  object id
	@return none
	*/
	Object(int id);
	/**
	object constructor, with almost everything an object has
	@param  int      id                  object id
	@param  int      origId              the original id of object
	@param  int      pos                 object position
	@param  int      clusterId           id of obj cluster
	@param  double   origDoubleAttr  double attr original
	@param  int      origIntAttr         int attr original
	@param  Category origCatAttr    category attr original
	@return none
	*/
	
	/**
	object destructor.
	@param  none
	@return none
	*/
	~Object();

	/**
	return the double original attr.
	@param  none
	@return double orignal double attribute
	*/
	double getOrigDoubleAttr(int index);
	/**
	return the int original attr.
	@param  none
	@return int orignal int attribute
	*/
	int getOrigIntAttr(int index);
	/**
	return  the category original attribute
	@param  none
	@return Category category original attribute
	*/
	
	/**
	set the double original attribute
	@param  double origDoubleAttr  original double attr
	@return none
	*/
	void setOrigDoubleAttrs(vector <double> origDoubleAttrs);

	void addNewDoubleOrigAttr(double value);

	void addNewIntOrigAttr(int value);

	void setOrigDoubleAttr(double origDoubleAttr, int index);
	/**
	set the int original attr.
	@param  int origIntAttr orignal int attribute
	@return none
	*/
	void setOrigIntAttrs(vector <int> origIntAttrs);
	/**
	set  the category original attribute
	@param  Category origCatAttr original category attribute
	@return none
	*/
	

	/**
	return the double normalized attr.
	@param  none
	@return double normDoubleAttr normalized double attribute
	*/
	double getNormDoubleAttr(int index);
	/**
	return the int normalized attr.
	@param  int index   attr index
	@return int normIntAttr normalized int attribute
	*/

	double getNormIntAttr(int index);
	/**
	return the int normalized attr.
	@param  int index attr index
	@return int normCatAttr normalized Category attribute
	*/

	
	/**
	set object Id.
	@param  int id object id
	@return none
	*/

	/**
	set object original Id.
	@param  int origId original id
	@return none
	*/


	/**
	set object position.
	@param  int pos
	@return none
	*/

	/**
	set which cluster object belongs
	@param  int clusterId
	@return none
	*/

	void addNewDoubleNormAttr(double attr);
	void addNewIntNormAttr(int value);
	void setNormDoubleAttr(double normDoubleAttr, int index);
	/**
	set all norm double attrs.
	@param  vector <double> values
	@return none
	*/
	void setNormDoubleAttrs(vector <double> values);

	/**
	set all norm category attrs.
	@param  vector <Category> values
	@return none
	*/
	/**
	set all norm attrs in once.
	@param  vector <double> valueDoubleAttrs, vector <Int> valueIntAttrs, vector <Category> valueCatAttrs
	@return none
	*/
	
	/**
	return object id.
	@param  none
	@return int id
	*/
	int getId();
	/**
	return the id of the cluster which object belongs
	@param  none
	@return int clusterId
	*/
	/**
	return the degree of the object
	@param  none
	@return int clusterId
	*/
	/**
	return tthe object
	@param  none
	@return Object object
	*/
	Object *getObject();

	vector <double> getNormDoubleAttrs();

	void addEdge(int id, double pesoA, int idDest);
	vector <Edge> getEdges();
	void removeEdge(int id);
	double getDistance(int id);


private:

	// orig = original , norm = normalized, simi = similarity, pos = position
	int id;

	vector <int>		objByProx;
	// Original attributes
	vector <double>		origDoubleAttrs;
	vector <int>		origIntAttrs;
	// Normalized Attributes
	vector <double>		normDoubleAttrs;
	vector <double>		normIntAttrs;

	double dissimilaritySameCluster;
	double dissimilarityOtherClusters;

	//Node.h

	vector <Edge> edges;




};

