
/*
#include <iostream>
#include "BigIntegerLibrary.hh"

using namespace std;

BigInteger pow(int puissance, int base = 10)
{
    //if(puissance == 0) return 1;
    BigInteger val = BigInteger(1);
    for(int i=1 ; i <= puissance; i++)
    {
        val = val * base;
    }
    return val;
}

void printFloating(bool x[], int startingBit, int endingBit)
{
    int j = 1;
    BigInteger valeur = 0;
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
    BigInteger j = 1;
    BigInteger valeur = 0;
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
    //cout.precision(15);
    cout << valeur;

    //cout<<std::fixed<< valeur <<endl;
    //std::cout << " " << valeur;
}

bool __inline is_integer(float f){
    int i = f;
    return (f == static_cast<float>(i));
}

int main()
{
    float inputF = 1.8;
    bool x[100];
    int normalisationMultiplier = 0;
    /******************************\
    |       Sign calculation       |
    \******************************

    x[0] = ( inputF < 0 ) ? 1 : 0;
    cout << "x[0] est " << x[0] << endl;
    /******************************\
    |       Get Rid of float       |
    \******************************

    while(!is_integer(inputF))
    {
        inputF = inputF * 10;
        normalisationMultiplier++;
    }

    //normalisationMultiplier++;
    //cout << "normalisationMultiplier est " << normalisationMultiplier << endl;
    BigInteger input = (unsigned long int) inputF;
    //cout << "input est " << input << endl;
    /******************************\
    |     Exponent calculation     |
    \******************************

    int exponent = 0;
    BigInteger leftLimit = BigInteger(5) * pow(normalisationMultiplier - 1, 10);
    BigInteger rightLimit = BigInteger(1) * pow(normalisationMultiplier, 10);
    //cout << "right limit : " << rightLimit << endl;
    //cout << endl <<"This should be 5 : " << BigInteger(5) * pow(normalisationMultiplier - 1, 10)  << endl;

    //BigInteger leftLimit = BigInteger(5) * pow(normalisationMultiplier, 10) / BigInteger(10);
    //BigInteger rightLimit = pow(normalisationMultiplier, 10);

    while(input >= rightLimit)
    {
        input = input / 2;
        exponent++;
    }

    while(input < leftLimit)
    {
        input = input * 2;
        exponent--;
    }

    cout << endl<<endl<<"input is " << input << endl;

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
    \******************************

    // x[14] -> x[99]

/**** PROBLEME PAR ICI ****

    //input = input - BigInteger(5) * pow(normalisationMultiplier, 10) / BigInteger(10); // car c'est normalise

    input = input - leftLimit;

    //BigInteger j = BigInteger(25) * pow(normalisationMultiplier, 10) / BigInteger(100);
    //cout << "j is "<< j<< endl;

    BigInteger j = BigInteger(25) * pow(normalisationMultiplier -1 , 10);

    input = input * pow(normalisationMultiplier, 10);

    for(int i = 14; i <= 99; i++)
    {
        j = j * 10;
        input = input * 10;
        //cout << "Is " << j << " in " << input << "?" << endl;

        //cout << "mantisse : " << mantisse << endl;
        if (input >= j)
        {
            input = input - j;
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


    cout << "This is the binary result : " << endl;
    for(int i=0; i < 100; i++)
    {
        if(i==14)
        {
            cout<<"   ";
        }
        if(x[i])
        {
            cout<<"1";
        }
        else
        {
            cout<<"0";
        }
    }

    return 0;

}
*/
