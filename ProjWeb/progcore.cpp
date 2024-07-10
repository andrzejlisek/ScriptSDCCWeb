#define ValueTypesImplementation
#include "prog/valuetypes.h"

#include "progcommon.cpp"
#include "prog/scriptenginemcs51.h"
#include "prog/scriptenginez180.h"
#include "prog/scriptenginemos65c02.h"

int WorkerId = 0;

void RespondClear()
{
    BufClear();
    BufTxt("_ProgCallback([");
}

void RespondClear0()
{
    BufClear();
    BufChr('!');
    BufChr(',');
    BufNum(WorkerId);
}

void RespondFinish()
{
    BufTxt("0]);");
    BufChr(0);
    emscripten_worker_respond(IOBuf, IOBufPtr);
}

void RespondPartial()
{
    BufTxt("0]);");
    BufChr(0);
    emscripten_worker_respond_provisionally(IOBuf, IOBufPtr);
}

ScriptEngine * SM = NULL;

std::string CodeLoadBuf = "";

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void CodeLoad(char * data, int size)
    {
        ValueConversionPrepare();
        BufSet(data);
        int ProgMachine = BufGetNum();
        std::string ProgCode1 = BufGetStr();
        std::string ProgCode2 = BufGetStr();
        int ProgAddrSwapPage = BufGetNum();
        int BundleIndex = BufGetNum();
        
        int MemMode = 0;
        if ((SM != NULL) && (ProgMachine < 100))
        {
            delete SM;
            SM = NULL;
        }
        switch (ProgMachine)
        {
            case 0: MemMode = 0; SM = new ScriptEngineMCS51();    break;
            case 1: MemMode = 0; SM = new ScriptEngineZ180();     break;
            case 2: MemMode = 0; SM = new ScriptEngineMOS65C02(); break;
            case 3: MemMode = 1; SM = new ScriptEngineMCS51();    break;
            case 4: MemMode = 1; SM = new ScriptEngineZ180();     break;
            case 5: MemMode = 1; SM = new ScriptEngineMOS65C02(); break;
            case 101:
                CodeLoadBuf = CodeLoadBuf + ProgCode1;
                RespondClear();
                BufNum(101);
                BufNum(WorkerId);
                BufNum(0);
                RespondFinish();
                return;
            case 102:
                ProgCode1 = CodeLoadBuf;
                break;
        }

        WorkerId = BundleIndex;
        SM->BundleIndex = BundleIndex;
        std::string EntryPoints = SM->LoadProgram(MemMode, ProgCode1, ProgCode2, ProgAddrSwapPage);
        bool CodeExists = (EntryPoints.length() > 2);
        CodeLoadBuf = "";

        RespondClear();
        BufNum(101);
        BufNum(WorkerId);
        BufNum(CodeExists ? 1 : 0);
        BufChr('\"');
        BufStr(EntryPoints);
        BufChr('\"');
        BufChr(',');
        RespondFinish();
    }

    EMSCRIPTEN_KEEPALIVE
    void CodeReset(char * data, int size)
    {
        BufSet(data);
        std::string EntryPoints = SM->ProgReset();
        bool CodeExists = (EntryPoints.length() > 2);
        RespondClear();
        BufNum(101);
        BufNum(WorkerId);
        BufNum(CodeExists ? 1 : 0);
        BufChr('\"');
        BufStr(EntryPoints);
        BufChr('\"');
        BufChr(',');
        RespondFinish();
    }


    EMSCRIPTEN_KEEPALIVE
    void CodeStart(char * data, int size)
    {
        long Time1, Time2, Time3, Time4;
        Time1 = TimeStamp();
        BufSet(data);
        int Cmds = BufGetNum();
        int IntN = BufGetNum();
        int Int1 = BufGetNum();
        int Int2 = BufGetNum();
        int CmdsX = 0;

        switch (IntN)
        {
            case 0:
                CmdsX = SM->ProgRun(Cmds);
                break;
            case 1:
            case 2:
                SM->Interrupt(IntN, Int1, Int2);
                break;
            case 3:
                CmdsX = SM->ProgRunParams(Cmds, Int1, Int2);
                break;
            case 4:
                {
                    if (Int2 & 0x04)
                    {
                        SM->GetDecompiledCode(Int1, Int2);
                    }
                    else
                    {
                        SM->GetMemoryMap(Int1, Int2);
                    }
                }
                break;
            case 5:
                CmdsX = SM->ProgRunInterrupt(Cmds);
                break;
            case 8:
                if (Int1 == 1)
                {
                    if (SM->StatusC == 0)
                    {
                        SM->StatusC = 8;
                    }
                }
                else
                {
                    SM->StatusC = 1;
                }
                break;
            case 9:
                std::string SwapRaw = BufGetStr();
                SM->ScriptShared_.SwapImport(SwapRaw);
                CmdsX = SM->ProgRun(Cmds);
                break;
        }
        RespondClear0();
        BufNum(Cmds);
        BufNum(CmdsX);
        BufNum(SM->StatusC);
        BufStr(SM->FeedbackGet());
        BufTxt(",");
        if (SM->StatusC == 9)
        {
            BufTxt(SM->ScriptShared_.SwapExport().c_str());
            BufChr(',');
        }
        RespondPartial();

        RespondClear();
        BufNum(102);
        BufNum(WorkerId);
        BufNum(CmdsX);
        BufNum(SM->StatusC);
        BufTxt(",");
        RespondFinish();
        Time4 = TimeStamp();
   }
}
