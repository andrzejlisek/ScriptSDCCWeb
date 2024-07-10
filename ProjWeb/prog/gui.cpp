#include "gui.h"

Gui::Gui()
{
    GuiFont_ = new GuiFont();
    ScriptShared_.SwapCreate();
    for (int I = 0; I < 256; I++)
    {
        GuiWidgets_[I].WidgetNum = I;
        GuiGraph_[I] = new GuiGraph();
    }
}

Gui::~Gui()
{
    for (int I = 0; I < 256; I++)
    {
        delete GuiGraph_[I];
    }
    ScriptShared_.SwapDestroy();
    delete GuiFont_;
}

void Gui::SetParams(std::string CellW_, std::string CellH_, std::string FontSize_)
{
    FontSizeW = std::stoi(FontSize_);
    FontSizeH = std::stoi(FontSize_);
    GuiFont_->SetFontSize(std::stoi(CellW_), std::stoi(CellH_), FontSizeW, FontSizeH);
    for (int I = 0; I < 256; I++)
    {
        GuiGraph_[I]->SetFontCellSize(GuiFont_->CellW, GuiFont_->CellH);
    }
}

std::string Gui::Swap(std::string Raw)
{
    ScriptShared_.SwapImport(Raw);
    switch (ScriptShared_.SwapData[0])
    {
        case IOWidgetCmd + 4:
            {
                int WidgetNum = ScriptShared_.SwapGetUC(1);
                int WidgetId = ScriptShared_.SwapGetUC(2);
                int WidgetParam = ScriptShared_.SwapGetUC(3);
                ScriptShared_.SwapSetStr(ScriptShared_.SwapGetUC(4), 0x08, Hex::StringDecode(GuiWidgets_[WidgetNum].WidgetParamGet(WidgetId, WidgetParam)));
                ScriptShared_.SwapExportLength = (ScriptShared_.SwapGetUC(4) == 11) ? -16 : 16;
            }
            break;
        case IOMemoCmd + 0:
            ScriptShared_.MemoSwapOperation();
            break;
        case IOMemoCmd + 1:
            ScriptShared_.MemoSwapProcessGet();
            break;
        case IOMemoCmd + 2:
            ScriptShared_.MemoSwapProcessSet();
            break;
    }

    ScriptShared_.SwapData[0] = 0;
    return ScriptShared_.SwapExport();
}

void Gui::FeedbackPrepareArray(std::string FeedbackItem)
{
    FeedbackItemArraySize = 0;
    int StrI = 0;
    for (int I = 0; I < FeedbackItem.size(); I++)
    {
        if (FeedbackItem[I] == ',')
        {
            FeedbackItemArray[FeedbackItemArraySize] = FeedbackItem.substr(StrI, I - StrI);
            StrI = I + 1;
            FeedbackItemArraySize++;
        }
    }
}

std::string Gui::Feedback(std::string FeedbackData)
{
    std::stringstream SS;
    int I0 = 0;
    int I = 0;
    while (I < FeedbackData.length())
    {
        if (FeedbackData[I] == '\n')
        {
            if ((I - I0) > 1)
            {
                std::string FeedbackItem = FeedbackData.substr(I0, I - I0);
                switch (FeedbackItem[0])
                {
                    case 'D':
                    case 'E':
                        {
                            SS << "XMemoScriptMessage(\"" << FeedbackItem << "\");" << std::endl;
                        }
                        break;
                    case 'W':
                        {
                            FeedbackPrepareArray(FeedbackItem);
                            int WidgetNum = ValueStrToInt(FeedbackItemArray[1]);
                            switch (FeedbackItem[1])
                            {
                                case 'C': // CLR
                                    SS << GuiWidgets_[WidgetNum].WidgetClear(WidgetNum) << std::endl;
                                    break;
                                case 'A': // ADD
                                    SS << GuiWidgets_[WidgetNum].WidgetAdd(WidgetNum, ValueStrToInt(FeedbackItemArray[2]), ValueStrToInt(FeedbackItemArray[3]), ValueStrToInt(FeedbackItemArray[4])) << std::endl;
                                    break;
                                case 'R': // REM
                                    SS << GuiWidgets_[WidgetNum].WidgetRemove(WidgetNum, ValueStrToInt(FeedbackItemArray[2])) << std::endl;
                                    break;
                                case 'S': // SET
                                    SS << GuiWidgets_[WidgetNum].WidgetParamSet(WidgetNum, ValueStrToInt(FeedbackItemArray[2]), ValueStrToInt(FeedbackItemArray[3]), Hex::StringDecode(FeedbackItemArray[4])) << std::endl;
                                    break;
                                case 'E': // EVT
                                    SS << GuiWidgets_[WidgetNum].WidgetRaiseEvent(WidgetNum, ValueStrToInt(FeedbackItemArray[2])) << std::endl;
                                    break;
                            }
                        }
                        break;
                    case 'M':
                    case 'N':
                        {
                            SS << "MemoPaint(\"" << FeedbackItem << "\");" << std::endl;
                        }
                        break;
                    case 'O':
                    case 'P':
                        {
                            SS << "MemoDecom(\"" << FeedbackItem << "\");" << std::endl;
                        }
                        break;
                    case 'G':
                        {
                            FeedbackPrepareArray(FeedbackItem);
                            int GraphNum = ValueStrToInt(FeedbackItemArray[1]);
                            switch (FeedbackItem[1])
                            {
                                case 'C':
                                    SS << GuiGraph_[GraphNum]->GraphClear(GraphNum) << std::endl;
                                    break;
                                case 'T':
                                    SS << GuiGraph_[GraphNum]->GraphThread(GraphNum, ValueStrToInt(FeedbackItemArray[2])) << std::endl;
                                    break;
                                case 'R':
                                    SS << GuiGraph_[GraphNum]->GraphThreadReset(GraphNum) << std::endl;
                                    break;
                                case 'P':
                                    SS << GuiGraph_[GraphNum]->GraphPoint(GraphNum, FeedbackItemArray[2], FeedbackItemArray[3], FeedbackItemArray[4], ValueStrToInt(FeedbackItemArray[5]), ValueStrToInt(FeedbackItemArray[6]), ValueStrToInt(FeedbackItemArray[7])) << std::endl;
                                    break;
                                case 'L':
                                    SS << GuiGraph_[GraphNum]->GraphLine(GraphNum, ValueStrToInt(FeedbackItemArray[2])) << std::endl;
                                    break;
                            }
                        }
                        break;
                    case 'T':
                        {
                            FeedbackPrepareArray(FeedbackItem);
                            int GraphNum = ValueStrToInt(FeedbackItemArray[1]);
                            switch (FeedbackItem[1])
                            {
                                case 'C':
                                    {
                                        int ColorDisp = ValueStrToInt(FeedbackItemArray[2]);
                                        int ColorBackR = ValueStrToInt(FeedbackItemArray[3]);
                                        int ColorBackG = ValueStrToInt(FeedbackItemArray[4]);
                                        int ColorBackB = ValueStrToInt(FeedbackItemArray[5]);
                                        int ColorForeR = ValueStrToInt(FeedbackItemArray[6]);
                                        int ColorForeG = ValueStrToInt(FeedbackItemArray[7]);
                                        int ColorForeB = ValueStrToInt(FeedbackItemArray[8]);
                                        SS << GuiGraph_[GraphNum]->TextColor(GraphNum, ColorDisp, ColorBackR, ColorBackG, ColorBackB, ColorForeR, ColorForeG, ColorForeB) << std::endl;
                                    }
                                    break;
                                case 'P':
                                    {
                                        std::string PointX = FeedbackItemArray[2];
                                        std::string PointY = FeedbackItemArray[3];
                                        std::string PointZ = FeedbackItemArray[4];
                                        SS << GuiGraph_[GraphNum]->TextPoint(GraphNum, PointX, PointY, PointZ) << std::endl;
                                    }
                                    break;
                                case 'S':
                                    {
                                        SS << GuiGraph_[GraphNum]->TextString(GraphNum, Hex::StringDecode(FeedbackItemArray[2])) << std::endl;
                                    }
                                    break;
                                case 'M':
                                    {
                                        int MoveX = ValueStrToInt(FeedbackItemArray[2]);
                                        int MoveY = ValueStrToInt(FeedbackItemArray[3]);
                                        int Mode = ValueStrToInt(FeedbackItemArray[4]);
                                        SS << GuiGraph_[GraphNum]->TextMove(GraphNum, MoveX, MoveY, Mode) << std::endl;
                                    }
                            }
                        }
                        break;
                }
            }
            I0 = I + 1;
        }
        I++;
    }
    return SS.str();
}

void Gui::WidgetInvokeEvent(int N, int WidgetId, int SetVal, std::string WidgetValue)
{
    if (SetVal)
    {
        GuiWidgets_[N].WidgetParamSet(N, WidgetId, 0, WidgetValue);
    }
    WidgetInvokeEventType = ValueStrToInt(GuiWidgets_[N].WidgetParamGet(WidgetId, GuiWidgets::WidgetParamEvent));
    FeedbackPrepareArray(GuiWidgets_[N].WidgetParamGet(WidgetId, GuiWidgets::WidgetParamEventAdd));
}

void Gui::GraphSetParams(int GraphNum, int GraphIdx, int ParamN, int P0, int P1, int P2, int P3, int P4, int P5, int P6, int P7, int P8, int P9)
{
    while (GuiGraphInstance_.size() <= GraphIdx)
    {
        GuiGraphInstance _;
        _.GuiGraph_ = GuiGraph_[GraphNum];
        _.GuiFont_ = GuiFont_;
        GuiGraphInstance_.push_back(_);
    }

    GuiGraphInstance_[GraphIdx].SetParams(ParamN, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);
}

void Gui::GraphClearScreen(int GraphNum, int GraphIdx, int ScrW, int ScrH)
{
    GuiGraph_[GraphNum]->GraphClear(GraphNum);
}

void Gui::GraphRepaintScreen(int GraphNum, int GraphIdx, int ScrW, int ScrH)
{
    while (GuiGraphInstance_.size() <= GraphIdx)
    {
        GuiGraphInstance _;
        _.GuiGraph_ = GuiGraph_[GraphNum];
        _.GuiFont_ = GuiFont_;
        GuiGraphInstance_.push_back(_);
    }

    GuiGraphInstance_[GraphIdx].RepaintScreen(GraphNum, GraphIdx, ScrW, ScrH);

    JavaScriptTasks.clear();
    if (GuiGraphInstance_[GraphIdx].RepaintY2 >= GuiGraphInstance_[GraphIdx].RepaintY1)
    {
        int ScrW4 = ScrW * 4;
        std::string JSPrefix = "GuiGraphRepaintResult(" + std::to_string(GraphIdx) + ", ";
        std::string JSSuffix = ");";

        std::stringstream JSStream;
        JSStream = std::stringstream();

        int X1 = GuiGraphInstance_[GraphIdx].RepaintX1;
        int X2 = GuiGraphInstance_[GraphIdx].RepaintX2;
        int Y1 = GuiGraphInstance_[GraphIdx].RepaintY1;
        int Y2 = GuiGraphInstance_[GraphIdx].RepaintY2;

        int DrawLineWidth = (X2 - X1 + 1) << 2;
        int ScriptLenLenSingle = DrawLineWidth + DrawLineWidth + 1;
        char * GraphRawData = new char[ScriptLenLenSingle];
        GraphRawData[DrawLineWidth + DrawLineWidth] = 0;
        uchar * Raw = GuiGraphInstance_[GraphIdx].ImgRaw.data();

        int ScriptLenCounter = 0;
        int ScriptLenMax = 10000;

        int PixelIdx = Y1 * ScrW4 + (X1 << 2);

        for (int Y_ = Y1; Y_ <= Y2; Y_++)
        {
            for (int X_ = 0; X_ < DrawLineWidth; X_++)
            {
                GraphRawData[(X_ << 1) + 0] = (Raw[PixelIdx + X_] >> 4) + 65;
                GraphRawData[(X_ << 1) + 1] = (Raw[PixelIdx + X_] & 15) + 65;
            }

            JSStream << JSPrefix << std::to_string(PixelIdx) << ", \"" << GraphRawData << "\", " << DrawLineWidth << JSSuffix;
            ScriptLenCounter += ScriptLenLenSingle;
            if (ScriptLenCounter >= ScriptLenMax)
            {
                JavaScriptTasks.push_back(JSStream.str());
                JSStream = std::stringstream();
                ScriptLenCounter = 0;
            }

            PixelIdx += ScrW4;
        }

        JSStream << "GuiGraphRepaintResultFinish(" << GraphIdx << ")";
        JavaScriptTasks.push_back(JSStream.str());

        delete[] GraphRawData;
    }
}
