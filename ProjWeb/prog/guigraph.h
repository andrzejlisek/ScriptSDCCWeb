#ifndef GUIGRAPH_H
#define GUIGRAPH_H

#include <string>
#include <vector>
#include <iostream>
#include "valuetypes.h"

#define GraphDimensionType double
#define GraphStrToDim(X) ValueStrToDouble(X);

class GuiGraph
{
public:
    GuiGraph();
    std::string GraphClear(int GraphNum);
    std::string GraphThread(int GraphNum, int Thr);
    std::string GraphThreadReset(int GraphNum);
    std::string GraphPoint(int GraphNum, std::string X, std::string Y, std::string Z, int R, int G, int B);
    std::string GraphLine(int GraphNum, int LinePoints);
    std::string TextColor(int GraphNum, int Disp, int BackR, int BackG, int BackB, int ForeR, int ForeG, int ForeB);
    std::string TextPoint(int GraphNum, std::string X, std::string Y, std::string Z);
    std::string TextString(int GraphNum, std::string Str);
    std::string TextMove(int GraphNum, int OffsetX, int OffsetY, int Mode);

    void SetFontCellSize(int TextFontW_, int TextFontH_);

    int ClearCounter = 1;

    enum PlotTypeDef { None, Text, Point, LineSolid, LineGradient, TriangleSolid, TriangleGradient };

    struct PlotDef
    {
        GraphDimensionType X = 0;
        GraphDimensionType Y = 0;
        GraphDimensionType Z = 0;
        uchar ColorR = 0;
        uchar ColorG = 0;
        uchar ColorB = 0;

        GraphDimensionType X0 = 0;
        GraphDimensionType Y0 = 0;
        GraphDimensionType Z0 = 0;
        uchar ColorR0 = 0;
        uchar ColorG0 = 0;
        uchar ColorB0 = 0;

        GraphDimensionType X00 = 0;
        GraphDimensionType Y00 = 0;
        GraphDimensionType Z00 = 0;
        uchar ColorR00 = 0;
        uchar ColorG00 = 0;
        uchar ColorB00 = 0;

        PlotTypeDef PlotType;

        std::string TextRaw = "";
        std::vector<int> TextUtf;
        int TextLenRaw = 0;
        int TextLenUtf = 0;
        int TextX = 0;
        int TextY = 0;
        int TextX_ = 0;
        int TextY_ = 0;

        bool TextF = true;
        bool TextB = false;

        int RepaintBack = 0;
    };

    std::vector<PlotDef> GraphDef;

private:
    int TextFontW = 8;
    int TextFontH = 16;



    uchar TextColorR = 255;
    uchar TextColorG = 255;
    uchar TextColorB = 255;

    uchar TextColorR0 = 0;
    uchar TextColorG0 = 0;
    uchar TextColorB0 = 0;

    bool TextFore = true;
    bool TextBack = false;



    uchar CurrentThread = 0;
    GraphDimensionType ThreadX[256];
    GraphDimensionType ThreadY[256];
    GraphDimensionType ThreadZ[256];
    uchar ThreadR[256];
    uchar ThreadG[256];
    uchar ThreadB[256];
    uchar ThreadS[256];

    GraphDimensionType Text_X = 0;
    GraphDimensionType Text_Y = 0;
    GraphDimensionType Text_Z = 0;
    int Text_X0 = 0;
    int Text_Y0 = 0;
};

#endif // GUIGRAPH_H
