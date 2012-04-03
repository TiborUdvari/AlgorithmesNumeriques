//
//  VectorND.h
//  Matrix
//
//  Created by Laurent Novac on 03.04.12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Matrix_VectorND_h
#define Matrix_VectorND_h
#include <iostream>

class VectorND
{
public:
    VectorND();
    VectorND(int n_);
    int getDim() const;
    double* getArrayElements() const;
    void print() const;
    ~VectorND();
private:
    int dim;//N*1
    double* arrayElements;
    void fill();
};

#endif
