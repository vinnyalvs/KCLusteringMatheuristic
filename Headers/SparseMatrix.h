#pragma once
#include <string>
#include <vector>
#include <stdio.h>
#include <tchar.h>
#include <iostream>

using namespace std;
class SparseMatrix
{
public:
	/**
	SparseMatrix Constructor. Builds a nxn sparsematrix
	@param int n rows and columns number
	@return none
	*/
	SparseMatrix(int n);
	/**
	SparseMatrix Constructor. Builds a rows x colluns sparsematrix. Calls buildMatrix internally
	@param int rows rows number
	@param int columns columns number
	@return none
	*/
	SparseMatrix(int rows, int columns);
	/**
	Add a new element to matrix
	@param double value  value of the new element
	@param int row row where element will be added
	@param int col column where element will be added
	@return none
	*/
	void addElement(double value, int row, int col);
	/**
	get element
	@param int row row where element is storaged
	@param int col columnrow where element is storaged
	@return double element
	*/
	double getElement(int row, int col);
	/**
	get the number of matrix rows ( m )
	@param none
	@return int numrows the number of rows
	*/
	int getNumRows();
	/**
	get the number of matrix Columns ( n )
	@param none
	@return int numCols the number of cols
	*/
	int getNumCols();
	~SparseMatrix();

private:
	int numRows;
	int numCols;
	vector <double> *values;
	vector <int> *rows, *cols;
	/**
	Build the sparseMatrix. Does the same thing as SparseMatrix(m,n) constructor. Used internally
	@param int rows rows
	@param int columns columns number
	@return none
	*/
	void buildMatrix(int rows, int columns);
	/**
	Insert the element in the matrix. Used internally
	@param int index used to calculate the element pos in vector
	@param double value  value of the new element
	@param int row row where element will be added
	@param int col column where element will be added
	@return none
	*/
	void insert(int index, double value, int row, int col);
};

