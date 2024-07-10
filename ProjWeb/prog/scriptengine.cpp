#include "scriptengine.h"

ScriptEngine::ScriptEngine()
{
    //RandomGen;
    //std::random_device rd;  //Will be used to obtain a seed for the random number engine
    //RandomGen.seed(rd());
    FeedbackClear();
    RandomGen.seed(time(0));
}

ScriptEngine::~ScriptEngine()
{
    delete[] MemData;
    if ((MemMode != 0) && (MemMode != 2))
    {
        delete[] MemProg;
    }
}

void ScriptEngine::FeedbackClear()
{
    //Feedback.str(std::string());
    Feedback = std::stringstream();
    FeedbackSize = 0;
}

void ScriptEngine::FeedbackData(std::string S0)
{
    Feedback << S0 << std::endl;
    FeedbackSize += S0.size();
}

void ScriptEngine::FeedbackData(std::string S0, std::string S1)
{
    Feedback << S0 << S1 << std::endl;
    FeedbackSize += S0.size();
    FeedbackSize += S1.size();
}

void ScriptEngine::FeedbackData(std::string S0, std::string S1, std::string S2)
{
    Feedback << S0 << S1 << S2 << std::endl;
    FeedbackSize += S0.size();
    FeedbackSize += S1.size();
    FeedbackSize += S2.size();
}

void ScriptEngine::FeedbackData(std::string S0, std::string S1, std::string S2, std::string S3)
{
    Feedback << S0 << S1 << S2 << S3 << std::endl;
    FeedbackSize += S0.size();
    FeedbackSize += S1.size();
    FeedbackSize += S2.size();
    FeedbackSize += S3.size();
}

std::string ScriptEngine::FeedbackGet()
{
    std::string FBData = Feedback.str();
    FeedbackClear();
    return FBData;
}

void ScriptEngine::PrepareMem(int Mode)
{
    MemData = new uchar[65536];
    MemMode = Mode;
    if (MemMode == 0)
    {
        MemProg = MemData;
    }
    else
    {
        MemProg = new uchar[65536];
    }
}

std::string ScriptEngine::LoadProgram(int Mode_, std::string &ProgCode1, std::string &ProgCode2, int SwapPage_)
{
    //BundleIndex
    MessagePrefix = Hex::IntToHex8(BundleIndex);
    SomeCodeExists = false;

    SwapPage = SwapPage_ << 8;

    // Clearing feedback
    FeedbackClear();

    // Preparing memory
    PrepareMem(Mode_);

    // Clearing memory
    int I, II;
    for (I = 0; I < 65536; I++)
    {
        MemProg[I] = 0;
        MemData[I] = 0;
        MemMapP[I] = 0;
        MemMapR[I] = 0;
        MemMapW[I] = 0;
        MemMapC[I] = 0;
    }
    for (I = 0; I < 256; I++)
    {
        for (II = 0; II < 256; II++)
        {
            MemMapPaint[I][II] = 'A';
        }
    }

    // Loading compiled code and patch
    for (int II = 1; II <= 2; II++)
    {
        std::string ProgCode = "";
        if (II == 1) ProgCode = ProgCode1;
        if (II == 2) ProgCode = ProgCode2;
        int ProgCodeI = 0;
        int ProgCodeL = ProgCode.size();
        for (ProgCodeI = 0; ProgCodeI <= ProgCodeL; ProgCodeI++)
        {
            if (ProgCode[ProgCodeI] == ':')
            {
                // Get binary code line
                int ProgCodeII = ProgCodeI + 1;
                while ((ProgCodeII < ProgCodeL) && (ProgCode[ProgCodeII] != ':'))
                {
                    ProgCodeII++;
                }
                std::string Buf = ProgCode.substr(ProgCodeI, ProgCodeII - ProgCodeI);

                if (Buf.size() > 11)
                {
                    if (Buf.substr(7, 2) == "00")
                    {
                        // Number of bytes
                        int DataLength = Hex::HexToInt(Buf.substr(1, 2));

                        // First byte address
                        int DataAddr = Hex::HexToInt(Buf.substr(3, 4));

                        // Writing bytes into CODE memory
                        for (I = 0; I < DataLength; I++)
                        {
                            SomeCodeExists = true;
                            MemMapP[DataAddr + I] = ScriptEngineMemMapP;
                            MemProg[DataAddr + I] = Hex::HexToInt(Buf.substr(I * 2 + 9, 2));
                        }
                    }
                }
            }
        }
    }

    ScriptShared_.SwapData = MemData;
    ScriptShared_.SwapOffset = SwapPage;

    // Resetting
    ProgReset();

    ScriptDecompile_->DecompilePrepare(MemProg, MemMapP, MemMapC);
    if (SomeCodeExists)
    {
        return GetEntryPoints();
    }
    else
    {
        return "X";
    }
}

void ScriptEngine::MemSet(ushort Addr, uchar Val)
{
    MemMapW[Addr] = ScriptEngineMemMapW;
    MemData[Addr] = Val;
}

void ScriptEngine::MemSet(ushort AddrH, ushort AddrL, uchar Val)
{
    MemMapW[(AddrH << 8) + AddrL] = ScriptEngineMemMapW;
    MemData[(AddrH << 8) + AddrL] = Val;
}

uchar ScriptEngine::MemPrg(ushort Addr)
{
    MemMapC[Addr] = ScriptEngineMemMapC;
    return MemProg[Addr];
}

uchar ScriptEngine::MemGet(ushort Addr)
{
    MemMapR[Addr] = ScriptEngineMemMapR;
    return MemData[Addr];
}

uchar ScriptEngine::MemGet(ushort AddrH, ushort AddrL)
{
    MemMapR[(AddrH << 8) + AddrL] = ScriptEngineMemMapR;
    return MemData[(AddrH << 8) + AddrL];
}

bool ScriptEngine::DoState()
{
    if (MemData[SwapPage] != 0)
    {
        switch (MemData[SwapPage])
        {
            default:
                ProgHalted = true;
                FeedbackData("E", MessagePrefix, "Unsupported I/O command ", Hex::IntToHex8(MemData[SwapPage]));
                StatusC = 3;
                return true;

            case IOConsoleCmd + 0:
                {
                    DebugBuf = "";
                }
                break;
            case IOConsoleCmd + 1:
                {
                    DebugBuf = DebugBuf + ScriptShared_.SwapGetStr(MemData[SwapPage + 1], 0x08);
                }
                break;
            case IOConsoleCmd + 2:
                {
                    FeedbackData("D", MessagePrefix, Hex::StringEncode(DebugBuf));
                    DebugBuf = "";
                }
                break;

            case IOWidgetCmd + 0:
                {
                    int WidgetNum = ScriptShared_.SwapGetUC(1);
                    FeedbackData("WCLR,", std::to_string(WidgetNum) + ",");
                }
                break;
            case IOWidgetCmd + 1:
                {
                    int WidgetNum = ScriptShared_.SwapGetUC(1);
                    int WidgetId = ScriptShared_.SwapGetUC(2);
                    int WidgetParId = ScriptShared_.SwapGetUC(3);
                    FeedbackData("WADD,", std::to_string(WidgetNum) + "," + std::to_string(WidgetId) + "," + std::to_string(WidgetParId) + "," + std::to_string(BundleIndex) + ",");
                }
                break;
            case IOWidgetCmd + 2:
                {
                    int WidgetNum = ScriptShared_.SwapGetUC(1);
                    int WidgetId = ScriptShared_.SwapGetUC(2);
                    FeedbackData("WREM,", std::to_string(WidgetNum) + "," + std::to_string(WidgetId) + ",");
                }
                break;
            case IOWidgetCmd + 3:
                {
                    int WidgetNum = ScriptShared_.SwapGetUC(1);
                    int WidgetId = ScriptShared_.SwapGetUC(2);
                    int WidgetParam = ScriptShared_.SwapGetUC(3);
                    FeedbackData("WSET,", std::to_string(WidgetNum) + "," + std::to_string(WidgetId) + "," + std::to_string(WidgetParam) + "," + Hex::StringEncode(ScriptShared_.SwapGetStr(ScriptShared_.SwapGetUC(4), 0x08)) + ",");
                }
                break;
            case IOWidgetCmd + 4:
                {
                    ScriptShared_.SwapExportLength = 5;
                    StatusC = 9;
                    return true;
                }
                break;
            case IOWidgetCmd + 5:
                {
                    int WidgetNum = ScriptShared_.SwapGetUC(1);
                    int WidgetId = ScriptShared_.SwapGetUC(2);
                    FeedbackData("WEVT,", std::to_string(WidgetNum) + "," + std::to_string(WidgetId) + ",");
                }
                break;

            case IOGraphCmd + 0:
                {
                    std::string GraphNum = std::to_string(ScriptShared_.SwapGetUC(1));
                    FeedbackData("GCLEAR,", GraphNum + ",");
                }
                break;
            case IOGraphCmd + 1:
                {
                    std::string GraphNum = std::to_string(ScriptShared_.SwapGetUC(1));
                    std::string GraphThr = std::to_string(ScriptShared_.SwapGetUC(2));
                    FeedbackData("GTHREAD,", GraphNum + "," + GraphThr + ",");
                }
                break;
            case IOGraphCmd + 2:
                {
                    std::string GraphNum = std::to_string(ScriptShared_.SwapGetUC(1));
                    FeedbackData("GRESET,", GraphNum + ",");
                }
                break;
            case IOGraphCmd + 3:
                {
                    std::string GraphNum = std::to_string(ScriptShared_.SwapGetUC(1));
                    int GraphFormat = ScriptShared_.SwapGetUC(2);
                    std::string GraphColorR = std::to_string(ScriptShared_.SwapGetUC(3));
                    std::string GraphColorG = std::to_string(ScriptShared_.SwapGetUC(4));
                    std::string GraphColorB = std::to_string(ScriptShared_.SwapGetUC(5));
                    std::string GraphPointX = ScriptShared_.SwapGetStr(GraphFormat, 0x10);
                    std::string GraphPointY = ScriptShared_.SwapGetStr(GraphFormat, 0x18);
                    std::string GraphPointZ = ScriptShared_.SwapGetStr(GraphFormat, 0x20);
                    FeedbackData("GPOINT,", GraphNum + "," + GraphPointX + "," + GraphPointY + "," + GraphPointZ + "," + GraphColorR + "," + GraphColorG + "," + GraphColorB + ",");
                }
                break;
            case IOGraphCmd + 4:
                {
                    std::string GraphNum = std::to_string(ScriptShared_.SwapGetUC(1));
                    std::string GraphLines = std::to_string(ScriptShared_.SwapGetUC(2));
                    FeedbackData("GLINE,", GraphNum + "," + GraphLines + ",");
                }
                break;

            case IOGraphTextCmd + 0:
                {
                    std::string GraphNum = std::to_string(ScriptShared_.SwapGetUC(1));
                    std::string DispBackFore = std::to_string(ScriptShared_.SwapGetUC(2));
                    std::string ColorBackR = std::to_string(ScriptShared_.SwapGetUC(3));
                    std::string ColorBackG = std::to_string(ScriptShared_.SwapGetUC(4));
                    std::string ColorBackB = std::to_string(ScriptShared_.SwapGetUC(5));
                    std::string ColorForeR = std::to_string(ScriptShared_.SwapGetUC(6));
                    std::string ColorForeG = std::to_string(ScriptShared_.SwapGetUC(7));
                    std::string ColorForeB = std::to_string(ScriptShared_.SwapGetUC(8));
                    FeedbackData("TCOLOR,", GraphNum + "," + DispBackFore + "," + ColorBackR + "," + ColorBackG + "," + ColorBackB + "," + ColorForeR + "," + ColorForeG + "," + ColorForeB + ",");
                }
                break;
            case IOGraphTextCmd + 1:
                {
                    std::string GraphNum = std::to_string(ScriptShared_.SwapGetUC(1));
                    int GraphFormat = ScriptShared_.SwapGetUC(2);
                    std::string GraphPointX = ScriptShared_.SwapGetStr(GraphFormat, 0x10);
                    std::string GraphPointY = ScriptShared_.SwapGetStr(GraphFormat, 0x18);
                    std::string GraphPointZ = ScriptShared_.SwapGetStr(GraphFormat, 0x20);
                    std::string GraphOffsetX = ScriptShared_.SwapGetStr(4, 0x28);
                    std::string GraphOffsetY = ScriptShared_.SwapGetStr(4, 0x30);
                    FeedbackData("TPOINT,", GraphNum + "," + GraphPointX + "," + GraphPointY + "," + GraphPointZ + "," + GraphOffsetX + "," + GraphOffsetY + ",");
                }
                break;
            case IOGraphTextCmd + 2:
                {
                    std::string GraphNum = std::to_string(ScriptShared_.SwapGetUC(1));
                    std::string GraphText = ScriptShared_.SwapGetStr(ScriptShared_.SwapGetUC(2), 0x08);
                    FeedbackData("TSTRING,", GraphNum + "," + Hex::StringEncode(GraphText) + ",");
                }
                break;
            case IOGraphTextCmd + 3:
                {
                    std::string GraphNum = std::to_string(ScriptShared_.SwapGetUC(1));
                    std::string GraphMoveX = ScriptShared_.SwapGetStr(4, 0x08);
                    std::string GraphMoveY = ScriptShared_.SwapGetStr(4, 0x10);
                    std::string GraphMode = std::to_string(ScriptShared_.SwapGetUC(2));
                    FeedbackData("TMOVE,", GraphNum + "," + GraphMoveX + "," + GraphMoveY + ",", GraphMode + ",");
                }
                break;

            case IOMemoCmd + 0:
                if ((ScriptShared_.SwapGetUC(2) > 1) && ScriptShared_.MemoIsShared())
                {
                    ScriptShared_.SwapExportLength = 8;
                    StatusC = 9;
                    return true;
                }
                else
                {
                    ScriptShared_.MemoSwapOperation();
                }
                break;
            case IOMemoCmd + 1:
                if (ScriptShared_.MemoIsShared())
                {
                    ScriptShared_.SwapExportLength = 24;
                    StatusC = 9;
                    return true;
                }
                else
                {
                    ScriptShared_.MemoSwapProcessGet();
                }
                break;
            case IOMemoCmd + 2:
                if (ScriptShared_.MemoIsShared())
                {
                    ScriptShared_.SwapExportLength = 24;
                    StatusC = 9;
                    return true;
                }
                else
                {
                    ScriptShared_.MemoSwapProcessSet();
                }
                break;

            case 235: // random.h - random_get_*
                {
                    uchar CmdX = MemData[SwapPage + 1];
                    switch(CmdX)
                    {
                        case 0: { std::uniform_int_distribution<schar>  dist(ScriptShared_.SwapGetSC(0x08), ScriptShared_.SwapGetSC(0x10)); ScriptShared_.SwapSetSC(0x08, dist(RandomGen)); } break;
                        case 1: { std::uniform_int_distribution<uchar>  dist(ScriptShared_.SwapGetUC(0x08), ScriptShared_.SwapGetUC(0x10)); ScriptShared_.SwapSetUC(0x08, dist(RandomGen)); } break;
                        case 4: { std::uniform_int_distribution<short>  dist(ScriptShared_.SwapGetSS(0x08), ScriptShared_.SwapGetSS(0x10)); ScriptShared_.SwapSetSS(0x08, dist(RandomGen)); } break;
                        case 5: { std::uniform_int_distribution<ushort> dist(ScriptShared_.SwapGetUS(0x08), ScriptShared_.SwapGetUS(0x10)); ScriptShared_.SwapSetUS(0x08, dist(RandomGen)); } break;
                        case 6: { std::uniform_int_distribution<int>    dist(ScriptShared_.SwapGetSI(0x08), ScriptShared_.SwapGetSI(0x10)); ScriptShared_.SwapSetSI(0x08, dist(RandomGen)); } break;
                        case 7: { std::uniform_int_distribution<uint>   dist(ScriptShared_.SwapGetUI(0x08), ScriptShared_.SwapGetUI(0x10)); ScriptShared_.SwapSetUI(0x08, dist(RandomGen)); } break;
                        case 8: { std::uniform_int_distribution<long>   dist(ScriptShared_.SwapGetSL(0x08), ScriptShared_.SwapGetSL(0x10)); ScriptShared_.SwapSetSL(0x08, dist(RandomGen)); } break;
                        case 9: { std::uniform_int_distribution<ulong>  dist(ScriptShared_.SwapGetUL(0x08), ScriptShared_.SwapGetUL(0x10)); ScriptShared_.SwapSetUL(0x08, dist(RandomGen)); } break;
                        case 10:{ std::uniform_real_distribution<float> dist(ScriptShared_.SwapGetF(0x08),  ScriptShared_.SwapGetF(0x10));  ScriptShared_.SwapSetF(0x08,  dist(RandomGen)); } break;
                    }
                }
                break;

            case 246: // engine_compute_*(uchar Op, uchar  Arg1, uchar  Arg2)
                {
                    EngineMath();
                }
                break;
            case 247: // engine_number()
                {
                    ScriptShared_.SwapSetUC(0x08, BundleIndex);
                }
                break;
            case 248: // string_get(char * V, ushort S)
                {
                    int ValueType = ScriptShared_.SwapGetUC(1);
                    if (ValueType < 11)
                    {
                        ScriptShared_.TextBufGetInit();
                        ScriptShared_.SwapSetStr(ValueType, 0x08, ScriptShared_.TextBufGetString());
                    }
                    else
                    {
                        ScriptShared_.SwapSetUI(0x08, ScriptShared_.TextBufGetInit());
                    }
                }
                break;
            case 249: // string_get(char * V, ushort S)
                ScriptShared_.SwapSetUC(0x08, ScriptShared_.TextBufGetChar());
                break;
            case 250: // string_set(char * V)
                ScriptShared_.TextBufClear();
                break;
            case 251: // string_set(char * V)
                {
                    int ValueType = ScriptShared_.SwapGetUC(1);
                    if (ValueType < 11)
                    {
                        ScriptShared_.TextBufAppendStr(ScriptShared_.SwapGetStr(ValueType, 0x08));
                    }
                    else
                    {
                        ScriptShared_.TextBufAppend(ScriptShared_.SwapGetUC(0x08));
                    }
                }
                break;
            case 252: // engine_counter(uchar div)
                {
                    switch (ScriptShared_.SwapGetUC(1))
                    {
                        case 0: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1LL); InstructionCounter = 0; break;
                        case 1: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10LL); InstructionCounter = 0; break;
                        case 2: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100LL); InstructionCounter = 0; break;
                        case 3: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000LL); InstructionCounter = 0; break;
                        case 4: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10000LL); InstructionCounter = 0; break;
                        case 5: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100000LL); InstructionCounter = 0; break;
                        case 6: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000000LL); InstructionCounter = 0; break;
                        case 7: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10000000LL); InstructionCounter = 0; break;
                        case 8: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100000000LL); InstructionCounter = 0; break;
                        case 9: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000000000LL); InstructionCounter = 0; break;
                        case 10: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10000000000LL); InstructionCounter = 0; break;
                        case 11: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100000000000LL); InstructionCounter = 0; break;
                        case 12: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000000000000LL); InstructionCounter = 0; break;
                        case 13: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10000000000000LL); InstructionCounter = 0; break;
                        case 14: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100000000000000LL); InstructionCounter = 0; break;
                        case 15: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000000000000000LL); InstructionCounter = 0; break;
                        case 16: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10000000000000000LL); InstructionCounter = 0; break;
                        case 17: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100000000000000000LL); InstructionCounter = 0; break;
                        case 18: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000000000000000000LL); InstructionCounter = 0; break;
                        case 20: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1LL); break;
                        case 21: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10LL); break;
                        case 22: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100LL); break;
                        case 23: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000LL); break;
                        case 24: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10000LL); break;
                        case 25: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100000LL); break;
                        case 26: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000000LL); break;
                        case 27: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10000000LL); break;
                        case 28: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100000000LL); break;
                        case 29: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000000000LL); break;
                        case 30: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10000000000LL); break;
                        case 31: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100000000000LL); break;
                        case 32: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000000000000LL); break;
                        case 33: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10000000000000LL); break;
                        case 34: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100000000000000LL); break;
                        case 35: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000000000000000LL); break;
                        case 36: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 10000000000000000LL); break;
                        case 37: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 100000000000000000LL); break;
                        case 38: ScriptShared_.SwapSetUL(0x08, InstructionCounter / 1000000000000000000LL); break;
                    }
                }
                break;
            case 253: // end()
                ProgHalted = true;
                StatusC = 2;
                return true;
            case 254: // stop()
                StatusC = 1;
                return true;
            case 255: // Halted due to error
                ProgHalted = true;
                StatusC = 3;
                return true;
        }
        MemData[SwapPage] = 0;
    }
    return false;
}

int ScriptEngine::ProgRunParams(int CmdCount_, int B1, int B2)
{
    MemData[SwapPage + 255] = B1;
    MemData[SwapPage + 254] = B2;
    return ProgRun(CmdCount_);
}

int ScriptEngine::ProgRunInterrupt(int CmdCount_)
{
    InterruptOnly = true;
    return ProgRun(CmdCount_);
}

int ScriptEngine::ProgRun(int CmdCount_)
{
    if (ProgHalted)
    {
        return 0;
    }

    StatusC = 0;
    MemData[SwapPage] = 0;

    int CmdCount = CmdCount_;
    while (CmdCount > 0)
    {
        InstructionCounter++;
        CmdCount--;
        DoCommand();
        if (DoState())
        {
            return (CmdCount_ - CmdCount);
        }
    }
    return CmdCount_;
}

std::string ScriptEngine::ProgReset()
{
    InstructionCounter = 0;

    ProgHalted = false;
    DebugBuf = "";
    StatusC = 0;
    MemData[SwapPage] = 0;
    while (!InterruptQueue.empty())
    {
        InterruptQueue.pop();
    }
    InterruptIdle = true;
    InterruptOnly = false;
    DoReset();

    int I;
    for (I = 0; I < 65536; I++)
    {
        MemMapR[I] = 0;
        MemMapW[I] = 0;
        MemMapC[I] = 0;
    }
    if (SomeCodeExists)
    {
        return GetEntryPoints();
    }
    else
    {
        return "X";
    }
}


void ScriptEngine::Interrupt(int N, int B1, int B2)
{
    InterruptQueue.push((N << 16) + (B1 << 8) + (B2));
}

int ScriptEngine::InterruptStartMem()
{
    if (MemData[SwapPage] != 0)
    {
        return 0;
    }

    int IntParam = InterruptQueue.front();
    InterruptQueue.pop();
    MemData[SwapPage + 255] = (uchar)((IntParam & 0xFF00) >> 8);
    MemData[SwapPage + 254] = (uchar)((IntParam & 0xFF));
    return IntParam;
}

void ScriptEngine::InterruptFinish()
{
    InterruptIdle = true;
    if (InterruptOnly)
    {
        if (InterruptQueue.size() == 0)
        {
            MemData[SwapPage] = 254;
            InterruptOnly = false;
        }
    }
}

void ScriptEngine::GetDecompiledCode(int Lines, int Opt)
{
    std::string FeedbackPrefix = ((Opt & 1) > 0) ? "P" : "O";

    if ((Opt & 2) > 0)
    {
        // Decompilation process
        ScriptDecompile_->InitDecompile(Opt >> 4);
        FeedbackData(FeedbackPrefix, Hex::IntToHex8(BundleIndex), "00 @@@@");

        bool Iterated = true;
        while (Iterated)
        {
            Iterated = ScriptDecompile_->DoIterate();
        }

        ScriptDecompile_->GetInfoReset();
    }
    else
    {
        // Print decompiled text
        while (Lines > 0)
        {
            std::string Buf = ScriptDecompile_->GetInfo();
            if (Buf != "")
            {
                FeedbackData(FeedbackPrefix, Hex::IntToHex8(BundleIndex), "00" + Buf);
            }
            else
            {
                FeedbackData(FeedbackPrefix, Hex::IntToHex8(BundleIndex), "!! ____");
                Lines = 0;
            }
            Lines--;
        }
    }
}

void ScriptEngine::GetMemoryMap(int Lines, int Opt)
{
    if (Opt & 0b00000010)
    {
        for (int I = 0; I < 65536; I++)
        {
            MemMapR[I] = 0;
            MemMapW[I] = 0;
            MemMapC[I] = 0;
        }
        Opt -= 2;
    }
    std::stringstream S;
    int Addr = 0;
    bool NoPaint = true;
    for (int II = 0; II < 256; II++)
    {
        S = std::stringstream();
        S << Hex::IntToHex8(BundleIndex) << Hex::IntToHex8(II);
        bool Differ = false;

        for (int I = 0; I < 256; I++)
        {
            uchar Chr = 0x41 + MemMapW[Addr] + MemMapR[Addr] + MemMapC[Addr] + MemMapP[Addr];

            S << Chr;

            if (MemMapPaint[II][I] != Chr)
            {
                MemMapPaint[II][I] = Chr;
                Differ = true;
            }

            Addr++;
        }

        if (Differ)
        {
            NoPaint = false;
            if (Opt > 0)
            {
                FeedbackData("N", S.str());
            }
            else
            {
                FeedbackData("M", S.str());
            }
            Lines--;
            if (Lines == 0)
            {
                break;
            }
        }
    }
    if (NoPaint)
    {
        S = std::stringstream();
        S << Hex::IntToHex8(BundleIndex) << "!!";
        if (Opt > 0)
        {
            FeedbackData("N", S.str());
        }
        else
        {
            FeedbackData("M", S.str());
        }
    }
}
