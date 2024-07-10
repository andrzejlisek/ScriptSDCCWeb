#ifndef SCRIPTENGINEZ180_H
#define SCRIPTENGINEZ180_H

#include "scriptengine.h"
#include "scriptdecompilez180.h"

#define FlagsAsReg

#ifdef FlagsAsReg
    #define FlagCSet Reg_F = Reg_F | 0b00000001
    #define FlagNSet Reg_F = Reg_F | 0b00000010
    #define FlagPSet Reg_F = Reg_F | 0b00000100
    #define FlagHSet Reg_F = Reg_F | 0b00010000
    #define FlagZSet Reg_F = Reg_F | 0b01000000
    #define FlagSSet Reg_F = Reg_F | 0b10000000

    #define FlagCClr Reg_F = Reg_F & 0b11111110
    #define FlagNClr Reg_F = Reg_F & 0b11111101
    #define FlagPClr Reg_F = Reg_F & 0b11111011
    #define FlagHClr Reg_F = Reg_F & 0b11101111
    #define FlagZClr Reg_F = Reg_F & 0b10111111
    #define FlagSClr Reg_F = Reg_F & 0b01111111

    #define FlagCGet ((Reg_F & 0b00000001) > 0)
    #define FlagNGet ((Reg_F & 0b00000010) > 0)
    #define FlagPGet ((Reg_F & 0b00000100) > 0)
    #define FlagHGet ((Reg_F & 0b00010000) > 0)
    #define FlagZGet ((Reg_F & 0b01000000) > 0)
    #define FlagSGet ((Reg_F & 0b10000000) > 0)
#else
    #define FlagCSet Reg_F0 = 0b00000001
    #define FlagNSet Reg_F1 = 0b00000010
    #define FlagPSet Reg_F2 = 0b00000100
    #define FlagHSet Reg_F4 = 0b00010000
    #define FlagZSet Reg_F6 = 0b01000000
    #define FlagSSet Reg_F7 = 0b10000000

    #define FlagCClr Reg_F0 = 0
    #define FlagNClr Reg_F1 = 0
    #define FlagPClr Reg_F2 = 0
    #define FlagHClr Reg_F4 = 0
    #define FlagZClr Reg_F6 = 0
    #define FlagSClr Reg_F7 = 0

    #define FlagCGet Reg_F0
    #define FlagNGet Reg_F1
    #define FlagPGet Reg_F2
    #define FlagHGet Reg_F4
    #define FlagZGet Reg_F6
    #define FlagSGet Reg_F7

    #define Reg_F_Get (Reg_F0 | Reg_F1 | Reg_F2 | Reg_F4 | Reg_F6 | Reg_F7)

    #define Reg_F_Set(X) { \
        Reg_F0 = X & 0b00000001;  \
        Reg_F1 = X & 0b00000010;  \
        Reg_F2 = X & 0b00000100;  \
        Reg_F4 = X & 0b00010000;  \
        Reg_F6 = X & 0b01000000;  \
        Reg_F7 = X & 0b10000000;  \
    }
#endif

#define SetFlagsSZ(Val) if (Val & 0b10000000) { FlagSSet; } else { FlagSClr; } if (Val) { FlagZClr; } else { FlagZSet; }
#define SetFlagsSZ_(ValH, ValL) if (ValH & 0b10000000) { FlagSSet; } else { FlagSClr; } if (ValH || ValL) { FlagZClr; } else { FlagZSet; }
#define SetFlagsP0000(Val) { bool P = 1; if (Val & 0b10000000) { P = !P; } if (Val & 0b01000000) { P = !P; } if (Val & 0b00100000) { P = !P; } if (Val & 0b00010000) { P = !P; } if (Val & 0b00001000) { P = !P; } if (Val & 0b00000100) { P = !P; } if (Val & 0b00000010) { P = !P; } if (Val & 0b00000001) { P = !P; } if (P) { FlagPSet; } else { FlagPClr; } }
#define SetFlagsP(Val) { if (FlagPArray[Val]) { FlagPSet; } else { FlagPClr; } }

#define RegIdxD ((Arg1 < 128) ? (Reg_Idx + ((ushort)Arg1)) : (Reg_Idx + ((ushort)Arg1) - 256))

class ScriptEngineZ180 : public ScriptEngine
{
public:
    ScriptEngineZ180();
    ~ScriptEngineZ180();

    void DoCommand();
    void DoReset();
    std::string GetEntryPoints();
private:
    uchar FlagPArray[256] = {
        1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
        0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
        0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
        1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
        0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
        1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
        1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
        0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
        0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
        1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
        1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
        0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
        1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
        0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
        0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
        1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1
    };

    void DoCommandExtCB(uchar OpCode0);
    void DoCommandExt_D(uchar OpCode0);
    void DoCommandExtED(uchar OpCode0);

    uchar Reg_A, Reg_A_;
    uchar Reg_F, Reg_F_;
    uchar Reg_F7, Reg_F7_;
    uchar Reg_F6, Reg_F6_;
    uchar Reg_F4, Reg_F4_;
    uchar Reg_F2, Reg_F2_;
    uchar Reg_F1, Reg_F1_;
    uchar Reg_F0, Reg_F0_;

    uchar Reg_B, Reg_B_;
    uchar Reg_C, Reg_C_;
    uchar Reg_D, Reg_D_;
    uchar Reg_E, Reg_E_;
    uchar Reg_H, Reg_H_;
    uchar Reg_L, Reg_L_;

    ushort Reg_IX;
    ushort Reg_IY;
    ushort Reg_SP;
    ushort Reg_Idx;

    uchar Reg_I;
    uchar Reg_R;

    ushort Reg_PC;

    bool Reg_IFF1;
    bool Reg_IFF2;

    void DoCALL(bool Condition);
    void DoPUSH(uchar &ValH, uchar &ValL);
    void DoPOP(uchar &ValH, uchar &ValL);
    void DoRET(bool Condition);
    void DoRETI();
    void DoRST(int Addr);
    void DoJR(bool Condition);
    void DoADD1(uchar Val, bool Carry);
    void DoADD2_HL(int Val, bool Carry);
    void DoADD2_HL(int ValH, int ValL, bool Carry);
    void DoADD2_I_(int Val);
    void DoADD2_I_(int ValH, int ValL);
    void DoSUB1(uchar Val, bool Carry);
    void DoSUB2(int Val, bool Carry);
    void DoSUB2(int ValH, int ValL, bool Carry);
    void DoCP(uchar Val);
    void DoTST(uchar Val);
    void DoTST(uchar Val0, uchar Val);
    void DoAND(uchar Val);
    void DoXOR(uchar Val);
    void DoOR(uchar Val);
    void DoINC(uchar &Reg);
    void DoDEC(uchar &Reg);
    void DoRL(uchar &Reg, bool NoAcc);
    void DoRR(uchar &Reg, bool NoAcc);
    void DoRLC(uchar &Reg, bool NoAcc);
    void DoRRC(uchar &Reg, bool NoAcc);
    void DoSLA(uchar &Reg);
    void DoSRA(uchar &Reg);
    void DoSLL(uchar &Reg);
    void DoSRL(uchar &Reg);
    void DoJumpAbs(int Addr, bool Call);
    void DoJumpAbs(int AddrH, int AddrL, bool Call);
    void DoJumpRel(int Addr, bool Call);
    void DoIN(uchar AddrH, uchar AddrL, uchar &Reg, bool Flags);
    void DoOUT(uchar AddrH, uchar AddrL, uchar &Reg);
    void DoBlock1I();
    void DoBlock1D();
    void DoBlock1IR();
    void DoBlock1DR();
    void DoBlock2I();
    void DoBlock2D();
    void DoBlock2IR(bool CompareA);
    void DoBlock2DR(bool CompareA);
    void DoBlock_CP();
    void DoBlock_LD();
};

#endif // SCRIPTENGINEZ180_H
