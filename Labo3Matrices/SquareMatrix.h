#ifndef SQUAREMATRIX_H_
#define SQUAREMATRIX_H_

#include <ctime>
#include <cstdlib>
#include <iostream>
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
	virtual ~SquareMatrix();
	void print();
	void forwardElimination(int iEntry, int jEntry);
	bool forwardElimination();
	double getDeterminant();
	bool isCompatible(SquareMatrix& matrixToCompare);
	double getN();
	SquareMatrix& additioner(SquareMatrix& matrixToAdd);
	SquareMatrix& substract(SquareMatrix& matrixToSubstract);
	double getLMatrixDiagonalElement(int iEntry, int jEntry);
private:
	unsigned int n;
	double *arrayElements;//row major indexation
	void fill();
	double generateRandom(double leftLimit, double rightLimit);
    unsigned int index(int x,int y);//2D matrix index to row major conversion
    
    
};

#endif /* SQUAREMATRIX_H_ */