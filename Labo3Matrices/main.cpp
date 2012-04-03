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
#include <unistd.h>
#include "SquareMatrix.h"

using namespace std;


/******************************************************************************************
 *
 * 	 	 	 	 	 	 	 	 	 Beginning of the program
 *
 ******************************************************************************************/

int main()
{
	clock_t init, final;
    
	    
	SquareMatrix matrix(3);
	cout << "___________________________________________________________"<<endl;
    
    /*------------------------------------------------------------------*\
    |*							Timer start     						*|
    \*------------------------------------------------------------------*/

    init=clock();
    double det=matrix.getDeterminant();
    final=clock()-init;
    
    /*------------------------------------------------------------------*\
    |*							Timer finish     						*|
    \*------------------------------------------------------------------*/
    
    cout << "Determinant est : " <<det<<endl;
	cout.precision(10);
	cout << "Temps d'execution : "<< (double)final / ((double)CLOCKS_PER_SEC) << endl;
	cout << "___________________________________________________________"<<endl<<endl;
    //matrix.print();

	return 0;
}
