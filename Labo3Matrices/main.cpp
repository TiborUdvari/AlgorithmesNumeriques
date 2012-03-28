/********************************************************************************************
* 	 	 	 	 	 	 	 	 	 	 Tibor Udvari
* 	 	 	 	 	 	 	 	 Haute Ecole Arc Ingénierie
* 	 	 	 	 	 	 	 	 Année académique 2011-2012
* 	 	 	 	 	 	 	 	 	 	 26 mars 2012
* 	 	 	 	 	 	  		 Labo algorithmes numériques
*	Description:
*   Square Matrix
********************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SquareMatrix.h"

using namespace std;

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

/******************************************************************************************
 *
 * 	 	 	 	 	 	 	 	 	 Beginning of the program
 *
 ******************************************************************************************/

int main()
{
	clock_t init, final;

	init=clock();

	/*------------------------------------------------------------------*\
	|*							Timer start     						*|
	\*------------------------------------------------------------------*/

	SquareMatrix matrix(50);
	matrix.print();
	cout << "___________________________________________________________"<<endl;

	//SquareMatrix matrixToAdd(50);
	//matrixToAdd.print();
	//cout << "___________________________________________________________"<<endl;

	//SquareMatrix resultMatrix = matrix.additioner(matrixToAdd);
	//resultMatrix.print();
	cout << "Determinant est : " << matrix.getDeterminant();
	cout << "___________________________________________________________"<<endl;
	//sleep(100);

	/*------------------------------------------------------------------*\
	|*							Timer finish     						*|
	\*------------------------------------------------------------------*/

	final=clock()-init;
	cout.precision(10);
	cout << "Temps d'execution : "<< (double)final / ((double)CLOCKS_PER_SEC) << endl;

	//matrix.forwardElimination();
	//cout << matrix.getDeterminant();
	//matrix.print();
	return 0;
}
