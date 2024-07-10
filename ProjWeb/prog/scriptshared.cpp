#include "scriptshared.h"

ScriptShared::ScriptShared()
{

}

void ScriptShared::SwapCreate()
{
    SwapData = new uchar[256];
    SwapOffset = 0;
}

void ScriptShared::SwapDestroy()
{
    delete[] SwapData;
}

std::string ScriptShared::SwapExport()
{
    std::stringstream S;
    if (SwapExportLength > 0)
    {
        for (int I = 0; I < SwapExportLength; I++)
        {
            S << Hex::IntToHex8(SwapData[SwapOffset + I]);
        }
    }
    else
    {
        for (int I = 0; I < (0 - SwapExportLength); I++)
        {
            S << Hex::IntToHex8(SwapData[SwapOffset + I]);
        }
        S << "|" << Hex::StringEncode(TextBuff.str());
    }
    return S.str();
}

void ScriptShared::SwapImport(std::string SwapStr)
{
    int L = SwapStr.size() / 2;
    for (int I = 0; I < L; I++)
    {
        if (SwapStr[I << 1] == '|')
        {
            TextBufClear();
            TextBuff << Hex::StringDecode(SwapStr.substr((I << 1) + 1));
            return;
        }
        SwapData[SwapOffset + I] = Hex::HexToInt(SwapStr.substr(I << 1, 2));
    }
}

schar ScriptShared::SwapGetSC(int Addr)
{
    TypeConv_.Raw[0] = SwapData[SwapOffset + Addr + 0];
    return TypeConv_.S1;
}

void ScriptShared::SwapSetSC(int Addr, schar Val)
{
    TypeConv_.S1 = Val;
    SwapData[SwapOffset + Addr + 0] = TypeConv_.Raw[0];
}

uchar ScriptShared::SwapGetUC(int Addr)
{
    TypeConv_.Raw[0] = SwapData[SwapOffset + Addr + 0];
    return TypeConv_.U1;
}

void ScriptShared::SwapSetUC(int Addr, uchar Val)
{
    TypeConv_.U1 = Val;
    SwapData[SwapOffset + Addr + 0] = TypeConv_.Raw[0];
}

short ScriptShared::SwapGetSS(int Addr)
{
    TypeConv_.Raw[0] = SwapData[SwapOffset + Addr + 0];
    TypeConv_.Raw[1] = SwapData[SwapOffset + Addr + 1];
    return TypeConv_.S2;
}

void ScriptShared::SwapSetSS(int Addr, short Val)
{
    TypeConv_.S2 = Val;
    SwapData[SwapOffset + Addr + 0] = TypeConv_.Raw[0];
    SwapData[SwapOffset + Addr + 1] = TypeConv_.Raw[1];
}

ushort ScriptShared::SwapGetUS(int Addr)
{
    TypeConv_.Raw[0] = SwapData[SwapOffset + Addr + 0];
    TypeConv_.Raw[1] = SwapData[SwapOffset + Addr + 1];
    return TypeConv_.U2;
}

void ScriptShared::SwapSetUS(int Addr, ushort Val)
{
    TypeConv_.U2 = Val;
    SwapData[SwapOffset + Addr + 0] = TypeConv_.Raw[0];
    SwapData[SwapOffset + Addr + 1] = TypeConv_.Raw[1];
}

int ScriptShared::SwapGetSI(int Addr)
{
    TypeConv_.Raw[0] = SwapData[SwapOffset + Addr + 0];
    TypeConv_.Raw[1] = SwapData[SwapOffset + Addr + 1];
    return TypeConv_.S2;
}

void ScriptShared::SwapSetSI(int Addr, int Val)
{
    TypeConv_.S2 = Val;
    SwapData[SwapOffset + Addr + 0] = TypeConv_.Raw[0];
    SwapData[SwapOffset + Addr + 1] = TypeConv_.Raw[1];
}

uint ScriptShared::SwapGetUI(int Addr)
{
    TypeConv_.Raw[0] = SwapData[SwapOffset + Addr + 0];
    TypeConv_.Raw[1] = SwapData[SwapOffset + Addr + 1];
    return TypeConv_.U2;
}

std::string ScriptShared::SwapGetStr(uchar NumType, int Addr)
{
    switch (NumType)
    {
        case 0: return std::to_string((int)SwapGetSC(Addr));
        case 1: return std::to_string((int)SwapGetUC(Addr));
        case 2: return std::string(1, SwapGetSC(Addr));
        case 3: return std::string(1, SwapGetUC(Addr));
        case 4: return std::to_string(SwapGetSS(Addr));
        case 5: return std::to_string(SwapGetUS(Addr));
        case 6: return std::to_string(SwapGetSI(Addr));
        case 7: return std::to_string(SwapGetUI(Addr));
        case 8: return std::to_string(SwapGetSL(Addr));
        case 9: return std::to_string(SwapGetUL(Addr));
        case 10:
            {
                bool NumNegative = false;
                float Num = SwapGetF(Addr);
                if (Num < 0)
                {
                    NumNegative = true;
                    Num = 0 - Num;
                }
                float NumX = Num;
                int Decimals = 10;
                while ((NumX < 1) && (NumX > 0))
                {
                    NumX = NumX * 10;
                    Decimals++;
                }
                std::stringstream Buf;
                Buf << std::fixed << std::setprecision(Decimals) << std::noshowpoint << Num;
                if (NumNegative)
                {
                    return "-" + FloatingPointCorrect(Buf.str(), 7);
                }
                else
                {
                    return FloatingPointCorrect(Buf.str(), 7);
                }
            }
        case 11: return TextBuff.str();
    }
    return "";
}

void ScriptShared::SwapSetUI(int Addr, uint Val)
{
    TypeConv_.U2 = Val;
    SwapData[SwapOffset + Addr + 0] = TypeConv_.Raw[0];
    SwapData[SwapOffset + Addr + 1] = TypeConv_.Raw[1];
}

long ScriptShared::SwapGetSL(int Addr)
{
    TypeConv_.Raw[0] = SwapData[SwapOffset + Addr + 0];
    TypeConv_.Raw[1] = SwapData[SwapOffset + Addr + 1];
    TypeConv_.Raw[2] = SwapData[SwapOffset + Addr + 2];
    TypeConv_.Raw[3] = SwapData[SwapOffset + Addr + 3];
    TypeConv_.Raw[4] = SwapData[SwapOffset + Addr + 4];
    TypeConv_.Raw[5] = SwapData[SwapOffset + Addr + 5];
    TypeConv_.Raw[6] = SwapData[SwapOffset + Addr + 6];
    TypeConv_.Raw[7] = SwapData[SwapOffset + Addr + 7];
    return TypeConv_.S4;
}

void ScriptShared::SwapSetSL(int Addr, long Val)
{
    TypeConv_.S4 = Val;
    SwapData[SwapOffset + Addr + 0] = TypeConv_.Raw[0];
    SwapData[SwapOffset + Addr + 1] = TypeConv_.Raw[1];
    SwapData[SwapOffset + Addr + 2] = TypeConv_.Raw[2];
    SwapData[SwapOffset + Addr + 3] = TypeConv_.Raw[3];
    SwapData[SwapOffset + Addr + 4] = TypeConv_.Raw[4];
    SwapData[SwapOffset + Addr + 5] = TypeConv_.Raw[5];
    SwapData[SwapOffset + Addr + 6] = TypeConv_.Raw[6];
    SwapData[SwapOffset + Addr + 7] = TypeConv_.Raw[7];
}

ulong ScriptShared::SwapGetUL(int Addr)
{
    TypeConv_.Raw[0] = SwapData[SwapOffset + Addr + 0];
    TypeConv_.Raw[1] = SwapData[SwapOffset + Addr + 1];
    TypeConv_.Raw[2] = SwapData[SwapOffset + Addr + 2];
    TypeConv_.Raw[3] = SwapData[SwapOffset + Addr + 3];
    TypeConv_.Raw[4] = SwapData[SwapOffset + Addr + 4];
    TypeConv_.Raw[5] = SwapData[SwapOffset + Addr + 5];
    TypeConv_.Raw[6] = SwapData[SwapOffset + Addr + 6];
    TypeConv_.Raw[7] = SwapData[SwapOffset + Addr + 7];
    return TypeConv_.U4;
}

void ScriptShared::SwapSetUL(int Addr, ulong Val)
{
    TypeConv_.U4 = Val;
    SwapData[SwapOffset + Addr + 0] = TypeConv_.Raw[0];
    SwapData[SwapOffset + Addr + 1] = TypeConv_.Raw[1];
    SwapData[SwapOffset + Addr + 2] = TypeConv_.Raw[2];
    SwapData[SwapOffset + Addr + 3] = TypeConv_.Raw[3];
    SwapData[SwapOffset + Addr + 4] = TypeConv_.Raw[4];
    SwapData[SwapOffset + Addr + 5] = TypeConv_.Raw[5];
    SwapData[SwapOffset + Addr + 6] = TypeConv_.Raw[6];
    SwapData[SwapOffset + Addr + 7] = TypeConv_.Raw[7];
}

float ScriptShared::SwapGetF(int Addr)
{
    TypeConv_.Raw[0] = SwapData[SwapOffset + Addr + 0];
    TypeConv_.Raw[1] = SwapData[SwapOffset + Addr + 1];
    TypeConv_.Raw[2] = SwapData[SwapOffset + Addr + 2];
    TypeConv_.Raw[3] = SwapData[SwapOffset + Addr + 3];
    TypeConv_.Raw[4] = SwapData[SwapOffset + Addr + 4];
    TypeConv_.Raw[5] = SwapData[SwapOffset + Addr + 5];
    TypeConv_.Raw[6] = SwapData[SwapOffset + Addr + 6];
    TypeConv_.Raw[7] = SwapData[SwapOffset + Addr + 7];
    return TypeConv_.Flt;
}

void ScriptShared::SwapSetF(int Addr, float Val)
{
    TypeConv_.Flt = Val;
    SwapData[SwapOffset + Addr + 0] = TypeConv_.Raw[0];
    SwapData[SwapOffset + Addr + 1] = TypeConv_.Raw[1];
    SwapData[SwapOffset + Addr + 2] = TypeConv_.Raw[2];
    SwapData[SwapOffset + Addr + 3] = TypeConv_.Raw[3];
    SwapData[SwapOffset + Addr + 4] = TypeConv_.Raw[4];
    SwapData[SwapOffset + Addr + 5] = TypeConv_.Raw[5];
    SwapData[SwapOffset + Addr + 6] = TypeConv_.Raw[6];
    SwapData[SwapOffset + Addr + 7] = TypeConv_.Raw[7];
}

void ScriptShared::SwapSetStr(uchar NumType, int Addr, std::string Val)
{
    switch (NumType)
    {
        case 0: SwapSetSC(Addr, ValueStrToLong(Val)); return;
        case 1: SwapSetUC(Addr, ValueStrToLong(Val)); return;
        case 2: if (Val.length() > 0) { SwapSetSC(Addr, Val[0]); } else { SwapSetSC(Addr, 0); } return;
        case 3: if (Val.length() > 0) { SwapSetUC(Addr, Val[0]); } else { SwapSetUC(Addr, 0); } return;
        case 4: SwapSetSS(Addr, ValueStrToLong(Val)); return;
        case 5: SwapSetUS(Addr, ValueStrToLong(Val)); return;
        case 6: SwapSetSI(Addr, ValueStrToLong(Val)); return;
        case 7: SwapSetUI(Addr, ValueStrToLong(Val)); return;
        case 8: SwapSetSL(Addr, ValueStrToLong(Val)); return;
        case 9: SwapSetUL(Addr, ValueStrToLong(Val)); return;
        case 10: SwapSetF(Addr, ValueStrToFloat(Val)); return;
        case 11: TextBuff.str(std::string()); TextBuff << Val; return;
    }
}

// https://en.wikipedia.org/wiki/IEEE_754
// float Digits=7.22
// double Digits=15.95
// ldouble Digits=34.02
std::string ScriptShared::FloatingPointCorrect(std::string NumStr, int Digits)
{
    int I;
    int L = NumStr.size();
    int NPos1 = -1;
    int NPos2 = -1;
    int DecimalPos = -1;

    for (I = 0; I < L; I++)
    {
        switch (NumStr[I])
        {
            case '0':
                if (NPos1 >= 0)
                {
                    Digits--;
                    if ((Digits == 1) && (NPos2 < 0))
                    {
                        NPos2 = I;
                    }
                }
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (NPos1 >= 0)
                {
                    Digits--;
                    if ((Digits == 1) && (NPos2 < 0))
                    {
                        NPos2 = I;
                    }
                }
                else NPos1 = I;
                break;
            case '.':
                DecimalPos = I;
                break;
            default:
                return NumStr;
                break;
        }
    }

    if (NPos1 < 0) return "0";
    if (NPos2 < 0)
    {
        NPos2 = L - 1;
    }

    bool RoundUp = false;
    if ((NPos2 + 1) < L)
    {
        if (NumStr[NPos2 + 1] != '.')
        {
            if (NumStr[NPos2 + 1] >= '5')
            {
                RoundUp = true;
            }
        }
        else
        {
            if ((NPos2 + 2) < L)
            {
                if (NumStr[NPos2 + 2] >= '5')
                {
                    RoundUp = true;
                }
            }
        }
    }

    if (RoundUp)
    {
        bool AdditionalZero = false;
        NPos1--;
        if (NPos1 < 0)
        {
            AdditionalZero = true;
            NumStr = "0" + NumStr;
            NPos1++;
            NPos2++;
        }
        bool Carry = true;
        for (I = NPos2; I >= NPos1; I--)
        {
            if (NumStr[I] != '.')
            {
                if (Carry)
                {
                    if (NumStr[I] == '9')
                    {
                        NumStr[I] = '0';
                        Carry = true;
                    }
                    else
                    {
                        NumStr[I]++;
                        Carry = false;
                    }
                }
            }
        }

        if (AdditionalZero)
        {
            if (NumStr[0] == '0')
            {
                NumStr = NumStr.substr(1);
            }
        }
    }

    // Truncate garbage digits and fractional part
    if (NPos2 < DecimalPos)
    {
        while (NPos2 < DecimalPos)
        {
            NPos2++;
            NumStr[NPos2] = '0';
        }
        return NumStr.substr(0, DecimalPos);
    }

    // Truncate garbage digits
    if (NPos2 < (L - 1))
    {
        NumStr = NumStr.substr(0, NPos2 + 1);
    }

    // Truncate trailing zeros
    if (DecimalPos < NumStr.size())
    {
        I = NumStr.size() - 1;
        int I0 = I;
        while ((I > 1) && (NumStr[I] == '0'))
        {
            I--;
        }
        if (I < I0)
        {
            if (NumStr[I] == '.')
            {
                NumStr = NumStr.substr(0, I);
            }
            else
            {
                NumStr = NumStr.substr(0, I + 1);
            }
        }
    }

    return NumStr;
}

void ScriptShared::MemoSwapOperation()
{
    int N = SwapGetUC(1);
    switch (SwapGetUC(2))
    {
        case 0:
            MemoTypeThr = N;
            MemoTypeX = true;
            break;
        case 1:
            MemoTypeThr = N;
            MemoTypeX = false;
            break;
        case 2:
            MemoDataP[N].clear();
            MemoDataN[N].clear();
            break;
    }
}

bool ScriptShared::MemoIsShared()
{
    if (MemoTypeX)
    {
        if (SwapGetUC(1) > MemoTypeThr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (SwapGetUC(1) <= MemoTypeThr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

ubyte1 ScriptShared::MemoGet1(uchar N, arrayidx Idx)
{
    if (Idx >= 0)
    {
        if (MemoDataP[N].size() > Idx)
        {
            return MemoDataP[N][Idx];
        }
        else
        {
            return 0;
        }
    }
    else
    {
        Idx = 0 - Idx;
        if (MemoDataN[N].size() > Idx)
        {
            return MemoDataN[N][Idx];
        }
        else
        {
            return 0;
        }
    }
}

ubyte2 ScriptShared::MemoGet2(uchar N, arrayidx Idx)
{
    if (Idx >= 0)
    {
        Idx = Idx << 1;
        if (MemoDataP[N].size() > (Idx + 1))
        {
            ByteData.Raw[0] = MemoDataP[N][Idx + 0];
            ByteData.Raw[1] = MemoDataP[N][Idx + 1];
            return ByteData.U2;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        Idx = (0 - Idx) << 1;
        if (MemoDataN[N].size() > (Idx + 1))
        {
            ByteData.Raw[0] = MemoDataN[N][Idx + 0];
            ByteData.Raw[1] = MemoDataN[N][Idx + 1];
            return ByteData.U2;
        }
        else
        {
            return 0;
        }
    }
}

ubyte4 ScriptShared::MemoGet4(uchar N, arrayidx Idx)
{
    if (Idx >= 0)
    {
        Idx = Idx << 2;
        if (MemoDataP[N].size() > (Idx + 3))
        {
            ByteData.Raw[0] = MemoDataP[N][Idx + 0];
            ByteData.Raw[1] = MemoDataP[N][Idx + 1];
            ByteData.Raw[2] = MemoDataP[N][Idx + 2];
            ByteData.Raw[3] = MemoDataP[N][Idx + 3];
            return ByteData.U4;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        Idx = (0 - Idx) << 2;
        if (MemoDataN[N].size() > (Idx + 3))
        {
            ByteData.Raw[0] = MemoDataN[N][Idx + 0];
            ByteData.Raw[1] = MemoDataN[N][Idx + 1];
            ByteData.Raw[2] = MemoDataN[N][Idx + 2];
            ByteData.Raw[3] = MemoDataN[N][Idx + 3];
            return ByteData.U4;
        }
        else
        {
            return 0;
        }
    }
}

void ScriptShared::MemoSet1(uchar N, arrayidx Idx, ubyte1 Val)
{
    if (Idx >= 0)
    {
        if (MemoDataP[N].size() <= Idx)
        {
            MemoDataP[N].resize(Idx + 1);
        }
        MemoDataP[N][Idx] = Val;
    }
    else
    {
        Idx = 0 - Idx;
        if (MemoDataN[N].size() <= Idx)
        {
            MemoDataN[N].resize(Idx + 1);
        }
        MemoDataN[N][Idx] = Val;
    }
}

void ScriptShared::MemoSet2(uchar N, arrayidx Idx, ubyte2 Val)
{
    if (Idx >= 0)
    {
        Idx = Idx << 1;
        if (MemoDataP[N].size() <= (Idx + 1))
        {
            MemoDataP[N].resize(Idx + 2);
        }
        ByteData.U2 = Val;
        MemoDataP[N][Idx + 0] = ByteData.Raw[0];
        MemoDataP[N][Idx + 1] = ByteData.Raw[1];
    }
    else
    {
        Idx = (0 - Idx) << 1;
        if (MemoDataN[N].size() <= (Idx + 1))
        {
            MemoDataN[N].resize(Idx + 2);
        }
        ByteData.U2 = Val;
        MemoDataN[N][Idx + 0] = ByteData.Raw[0];
        MemoDataN[N][Idx + 1] = ByteData.Raw[1];
    }
}

void ScriptShared::MemoSet4(uchar N, arrayidx Idx, ubyte4 Val)
{
    if (Idx >= 0)
    {
        Idx = Idx << 2;
        if (MemoDataP[N].size() <= (Idx + 3))
        {
            MemoDataP[N].resize(Idx + 4);
        }
        ByteData.U4 = Val;
        MemoDataP[N][Idx + 0] = ByteData.Raw[0];
        MemoDataP[N][Idx + 1] = ByteData.Raw[1];
        MemoDataP[N][Idx + 2] = ByteData.Raw[2];
        MemoDataP[N][Idx + 3] = ByteData.Raw[3];
    }
    else
    {
        Idx = (0 - Idx) << 2;
        if (MemoDataN[N].size() <= (Idx + 3))
        {
            MemoDataN[N].resize(Idx + 4);
        }
        ByteData.U4 = Val;
        MemoDataN[N][Idx + 0] = ByteData.Raw[0];
        MemoDataN[N][Idx + 1] = ByteData.Raw[1];
        MemoDataN[N][Idx + 2] = ByteData.Raw[2];
        MemoDataN[N][Idx + 3] = ByteData.Raw[3];
    }
}

void ScriptShared::MemoSwapProcessGet()
{
    int MemoNum = SwapGetUC(1);
    int MemoTypeDims = SwapGetUC(2);
    int MemoDim = SwapGetSL(0x10);
    if (MemoDim < 0)
    {
        SwapSetUL(0x08, 0);
        SwapExportLength = 16;
        return;
    }

    switch (MemoTypeDims)
    {
        case 1: SwapSetUC(0x08, MemoGet1(MemoNum, MemoDim)); break;
        case 2: SwapSetUI(0x08, MemoGet2(MemoNum, MemoDim)); break;
        case 4: SwapSetUL(0x08, MemoGet4(MemoNum, MemoDim)); break;
    }

    SwapExportLength = 16;
}

void ScriptShared::MemoSwapProcessSet()
{
    int MemoNum = SwapGetUC(1);
    int MemoTypeDims = SwapGetUC(2);
    int MemoDim = SwapGetSL(0x10);
    if (MemoDim < 0)
    {
        return;
    }

    switch (MemoTypeDims)
    {
        case 1: MemoSet1(MemoNum, MemoDim, SwapGetUC(0x08)); break;
        case 2: MemoSet2(MemoNum, MemoDim, SwapGetUI(0x08)); break;
        case 4: MemoSet4(MemoNum, MemoDim, SwapGetUL(0x08)); break;
    }

    SwapExportLength = 1;
}

void ScriptShared::TextBufClear()
{
    TextBuff.str(std::string());
}

void ScriptShared::TextBufAppend(uchar Chr)
{
    TextBuff << Chr;
}

void ScriptShared::TextBufAppendStr(std::string Chr)
{
    TextBuff << Chr;
}

std::string ScriptShared::TextBufGetString()
{
    return TextBuffS;
}

uint ScriptShared::TextBufGetInit()
{
    TextBuffS = TextBuff.str();
    TextBuffI = 0;
    if (TextBuffS.size() < 65535)
    {
        return TextBuffS.size();
    }
    else
    {
        return 65535;
    }
}

uchar ScriptShared::TextBufGetChar()
{
    uchar Chr = 0;
    if (TextBuffI < TextBuffS.size())
    {
        Chr = TextBuffS[TextBuffI];
        TextBuffI++;
    }
    return Chr;
}
