#pragma once
class Category
{
public:
	/**
	Category Constructor with int value
	@param int id Category id
	@param int value 
	@return none
	*/
	Category(int id,int value);
	/**
	Category Constructor with double value
	@param int id Category id
	@param double value
	@return none
	*/
	Category(int id,double value);
	/**
	Default Category destructor
	@param  none
	@return none
	*/
	~Category();
private:
	double doubleValue;
	int    intValue;
	int id;
};

