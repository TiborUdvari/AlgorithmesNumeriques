/********************************************************************************************
*
* 	 	 	 	 	 	 	 	 Laurent Novac,Tibor Udvari
* 	 	 	 	 	 	 	 	 Haute Ecole Arc Ingénierie
* 	 	 	 	 	 	 	 	 Année académique 2011-2012
* 	 	 	 	 	 	 	 	 	 	 12 mars 2012
*
* 	 	 	 	 	 	   Laboratoire d'Algorithmes Numériques
*
*	Description:
*   Implémentation de la méthode de bisection de Bolzano
*
********************************************************************************************/

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "main.h"
#include "GeomGlut.h"

extern GeomGlut graphWin;

/******************************************************************************************
*
* 	 	 	 	 	 	   Globals / Typedefs / Defines / Constants
*
 ******************************************************************************************/
using namespace std;

const double LEFTLIMIT = -20;
const double RIGHTLIMIT = 20;
const double MAXHEIGHT = 4.1;
const double MINHEIGHT = -4.1;
/******************************************************************************************
*
* 	 	 	 	 	 	 	 	 	 Function prototypes
*
 ******************************************************************************************/

/****************************************************
*        Mathematical functions for testing
 ****************************************************/
double f(double x);
double g(double x);

/****************************************************
*                  Solving methods
 ****************************************************/
void bolzanoBisectionRecursive(double a, double b, double epsilon);

/****************************************************
*                  Helper functions
 ****************************************************/
bool oppositeSigns(double a, double b);

/******************************************************************************************
*
* 	 	 	 	 	 	 	 	 	 Beginning of the program
*
 ******************************************************************************************/
void mainFunction( void )
{

    for(double i = LEFTLIMIT; i <= RIGHTLIMIT; i = i + 0.001)
    {
        graphWin.plot(i,f(i),1);
    }

    cout << "Starting recursive Bolzano method ... " << endl;
    bolzanoBisectionRecursive(-15.1,15.1,0.02);

//graphWin.plot(1.1,1.1, 2);
//graphWin.segment(10.10,20.10,30.0,40.0);
//graphWin.plot( (réel)x, (réel)y, [(entier) rayon] )
//graphWin.segment( (réel)x1, (réel)y1, (réel)x2, (réel)y2 )


}

int main(int argc, char **argv)
{
  graphWin.initGraphicsWin( 1000, -15.1, 15.1, -4.1, 4.1 );
  mainFunction();
  return( 0 );
}

/******************************************************************************************
*
* 	 	 	 	 	 	 	 	 	 Function declarations
*
 ******************************************************************************************/

double f(double x)
{
    return sin(x) - x/3;
}

double g(double x)
{
    return x/(1-pow(x,2));
}

bool oppositeSigns(double a, double b)
{
    return (a == 0 && b > 0) || (a > 0 && b == 0) || ( a < 0 && b > 0) || (a > 0 && b < 0) || (a == 0 && b < 0) || (a < 0 && b == 0);
}

/*
* Assumptions *
b is larger than a
epsilon is chosen so that it still gives correct value and is positive

Note :
Intervals may show up more times, we did not consider this as an error
Ex 0 and an interval to the left and an interval to the right
*/

void bolzanoBisectionRecursive(double a, double b, double epsilon)
{
    if(fabs(b-a) <= epsilon)
    {

        return;
    }
    double c = (a+b)/2;

    graphWin.segment(a,MAXHEIGHT,a,MINHEIGHT);
    graphWin.segment(b,MAXHEIGHT,b,MINHEIGHT);
    graphWin.segment(c,MAXHEIGHT,c,MINHEIGHT);

    //cout << "Analysing interval [" << a <<", " << b << "] with middle point at : "<< c <<endl;
    if (c == 0)
    {
        cout << "0 is in " << c << endl;
    }
    if (oppositeSigns(f(a),f(c)))
    {
        //cout << "   ---> 0 is between [" << a <<", " << c << "]" << endl;
        bolzanoBisectionRecursive(a,c,epsilon);
    }
    if (oppositeSigns(f(c), f(b)))
    {
        //cout << "   ---> 0 is between [" << c <<", " << b << "]" << endl;
        bolzanoBisectionRecursive(c,b,epsilon);
    }
}
