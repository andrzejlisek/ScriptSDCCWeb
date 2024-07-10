#ifndef VALUETYPES_H
#define VALUETYPES_H

#include <string>
#include <sstream>

#define Range(X, A, B) (((X) < (A)) ? (A) : (((X) > (B)) ? (B) : (X)))
#define RangeMod(V, A, B, M) { while (V <= (A)) { V += (M); } while (V > (B)) { V -= (M); } }

typedef signed char sbyte1;
typedef signed short sbyte2;
typedef signed int sbyte4;

typedef unsigned char ubyte1;
typedef unsigned short ubyte2;
typedef unsigned int ubyte4;

typedef int arrayidx;

typedef signed char schar;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long llong;
typedef unsigned long long ullong;
typedef unsigned short ushort;
typedef long double ldouble;

union TypeConv
{
    uchar Raw[8];
    sbyte1 S1;
    ubyte1 U1;
    sbyte2 S2;
    ubyte2 U2;
    sbyte4 S4;
    ubyte4 U4;
    float Flt;
    double Dbl;
};

extern int ValueStrToInt(std::string S);
extern long ValueStrToLong(std::string S);
extern llong ValueStrToLLong(std::string S);
extern float ValueStrToFloat(std::string S);
extern double ValueStrToDouble(std::string S);

#endif // VALUETYPES_H

#ifdef ValueTypesImplementation

#include <clocale>

void ValueConversionPrepare()
{
    std::setlocale(LC_NUMERIC,"C");
}

std::string ValueStrToNumPrepare(std::string S, bool Decimal)
{
    // Filtering characters
    std::string SS;
    int FilterState = 0;
    int FilterComma = 0;
    int FilterDot = 0;
    int FilterPoint = 0;
    int FilterLast = 0;
    bool NumNegative = false;
    for (int I = 0; I < S.length(); I++)
    {
        switch(S[I])
        {
            case '.':
                if ((FilterState == 0) || (FilterState == 2))
                {
                    SS.push_back('0');
                    FilterState = 1;
                }
                if (FilterState == 1)
                {
                    FilterPoint = SS.size();
                    FilterLast = 1;
                    FilterDot++;
                    SS.push_back('.');
                }
                break;
            case ',':
                if ((FilterState == 0) || (FilterState == 2))
                {
                    SS.push_back('0');
                    FilterState = 1;
                }
                if (FilterState == 1)
                {
                    FilterPoint = SS.size();
                    FilterLast = 2;
                    FilterComma++;
                    SS.push_back(',');
                }
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                FilterState = 1;
                SS.push_back(S[I]);
                break;
            case '+':
                FilterState = 2;
                break;
            case '-':
                if (FilterState == 0)
                {
                    NumNegative = true;
                }
                FilterState = 2;
                break;
        }
    }

    // Eliminate decimal point finishing the number
    while ((SS.size() > 0) && ((SS[SS.size() - 1] == ',') || (SS[SS.size() - 1] == '.')))
    {
        SS.pop_back();
    }

    // Prepare decimal separator
    S = "";
    for (int I = 0; I < SS.length(); I++)
    {
        switch(SS[I])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                S.push_back(SS[I]);
                break;
            case ',':
                if ((I == FilterPoint) && (FilterComma == 1))
                {
                    if (Decimal)
                    {
                        S.push_back('.');
                    }
                    else
                    {
                        I = SS.length();
                    }
                }
                break;
            case '.':
                if ((I == FilterPoint) && (FilterDot == 1))
                {
                    if (Decimal)
                    {
                        S.push_back('.');
                    }
                    else
                    {
                        I = SS.length();
                    }
                }
                break;
        }
    }

    // Remove leading zeros
    while ((S.size() > 1) && (S[0] == '0') && (S[1] != '.'))
    {
        S = S.substr(1);
    }

    // Return zero if filterred string contains no digits other than zero
    if (S == "") return "0";

    if (NumNegative && (S != "0"))
    {
        return "-" + S;
    }
    else
    {
        return S;
    }
}

int ValueStrToInt(std::string S)
{
    S = ValueStrToNumPrepare(S, false);
    return std::stoi(S);
}

long ValueStrToLong(std::string S)
{
    S = ValueStrToNumPrepare(S, false);
    return std::stol(S);
}

llong ValueStrToLLong(std::string S)
{
    S = ValueStrToNumPrepare(S, false);
    return std::stoll(S);
}

float ValueStrToFloat(std::string S)
{
    S = ValueStrToNumPrepare(S, true);
    return std::stof(S);
}

double ValueStrToDouble(std::string S)
{
    S = ValueStrToNumPrepare(S, true);
    return std::stod(S);
}

#undef ValueTypesImplementation
#endif
