/********************************************************************************************
 *
 *				       Equipe 1
 *
 * 	 	  Laurent Novac, Tibor Udvari, Clément Borel, Jérémy Landry
 *
 *                             Haute Ecole Arc Ingénierie
 * 	 	 	       Année académique 2011-2012
 * 	 	 	 	      28 avr. 2012
 *
 * 	 	 	  Laboratoire 5 d'algorithmes numériques
 *                                 Intégration Numérique
 *
 *   Description:
 *   Implémentation des algorithmes d'intégration et utilisation pour un aproximation de PI
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
// Recommended settings for demonstrations

const double LEFT = -0.3;
const double RIGHT = 2;
const double BOTTOM = -0.1;
const double TOP = 1.5;

// Recommended settings for general overview, nature of the given function
/*
const double LEFT = -7;
const double RIGHT = 7;
const double BOTTOM = -2;
const double TOP = 2;
*/

enum functionENUM
    {
    PI_FUNCTION,
    SIN_FUNCTION
    };

enum reimannRectangleTypeENUM
    {
    UPPER_RECTANGLE,
    LOWER_RECTANGLE
    };

/******************************************************************************************
 *
 * 	 	 	 	 Function prototypes
 *
 ******************************************************************************************/
void mainFunction();
/*------------------------------------------------------------------*\
|*			   Test Functions		            *|
 \*------------------------------------------------------------------*/
/* --- NOTE --- */
// Here we only use this PI function but to be able to expand it to other functions we will be able to very easily
double piFunction(double x);

/*------------------------------------------------------------------*\
|*			  Use functions			            *|
\*------------------------------------------------------------------*/
void demonstrateReimannUpperRectangles();
void demonstrateReinmannLowerRectangles();
void demonstrateMiddlePoint();
void demonstrateTrapezoid();
void demonstrateSinFunctionWithReinmannUpper();


/*------------------------------------------------------------------*\
|*			 Integration functions		            *|
 \*------------------------------------------------------------------*/
// We use rectangleNumber to be sure that dx is correct, that we have equal rectangles and we will not have any problems at the limits
double calculateIntegralReimann(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber, reimannRectangleTypeENUM rectangleType, bool visualise = false, float redColor = 0.0f,float greenColor = 0.0f ,float blueColor = 0.0f);
double calculateIntegralMiddlePoint(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber, bool visualise = false, float redColor = 0.0f,float greenColor = 0.0f ,float blueColor = 0.0f);
double calculateIntegralTrapezoid(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber, bool visualise = false, float redColor = 0.0f,float greenColor = 0.0f ,float blueColor = 0.0f);
double calculateIntegralMedianPoint(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber);
double calculateIntegralSimpson(functionENUM function, double leftLimit, double rightLimit, unsigned int n);

/*------------------------------------------------------------------*\
|*			Visualisation functions		            *|
 \*------------------------------------------------------------------*/
//TODO
void plotFunction(functionENUM function, unsigned int pointSize = 1, float redColor = 0.0f,float greenColor = 0.0f ,float blueColor = 0.0f);

void drawRectangle(double x1, double y1, double x2, double y2,float redColor = 0.0f,float greenColor = 0.0f ,float blueColor = 0.0f );
/*------------------------------------------------------------------*\
|*			 Helper functions		            *|
 \*------------------------------------------------------------------*/
double calculateFunctionValue(double x, functionENUM function);
void checkAndFixLimits(double &leftLimit, double &rightLimit);
void exchange(double &a, double &b);

void checkNForSimpsonMethod(unsigned int &n);
double calculateIntegralTrapezoid(functionENUM function, double leftLimit, double rightLimit, bool visualise = false, float redColor = 0.0f,float greenColor = 0.0f ,float blueColor = 0.0f);

/******************************************************************************************
 *
 * 	 	 	 	 Beginning of the program
 *
 ******************************************************************************************/

void mainFunction()
    {
    // pi = 3,14159265

    //TODO check limit values on all function, may have fucked up
    //TODO replace unsigned ints with doubles, maybe will get a better result, but this will ruin the minimum protection we have for having positive values

    double piDivisePar4;
    piDivisePar4 = calculateIntegralSimpson(PI_FUNCTION,0,1,9999999);

    double pi = piDivisePar4 * 4;
    cout << "Premier approximation de pi : " << pi << endl;

    // Use fonctions, decomment for visual feedback
    // Please decomment at top for recommended settings

    //demonstrateMiddlePoint();
    //demonstrateReimannUpperRectangles();
    //demonstrateReinmannLowerRectangles();
    //demonstrateSinFunctionWithReinmannUpper();
    demonstrateTrapezoid();
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
|*			   Test Functions		            *|
 \*------------------------------------------------------------------*/
double piFunction(double x)
    {
    return 1 / (1 + pow(x, 2));
    }

/*------------------------------------------------------------------*\
|*			  Use functions			            *|
\*------------------------------------------------------------------*/

void demonstrateReimannUpperRectangles()
    {
    plotFunction(PI_FUNCTION,1);
    calculateIntegralReimann(PI_FUNCTION, 0, 1, 5, UPPER_RECTANGLE,true);
    }

void demonstrateReinmannLowerRectangles()
    {
    plotFunction(PI_FUNCTION,1);
    calculateIntegralReimann(PI_FUNCTION, 0, 1, 5, LOWER_RECTANGLE,true);
    }

void demonstrateMiddlePoint()
    {
    plotFunction(PI_FUNCTION,1);
    calculateIntegralMiddlePoint(PI_FUNCTION, 0, 1, 5,true, 1.0f, 0.0f,0.0f);
    }

void demonstrateTrapezoid()
    {
    plotFunction(PI_FUNCTION,1);
    calculateIntegralTrapezoid(PI_FUNCTION, 0,1,3,true, 0.0f, 1.0f, 0.0f);
    }

void demonstrateSinFunctionWithReinmannUpper()
    {
    plotFunction(SIN_FUNCTION,1);
    calculateIntegralReimann(SIN_FUNCTION, -1, 1, 10, UPPER_RECTANGLE,true);
    }

/*------------------------------------------------------------------*\
|*			 Integration functions		            *|
 \*------------------------------------------------------------------*/
double calculateIntegralReimann(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber, reimannRectangleTypeENUM rectangleType, bool visualise, float redColor,float greenColor,float blueColor)
    {
    checkAndFixLimits(leftLimit, rightLimit);
    double integral = 0;
    double delta = (rightLimit - leftLimit) / rectangleNumber;

    // using small rectangles underneath function
    double rectangleWidth = delta;
    double currentRectangleHeight;
    double currentRectangleSurface;

    // Poits
    double firstPoint;
    double secondPoint;
    for (double x = leftLimit; x < rightLimit; x += delta)
	{
	switch (rectangleType)
	    {
	case UPPER_RECTANGLE:
	    firstPoint = calculateFunctionValue(x, function);
	    secondPoint = calculateFunctionValue(x + delta, function);
	    currentRectangleHeight = max(firstPoint, secondPoint);
	    break;
	case LOWER_RECTANGLE:
	    firstPoint = calculateFunctionValue(x, function);
	    secondPoint = calculateFunctionValue(x + delta, function);
	    currentRectangleHeight = min(firstPoint, secondPoint);
	    break;
	default:
	    break;
	    }

	if(visualise) drawRectangle(x,currentRectangleHeight, x+delta, redColor, greenColor,blueColor);

	currentRectangleSurface = rectangleWidth * currentRectangleHeight;
	integral += currentRectangleSurface;
	}

    return integral;
    }

double calculateIntegralMiddlePoint(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber, bool visualise, float redColor,float greenColor,float blueColor)
    {
    checkAndFixLimits(leftLimit, rightLimit);
    double integral = 0;
    double delta = (rightLimit - leftLimit) / rectangleNumber;

    double rectangleWidth = delta;
    double currentRectangleHeight;
    double currentRectangleSurface;

    double middlePoint;
    for (double x = leftLimit; x < rightLimit; x += delta)
	{
	middlePoint = x + delta / 2;
	currentRectangleHeight = calculateFunctionValue(middlePoint, function);
	currentRectangleSurface = rectangleWidth * currentRectangleHeight;

	if(visualise)
	    {
	    drawRectangle(x,currentRectangleHeight, x+delta,0, redColor, greenColor,blueColor);
	    graphWin.segment(middlePoint, 0, middlePoint, currentRectangleHeight);
	    graphWin.plot(middlePoint, currentRectangleHeight, 3);
	    }

	integral += currentRectangleSurface;
	}

    return integral;
    }

double calculateIntegralTrapezoid(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber, bool visualise, float redColor,float greenColor,float blueColor)
    {
    checkAndFixLimits(leftLimit, rightLimit);
    double integral = 0;
    double delta = (rightLimit - leftLimit) / rectangleNumber;

    for (double x = leftLimit; x < rightLimit; x += delta)
	{
	integral += calculateIntegralTrapezoid(function, x, x + delta, visualise, redColor, greenColor, blueColor);
	}

    return integral;
    }

double calculateIntegralMedianPoint(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber)
    {
    //TODO ask professor what is the differende between this and middle point mathod
    return 0;
    }

double calculateIntegralSimpson(functionENUM function, double leftLimit, double rightLimit, unsigned int n)
    {
    double integral;
    checkNForSimpsonMethod(n);
    double delta = (rightLimit - leftLimit) / n;

    double evenPart = 0;
    double oddPart = 0;
    cout << "delta = " <<delta << endl;
    cout << "leftLimit = " << leftLimit << endl;
    cout << "rightLimit = " << rightLimit << endl;
    //TODO check these
    for (double x = leftLimit+ delta; x < rightLimit; x += 2 * delta)
	{
	oddPart += calculateFunctionValue(x, function);
	}

    for (double x = leftLimit + 2 * delta; x < rightLimit; x += 2 * delta)
	{
	evenPart += calculateFunctionValue(x, function);
	}

    integral = ( delta / 3 ) *  (calculateFunctionValue(leftLimit, function)    + 4 * oddPart + 2 * evenPart + calculateFunctionValue(rightLimit, function));

    return integral;
    }

/*------------------------------------------------------------------*\
|*			Visualisation functions		            *|
 \*------------------------------------------------------------------*/
void plotFunction(functionENUM function, unsigned int pointSize, float redColor,float greenColor ,float blueColor)
    {
    for(double i = LEFT; i <= RIGHT; i+= 0.001)
	{
	graphWin.plot(i, calculateFunctionValue(i,function),pointSize, redColor, greenColor, blueColor);
	}
    }

void drawRectangle(double x1, double y1, double x2, double y2,float redColor,float greenColor ,float blueColor)
    {
    graphWin.segment(x1,y1,x2,y1,redColor,greenColor, blueColor);
    graphWin.segment(x2,y1,x2,y2,redColor,greenColor, blueColor);
    graphWin.segment(x1,y2,x2,y2,redColor,greenColor, blueColor);
    graphWin.segment(x1,y1,x1,y2,redColor,greenColor, blueColor);
    }
/*------------------------------------------------------------------*\
|*			 Helper functions		            *|
 \*------------------------------------------------------------------*/
double calculateFunctionValue(double x, functionENUM function)
    {
    double calculatedValue;
    switch (function)
	{
    case PI_FUNCTION:
	calculatedValue = piFunction(x);
	break;
    case SIN_FUNCTION:
	calculatedValue = sin(x);
	break;
    default:
	break;
	}
    return calculatedValue;
    }

void checkAndFixLimits(double& leftLimit, double& rightLimit)
    {
    if (leftLimit > rightLimit)
	{
	cout << "Exchanging left and right limit" << endl;
	exchange(leftLimit, rightLimit);
	}
    if (leftLimit == rightLimit)
	{
	cout << "Limits are the same" << endl;
	}
    }

void exchange(double& a, double& b)
    {
    double temp = a;
    a = b;
    b = temp;
    }

double calculateIntegralTrapezoid(functionENUM function, double leftLimit, double rightLimit, bool visualise, float redColor,float greenColor,float blueColor)
    {
    checkAndFixLimits(leftLimit, rightLimit);
    double width = rightLimit - leftLimit;
    double leftLimitHeight = calculateFunctionValue(leftLimit, function);
    double rightLimitHeight = calculateFunctionValue(rightLimit, function);
    double height = (leftLimitHeight + rightLimitHeight) / 2;

    if(visualise)
	{
	graphWin.segment(leftLimit, 0, leftLimit, leftLimitHeight,redColor, greenColor, blueColor);
	graphWin.segment(rightLimit, 0, rightLimit, rightLimitHeight,redColor, greenColor, blueColor);
	graphWin.segment(leftLimit, leftLimitHeight, rightLimit, rightLimitHeight,redColor, greenColor, blueColor);
	}

    return width * height;
    }

void checkNForSimpsonMethod(unsigned int& n)
    {
    if (n % 2 == 1)
	{
	cout << "Given n : " << n << " is not even, decrementing it by one ... " << endl;
	n = n - 1;
	}
    }

