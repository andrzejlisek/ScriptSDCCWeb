#ifndef SCRIPTDECOMPILE_H
#define SCRIPTDECOMPILE_H

#include "valuetypes.h"
#include "hex.h"
#include <vector>
#include <iostream>

class ScriptDecompile
{
public:
    ScriptDecompile();
    virtual ~ScriptDecompile();
    void DecompilePrepare(uchar * MemProg_, uchar * MemMapP_, uchar * MemMapC_);
    void InitDecompile(int EntryPoint);
    bool DoIterate();
    void GetInfoReset();
    std::string GetInfo();
    std::string GetInfoMem(int Line, int Length);
    void JumpVectorAddr(int Reg_PC, int Addr);
protected:
    std::vector<int> ProgramCounterThreads;
    std::string InstrPattern[65536];
    void ThreadNext(int Thr, int Step);
    void ThreadAdd(int Addr);
    void ThreadAddVector(int Reg_PC);
    uchar * MemProg;
    uchar * MemMapC;
    uchar * MemMapP;
    uchar DecompiledOpcodes[65536];
    uchar DecompiledLabels[65536];
    std::string StringFindReplace(std::string S, std::string From, std::string To);
    std::string LabelPrefix = "_";
private:
    std::vector<int> JumpVector1;
    std::vector<int> JumpVector2;
    virtual void ProcessOpcode(int Thr) = 0;
    virtual std::string InstructionName(int Addr) = 0;
    int InfoState = 0;
    bool InfoStateLabel = false;
};

#endif // SCRIPTDECOMPILE_H
