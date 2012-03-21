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
 * 	 	 	 	 	 	 	 	 	 	 20 mars 2012
 *
 * 	 	 	 	 	 	   Laboratoire 2 d'Algorithmes Numériques
 *                                   Résolution d'equations
 *
 *	Description:
 *   Implémentation de la méthode de bisection de Bolzano et la méthode du point fixe
 *
 ********************************************************************************************/

#include <math.h>
#include <stdio.h>
#include <iostream>

#include "main.h"
#include "GeomGlut.h"

extern GeomGlut graphWin;

/******************************************************************************************
 *
 * 	 	 	 	 	 	   Globals / Typedefs / Defines / Constants
 *
 ******************************************************************************************/
using namespace std;

int numberLine = 0;
/****************************************************
 *  Comment, uncomment here for different behaviour
 ****************************************************/

#define USING_FIRST_FUNCTION
#define USING_BISECTION

const double LEFTLIMIT = -5.0;
const double RIGHTLIMIT = 5.0;
const double MAXHEIGHT = 4.1;
const double MINHEIGHT = -4.1;

const double TEST_EPSILON = 0.01;
const double STARTING_POINT = 0.1;
const double TEST_LAMBDA = 5.2;
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
void fixedPoint(double epsilon = TEST_EPSILON, double lambda = TEST_LAMBDA, double startingPoint = STARTING_POINT, bool isFirst = false);

/****************************************************
 *                  Helper functions
 ****************************************************/
void plotCurrentFunction();
bool oppositeSigns(double a, double b);

double fixedPointLinearFunction(double x);
double fixedPointAdapterFunction(double x, double lambda = TEST_LAMBDA);
void plotLinearFunction();
void plotAdaptedFunction(double lambda = TEST_LAMBDA);

/******************************************************************************************
 *
 * 	 	 	 	 	 	 	 	 	 Beginning of the program
 *
 ******************************************************************************************/
void mainFunction(void)
{
    numberLine = 0;
#ifdef USING_FIRST_FUNCTION
    cout << "First function is defined " << endl;
#else
    cout << "Second function is defined " << endl;
#endif

#ifdef USING_BISECTION
    plotCurrentFunction();
    cout << "Starting recursive Bolzano method ... " << endl;
    bolzanoBisectionRecursive(LEFTLIMIT+0.2,RIGHTLIMIT,0.02);//little offset on the leftLimit to get more graphically interesting results

#else
    double lambda = 5.2;

    cout << "Starting fixed point method ... " << endl;
    plotLinearFunction();
    fixedPoint(0.01, lambda, 0.1);
#endif
    cout << "___________________________________________________________________________" << endl;

}

int main(int argc, char **argv)
{
    graphWin.initGraphicsWin( 1000, LEFTLIMIT, RIGHTLIMIT, MINHEIGHT, MAXHEIGHT );
    mainFunction();
    return(0);
}

/******************************************************************************************
 *
 * 	 	 	 	 	 	 	 	 	 Function declarations
 *
 ******************************************************************************************/
/****************************************************
 *        Mathematical functions for testing
 ****************************************************/

double f(double x)
{
    return sin(x) - x/3;
}

double g(double x)
{
    return x/(1-pow(x,2));
}

/****************************************************
 *                  Solving methods
 ****************************************************/

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

void fixedPoint(double epsilon, double lambda, double startingPoint,bool isFirst)
{
    double previousPoint = startingPoint;
    int loopCounter = 0;
    while (fabs(fixedPointAdapterFunction(previousPoint) - previousPoint) > epsilon && loopCounter < LOOP_LIMIT)
    {
        previousPoint=fixedPointAdapterFunction(previousPoint, lambda);
        if(numberLine == 2)
        {
            plotAdaptedFunction(lambda);//we plot it here to have the proper lamda drawn
            graphWin.segment(previousPoint, fixedPointAdapterFunction(previousPoint, lambda), fixedPointAdapterFunction(previousPoint, lambda), fixedPointAdapterFunction(previousPoint, lambda));
            graphWin.segment(previousPoint, previousPoint, previousPoint, fixedPointAdapterFunction(previousPoint, lambda));
        }
        loopCounter++;
    }

#ifdef USING_FIRST_FUNCTION
    if(f(previousPoint) <= epsilon)
#else
        if(g(previousPoint) <= epsilon)
#endif
        {
            graphWin.plot(previousPoint,fixedPointAdapterFunction(previousPoint, lambda),5);
            cout << "x = " << previousPoint << endl;
        }
        else
        {
            cout << "x MAUVAIS = " << previousPoint << endl;
        }

    double tester = 2.0;
    if(lambda > tester)
    {
        numberLine++;
        lambda -= tester;
        fixedPoint(epsilon, lambda,startingPoint);
    }
}

/****************************************************
 *                  Helper functions
 ****************************************************/
void plotCurrentFunction()
{
    for(double i = LEFTLIMIT; i <= RIGHTLIMIT; i = i + 0.01)
    {
#ifdef USING_FIRST_FUNCTION
        graphWin.plot(i,f(i),1);
#else
        graphWin.plot(i,g(i),1);
#endif
    }
}

bool oppositeSigns(double a, double b)
{
    return (a*b) < 0;
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
    graphWin.segment(LEFTLIMIT, LEFTLIMIT, RIGHTLIMIT, RIGHTLIMIT);
}

void plotAdaptedFunction(double lambda)
{
    for(double i = LEFTLIMIT; i < RIGHTLIMIT; i += 0.01)
    {
        graphWin.plot(i, fixedPointAdapterFunction(i, lambda), 1);
    }
}
