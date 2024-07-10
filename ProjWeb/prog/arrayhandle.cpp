#include "arrayhandle.h"

ArrayHandle::ArrayHandle()
{
    for (int I = 0; I < ArrayHandleCount; I++)
    {
        ArrayS1[I] = NULL;
        ArrayU1[I] = NULL;
        ArrayS2[I] = NULL;
        ArrayU2[I] = NULL;
        ArrayS4[I] = NULL;
        ArrayU4[I] = NULL;
        ArrayFL[I] = NULL;
    }
    for (int I = 0; I < ArrayHandleCount; I++)
    {
        ArrayDelete(I);
    }
}

ArrayHandle::~ArrayHandle()
{
    for (int I = 0; I < ArrayHandleCount; I++)
    {
        ArrayDelete(I);
    }
}

void ArrayHandle::ArrayCreate(uchar Handle, char TypeDim, ArrayDim Idx1Min_, ArrayDim Idx1Max_, ArrayDim Idx2Min_, ArrayDim Idx2Max_, ArrayDim Idx3Min_, ArrayDim Idx3Max_)
{
    ArrayDelete(Handle);
    if ((Idx1Max_ < Idx1Min_) || (Idx2Max_ < Idx2Min_) || (Idx3Max_ < Idx3Min_))
    {
        return;
    }
    std::string InfoDim = "[" + std::to_string(Idx1Min_) + ".." + std::to_string(Idx1Max_) + "," + std::to_string(Idx2Min_) + ".." + std::to_string(Idx2Max_) + "," + std::to_string(Idx3Min_) + ".." + std::to_string(Idx3Max_) + "]";
    if ((TypeDim > (-30)) && (TypeDim < 30))
    {
        Idx3Min_ = 0;
        Idx3Max_ = 0;
        InfoDim = "[" + std::to_string(Idx1Min_) + ".." + std::to_string(Idx1Max_) + "," + std::to_string(Idx2Min_) + ".." + std::to_string(Idx2Max_) + "]";
    }
    if ((TypeDim > (-20)) && (TypeDim < 20))
    {
        Idx2Min_ = 0;
        Idx2Max_ = 0;
        InfoDim = "[" + std::to_string(Idx1Min_) + ".." + std::to_string(Idx1Max_) + "]";
    }

    std::string InfoType = "";
    switch (TypeDim)
    {
        case -10:
        case -20:
        case -30:
            InfoType = "S1";
            ArrayS1[Handle] = new ArrayStructSparse<TypeS1>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, -128, 127);
            break;
        case -11:
        case -21:
        case -31:
            InfoType = "U1";
            ArrayU1[Handle] = new ArrayStructSparse<TypeU1>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, 0, 255);
            break;
        case -12:
        case -22:
        case -32:
            InfoType = "S2";
            ArrayS2[Handle] = new ArrayStructSparse<TypeS2>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, -32768, 32767);
            break;
        case -13:
        case -23:
        case -33:
            InfoType = "U2";
            ArrayU2[Handle] = new ArrayStructSparse<TypeU2>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, 0, 65535);
            break;
        case -14:
        case -24:
        case -34:
            InfoType = "S4";
            ArrayS4[Handle] = new ArrayStructSparse<TypeS4>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, -2147483648L, 2147483647L);
            break;
        case -15:
        case -25:
        case -35:
            InfoType = "U4";
            ArrayU4[Handle] = new ArrayStructSparse<TypeU4>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, 0, 4294967295UL);
            break;
        case -16:
        case -26:
        case -36:
            InfoType = "FL";
            ArrayFL[Handle] = new ArrayStructSparse<TypeFL>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, -INFINITY, INFINITY);
            break;
        case 10:
        case 20:
        case 30:
            InfoType = "S1";
            ArrayS1[Handle] = new ArrayStructDense<TypeS1>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, -128, 127);
            break;
        case 11:
        case 21:
        case 31:
            InfoType = "U1";
            ArrayU1[Handle] = new ArrayStructDense<TypeU1>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, 0, 255);
            break;
        case 12:
        case 22:
        case 32:
            InfoType = "S2";
            ArrayS2[Handle] = new ArrayStructDense<TypeS2>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, -32768, 32767);
            break;
        case 13:
        case 23:
        case 33:
            InfoType = "U2";
            ArrayU2[Handle] = new ArrayStructDense<TypeU2>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, 0, 65535);
            break;
        case 14:
        case 24:
        case 34:
            InfoType = "S4";
            ArrayS4[Handle] = new ArrayStructDense<TypeS4>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, -2147483648L, 2147483647L);
            break;
        case 15:
        case 25:
        case 35:
            InfoType = "U4";
            ArrayU4[Handle] = new ArrayStructDense<TypeU4>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, 0, 4294967295UL);
            break;
        case 16:
        case 26:
        case 36:
            InfoType = "FL";
            ArrayFL[Handle] = new ArrayStructDense<TypeFL>(Idx1Min_, Idx1Max_, Idx2Min_, Idx2Max_, Idx3Min_, Idx3Max_, -INFINITY, INFINITY);
            break;
        default:
            InfoDim = "";
    }
    if (InfoDim != "")
    {
        ArrayInfo[Handle] = "Array " + std::to_string((int)Handle);
        if (TypeDim > 0)
        {
            ArrayInfo[Handle] = ArrayInfo[Handle] + " (dense)";
        }
        else
        {
            ArrayInfo[Handle] = ArrayInfo[Handle] + " (sparse)";
        }
        ArrayInfo[Handle] = ArrayInfo[Handle] + ": " + InfoType + InfoDim;
    }
}

void ArrayHandle::ArrayDelete(uchar Handle)
{
    ArrayInfo[Handle] = "";
    if (ArrayS1[Handle] != NULL)
    {
        delete ArrayS1[Handle];
        ArrayS1[Handle] = NULL;
    }
    if (ArrayU1[Handle] != NULL)
    {
        delete ArrayU1[Handle];
        ArrayU1[Handle] = NULL;
    }
    if (ArrayS2[Handle] != NULL)
    {
        delete ArrayS2[Handle];
        ArrayS2[Handle] = NULL;
    }
    if (ArrayU2[Handle] != NULL)
    {
        delete ArrayU2[Handle];
        ArrayU2[Handle] = NULL;
    }
    if (ArrayS4[Handle] != NULL)
    {
        delete ArrayS4[Handle];
        ArrayS4[Handle] = NULL;
    }
    if (ArrayU4[Handle] != NULL)
    {
        delete ArrayU4[Handle];
        ArrayU4[Handle] = NULL;
    }
    if (ArrayFL[Handle] != NULL)
    {
        delete ArrayFL[Handle];
        ArrayFL[Handle] = NULL;
    }
}

void ArrayHandle::ArraySetS1(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeS1 Val, char Mode)
{
    if (ArrayS1[Handle] != NULL)
    {
        ArrayS1[Handle]->Set(Idx1, Idx2, Idx3, Mode, Val);
    }
}

void ArrayHandle::ArraySetU1(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeU1 Val, char Mode)
{
    if (ArrayU1[Handle] != NULL)
    {
        ArrayU1[Handle]->Set(Idx1, Idx2, Idx3, Mode, Val);
    }
}

void ArrayHandle::ArraySetS2(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeS2 Val, char Mode)
{
    if (ArrayS2[Handle] != NULL)
    {
        ArrayS2[Handle]->Set(Idx1, Idx2, Idx3, Mode, Val);
    }
}

void ArrayHandle::ArraySetU2(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeU2 Val, char Mode)
{
    if (ArrayU2[Handle] != NULL)
    {
        ArrayU2[Handle]->Set(Idx1, Idx2, Idx3, Mode, Val);
    }
}

void ArrayHandle::ArraySetS4(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeS4 Val, char Mode)
{
    if (ArrayS4[Handle] != NULL)
    {
        ArrayS4[Handle]->Set(Idx1, Idx2, Idx3, Mode, Val);
    }
}

void ArrayHandle::ArraySetU4(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeU4 Val, char Mode)
{
    if (ArrayU4[Handle] != NULL)
    {
        ArrayU4[Handle]->Set(Idx1, Idx2, Idx3, Mode, Val);
    }
}

void ArrayHandle::ArraySetFL(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3, TypeFL Val, char Mode)
{
    if (ArrayFL[Handle] != NULL)
    {
        ArrayFL[Handle]->Set(Idx1, Idx2, Idx3, Mode, Val);
    }
}

TypeS1 ArrayHandle::ArrayGetS1(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3)
{
    TypeS1 Val = 0;
    if (ArrayS1[Handle] != NULL)
    {
        Val = ArrayS1[Handle]->Get(Idx1, Idx2, Idx3);
    }
    return Val;
}

TypeU1 ArrayHandle::ArrayGetU1(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3)
{
    TypeU1 Val = 0;
    if (ArrayU1[Handle] != NULL)
    {
        Val = ArrayU1[Handle]->Get(Idx1, Idx2, Idx3);
    }
    return Val;
}

TypeS2 ArrayHandle::ArrayGetS2(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3)
{
    TypeS2 Val = 0;
    if (ArrayS2[Handle] != NULL)
    {
        Val = ArrayS2[Handle]->Get(Idx1, Idx2, Idx3);
    }
    return Val;
}

TypeU2 ArrayHandle::ArrayGetU2(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3)
{
    TypeU2 Val = 0;
    if (ArrayU2[Handle] != NULL)
    {
        Val = ArrayU2[Handle]->Get(Idx1, Idx2, Idx3);
    }
    return Val;
}

TypeS4 ArrayHandle::ArrayGetS4(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3)
{
    TypeS4 Val = 0;
    if (ArrayS4[Handle] != NULL)
    {
        Val = ArrayS4[Handle]->Get(Idx1, Idx2, Idx3);
    }
    return Val;
}

TypeU4 ArrayHandle::ArrayGetU4(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3)
{
    TypeU4 Val = 0;
    if (ArrayU4[Handle] != NULL)
    {
        Val = ArrayU4[Handle]->Get(Idx1, Idx2, Idx3);
    }
    return Val;
}

TypeFL ArrayHandle::ArrayGetFL(uchar Handle, ArrayDim Idx1, ArrayDim Idx2, ArrayDim Idx3)
{
    TypeFL Val = 0;
    if (ArrayFL[Handle] != NULL)
    {
        Val = ArrayFL[Handle]->Get(Idx1, Idx2, Idx3);
    }
    return Val;
}

std::string ArrayHandle::Info()
{
    std::stringstream Info;
    for (int I = 0; I < ArrayHandleCount; I++)
    {
        if (ArrayInfo[I] != "")
        {
            Info << ArrayInfo[I] << std::endl;
        }
    }
    return Info.str();
}
