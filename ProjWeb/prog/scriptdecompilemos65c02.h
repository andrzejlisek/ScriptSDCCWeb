#ifndef SCRIPTDECOMPILEMOS65C02_H
#define SCRIPTDECOMPILEMOS65C02_H

#include "scriptdecompile.h"

class ScriptDecompileMOS65C02 : public ScriptDecompile
{
public:
    ScriptDecompileMOS65C02();
private:
    void ProcessOpcode(int Thr);
    void ProcessOpcodeExt(int Thr);
    int CalcAddr(int Reg_PC);
    int CalcBranch(int Reg_PC);
    int CalcBranch1(int Reg_PC);
    std::string InstructionName(int Addr);
};

#endif // SCRIPTDECOMPILEMOS65C02_H
