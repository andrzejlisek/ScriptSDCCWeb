#include "guigraphinstance.h"

GuiGraphInstance::GuiGraphInstance()
{
    BackColorR = 0;
    BackColorG = 0;
    BackColorB = 0;
    BackColorRI = 255;
    BackColorGI = 255;
    BackColorBI = 255;

    for (int I = 0; I <= MaxPlotWidth; I++)
    {
        for (int Y = 0; Y <= MaxPlotWidth; Y++)
        {
            for (int X = 0; X <= MaxPlotWidth; X++)
            {
                MaskAll[I][X][Y] = (((X * X) + (Y * Y)) <= (I * I)) ? 1 : 0;
            }
        }
    }

    ImgW = 0;
    ImgH = 0;
}

void GuiGraphInstance::RotateScale(double &Angle, double &ScaleX, double &ScaleY)
{
    GraphDimensionType Dist = (ScaleX * ScaleX) + (ScaleY * ScaleY);
    GraphDimensionType AngDiff = atan2f(ScaleY, ScaleX);
    Dist = sqrt(Dist);
    AngDiff += Angle;
    ScaleX = cosf(AngDiff) * Dist;
    ScaleY = sinf(AngDiff) * Dist;
}

void GuiGraphInstance::RefreshParams()
{
    RefreshParamsModified1 = false;
    RefreshParamsModified2 = false;

    RefreshParVal1(PlotSurface, Param_PlotSurface);
    RefreshParVal1(PlotText, Param_PlotText);
    RefreshParVal1(InverseDraw, Param_InverseDraw);

    RefreshParVal1(PlotSizeP_, Param_PlotSizeP);
    RefreshParVal1(PlotSizeL_, Param_PlotSizeL);

    RefreshParVal1(DrawXtoX_, Param_GrScaleXX * Param_GrScaleX);
    RefreshParVal1(DrawXtoY_, Param_GrScaleXY * Param_GrScaleX);
    RefreshParVal1(DrawXtoZ_, Param_GrScaleXZ * Param_GrScaleX);
    RefreshParVal1(DrawYtoX_, Param_GrScaleYX * Param_GrScaleY);
    RefreshParVal1(DrawYtoY_, Param_GrScaleYY * Param_GrScaleY);
    RefreshParVal1(DrawYtoZ_, Param_GrScaleYZ * Param_GrScaleY);
    RefreshParVal1(DrawZtoX_, Param_GrScaleZX * Param_GrScaleZ);
    RefreshParVal1(DrawZtoY_, Param_GrScaleZY * Param_GrScaleZ);
    RefreshParVal1(DrawZtoZ_, Param_GrScaleZZ * Param_GrScaleZ);

    RangeMod(Param_Rot1X, (0 - 180), (0 + 180), 360);
    RangeMod(Param_Rot1Y, (0 - 180), (0 + 180), 360);
    RangeMod(Param_Rot1Z, (0 - 180), (0 + 180), 360);
    RangeMod(Param_Rot2X, (0 - 180), (0 + 180), 360);
    RangeMod(Param_Rot2Y, (0 - 180), (0 + 180), 360);
    RangeMod(Param_Rot2Z, (0 - 180), (0 + 180), 360);
    RangeMod(Param_LightAngleH, (0 - 180), (0 + 180), 360);
    RangeMod(Param_LightAngleV, (0 - 180), (0 + 180), 360);

    RefreshParVal1(Angle1X_, Param_Rot1X);
    RefreshParVal1(Angle1Y_, Param_Rot1Y);
    RefreshParVal1(Angle1Z_, Param_Rot1Z);
    RefreshParVal1(Angle2X_, Param_Rot2X);
    RefreshParVal1(Angle2Y_, Param_Rot2Y);
    RefreshParVal1(Angle2Z_, Param_Rot2Z);

    RefreshParVal1(Rot1Order, Param_Rot1Order);
    RefreshParVal1(Rot2Order, Param_Rot2Order);

    RefreshParVal1(OffsetX_, Param_GrOffset1X);
    RefreshParVal1(OffsetY_, Param_GrOffset1Y);
    RefreshParVal1(OffsetZ_, Param_GrOffset1Z);

    RefreshParVal1(OffsetXRender, Param_GrOffset2X);
    RefreshParVal1(OffsetYRender, Param_GrOffset2Y);
    RefreshParVal1(OffsetZRender, Param_GrOffset2Z);

    RefreshParVal1(BoundZMin, Param_BoundZMin);
    RefreshParVal1(BoundZMax, Param_BoundZMax);

    RefreshParVal2(BackColorR, Param_ColorR);
    RefreshParVal2(BackColorG, Param_ColorG);
    RefreshParVal2(BackColorB, Param_ColorB);

    RefreshParVal2(LightMode, Param_LightMode);
    RefreshParVal2(LightAngleH, Param_LightAngleH);
    RefreshParVal2(LightAngleV, Param_LightAngleV);
    RefreshParVal2(LightDistance0, Param_LightDist0);
    RefreshParVal2(LightDistance1__, Param_LightDist1);
    RefreshParVal2(LightDistance2__, Param_LightDist2);

    if (RefreshParamsModified1)
    {
        RefreshParamsApply1();
    }
    if (RefreshParamsModified2)
    {
        RefreshParamsApply2();
    }
}


void GuiGraphInstance::RefreshParamsApply1()
{
    InverseDraw1 = false;
    InverseDraw2 = false;
    if (InverseDraw)
    {
        InverseDraw1 = true;
        InverseDraw2 = true;
    }

    if (PlotSizeP_ > 0)
    {
        PlotPointSquare = false;
        PlotSizeP = PlotSizeP_ - 1;
    }
    else
    {
        PlotPointSquare = true;
        PlotSizeP = (0 - PlotSizeP_) - 1;
    }
    PlotSizeP2 = PlotSizeP & 1;
    PlotSizeP = PlotSizeP >> 1;
    if (PlotSizeL_ > 0)
    {
        PlotSizeL = PlotSizeL_ - 1;
        PlotLineCross = false;
    }
    else
    {
        PlotSizeL = (0 - PlotSizeL_) - 1;
        PlotLineCross = true;
    }

    DrawXtoX = DrawXtoX_; DrawXtoX /= 1000000.0;
    DrawXtoY = DrawXtoY_; DrawXtoY /= 1000000.0;
    DrawXtoZ = DrawXtoZ_; DrawXtoZ /= 1000000.0;
    DrawYtoX = DrawYtoX_; DrawYtoX /= 1000000.0;
    DrawYtoY = DrawYtoY_; DrawYtoY /= 1000000.0;
    DrawYtoZ = DrawYtoZ_; DrawYtoZ /= 1000000.0;
    DrawZtoX = DrawZtoX_; DrawZtoX /= 1000000.0;
    DrawZtoY = DrawZtoY_; DrawZtoY /= 1000000.0;
    DrawZtoZ = DrawZtoZ_; DrawZtoZ /= 1000000.0;

    PlotSizeL2 = PlotSizeL & 1;
    PlotSizeL = PlotSizeL >> 1;

    if (PlotSizeP >= 0)
    {
        if (PlotPointSquare)
        {
            for (int YY = 0; YY <= MaxPlotWidth; YY++)
            {
                for (int XX = 0; XX <= MaxPlotWidth; XX++)
                {
                    Mask[XX][YY] = 1;
                }
            }
        }
        else
        {
            for (int YY = 0; YY <= MaxPlotWidth; YY++)
            {
                for (int XX = 0; XX <= MaxPlotWidth; XX++)
                {
                    Mask[XX][YY] = MaskAll[PlotSizeP][XX][YY];
                }
            }
        }
    }
    else
    {
        for (int YY = 0; YY <= MaxPlotWidth; YY++)
        {
            for (int XX = 0; XX <= MaxPlotWidth; XX++)
            {
                Mask[XX][YY] = 0;
            }
        }
    }


    int BoundX = (((double)((PlotSizeL + PlotSizeL + PlotSizeL2) << 1)) / sqrt(2));
    //BoundX = PlotSizeL + PlotSizeL + PlotSizeL2;
    int BoundXX = BoundX >> 1;
    PlotSizeDiagonal1 = (BoundXX >> 1) + (BoundXX & 1);
    PlotSizeDiagonal2 = BoundXX >> 1;
    PlotSizeDiagonal3 = PlotSizeDiagonal1 - 1;
    PlotSizeDiagonal4 = PlotSizeDiagonal2;
    if ((BoundXX & 1))
    {
        PlotSizeDiagonal4 += ((BoundX & 1));
    }
    else
    {
        PlotSizeDiagonal3 += ((BoundX & 1));
    }

    GraphDimensionType Val_;
    Val_ = Angle1X_; Val_ = Val_ * M_PI / 180.0; Angle1X = Val_;
    Val_ = Angle1Y_; Val_ = Val_ * M_PI / 180.0; Angle1Y = Val_;
    Val_ = Angle1Z_; Val_ = Val_ * M_PI / 180.0; Angle1Z = Val_;
    Val_ = Angle2X_; Val_ = Val_ * M_PI / 180.0; Angle2X = 0.0 - Val_;
    Val_ = Angle2Y_; Val_ = Val_ * M_PI / 180.0; Angle2Y = 0.0 - Val_;
    Val_ = Angle2Z_; Val_ = Val_ * M_PI / 180.0; Angle2Z = 0.0 - Val_;

    switch (Rot1Order)
    {
        case 0: RotateScale(Angle1X, DrawYtoX, DrawZtoX); RotateScale(Angle1X, DrawYtoY, DrawZtoY); RotateScale(Angle1X, DrawYtoZ, DrawZtoZ); RotateScale(Angle1Y, DrawZtoX, DrawXtoX); RotateScale(Angle1Y, DrawZtoY, DrawXtoY); RotateScale(Angle1Y, DrawZtoZ, DrawXtoZ); RotateScale(Angle1Z, DrawXtoX, DrawYtoX); RotateScale(Angle1Z, DrawXtoY, DrawYtoY); RotateScale(Angle1Z, DrawXtoZ, DrawYtoZ); break;
        case 1: RotateScale(Angle1X, DrawYtoX, DrawZtoX); RotateScale(Angle1X, DrawYtoY, DrawZtoY); RotateScale(Angle1X, DrawYtoZ, DrawZtoZ); RotateScale(Angle1Z, DrawXtoX, DrawYtoX); RotateScale(Angle1Z, DrawXtoY, DrawYtoY); RotateScale(Angle1Z, DrawXtoZ, DrawYtoZ); RotateScale(Angle1Y, DrawZtoX, DrawXtoX); RotateScale(Angle1Y, DrawZtoY, DrawXtoY); RotateScale(Angle1Y, DrawZtoZ, DrawXtoZ); break;
        case 2: RotateScale(Angle1Y, DrawZtoX, DrawXtoX); RotateScale(Angle1Y, DrawZtoY, DrawXtoY); RotateScale(Angle1Y, DrawZtoZ, DrawXtoZ); RotateScale(Angle1Z, DrawXtoX, DrawYtoX); RotateScale(Angle1Z, DrawXtoY, DrawYtoY); RotateScale(Angle1Z, DrawXtoZ, DrawYtoZ); RotateScale(Angle1X, DrawYtoX, DrawZtoX); RotateScale(Angle1X, DrawYtoY, DrawZtoY); RotateScale(Angle1X, DrawYtoZ, DrawZtoZ); break;
        case 3: RotateScale(Angle1Y, DrawZtoX, DrawXtoX); RotateScale(Angle1Y, DrawZtoY, DrawXtoY); RotateScale(Angle1Y, DrawZtoZ, DrawXtoZ); RotateScale(Angle1X, DrawYtoX, DrawZtoX); RotateScale(Angle1X, DrawYtoY, DrawZtoY); RotateScale(Angle1X, DrawYtoZ, DrawZtoZ); RotateScale(Angle1Z, DrawXtoX, DrawYtoX); RotateScale(Angle1Z, DrawXtoY, DrawYtoY); RotateScale(Angle1Z, DrawXtoZ, DrawYtoZ); break;
        case 4: RotateScale(Angle1Z, DrawXtoX, DrawYtoX); RotateScale(Angle1Z, DrawXtoY, DrawYtoY); RotateScale(Angle1Z, DrawXtoZ, DrawYtoZ); RotateScale(Angle1X, DrawYtoX, DrawZtoX); RotateScale(Angle1X, DrawYtoY, DrawZtoY); RotateScale(Angle1X, DrawYtoZ, DrawZtoZ); RotateScale(Angle1Y, DrawZtoX, DrawXtoX); RotateScale(Angle1Y, DrawZtoY, DrawXtoY); RotateScale(Angle1Y, DrawZtoZ, DrawXtoZ); break;
        case 5: RotateScale(Angle1Z, DrawXtoX, DrawYtoX); RotateScale(Angle1Z, DrawXtoY, DrawYtoY); RotateScale(Angle1Z, DrawXtoZ, DrawYtoZ); RotateScale(Angle1Y, DrawZtoX, DrawXtoX); RotateScale(Angle1Y, DrawZtoY, DrawXtoY); RotateScale(Angle1Y, DrawZtoZ, DrawXtoZ); RotateScale(Angle1X, DrawYtoX, DrawZtoX); RotateScale(Angle1X, DrawYtoY, DrawZtoY); RotateScale(Angle1X, DrawYtoZ, DrawZtoZ); break;
    }

    switch (Rot2Order)
    {
        case 0: RotateScale(Angle2X, DrawXtoY, DrawXtoZ); RotateScale(Angle2X, DrawYtoY, DrawYtoZ); RotateScale(Angle2X, DrawZtoY, DrawZtoZ); RotateScale(Angle2Y, DrawXtoZ, DrawXtoX); RotateScale(Angle2Y, DrawYtoZ, DrawYtoX); RotateScale(Angle2Y, DrawZtoZ, DrawZtoX); RotateScale(Angle2Z, DrawXtoX, DrawXtoY); RotateScale(Angle2Z, DrawYtoX, DrawYtoY); RotateScale(Angle2Z, DrawZtoX, DrawZtoY); break;
        case 1: RotateScale(Angle2X, DrawXtoY, DrawXtoZ); RotateScale(Angle2X, DrawYtoY, DrawYtoZ); RotateScale(Angle2X, DrawZtoY, DrawZtoZ); RotateScale(Angle2Z, DrawXtoX, DrawXtoY); RotateScale(Angle2Z, DrawYtoX, DrawYtoY); RotateScale(Angle2Z, DrawZtoX, DrawZtoY); RotateScale(Angle2Y, DrawXtoZ, DrawXtoX); RotateScale(Angle2Y, DrawYtoZ, DrawYtoX); RotateScale(Angle2Y, DrawZtoZ, DrawZtoX); break;
        case 2: RotateScale(Angle2Y, DrawXtoZ, DrawXtoX); RotateScale(Angle2Y, DrawYtoZ, DrawYtoX); RotateScale(Angle2Y, DrawZtoZ, DrawZtoX); RotateScale(Angle2Z, DrawXtoX, DrawXtoY); RotateScale(Angle2Z, DrawYtoX, DrawYtoY); RotateScale(Angle2Z, DrawZtoX, DrawZtoY); RotateScale(Angle2X, DrawXtoY, DrawXtoZ); RotateScale(Angle2X, DrawYtoY, DrawYtoZ); RotateScale(Angle2X, DrawZtoY, DrawZtoZ); break;
        case 3: RotateScale(Angle2Y, DrawXtoZ, DrawXtoX); RotateScale(Angle2Y, DrawYtoZ, DrawYtoX); RotateScale(Angle2Y, DrawZtoZ, DrawZtoX); RotateScale(Angle2X, DrawXtoY, DrawXtoZ); RotateScale(Angle2X, DrawYtoY, DrawYtoZ); RotateScale(Angle2X, DrawZtoY, DrawZtoZ); RotateScale(Angle2Z, DrawXtoX, DrawXtoY); RotateScale(Angle2Z, DrawYtoX, DrawYtoY); RotateScale(Angle2Z, DrawZtoX, DrawZtoY); break;
        case 4: RotateScale(Angle2Z, DrawXtoX, DrawXtoY); RotateScale(Angle2Z, DrawYtoX, DrawYtoY); RotateScale(Angle2Z, DrawZtoX, DrawZtoY); RotateScale(Angle2X, DrawXtoY, DrawXtoZ); RotateScale(Angle2X, DrawYtoY, DrawYtoZ); RotateScale(Angle2X, DrawZtoY, DrawZtoZ); RotateScale(Angle2Y, DrawXtoZ, DrawXtoX); RotateScale(Angle2Y, DrawYtoZ, DrawYtoX); RotateScale(Angle2Y, DrawZtoZ, DrawZtoX); break;
        case 5: RotateScale(Angle2Z, DrawXtoX, DrawXtoY); RotateScale(Angle2Z, DrawYtoX, DrawYtoY); RotateScale(Angle2Z, DrawZtoX, DrawZtoY); RotateScale(Angle2Y, DrawXtoZ, DrawXtoX); RotateScale(Angle2Y, DrawYtoZ, DrawYtoX); RotateScale(Angle2Y, DrawZtoZ, DrawZtoX); RotateScale(Angle2X, DrawXtoY, DrawXtoZ); RotateScale(Angle2X, DrawYtoY, DrawYtoZ); RotateScale(Angle2X, DrawZtoY, DrawZtoZ); break;
    }

    OffsetX = OffsetX_; OffsetX /= 1000.0;
    OffsetY = OffsetY_; OffsetY /= 1000.0;
    OffsetZ = OffsetZ_; OffsetZ /= 1000.0;
}

void GuiGraphInstance::RefreshParamsApply2()
{
    LightDistance1 = LightDistance1__;
    LightDistance2 = LightDistance2__;

    BackColorRI = 255 - BackColorR;
    BackColorGI = 255 - BackColorG;
    BackColorBI = 255 - BackColorB;

    if (LightDistance1 < 0)
    {
        LightDistance1 = 0 - LightDistance1;
        Light1R = BackColorRI;
        Light1G = BackColorGI;
        Light1B = BackColorBI;
    }
    else
    {
        Light1R = BackColorR;
        Light1G = BackColorG;
        Light1B = BackColorB;
    }
    if (LightDistance2 < 0)
    {
        LightDistance2 = 0 - LightDistance2;
        Light2R = BackColorRI;
        Light2G = BackColorGI;
        Light2B = BackColorBI;
    }
    else
    {
        Light2R = BackColorR;
        Light2G = BackColorG;
        Light2B = BackColorB;
    }
    Light1R_ = Light1R;
    Light1G_ = Light1G;
    Light1B_ = Light1B;
    Light2R_ = Light2R;
    Light2G_ = Light2G;
    Light2B_ = Light2B;

    LightDistance0P_ = LightDistance0;
    LightDistance0N_ = 0 - LightDistance0;
    LightDistance1_ = LightDistance1;
    LightDistance2_ = LightDistance2;

    LightAngleHradP = ((double)(LightAngleH)) * M_PI / 180.0;
    LightAngleHradN = ((double)(0 - LightAngleH)) * M_PI / 180.0;
    LightAngleVradP = ((double)(LightAngleV)) * M_PI / 180.0;
    LightAngleVradN = ((double)(0 - LightAngleV)) * M_PI / 180.0;

    LightDistX = sin(LightAngleHradP) * cos(LightAngleVradP);
    LightDistY = (0.0 - cos(LightAngleHradP)) * cos(LightAngleVradP);
    LightDistZ = sin(LightAngleVradP);
    LightDistXYZ = sqrt((LightDistX * LightDistX) + (LightDistY * LightDistY) + (LightDistZ * LightDistZ));

    LightVectorX = sin(LightAngleHradP) * cos(LightAngleVradP);
    LightVectorY = cos(LightAngleHradP) * cos(LightAngleVradP);
    LightVectorZ = sin(LightAngleVradP);
}
