#include <iostream>

using namespace std;

void printFloating(bool x[], int startingBit, int endingBit)
{
    int j = 1;
    float valeur = 0;
    for(int i = endingBit; i >= startingBit; i--)
    {
        if (x[i])
        {
            valeur += j;
        }
        j *= 2;
    }
    std::cout << " " << valeur;
}

//Obligatoire car on a le bit deduit
void printFloatingMantissa(bool x[], int startingBit, int endingBit)
{
    double j = 1;
    float valeur = 0;
    for(int i = endingBit; i >= startingBit; i--)
    {
        if (x[i])
        {
            valeur += j;

        }
        j *= 2;
        //cout << "j est : " << j << endl;
    }
    valeur += j;
    cout.precision(15);

    cout<<std::fixed<< valeur <<endl;
    //std::cout << " " << valeur;
}

int main()
{
    float ourNumber = 1.8;
    bool x[100];

    /******************************\
    |       Sign calculation       |
    \******************************/

    x[0] = ( ourNumber < 0 ) ? 1 : 0;

    /******************************\
    |     Exponent calculation     |
    \******************************/

    int exponent = 0;

    while(ourNumber >= 1)
    {
        ourNumber = ourNumber / 2;
        exponent++;
    }

    while(ourNumber < 0.5)
    {
        ourNumber = ourNumber * 2;
        exponent--;
    }

    float mantisse = ourNumber;



    int converterNumber = 4096;
    for( int i = 1; i <= 13; i++ )
    {
        if (converterNumber <= exponent)
        {
            exponent = exponent - converterNumber;
            x[i] = true;   //(1)
        }
        else
        {
            x[i] = false; //(0)
        }

        converterNumber = converterNumber / 2;
    }

    // TODO ajout de d et nombre negatif

    /******************************\
    |     Mantisse calculation     |
    \******************************/

    // x[14] -> x[99]

    mantisse = mantisse - 0.5; // car c'est normalise

    float j = 0.25;
    for(int i = 14; i <= 99; i++)
    {
        //cout << "mantisse : " << mantisse << endl;
        if (mantisse >= j)
        {
            mantisse = mantisse - j;
            x[i] = true; // 1
        }
        else
        {
            x[i] = false; // 0
        }
        j = j / 2;
        //cout << i - 13 << "." << x[i] << endl;
    }

    printFloating(x, 0, 0);
    cout << "| 2^" ;
    printFloating(x, 1, 13);
    cout << " * " ;
    printFloatingMantissa(x, 14, 99);

    return 0;

}
