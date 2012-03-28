#ifndef SQUAREMATRIX_H_
#define SQUAREMATRIX_H_

#include <ctime>
#include <cstdlib>
#include <iostream>

class SquareMatrix
{
public:
	SquareMatrix();
	SquareMatrix(int _n);
	virtual ~SquareMatrix();
	void print();
	void forwardElimination(int iEntry, int jEntry);
	void forwardElimination();
	void fillMyValues();
	double getDeterminant();
	bool isCompatible(SquareMatrix& matrixToCompare);
	double getN();
	SquareMatrix& additioner(SquareMatrix& matrixToAdd);
	SquareMatrix& substract(SquareMatrix& matrixToSubstract);
	double getLMatrixDiagonalElement(int iEntry, int jEntry);
private:
	int n;
	double **array2Delements;
	void fill();
	double generateRandom(double leftLimit, double rightLimit);
};

#endif /* SQUAREMATRIX_H_ */
