#include "guigraph.h"

GuiGraph::GuiGraph()
{

}

std::string GuiGraph::GraphClear(int GraphNum)
{
    ClearCounter++;
    GraphDef.clear();

    TextColorR = 255;
    TextColorG = 255;
    TextColorB = 255;

    TextColorR0 = 0;
    TextColorG0 = 0;
    TextColorB0 = 0;

    TextFore = true;
    TextBack = false;

    Text_X = 0;
    Text_Y = 0;
    Text_Z = 0;
    Text_X0 = 0;
    Text_Y0 = 0;

    for (int I = 0; I < 256; I++)
    {
        ThreadS[I] = 0;
    }
    CurrentThread = 0;
    return "";
}

std::string GuiGraph::GraphThread(int GraphNum, int Thr)
{
    CurrentThread = Thr;
    return "";
}

std::string GuiGraph::GraphThreadReset(int GraphNum)
{
    ThreadS[CurrentThread] = 0;
    return "";
}

std::string GuiGraph::GraphPoint(int GraphNum, std::string X, std::string Y, std::string Z, int R, int G, int B)
{
    PlotDef PD;
    PD.X = GraphStrToDim(X);
    PD.Y = GraphStrToDim(Y);
    PD.Z = GraphStrToDim(Z);
    PD.ColorR = R;
    PD.ColorG = G;
    PD.ColorB = B;
    if (CurrentThread == 0)
    {
        PD.PlotType = PlotTypeDef::Point;
        GraphDef.push_back(PD);
    }
    else
    {
        if (ThreadS[CurrentThread] == 0)
        {
            PD.PlotType = PlotTypeDef::Point;
            GraphDef.push_back(PD);
            ThreadS[CurrentThread] = 1;
        }
        else
        {
            PD.X0 = ThreadX[CurrentThread];
            PD.Y0 = ThreadY[CurrentThread];
            PD.Z0 = ThreadZ[CurrentThread];
            PD.ColorR0 = ThreadR[CurrentThread];
            PD.ColorG0 = ThreadG[CurrentThread];
            PD.ColorB0 = ThreadB[CurrentThread];
            PD.PlotType = ((PD.ColorR0 == R) && (PD.ColorG0 == G) && (PD.ColorB0 == B)) ? PlotTypeDef::LineSolid : PlotTypeDef::LineGradient;
            GraphDef.push_back(PD);
        }
        ThreadX[CurrentThread] = GraphStrToDim(X);
        ThreadY[CurrentThread] = GraphStrToDim(Y);
        ThreadZ[CurrentThread] = GraphStrToDim(Z);
        ThreadR[CurrentThread] = R;
        ThreadG[CurrentThread] = G;
        ThreadB[CurrentThread] = B;
    }
    //Changed = true;
    return "";
}

std::string GuiGraph::GraphLine(int GraphNum, int LinePoints)
{
    if (LinePoints > 0)
    {
        std::vector<int> LineX;
        std::vector<int> LineY;
        std::vector<int> LineZ;
        std::vector<uchar> LineR;
        std::vector<uchar> LineG;
        std::vector<uchar> LineB;

        int I = GraphDef.size();
        while (I > 0)
        {
            I--;
            switch (GraphDef[I].PlotType)
            {
                case PlotTypeDef::None:
                case PlotTypeDef::Text:
                    break;
                case PlotTypeDef::Point:
                    GraphDef[I].PlotType = PlotTypeDef::None;
                    LineX.push_back(GraphDef[I].X);
                    LineY.push_back(GraphDef[I].Y);
                    LineZ.push_back(GraphDef[I].Z);
                    LineR.push_back(GraphDef[I].ColorR);
                    LineG.push_back(GraphDef[I].ColorG);
                    LineB.push_back(GraphDef[I].ColorB);
                    LinePoints--;
                    break;
                case PlotTypeDef::LineSolid:
                case PlotTypeDef::LineGradient:
                    GraphDef[I].PlotType = PlotTypeDef::None;
                    LineX.push_back(GraphDef[I].X);
                    LineY.push_back(GraphDef[I].Y);
                    LineZ.push_back(GraphDef[I].Z);
                    LineR.push_back(GraphDef[I].ColorR);
                    LineG.push_back(GraphDef[I].ColorG);
                    LineB.push_back(GraphDef[I].ColorB);
                    LinePoints--;
                    if (LinePoints >= 0)
                    {
                        LineX.push_back(GraphDef[I].X0);
                        LineY.push_back(GraphDef[I].Y0);
                        LineZ.push_back(GraphDef[I].Z0);
                        LineR.push_back(GraphDef[I].ColorR0);
                        LineG.push_back(GraphDef[I].ColorG0);
                        LineB.push_back(GraphDef[I].ColorB0);
                        LinePoints--;
                    }
                    break;
                case PlotTypeDef::TriangleSolid:
                case PlotTypeDef::TriangleGradient:
                    LineX.push_back(GraphDef[I].X);
                    LineY.push_back(GraphDef[I].Y);
                    LineZ.push_back(GraphDef[I].Z);
                    LineR.push_back(GraphDef[I].ColorR);
                    LineG.push_back(GraphDef[I].ColorG);
                    LineB.push_back(GraphDef[I].ColorB);
                    LinePoints--;
                    if (LinePoints >= 0)
                    {
                        LineX.push_back(GraphDef[I].X0);
                        LineY.push_back(GraphDef[I].Y0);
                        LineZ.push_back(GraphDef[I].Z0);
                        LineR.push_back(GraphDef[I].ColorR0);
                        LineG.push_back(GraphDef[I].ColorG0);
                        LineB.push_back(GraphDef[I].ColorB0);
                        LinePoints--;
                    }
                    if (LinePoints >= 0)
                    {
                        LineX.push_back(GraphDef[I].X00);
                        LineY.push_back(GraphDef[I].Y00);
                        LineZ.push_back(GraphDef[I].Z00);
                        LineR.push_back(GraphDef[I].ColorR00);
                        LineG.push_back(GraphDef[I].ColorG00);
                        LineB.push_back(GraphDef[I].ColorB00);
                        LinePoints--;
                    }
                    break;
            }
            if (LinePoints < 0)
            {
                I = 0;
            }
        }

        for (I = LineX.size() - 1; I > 0; I--)
        {
            PlotDef PD_;

            PD_.X0 = LineX[I];
            PD_.Y0 = LineY[I];
            PD_.Z0 = LineZ[I];
            PD_.ColorR0 = LineR[I];
            PD_.ColorG0 = LineG[I];
            PD_.ColorB0 = LineB[I];

            PD_.X = LineX[I - 1];
            PD_.Y = LineY[I - 1];
            PD_.Z = LineZ[I - 1];
            PD_.ColorR = LineR[I - 1];
            PD_.ColorG = LineG[I - 1];
            PD_.ColorB = LineB[I - 1];

            if ((PD_.ColorR != PD_.ColorR0) || (PD_.ColorG != PD_.ColorG0) || (PD_.ColorB != PD_.ColorB0))
            {
                PD_.PlotType = PlotTypeDef::LineGradient;
            }
            else
            {
                PD_.PlotType = PlotTypeDef::LineSolid;
            }

            GraphDef.push_back(PD_);
        }
    }
    else
    {
        int I = GraphDef.size();
        int PtrIdx = 1;
        PlotDef PD_;
        while (I > 0)
        {
            I--;
            switch (GraphDef[I].PlotType)
            {
                case PlotTypeDef::None:
                case PlotTypeDef::Text:
                    break;
                case PlotTypeDef::Point:
                case PlotTypeDef::LineSolid:
                case PlotTypeDef::LineGradient:
                    GraphDef[I].PlotType = PlotTypeDef::None;
                    switch (PtrIdx)
                    {
                        case 1:
                            PD_.X   = GraphDef[I].X; PD_.Y   = GraphDef[I].Y; PD_.Z   = GraphDef[I].Z; PD_.ColorR   = GraphDef[I].ColorR; PD_.ColorG   = GraphDef[I].ColorG; PD_.ColorB   = GraphDef[I].ColorB;
                            PtrIdx = 2;
                            break;
                        case 2:
                            PD_.X0  = GraphDef[I].X; PD_.Y0  = GraphDef[I].Y; PD_.Z0  = GraphDef[I].Z; PD_.ColorR0  = GraphDef[I].ColorR; PD_.ColorG0  = GraphDef[I].ColorG; PD_.ColorB0  = GraphDef[I].ColorB;
                            PtrIdx = 3;
                            break;
                        case 3:
                            PD_.X00 = GraphDef[I].X; PD_.Y00 = GraphDef[I].Y; PD_.Z00 = GraphDef[I].Z; PD_.ColorR00 = GraphDef[I].ColorR; PD_.ColorG00 = GraphDef[I].ColorG; PD_.ColorB00 = GraphDef[I].ColorB;
                            PtrIdx = 4;
                            I = 0;
                            break;
                    }
                    break;
                case PlotTypeDef::TriangleSolid:
                case PlotTypeDef::TriangleGradient:
                    switch (PtrIdx)
                    {
                        case 1:
                            PD_.X   = GraphDef[I].X;   PD_.Y   = GraphDef[I].Y;   PD_.Z   = GraphDef[I].Z;   PD_.ColorR   = GraphDef[I].ColorR;   PD_.ColorG   = GraphDef[I].ColorG;   PD_.ColorB   = GraphDef[I].ColorB;
                            PD_.X0  = GraphDef[I].X0;  PD_.Y0  = GraphDef[I].Y0;  PD_.Z0  = GraphDef[I].Z0;  PD_.ColorR0  = GraphDef[I].ColorR0;  PD_.ColorG0  = GraphDef[I].ColorG0;  PD_.ColorB0  = GraphDef[I].ColorB0;
                            PD_.X00 = GraphDef[I].X00; PD_.Y00 = GraphDef[I].Y00; PD_.Z00 = GraphDef[I].Z00; PD_.ColorR00 = GraphDef[I].ColorR00; PD_.ColorG00 = GraphDef[I].ColorG00; PD_.ColorB00 = GraphDef[I].ColorB00;
                            PtrIdx = 4;
                            break;
                        case 2:
                            PD_.X0  = GraphDef[I].X;   PD_.Y0  = GraphDef[I].Y;   PD_.Z0  = GraphDef[I].Z;   PD_.ColorR0  = GraphDef[I].ColorR;   PD_.ColorG0  = GraphDef[I].ColorG;   PD_.ColorB0  = GraphDef[I].ColorB;
                            PD_.X00 = GraphDef[I].X0;  PD_.Y00 = GraphDef[I].Y0;  PD_.Z00 = GraphDef[I].Z0;  PD_.ColorR00 = GraphDef[I].ColorR0;  PD_.ColorG00 = GraphDef[I].ColorG0;  PD_.ColorB00 = GraphDef[I].ColorB0;
                            PtrIdx = 4;
                            break;
                        case 3:
                            PD_.X00 = GraphDef[I].X;   PD_.Y00 = GraphDef[I].Y;   PD_.Z00 = GraphDef[I].Z;   PD_.ColorR00 = GraphDef[I].ColorR;   PD_.ColorG00 = GraphDef[I].ColorG;   PD_.ColorB00 = GraphDef[I].ColorB;
                            PtrIdx = 4;
                            I = 0;
                            break;
                    }
                    break;
            }
        }

        if (PtrIdx >= 4)
        {
            PD_.PlotType = PlotTypeDef::TriangleSolid;
            if ((PD_.ColorR != PD_.ColorR0) || (PD_.ColorR0 != PD_.ColorR00) || (PD_.ColorR00 != PD_.ColorR))
            {
                PD_.PlotType = PlotTypeDef::TriangleGradient;
            }
            else
            {
                if ((PD_.ColorG != PD_.ColorG0) || (PD_.ColorG0 != PD_.ColorG00) || (PD_.ColorG00 != PD_.ColorG))
                {
                    PD_.PlotType = PlotTypeDef::TriangleGradient;
                }
                else
                {
                    if ((PD_.ColorB != PD_.ColorB0) || (PD_.ColorB0 != PD_.ColorB00) || (PD_.ColorB00 != PD_.ColorB))
                    {
                        PD_.PlotType = PlotTypeDef::TriangleGradient;
                    }
                }
            }
            GraphDef.push_back(PD_);
        }
    }
    return "";
}

std::string GuiGraph::TextColor(int GraphNum, int Disp, int BackR, int BackG, int BackB, int ForeR, int ForeG, int ForeB)
{
    TextBack = ((Disp & 2) > 0) ? true : false;
    TextFore = ((Disp & 1) > 0) ? true : false;
    TextColorR0 = BackR;
    TextColorG0 = BackG;
    TextColorB0 = BackB;
    TextColorR = ForeR;
    TextColorG = ForeG;
    TextColorB = ForeB;
    return "";
}

std::string GuiGraph::TextPoint(int GraphNum, std::string X, std::string Y, std::string Z)
{
    Text_X = GraphStrToDim(X);
    Text_Y = GraphStrToDim(Y);
    Text_Z = GraphStrToDim(Z);
    Text_X0 = 0;
    Text_Y0 = 0;
    return "";
}

std::string GuiGraph::TextString(int GraphNum, std::string Str)
{
    PlotDef PD;
    PD.X = Text_X;
    PD.Y = Text_Y;
    PD.Z = Text_Z;
    PD.ColorR = TextColorR;
    PD.ColorG = TextColorG;
    PD.ColorB = TextColorB;
    PD.ColorR0 = TextColorR0;
    PD.ColorG0 = TextColorG0;
    PD.ColorB0 = TextColorB0;
    PD.TextB = TextBack;
    PD.TextF = TextFore;
    PD.PlotType = PlotTypeDef::Text;
    PD.TextRaw = Str;
    PD.TextLenRaw = PD.TextRaw.size();
    PD.TextUtf.clear();

    int CharNumState = 0;
    int CharNum, CharNumX;
    for (int I = 0; I < PD.TextLenRaw; I++)
    {
        CharNumX = (uchar)PD.TextRaw[I];
        if (CharNumState == 0)
        {
            CharNum = 32;
            // 0x0000 - 0x007F
            if ((CharNumX & 0b10000000) == 0)
            {
                CharNum = CharNumX;
            }
            else
            {
                // 0x0080 - 0x07FF
                if ((CharNumX & 0b11100000) == 0b11000000)
                {
                    CharNumState = 1;
                    CharNum = (CharNumX & 0b00011111);
                }
                else
                {
                    // 0x0800 - 0xFFFF
                    if ((CharNumX & 0b11110000) == 0b11100000)
                    {
                        CharNumState = 2;
                        CharNum = (CharNumX & 0b00001111);
                    }
                    else
                    {
                        // 0x10000 do 0x1FFFFF
                        if ((CharNumX & 0b11111000) == 0b11110000)
                        {
                            CharNumState = 3;
                            CharNum = (CharNumX & 0b00001111);
                        }
                        else
                        {
                            // 0x200000 do 0x3FFFFFF
                            if ((CharNumX & 0b11111100) == 0b11111000)
                            {
                                CharNumState = 4;
                                CharNum = (CharNumX & 0b00001111);
                            }
                            else
                            {
                                // 0x4000000 do 0x7FFFFFFF
                                if ((CharNumX & 0b11111110) == 0b11111100)
                                {
                                    CharNumState = 5;
                                    CharNum = (CharNumX & 0b00001111);
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            CharNumX = (CharNumX & 0b00111111);
            CharNum = CharNum << 6;
            CharNum = CharNum + CharNumX;
            CharNum = CharNum & 65535;
            CharNumState--;
        }

        if (CharNumState == 0)
        {
            PD.TextUtf.push_back(CharNum);
        }
    }

    PD.TextLenUtf = PD.TextUtf.size();

    PD.TextX_ = (Text_X0 - PD.TextLenUtf);
    PD.TextY_ = (Text_Y0 - 1);
    PD.TextX = PD.TextX_ * TextFontW / 2;
    PD.TextY = PD.TextY_ * TextFontH / 2;
    GraphDef.push_back(PD);
    return "";
}

std::string GuiGraph::TextMove(int GraphNum, int OffsetX, int OffsetY, int Mode)
{
    switch (Mode)
    {
        case 0:
            Text_X0 = OffsetX;
            Text_Y0 = OffsetY;
            break;
        case 1:
            Text_X0 = Text_X0 + OffsetX;
            Text_Y0 = Text_Y0 + OffsetY;
            break;
    }
    return "";
}

void GuiGraph::SetFontCellSize(int TextFontW_, int TextFontH_)
{
    TextFontW = TextFontW_;
    TextFontH = TextFontH_;
    for (int I = 0; I < GraphDef.size(); I++)
    {
        GraphDef[I].TextX = GraphDef[I].TextX_ * TextFontW / 2;
        GraphDef[I].TextY = GraphDef[I].TextY_ * TextFontH / 2;
    }
}
