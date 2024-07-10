#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include "valuetypes.h"
#include <string>
#include <iostream>
#include <random>
#include <queue>
#include "scriptshared.h"
#include <chrono>
#include <cmath>
#include "scriptdecompile.h"

#define ScriptEngineMemMapR 1
#define ScriptEngineMemMapW 2
#define ScriptEngineMemMapP 4
#define ScriptEngineMemMapC 8

class ScriptEngine
{
    typedef int ArrayDim;
public:
    long TimeStamp0()
    {
        auto TimeNow = std::chrono::high_resolution_clock::now();
        auto TimeBase = std::chrono::floor<std::chrono::hours>(TimeNow);
        return std::chrono::duration_cast<std::chrono::milliseconds>(TimeNow - TimeBase).count();
    }


    ScriptEngine();
    virtual ~ScriptEngine();

    ScriptDecompile * ScriptDecompile_;

    uchar BundleIndex;

    uchar * MemData;
    uchar * MemProg;
    uchar MemMapR[65536];
    uchar MemMapW[65536];
    uchar MemMapP[65536];
    uchar MemMapC[65536];
    uchar MemMapPaint[256][256];

    void MemSet(ushort Addr, uchar Val);
    void MemSet(ushort AddrH, ushort AddrL, uchar Val);
    uchar MemPrg(ushort Addr);
    uchar MemGet(ushort Addr);
    uchar MemGet(ushort AddrH, ushort AddrL);
    int MemMode;
    void PrepareMem(int Mode);

    std::string LoadProgram(int Mode_, std::string &ProgCode1, std::string &ProgCode2, int SwapPage_);

    std::mt19937 RandomGen;


    TypeConv IOBuffer;

    void InputValue(std::string Val);


    virtual void DoCommand() = 0;
    virtual void DoReset() = 0;
    virtual std::string GetEntryPoints() = 0;

    int ProgRunParams(int CmdCount_, int B1, int B2);
    int ProgRun(int CmdCount_);
    int ProgRunInterrupt(int CmdCount_);
    std::string ProgReset();

    int SwapPage = 0;

    uchar StatusC = 0;

    volatile uchar CoreInvokeWait;

    void Interrupt(int N, int B1, int B2);
    int InterruptStartMem();
    void InterruptFinish();

    void GetDecompiledCode(int Lines, int Opt);
    void GetMemoryMap(int Lines, int Opt);


    void FeedbackClear();
    void FeedbackData(std::string S0);
    void FeedbackData(std::string S0, std::string S1);
    void FeedbackData(std::string S0, std::string S1, std::string S2);
    void FeedbackData(std::string S0, std::string S1, std::string S2, std::string S3);
    std::string FeedbackGet();

    ScriptShared ScriptShared_;
private:
    llong InstructionCounter = 0;
    bool SomeCodeExists = false;
    std::stringstream Feedback;
    int FeedbackSize;

    bool ProgHalted = false;

    bool DoState();

    std::string DebugBuf;

    void EngineMath();

protected:
    bool InterruptOnly = false;
    std::string MessagePrefix;
    std::queue<int> InterruptQueue;
    bool InterruptIdle;
};

#endif // SCRIPTENGINE_H
