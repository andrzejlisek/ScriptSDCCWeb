#ifndef GUI_H
#define GUI_H

#include <iostream>
#include "guiwidgets.h"
#include "guigraph.h"
#include "guigraphinstance.h"
#include "guifont.h"
#include "scriptshared.h"
#include <chrono>
#include <cstring>

class Gui
{
public:
    Gui();
    ~Gui();

    int FontSizeW = 1;
    int FontSizeH = 1;
    void SetParams(std::string CellW_, std::string CellH_, std::string FontSize_);
    GuiFont * GuiFont_;

    GuiWidgets GuiWidgets_[256];
    GuiGraph * GuiGraph_[256];
    std::vector<GuiGraphInstance> GuiGraphInstance_;

    ScriptShared ScriptShared_;
    std::string Swap(std::string Raw);
    std::string Feedback(std::string FeedbackData);
    void WidgetInvokeEvent(int N, int WidgetId, int SetVal, std::string WidgetValue);
    void GraphSetParams(int GraphNum, int GraphIdx, int ParamN, int P0, int P1, int P2, int P3, int P4, int P5, int P6, int P7, int P8, int P9);
    void GraphClearScreen(int GraphNum, int GraphIdx, int ScrW, int ScrH);
    void GraphRepaintScreen(int GraphNum, int GraphIdx, int ScrW, int ScrH);
    int WidgetInvokeEventType;
    std::vector<int> WidgetInvokeEventBundle;
    std::string FeedbackItemArray[250];
    int FeedbackItemArraySize = 0;
    std::vector<std::string> JavaScriptTasks;


    long TimeStamp0()
    {
        auto TimeNow = std::chrono::high_resolution_clock::now();
        auto TimeBase = std::chrono::floor<std::chrono::hours>(TimeNow);
        return std::chrono::duration_cast<std::chrono::milliseconds>(TimeNow - TimeBase).count();
    }

private:
    void FeedbackPrepareArray(std::string FeedbackItem);
};

#endif // GUI_H
