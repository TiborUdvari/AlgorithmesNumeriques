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
#include "VectorND.h"
using namespace std;


/******************************************************************************************
 *
 * 	 	 	 	 	 	 	 	 	 Beginning of the program
 *
 ******************************************************************************************/

int main()
{
	clock_t init, final;
    
	    
	SquareMatrix matrix=SquareMatrix(3);
    SquareMatrix matrix2=SquareMatrix(3);
    SquareMatrix matrixRes=SquareMatrix(3);
    VectorND vector=VectorND(3);
    cout << "___________________________________________________________"<<endl;
    matrix.print();
    cout << "___________________________________________________________"<<endl;
    vector.print();

    matrix.forwardEliminationLaurent();
    matrix.print();
    
    
//	cout << "___________________________________________________________"<<endl;
//    cout<<"add"<<endl;
//    matrixRes=matrix+matrix2;
//    matrixRes.print();
//    cout << "___________________________________________________________"<<endl;
//    
//    cout <<"sub"<<endl;
//    matrixRes=matrix-matrix2;
//    matrixRes.print();
//    
//    cout << "___________________________________________________________"<<endl;
//    cout<<"mult by vec"<<endl;
//    
//    matrixRes=matrix*vector;
//    matrixRes.print();
    
    /*------------------------------------------------------------------*\
    |*							Timer start     						*|
    \*------------------------------------------------------------------*/
    
//    init=clock();
//    double det=matrix.getDeterminant();
//    final=clock()-init;
    
    /*------------------------------------------------------------------*\
    |*							Timer finish     						*|
    \*------------------------------------------------------------------*/
    
//    cout << "Determinant est : " <<det<<endl;
//	cout.precision(10);
//	cout << "Temps d'execution : "<< (double)final / ((double)CLOCKS_PER_SEC) << endl;
//	cout << "___________________________________________________________"<<endl<<endl;
//    //matrix.print()

	return 0;
}
