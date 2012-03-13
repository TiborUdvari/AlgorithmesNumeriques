/********************************************************************************************
*                             _____            _              _
*                            | ____|__ _ _   _(_)_ __   ___  / |
*                            |  _| / _` | | | | | '_ \ / _ \ | |
*                            | |__| (_| | |_| | | |_) |  __/ | |
*                            |_____\__, |\__,_|_| .__/ \___| |_|
*                                     |_|       |_|
*
* 	 	 	 	 	 	 	 	 Laurent Novac, Tibor Udvari
*                               Landry Jérémy, Borel Clément
*
*                                Haute Ecole Arc Ingénierie
* 	 	 	 	 	 	 	 	 Année académique 2011-2012
* 	 	 	 	 	 	 	 	 	 	 12 mars 2012
*
* 	 	 	 	 	 	   Laboratoire 2 d'Algorithmes Numériques
*                                   Résolution d'equations
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

//#define USING_FIRST_FUNCTION
//#define USING_BISECTION

const double LEFTLIMIT = -20;
const double RIGHTLIMIT = 20;
const double MAXHEIGHT = 4.1;
const double MINHEIGHT = -4.1;

const double TEST_EPSILON = 0.02;
const double STARTING_POINT = 0.1;
const double TEST_LAMBDA = 5.0;
const int LOOP_LIMIT = 10000;

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
void bolzanoBisectionRecursive(double a, double b, double epsilon = TEST_EPSILON);
void fixedPoint(double epsilon = TEST_EPSILON, double lambda = TEST_LAMBDA, double startingPoint = STARTING_POINT);

/****************************************************
*                  Helper functions
 ****************************************************/
double fixedPointLinearFunction(double x);
double fixedPointAdapterFunction(double x, double lambda = TEST_LAMBDA);
bool oppositeSigns(double a, double b);
void plotCurrentFunction();
void plotLinearFunction();
void plotAdaptedFunction(double lambda = TEST_LAMBDA);

/******************************************************************************************
*
* 	 	 	 	 	 	 	 	 	 Beginning of the program
*
 ******************************************************************************************/
void mainFunction(void)
{
    #ifdef USING_FIRST_FUNCTION
    cout << "First function is defined " << endl;
    #else
    cout << "Second function is defined " << endl;
    #endif

    #ifdef USING_BISECTION
    plotCurrentFunction();
    cout << "Starting recursive Bolzano method ... " << endl;
    bolzanoBisectionRecursive(LEFTLIMIT,RIGHTLIMIT,0.02);

    #else
    cout << "Starting fixed point method ... " << endl;
    plotLinearFunction();
    plotAdaptedFunction();
    fixedPoint(0.2, 5);
    #endif
    cout << "___________________________________________________________________________" << endl;
}

int main(int argc, char **argv)
{
  graphWin.initGraphicsWin( 1000, LEFTLIMIT, RIGHTLIMIT, MINHEIGHT, MAXHEIGHT );
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
        #ifdef USING_FIRST_FUNCTION
        if (f(a) <= epsilon )
        #else
        if (g(a) <= epsilon )
        #endif
        cout << endl << ">>> " << b << " <<<<" << endl << endl;
        return;
    }
    double c = (a+b)/2;

    graphWin.segment(a,MAXHEIGHT,a,MINHEIGHT);
    graphWin.segment(b,MAXHEIGHT,b,MINHEIGHT);
    graphWin.segment(c,MAXHEIGHT,c,MINHEIGHT);

    cout << "Analysing interval [" << a <<", " << b << "] with middle point at : "<< c <<endl;
    if (c == 0)
    {
        cout << "0 is in " << c << endl;
    }
    #ifdef USING_FIRST_FUNCTION
    if (oppositeSigns(f(a),f(c)))
    #else
    if (oppositeSigns(g(a),g(c)))
    #endif
    {
        cout << " Narrowing interval to [" << a <<", " << c << "]" << endl;
        bolzanoBisectionRecursive(a,c,epsilon);
    }

    #ifdef USING_FIRST_FUNCTION
    if (oppositeSigns(f(c), f(b)))
    #else
    if (oppositeSigns(g(c), g(b)))
    #endif
    {
        cout << " Narrowing interval to [" << c <<", " << b << "]" << endl;
        bolzanoBisectionRecursive(c,b,epsilon);
    }
}

void plotCurrentFunction()
{
    for(double i = LEFTLIMIT; i <= RIGHTLIMIT; i = i + 0.001)
    {
        #ifdef USING_FIRST_FUNCTION
        graphWin.plot(i,f(i),1);
        #else
        graphWin.plot(i,g(i),1);
        #endif
    }
}

double fixedPointLinearFunction(double x)
{
    return x;
}

double fixedPointAdapterFunction(double x, double lambda)
{
    #ifdef USING_FIRST_FUNCTION
    return lambda * f(x) + x;
    #else
    return lambda * g(x) + x;
    #endif
}

void plotLinearFunction()
{
    for(double i =- LEFTLIMIT; i < RIGHTLIMIT; i += 0.01)
    {
        graphWin.plot(i, fixedPointLinearFunction(i), 1);
    }
}

void plotAdaptedFunction(double lambda)
{
    for(double i =- LEFTLIMIT; i < RIGHTLIMIT; i += 0.01)
    {
        graphWin.plot(i, fixedPointAdapterFunction(i, lambda), 1);
    }
}

void fixedPoint(double epsilon, double lambda, double startingPoint)
{
    double previousPoint = startingPoint;
    int loopCounter = 0;
    while (fabs(fixedPointAdapterFunction(previousPoint) - previousPoint) > epsilon || loopCounter < LOOP_LIMIT)
    {
        previousPoint=fixedPointAdapterFunction(previousPoint);
        graphWin.segment(previousPoint, fixedPointAdapterFunction(previousPoint), fixedPointAdapterFunction(previousPoint), fixedPointAdapterFunction(previousPoint));
        graphWin.segment(previousPoint, previousPoint, previousPoint, fixedPointAdapterFunction(previousPoint));
        loopCounter++;
    }

    #ifdef USING_FIRST_FUNCTION
    if(f(previousPoint) <= epsilon)
    #else
    if(g(previousPoint) <= epsilon)
    #endif
    {
        cout << "x = " << previousPoint << endl;
        #ifdef USING_FIRST_FUNCTION
        //cout<<". Function gives value of  " << f(previousPoint) << " which is smaller than epsilon (" << epsilon << ")." <<  endl;
        #else
        //cout<<". Function gives value of  " << g(previousPoint) << " which is smaller than epsilon (" << epsilon << ")." <<  endl;
        #endif
    }
    else
    {
        std::cout<<"Zero prob : "<<previousPoint<<std::endl;
        //std::cout<<"Value : "<<g2(previousPoint)<<std::endl;
    }
    if(lambda > 0.0)
    {
        lambda -= 2;
        fixedPoint(epsilon, lambda);
    }
}
