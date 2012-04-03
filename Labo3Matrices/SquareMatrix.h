#ifndef SQUAREMATRIX_H_
#define SQUAREMATRIX_H_

#include <ctime>
#include <cstdlib>
#include <iostream>
#include "VectorND.h"
/**
 *The Matrix is structured in 1D tab (row major order)
 *[ line1 | line2 | line3 |...]
 */
const int MAX_MY_ARRAY=12;
class SquareMatrix
{
public:
	SquareMatrix();
	SquareMatrix(unsigned int _n);
	SquareMatrix(unsigned int _n, double numberToFillWith);
	virtual ~SquareMatrix();
	void print();
	double getDeterminant();
	double getN() const;
	void fillWithNumber(double number);
	void fillWithArray(double elements[]);
	void setElement(unsigned int i, unsigned int j, double value);
	double getElement(unsigned int i, unsigned int j);

	void doolittleLUdecomposition(); //TODO make private after testing
	double getDeterminantDoolittle();
	/*************************************\
	| 	      Operator overrides          |
	\*************************************/
	SquareMatrix& operator+(const SquareMatrix& matrixToAdd);
	SquareMatrix& operator-(const SquareMatrix& matrixToSubstract);
    SquareMatrix& operator*(const VectorND& vec);
private:
	/*************************************\
	| 			   Attributes             |
	\*************************************/
	unsigned int n;
	double *arrayElements;//row major indexation
	SquareMatrix* lMatrix;
	SquareMatrix* uMatrix;
	/*************************************\
	| 			    Methods               |
	\*************************************/
	double calculateUElement(unsigned int i, unsigned int j);
	double calculateLElement(unsigned int i, unsigned int j);


	void fill();
	void forwardElimination(int iEntry, int jEntry);
	bool forwardElimination();
    bool forwardEliminationLaurent();
	double getLMatrixDiagonalElement(int iEntry, int jEntry);
	double generateRandom(double leftLimit, double rightLimit);
    unsigned int index(int x,int y);//2D matrix index to row major conversion
    unsigned int tibiIndex(int x, int y);
    bool isCompatible(const SquareMatrix& matrixToCompare) const;
    bool isCompatible(const VectorND& vec) const;
};

#endif /* SQUAREMATRIX_H_ */
