#include "guiwidgets.h"

GuiWidgets::GuiWidgets()
{

}

std::string GuiWidgets::WidgetClear(int WidgetNum)
{
    WidgetTree.clear();
    return "GuiWidgetClear(" + std::to_string(WidgetNum) + ");";

}

std::string GuiWidgets::WidgetAdd(int WidgetNum, int Id, int ParId, int BundleIdxDefault)
{
    if (GetWidgetById(Id) >= 0)
    {
        return "";
    }
    WidgetTreeItem WTI;
    WTI.Id = Id;
    WTI.ParId = ParId;
    WTI.BundleIdx.push_back(BundleIdxDefault);
    WidgetTree.push_back(WTI);
    return "GuiWidgetAdd(" + std::to_string(WidgetNum) + "," + std::to_string(Id) + "," + std::to_string(ParId) + ");";
}

std::string GuiWidgets::WidgetRemove(int WidgetNum, int Id)
{
    int Item = GetWidgetById(Id);
    if (Item >= 0)
    {
        WidgetTree.erase(WidgetTree.begin() + Item);
        for (int I = 0; I < WidgetTree.size(); I++)
        {
            if (WidgetTree[I].ParId == Id)
            {
                WidgetRemove(WidgetNum, WidgetTree[I].Id);
                I--;
            }
        }
    }
    return "GuiWidgetRemove(" + std::to_string(WidgetNum) + "," + std::to_string(Id) + ");";
}

std::string GuiWidgets::WidgetParamSet(int WidgetNum, int Id, int Param, std::string Value)
{
    if (Id == 0)
    {
        switch (Param)
        {
            case WidgetParamOrientation:
                WidgetTree0.WidgetOrientation = ValueStrToInt(Value);
                return "GuiWidgetParamSet(" + std::to_string(WidgetNum) + "," + std::to_string(Id) + "," + std::to_string(Param) + ",\"" + Hex::StringEncode(Value) + "\");";
        }
        return "";
    }

    int Item = GetWidgetById(Id);
    if (Item >= 0)
    {
        switch (Param)
        {
            case WidgetParamType: WidgetTree[Item].WidgetType = ValueStrToInt(Value); break;
            case WidgetParamOrientation: WidgetTree[Item].WidgetOrientation = ValueStrToInt(Value); break;
            case WidgetParamSize: WidgetTree[Item].WidgetSize = ValueStrToInt(Value); break;
            case WidgetParamValue: WidgetTree[Item].WidgetValue = Value; break;
            case WidgetParamEvent: WidgetTree[Item].WidgetEvent = ValueStrToInt(Value); break;
            case WidgetParamMin:
                {
                    switch (WidgetTree[Item].WidgetType)
                    {
                        case 1:
                        case 2:
                        case 4:
                        case 6:
                            WidgetTree[Item].WidgetValue = Value + WidgetTree[Item].WidgetValue;
                            break;
                        case 5:
                            WidgetTree[Item].WidgetMin = ValueStrToInt(Value);
                            break;
                    }
                }
                break;
            case WidgetParamMax:
                {
                    switch (WidgetTree[Item].WidgetType)
                    {
                        case 1:
                        case 2:
                        case 4:
                        case 6:
                            WidgetTree[Item].WidgetValue = WidgetTree[Item].WidgetValue + Value;
                            break;
                        case 5:
                            WidgetTree[Item].WidgetMax = ValueStrToInt(Value);
                            break;
                    }
                }
                break;
            case WidgetParamEventAdd:
                {
                    for (int I = 0; I < WidgetTree[Item].BundleIdx.size(); I++)
                    {
                        if (WidgetTree[Item].BundleIdx[I] == ValueStrToInt(Value))
                        {
                            return "";
                        }
                    }
                    WidgetTree[Item].BundleIdx.push_back(ValueStrToInt(Value));
                }
                return "";
            case WidgetParamEventRem:
                {
                    for (int I = 0; I < WidgetTree[Item].BundleIdx.size(); I++)
                    {
                        if (WidgetTree[Item].BundleIdx[I] == ValueStrToInt(Value))
                        {
                            WidgetTree[Item].BundleIdx.erase(WidgetTree[Item].BundleIdx.begin() + I);
                            return "";
                        }
                    }
                }
                return "";
        }
    }
    return "GuiWidgetParamSet(" + std::to_string(WidgetNum) + "," + std::to_string(Id) + "," + std::to_string(Param) + ",\"" + Hex::StringEncode(Value) + "\");";
}

std::string GuiWidgets::WidgetRaiseEvent(int WidgetNum, int Id)
{
    return "GuiWidgetEventProg(" + std::to_string(WidgetNum) + "," + std::to_string(Id) + ");";
}

std::string GuiWidgets::WidgetParamGet(int Id, uchar Param)
{
    if (Id == 0)
    {
        switch (Param)
        {
            case WidgetParamOrientation: return std::to_string(WidgetTree0.WidgetOrientation);
        }
        return "";
    }

    int Item = GetWidgetById(Id);
    if (Item >= 0)
    {
        switch (Param)
        {
            case WidgetParamType: return std::to_string(WidgetTree[Item].WidgetType);
            case WidgetParamOrientation: return std::to_string(WidgetTree[Item].WidgetOrientation);
            case WidgetParamSize: return std::to_string(WidgetTree[Item].WidgetSize);
            case WidgetParamValue: return WidgetTree[Item].WidgetValue;
            case WidgetParamMin: return std::to_string(WidgetTree[Item].WidgetMin);
            case WidgetParamMax: return std::to_string(WidgetTree[Item].WidgetMax);
            case WidgetParamEvent: return std::to_string(WidgetTree[Item].WidgetEvent);

            case WidgetParamEventAdd:
            case WidgetParamEventRem:
                std::string BundleIdx = "";
                for (int I = 0; I < WidgetTree[Item].BundleIdx.size(); I++)
                {
                    BundleIdx = BundleIdx + std::to_string(WidgetTree[Item].BundleIdx[I]) + ",";
                }
                return BundleIdx;
        }
    }
    return "";
}

int GuiWidgets::GetWidgetById(int Id)
{
    for (int I = 0; I < WidgetTree.size(); I++)
    {
        if (WidgetTree[I].Id == Id)
        {
            return I;
        }
    }
    return -1;
}

std::string GuiWidgets::GetTree(int WidgetNum)
{
    std::stringstream SS;
    SS << "GuiWidgetClear_(" << WidgetNum << ");" << std::endl;
    SS << "GuiWidgetParamSet_(" << WidgetNum << "," << "0" << "," << WidgetParamOrientation << ",\"" << WidgetTree0.WidgetOrientation << "\");" << std::endl;
    for (int I = 0; I < WidgetTree.size(); I++)
    {
        SS << "GuiWidgetAdd_(" << WidgetNum << "," << WidgetTree[I].Id << "," << WidgetTree[I].ParId << ");" << std::endl;
        SS << "GuiWidgetParamSet_(" << WidgetNum << "," << WidgetTree[I].Id << "," << WidgetParamOrientation << ",\"" << WidgetTree[I].WidgetOrientation << "\");" << std::endl;
        SS << "GuiWidgetParamSet_(" << WidgetNum << "," << WidgetTree[I].Id << "," << WidgetParamType << ",\"" << WidgetTree[I].WidgetType << "\");" << std::endl;
        SS << "GuiWidgetParamSet_(" << WidgetNum << "," << WidgetTree[I].Id << "," << WidgetParamSize << ",\"" << WidgetTree[I].WidgetSize << "\");" << std::endl;
        if (WidgetTree[I].WidgetType == 5)
        {
            SS << "GuiWidgetParamSet_(" << WidgetNum << "," << WidgetTree[I].Id << "," << WidgetParamMin << ",\"" << WidgetTree[I].WidgetMin << "\");" << std::endl;
            SS << "GuiWidgetParamSet_(" << WidgetNum << "," << WidgetTree[I].Id << "," << WidgetParamMax << ",\"" << WidgetTree[I].WidgetMax << "\");" << std::endl;
        }
        SS << "GuiWidgetParamSet_(" << WidgetNum << "," << WidgetTree[I].Id << "," << WidgetParamValue << ",\"" << Hex::StringEncode(WidgetTree[I].WidgetValue) << "\");" << std::endl;
    }
    return SS.str();
}
