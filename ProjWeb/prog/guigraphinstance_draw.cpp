#include "guigraphinstance.h"

void GuiGraphInstance::CalcColor(uchar &R, uchar &G, uchar &B, int X, int Y, int Z, double LightAngle)
{
    if (LightMode > 0)
    {
        int R0 = R;
        int G0 = G;
        int B0 = B;
        double Dist1 = 0;
        double Dist2;


        /*R0 = 255;
        G0 = 0;
        B0 = 0;
        Light2R = 0;
        Light2G = 255;
        Light2B = 0;
        Light2R_ = 0;
        Light2G_ = 255;
        Light2B_ = 0;
        Light1R = 0;
        Light1G = 0;
        Light1B = 255;
        Light1R_ = 0;
        Light1G_ = 0;
        Light1B_ = 255;*/



        if (LightMode == 1)
        {
            double DX = X - ZeroX;
            double DY = Y - ZeroY;
            double DZ = Z - ZeroZ;

            Dist1 = ((LightDistX * DX) + (LightDistY * DY) + (LightDistZ * DZ)) / LightDistXYZ;
        }

        if (LightMode == 2)
        {
            double SurfaceAngle = LightAngle * 180.0 / M_PI;
            Dist1 = 0.0 - SurfaceAngle + 90.0;
        }

        Dist2 = 0.0 - Dist1;

        if (LightDistance1 > 0)
        {
            if ((Dist1 > LightDistance0P_) && (Dist1 < (LightDistance1_ + LightDistance0P_)))
            {
                double Prop = (Dist1 - LightDistance0P_) / LightDistance1_;
                double Prop0 = 1.0 - Prop;
                R0 = (Prop0 * ((double)R0)) + (Prop * Light1R_);
                G0 = (Prop0 * ((double)G0)) + (Prop * Light1G_);
                B0 = (Prop0 * ((double)B0)) + (Prop * Light1B_);
            }
            else
            {
                if (Dist1 >= (LightDistance1_ + LightDistance0P_))
                {
                    R0 = Light1R;
                    G0 = Light1G;
                    B0 = Light1B;
                }
            }
        }
        if (LightDistance2 > 0)
        {
            if ((Dist2 > LightDistance0N_) && (Dist2 < (LightDistance2_ + LightDistance0N_)))
            {
                double Prop = (Dist2 - LightDistance0N_) / (LightDistance2_);
                double Prop0 = 1.0 - Prop;
                R0 = (Prop0 * ((double)R0)) + (Prop * Light2R_);
                G0 = (Prop0 * ((double)G0)) + (Prop * Light2G_);
                B0 = (Prop0 * ((double)B0)) + (Prop * Light2B_);
            }
            else
            {
                if (Dist2 >= (LightDistance2_ + LightDistance0N_))
                {
                    R0 = Light2R;
                    G0 = Light2G;
                    B0 = Light2B;
                }
            }
        }

        /*double Dist000 = sqrt(DX * DX + DY * DY + DZ * DZ);
        if ((Dist000 >= 98.0) && (Dist000 <= 102.0))
        {
            R0 = 255;
            G0 = 0;
            B0 = 0;
        }
        else
        {
            R0 = 0;
            G0 = 0;
            B0 = 255;
        }

        if ((Dist1 >= 98.0) && (Dist1 <= 102.0))
        {
            G0 = 255;
        }*/


        R = Range(R0, 0, 255);
        G = Range(G0, 0, 255);
        B = Range(B0, 0, 255);
    }
}

void GuiGraphInstance::DrawUpdateRepaint(int X, int Y, int MarginX, int MarginY)
{
    if (RepaintX1 > (X - MarginX)) { RepaintX1 = (X - MarginX); }
    if (RepaintX2 < (X + MarginX)) { RepaintX2 = (X + MarginX); }
    if (RepaintY1 > (Y - MarginY)) { RepaintY1 = (Y - MarginY); }
    if (RepaintY2 < (Y + MarginY)) { RepaintY2 = (Y + MarginY); }
}

void GuiGraphInstance::DrawPoint(int X, int Y, int Z, uchar R, uchar G, uchar B, double LightAngle)
{
    int DrawX = X + ZeroX;
    int DrawY = ZeroY - Y;
    int DrawZ = Z + ZeroZ;
    uchar R0, G0, B0;

    if ((DrawX >= BoundLP) && (DrawY >= BoundTP) && (DrawX <= BoundRP) && (DrawY <= BoundBP) && (DrawZ >= BoundZMin) && (DrawZ <= BoundZMax))
    {
        DrawUpdateRepaint(DrawX, DrawY, PlotSizeP_Margin, PlotSizeP_Margin);
        int Pos = (DrawY * ImgW) + DrawX;
        int XX, YY, PosX, Pos4X;
        if (InverseDraw1)
        {
            for (YY = 0; YY <= PlotSizeP; YY++)
            {
                for (XX = 0; XX <= PlotSizeP; XX++)
                {
                    if (Mask[XX][YY])
                    {
                        PosX = Pos + (ImgW * (YY)) + XX;
                        if (ImgZ[PosX] < DrawZ)
                        {
                            R0 = R;
                            G0 = G;
                            B0 = B;
                            CalcColor(R0, G0, B0, DrawX + XX, DrawY + YY, DrawZ, LightAngle);
                            ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                        }

                        PosX = Pos + (ImgW * (YY)) - XX - PlotSizeP2;
                        if (ImgZ[PosX] < DrawZ)
                        {
                            R0 = R;
                            G0 = G;
                            B0 = B;
                            CalcColor(R0, G0, B0, DrawX - XX, DrawY + YY, DrawZ, LightAngle);
                            ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                        }

                        PosX = Pos - (ImgW * (YY + PlotSizeP2)) + XX;
                        if (ImgZ[PosX] < DrawZ)
                        {
                            R0 = R;
                            G0 = G;
                            B0 = B;
                            CalcColor(R0, G0, B0, DrawX + XX, DrawY - YY, DrawZ, LightAngle);
                            ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                        }

                        PosX = Pos - (ImgW * (YY + PlotSizeP2)) - XX - PlotSizeP2;
                        if (ImgZ[PosX] < DrawZ)
                        {
                            R0 = R;
                            G0 = G;
                            B0 = B;
                            CalcColor(R0, G0, B0, DrawX - XX, DrawY - YY, DrawZ, LightAngle);
                            ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                        }
                    }
                }
            }
        }
        else
        {
            for (YY = 0; YY <= PlotSizeP; YY++)
            {
                for (XX = 0; XX <= PlotSizeP; XX++)
                {
                    if (Mask[XX][YY])
                    {
                        PosX = Pos + (ImgW * (YY)) + XX;
                        if (ImgZ[PosX] <= DrawZ)
                        {
                            R0 = R;
                            G0 = G;
                            B0 = B;
                            CalcColor(R0, G0, B0, DrawX + XX, DrawY + YY, DrawZ, LightAngle);
                            ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                        }

                        PosX = Pos + (ImgW * (YY)) - XX - PlotSizeP2;
                        if (ImgZ[PosX] <= DrawZ)
                        {
                            R0 = R;
                            G0 = G;
                            B0 = B;
                            CalcColor(R0, G0, B0, DrawX - XX, DrawY + YY, DrawZ, LightAngle);
                            ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                        }

                        PosX = Pos - (ImgW * (YY + PlotSizeP2)) + XX;
                        if (ImgZ[PosX] <= DrawZ)
                        {
                            R0 = R;
                            G0 = G;
                            B0 = B;
                            CalcColor(R0, G0, B0, DrawX + XX, DrawY - YY, DrawZ, LightAngle);
                            ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                        }

                        PosX = Pos - (ImgW * (YY + PlotSizeP2)) - XX - PlotSizeP2;
                        if (ImgZ[PosX] <= DrawZ)
                        {
                            R0 = R;
                            G0 = G;
                            B0 = B;
                            CalcColor(R0, G0, B0, DrawX - XX, DrawY - YY, DrawZ, LightAngle);
                            ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                        }
                    }
                }
            }
        }
    }
}

void GuiGraphInstance::DrawPointT(int X, int Y, int Z, uchar R, uchar G, uchar B)
{
    int DrawX = X + ZeroX;
    int DrawY = ZeroY - Y;
    int DrawZ = Z + ZeroZ;
    uchar R0, G0, B0;

    if ((DrawX >= 0) && (DrawY >= 0) && (DrawX <= ImgW1) && (DrawY <= ImgH1))
    {
        DrawUpdateRepaint(DrawX, DrawY, 0, 0);
        int Pos = (DrawY * ImgW) + DrawX;
        int PosX, Pos4X;
        if (InverseDraw1)
        {
            PosX = Pos;
            if (ImgZ[PosX] < DrawZ)
            {
                R0 = R;
                G0 = G;
                B0 = B;
                ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
            }
        }
        else
        {
            PosX = Pos;
            if (ImgZ[PosX] <= DrawZ)
            {
                R0 = R;
                G0 = G;
                B0 = B;
                ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
            }
        }
    }
}

void GuiGraphInstance::DrawPointH(int X, int Y, int Z, uchar R, uchar G, uchar B, double LightAngle)
{
    int DrawX = X + ZeroX;
    int DrawY = ZeroY - Y;
    int DrawZ = Z + ZeroZ;
    uchar R0, G0, B0;

    if ((DrawX >= BoundLL) && (DrawY >= 0) && (DrawX <= BoundRL) && (DrawY <= ImgH1) && (DrawZ >= BoundZMin) && (DrawZ <= BoundZMax))
    {
        DrawUpdateRepaint(DrawX, DrawY, PlotSizeL_Margin, 0);
        int Pos = (DrawY * ImgW) + DrawX;
        int XX, PosX, Pos4X;
        if (InverseDraw1)
        {
            for (XX = 0 - PlotSizeL - PlotSizeL2; XX <= PlotSizeL; XX++)
            {
                PosX = Pos + XX;
                if (ImgZ[PosX] < DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX + XX, DrawY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
        }
        else
        {
            for (XX = 0 - PlotSizeL - PlotSizeL2; XX <= PlotSizeL; XX++)
            {
                PosX = Pos + XX;
                if (ImgZ[PosX] <= DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX + XX, DrawY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
        }
    }
}

void GuiGraphInstance::DrawPointV(int X, int Y, int Z, uchar R, uchar G, uchar B, double LightAngle)
{
    int DrawX = X + ZeroX;
    int DrawY = ZeroY - Y;
    int DrawZ = Z + ZeroZ;
    uchar R0, G0, B0;

    if ((DrawX >= 0) && (DrawY >= BoundTL) && (DrawX <= ImgW1) && (DrawY <= BoundBL) && (DrawZ >= BoundZMin) && (DrawZ <= BoundZMax))
    {
        DrawUpdateRepaint(DrawX, DrawY, 0, PlotSizeL_Margin);
        int Pos = (DrawY * ImgW) + DrawX;
        int YY, PosX, Pos4X;
        if (InverseDraw1)
        {
            for (YY = 0 - PlotSizeL - PlotSizeL2; YY <= PlotSizeL; YY++)
            {
                PosX = Pos + (ImgW * YY);
                if (ImgZ[PosX] < DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX, DrawY + YY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
        }
        else
        {
            for (YY = 0 - PlotSizeL - PlotSizeL2; YY <= PlotSizeL; YY++)
            {
                PosX = Pos + (ImgW * YY);
                if (ImgZ[PosX] <= DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX, DrawY + YY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
        }
    }
}

void GuiGraphInstance::DrawPointD1(int X, int Y, int Z, uchar R, uchar G, uchar B, double LightAngle)
{
    int DrawX = X + ZeroX;
    int DrawY = ZeroY - Y;
    int DrawZ = Z + ZeroZ;
    uchar R0, G0, B0;

    if ((DrawX >= BoundLL) && (DrawY >= BoundTL) && (DrawX <= BoundRL) && (DrawY <= BoundBL) && (DrawZ >= BoundZMin) && (DrawZ <= BoundZMax))
    {
        DrawUpdateRepaint(DrawX, DrawY, PlotSizeL_Margin, PlotSizeL_Margin);
        int Pos = (DrawY * ImgW) + DrawX;
        int XX, PosX, Pos4X;
        if (InverseDraw1)
        {
            for (XX = 0 - PlotSizeDiagonal1; XX <= PlotSizeDiagonal2; XX++)
            {
                PosX = Pos + (ImgW * XX) + XX;
                if (ImgZ[PosX] < DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX + XX, DrawY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
            for (XX = 0 - PlotSizeDiagonal3; XX <= PlotSizeDiagonal4; XX++)
            {
                PosX = Pos + (ImgW * XX) + XX - 1;
                if (ImgZ[PosX] < DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX + XX, DrawY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
        }
        else
        {
            for (XX = 0 - PlotSizeDiagonal1; XX <= PlotSizeDiagonal2; XX++)
            {
                PosX = Pos + (ImgW * XX) + XX;
                if (ImgZ[PosX] <= DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX + XX, DrawY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
            for (XX = 0 - PlotSizeDiagonal3; XX <= PlotSizeDiagonal4; XX++)
            {
                PosX = Pos + (ImgW * XX) + XX - 1;
                if (ImgZ[PosX] <= DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX + XX, DrawY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
        }
    }
}

void GuiGraphInstance::DrawPointD2(int X, int Y, int Z, uchar R, uchar G, uchar B, double LightAngle)
{
    int DrawX = X + ZeroX;
    int DrawY = ZeroY - Y;
    int DrawZ = Z + ZeroZ;
    uchar R0, G0, B0;

    if ((DrawX >= BoundLL) && (DrawY >= BoundTL) && (DrawX <= BoundRL) && (DrawY <= BoundBL) && (DrawZ >= BoundZMin) && (DrawZ <= BoundZMax))
    {
        DrawUpdateRepaint(DrawX, DrawY, PlotSizeL_Margin, PlotSizeL_Margin);
        int Pos = (DrawY * ImgW) + DrawX;
        int XX, PosX, Pos4X;
        if (InverseDraw1)
        {
            for (XX = 0 - PlotSizeDiagonal1; XX <= PlotSizeDiagonal2; XX++)
            {
                PosX = Pos + (ImgW * XX) - XX;
                if (ImgZ[PosX] < DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX + XX, DrawY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
            for (XX = 0 - PlotSizeDiagonal3; XX <= PlotSizeDiagonal4; XX++)
            {
                PosX = Pos + (ImgW * XX) - XX + 1;
                if (ImgZ[PosX] < DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX + XX, DrawY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
        }
        else
        {
            for (XX = 0 - PlotSizeDiagonal1; XX <= PlotSizeDiagonal2; XX++)
            {
                PosX = Pos + (ImgW * XX) - XX;
                if (ImgZ[PosX] <= DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX + XX, DrawY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
            for (XX = 0 - PlotSizeDiagonal3; XX <= PlotSizeDiagonal4; XX++)
            {
                PosX = Pos + (ImgW * XX) - XX + 1;
                if (ImgZ[PosX] <= DrawZ)
                {
                    R0 = R;
                    G0 = G;
                    B0 = B;
                    CalcColor(R0, G0, B0, DrawX + XX, DrawY, DrawZ, LightAngle);
                    ImgZ[PosX] = DrawZ; Pos4X = PosX << 2; ImgRaw[Pos4X + 0] = R0; ImgRaw[Pos4X + 1] = G0; ImgRaw[Pos4X + 2] = B0;
                }
            }
        }
    }
}

void GuiGraphInstance::DrawLine(int X0, int Y0, int Z0, int X1, int Y1, int Z1, uchar R, uchar G, uchar B, double LightAngle)
{
    int DrawX0_ = X0 + ZeroX;
    int DrawY0_ = ZeroY - Y0;
    int DrawX1_ = X1 + ZeroX;
    int DrawY1_ = ZeroY - Y1;

    if ((DrawX0_ < 0) && (DrawX1_ < 0)) { return; }
    if ((DrawY0_ < 0) && (DrawY1_ < 0)) { return; }
    if ((DrawX0_ > ImgW1) && (DrawX1_ > ImgW1)) { return; }
    if ((DrawY0_ > ImgH1) && (DrawY1_ > ImgH1)) { return; }

    int Temp;
    double dx0,  dy0,  dz0;
    double dx,   dy,   dz;
    double tempx,tempy,tempz;
    double x,    y,    z;
    double x1,   y1,   z1;
    double rob;
    x1 = X0;
    y1 = Y0;
    z1 = Z0;

    dx0 = X1 - X0;
    dy0 = Y1 - Y0;
    dz0 = Z1 - Z0;

    if (X0 > X1) { Temp = X0; X0 = X1; X1 = Temp; }
    if (Y0 > Y1) { Temp = Y0; Y0 = Y1; Y1 = Temp; }
    if (Z0 > Z1) { Temp = Z0; Z0 = Z1; Z1 = Temp; }
    dx = X1 - X0;
    dy = Y1 - Y0;
    dz = Z1 - Z0;

    int DrawLineMode = 0;
    if (dx > (dy * 1.7321))
    {
        DrawLineMode = 1;
        rob = dx;
    }
    else
    {
        if (dy > (dx * 1.7321))
        {
            DrawLineMode = 2;
            rob = dy;
        }
        else
        {
            if (dx > dy)
            {
                rob = dx;
            }
            else
            {
                rob = dy;
            }
            if ((dx0 * dy0) >= 0)
            {
                DrawLineMode = 3;
            }
            else
            {
                DrawLineMode = 4;
            }
        }
    }

    int rob_ = rob;
    (dx != 0) ? tempx = (dx0 / rob) : tempx = 0;
    (dy != 0) ? tempy = (dy0 / rob) : tempy = 0;
    (dz != 0) ? tempz = (dz0 / rob) : tempz = 0;

    switch (DrawLineMode)
    {
        case 1:
            while (rob_ != 0)
            {
                x1 = x1 + tempx;
                y1 = y1 + tempy;
                z1 = z1 + tempz;
                x = floor(x1 + 0.5);
                y = floor(y1 + 0.5);
                z = floor(z1 + 0.5);
                DrawPointV(x, y, z, R, G, B, LightAngle);
                rob_--;
            }
            return;
        case 2:
            while (rob_ != 0)
            {
                x1 = x1 + tempx;
                y1 = y1 + tempy;
                z1 = z1 + tempz;
                x = floor(x1 + 0.5);
                y = floor(y1 + 0.5);
                z = floor(z1 + 0.5);
                DrawPointH(x, y, z, R, G, B, LightAngle);
                rob_--;
            }
            return;
        case 3:
            while (rob_ != 0)
            {
                x1 = x1 + tempx;
                y1 = y1 + tempy;
                z1 = z1 + tempz;
                x = floor(x1 + 0.5);
                y = floor(y1 + 0.5);
                z = floor(z1 + 0.5);
                DrawPointD1(x, y, z, R, G, B, LightAngle);
                rob_--;
            }
            return;
        case 4:
            while (rob_ != 0)
            {
                x1 = x1 + tempx;
                y1 = y1 + tempy;
                z1 = z1 + tempz;
                x = floor(x1 + 0.5);
                y = floor(y1 + 0.5);
                z = floor(z1 + 0.5);
                DrawPointD2(x, y, z, R, G, B, LightAngle);
                rob_--;
            }
            return;
    }
}

void GuiGraphInstance::DrawLine0(int X0, int Y0, int Z0, int X1, int Y1, int Z1, int R0, int G0, int B0, int R1, int G1, int B1, double LightAngle)
{
    int DrawX0_ = X0 + ZeroX;
    int DrawY0_ = ZeroY - Y0;
    int DrawX1_ = X1 + ZeroX;
    int DrawY1_ = ZeroY - Y1;

    if ((DrawX0_ < 0) && (DrawX1_ < 0)) { return; }
    if ((DrawY0_ < 0) && (DrawY1_ < 0)) { return; }
    if ((DrawX0_ > ImgW1) && (DrawX1_ > ImgW1)) { return; }
    if ((DrawY0_ > ImgH1) && (DrawY1_ > ImgH1)) { return; }

    int Temp;
    double dx0,   dy0,   dz0,   dr0,   dg0,   db0;
    double dx,    dy,    dz,    dr,    dg,    db;
    double tempx, tempy, tempz, tempr, tempg, tempb;
    double x,     y,     z,     r,     g,     b;
    double x1,    y1,    z1,    r1,    g1,    b1;
    double rob;
    x1 = X0;
    y1 = Y0;
    z1 = Z0;
    r1 = R0;
    g1 = G0;
    b1 = B0;

    dx0 = X1 - X0;
    dy0 = Y1 - Y0;
    dz0 = Z1 - Z0;
    dr0 = R1 - R0;
    dg0 = G1 - G0;
    db0 = B1 - B0;

    if (X0 > X1) { Temp = X0; X0 = X1; X1 = Temp; }
    if (Y0 > Y1) { Temp = Y0; Y0 = Y1; Y1 = Temp; }
    if (Z0 > Z1) { Temp = Z0; Z0 = Z1; Z1 = Temp; }
    if (R0 > R1) { Temp = R0; R0 = R1; R1 = Temp; }
    if (G0 > G1) { Temp = G0; G0 = G1; G1 = Temp; }
    if (B0 > B1) { Temp = B0; B0 = B1; B1 = Temp; }
    dx = X1 - X0;
    dy = Y1 - Y0;
    dz = Z1 - Z0;
    dr = R1 - R0;
    dg = G1 - G0;
    db = B1 - B0;

    int DrawLineMode = 0;
    if (dx > (dy * 2))
    {
        DrawLineMode = 1;
        rob = dx;
    }
    else
    {
        if (dy > (dx * 2))
        {
            DrawLineMode = 2;
            rob = dy;
        }
        else
        {
            if (dx > dy)
            {
                rob = dx;
            }
            else
            {
                rob = dy;
            }
            if ((dx0 * dy0) >= 0)
            {
                DrawLineMode = 3;
            }
            else
            {
                DrawLineMode = 4;
            }
        }
    }

    int rob_ = rob;
    (dx != 0) ? tempx = (dx0 / rob) : tempx = 0;
    (dy != 0) ? tempy = (dy0 / rob) : tempy = 0;
    (dz != 0) ? tempz = (dz0 / rob) : tempz = 0;
    (dr != 0) ? tempr = (dr0 / rob) : tempr = 0;
    (dg != 0) ? tempg = (dg0 / rob) : tempg = 0;
    (db != 0) ? tempb = (db0 / rob) : tempb = 0;
    switch (DrawLineMode)
    {
        case 1:
            while (rob_ != 0)
            {
                x1 = x1 + tempx;
                y1 = y1 + tempy;
                z1 = z1 + tempz;
                r1 = r1 + tempr;
                g1 = g1 + tempg;
                b1 = b1 + tempb;
                x = floor(x1 + 0.5);
                y = floor(y1 + 0.5);
                z = floor(z1 + 0.5);
                r = floor(r1 + 0.5);
                g = floor(g1 + 0.5);
                b = floor(b1 + 0.5);
                DrawPointV(x, y, z, r, g, b, LightAngle);
                rob_--;
            }
            return;
        case 2:
            while (rob_ != 0)
            {
                x1 = x1 + tempx;
                y1 = y1 + tempy;
                z1 = z1 + tempz;
                r1 = r1 + tempr;
                g1 = g1 + tempg;
                b1 = b1 + tempb;
                x = floor(x1 + 0.5);
                y = floor(y1 + 0.5);
                z = floor(z1 + 0.5);
                r = floor(r1 + 0.5);
                g = floor(g1 + 0.5);
                b = floor(b1 + 0.5);
                DrawPointH(x, y, z, r, g, b, LightAngle);
                rob_--;
            }
            return;
        case 3:
            while (rob_ != 0)
            {
                x1 = x1 + tempx;
                y1 = y1 + tempy;
                z1 = z1 + tempz;
                r1 = r1 + tempr;
                g1 = g1 + tempg;
                b1 = b1 + tempb;
                x = floor(x1 + 0.5);
                y = floor(y1 + 0.5);
                z = floor(z1 + 0.5);
                r = floor(r1 + 0.5);
                g = floor(g1 + 0.5);
                b = floor(b1 + 0.5);
                DrawPointD1(x, y, z, r, g, b, LightAngle);
                rob_--;
            }
            return;
        case 4:
            while (rob_ != 0)
            {
                x1 = x1 + tempx;
                y1 = y1 + tempy;
                z1 = z1 + tempz;
                r1 = r1 + tempr;
                g1 = g1 + tempg;
                b1 = b1 + tempb;
                x = floor(x1 + 0.5);
                y = floor(y1 + 0.5);
                z = floor(z1 + 0.5);
                r = floor(r1 + 0.5);
                g = floor(g1 + 0.5);
                b = floor(b1 + 0.5);
                DrawPointD2(x, y, z, r, g, b, LightAngle);
                rob_--;
            }
            return;
    }
}

void GuiGraphInstance::CalcTriangleAngle(int X1, int Y1, int Z1, int X2, int Y2, int Z2, int X3, int Y3, int Z3, double &LightAngle)
{
    /*
          | Y1 Z1 1 |      | X1 Z1 1 |      | X1 Y1 1 |      | X1 Y1 Z1 |
      A = | Y2 Z2 1 |  B = | X2 Z2 1 |  C = | X2 Y2 1 |  D = | X2 Y2 Z2 |
          | Y3 Z3 1 |      | X3 Z3 1 |      | X3 Y3 1 |      | X3 Y3 Z3 |

          A*X - B*Y + C*Z - D = 0;
     */
    /*double A = Det3(Y1, Z1, 1, Y2, Z2, 1, Y3, Z3, 1);
    double B = 0 - Det3(X1, Z1, 1, X2, Z2, 1, X3, Z3, 1);
    double C = Det3(X1, Y1, 1, X2, Y2, 1, X3, Y3, 1);*/


    int Len12 = ((X1 - X2) * (X1 - X2)) + ((Y1 - Y2) * (Y1 - Y2)) + ((Z1 - Z2) * (Z1 - Z2));
    int Len23 = ((X2 - X3) * (X2 - X3)) + ((Y2 - Y3) * (Y2 - Y3)) + ((Z2 - Z3) * (Z2 - Z3));
    int Len31 = ((X3 - X1) * (X3 - X1)) + ((Y3 - Y1) * (Y3 - Y1)) + ((Z3 - Z1) * (Z3 - Z1));

    double Vec1X, Vec1Y, Vec1Z;
    double Vec2X, Vec2Y, Vec2Z;

    if ((Len12 <= Len23) && (Len12 <= Len31))
    {
        Vec1X = X1 - X3; Vec1Y = Y1 - Y3; Vec1Z = Z1 - Z3;
        Vec2X = X2 - X3; Vec2Y = Y2 - Y3; Vec2Z = Z2 - Z3;
    }
    else
    {
        if ((Len23 <= Len12) && (Len23 <= Len31))
        {
            Vec1X = X2 - X1; Vec1Y = Y2 - Y1; Vec1Z = Z2 - Z1;
            Vec2X = X3 - X1; Vec2Y = Y3 - Y1; Vec2Z = Z3 - Z1;
        }
        else
        {
            Vec1X = X3 - X2; Vec1Y = Y3 - Y2; Vec1Z = Z3 - Z2;
            Vec2X = X1 - X2; Vec2Y = Y1 - Y2; Vec2Z = Z1 - Z2;
        }
    }

    double TriX = Vec1Y * Vec2Z - Vec1Z * Vec2Y;
    double TriY = Vec1Z * Vec2X - Vec1X * Vec2Z;
    double TriZ = Vec1X * Vec2Y - Vec1Y * Vec2X;

    LightAngle = VectorAngle(TriX, TriY, TriZ, LightVectorX, LightVectorY, LightVectorZ);
    if (LightAngle > M_PI_2)
    {
        if (VectorAngle(TriX, TriY, TriZ, 0.0, 0.0, -1.0) < M_PI_2)
        {
            LightAngle = M_PI - LightAngle;
        }
    }
    else
    {
        if (VectorAngle(TriX, TriY, TriZ, 0.0, 0.0, 1.0) > M_PI_2)
        {
            LightAngle = M_PI - LightAngle;
        }
    }
}

void GuiGraphInstance::DrawHalfTriangle(int X0, int Y0, int Z0, int X1, int X2, int Y_, int Z1, int Z2, uchar R0, uchar G0, uchar B0, double LightAngle)
{
    int DrawX0 = X0 + ZeroX;
    int DrawY0 = ZeroY - Y0;
    int DrawX1 = X1 + ZeroX;
    int DrawX2 = X2 + ZeroX;
    int DrawY_ = ZeroY - Y_;

    int X, Y, Z, YI1, YI2, XI1, XI2, ZI1, ZI2;
    double DX1, DX2, DZ1, DZ2, DY, DYX, A1, A2, A1Z, A2Z, ZProp;
    int XDelta, YDelta, ZDelta;

    if (DrawX1 > DrawX2)
    {
        X = DrawX1;
        DrawX1 = DrawX2;
        DrawX2 = X;
        X = Z1;
        Z1 = Z2;
        Z2 = X;
    }

    DX1 = DrawX1 - DrawX0;
    DX2 = DrawX2 - DrawX0;
    DY = DrawY0 - DrawY_;
    DZ1 = Z1 - Z0;
    DZ2 = Z2 - Z0;
    A1 = DX1 / DY;
    A2 = DX2 / DY;
    A1Z = DZ1 / DY;
    A2Z = DZ2 / DY;

    if (DrawY_ < DrawY0)
    {
        YI1 = DrawY_;
        YI2 = DrawY0;
    }
    else
    {
        YI1 = DrawY0;
        YI2 = DrawY_;
    }

    YDelta = YI2 - YI1;
    if (YDelta < 1)
    {
        YDelta = 1;
    }
    DrawUpdateRepaint(XI1, YI1, 0, 0);
    DrawUpdateRepaint(XI2, YI2, 0, 0);
    for (Y = YI1; Y <= YI2; Y++)
    {
        DYX = (DrawY_ - Y);
        XI1 = round(DYX * A1) + DrawX1;
        XI2 = round(DYX * A2) + DrawX2;
        ZI1 = round(DYX * A1Z) + Z1;
        ZI2 = round(DYX * A2Z) + Z2;
        XDelta = XI2 - XI1;
        ZDelta = ZI2 - ZI1;
        ZProp = (double)ZDelta / (double)XDelta;
        if (XDelta < 1)
        {
            XDelta = 1;
        }
        if (InverseDraw1)
        {
            for (X = XI1; X <= XI2; X++)
            {
                if ((X >= 0) && (Y >= 0) && (X <= ImgW1) && (Y <= ImgH1))
                {
                    Z = ZI1 + ((X - XI1) * ZProp);
                    if ((Z >= BoundZMin) && (Z <= BoundZMax))
                    {
                        int Pos = (Y * ImgW) + X;
                        if (ImgZ[Pos] < Z)
                        {
                            int Pos4X = Pos << 2;
                            uchar R0_ = R0;
                            uchar G0_ = G0;
                            uchar B0_ = B0;
                            CalcColor(R0_, G0_, B0_, X, Y, Z, LightAngle);
                            ImgZ[Pos] = Z;
                            ImgRaw[Pos4X + 0] = R0_;
                            ImgRaw[Pos4X + 1] = G0_;
                            ImgRaw[Pos4X + 2] = B0_;
                        }
                    }
                }
            }
        }
        else
        {
            for (X = XI1; X <= XI2; X++)
            {
                if ((X >= 0) && (Y >= 0) && (X <= ImgW1) && (Y <= ImgH1))
                {
                    Z = ZI1 + ((X - XI1) * ZProp);
                    if ((Z >= BoundZMin) && (Z <= BoundZMax))
                    {
                        int Pos = (Y * ImgW) + X;
                        if (ImgZ[Pos] <= Z)
                        {
                            int Pos4X = Pos << 2;
                            uchar R0_ = R0;
                            uchar G0_ = G0;
                            uchar B0_ = B0;
                            CalcColor(R0_, G0_, B0_, X, Y, Z, LightAngle);
                            ImgZ[Pos] = Z;
                            ImgRaw[Pos4X + 0] = R0_;
                            ImgRaw[Pos4X + 1] = G0_;
                            ImgRaw[Pos4X + 2] = B0_;
                        }
                    }
                }
            }
        }
    }
}

void GuiGraphInstance::DrawTriangle(int X1, int Y1, int Z1, int X2, int Y2, int Z2, int X3, int Y3, int Z3, uchar R0, uchar G0, uchar B0, double LightAngle)
{
    int XMin;
    int XMax;
    int YMin;
    int YMax;

    double F1, F2, F3, F3Z, F4, F4Z;

    int P0X_;
    int P0X__;
    int P0Y_;
    int P0Z_;
    int P0Z__;
    int P1X_;
    int P1Y_;
    int P1Z_;
    int P2X_;
    int P2Y_;
    int P2Z_;

    XMin = X1;
    XMax = X1;
    if (XMin > X2) { XMin = X2; }
    if (XMax < X2) { XMax = X2; }
    if (XMin > X3) { XMin = X3; }
    if (XMax < X3) { XMax = X3; }

    YMin = Y1;
    YMax = Y1;
    if (YMin > Y2) { YMin = Y2; }
    if (YMax < Y2) { YMax = Y2; }
    if (YMin > Y3) { YMin = Y3; }
    if (YMax < Y3) { YMax = Y3; }

    P0Y_ = YMin;

    if ((Y1 > YMin) && (Y1 < YMax))
    {
        P0X_ = X1; P0Y_ = Y1; P0Z_ = Z1;
        if (Y2 == YMin)
        {
            P1X_ = X2; P1Y_ = Y2; P1Z_ = Z2;
            P2X_ = X3; P2Y_ = Y3; P2Z_ = Z3;
        }
        else
        {
            P1X_ = X3; P1Y_ = Y3; P1Z_ = Z3;
            P2X_ = X2; P2Y_ = Y2; P2Z_ = Z2;
        }
    }
    else
    {
        if ((Y2 > YMin) && (Y2 < YMax))
        {
            P0X_ = X2; P0Y_ = Y2; P0Z_ = Z2;
            if (Y3 == YMin)
            {
                P1X_ = X3; P1Y_ = Y3; P1Z_ = Z3;
                P2X_ = X1; P2Y_ = Y1; P2Z_ = Z1;
            }
            else
            {
                P1X_ = X1; P1Y_ = Y1; P1Z_ = Z1;
                P2X_ = X3; P2Y_ = Y3; P2Z_ = Z3;
            }
        }
        else
        {
            if ((Y3 > YMin) && (Y3 < YMax))
            {
                P0X_ = X3; P0Y_ = Y3; P0Z_ = Z3;
                if (Y1 == YMin)
                {
                    P1X_ = X1; P1Y_ = Y1; P1Z_ = Z1;
                    P2X_ = X2; P2Y_ = Y2; P2Z_ = Z2;
                }
                else
                {
                    P1X_ = X2; P1Y_ = Y2; P1Z_ = Z2;
                    P2X_ = X1; P2Y_ = Y1; P2Z_ = Z1;
                }
            }
        }
    }



    if ((P0Y_ > YMin) && (P0Y_ < YMax))
    {
        F1 = P0Y_ - P1Y_;
        F2 = P2Y_ - P1Y_;

        F3 = P2X_ - P1X_;
        F3Z = P2Z_ - P1Z_;
        F4 = F3 * (F1 / F2);
        F4Z = F3Z * (F1 / F2);

        P0X__ = P1X_ + F4;
        P0Z__ = P1Z_ + F4Z;

        if (PlotSurface)
        {
            DrawHalfTriangle(P1X_, P1Y_, P1Z_, P0X_, P0X__, P0Y_, P0Z_, P0Z__, R0, G0, B0, LightAngle);
            DrawHalfTriangle(P2X_, P2Y_, P2Z_, P0X_, P0X__, P0Y_, P0Z_, P0Z__, R0, G0, B0, LightAngle);
        }
    }
    else
    {
        if (Y1 == Y2)
        {
            if (PlotSurface)
            {
                DrawHalfTriangle(X3, Y3, Z3, X1, X2, Y1, Z1, Z2, R0, G0, B0, LightAngle);
            }
        }
        if (Y2 == Y3)
        {
            if (PlotSurface)
            {
                DrawHalfTriangle(X1, Y1, Z1, X2, X3, Y2, Z2, Z3, R0, G0, B0, LightAngle);
            }
        }
        if (Y3 == Y1)
        {
            if (PlotSurface)
            {
                DrawHalfTriangle(X2, Y2, Z2, X3, X1, Y3, Z3, Z1, R0, G0, B0, LightAngle);
            }
        }
    }
}

void GuiGraphInstance::DrawHalfTriangle0(int X0, int Y0, int Z0, int X1, int X2, int Y_, int Z1, int Z2, uchar R0, uchar G0, uchar B0, uchar R1, uchar G1, uchar B1, uchar R2, uchar G2, uchar B2, double LightAngle)
{
    int ColorR0 = R0;
    int ColorG0 = G0;
    int ColorB0 = B0;
    int ColorR1 = R1;
    int ColorG1 = G1;
    int ColorB1 = B1;
    int ColorR2 = R2;
    int ColorG2 = G2;
    int ColorB2 = B2;

    int DrawX0 = X0 + ZeroX;
    int DrawY0 = ZeroY - Y0;
    int DrawX1 = X1 + ZeroX;
    int DrawX2 = X2 + ZeroX;
    int DrawY_ = ZeroY - Y_;

    int X, Y, Z, YI1, YI2, XI1, XI2, ZI1, ZI2;
    double DX1, DX2, DZ1, DZ2, DY, DYX, A1, A2, A1Z, A2Z, ZProp;
    int ColorR, ColorG, ColorB, YProp, YProp0, XProp, XProp0, XDelta, YDelta, ZDelta;
    int ColorRW1, ColorGW1, ColorBW1;
    int ColorRW2, ColorGW2, ColorBW2;

    if (DrawX1 > DrawX2)
    {
        X = DrawX1;
        DrawX1 = DrawX2;
        DrawX2 = X;
        X = Z1;
        Z1 = Z2;
        Z2 = X;
        X = ColorR1;
        ColorR1 = ColorR2;
        ColorR2 = X;
        X = ColorG1;
        ColorG1 = ColorG2;
        ColorG2 = X;
        X = ColorB1;
        ColorB1 = ColorB2;
        ColorB2 = X;
    }

    DX1 = DrawX1 - DrawX0;
    DX2 = DrawX2 - DrawX0;
    DZ1 = Z1 - Z0;
    DZ2 = Z2 - Z0;
    DY = DrawY0 - DrawY_;
    A1 = DX1 / DY;
    A2 = DX2 / DY;
    A1Z = DZ1 / DY;
    A2Z = DZ2 / DY;

    if (DrawY_ < DrawY0)
    {
        YI1 = DrawY_;
        YI2 = DrawY0;
    }
    else
    {
        YI1 = DrawY0;
        YI2 = DrawY_;
    }

    YDelta = YI2 - YI1;
    if (YDelta < 1)
    {
        YDelta = 1;
    }
    DrawUpdateRepaint(XI1, YI1, 0, 0);
    DrawUpdateRepaint(XI2, YI2, 0, 0);
    for (Y = YI1; Y <= YI2; Y++)
    {
        DYX = (DrawY_ - Y);
        XI1 = round(DYX * A1) + DrawX1;
        XI2 = round(DYX * A2) + DrawX2;
        ZI1 = round(DYX * A1Z) + Z1;
        ZI2 = round(DYX * A2Z) + Z2;

        if (DrawY_ < DrawY0)
        {
            YProp = (((Y - YI1) * 100) / (YDelta));
        }
        else
        {
            YProp = (((YI2 - Y) * 100) / (YDelta));
        }
        YProp0 = 100 - YProp;
        XDelta = XI2 - XI1;
        ZDelta = ZI2 - ZI1;
        ZProp = (double)ZDelta / (double)XDelta;
        if (XDelta < 1)
        {
            XDelta = 1;
        }
        if (InverseDraw1)
        {
            for (X = XI1; X <= XI2; X++)
            {
                if ((X >= 0) && (Y >= 0) && (X <= ImgW1) && (Y <= ImgH1))
                {
                    Z = ZI1 + ((X - XI1) * ZProp);
                    if ((Z >= BoundZMin) && (Z <= BoundZMax))
                    {
                        int Pos = (Y * ImgW) + X;
                        if (ImgZ[Pos] < Z)
                        {
                            XProp = ((X - XI1) * 100) / XDelta;
                            XProp0 = 100 - XProp;

                            ColorRW1 = ((ColorR1 * YProp0) + (ColorR0 * YProp)) / 100;
                            ColorGW1 = ((ColorG1 * YProp0) + (ColorG0 * YProp)) / 100;
                            ColorBW1 = ((ColorB1 * YProp0) + (ColorB0 * YProp)) / 100;

                            ColorRW2 = ((ColorR2 * YProp0) + (ColorR0 * YProp)) / 100;
                            ColorGW2 = ((ColorG2 * YProp0) + (ColorG0 * YProp)) / 100;
                            ColorBW2 = ((ColorB2 * YProp0) + (ColorB0 * YProp)) / 100;

                            ColorR = ((ColorRW1 * XProp0) + (ColorRW2) * XProp) / 100;
                            ColorG = ((ColorGW1 * XProp0) + (ColorGW2) * XProp) / 100;
                            ColorB = ((ColorBW1 * XProp0) + (ColorBW2) * XProp) / 100;

                            uchar ColorR_ = Range(ColorR, 0, 255);
                            uchar ColorG_ = Range(ColorG, 0, 255);
                            uchar ColorB_ = Range(ColorB, 0, 255);

                            int Pos4X = Pos << 2;
                            CalcColor(ColorR_, ColorG_, ColorB_, X, Y, Z, LightAngle);
                            ImgZ[Pos] = Z;
                            ImgRaw[Pos4X + 0] = ColorR_;
                            ImgRaw[Pos4X + 1] = ColorG_;
                            ImgRaw[Pos4X + 2] = ColorB_;
                        }
                    }
                }
            }
        }
        else
        {
            for (X = XI1; X <= XI2; X++)
            {
                if ((X >= 0) && (Y >= 0) && (X <= ImgW1) && (Y <= ImgH1))
                {
                    Z = ZI1 + ((X - XI1) * ZProp);
                    if ((Z >= BoundZMin) && (Z <= BoundZMax))
                    {
                        int Pos = (Y * ImgW) + X;
                        if (ImgZ[Pos] <= Z)
                        {
                            XProp = ((X - XI1) * 100) / XDelta;
                            XProp0 = 100 - XProp;

                            ColorRW1 = ((ColorR1 * YProp0) + (ColorR0 * YProp)) / 100;
                            ColorGW1 = ((ColorG1 * YProp0) + (ColorG0 * YProp)) / 100;
                            ColorBW1 = ((ColorB1 * YProp0) + (ColorB0 * YProp)) / 100;

                            ColorRW2 = ((ColorR2 * YProp0) + (ColorR0 * YProp)) / 100;
                            ColorGW2 = ((ColorG2 * YProp0) + (ColorG0 * YProp)) / 100;
                            ColorBW2 = ((ColorB2 * YProp0) + (ColorB0 * YProp)) / 100;

                            ColorR = ((ColorRW1 * XProp0) + (ColorRW2) * XProp) / 100;
                            ColorG = ((ColorGW1 * XProp0) + (ColorGW2) * XProp) / 100;
                            ColorB = ((ColorBW1 * XProp0) + (ColorBW2) * XProp) / 100;

                            uchar ColorR_ = Range(ColorR, 0, 255);
                            uchar ColorG_ = Range(ColorG, 0, 255);
                            uchar ColorB_ = Range(ColorB, 0, 255);

                            int Pos4X = Pos << 2;
                            CalcColor(ColorR_, ColorG_, ColorB_, X, Y, Z, LightAngle);
                            ImgZ[Pos] = Z;
                            ImgRaw[Pos4X + 0] = ColorR_;
                            ImgRaw[Pos4X + 1] = ColorG_;
                            ImgRaw[Pos4X + 2] = ColorB_;
                        }
                    }
                }
            }
        }
    }
}

void GuiGraphInstance::DrawTriangle0(int X1, int Y1, int Z1, int X2, int Y2, int Z2, int X3, int Y3, int Z3, uchar R1, uchar G1, uchar B1, uchar R2, uchar G2, uchar B2, uchar R3, uchar G3, uchar B3, double LightAngle)
{
    int XMin;
    int XMax;
    int YMin;
    int YMax;

    double F1, F2, F3, F3Z, F4, F4Z, F5, F6;

    int P0X_;
    int P0X__;
    int P0Y_;
    int P0Z_;
    int P0Z__;
    int P1X_;
    int P1Y_;
    int P1Z_;
    int P2X_;
    int P2Y_;
    int P2Z_;

    int Color0R_ = 0;
    int Color0G_ = 0;
    int Color0B_ = 0;

    int Color1R_ = 0;
    int Color1G_ = 0;
    int Color1B_ = 0;

    int Color2R_ = 0;
    int Color2G_ = 0;
    int Color2B_ = 0;

    int Color3R_ = 0;
    int Color3G_ = 0;
    int Color3B_ = 0;

    if (LightMode == 2)
    {
        CalcTriangleAngle(X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, LightAngle);
    }

    XMin = X1;
    XMax = X1;
    if (XMin > X2) { XMin = X2; }
    if (XMax < X2) { XMax = X2; }
    if (XMin > X3) { XMin = X3; }
    if (XMax < X3) { XMax = X3; }

    YMin = Y1;
    YMax = Y1;
    if (YMin > Y2) { YMin = Y2; }
    if (YMax < Y2) { YMax = Y2; }
    if (YMin > Y3) { YMin = Y3; }
    if (YMax < Y3) { YMax = Y3; }

    P0Y_ = YMin;

    if ((Y1 > YMin) && (Y1 < YMax))
    {
        P0X_ = X1; P0Y_ = Y1; P0Z_ = Z1;
        if (Y2 == YMin)
        {
            P1X_ = X2; P1Y_ = Y2; P1Z_ = Z2;
            P2X_ = X3; P2Y_ = Y3; P2Z_ = Z3;
            Color1R_ = R2; Color1G_ = G2; Color1B_ = B2;
            Color2R_ = R1; Color2G_ = G1; Color2B_ = B1;
            Color3R_ = R3; Color3G_ = G3; Color3B_ = B3;
        }
        else
        {
            P1X_ = X3; P1Y_ = Y3; P1Z_ = Z3;
            P2X_ = X2; P2Y_ = Y2; P2Z_ = Z2;
            Color1R_ = R3; Color1G_ = G3; Color1B_ = B3;
            Color2R_ = R1; Color2G_ = G1; Color2B_ = B1;
            Color3R_ = R2; Color3G_ = G2; Color3B_ = B2;
        }
    }
    else
    {
        if ((Y2 > YMin) && (Y2 < YMax))
        {
            P0X_ = X2; P0Y_ = Y2; P0Z_ = Z2;
            if (Y3 == YMin)
            {
                P1X_ = X3; P1Y_ = Y3; P1Z_ = Z3;
                P2X_ = X1; P2Y_ = Y1; P2Z_ = Z1;
                Color1R_ = R3; Color1G_ = G3; Color1B_ = B3;
                Color2R_ = R2; Color2G_ = G2; Color2B_ = B2;
                Color3R_ = R1; Color3G_ = G1; Color3B_ = B1;
            }
            else
            {
                P1X_ = X1; P1Y_ = Y1; P1Z_ = Z1;
                P2X_ = X3; P2Y_ = Y3; P2Z_ = Z3;
                Color1R_ = R1; Color1G_ = G1; Color1B_ = B1;
                Color2R_ = R2; Color2G_ = G2; Color2B_ = B2;
                Color3R_ = R3; Color3G_ = G3; Color3B_ = B3;
            }
        }
        else
        {
            if ((Y3 > YMin) && (Y3 < YMax))
            {
                P0X_ = X3; P0Y_ = Y3; P0Z_ = Z3;
                if (Y1 == YMin)
                {
                    P1X_ = X1; P1Y_ = Y1; P1Z_ = Z1;
                    P2X_ = X2; P2Y_ = Y2; P2Z_ = Z2;
                    Color1R_ = R1; Color1G_ = G1; Color1B_ = B1;
                    Color2R_ = R3; Color2G_ = G3; Color2B_ = B3;
                    Color3R_ = R2; Color3G_ = G2; Color3B_ = B2;
                }
                else
                {
                    P1X_ = X2; P1Y_ = Y2; P1Z_ = Z2;
                    P2X_ = X1; P2Y_ = Y1; P2Z_ = Z1;
                    Color1R_ = R2; Color1G_ = G2; Color1B_ = B2;
                    Color2R_ = R3; Color2G_ = G3; Color2B_ = B3;
                    Color3R_ = R1; Color3G_ = G1; Color3B_ = B1;
                }
            }
        }
    }



    if ((P0Y_ > YMin) && (P0Y_ < YMax))
    {
        F1 = P0Y_ - P1Y_;
        F2 = P2Y_ - P1Y_;

        F3 = P2X_ - P1X_;
        F3Z = P2Z_ - P1Z_;
        F4 = F3 * (F1 / F2);
        F4Z = F3Z * (F1 / F2);
        F5 = (F1 / F2);
        F6 = 1.0 - (F1 / F2);

        P0X__ = P1X_ + F4;
        P0Z__ = P1Z_ + F4Z;

        if ((F5 > 0) && (F6 > 0))
        {
            Color0R_ = (Color1R_ * F6) + (Color3R_ * F5);
            Color0G_ = (Color1G_ * F6) + (Color3G_ * F5);
            Color0B_ = (Color1B_ * F6) + (Color3B_ * F5);
        }
        else
        {
            Color0R_ = 0;
            Color0G_ = 0;
            Color0B_ = 0;
        }

        if (PlotSurface)
        {
            DrawHalfTriangle0(P1X_, P1Y_, P1Z_, P0X_, P0X__, P0Y_, P0Z_, P0Z__, Color1R_, Color1G_, Color1B_, Color2R_, Color2G_, Color2B_, Color0R_, Color0G_, Color0B_, LightAngle);
            DrawHalfTriangle0(P2X_, P2Y_, P2Z_, P0X_, P0X__, P0Y_, P0Z_, P0Z__, Color3R_, Color3G_, Color3B_, Color2R_, Color2G_, Color2B_, Color0R_, Color0G_, Color0B_, LightAngle);
        }
    }
    else
    {
        if (Y1 == Y2)
        {
            if (PlotSurface)
            {
                DrawHalfTriangle0(X3, Y3, Z3, X1, X2, Y1, Z1, Z2, R3, G3, B3, R1, G1, B1, R2, G2, B2, LightAngle);
            }
        }
        if (Y2 == Y3)
        {
            if (PlotSurface)
            {
                DrawHalfTriangle0(X1, Y1, Z1, X2, X3, Y2, Z2, Z3, R1, G1, B1, R2, G2, B2, R3, G3, B3, LightAngle);
            }
        }
        if (Y3 == Y1)
        {
            if (PlotSurface)
            {
                DrawHalfTriangle0(X2, Y2, Z2, X3, X1, Y3, Z3, Z1, R2, G2, B2, R3, G3, B3, R1, G1, B1, LightAngle);
            }
        }
    }
}
