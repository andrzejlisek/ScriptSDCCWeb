#ifndef ARRAYHANDLE_H
#define ARRAYHANDLE_H

#include "valuetypes.h"
#include <iostream>
#include "arraystructsparse.h"
#include "arraystructdense.h"
#include <string>
#include <sstream>
#include <cmath>

class ArrayHandle
{
    #define TypeS1 schar
    #define TypeU1 uchar
    #define TypeS2 short
    #define TypeU2 ushort
    #define TypeS4 int
    #define TypeU4 uint
    #define TypeFL float
    #define ArrayHandleCount 256
    typedef int ArrayDim;
public:
    ArrayHandle();
    ~ArrayHandle();
    void ArrayCreate(uchar Handle, char TypeDim, ArrayDim Idx1Min_, ArrayDim Idx1Max_, ArrayDim Idx2Min_, ArrayDim Idx2Max_, ArrayDim Idx3Min_, ArrayDim Idx3Max_);
    void ArrayDelete(uchar Handle);
    void ArraySetS1(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeS1 Val, char Mode);
    void ArraySetU1(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeU1 Val, char Mode);
    void ArraySetS2(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeS2 Val, char Mode);
    void ArraySetU2(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeU2 Val, char Mode);
    void ArraySetS4(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeS4 Val, char Mode);
    void ArraySetU4(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeU4 Val, char Mode);
    void ArraySetFL(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeFL Val, char Mode);
    TypeS1 ArrayGetS1(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3);
    TypeU1 ArrayGetU1(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3);
    TypeS2 ArrayGetS2(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3);
    TypeU2 ArrayGetU2(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3);
    TypeS4 ArrayGetS4(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3);
    TypeU4 ArrayGetU4(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3);
    TypeFL ArrayGetFL(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3);
    std::string Info();
private:
    ArrayStruct<TypeS1> * ArrayS1[ArrayHandleCount];
    ArrayStruct<TypeU1> * ArrayU1[ArrayHandleCount];
    ArrayStruct<TypeS2> * ArrayS2[ArrayHandleCount];
    ArrayStruct<TypeU2> * ArrayU2[ArrayHandleCount];
    ArrayStruct<TypeS4> * ArrayS4[ArrayHandleCount];
    ArrayStruct<TypeU4> * ArrayU4[ArrayHandleCount];
    ArrayStruct<TypeFL> * ArrayFL[ArrayHandleCount];
    std::string ArrayInfo[ArrayHandleCount];
};

#endif // ARRAYHANDLE_H
