/********************************************************************************************
 *
 *				       Equipe 1
 *
 * 	 	  Laurent Novac, Tibor Udvari, Clément Borel, Jérémy Landry
 *
 *                             Haute Ecole Arc Ingénierie
 * 	 	 	       Année académique 2011-2012
 * 	 	 	 	      24 avr. 2012
 *
 * 	 	 	  Laboratoire 4 d'algorithmes numériques
 *                                 Dérivation numérique
 *
 *   Description:
 *   Implementation of 3 derivation methods :
 *   	Progressive Difference
 *   	Central Difference
 *   	Fourth Degree Polynom
 *   and the second degree derivative.
 *   We have created functions to calculate, demonstrate, and plot all of these methods and
 *   applied them to solve the problem of optimising gold buying and selling.
 ********************************************************************************************/

#include <iostream>
#include <cmath>
#include "GeomGlut.h"

extern GeomGlut graphWin;

using namespace std;

/******************************************************************************************
 *
 * 	 	 	 	 Globals / Typedefs / Constants
 *
 ******************************************************************************************/
//For everything except the derivation methods demonstations
/*
 const double LEFT = -15.1;
 const double RIGHT = 15.1;
 const double BOTTOM = -4.1;
 const double TOP = 4.1;
 */

// For derivation method demonstration
const double LEFT = -1;
const double RIGHT = 1;
const double BOTTOM = -1;
const double TOP = 1;

enum FunctionENUM
    {
    FUNCTION1,
    FUNCTION2,
    GOLD_FUNCTION
    };

enum FunctionNatureENUM
    {
    NORMAL,
    DERIVATIVE,
    DOUBLE_DERIVATIVE
    };

enum DerivationMethodENUM
    {
    PROGRESSIVE_DIFFERENCE,
    CENTRAL_DIFFERENCE,
    FOURTH_DEGREE_POLYNOM
    };

// From 1991 to 2011
// source : http://www.onlygold.com/tutorialpages/prices200yrsfs.htm
double arrayGold[] =
{
353.15, 333.0, 391.75, 383.25, 387.0, 369.0, 287.05, 288.7, 290.25, 272.65, 276.50, 342.75, 417.25, 435.6, 513.0, 635.7, 836.5, 869.75, 1087.5, 1420.25, 1531.0
};
/******************************************************************************************
 *
 * 	 	 	 	 Function prototypes
 *
 ******************************************************************************************/
/*------------------------------------------------------------------*\
|*			   Test functions		            *|
 \*------------------------------------------------------------------*/
double f1(double x);
double f2(double x);

/*------------------------------------------------------------------*\
|*			 Calculation functions	     	            *|
 \*------------------------------------------------------------------*/
double calculateDerivative(FunctionENUM function, double x, double h, DerivationMethodENUM derivativeMethod);

double calculateDerivativeProgressiveDifference(FunctionENUM function, double x, double h);
double calculateDerivativeCentralDifference(FunctionENUM function, double x, double h);
double calculateDerivativeFourthDegreePolynom(FunctionENUM function, double x, double h);
double calculateSecondDegreeDerivative(FunctionENUM function, double x, double h);

void printCriticalPointsForGoldFunction(DerivationMethodENUM derivativeMethod);

/*------------------------------------------------------------------*\
|*			Visualization functions	     	            *|
 \*------------------------------------------------------------------*/
void plotFunction(FunctionENUM function);
void plotDerivationMethod(FunctionENUM function, double x, double h, DerivationMethodENUM derivativeMethod);
void plotDerivatedFunction(FunctionENUM function, DerivationMethodENUM derivationMethod, double h);
void plotSecondDegreeDerivatedFunction(FunctionENUM function, double h);

inline double map(double value, double min1, double max1, double min2, double max2)
    {
    double slope = (max2 - min2) / (max1 - min1);
    return min2 + value * slope;
    }

/******************************************************************************************
 *
 * 	 	 	 	 Beginning of the program
 *
 ******************************************************************************************/

void mainFunction()
    {
    double h = 0.0001;

    // Demonstration of derivation methods on function 2
    // Don't forget to change the limits (uncomment the lines at the top)

    plotFunction(FUNCTION2);
    //plotDerivationMethod(FUNCTION2, 0.2, 0.1, PROGRESSIVE_DIFFERENCE);
    //plotDerivationMethod(FUNCTION2, 0.2, 0.1, CENTRAL_DIFFERENCE);
    plotDerivationMethod(FUNCTION2, 0.2, 0.1, FOURTH_DEGREE_POLYNOM);

    //Plot first function and derivatives

    //plotFunction(FUNCTION1);
    //plotDerivatedFunction(FUNCTION1, PROGRESSIVE_DIFFERENCE, h);
    //plotDerivatedFunction(FUNCTION1, CENTRAL_DIFFERENCE, h);
    //plotDerivatedFunction(FUNCTION1, FOURTH_DEGREE_POLYNOM, h);
    //plotSecondDegreeDerivatedFunction(FUNCTION1, h);

    //Plot second function and derivative

    //plotFunction(FUNCTION2);
    //plotDerivatedFunction(FUNCTION2, PROGRESSIVE_DIFFERENCE, h);
    //plotDerivatedFunction(FUNCTION2, CENTRAL_DIFFERENCE, h);
    //plotDerivatedFunction(FUNCTION2, FOURTH_DEGREE_POLYNOM, h);
    //plotSecondDegreeDerivatedFunction(FUNCTION2, h);

    //Plot the gold function and the derivatives

    //plotFunction(GOLD_FUNCTION);
    //plotDerivatedFunction(GOLD_FUNCTION, PROGRESSIVE_DIFFERENCE, 1);
    //plotDerivatedFunction(GOLD_FUNCTION, CENTRAL_DIFFERENCE, 1);
    //plotSecondDegreeDerivatedFunction(GOLD_FUNCTION, 1);

    // Get the critical points of the gold function

    //printCriticalPointsForGoldFunction(PROGRESSIVE_DIFFERENCE);
    //printCriticalPointsForGoldFunction(CENTRAL_DIFFERENCE);

    }

int main(int argc, char **argv)
    {
    graphWin.initGraphicsWin(1000, LEFT, RIGHT, BOTTOM, TOP);
    mainFunction();
    return 0;
    }

/******************************************************************************************
 *
 * 	 	 	 	 Function declarations
 *
 ******************************************************************************************/
/*------------------------------------------------------------------*\
|*			    Test Functions		            *|
 \*------------------------------------------------------------------*/
double f1(double x)
    {
    return pow(x, 5) + 5 * pow(x, 3) + 2 * x;
    }

double f2(double x)
    {
    return x / (1 - pow(x, 2));
    }
/*------------------------------------------------------------------*\
|*			 Calculation Functions		            *|
 \*------------------------------------------------------------------*/
double calculateDerivative(FunctionENUM function, double x, double h, DerivationMethodENUM derivativeMethod)
    {
    double derivative;
    switch (derivativeMethod)
	{
    case PROGRESSIVE_DIFFERENCE:
	derivative = calculateDerivativeProgressiveDifference(function, x, h);
	break;
    case CENTRAL_DIFFERENCE:
	derivative = calculateDerivativeCentralDifference(function, x, h);
	break;
    case FOURTH_DEGREE_POLYNOM:
	derivative = calculateDerivativeFourthDegreePolynom(function, x, h);
	break;
    default:
	break;
	}
    return derivative;
    }

double calculateDerivativeProgressiveDifference(FunctionENUM function, double x, double h)
    {
    double derivative;
    switch (function)
	{
    case FUNCTION1:
	derivative = (f1(x + h) - f1(x)) / h;
	break;
    case FUNCTION2:
	derivative = (f2(x + h) - f2(x)) / h;
	break;
    case GOLD_FUNCTION:
	if (x < 0 || x > 18)
	    {
	    cout << "Out of range" << endl;
	    return -1;
	    }
	h = 1;
	derivative = (arrayGold[int(x + h)] - arrayGold[int(x)]) / h;
	break;
    default:
	cout << "The given function does not exist.";
	break;
	}
    return derivative;
    }

double calculateDerivativeCentralDifference(FunctionENUM function, double x, double h)
    {
    double derivative;
    switch (function)
	{
    case FUNCTION1:
	derivative = (f1(x + h) - f1(x - h)) / (2 * h);
	break;
    case FUNCTION2:
	derivative = (f2(x + h) - f2(x - h)) / (2 * h);
	break;
    case GOLD_FUNCTION:
	if (x < 1 || x > 18)
	    {
	    cout << "Out of range" << endl;
	    return -1;
	    }
	h = 1;
	derivative = (arrayGold[int(x + h)] - arrayGold[int(x - h)]) / (2 * h);
	break;
    default:
	cout << "The given function does not exist.";
	break;
	}
    return derivative;
    }

double calculateDerivativeFourthDegreePolynom(FunctionENUM function, double x, double h)
    {
    double derivative;
    switch (function)
	{
    case FUNCTION1:
	derivative = (8 * (f1(x + h / 2) - f1(x - h / 2)) - f1(x + h) + f1(x - h)) / (6 * h);
	break;
    case FUNCTION2:
	derivative = (8 * (f2(x + h / 2) - f2(x - h / 2)) - f2(x + h) + f2(x - h)) / (6 * h);
	break;
    default:
	cout << "The given function does not exist.";
	break;
	}
    return derivative;
    }

double calculateSecondDegreeDerivative(FunctionENUM function, double x, double h)
    {
    double derivative;
    switch (function)
	{
    case FUNCTION1:
	derivative = (f1(x + h) + f1(x - h) - 2 * f1(x)) / pow(h, 2);
	break;
    case FUNCTION2:
	derivative = (f2(x + h) + f2(x - h) - 2 * f2(x)) / pow(h, 2);
	break;
    case GOLD_FUNCTION:
	h = 1;
	derivative = (arrayGold[int(x + h)] + arrayGold[int(x + h)] - 2 * arrayGold[int(x)]) / pow(h, 2);
	break;
    default:
	break;
	}
    return derivative;
    }

void printCriticalPointsForGoldFunction(DerivationMethodENUM derivativeMethod)
    {
    double leftLimit = derivativeMethod == CENTRAL_DIFFERENCE ? 1 : 0;
    for (int i = leftLimit; i < 19; i++)
	{
	double derivative = calculateDerivative(GOLD_FUNCTION, i, 1, derivativeMethod);
	double epsilon = 2;
	if (abs(derivative) <= epsilon)
	    {
	    double secondDegreeDerivative = calculateSecondDegreeDerivative(GOLD_FUNCTION, i, 1);
	    cout << i + 1991 << ", " << arrayGold[i] << " Derivative : " << derivative << " Second Derivative : " << secondDegreeDerivative << endl;
	    }
	}

    }
/*------------------------------------------------------------------*\
|*			Visualization functions	     	            *|
 \*------------------------------------------------------------------*/
void plotFunction(FunctionENUM function)
    {
    switch (function)
	{
    case FUNCTION1:
	for (double i = LEFT; i <= RIGHT; i += 0.001)
	    {
	    graphWin.plot(i, f1(i), 1);
	    }
	break;

    case FUNCTION2:
	for (double i = LEFT; i <= RIGHT; i += 0.0001)
	    {
	    graphWin.plot(i, f2(i), 1);
	    }
	break;
    case GOLD_FUNCTION:
	for (int i = 0; i < 19; i++)
	    {
	    graphWin.segment(map(i, 0, 19, 0, RIGHT), map(arrayGold[i], 250, 1700, 0, TOP), map(i + 1, 0, 19, 0, RIGHT), map(arrayGold[i + 1], 250, 1700, 0, TOP));
	    }
	break;
    default:
	cout << "The given function does not exist";
	break;
	}
    }

void plotDerivationMethod(FunctionENUM function, double x, double h, DerivationMethodENUM derivativeMethod)
    {
    switch (function)
	{
    case FUNCTION1:
	switch (derivativeMethod)
	    {
	case PROGRESSIVE_DIFFERENCE:
	    for (double delta = 0; delta <= h; delta += h)
		{
		graphWin.plot(x + delta, f1(x + delta), 4);
		graphWin.segment(x + delta, 0, x + delta, f1(x + delta));
		graphWin.segment(0, f1(x + delta), x + delta, f1(x + delta));
		}

	    //Segment between two points
	    graphWin.segment(x, f1(x), x + h, f1(x + h));

	    break;
	case CENTRAL_DIFFERENCE:
	    for (double delta = -h; delta <= h; delta += h)
		{
		//Points
		graphWin.plot(x + delta, f1(x + delta), 4);
		//Lines from X axe
		graphWin.segment(x + delta, 0, x + delta, f1(x + delta));
		//Lines from Y axe
		graphWin.segment(0, f1(x + delta), x + delta, f1(x + delta));
		}
	    //Segment between two points
	    graphWin.segment(x - h, f1(x - h), x + h, f1(x + h));
	    break;
	case FOURTH_DEGREE_POLYNOM:
	    for (double delta = -h; delta <= h; delta += h / 2)
		{
		graphWin.segment(x + delta, 0, x + delta, f1(x + delta));
		graphWin.plot(x + delta, f1(x + delta), 4);
		}
	    break;
	default:
	    break;
	    }
	break;
    case FUNCTION2:
	switch (derivativeMethod)
	    {
	case PROGRESSIVE_DIFFERENCE:
	    for (double delta = 0; delta <= h; delta += h)
		{
		graphWin.plot(x + delta, f2(x + delta), 4);
		graphWin.segment(x + delta, 0, x + delta, f2(x + delta));
		graphWin.segment(0, f2(x + delta), x + delta, f2(x + delta));
		}

	    //Segment between two points
	    graphWin.segment(x, f2(x), x + h, f2(x + h));
	    break;
	case CENTRAL_DIFFERENCE:
	    for (double delta = -h; delta <= h; delta += h)
		{
		//Points
		graphWin.plot(x + delta, f2(x + delta), 4);
		//Lines from X axe
		graphWin.segment(x + delta, 0, x + delta, f2(x + delta));
		//Lines from Y axe
		graphWin.segment(0, f2(x + delta), x + delta, f2(x + delta));
		}
	    //Segment between two points
	    graphWin.segment(x - h, f2(x - h), x + h, f2(x + h));
	    break;
	case FOURTH_DEGREE_POLYNOM:
	    for (double delta = -h; delta <= h; delta += h / 2)
		{
		graphWin.segment(x + delta, 0, x + delta, f2(x + delta));
		graphWin.plot(x + delta, f2(x + delta), 4);
		}
	    break;
	default:
	    break;
	    }
	break;
    default:
	break;
	}
    }

void plotDerivatedFunction(FunctionENUM function, DerivationMethodENUM derivationMethod, double h)
    {
    if (function != GOLD_FUNCTION)
	{
	for (double i = LEFT; i <= RIGHT; i += 0.001)
	    {
	    graphWin.plot(i, calculateDerivative(function, i, h, derivationMethod), 1);
	    }
	}
    else
	{
	double leftLimit = derivationMethod == CENTRAL_DIFFERENCE ? 1 : 0;

	for (double i = leftLimit; i < 18; i += 1)
	    {
	    double derivative = calculateDerivative(function, i, h, derivationMethod);
	    double derivativePlusOne = calculateDerivative(function, i + 1, h, derivationMethod);
	    graphWin.segment(map(i, 0, 19, 0, RIGHT), map(derivative, 250, 1700, 0, TOP), map(i + 1, 0, 19, 0, RIGHT), map(derivativePlusOne, 250, 1700, 0, TOP));
	    }
	}

    }

void plotSecondDegreeDerivatedFunction(FunctionENUM function, double h)
    {
    if (function != GOLD_FUNCTION)
	{
	for (double i = LEFT; i <= RIGHT; i += 0.001)
	    {
	    graphWin.plot(i, calculateSecondDegreeDerivative(function, i, h), 1);
	    }
	}
    else
	{
	for (double i = 0; i < 18; i += 1)
	    {
	    double secondDegreeDerivative = calculateSecondDegreeDerivative(function, i, h);
	    double secondDegreeDerivativePlusOne = calculateSecondDegreeDerivative(function, i + 1, h);
	    graphWin.segment(map(i, 0, 19, 0, RIGHT), map(secondDegreeDerivative, 250, 1700, 0, TOP), map(i + 1, 0, 19, 0, RIGHT), map(secondDegreeDerivativePlusOne, 250, 1700, 0, TOP));
	    }
	}
    }

void plotFunction(functionENUM function, unsigned int pointSize, float redColor, float greenColor, float blueColor)
    {
    }

void drawRectangle(double x1, double y1, double x2, double y2)
    {
    }

void demonstrateReimannUpperRectangles()
    {
    }

void main(int choice)
    {
    }

void menu(int choice)
    {
    }






