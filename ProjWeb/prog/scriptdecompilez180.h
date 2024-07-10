#ifndef SCRIPTDECOMPILEZ180_H
#define SCRIPTDECOMPILEZ180_H

#include "scriptdecompile.h"

class ScriptDecompileZ180 : public ScriptDecompile
{
public:
    ScriptDecompileZ180();
private:
    void ProcessOpcode(int Thr);
    void ProcessOpcodeExtCB(int Thr);
    void ProcessOpcodeExt_D(int Thr);
    void ProcessOpcodeExtED(int Thr);
    std::string InstructionName(int Addr);
    int CalcAddr(int Reg_PC);
    int CalcRel(int Reg_PC);
};

#endif // SCRIPTDECOMPILEZ180_H
