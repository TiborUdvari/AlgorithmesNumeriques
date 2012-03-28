#include "SquareMatrix.h"

SquareMatrix::SquareMatrix()
{

}

SquareMatrix::SquareMatrix(int _n) :
		n(_n)
{
	array2Delements = new double*[n];
	for (int i = 0; i < n; ++i)
		array2Delements[i] = new double[n];
	fill();
	//fillMyValues();
}

SquareMatrix::~SquareMatrix()
{
	for (int i = 0; i < n; ++i)
		delete[] array2Delements[i];
	delete[] array2Delements;
}

void SquareMatrix::fill()
{
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			array2Delements[i - 1][j - 1] = generateRandom(10, 99);
			//array2Delements[i - 1][j - 1] = 10.0;
		}
	}
}

double SquareMatrix::generateRandom(double leftLimit, double rightLimit)
{
	return (rand() / (double) RAND_MAX) * (rightLimit - leftLimit) + leftLimit;
}

void SquareMatrix::print()
{
	std::cout.precision(2);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			std::cout << std::fixed << array2Delements[i - 1][j - 1] << "   ";
		}
		std::cout << std::endl;
	}
}

void SquareMatrix::forwardElimination(int iEntry, int jEntry)
{
	double multiplier = array2Delements[iEntry - 1][jEntry - 1]
			/ array2Delements[jEntry - 1][jEntry - 1];
	//std::cout << "Multiplier is "<< multiplier << std::endl;
	for (int j = 1; j <= n; j++)
	{
		//std::cout << " = M[" << iEntry-1 << "," << j-1 << "]" << array2Delements[iEntry-1][j-1] <<" - "<< multiplier << " * M[" << iEntry-jEntry-1<<","<< j-1 << "]" << array2Delements[iEntry-jEntry-1][j-1] <<" = ";
		array2Delements[iEntry - 1][j - 1] = array2Delements[iEntry - 1][j - 1]
				- multiplier * array2Delements[jEntry - 1][j - 1];
		//std::cout << " = M["<< iEntry-1 <<"," << j-1 << "]" << array2Delements[jEntry-1][j-1] << std::endl;
	}
}

double SquareMatrix::getLMatrixDiagonalElement(int iEntry, int jEntry)
{
	//TODO
}

void SquareMatrix::forwardElimination()
{
	int i = 2;
	int j = 1;

	while (i <= n)
	{
		while (j < i)
		{
			std::cout << "Forward elimination for : " << i << "," << j
					<< std::endl;
			forwardElimination(i, j);
			j++;
		}
		i++;
		j = 1;
	}

}

void SquareMatrix::fillMyValues()
{
	//For 2*2
	array2Delements[0][0] = 10;
	array2Delements[0][1] = 4;
	array2Delements[1][0] = 1;
	array2Delements[1][1] = 2;
}

double SquareMatrix::getDeterminant()
{
	forwardElimination();
	double determinant = 1;
	for (int i = 0; i < n; ++i)
	{
		determinant *= array2Delements[i][i];
	}
	return determinant;
}

bool SquareMatrix::isCompatible(SquareMatrix& matrixToCompare)
{
	return n == matrixToCompare.getN();
}

double SquareMatrix::getN()
{
	return n;
}

SquareMatrix& SquareMatrix::additioner(SquareMatrix& matrixToAdd)
{
	// Exception minimalist
	try
	{
		if (!isCompatible(matrixToAdd))
		{
			throw 20;
		}
		SquareMatrix* matrixResult = new SquareMatrix(n);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				matrixResult->array2Delements[i - 1][j - 1] =
						matrixToAdd.array2Delements[i - 1][j - 1]
								+ matrixToAdd.array2Delements[i - 1][j - 1];
			}
		}
		return *matrixResult;

	} catch (int e)
	{
		std::cout << "Your matrices are not compatible. Killing program ... "
				<< std::endl;
		exit(1);
	}
}

SquareMatrix& SquareMatrix::substract(SquareMatrix& matrixToSubstract)
{
	try
	{
		if (!isCompatible(matrixToSubstract))
		{
			throw 20;
		}

		SquareMatrix* matrixResult = new SquareMatrix(n);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				matrixResult->array2Delements[i - 1][j - 1] =
						matrixToSubstract.array2Delements[i - 1][j - 1]
								- matrixToSubstract.array2Delements[i - 1][j - 1];
			}
		}
		return *matrixResult;
	} catch (int e)
	{
		std::cout << "Your matrices are not compatible for substraction. Killing program ... " << std::endl;
		exit(1);
	}
}

