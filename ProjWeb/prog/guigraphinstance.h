#ifndef GUIGRAPHINSTANCE_H
#define GUIGRAPHINSTANCE_H

#include <vector>
#include "valuetypes.h"
#include <cmath>
#include "guigraph.h"
#include "guifont.h"

#define GraphDimensionType double
#define MaxPlotWidth 25
#define Det3(X11, X12, X13, X21, X22, X23, X31, X32, X33) ((X11)*(X22)*(X33) + (X21)*(X32)*(X13) + (X31)*(X12)*(X23) - (X21)*(X12)*(X33) - (X11)*(X32)*(X23) - (X31)*(X22)*(X13))
#define VectorAngle(A1, B1, C1, A2, B2, C2) abs(acos((((A1) * (A2)) + ((B1) * (B2)) + ((C1 * C2))) / (sqrt(((A1) * (A1)) + ((B1) * (B1)) + ((C1) * (C1))) * sqrt(((A2) * (A2)) + ((B2) * (B2)) + ((C2) * (C2))))))

#define RefreshParVal1(Param, Value) { if ((Param) != (Value)) { RefreshParamsModified1 = true; } Param = (Value); }
#define RefreshParVal2(Param, Value) { if ((Param) != (Value)) { RefreshParamsModified2 = true; } Param = (Value); }

class GuiGraphInstance
{
public:
    int Param_ColorR = 0;
    int Param_ColorG = 0;
    int Param_ColorB = 0;
    int Param_PlotSizeP = 1;
    int Param_PlotSizeL = 1;
    bool Param_PlotSurface = true;
    bool Param_PlotText = true;
    int Param_InverseDraw = false;
    int Param_BoundZMin = -1000;
    int Param_BoundZMax = 1000;

    int Param_GrScaleXX = 1000;
    int Param_GrScaleXY = 0;
    int Param_GrScaleXZ = 0;
    int Param_GrScaleYX = 0;
    int Param_GrScaleYY = 1000;
    int Param_GrScaleYZ = 0;
    int Param_GrScaleZX = 0;
    int Param_GrScaleZY = 0;
    int Param_GrScaleZZ = 1000;
    int Param_GrScaleX = 1000;
    int Param_GrScaleY = 1000;
    int Param_GrScaleZ = 1000;
    int Param_GrOffset1X = 0;
    int Param_GrOffset1Y = 0;
    int Param_GrOffset1Z = 0;
    int Param_GrOffset2X = 0;
    int Param_GrOffset2Y = 0;
    int Param_GrOffset2Z = 0;
    int Param_Rot1Order = 0;
    int Param_Rot1X = 0;
    int Param_Rot1Y = 0;
    int Param_Rot1Z = 0;
    int Param_Rot2Order = 0;
    int Param_Rot2X = 0;
    int Param_Rot2Y = 0;
    int Param_Rot2Z = 0;

    int Param_LightMode = 0;
    int Param_LightAngleH = 0;
    int Param_LightAngleV = 0;
    int Param_LightDist0 = 0;
    int Param_LightDist1 = -90;
    int Param_LightDist2 = 90;

    int Rot1Order;
    int Rot2Order;

    GuiGraphInstance();
    GuiGraph * GuiGraph_;
    GuiFont * GuiFont_;
    void SetParams(int ParamN, int P0, int P1, int P2, int P3, int P4, int P5, int P6, int P7, int P8, int P9);
    std::string RepaintScreen(int GraphNum, int GraphIdx, int ScrW, int ScrH);
    int RepaintX1, RepaintX2, RepaintY1, RepaintY2;

    int ImgW = 0;
    int ImgH = 0;
    int ImgW1 = 0;
    int ImgH1 = 0;
    int ImgWH = 0;
    std::vector<uchar> ImgRaw;
    std::vector<int> ImgZ;

    int ZeroX = 0;
    int ZeroY = 0;
    int ZeroZ = 0;

    GraphDimensionType OffsetX = 0;
    GraphDimensionType OffsetY = 0;
    GraphDimensionType OffsetZ = 0;

    int OffsetX_ = 0;
    int OffsetY_ = 0;
    int OffsetZ_ = 0;

    int OffsetXRender = 0;
    int OffsetYRender = 0;
    int OffsetZRender = 0;

    int DrawXtoX_ = 0;
    int DrawXtoY_ = 0;
    int DrawXtoZ_ = 0;

    int DrawYtoX_ = 0;
    int DrawYtoY_ = 0;
    int DrawYtoZ_ = 0;

    int DrawZtoX_ = 0;
    int DrawZtoY_ = 0;
    int DrawZtoZ_ = 0;

    GraphDimensionType DrawXtoX = 0;
    GraphDimensionType DrawXtoY = 0;
    GraphDimensionType DrawXtoZ = 0;

    GraphDimensionType DrawYtoX = 0;
    GraphDimensionType DrawYtoY = 0;
    GraphDimensionType DrawYtoZ = 0;

    GraphDimensionType DrawZtoX = 0;
    GraphDimensionType DrawZtoY = 0;
    GraphDimensionType DrawZtoZ = 0;

    GraphDimensionType Angle1X = 0;
    GraphDimensionType Angle1Y = 0;
    GraphDimensionType Angle1Z = 0;

    GraphDimensionType Angle2X = 0;
    GraphDimensionType Angle2Y = 0;
    GraphDimensionType Angle2Z = 0;

    int Angle1X_ = 999;
    int Angle1Y_ = 999;
    int Angle1Z_ = 999;

    int Angle2X_ = 999;
    int Angle2Y_ = 999;
    int Angle2Z_ = 999;

    double LightDistX = 0;
    double LightDistY = 0;
    double LightDistZ = 0;
    double LightDistXYZ = 0;

    int PlotSizeP_Margin = 0;
    int PlotSizeL_Margin = 0;

    int PlotSizeP = 0;
    int PlotSizeP_ = 0;
    bool PlotPointSquare = false;
    int PlotSizeL = 0;
    int PlotSizeL_ = 0;
    bool PlotLineCross = false;
    int PlotSizeP2 = 0;
    int PlotSizeL2 = 0;
    bool PlotSurface = true;
    bool PlotText = true;
    int BoundLP, BoundRP, BoundTP, BoundBP, BoundLL, BoundRL, BoundTL, BoundBL;
    int PlotSizeDiagonal1, PlotSizeDiagonal2, PlotSizeDiagonal3, PlotSizeDiagonal4;
    int BoundZMin = -1000;
    int BoundZMax = 1000;

    int LightMode = 0;
    int LightAngleH = 0;
    int LightAngleV = 0;
    int LightDistance0 = 0;
    int LightDistance1 = 0;
    int LightDistance2 = 0;
    int LightDistance1__ = 0;
    int LightDistance2__ = 0;
    double LightAngleHradP = 0;
    double LightAngleVradP = 0;
    double LightAngleHradN = 0;
    double LightAngleVradN = 0;
    double LightAngle_rad = 0;
    double LightDistance0P_ = 0;
    double LightDistance0N_ = 0;
    double LightDistance1_ = 0;
    double LightDistance2_ = 0;

    double LightVectorX = 0;
    double LightVectorY = 0;
    double LightVectorZ = 0;

    int InverseDraw = 0;
    bool InverseDraw1 = false;
    bool InverseDraw2 = false;
    uchar MaskAll[MaxPlotWidth + 1][MaxPlotWidth + 1][MaxPlotWidth + 1];
    uchar Mask[MaxPlotWidth + 1][MaxPlotWidth + 1];
    uchar BackColorR;
    uchar BackColorG;
    uchar BackColorB;
    uchar BackColorRI;
    uchar BackColorGI;
    uchar BackColorBI;

    uchar Light1R = 0;
    uchar Light1G = 0;
    uchar Light1B = 0;
    uchar Light2R = 0;
    uchar Light2G = 0;
    uchar Light2B = 0;
    double Light1R_ = 0;
    double Light1G_ = 0;
    double Light1B_ = 0;
    double Light2R_ = 0;
    double Light2G_ = 0;
    double Light2B_ = 0;


    int RefreshClearCounter = 0;
    int RefreshItemCounter = 0;


    void RotateScale(double &Angle, double &ScaleX, double &ScaleY);
    void RefreshParams();
    void RefreshParamsApply1();
    void RefreshParamsApply2();

    bool RefreshParamsModified1;
    bool RefreshParamsModified2;

    void CalcColor(uchar &R, uchar &G, uchar &B, int X, int Y, int Z, double LightAngle);

    void DrawUpdateRepaint(int X, int Y, int MarginX, int MarginY);

    void DrawPoint(int X, int Y, int Z, uchar R, uchar G, uchar B, double LightAngle);
    void DrawPointT(int X, int Y, int Z, uchar R, uchar G, uchar B, double LightAngle);
    void DrawPointH(int X, int Y, int Z, uchar R, uchar G, uchar B, double LightAngle);
    void DrawPointV(int X, int Y, int Z, uchar R, uchar G, uchar B, double LightAngle);
    void DrawPointD1(int X, int Y, int Z, uchar R, uchar G, uchar B, double LightAngle);
    void DrawPointD2(int X, int Y, int Z, uchar R, uchar G, uchar B, double LightAngle);
    void DrawLine(int X0, int Y0, int Z0, int X1, int Y1, int Z1, uchar R, uchar G, uchar B, double LightAngle);
    void DrawLine0(int X0, int Y0, int Z0, int X1, int Y1, int Z1, int R0, int G0, int B0, int R1, int G1, int B1, double LightAngle);

    void CalcTriangleAngle(int X1, int Y1, int Z1, int X2, int Y2, int Z2, int X3, int Y3, int Z3, double &LightAngle);

    void DrawHalfTriangle(int X0, int Y0, int Z0, int X1, int X2, int Y_, int Z1, int Z2, uchar R0, uchar G0, uchar B0, double LightAngle);
    void DrawTriangle(int X1, int Y1, int Z1, int X2, int Y2, int Z2, int X3, int Y3, int Z3, uchar R0, uchar G0, uchar B0, double LightAngle);
    void DrawHalfTriangle0(int X0, int Y0, int Z0, int X1, int X2, int Y_, int Z1, int Z2, uchar R0, uchar G0, uchar B0, uchar R1, uchar G1, uchar B1, uchar R2, uchar G2, uchar B2, double LightAngle);
    void DrawTriangle0(int X1, int Y1, int Z1, int X2, int Y2, int Z2, int X3, int Y3, int Z3, uchar R1, uchar G1, uchar B1, uchar R2, uchar G2, uchar B2, uchar R3, uchar G3, uchar B3, double LightAngle);

};

#endif // GUIGRAPHINSTANCE_H
