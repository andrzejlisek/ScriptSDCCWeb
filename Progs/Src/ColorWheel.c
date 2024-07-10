/*
Draws the wheel of colors with labels on Graph 0, input parameters are on Spreadsheet 0.
*/


#include "core.h"
#include "graph.h"
#include "graphtext.h"
#include "mathx.h"
#include "widget.h"
#include <math.h>

void TextToArray(uchar * A, char * S)
{
 uchar I = 0;
 while (S[I] != 0)
 {
  A[I] = S[I];
  I++;
 }
 A[I] = 0;
}

void main(void)
{
 // Engine number
 uchar Engine = engine_number();

 // Drawing shape
 float Angle;
 float Radius = 100;
 float Distance = 150;

 // Scale for drawing
 float ScaleX1;
 float ScaleY1;
 float ScaleX2;
 float ScaleY2;

 // Colors
 uchar ColorR_ = 128;
 uchar ColorG_ = 128;
 uchar ColorB_ = 128;
 uchar ColorR[25];
 uchar ColorG[25];
 uchar ColorB[25];

 int I;

 // Color label array
 uchar Label[6][10];

 // Color names
 TextToArray(Label[0], "RED");
 TextToArray(Label[1], "YELLOW");
 TextToArray(Label[2], "GREEN");
 TextToArray(Label[3], "CYAN");
 TextToArray(Label[4], "BLUE");
 TextToArray(Label[5], "MAGENTA");

 // Color of wheel parts
 ColorR[0]  = 255; ColorG[0]  =   0; ColorB[0]  =   0;
 ColorR[1]  = 255; ColorG[1]  =  64; ColorB[1]  =   0;
 ColorR[2]  = 255; ColorG[2]  = 128; ColorB[2]  =   0;
 ColorR[3]  = 255; ColorG[3]  = 192; ColorB[3]  =   0;
 ColorR[4]  = 255; ColorG[4]  = 255; ColorB[4]  =   0;
 ColorR[5]  = 192; ColorG[5]  = 255; ColorB[5]  =   0;
 ColorR[6]  = 128; ColorG[6]  = 255; ColorB[6]  =   0;
 ColorR[7]  =  64; ColorG[7]  = 255; ColorB[7]  =   0;
 ColorR[8]  =   0; ColorG[8]  = 255; ColorB[8]  =   0;
 ColorR[9]  =   0; ColorG[9]  = 255; ColorB[9]  =  64;
 ColorR[10] =   0; ColorG[10] = 255; ColorB[10] = 128;
 ColorR[11] =   0; ColorG[11] = 255; ColorB[11] = 192;
 ColorR[12] =   0; ColorG[12] = 255; ColorB[12] = 255;
 ColorR[13] =   0; ColorG[13] = 192; ColorB[13] = 255;
 ColorR[14] =   0; ColorG[14] = 128; ColorB[14] = 255;
 ColorR[15] =   0; ColorG[15] =  64; ColorB[15] = 255;
 ColorR[16] =   0; ColorG[16] =   0; ColorB[16] = 255;
 ColorR[17] =  64; ColorG[17] =   0; ColorB[17] = 255;
 ColorR[18] = 128; ColorG[18] =   0; ColorB[18] = 255;
 ColorR[19] = 192; ColorG[19] =   0; ColorB[19] = 255;
 ColorR[20] = 255; ColorG[20] =   0; ColorB[20] = 255;
 ColorR[21] = 255; ColorG[21] =   0; ColorB[21] = 192;
 ColorR[22] = 255; ColorG[22] =   0; ColorB[22] = 128;
 ColorR[23] = 255; ColorG[23] =   0; ColorB[23] =  64;
 ColorR[24] = 255; ColorG[24] =   0; ColorB[24] =   0;

 widget_clear(Engine);
 widget_add(Engine, 1, 0);
 widget_add(Engine, 2, 0);
 widget_add(Engine, 3, 0);
 widget_add(Engine, 4, 0);
 widget_add(Engine, 5, 0);
 widget_set_sint(Engine, 1, widget_size, 17);
 widget_set_sint(Engine, 2, widget_size, 17);
 widget_set_sint(Engine, 3, widget_size, 17);
 widget_set_sint(Engine, 4, widget_size, 17);
 widget_set_sint(Engine, 5, widget_size, 17);
 widget_set_sint(Engine, 1, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 2, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 3, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 4, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 5, widget_orientation, widget_horizontal);

 widget_add(Engine, 6, 1);
 widget_add(Engine, 7, 1);
 widget_set_sint(Engine, 6, widget_size, 50);
 widget_set_sint(Engine, 7, widget_size, 50);
 widget_set_sint(Engine, 6, widget_type, widget_label);
 widget_set_sint(Engine, 7, widget_type, widget_text);
 widget_set_string(Engine, 6, widget_value, "Radius:");
 widget_set_sint(Engine, 7, widget_value, Radius);

 widget_add(Engine, 8, 2);
 widget_add(Engine, 9, 2);
 widget_set_sint(Engine, 8, widget_size, 50);
 widget_set_sint(Engine, 9, widget_size, 50);
 widget_set_sint(Engine, 8, widget_type, widget_label);
 widget_set_sint(Engine, 9, widget_type, widget_text);
 widget_set_string(Engine, 8, widget_value, "Label distance:");
 widget_set_sint(Engine, 9, widget_value, Distance);

 widget_add(Engine, 10, 3);
 widget_add(Engine, 11, 3);
 widget_add(Engine, 16, 3);
 widget_set_sint(Engine, 10, widget_size, 50);
 widget_set_sint(Engine, 10, widget_type, widget_label);
 widget_set_string(Engine, 10, widget_value, "Middle point R:");
 widget_set_sint(Engine, 11, widget_size, 40);
 widget_set_sint(Engine, 11, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 11, widget_type, widget_slider);
 widget_set_sint(Engine, 11, widget_min, 0);
 widget_set_sint(Engine, 11, widget_max, 255);
 widget_set_sint(Engine, 11, widget_value, ColorR_);
 widget_set_sint(Engine, 11, widget_event, widget_runscript);
 widget_set_sint(Engine, 16, widget_size, 10);
 widget_set_sint(Engine, 16, widget_type, widget_label);
 widget_set_string(Engine, 16, widget_value, "?");

 widget_add(Engine, 12, 4);
 widget_add(Engine, 13, 4);
 widget_add(Engine, 17, 4);
 widget_set_sint(Engine, 12, widget_size, 50);
 widget_set_sint(Engine, 12, widget_type, widget_label);
 widget_set_string(Engine, 12, widget_value, "Middle point G:");
 widget_set_sint(Engine, 13, widget_size, 40);
 widget_set_sint(Engine, 13, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 13, widget_type, widget_slider);
 widget_set_sint(Engine, 13, widget_min, 0);
 widget_set_sint(Engine, 13, widget_max, 255);
 widget_set_sint(Engine, 13, widget_value, ColorG_);
 widget_set_sint(Engine, 13, widget_event, widget_runscript);
 widget_set_sint(Engine, 17, widget_size, 10);
 widget_set_sint(Engine, 17, widget_type, widget_label);
 widget_set_string(Engine, 17, widget_value, "?");

 widget_add(Engine, 14, 5);
 widget_add(Engine, 15, 5);
 widget_add(Engine, 18, 5);
 widget_set_sint(Engine, 14, widget_size, 50);
 widget_set_sint(Engine, 14, widget_type, widget_label);
 widget_set_string(Engine, 14, widget_value, "Middle point B:");
 widget_set_sint(Engine, 15, widget_size, 40);
 widget_set_sint(Engine, 15, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 15, widget_type, widget_slider);
 widget_set_sint(Engine, 15, widget_min, 0);
 widget_set_sint(Engine, 15, widget_max, 255);
 widget_set_sint(Engine, 15, widget_value, ColorB_);
 widget_set_sint(Engine, 15, widget_event, widget_runscript);
 widget_set_sint(Engine, 18, widget_size, 10);
 widget_set_sint(Engine, 18, widget_type, widget_label);
 widget_set_string(Engine, 18, widget_value, "?");

 widget_add(Engine, 20, 0);
 widget_set_sint(Engine, 20, widget_size, 15);
 widget_set_sint(Engine, 20, widget_type, widget_button);
 widget_set_string(Engine, 20, widget_value, "Apply");
 widget_set_sint(Engine, 20, widget_event, widget_runscript);

 while(1)
 {
  // Clear the screen
  graph_clear(Engine);

  // Read parameters from form
  Radius = widget_get_sint(Engine, 7, widget_value);
  Distance = widget_get_sint(Engine, 9, widget_value);
  ColorR_ = widget_get_sint(Engine, 11, widget_value);
  ColorG_ = widget_get_sint(Engine, 13, widget_value);
  ColorB_ = widget_get_sint(Engine, 15, widget_value);
  widget_set_sint(Engine, 16, widget_value, ColorR_);
  widget_set_sint(Engine, 17, widget_value, ColorG_);
  widget_set_sint(Engine, 18, widget_value, ColorB_);

  // draw the wheel as 24 parts
  for (I = 0; I < 24; I++)
  {
   Angle = I * 15.0 * angle_deg_rad;
   ScaleX1 = cosf(Angle) * Radius;
   ScaleY1 = sinf(Angle) * Radius;

   Angle = (I + 1) * 15.0 * angle_deg_rad;
   ScaleX2 = cosf(Angle) * Radius;
   ScaleY2 = sinf(Angle) * Radius;

   graph_plot_float(Engine, ScaleX1, ScaleY1, 0, ColorR[I], ColorG[I], ColorB[I]);
   graph_plot_float(Engine, ScaleX2, ScaleY2, 0, ColorR[I + 1], ColorG[I + 1], ColorB[I + 1]);
   graph_plot_float(Engine, 0, 0, 0, ColorR_, ColorG_, ColorB_);
   graph_triangle(Engine);
  }

  // Draw color labels
  if (Distance > 0)
  {
   for (I = 0; I < 6; I++)
   {
    Angle = I * 60.0 * angle_deg_rad;
    ScaleX1 = cosf(Angle) * Distance;
    ScaleY1 = sinf(Angle) * Distance;

    graph_text_color_f(Engine, ColorR[I * 4], ColorG[I * 4], ColorB[I * 4]);
    graph_text_xyz_float(Engine, ScaleX1, ScaleY1, 0);
    graph_text_string(Engine, Label[I]);
   }
  }

  // Wait for user input
  stop();
 }
}

