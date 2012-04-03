#include "SquareMatrix.h"
SquareMatrix::SquareMatrix()
{
    
}

SquareMatrix::SquareMatrix(unsigned int _n) : n(_n)
{
	B = new VectorND(n);
    arrayElements = new double[n*n];
	fill();
}

SquareMatrix::~SquareMatrix()
{
	//delete[] arrayElements;//FIXME makes execution error
}

void SquareMatrix::fill()
{
    double m[9]={-2,-1,2,2,1,0,-3,3,1};//matrix given in class
    
    for (int i=0; i<9; i++) 
    {
        arrayElements[i]=m[i];    
    }
    
}

double SquareMatrix::generateRandom(double leftLimit, double rightLimit)
{
    double r=(double)rand();
    
    return (r / (double) RAND_MAX) * (rightLimit - leftLimit) + leftLimit;
}

void SquareMatrix::print()
{
	std::cout.precision(2);
	for (int j = 1; j <= n; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			std::cout << std::fixed << arrayElements[index(i-1,j-1)] << "   ";
		}
		std::cout << std::endl;
	}
}

bool SquareMatrix::forwardElimination()
{
    for (int i=n-1; i>0; i--) 
    {
        for (int j=0; j<i; j++) 
        {
            double mult=arrayElements[index(i,j)]/arrayElements[index(i, i)];
            
            for (int m=0; m<n; m++) 
            {
                arrayElements[index(m, j)]=arrayElements[index(m, j)]-mult*arrayElements[index(m, i)];
            }
        }
    }
    return true;
}

bool SquareMatrix::gaussElimination()
{
    forwardElimination();
    std::cout<<std::endl;
    print();
    std::cout<<std::endl;
    double *tabRes=new double[n];
    
    for(int i = 0;i < n;i++)
    {
        if(arrayElements[index(i, i)]==0)
        {
            return false;
        }
        tabRes[i]=B->getArrayElements()[i]/arrayElements[index(i, i)];
        for(int j=0;j<i;j++)
        {
            tabRes[i]-=arrayElements[index(j,i)];
        }
    }
    
    for (int i=0; i<n; i++) 
    {
        std::cout<<"x"<<i<<" = "<<tabRes[i]<<std::endl;
    }
    
    return true;
}

double SquareMatrix::getDeterminant()
{
	forwardElimination();
    
	double determinant = 1;
	for (int i = 1; i <= n; ++i)
	{
		determinant *= arrayElements[index(i-1, i-1)];
	}
	return determinant;
}

bool SquareMatrix::isCompatible(const SquareMatrix& matrixToCompare) const
{
	return n == matrixToCompare.getN();
}

bool SquareMatrix::isCompatible(const VectorND &vec) const
{
    return n==vec.getDim();
}
double SquareMatrix::getN() const
{
	return n;
}

SquareMatrix& SquareMatrix::operator+(const SquareMatrix& matrixToAdd) 
{
	try
	{
		if (!isCompatible(matrixToAdd))
		{
			throw 20;
		}
		SquareMatrix matrixResult(n);
		for (int i = 1; i <= n*n; i++)
		{
			matrixResult.arrayElements[i-1]=matrixToAdd.arrayElements[i-1]+this->arrayElements[i-1];
		}
		return matrixResult;
        
	} catch (int e)
	{
		std::cout << "Error: "<<e<<"Your matrices are not compatible for addition. Killing program ... " << std::endl;
		exit(1);
	}
}

SquareMatrix& SquareMatrix::operator*(const VectorND& vec)
{
    try
    {
        if (!isCompatible(vec)) 
        {
            throw 21;
        }
        SquareMatrix matrixResult(n);
        
        for (int i=1;i<=n; i++)
        {
            for (int j=1; j<=n; j++) 
            {
                matrixResult.arrayElements[index(i-1, j-1)]=arrayElements[index(i-1, j-1)]*vec.getArrayElements()[i-1];
            }
        }
        
        return matrixResult;
    }
    catch(int e)
    {
        std::cout << "Error: "<<e<<"Your matrices and vector is not compatible for multiplication. Killing program ... " << std::endl;
		exit(1);
    }
}
SquareMatrix& SquareMatrix::operator-(const SquareMatrix& matrixToSubstract) 
{
	try
	{
		if (!isCompatible(matrixToSubstract))
		{
			throw 22;
		}
        
		SquareMatrix matrixResult(n);
		for (int i = 1; i <= n*n; i++)
		{
            matrixResult.arrayElements[i-1]=this->arrayElements[i-1]-matrixToSubstract.arrayElements[i-1];
		}
		return matrixResult;
	} catch (int e)
	{
		std::cout << "Error: "<<e<<"Your matrices are not compatible for substraction. Killing program ... " << std::endl;
		exit(1);
	}
}

unsigned int SquareMatrix::index(int x,int y)//row major indexation
{
    return y*n+x;
}