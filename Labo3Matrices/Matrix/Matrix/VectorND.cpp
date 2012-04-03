//
//  VectorND.cpp
//  Matrix
//
//  Created by Laurent Novac on 03.04.12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "VectorND.h"

VectorND::VectorND()
{
    this->dim=10;
    this->arrayElements=new double[dim];
    fill();
}

VectorND::VectorND(int n_)
{
    this->dim=n_;
    this->arrayElements=new double[dim];
    fill();
}

void VectorND::fill()
{
    for (int i=1; i<=dim; i++)
    {
        if(i==1)
            arrayElements[i-1]=2;//TODO random
        else
            arrayElements[i-1]=0;
    }
}

int VectorND::getDim() const
{
    return dim;
}

double* VectorND::getArrayElements() const
{
    return arrayElements;
}

void VectorND::print() const
{
    for (int i=1; i<=dim; i++)
    {
        std::cout<<arrayElements[i-1]<<std::endl;
    }
}

VectorND::~VectorND()
{
    delete[] arrayElements;
}