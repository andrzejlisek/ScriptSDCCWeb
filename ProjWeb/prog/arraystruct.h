#ifndef ARRAYSTRUCT_H
#define ARRAYSTRUCT_H

#include <iostream>

template <typename T>
class ArrayStruct
{
    typedef int ArrayDim;
public:
    ArrayStruct()
    {

    }

    virtual ~ArrayStruct()
    {

    }

    virtual void Set(ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, unsigned char Mode, T Val) = 0;
    virtual T Get(ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3) = 0;
};

#endif // ARRAYSTRUCT_H
