#ifndef ARRAYSTRUCTDENSE_H
#define ARRAYSTRUCTDENSE_H

#include "arraystruct.h"
#include <iostream>

template <typename T>
class ArrayStructDense : public ArrayStruct<T>
{
    typedef int ArrayDim;
public:
    ArrayStructDense(ArrayDim Idx1Min_, ArrayDim Idx1Max_, ArrayDim Idx2Min_, ArrayDim Idx2Max_, ArrayDim Idx3Min_, ArrayDim Idx3Max_, T ValMin_, T ValMax_)
    {
        Idx1Min = Idx1Min_;
        Idx1Max = Idx1Max_;
        Idx2Min = Idx2Min_;
        Idx2Max = Idx2Max_;
        Idx3Min = Idx3Min_;
        Idx3Max = Idx3Max_;
        ValMin = ValMin_;
        ValMax = ValMax_;

        Dim2L = (Idx1Max_ - Idx1Min_ + 1);
        Dim3L = (Idx2Max_ - Idx2Min_ + 1) * Dim2L;
        ArrLen = (Idx1Max_ - Idx1Min_ + 1) * (Idx2Max_ - Idx2Min_ + 1) * (Idx3Max_ - Idx3Min_ + 1);

        Data = new T[ArrLen];
        for (ArrayDim I = 0; I < ArrLen; I++)
        {
            Data[I] = 0;
        }
    }

    ~ArrayStructDense()
    {
        delete[] Data;
    }

    void Set(ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, unsigned char Mode, T Val)
    {
        if ((Idx1 >= Idx1Min) && (Idx1 <= Idx1Max))
        {
            if ((Idx2 >= Idx2Min) && (Idx2 <= Idx2Max))
            {
                if ((Idx3 >= Idx3Min) && (Idx3 <= Idx3Max))
                {
                    ArrayDim Idx = (Idx1 - Idx1Min) + ((Idx2 - Idx2Min) * Dim2L) + ((Idx3 - Idx3Min) * Dim3L);
                    switch (Mode)
                    {
                        case 0: Data[Idx] = Val; break;
                        case 1: Data[Idx] += Val; break;
                        case 2: Data[Idx] -= Val; break;
                        case 3: Data[Idx] *= Val; break;
                        case 4: if (Val != 0) { Data[Idx] /= Val; } else { if (Data[Idx] != 0) { Data[Idx] = ((Data[Idx] >= 0) ? ValMax : ValMin); } } break;
                    }
                }
            }
        }
    }

    T Get(ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3)
    {
        if ((Idx1 >= Idx1Min) && (Idx1 <= Idx1Max))
        {
            if ((Idx2 >= Idx2Min) && (Idx2 <= Idx2Max))
            {
                if ((Idx3 >= Idx3Min) && (Idx3 <= Idx3Max))
                {
                    return Data[(Idx1 - Idx1Min) + ((Idx2 - Idx2Min) * Dim2L) + ((Idx3 - Idx3Min) * Dim3L)];
                }
            }
        }
        return 0;
    }

private:
    T ValMin;
    T ValMax;
    ArrayDim Idx1Min;
    ArrayDim Idx1Max;
    ArrayDim Idx2Min;
    ArrayDim Idx2Max;
    ArrayDim Idx3Min;
    ArrayDim Idx3Max;

    T * Data;
    ArrayDim Dim2L;
    ArrayDim Dim3L;
    ArrayDim ArrLen;
};

#endif // ARRAYSTRUCTDENSE_H
