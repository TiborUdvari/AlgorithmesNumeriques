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
	virtual ~SquareMatrix();
	void print();
	bool forwardElimination();
    bool gaussElimination();//shows solution in console
	double getDeterminant();
	double getN() const;
	SquareMatrix& operator+(const SquareMatrix& matrixToAdd);
	SquareMatrix& operator-(const SquareMatrix& matrixToSubstract);
    SquareMatrix& operator*(const VectorND& vec);
	double getLMatrixDiagonalElement(int iEntry, int jEntry);
private:
	unsigned int n;
	double *arrayElements;//row major indexation
	void fill();
	double generateRandom(double leftLimit, double rightLimit);
    unsigned int index(int x,int y);//2D matrix index to row major conversion
    bool isCompatible(const SquareMatrix& matrixToCompare) const;
    bool isCompatible(const VectorND& vec) const;
    VectorND* B;
};

#endif /* SQUAREMATRIX_H_ */