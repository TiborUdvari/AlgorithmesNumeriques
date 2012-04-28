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

using namespace std;

/******************************************************************************************
 *
 * 	 	 	 	 Globals / Typedefs / Constants
 *
 ******************************************************************************************/

enum functionENUM
    {
    PI_FUNCTION
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

/*------------------------------------------------------------------*\
|*			   Test Functions		            *|
 \*------------------------------------------------------------------*/
/* --- NOTE --- */
// Here we only use this PI function but to be able to expand it to other functions we will be able to very easily
double piFunction(double x);

/*------------------------------------------------------------------*\
|*			 Integration functions		            *|
 \*------------------------------------------------------------------*/
// We use rectangleNumber to be sure that dx is correct, that we have equal rectangles and we will not have any problems at the limits
double calculateIntegralReimann(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber, reimannRectangleTypeENUM rectangleType);
double calculateIntegralMiddlePoint(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber);
double calculateIntegralTrapezoid(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber);
/*------------------------------------------------------------------*\
|*			 Helper functions		            *|
 \*------------------------------------------------------------------*/
double calculateFunctionValue(double x, functionENUM function);
void checkAndFixLimits(double &leftLimit, double &rightLimit);
void exchange(double &a, double &b);

double calculateIntegralTrapezoid(functionENUM function, double leftLimit, double rightLimit);

/******************************************************************************************
 *
 * 	 	 	 	 Beginning of the program
 *
 ******************************************************************************************/

int main()
    {
    // pi = 3,14159265
    //TODO try with largest
    unsigned int largestUnisgnedInt = 10000000;

    double piDivisePar4;
    //piDivisePar4 = calculateIntegralReimann(PI_FUNCTION, 0, 1, largestUnisgnedInt, UPPER_RECTANGLE);

    piDivisePar4 = calculateIntegralMiddlePoint(PI_FUNCTION, 0, 1, largestUnisgnedInt);

    double pi = piDivisePar4 * 4;
    cout << "Premier approximation de pi : " << pi << endl;

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
|*			 Integration functions		            *|
 \*------------------------------------------------------------------*/
double calculateIntegralReimann(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber, reimannRectangleTypeENUM rectangleType)
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
	currentRectangleSurface = rectangleWidth * currentRectangleHeight;
	integral += currentRectangleSurface;
	}

    return integral;
    }

double calculateIntegralMiddlePoint(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber)
    {
    checkAndFixLimits(leftLimit, rightLimit);
    double integral = 0;
    double delta = (rightLimit - leftLimit) / rectangleNumber;

    // using small rectangles underneath function
    double rectangleWidth = delta;
    double currentRectangleHeight;
    double currentRectangleSurface;

    // Poits
    double middlePoint;
    for (double x = leftLimit; x < rightLimit; x += delta)
	{
	middlePoint = x + delta / 2;
	currentRectangleHeight = calculateFunctionValue(middlePoint, function);
	currentRectangleSurface = rectangleWidth * currentRectangleHeight;
	integral += currentRectangleSurface;
	}

    return integral;

    }

double calculateIntegralTrapezoid(functionENUM function, double leftLimit, double rightLimit, unsigned int rectangleNumber)
    {
    checkAndFixLimits(leftLimit, rightLimit);
    double integral = 0;
    double delta = (rightLimit - leftLimit) / rectangleNumber;

    for (double x = leftLimit; x < rightLimit; x += delta)
	{
	integral += calculateIntegralTrapezoid(function, x, x + delta);
	}

    return integral;
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

double calculateIntegralTrapezoid(functionENUM function, double leftLimit, double rightLimit)
    {
    checkAndFixLimits(leftLimit, rightLimit);
    double width = rightLimit - leftLimit;
    double leftLimitHeight = calculateFunctionValue(leftLimit, function);
    double rightLimitHeight = calculateFunctionValue(rightLimit, function);
    double height = (leftLimitHeight + rightLimitHeight) / 2;

    return width * height;
    }

