#ifndef SCRIPTDECOMPILEMCS51_H
#define SCRIPTDECOMPILEMCS51_H

#include "scriptdecompile.h"

class ScriptDecompileMCS51 : public ScriptDecompile
{
public:
    ScriptDecompileMCS51();
private:
    void ProcessOpcode(int Thr);
    std::string InstructionName(int Addr);
    int CalcAJMP(int Reg_PC, int Offset);
    int CalcAddr(int Reg_PC);
    int CalcRel(int Reg_PC);
};

#endif // SCRIPTDECOMPILEMCS51_H
