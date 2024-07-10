#ifndef GUIWIDGETS_H
#define GUIWIDGETS_H

#include <string>
#include <vector>
#include "valuetypes.h"
#include <sstream>
#include "hex.h"
#include <iostream>

class GuiWidgets
{
public:
    int WidgetNum = 0;
    GuiWidgets();
    std::string WidgetClear(int WidgetNum);
    std::string WidgetAdd(int WidgetNum, int Id, int ParId, int BundleIdxDefault);
    std::string WidgetRemove(int WidgetNum, int Id);
    std::string WidgetParamSet(int WidgetNum, int Id, int Param, std::string Value);
    std::string WidgetParamGet(int Id, uchar Param);
    std::string WidgetRaiseEvent(int WidgetNum, int Id);
    std::string GetTree(int WidgetNum);


    constexpr static int WidgetParamValue = 0;
    constexpr static int WidgetParamOrientation = 1;
    constexpr static int WidgetParamMin = 2;
    constexpr static int WidgetParamMax = 3;

    constexpr static int WidgetParamEvent = 125;
    constexpr static int WidgetParamEventAdd = 124;
    constexpr static int WidgetParamEventRem = 123;
    constexpr static int WidgetParamSize = 126;
    constexpr static int WidgetParamType = 127;
private:

    int GetWidgetById(int Id);

    struct WidgetTreeItem
    {
        int Id = 0;
        int ParId = 0;
        std::string WidgetValue = "";
        int WidgetOrientation = 0;
        int WidgetSize = 100;
        int WidgetType = 0;
        int WidgetMin = -100;
        int WidgetMax = 100;
        int WidgetEvent = 0;
        std::vector<int> BundleIdx;
    };

    std::vector<WidgetTreeItem> WidgetTree;
    WidgetTreeItem WidgetTree0;

};

#endif // GUIWIDGETS_H
