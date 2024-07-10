// https://stackoverflow.com/questions/32291084/minimal-working-example-for-emscripten-webworker
// https://emscripten.org/docs/api_reference/emscripten.h.html

#include "progcommon.cpp"
#include <queue>
#include "prog/gui.h"

#define ValueTypesImplementation
#include "prog/valuetypes.h"

struct WrkRequest
{
    // 1 - Interrupt 1
    // 2 - Interrupt 2
    // 3 - Parameters for resume
    // 4 - Get memory map or decompiled code
    // 5 - Run interrupt only
    // 8 - Stop
    unsigned int ReqType;
    unsigned int ReqPar1;
    unsigned int ReqPar2;
};

struct
{
    worker_handle Wrk;
    
    // 0 - Worker not created
    // 1 - Idle
    // 2 - Working
    char State = 0;

    std::queue<WrkRequest> Requests;
    int Cmds;
    int CmdsToRun;
    int MemoLines = 1;
} ScriptMachineWrk[256];


void ScriptMachineWrkRequest(int Idx, int ReqType, int ReqPar1, int ReqPar2)
{
    if (ScriptMachineWrk[Idx].Requests.size() > 0)
    {
        WrkRequest Item0 = ScriptMachineWrk[Idx].Requests.back();
        if (Item0.ReqType == ReqType)
        {
            if (Item0.ReqPar1 == ReqPar1)
            {
                if (Item0.ReqPar2 == ReqPar2)
                {
                    if ((ReqType != 1) && (ReqType != 2) && (ReqType != 3))
                    {
                        return;
                    }
                }
            }
        }
    }
    WrkRequest Item;
    Item.ReqType = ReqType;
    Item.ReqPar1 = ReqPar1;
    Item.ReqPar2 = ReqPar2;
    ScriptMachineWrk[Idx].Requests.push(Item);
}

void ScriptMachineWrkRequestRemoveStop(int WrkId)
{
    if (!ScriptMachineWrk[WrkId].Requests.empty())
    {
        WrkRequest T = ScriptMachineWrk[WrkId].Requests.front();
        if (T.ReqType == 8)
        {
            ScriptMachineWrk[WrkId].Requests.pop();
        }
    }
}

extern "C"
{
    void CodeStartWork(int WrkId);
    void CodeStartSwap(int WrkId, std::string SwapRaw);
}

Gui Gui_;

void Callback(char * data, int size, void * arg)
{
    switch(data[0])
    {
        case '_':
            emscripten_run_script(data);
            return;
        default:
            {
                BufSet(data);
                std::string W1 = BufGetStr();
                int WrkId = BufGetNum();
                int Cmds = BufGetNum();
                int CmdsX = BufGetNum();
                int StatusC = BufGetNum();
                std::string Feedback = BufGetStr();
                
                Feedback = Gui_.Feedback(Feedback);
                if (Feedback.size() > 1)
                {
                    emscripten_run_script(Feedback.c_str());

                    // Detect, if there is drawing memory map
                    if (Feedback[0] == 'M')
                    {
                        bool MemoScriptStop = ((Feedback[11] == 'N') || (Feedback[11] == 'P'));
                        bool MemoEnd = (Feedback[14] == '!');
                        int MemoOpt = 0;
                        if ((Feedback[11] == 'O') || (Feedback[11] == 'P')) MemoOpt = 4;

                        if (MemoEnd)
                        {
                            if (MemoScriptStop)
                            {
                                ScriptMachineWrkRequestRemoveStop(WrkId);
                                ScriptMachineWrkRequest(WrkId, 8, 1, 0);
                            }
                        }
                        else
                        {
                            ScriptMachineWrkRequest(WrkId, 4, ScriptMachineWrk[WrkId].MemoLines, MemoOpt + (MemoScriptStop ? 1 : 0));
                        }
                        CodeStartWork(WrkId);
                        return;
                    }
                }

                if (StatusC == 9)
                {
                    ScriptMachineWrk[WrkId].CmdsToRun = ScriptMachineWrk[WrkId].CmdsToRun - CmdsX;
                    if (ScriptMachineWrk[WrkId].CmdsToRun < 1) ScriptMachineWrk[WrkId].CmdsToRun = 1;
                    std::string SwapRaw = BufGetStr();
                    SwapRaw = Gui_.Swap(SwapRaw);
                    CodeStartSwap(WrkId, SwapRaw);
                }
                else
                {
                    ScriptMachineWrk[WrkId].CmdsToRun = ScriptMachineWrk[WrkId].Cmds;
                    if (StatusC == 0)
                    {
                        CodeStartWork(WrkId);
                    }
                    else
                    {
                        if ((StatusC == 1) || (StatusC == 8))
                        {
                            bool WaitingEvent = false;
                            if (!ScriptMachineWrk[WrkId].Requests.empty())
                            {
                                WrkRequest T = ScriptMachineWrk[WrkId].Requests.front();
                                if ((T.ReqType <= 3) || (T.ReqType == 5))
                                {
                                    WaitingEvent = true;
                                }
                            }
                            if (WaitingEvent)
                            {
                                CodeStartWork(WrkId);
                            }
                            else
                            {
                                ScriptMachineWrkRequestRemoveStop(WrkId);
                                ScriptMachineWrk[WrkId].State = 1;
                            }
                        }
                        else
                        {
                            while (!ScriptMachineWrk[WrkId].Requests.empty())
                            {
                                ScriptMachineWrk[WrkId].Requests.pop();
                            }
                            ScriptMachineWrk[WrkId].State = 1;
                        }
                    }
                }
            }
            return;
    }
}

void CodeStartWork(int WrkId)
{
    if (ScriptMachineWrk[WrkId].Requests.empty())
    {
        BufClear();
        BufNum(ScriptMachineWrk[WrkId].CmdsToRun);
        BufNum(0);
        BufNum(0);
        BufNum(0);
        BufChr(0);
        emscripten_call_worker(ScriptMachineWrk[WrkId].Wrk, "CodeStart", IOBuf, IOBufPtr, Callback, (void*)0);
    }
    else
    {
        WrkRequest T = ScriptMachineWrk[WrkId].Requests.front();
        ScriptMachineWrk[WrkId].Requests.pop();
        BufClear();
        BufNum(ScriptMachineWrk[WrkId].CmdsToRun);
        BufNum(T.ReqType);
        BufNum(T.ReqPar1);
        BufNum(T.ReqPar2);
        BufChr(0);
        emscripten_call_worker(ScriptMachineWrk[WrkId].Wrk, "CodeStart", IOBuf, IOBufPtr, Callback, (void*)0);
    }
}

void CodeStartSwap(int WrkId, std::string SwapRaw)
{
    BufClear();
    BufNum(ScriptMachineWrk[WrkId].CmdsToRun);
    BufNum(9);
    BufNum(0);
    BufNum(0);
    BufTxt(SwapRaw.c_str());
    BufChr(',');
    BufChr(0);
    emscripten_call_worker(ScriptMachineWrk[WrkId].Wrk, "CodeStart", IOBuf, IOBufPtr, Callback, (void*)0);
}

int main()
{
    ValueConversionPrepare();
    BufInit();
    return 0;
}

std::string GetGlyph(int N)
{
    std::string strJS = "FontGetGlyph(" + std::to_string(N) + ");";
    std::string str_ = "";
    str_.append(emscripten_run_script_string(strJS.c_str()));
    return str_;
}

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    void Init(const char * ConfData)
    {
        Gui_.GuiFont_->GetGlyphJS = GetGlyph;
        emscripten_run_script("_ProgCallback([100,0]);");
    }

    EMSCRIPTEN_KEEPALIVE
    void GuiSetParams()
    {
        std::string strW = "";
        std::string strH = "";
        std::string strF = "";
        strW.append(emscripten_run_script_string("FontGetParam(1);"));
        strH.append(emscripten_run_script_string("FontGetParam(2);"));
        strF.append(emscripten_run_script_string("FontGetParam(3);"));
        Gui_.SetParams(strW, strH, strF);
    }

    EMSCRIPTEN_KEEPALIVE
    void CodeLoad(int WrkId, int Cmds, int Machine, const char * Code1, const char * Code2, int SwapPage)
    {
        if (ScriptMachineWrk[WrkId].State == 2)
        {
            return;
        }

        if (Machine < 100)
        {
            ScriptMachineWrk[WrkId].Wrk = emscripten_create_worker("compiled/progcore.js");
            ScriptMachineWrk[WrkId].State = 1;
            ScriptMachineWrk[WrkId].Cmds = Cmds;
            ScriptMachineWrk[WrkId].CmdsToRun = Cmds;
            while (!ScriptMachineWrk[WrkId].Requests.empty())
            {
                ScriptMachineWrk[WrkId].Requests.pop();
            }
        }

        BufClear();
        BufNum(Machine);
        BufTxt(Code1);
        BufChr(',');
        BufTxt(Code2);
        BufChr(',');
        BufNum(SwapPage);
        BufNum(WrkId);
        BufChr(0);
        emscripten_call_worker(ScriptMachineWrk[WrkId].Wrk, "CodeLoad", IOBuf, IOBufPtr, Callback, (void*)0);
    }

    EMSCRIPTEN_KEEPALIVE
    void CodeStart(int WrkId)
    {
        if (ScriptMachineWrk[WrkId].State == 1)
        {
            ScriptMachineWrk[WrkId].State = 2;
            CodeStartWork(WrkId);
        }
    }

    EMSCRIPTEN_KEEPALIVE
    void CodeStop(int WrkId)
    {
        ScriptMachineWrkRequest(WrkId, 8, 0, 0);
    }

    EMSCRIPTEN_KEEPALIVE
    void CodeReset(int WrkId)
    {
        if (ScriptMachineWrk[WrkId].State == 1)
        {
            BufClear();
            BufNum(0);
            BufChr(0);
            emscripten_call_worker(ScriptMachineWrk[WrkId].Wrk, "CodeReset", IOBuf, IOBufPtr, Callback, (void*)0);
        }
    }


    EMSCRIPTEN_KEEPALIVE
    void MemoMap(int WrkId, int Lines, int Opt)
    {
        ScriptMachineWrk[WrkId].MemoLines = Lines;
        if (ScriptMachineWrk[WrkId].State > 0)
        {
            if (ScriptMachineWrk[WrkId].State == 1)
            {
                ScriptMachineWrkRequest(WrkId, 4, ScriptMachineWrk[WrkId].MemoLines, 1 + Opt);
                ScriptMachineWrk[WrkId].State = 2;
                CodeStartWork(WrkId);
            }
            else
            {
                ScriptMachineWrkRequest(WrkId, 4, ScriptMachineWrk[WrkId].MemoLines, 0 + Opt);
            }
        }
    }

    
    EMSCRIPTEN_KEEPALIVE
    void WidgetRefresh(int Num, int Idx)
    {
        emscripten_run_script(Gui_.GuiWidgets_[Num].GetTree(Idx).c_str());
    }
    
    EMSCRIPTEN_KEEPALIVE
    void WidgetInvokeEvent(int N, int WidgetId, int SetVal, const char * WidgetValue)
    {
        Gui_.WidgetInvokeEvent(N, WidgetId, SetVal, std::string(WidgetValue));
        for (int I = 0; I < Gui_.FeedbackItemArraySize; I++)
        {
            int WrkId = ValueStrToInt(Gui_.FeedbackItemArray[I]);
            bool RunInterrupt = false;
            
            // 0b-------1
            if (Gui_.WidgetInvokeEventType & 0x01)
            {
                ScriptMachineWrkRequest(WrkId, 1, N, WidgetId);
                RunInterrupt = true;
            }
            
            // 0b------1-
            if (Gui_.WidgetInvokeEventType & 0x02)
            {
                ScriptMachineWrkRequest(WrkId, 2, N, WidgetId);
                RunInterrupt = true;
            }
            
            // 0b-----1--
            if (Gui_.WidgetInvokeEventType & 0x04)
            {
                ScriptMachineWrkRequest(WrkId, 3, N, WidgetId);
                CodeStart(WrkId);
            }
            else
            {
                if (RunInterrupt && (ScriptMachineWrk[WrkId].State == 1))
                {
                    ScriptMachineWrkRequest(WrkId, 5, N, WidgetId);
                    CodeStart(WrkId);
                }
            }
        }
    }

    EMSCRIPTEN_KEEPALIVE
    void GraphSetParams(int GraphNum, int GraphIdx, int ParamN, int P0, int P1, int P2, int P3, int P4, int P5, int P6, int P7, int P8, int P9)
    {
        Gui_.GraphSetParams(GraphNum, GraphIdx, ParamN, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);
    }

    EMSCRIPTEN_KEEPALIVE
    void GraphRepaintScreen(int GraphNum, int GraphIdx, int ScrW, int ScrH)
    {
        Gui_.GraphRepaintScreen(GraphNum, GraphIdx, ScrW, ScrH);
        for (int I = 0; I < Gui_.JavaScriptTasks.size(); I++)
        {
            //std::cout << Gui_.JavaScriptTasks[I] << std::endl;
            emscripten_run_script(Gui_.JavaScriptTasks[I].c_str());
        }
    }

    EMSCRIPTEN_KEEPALIVE
    void GraphClearScreen(int GraphNum, int GraphIdx, int ScrW, int ScrH)
    {
        Gui_.GraphClearScreen(GraphNum, GraphIdx, ScrW, ScrH);
        GraphRepaintScreen(GraphNum, GraphIdx, ScrW, ScrH);
    }
}

