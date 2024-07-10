#ifndef ARRAYSTRUCTSPARSE_H
#define ARRAYSTRUCTSPARSE_H

#include "arraystruct.h"
#include <iostream>
#include <map>

template <typename T>
class ArrayStructSparse : public ArrayStruct<T>
{
    typedef int ArrayDim;
    #define ArrayDim_ int
public:
    ArrayStructSparse(ArrayDim Idx1Min_, ArrayDim Idx1Max_, ArrayDim Idx2Min_, ArrayDim Idx2Max_, ArrayDim Idx3Min_, ArrayDim Idx3Max_, T ValMin_, T ValMax_)
    {
        Idx1Min = Idx1Min_;
        Idx1Max = Idx1Max_;
        Idx2Min = Idx2Min_;
        Idx2Max = Idx2Max_;
        Idx3Min = Idx3Min_;
        Idx3Max = Idx3Max_;
        ValMin = ValMin_;
        ValMax = ValMax_;

        Dim2L = 0;
        if ((Idx1Max_ > 0) && (Dim2L < (Idx1Max_ + 1)))
        {
            Dim2L = (Idx1Max_ + 1);
        }
        if ((Idx1Min_ < 0) && (Dim2L < (0 - Idx1Min_ + 1)))
        {
            Dim2L = (0 - Idx1Min_ + 1);
        }

        Dim3L = 0;
        if ((Idx2Max_ > 0) && (Dim3L < (Idx2Max_ + 1)))
        {
            Dim3L = (Idx2Max_ + 1);
        }
        if ((Idx2Min_ < 0) && (Dim3L < (0 - Idx2Min_ + 1)))
        {
            Dim3L = (0 - Idx2Min_ + 1);
        }
        Dim3L = Dim3L * Dim2L;

    }

    ~ArrayStructSparse()
    {

    }

    void Set(ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, unsigned char Mode, T Val)
    {
        if ((Idx1 >= Idx1Min) && (Idx1 <= Idx1Max))
        {
            if ((Idx2 >= Idx2Min) && (Idx2 <= Idx2Max))
            {
                if ((Idx3 >= Idx3Min) && (Idx3 <= Idx3Max))
                {
                    ArrayDim Idx = Idx1 + (Idx2 * Dim2L) + (Idx3 * Dim3L);

                    DataI = Data.find(Idx);
                    if (Mode > 0)
                    {
                        if (DataI != Data.end())
                        {
                            switch (Mode)
                            {
                                case 1: DataI->second += Val; break;
                                case 2: DataI->second -= Val; break;
                                case 3: DataI->second *= Val; break;
                                case 4: if (Val != 0) { DataI->second /= Val; } else { if (DataI->second != 0) { DataI->second = ((DataI->second >= 0) ? ValMax : ValMin); } } break;
                            }
                            if (DataI->second == 0)
                            {
                                Data.erase(DataI);
                            }
                        }
                        else
                        {
                            if (Val != 0)
                            {
                                switch (Mode)
                                {
                                    case 1: Data.insert(Data.begin(), std::pair<ArrayDim, T>(Idx, Val)); break;
                                    case 2: Data.insert(Data.begin(), std::pair<ArrayDim, T>(Idx, 0 - Val)); break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (DataI != Data.end())
                        {
                            if (Val != 0)
                            {
                                DataI->second = Val;
                            }
                            else
                            {
                                Data.erase(DataI);
                            }
                        }
                        else
                        {
                            if (Val != 0)
                            {
                                Data.insert(Data.begin(), std::pair<ArrayDim, T>(Idx, Val));
                            }
                        }
                    }
                }
            }
        }
    }

    T Get(ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3)
    {
        DataI = Data.find(Idx1 + (Idx2 * Dim2L) + (Idx3 * Dim3L));
        if (DataI != Data.end())
        {
            return DataI->second;
        }
        else
        {
            return 0;
        }
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

    std::map<ArrayDim_, T> Data;
    typename std::map<ArrayDim_, T>::iterator DataI;
    ArrayDim Dim2L;
    ArrayDim Dim3L;
};

#endif // ARRAYSTRUCTSPARSE_H
