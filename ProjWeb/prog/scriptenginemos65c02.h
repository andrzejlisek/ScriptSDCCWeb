#ifndef SCRIPTENGINE65C02_H
#define SCRIPTENGINE65C02_H

#include "scriptengine.h"
#include "scriptdecompilemos65c02.h"

// https://www.pagetable.com/c64ref/6502/?cpu=65c02s
// Rockwell R65C02 | WDC 65C02S

///#define AddrSetZeroPage(Val) MemSet(MemPrg(Reg_PC), Val);
///#define AddrGetZeroPage() MemGet(MemPrg(Reg_PC))

#undef MOS6502_FlagsAsReg

#ifdef MOS6502_FlagsAsReg
    #define MOS6502_FlagNSet Reg_F = Reg_F | 0b10000000
    #define MOS6502_FlagVSet Reg_F = Reg_F | 0b01000000
    #define MOS6502_FlagBSet Reg_F = Reg_F | 0b00010000
    #define MOS6502_FlagDSet Reg_F = Reg_F | 0b00001000
    #define MOS6502_FlagISet Reg_F = Reg_F | 0b00000100
    #define MOS6502_FlagZSet Reg_F = Reg_F | 0b00000010
    #define MOS6502_FlagCSet Reg_F = Reg_F | 0b00000001

    #define MOS6502_FlagNClr Reg_F = Reg_F & 0b01111111
    #define MOS6502_FlagVClr Reg_F = Reg_F & 0b10111111
    #define MOS6502_FlagBClr Reg_F = Reg_F & 0b11101111
    #define MOS6502_FlagDClr Reg_F = Reg_F & 0b11110111
    #define MOS6502_FlagIClr Reg_F = Reg_F & 0b11111011
    #define MOS6502_FlagZClr Reg_F = Reg_F & 0b11111101
    #define MOS6502_FlagCClr Reg_F = Reg_F & 0b11111110

    #define MOS6502_FlagNGet ((Reg_F & 0b10000000) > 0)
    #define MOS6502_FlagVGet ((Reg_F & 0b01000000) > 0)
    #define MOS6502_FlagBGet ((Reg_F & 0b00010000) > 0)
    #define MOS6502_FlagDGet ((Reg_F & 0b00001000) > 0)
    #define MOS6502_FlagIGet ((Reg_F & 0b00000100) > 0)
    #define MOS6502_FlagZGet ((Reg_F & 0b00000010) > 0)
    #define MOS6502_FlagCGet ((Reg_F & 0b00000001) > 0)
#else
    #define MOS6502_FlagNSet Reg_F_N = 0b10000000
    #define MOS6502_FlagVSet Reg_F_V = 0b01000000
    #define MOS6502_FlagBSet Reg_F_B = 0b00010000
    #define MOS6502_FlagDSet Reg_F_D = 0b00001000
    #define MOS6502_FlagISet Reg_F_I = 0b00000100
    #define MOS6502_FlagZSet Reg_F_Z = 0b00000010
    #define MOS6502_FlagCSet Reg_F_C = 0b00000001

    #define MOS6502_FlagNClr Reg_F_N = 0
    #define MOS6502_FlagVClr Reg_F_V = 0
    #define MOS6502_FlagBClr Reg_F_B = 0
    #define MOS6502_FlagDClr Reg_F_D = 0
    #define MOS6502_FlagIClr Reg_F_I = 0
    #define MOS6502_FlagZClr Reg_F_Z = 0
    #define MOS6502_FlagCClr Reg_F_C = 0

    #define MOS6502_FlagNGet Reg_F_N
    #define MOS6502_FlagVGet Reg_F_V
    #define MOS6502_FlagBGet Reg_F_B
    #define MOS6502_FlagDGet Reg_F_D
    #define MOS6502_FlagIGet Reg_F_I
    #define MOS6502_FlagZGet Reg_F_Z
    #define MOS6502_FlagCGet Reg_F_C

    #define Reg_F_Get (Reg_F_N | Reg_F_V | 0b00100000 | Reg_F_B | Reg_F_D | Reg_F_I | Reg_F_Z | Reg_F_C)

    #define Reg_F_Set(X) { \
        Reg_F_N = X & 0b10000000;  \
        Reg_F_V = X & 0b01000000;  \
        Reg_F_B = X & 0b00010000;  \
        Reg_F_D = X & 0b00001000;  \
        Reg_F_I = X & 0b00000100;  \
        Reg_F_Z = X & 0b00000010;  \
        Reg_F_C = X & 0b00000001;  \
    }
#endif


#define MOS6502_FlagNVal(X) if (X) { MOS6502_FlagNSet; } else { MOS6502_FlagNClr; }
#define MOS6502_FlagZVal(X) if (X) { MOS6502_FlagZSet; } else { MOS6502_FlagZClr; }
#define MOS6502_FlagVVal(X) if (X) { MOS6502_FlagVSet; } else { MOS6502_FlagVClr; }
#define MOS6502_FlagCVal(X) if (X) { MOS6502_FlagCSet; } else { MOS6502_FlagCClr; }

class ScriptEngineMOS65C02 : public ScriptEngine
{
public:
    ScriptEngineMOS65C02();
    ~ScriptEngineMOS65C02();

    void DoCommand();
    void DoReset();
    std::string GetEntryPoints();

private:

    void DebugTraceMem(int Addr, int Quan);
    void DebugTrace();


    int Reg_A;
    int Reg_SP;
    int Reg_PC;
    int Reg_X;
    int Reg_Y;

#ifdef MOS6502_FlagsAsReg
    uchar Reg_F = 0;
#else
    uchar Reg_F_N = 0;
    uchar Reg_F_V = 0;
    uchar Reg_F_B = 0;
    uchar Reg_F_D = 0;
    uchar Reg_F_I = 0;
    uchar Reg_F_Z = 0;
    uchar Reg_F_C = 0;
#endif

    void DoCommandExt(uchar OpCode);

    int MemoryAddress(uchar H, uchar L)
    {
        int H_ = H;
        int L_ = L;
        return (H_ << 8) + L_;
    }

    uchar AddrGetAbsolute()
    {
        return MemGet(MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC)));
    }

    uchar AddrGetAbsoluteIndirect()
    {
        int Addr = MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC));
        return MemGet(MemoryAddress(MemGet(Addr + 1), MemGet(Addr)));
    }

    uchar AddrGetAbsoluteXIndexedIndirect()
    {
        int Addr = MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC)) + Reg_X;
        return MemGet(MemoryAddress(MemGet(Addr + 1), MemGet(Addr)));
    }

    uchar AddrGetXIndexedAbsolute()
    {
        return MemGet(MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC)) + Reg_X);
    }

    uchar AddrGetYIndexedAbsolute()
    {
        return MemGet(MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC)) + Reg_Y);
    }

    uchar AddrGetZeroPage()
    {
        return MemGet(MemPrg(Reg_PC));
    }

    uchar AddrGetXIndexedZeroPage()
    {
        return MemGet((MemPrg(Reg_PC) + Reg_X) & 255);
    }

    uchar AddrGetYIndexedZeroPage()
    {
        return MemGet((MemPrg(Reg_PC) + Reg_Y) & 255);
    }

    uchar AddrGetZeroPageIndirect()
    {
        int Addr = (MemPrg(Reg_PC)) & 255;
        return MemGet(MemoryAddress(MemGet(Addr + 1), MemGet(Addr)));
    }

    uchar AddrGetXIndexedZeroPageIndirect()
    {
        int Addr = (MemPrg(Reg_PC) + Reg_X) & 255;
        return MemGet(MemoryAddress(MemGet(Addr + 1), MemGet(Addr)));
    }

    uchar AddrGetZeroPageIndirectYIndexed()
    {
        int Addr = (MemPrg(Reg_PC));
        return MemGet(MemoryAddress(MemGet(Addr + 1), MemGet(Addr)) + Reg_Y);
    }

    void AddrSetAbsolute(uchar Val)
    {
        MemSet(MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC)), Val);
    }

    void AddrSetXIndexedAbsolute(uchar Val)
    {
        MemSet(MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC)) + Reg_X, Val);
    }

    void AddrSetYIndexedAbsolute(uchar Val)
    {
        MemSet(MemoryAddress(MemPrg(Reg_PC + 1), MemPrg(Reg_PC)) + Reg_Y, Val);
    }

    void AddrSetZeroPage(uchar Val)
    {
        MemSet(MemPrg(Reg_PC), Val);
    }

    void AddrSetXIndexedZeroPage(uchar Val)
    {
        MemSet((MemPrg(Reg_PC) + Reg_X) & 255, Val);
    }

    void AddrSetYIndexedZeroPage(uchar Val)
    {
        MemSet((MemPrg(Reg_PC) + Reg_Y) & 255, Val);
    }

    void AddrSetZeroPageIndirect(uchar Val)
    {
        int Addr = (MemPrg(Reg_PC)) & 255;
        MemSet(MemoryAddress(MemGet(Addr + 1), MemGet(Addr)), Val);
    }

    void AddrSetXIndexedZeroPageIndirect(uchar Val)
    {
        int Addr = (MemPrg(Reg_PC) + Reg_X) & 255;
        MemSet(MemoryAddress(MemGet(Addr + 1), MemGet(Addr)), Val);
    }

    void AddrSetZeroPageIndirectYIndexed(uchar Val)
    {
        int Addr = (MemPrg(Reg_PC));
        MemSet(MemoryAddress(MemGet(Addr + 1), MemGet(Addr)) + Reg_Y, Val);
    }

    void SetFlagsNZ(uchar Val)
    {
        MOS6502_FlagZVal(Val == 0);
        MOS6502_FlagNVal(Val >= 128);
    }

    void DoPush(uchar Val)
    {
        MemSet(Reg_SP + 256, Val);
        if (Reg_SP == 0)
        {
            Reg_SP = 255;
        }
        else
        {
            Reg_SP--;
        }
    }

    uchar DoPop()
    {
        if (Reg_SP == 255)
        {
            Reg_SP = 0;
        }
        else
        {
            Reg_SP++;
        }
        return MemGet(Reg_SP + 256);
    }

    uchar DoShiftL(uchar Val, bool Loop)
    {
        uchar Bit = (Loop && (MOS6502_FlagCGet)) ? 0b00000001 : 0;
        MOS6502_FlagCVal(Val & 0b10000000);
        Val = Val & 0b01111111;
        Val = Val << 1;
        Val = Val + Bit;
        MOS6502_FlagZVal(Val == 0);
        MOS6502_FlagNVal(Val & 0b10000000);
        return Val;
    }

    uchar DoShiftR(uchar Val, bool Loop)
    {
        uchar Bit = (Loop && (MOS6502_FlagCGet)) ? 0b10000000 : 0;
        MOS6502_FlagCVal(Val & 0b00000001);
        Val = Val & 0b11111110;
        Val = Val >> 1;
        Val = Val + Bit;
        MOS6502_FlagZVal(Val == 0);
        MOS6502_FlagNVal(Bit > 0);
        return Val;
    }

    uchar DoADC(uchar Val1, uchar Val2)
    {
        int Val1_ = Val1;
        int Val2_ = Val2;
        int ValC_ = MOS6502_FlagCGet ? 1 : 0;

        if ((Val1_ ^ Val2_) & 0x80)
        {
            MOS6502_FlagVClr;
        }
        else
        {
            MOS6502_FlagVSet;
        }

        int ValResult_;

        if (MOS6502_FlagDGet)
        {
            ValResult_ = (Val1_ & 0x0f) + (Val2_ & 0x0f) + ValC_;
            if (ValResult_ >= 10)
            {
                ValResult_ = 0x10 | ((ValResult_ + 6) & 0x0f);
            }
            ValResult_ = ValResult_ + (Val1_ & 0xf0) + (Val2_ & 0xf0);
            if (ValResult_ >= 160)
            {
                MOS6502_FlagCSet;
                if ((MOS6502_FlagVGet) && (ValResult_ >= 0x180))
                {
                    MOS6502_FlagVClr;
                }
                ValResult_ += 0x60;
            }
            else
            {
                MOS6502_FlagCClr;
                if ((MOS6502_FlagVGet) && (ValResult_ < 0x80))
                {
                    MOS6502_FlagVClr;
                }
            }
        }
        else
        {
            ValResult_ = Val1_ + Val2_ + ValC_;
            if (ValResult_ >= 0x100)
            {
                MOS6502_FlagCSet;
                if ((MOS6502_FlagVGet) && (ValResult_ >= 0x180))
                {
                    MOS6502_FlagVClr;
                }
            }
            else
            {
                MOS6502_FlagCClr;
                if ((MOS6502_FlagVGet) && (ValResult_ < 0x80))
                {
                    MOS6502_FlagVClr;
                }
            }
        }
        uchar ValResult = ValResult_ & 255;
        SetFlagsNZ(ValResult);
        return ValResult;
    }

    uchar DoSUB(uchar Val1, uchar Val2)
    {
        int Val1_ = Val1;
        int Val2_ = Val2;
        int ValC_ = MOS6502_FlagCGet ? 1 : 0;

        if ((Val1_ ^ Val2_) & 0x80)
        {
            MOS6502_FlagVSet;
        }
        else
        {
            MOS6502_FlagVClr;
        }

        int ValResult_;

        if (MOS6502_FlagDGet)
        {
            int ValResult__ = 0x0f + (Val1_ & 0x0f) - (Val2_ & 0x0f) + ValC_;
            if (ValResult__ < 0x10)
            {
                ValResult_ = 0;
                ValResult__ -= 6;
            }
            else
            {
                ValResult_ = 0x10;
                ValResult__ -= 0x10;
            }
            ValResult_ = ValResult_ + 0xf0 + (Val1_ & 0xf0) - (Val2_ & 0xf0);
            if (ValResult_ < 0x100)
            {
                MOS6502_FlagCClr;
                if ((MOS6502_FlagVGet) && (ValResult_ < 0x80))
                {
                    MOS6502_FlagVClr;
                }
                ValResult_ -= 0x60;
            }
            else
            {
                MOS6502_FlagCSet;
                if ((MOS6502_FlagVGet) && (ValResult_ >= 0x180))
                {
                    MOS6502_FlagVClr;
                }
            }
            ValResult_ += ValResult__;
        }
        else
        {
            ValResult_ = 0xff + Val1_ - Val2_ + ValC_;
            if (ValResult_ < 0x100)
            {
                MOS6502_FlagCClr;
                if ((MOS6502_FlagVGet) && (ValResult_ < 0x80))
                {
                    MOS6502_FlagVClr;
                }
            }
            else
            {
                MOS6502_FlagCSet;
                if ((MOS6502_FlagVGet) && (ValResult_ >= 0x180))
                {
                    MOS6502_FlagVClr;
                }
            }
        }

        uchar ValResult = ValResult_ & 255;
        SetFlagsNZ(ValResult);
        return ValResult;
    }

    void DoCMP(uchar Val1, uchar Val2)
    {
        uchar CmpResult = Val1 - Val2;
        MOS6502_FlagZVal(CmpResult == 0);
        MOS6502_FlagNVal(CmpResult & 0x80);
        MOS6502_FlagCVal(Val1 >= Val2);
    }

    uchar DoDEC(uchar Val)
    {
        if (Val != 0)
        {
            Val--;
            SetFlagsNZ(Val);
            return Val;
        }
        else
        {
            MOS6502_FlagZClr;
            MOS6502_FlagNSet;
            return 255;
        }
    }

    uchar DoINC(uchar Val)
    {
        if (Val != 255)
        {
            Val++;
            SetFlagsNZ(Val);
            return Val;
        }
        else
        {
            MOS6502_FlagZSet;
            MOS6502_FlagNClr;
            return 0;
        }
    }

    std::string BranchAddr(int RegPC_Offset)
    {
        int Offset = MemPrg(Reg_PC + RegPC_Offset);
        if (Offset < 128)
        {
            return Hex::IntToHex16(Reg_PC + Offset + 1);
        }
        else
        {
            return Hex::IntToHex16(Reg_PC + Offset - 255);
        }
    }

    void DoBranch()
    {
        int Offset = MemPrg(Reg_PC);
        if (Offset < 128)
        {
            Reg_PC = Reg_PC + Offset + 1;
        }
        else
        {
            Reg_PC = Reg_PC + Offset - 255;
        }
    }

    void DoBranch1()
    {
        Reg_PC++;
        int Offset = MemPrg(Reg_PC);
        if (Offset < 128)
        {
            Reg_PC = Reg_PC + Offset;
        }
        else
        {
            Reg_PC = Reg_PC + Offset - 256;
        }
    }

};

#endif // SCRIPTENGINE65C02_H
