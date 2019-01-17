#include "../Headers/Category.h"




Category::Category(int id,int value)
{
	this->id = id;
	this->intValue = value;
	this->doubleValue = 0.0;
}

Category::Category(int id,double value)
{
	this->id = id;
	this->intValue = 0;
	this->doubleValue = value;
}

Category::~Category()
{
}
