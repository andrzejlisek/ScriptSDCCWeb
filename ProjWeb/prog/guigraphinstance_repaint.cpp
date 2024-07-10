#include "guigraphinstance.h"

void GuiGraphInstance::SetParams(int ParamN, int P0, int P1, int P2, int P3, int P4, int P5, int P6, int P7, int P8, int P9)
{
    switch (ParamN)
    {
        case 0:
            Param_ColorR = P0;
            Param_ColorG = P1;
            Param_ColorB = P2;
            Param_PlotSizeP = P3;
            Param_PlotSizeL = P4;
            Param_PlotSurface = P5;
            Param_PlotText = P6;
            Param_InverseDraw = P7;
            Param_BoundZMin = P8;
            Param_BoundZMax = P9;
            break;
        case 1:
            Param_GrScaleXX = P0;
            Param_GrScaleXY = P1;
            Param_GrScaleXZ = P2;
            Param_GrScaleYX = P3;
            Param_GrScaleYY = P4;
            Param_GrScaleYZ = P5;
            Param_GrScaleZX = P6;
            Param_GrScaleZY = P7;
            Param_GrScaleZZ = P8;
            break;
        case 2:
            Param_GrScaleX = P0;
            Param_GrScaleY = P1;
            Param_GrScaleZ = P2;
            Param_GrOffset1X = P3;
            Param_GrOffset1Y = P4;
            Param_GrOffset1Z = P5;
            Param_GrOffset2X = P6;
            Param_GrOffset2Y = P7;
            Param_GrOffset2Z = P8;
            break;
        case 3:
            Param_Rot1Order = P0;
            Param_Rot1X = P1;
            Param_Rot1Y = P2;
            Param_Rot1Z = P3;
            Param_Rot2Order = P4;
            Param_Rot2X = P5;
            Param_Rot2Y = P6;
            Param_Rot2Z = P7;
            break;
        case 4:
            Param_LightMode = P0;
            Param_LightAngleH = P1;
            Param_LightAngleV = P2;
            Param_LightDist0 = P3;
            Param_LightDist1 = P4;
            Param_LightDist2 = P5;
            break;
    }
}

std::string GuiGraphInstance::RepaintScreen(int GraphNum, int GraphIdx, int ScrW, int ScrH)
{
    RepaintX2 = 0;
    RepaintX1 = ImgW - 1;
    RepaintY2 = 0;
    RepaintY1 = ImgH - 1;

    if ((ScrW <= 0) || (ScrH <= 0))
    {
        return "";
    }

    bool NeedRecreate = false;

    if (ImgW != ScrW) NeedRecreate = true;
    if (ImgH != ScrH) NeedRecreate = true;

    if (NeedRecreate)
    {
        ImgW = ScrW;
        ImgH = ScrH;
        ImgWH = ScrW * ScrH;
        ImgRaw.resize(ImgWH << 2);
        ImgZ.resize(ImgWH);
    }

    RefreshParams();
    if (RefreshParamsModified1 || RefreshParamsModified2)
    {
        NeedRecreate = true;
    }

    GraphDimensionType X, Y, Z, X0, Y0, Z0, X00, Y00, Z00;
    int DrawX, DrawY, DrawZ, DrawX0, DrawY0, DrawZ0, DrawX00, DrawY00, DrawZ00;
    GuiGraph::PlotTypeDef PlotType;
    double LightAngle;

    if (NeedRecreate)
    {
        ZeroX = (ImgW >> 1) - OffsetXRender;
        ZeroY = (ImgH >> 1) + OffsetYRender;
        ZeroZ = 0 - OffsetZRender;

        ImgW1 = ImgW - 1;
        ImgH1 = ImgH - 1;
        PlotSizeP_Margin = PlotSizeP + PlotSizeP2;
        BoundLP = PlotSizeP + PlotSizeP2;
        BoundTP = PlotSizeP + PlotSizeP2;
        BoundRP = ImgW1 - PlotSizeP;
        BoundBP = ImgH1 - PlotSizeP;
        PlotSizeL_Margin = PlotSizeL + PlotSizeL2;
        BoundLL = PlotSizeL + PlotSizeL2;
        BoundTL = PlotSizeL + PlotSizeL2;
        BoundRL = ImgW1 - PlotSizeL;
        BoundBL = ImgH1 - PlotSizeL;

        RefreshClearCounter = 0;
    }

    if (RefreshClearCounter != GuiGraph_->ClearCounter)
    {
        RepaintX1 = 0;
        RepaintX2 = ImgW - 1;
        RepaintY1 = 0;
        RepaintY2 = ImgH - 1;

        int P1 = 0;
        int P4 = 0;
        for (int Y = 0; Y < ImgH; Y++)
        {
            for (int X = 0; X < ImgW; X++)
            {
                ImgZ[P1] = -2147483648;
                P1++;
                ImgRaw[P4 + 0] = BackColorR;
                ImgRaw[P4 + 1] = BackColorG;
                ImgRaw[P4 + 2] = BackColorB;
                ImgRaw[P4 + 3] = 255;
                P4 += 4;
            }
        }
        RefreshItemCounter = 0;
    }

    if (true)
    {
        int L = GuiGraph_->GraphDef.size();

        for (int I = RefreshItemCounter; I < L; I++)
        {
            PlotType = GuiGraph_->GraphDef[I].PlotType;

            X = GuiGraph_->GraphDef[I].X - OffsetX;
            Y = GuiGraph_->GraphDef[I].Y - OffsetY;
            Z = GuiGraph_->GraphDef[I].Z - OffsetZ;
            DrawX = round((X * DrawXtoX) + (Y * DrawYtoX) + (Z * DrawZtoX));
            DrawY = round((X * DrawXtoY) + (Y * DrawYtoY) + (Z * DrawZtoY));
            DrawZ = round((X * DrawXtoZ) + (Y * DrawYtoZ) + (Z * DrawZtoZ));

            switch (PlotType)
            {
                case GuiGraph::PlotTypeDef::None:
                    break;
                case GuiGraph::PlotTypeDef::Text:
                    if (PlotText)
                    {
                        std::vector<int> Text = GuiGraph_->GraphDef[I].TextUtf;
                        int TextLen = GuiGraph_->GraphDef[I].TextLenUtf;
                        int III = 0;
                        int FontW = GuiFont_->CellW;
                        int FontH = GuiFont_->CellH;
                        bool TextB = GuiGraph_->GraphDef[I].TextB;
                        bool TextF = GuiGraph_->GraphDef[I].TextF;
                        for (int II = 0; II < TextLen; II++)
                        {
                            char * Glyph = GuiFont_->GetGlyph(Text[II]);
                            if (Glyph != NULL)
                            {
                                int P = 0;
                                int DrawXX = DrawX + III + GuiGraph_->GraphDef[I].TextX;
                                int DrawYY = DrawY - GuiGraph_->GraphDef[I].TextY;
                                for (int YY = 0; YY < FontH; YY++)
                                {
                                    for (int XX = 0; XX < FontW; XX++)
                                    {
                                        if (Glyph[P])
                                        {
                                            if (TextF)
                                            {
                                                DrawPointT(DrawXX + XX, DrawYY - YY, DrawZ, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB);
                                            }
                                        }
                                        else
                                        {
                                            if (TextB)
                                            {
                                                DrawPointT(DrawXX + XX, DrawYY - YY, DrawZ, GuiGraph_->GraphDef[I].ColorR0, GuiGraph_->GraphDef[I].ColorG0, GuiGraph_->GraphDef[I].ColorB0);
                                            }
                                        }
                                        P++;
                                    }
                                }
                            }
                            III += FontW;
                        }
                    }
                    break;
                case GuiGraph::PlotTypeDef::Point:
                    if (PlotSizeP >= 0)
                    {
                        DrawPoint(DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, M_PI_2);
                    }
                    break;
                case GuiGraph::PlotTypeDef::LineSolid:
                case GuiGraph::PlotTypeDef::LineGradient:
                    X0 = GuiGraph_->GraphDef[I].X0 - OffsetX;
                    Y0 = GuiGraph_->GraphDef[I].Y0 - OffsetY;
                    Z0 = GuiGraph_->GraphDef[I].Z0 - OffsetZ;
                    DrawX0 = round((X0 * DrawXtoX) + (Y0 * DrawYtoX) + (Z0 * DrawZtoX));
                    DrawY0 = round((X0 * DrawXtoY) + (Y0 * DrawYtoY) + (Z0 * DrawZtoY));
                    DrawZ0 = round((X0 * DrawXtoZ) + (Y0 * DrawYtoZ) + (Z0 * DrawZtoZ));

                    DrawX00 = 0;
                    DrawY00 = 0;
                    DrawZ00 = 0;
                    if (LightMode == 2)
                    {
                        double DrawX_ = DrawX - DrawX0;
                        double DrawY_ = DrawY - DrawY0;
                        double DrawZ_ = DrawZ - DrawZ0;
                        LightAngle = VectorAngle(DrawX_, DrawY_, DrawZ_, LightVectorX, LightVectorY, LightVectorZ);
                        if (LightAngle > M_PI_2)
                        {
                            LightAngle = M_PI - LightAngle;
                        }
                        LightAngle = M_PI_2 - LightAngle;
                    }

                    if (InverseDraw2)
                    {
                        if (PlotSizeP >= 0)
                        {
                            DrawPoint(DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                            DrawPoint(DrawX0, DrawY0, DrawZ0, GuiGraph_->GraphDef[I].ColorR0, GuiGraph_->GraphDef[I].ColorG0, GuiGraph_->GraphDef[I].ColorB0, LightAngle);
                        }
                    }
                    if (PlotSizeL >= 0)
                    {
                        if (PlotType == GuiGraph::PlotTypeDef::LineSolid)
                        {
                            DrawLine(DrawX0, DrawY0, DrawZ0, DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                        }
                        else
                        {
                            DrawLine0(DrawX0, DrawY0, DrawZ0, DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR0, GuiGraph_->GraphDef[I].ColorG0, GuiGraph_->GraphDef[I].ColorB0, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                        }
                    }
                    if (!InverseDraw2)
                    {
                        if (PlotSizeP >= 0)
                        {
                            DrawPoint(DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                            DrawPoint(DrawX0, DrawY0, DrawZ0, GuiGraph_->GraphDef[I].ColorR0, GuiGraph_->GraphDef[I].ColorG0, GuiGraph_->GraphDef[I].ColorB0, LightAngle);
                        }
                    }
                    break;
                case GuiGraph::PlotTypeDef::TriangleSolid:
                case GuiGraph::PlotTypeDef::TriangleGradient:
                    X0 = GuiGraph_->GraphDef[I].X0 - OffsetX;
                    Y0 = GuiGraph_->GraphDef[I].Y0 - OffsetY;
                    Z0 = GuiGraph_->GraphDef[I].Z0 - OffsetZ;
                    DrawX0 = round((X0 * DrawXtoX) + (Y0 * DrawYtoX) + (Z0 * DrawZtoX));
                    DrawY0 = round((X0 * DrawXtoY) + (Y0 * DrawYtoY) + (Z0 * DrawZtoY));
                    DrawZ0 = round((X0 * DrawXtoZ) + (Y0 * DrawYtoZ) + (Z0 * DrawZtoZ));

                    X00 = GuiGraph_->GraphDef[I].X00 - OffsetX;
                    Y00 = GuiGraph_->GraphDef[I].Y00 - OffsetY;
                    Z00 = GuiGraph_->GraphDef[I].Z00 - OffsetZ;
                    DrawX00 = round((X00 * DrawXtoX) + (Y00 * DrawYtoX) + (Z00 * DrawZtoX));
                    DrawY00 = round((X00 * DrawXtoY) + (Y00 * DrawYtoY) + (Z00 * DrawZtoY));
                    DrawZ00 = round((X00 * DrawXtoZ) + (Y00 * DrawYtoZ) + (Z00 * DrawZtoZ));

                    if (LightMode == 2)
                    {
                        CalcTriangleAngle(DrawX00, DrawY00, DrawZ00, DrawX0, DrawY0, DrawZ0, DrawX, DrawY, DrawZ, LightAngle);
                    }

                    if (InverseDraw2)
                    {
                        if (PlotSizeP >= 0)
                        {
                            DrawPoint(DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                            DrawPoint(DrawX0, DrawY0, DrawZ0, GuiGraph_->GraphDef[I].ColorR0, GuiGraph_->GraphDef[I].ColorG0, GuiGraph_->GraphDef[I].ColorB0, LightAngle);
                            DrawPoint(DrawX00, DrawY00, DrawZ00, GuiGraph_->GraphDef[I].ColorR00, GuiGraph_->GraphDef[I].ColorG00, GuiGraph_->GraphDef[I].ColorB00, LightAngle);
                        }
                        if (PlotSizeL >= 0)
                        {
                            if (PlotType == GuiGraph::PlotTypeDef::TriangleSolid)
                            {
                                DrawLine(DrawX0, DrawY0, DrawZ0, DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                                DrawLine(DrawX00, DrawY00, DrawZ00, DrawX0, DrawY0, DrawZ0, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                                DrawLine(DrawX, DrawY, DrawZ, DrawX00, DrawY00, DrawZ00, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                            }
                            else
                            {
                                DrawLine0(DrawX0, DrawY0, DrawZ0, DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR0, GuiGraph_->GraphDef[I].ColorG0, GuiGraph_->GraphDef[I].ColorB0, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                                DrawLine0(DrawX00, DrawY00, DrawZ00, DrawX0, DrawY0, DrawZ0, GuiGraph_->GraphDef[I].ColorR00, GuiGraph_->GraphDef[I].ColorG00, GuiGraph_->GraphDef[I].ColorB00, GuiGraph_->GraphDef[I].ColorR0, GuiGraph_->GraphDef[I].ColorG0, GuiGraph_->GraphDef[I].ColorB0, LightAngle);
                                DrawLine0(DrawX, DrawY, DrawZ, DrawX00, DrawY00, DrawZ00, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, GuiGraph_->GraphDef[I].ColorR00, GuiGraph_->GraphDef[I].ColorG00, GuiGraph_->GraphDef[I].ColorB00, LightAngle);
                            }
                        }
                    }
                    if (PlotSurface)
                    {
                        if (PlotType == GuiGraph::PlotTypeDef::TriangleSolid)
                        {
                            DrawTriangle(DrawX00, DrawY00, DrawZ00, DrawX0, DrawY0, DrawZ0, DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                        }
                        else
                        {
                            DrawTriangle0(DrawX00, DrawY00, DrawZ00, DrawX0, DrawY0, DrawZ0, DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR00, GuiGraph_->GraphDef[I].ColorG00, GuiGraph_->GraphDef[I].ColorB00, GuiGraph_->GraphDef[I].ColorR0, GuiGraph_->GraphDef[I].ColorG0, GuiGraph_->GraphDef[I].ColorB0, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                        }
                    }
                    if (!InverseDraw2)
                    {
                        if (PlotSizeL >= 0)
                        {
                            if (PlotType == GuiGraph::PlotTypeDef::TriangleSolid)
                            {
                                DrawLine(DrawX0, DrawY0, DrawZ0, DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                                DrawLine(DrawX00, DrawY00, DrawZ00, DrawX0, DrawY0, DrawZ0, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                                DrawLine(DrawX, DrawY, DrawZ, DrawX00, DrawY00, DrawZ00, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                            }
                            else
                            {
                                DrawLine0(DrawX0, DrawY0, DrawZ0, DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR0, GuiGraph_->GraphDef[I].ColorG0, GuiGraph_->GraphDef[I].ColorB0, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                                DrawLine0(DrawX00, DrawY00, DrawZ00, DrawX0, DrawY0, DrawZ0, GuiGraph_->GraphDef[I].ColorR00, GuiGraph_->GraphDef[I].ColorG00, GuiGraph_->GraphDef[I].ColorB00, GuiGraph_->GraphDef[I].ColorR0, GuiGraph_->GraphDef[I].ColorG0, GuiGraph_->GraphDef[I].ColorB0, LightAngle);
                                DrawLine0(DrawX, DrawY, DrawZ, DrawX00, DrawY00, DrawZ00, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, GuiGraph_->GraphDef[I].ColorR00, GuiGraph_->GraphDef[I].ColorG00, GuiGraph_->GraphDef[I].ColorB00, LightAngle);
                            }
                        }
                        if (PlotSizeP >= 0)
                        {
                            DrawPoint(DrawX, DrawY, DrawZ, GuiGraph_->GraphDef[I].ColorR, GuiGraph_->GraphDef[I].ColorG, GuiGraph_->GraphDef[I].ColorB, LightAngle);
                            DrawPoint(DrawX0, DrawY0, DrawZ0, GuiGraph_->GraphDef[I].ColorR0, GuiGraph_->GraphDef[I].ColorG0, GuiGraph_->GraphDef[I].ColorB0, LightAngle);
                            DrawPoint(DrawX00, DrawY00, DrawZ00, GuiGraph_->GraphDef[I].ColorR00, GuiGraph_->GraphDef[I].ColorG00, GuiGraph_->GraphDef[I].ColorB00, LightAngle);
                        }
                    }
                    break;
            }
        }

        RefreshClearCounter = GuiGraph_->ClearCounter;
        RefreshItemCounter = L;
    }

    if (RepaintX1 < 0) RepaintX1 = 0;
    if (RepaintY1 < 0) RepaintY1 = 0;
    if (RepaintX2 > ImgW1) RepaintX2 = ImgW1;
    if (RepaintY2 > ImgH1) RepaintY2 = ImgH1;

    return "";
}
