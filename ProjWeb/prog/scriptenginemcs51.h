#ifndef SCRIPTENGINEMCS51_H
#define SCRIPTENGINEMCS51_H

#include "scriptengine.h"
#include "scriptdecompilemcs51.h"

#define MCS51_PSW_CYClr RegBitsX[0x0A] = RegBitsX[0x0A] & 0b01111111
#define MCS51_PSW_ACClr RegBitsX[0x0A] = RegBitsX[0x0A] & 0b10111111
#define MCS51_PSW_F0Clr RegBitsX[0x0A] = RegBitsX[0x0A] & 0b11011111
#define MCS51_PSW_R1Clr RegBitsX[0x0A] = RegBitsX[0x0A] & 0b11101111
#define MCS51_PSW_R0Clr RegBitsX[0x0A] = RegBitsX[0x0A] & 0b11110111
#define MCS51_PSW_OVClr RegBitsX[0x0A] = RegBitsX[0x0A] & 0b11111011
#define MCS51_PSW___Clr RegBitsX[0x0A] = RegBitsX[0x0A] & 0b11111101
#define MCS51_PSW_P_Clr RegBitsX[0x0A] = RegBitsX[0x0A] & 0b11111110

#define MCS51_PSW_CYSet RegBitsX[0x0A] = RegBitsX[0x0A] | 0b10000000
#define MCS51_PSW_ACSet RegBitsX[0x0A] = RegBitsX[0x0A] | 0b01000000
#define MCS51_PSW_F0Set RegBitsX[0x0A] = RegBitsX[0x0A] | 0b00100000
#define MCS51_PSW_R1Set RegBitsX[0x0A] = RegBitsX[0x0A] | 0b00010000
#define MCS51_PSW_R0Set RegBitsX[0x0A] = RegBitsX[0x0A] | 0b00001000
#define MCS51_PSW_OVSet RegBitsX[0x0A] = RegBitsX[0x0A] | 0b00000100
#define MCS51_PSW___Set RegBitsX[0x0A] = RegBitsX[0x0A] | 0b00000010
#define MCS51_PSW_P_Set RegBitsX[0x0A] = RegBitsX[0x0A] | 0b00000001

#define MCS51_PSW_CYGet (RegBitsX[0x0A] & 0b10000000)
#define MCS51_PSW_ACGet (RegBitsX[0x0A] & 0b01000000)
#define MCS51_PSW_F0Get (RegBitsX[0x0A] & 0b00100000)
#define MCS51_PSW_R1Get (RegBitsX[0x0A] & 0b00010000)
#define MCS51_PSW_R0Get (RegBitsX[0x0A] & 0b00001000)
#define MCS51_PSW_OVGet (RegBitsX[0x0A] & 0b00000100)
#define MCS51_PSW___Get (RegBitsX[0x0A] & 0b00000010)
#define MCS51_PSW_P_Get (RegBitsX[0x0A] & 0b00000001)

#define MCS51_AccumulatorRead RegBitsX[0x0C]
#define MCS51_AccumulatorWrite(Data) RegBitsX[0x0C] = (Data); /*!!!!CheckParity()*/

class ScriptEngineMCS51 : public ScriptEngine
{
public:
    ScriptEngineMCS51();
    ~ScriptEngineMCS51();

    void DoCommand();
    void DoReset();
    std::string GetEntryPoints();
private:
public:
    uchar IRAM[256];

    int BitAddress1[256];
    int BitAddress2[256];
    int RegBankAddr[256];

    uchar RegSP;
    uchar RegDPH;
    uchar RegDPL;
    int PC;

    inline uchar PrgRead(int X)
    {
        MemMapC[X] = ScriptEngineMemMapC;
        return MemProg[X];
    }
    inline uchar XBYTERead(int X)
    {
        MemMapR[X] = ScriptEngineMemMapR;
        return MemData[X];
    }
    inline void XBYTEWrite(int X, uchar Y)
    {
        MemMapW[X] = ScriptEngineMemMapW;
        MemData[X] = Y;
    }

    void DoAJMP(int Addr, int Offset);
    void DoACALL(int Addr, int Offset);
    void DoCJNE(int Data1, int Data2, int Addr);
    void DoDJNZ(int R, int Addr);
    void DoADD(int Arg);
    void DoADDC(int Arg);
    void DoSUBB(int Arg);
    int CalcRel(int Data);
    int RRead(int N);
    void RWrite(int N, int Data);
    int IBYTERead(int Addr);
    void IBYTEWrite(int Addr, int Data);
    bool BitRead(int Addr);
    void BitWrite(int Addr, bool Val);
    //void CheckParity();

    int RegBitsX[16];
};

#endif // SCRIPTENGINEMCS51_H
