#include "core.h"
#include "widget.h"
#include "graph.h"
#include <math.h>
#include "mathx.h"
#include "memo.h"
#include <stdlib.h>


int ExampleValue[5][21] = {
 {0, 0, 0, 0, 0,  0, 0, 1,  -1,      0,     0, 0, 0, 0, 0, 0, 0, 0, 0, 1,       2},
 {0, 0, 0, 0, 1,  0, 0, 0, -10,      0,     0, 0, 0, 0, 0, 0, 0, 0, 0, 1,      20},
 {0, 0, 0, 0, 0, -1, 0, 0,   0,   1000,     0, 0, 0, 0, 0, 0, 0, 1, 1, 0,       2},
 {0, 0, 0, 0, 1,  0, 1, 0,   0, -10000,     0, 0, 0, 0, 0, 0, 0, 0, 0, 1,     400},
 {1, 2, 3, 4, 5,  6, 7, 8,   9,     10,    11,12,13,14,15,16,17,18,19,20,      21}
};

void SetExample(int N)
{
 widget_set_sint(0, 20, widget_value, ExampleValue[N][ 0]);
 widget_set_sint(0, 21, widget_value, ExampleValue[N][ 1]);
 widget_set_sint(0, 22, widget_value, ExampleValue[N][ 2]);
 widget_set_sint(0, 23, widget_value, ExampleValue[N][ 3]);
 widget_set_sint(0, 24, widget_value, ExampleValue[N][ 4]);
 widget_set_sint(0, 25, widget_value, ExampleValue[N][ 5]);
 widget_set_sint(0, 26, widget_value, ExampleValue[N][ 6]);
 widget_set_sint(0, 27, widget_value, ExampleValue[N][ 7]);
 widget_set_sint(0, 28, widget_value, ExampleValue[N][ 8]);
 widget_set_sint(0, 29, widget_value, ExampleValue[N][ 9]);

 widget_set_sint(0, 30, widget_value, ExampleValue[N][10]);
 widget_set_sint(0, 31, widget_value, ExampleValue[N][11]);
 widget_set_sint(0, 32, widget_value, ExampleValue[N][12]);
 widget_set_sint(0, 33, widget_value, ExampleValue[N][13]);
 widget_set_sint(0, 34, widget_value, ExampleValue[N][14]);
 widget_set_sint(0, 35, widget_value, ExampleValue[N][15]);
 widget_set_sint(0, 36, widget_value, ExampleValue[N][16]);
 widget_set_sint(0, 37, widget_value, ExampleValue[N][17]);
 widget_set_sint(0, 38, widget_value, ExampleValue[N][18]);
 widget_set_sint(0, 39, widget_value, ExampleValue[N][19]);

 widget_set_sint(0,  8, widget_value, ExampleValue[N][20]);
}

long ProgressCounter;
long ProgressLength;

uchar Color1R;
uchar Color1G;
uchar Color1B;

uchar Color0R;
uchar Color0G;
uchar Color0B;

uchar ColorXR;
uchar ColorXG;
uchar ColorXB;

int ThreadNumber;
int ThreadCount;

long Xmin;
long Xmax;
long Ymin;
long Ymax;

long X_;
long Y_;
long Xstep;
long Ystep;

int X__;
int Y__;
int X___;

float X1;
float Y1;
float X2;
float Y2;
float X3;
float Y3;

float XXX_1;
float XXY_1;
float XYY_1;
float YYY_1;
float XX_1;
float XY_1;
float YY_1;
float X_1;
float Y_1;
float C_1;

float XXX_2;
float XXY_2;
float XYY_2;
float YYY_2;
float XX_2;
float XY_2;
float YY_2;
float X_2;
float Y_2;
float C_2;

float Val;
float Val_1;
float Val_2;

float Val_1_1;
float Val_1_2;
float Val_1_3;
float Val_1_4;
float Val_1_5;
float Val_1_6;
float Val_1_7;
float Val_1_8;
float Val_1_9;

float Val_2_1;
float Val_2_2;
float Val_2_3;
float Val_2_4;
float Val_2_5;
float Val_2_6;
float Val_2_7;
float Val_2_8;
float Val_2_9;

float ToleranceP;
float ToleranceN;

char DrawChartLabel1[22] = "Draw chart - standard";
char DrawChartLabel2[20] = "Draw chart - engine";
char DrawChartLabel3[8]  = "Waiting";

void main(void)
{
 memo_shared_local(128);

 ThreadNumber = engine_number();
 ThreadCount = 0;

 Xmin = -200;
 Xmax = 200;
 Ymin = -200;
 Ymax = 200;

 Xstep = 2;
 Ystep = 2;

 // Main thread only - create function parameter form
 if (ThreadNumber == 0)
 {
  widget_clear(0);
  widget_set_sint(0, 0, widget_orientation, widget_vertical);

  widget_add(0, 255, 0);
  widget_set_sint(0, 255, widget_orientation, widget_horizontal);
  widget_set_sint(0, 255, widget_size, 80);

  widget_add(0, 1, 255); widget_set_sint(0, 1, widget_size, 32); widget_set_sint(0, 1, widget_orientation, widget_vertical);
  widget_add(0, 2, 255); widget_set_sint(0, 2, widget_size, 34); widget_set_sint(0, 2, widget_orientation, widget_vertical);
  widget_add(0, 3, 255); widget_set_sint(0, 3, widget_size, 34); widget_set_sint(0, 3, widget_orientation, widget_vertical);

  widget_add(0,  4, 1); widget_set_sint(0,  4, widget_size, 10); widget_set_sint(0, 4, widget_type, widget_label);
  widget_add(0, 10, 1); widget_set_sint(0, 10, widget_size, 8); widget_set_sint(0, 10, widget_type, widget_label); widget_set_string(0, 10, widget_value, "XXX");
  widget_add(0, 11, 1); widget_set_sint(0, 11, widget_size, 8); widget_set_sint(0, 11, widget_type, widget_label); widget_set_string(0, 11, widget_value, "XXY");
  widget_add(0, 12, 1); widget_set_sint(0, 12, widget_size, 8); widget_set_sint(0, 12, widget_type, widget_label); widget_set_string(0, 12, widget_value, "XYY");
  widget_add(0, 13, 1); widget_set_sint(0, 13, widget_size, 8); widget_set_sint(0, 13, widget_type, widget_label); widget_set_string(0, 13, widget_value, "YYY");
  widget_add(0, 14, 1); widget_set_sint(0, 14, widget_size, 8); widget_set_sint(0, 14, widget_type, widget_label); widget_set_string(0, 14, widget_value, "XX");
  widget_add(0, 15, 1); widget_set_sint(0, 15, widget_size, 8); widget_set_sint(0, 15, widget_type, widget_label); widget_set_string(0, 15, widget_value, "XY");
  widget_add(0, 16, 1); widget_set_sint(0, 16, widget_size, 8); widget_set_sint(0, 16, widget_type, widget_label); widget_set_string(0, 16, widget_value, "YY");
  widget_add(0, 17, 1); widget_set_sint(0, 17, widget_size, 8); widget_set_sint(0, 17, widget_type, widget_label); widget_set_string(0, 17, widget_value, "X");
  widget_add(0, 18, 1); widget_set_sint(0, 18, widget_size, 8); widget_set_sint(0, 18, widget_type, widget_label); widget_set_string(0, 18, widget_value, "Y");
  widget_add(0, 19, 1); widget_set_sint(0, 19, widget_size, 8); widget_set_sint(0, 19, widget_type, widget_label); widget_set_string(0, 19, widget_value, "Const");
  widget_add(0,  7, 1); widget_set_sint(0,  7, widget_size, 10); widget_set_sint(0,  7, widget_type, widget_label); widget_set_string(0,  7, widget_value, "Tolerance");

  widget_add(0,  5, 2); widget_set_sint(0,  5, widget_size, 10); widget_set_sint(0, 5, widget_type, widget_label); widget_set_string(0, 5, widget_value, "Numerator");
  widget_add(0, 20, 2); widget_set_sint(0, 20, widget_size, 8); widget_set_sint(0, 20, widget_type, widget_text);
  widget_add(0, 21, 2); widget_set_sint(0, 21, widget_size, 8); widget_set_sint(0, 21, widget_type, widget_text);
  widget_add(0, 22, 2); widget_set_sint(0, 22, widget_size, 8); widget_set_sint(0, 22, widget_type, widget_text);
  widget_add(0, 23, 2); widget_set_sint(0, 23, widget_size, 8); widget_set_sint(0, 23, widget_type, widget_text);
  widget_add(0, 24, 2); widget_set_sint(0, 24, widget_size, 8); widget_set_sint(0, 24, widget_type, widget_text);
  widget_add(0, 25, 2); widget_set_sint(0, 25, widget_size, 8); widget_set_sint(0, 25, widget_type, widget_text);
  widget_add(0, 26, 2); widget_set_sint(0, 26, widget_size, 8); widget_set_sint(0, 26, widget_type, widget_text);
  widget_add(0, 27, 2); widget_set_sint(0, 27, widget_size, 8); widget_set_sint(0, 27, widget_type, widget_text);
  widget_add(0, 28, 2); widget_set_sint(0, 28, widget_size, 8); widget_set_sint(0, 28, widget_type, widget_text);
  widget_add(0, 29, 2); widget_set_sint(0, 29, widget_size, 8); widget_set_sint(0, 29, widget_type, widget_text);
  widget_add(0,  8, 2); widget_set_sint(0,  8, widget_size, 10); widget_set_sint(0,  8, widget_type, widget_text);

  widget_add(0,  6, 3); widget_set_sint(0,  6, widget_size, 10); widget_set_sint(0, 6, widget_type, widget_label); widget_set_string(0, 6, widget_value, "Denominator");
  widget_add(0, 30, 3); widget_set_sint(0, 30, widget_size, 8); widget_set_sint(0, 30, widget_type, widget_text);
  widget_add(0, 31, 3); widget_set_sint(0, 31, widget_size, 8); widget_set_sint(0, 31, widget_type, widget_text);
  widget_add(0, 32, 3); widget_set_sint(0, 32, widget_size, 8); widget_set_sint(0, 32, widget_type, widget_text);
  widget_add(0, 33, 3); widget_set_sint(0, 33, widget_size, 8); widget_set_sint(0, 33, widget_type, widget_text);
  widget_add(0, 34, 3); widget_set_sint(0, 34, widget_size, 8); widget_set_sint(0, 34, widget_type, widget_text);
  widget_add(0, 35, 3); widget_set_sint(0, 35, widget_size, 8); widget_set_sint(0, 35, widget_type, widget_text);
  widget_add(0, 36, 3); widget_set_sint(0, 36, widget_size, 8); widget_set_sint(0, 36, widget_type, widget_text);
  widget_add(0, 37, 3); widget_set_sint(0, 37, widget_size, 8); widget_set_sint(0, 37, widget_type, widget_text);
  widget_add(0, 38, 3); widget_set_sint(0, 38, widget_size, 8); widget_set_sint(0, 38, widget_type, widget_text);
  widget_add(0, 39, 3); widget_set_sint(0, 39, widget_size, 8); widget_set_sint(0, 39, widget_type, widget_text);
  widget_add(0,  9, 2); widget_set_sint(0,  9, widget_size, 10); widget_set_sint(0,  9, widget_type, widget_label);

  widget_add(0, 42, 0); widget_set_sint(0, 42, widget_size, 10); widget_set_sint(0, 42, widget_orientation, widget_horizontal);
  widget_add(0, 43, 42); widget_set_sint(0, 43, widget_size, 25); widget_set_sint(0, 43, widget_type, widget_button); widget_set_string(0, 43, widget_value, "Line");      widget_set_sint(0, 43, widget_event, widget_runscript);
  widget_add(0, 44, 42); widget_set_sint(0, 44, widget_size, 25); widget_set_sint(0, 44, widget_type, widget_button); widget_set_string(0, 44, widget_value, "Parabola");  widget_set_sint(0, 44, widget_event, widget_runscript);
  widget_add(0, 45, 42); widget_set_sint(0, 45, widget_size, 25); widget_set_sint(0, 45, widget_type, widget_button); widget_set_string(0, 45, widget_value, "Hyperbola"); widget_set_sint(0, 45, widget_event, widget_runscript);
  widget_add(0, 46, 42); widget_set_sint(0, 46, widget_size, 25); widget_set_sint(0, 46, widget_type, widget_button); widget_set_string(0, 46, widget_value, "Circle");    widget_set_sint(0, 46, widget_event, widget_runscript);

  widget_add(0, 47, 0); widget_set_sint(0, 47, widget_size, 10); widget_set_sint(0, 47, widget_orientation, widget_horizontal);
  widget_add(0, 48, 47); widget_set_sint(0, 48, widget_size, 50); widget_set_sint(0, 48, widget_type, widget_button); widget_set_string(0, 48, widget_value, DrawChartLabel1); widget_set_sint(0, 48, widget_event, widget_runscript);
  widget_add(0, 49, 47); widget_set_sint(0, 49, widget_size, 50); widget_set_sint(0, 49, widget_type, widget_button); widget_set_string(0, 49, widget_value, DrawChartLabel2); widget_set_sint(0, 49, widget_event, widget_runscript);

  SetExample(2);
 }


 // Main thread only - create drawing parameter form
 if (ThreadNumber == 0)
 {
  widget_clear(1);
  widget_set_sint(1, 0, widget_orientation, widget_vertical);

  widget_add(1, 255, 0);
  widget_set_sint(1, 255, widget_orientation, widget_horizontal);
  widget_set_sint(1, 255, widget_size, 80);

  widget_add(1, 1, 255); widget_set_sint(1, 1, widget_size, 25); widget_set_sint(1, 1, widget_orientation, widget_vertical);
  widget_add(1, 2, 255); widget_set_sint(1, 2, widget_size, 25); widget_set_sint(1, 2, widget_orientation, widget_vertical);
  widget_add(1, 3, 255); widget_set_sint(1, 3, widget_size, 25); widget_set_sint(1, 3, widget_orientation, widget_vertical);
  widget_add(1, 4, 255); widget_set_sint(1, 4, widget_size, 25); widget_set_sint(1, 4, widget_orientation, widget_vertical);

  widget_add(1,  5, 1); widget_set_sint(1,  5, widget_size, 15); widget_set_sint(1,  5, widget_type, widget_label);
  widget_add(1, 10, 1); widget_set_sint(1, 10, widget_size, 14); widget_set_sint(1, 10, widget_type, widget_label); widget_set_string(1, 10, widget_value, "X");
  widget_add(1, 11, 1); widget_set_sint(1, 11, widget_size, 14); widget_set_sint(1, 11, widget_type, widget_label); widget_set_string(1, 11, widget_value, "Y");
  widget_add(1, 12, 1); widget_set_sint(1, 12, widget_size, 15); widget_set_sint(1, 12, widget_type, widget_label);
  widget_add(1, 13, 1); widget_set_sint(1, 13, widget_size, 14); widget_set_sint(1, 13, widget_type, widget_label); widget_set_string(1, 13, widget_value, "True");
  widget_add(1, 14, 1); widget_set_sint(1, 14, widget_size, 14); widget_set_sint(1, 14, widget_type, widget_label); widget_set_string(1, 14, widget_value, "False");
  widget_add(1, 15, 1); widget_set_sint(1, 15, widget_size, 14); widget_set_sint(1, 15, widget_type, widget_label); widget_set_string(1, 15, widget_value, "Div 0");

  widget_add(1,  6, 2); widget_set_sint(1,  6, widget_size, 15); widget_set_sint(1,  6, widget_type, widget_label); widget_set_string(1,  6, widget_value, "Min");
  widget_add(1, 20, 2); widget_set_sint(1, 20, widget_size, 14); widget_set_sint(1, 20, widget_type, widget_text);  widget_set_string(1, 20, widget_value, "-200");
  widget_add(1, 21, 2); widget_set_sint(1, 21, widget_size, 14); widget_set_sint(1, 21, widget_type, widget_text);  widget_set_string(1, 21, widget_value, "-200");
  widget_add(1, 22, 2); widget_set_sint(1, 22, widget_size, 15); widget_set_sint(1, 22, widget_type, widget_label); widget_set_string(1, 22, widget_value, "Red");
  widget_add(1, 23, 2); widget_set_sint(1, 23, widget_size, 14); widget_set_sint(1, 23, widget_type, widget_text);  widget_set_string(1, 23, widget_value, "255");
  widget_add(1, 24, 2); widget_set_sint(1, 24, widget_size, 14); widget_set_sint(1, 24, widget_type, widget_text);  widget_set_string(1, 24, widget_value, "64");
  widget_add(1, 25, 2); widget_set_sint(1, 25, widget_size, 14); widget_set_sint(1, 25, widget_type, widget_text);  widget_set_string(1, 25, widget_value, "0");
 
  widget_add(1,  7, 3); widget_set_sint(1,  7, widget_size, 15); widget_set_sint(1,  7, widget_type, widget_label); widget_set_string(1,  7, widget_value, "Max");
  widget_add(1, 30, 3); widget_set_sint(1, 30, widget_size, 14); widget_set_sint(1, 30, widget_type, widget_text);  widget_set_string(1, 30, widget_value, "200");
  widget_add(1, 31, 3); widget_set_sint(1, 31, widget_size, 14); widget_set_sint(1, 31, widget_type, widget_text);  widget_set_string(1, 31, widget_value, "200");
  widget_add(1, 32, 3); widget_set_sint(1, 32, widget_size, 15); widget_set_sint(1, 32, widget_type, widget_label); widget_set_string(1, 32, widget_value, "Green");
  widget_add(1, 33, 3); widget_set_sint(1, 33, widget_size, 14); widget_set_sint(1, 33, widget_type, widget_text);  widget_set_string(1, 33, widget_value, "255");
  widget_add(1, 34, 3); widget_set_sint(1, 34, widget_size, 14); widget_set_sint(1, 34, widget_type, widget_text);  widget_set_string(1, 34, widget_value, "64");
  widget_add(1, 35, 3); widget_set_sint(1, 35, widget_size, 14); widget_set_sint(1, 35, widget_type, widget_text);  widget_set_string(1, 35, widget_value, "0");

  widget_add(1,  8, 4); widget_set_sint(1,  8, widget_size, 15); widget_set_sint(1,  8, widget_type, widget_label); widget_set_string(1,  8, widget_value, "Step");
  widget_add(1, 40, 4); widget_set_sint(1, 40, widget_size, 14); widget_set_sint(1, 40, widget_type, widget_text);  widget_set_string(1, 40, widget_value, "2");
  widget_add(1, 41, 4); widget_set_sint(1, 41, widget_size, 14); widget_set_sint(1, 41, widget_type, widget_text);  widget_set_string(1, 41, widget_value, "2");
  widget_add(1, 42, 4); widget_set_sint(1, 42, widget_size, 15); widget_set_sint(1, 42, widget_type, widget_label); widget_set_string(1, 42, widget_value, "Blue");
  widget_add(1, 43, 4); widget_set_sint(1, 43, widget_size, 14); widget_set_sint(1, 43, widget_type, widget_text);  widget_set_string(1, 43, widget_value, "255");
  widget_add(1, 44, 4); widget_set_sint(1, 44, widget_size, 14); widget_set_sint(1, 44, widget_type, widget_text);  widget_set_string(1, 44, widget_value, "64");
  widget_add(1, 45, 4); widget_set_sint(1, 45, widget_size, 14); widget_set_sint(1, 45, widget_type, widget_text);  widget_set_string(1, 45, widget_value, "0");

  widget_add(1, 56, 0); widget_set_sint(1, 56, widget_size, 10); widget_set_sint(1, 56, widget_orientation, widget_horizontal);
  widget_add(1, 54,56); widget_set_sint(1, 54, widget_size, 50); widget_set_sint(1, 54, widget_type, widget_label); widget_set_string(1, 54, widget_value, "Threads (1 - 8)");
  widget_add(1, 55,56); widget_set_sint(1, 55, widget_size, 50); widget_set_sint(1, 55, widget_type, widget_text);  widget_set_string(1, 55, widget_value, "1");

  widget_add(1,  9, 0); widget_set_sint(1,  9, widget_size, 10); widget_set_sint(1,  9, widget_orientation, widget_horizontal);
  widget_add(1, 52, 9); widget_set_sint(1, 52, widget_size, 50); widget_set_sint(1, 52, widget_type, widget_button); widget_set_string(1, 52, widget_value, DrawChartLabel1); widget_set_sint(1, 52, widget_event, widget_runscript);
  widget_add(1, 53, 9); widget_set_sint(1, 53, widget_size, 50); widget_set_sint(1, 53, widget_type, widget_button); widget_set_string(1, 53, widget_value, DrawChartLabel2); widget_set_sint(1, 53, widget_event, widget_runscript);
 }

 // Main thread only - create dummy (invisible) buttons for run threads
 if (ThreadNumber == 0)
 {
  for (int ThrI = 1; ThrI <= 8; ThrI++)
  {
   widget_add(1, 60 + ThrI, 9);
   widget_set_sint(1, 60 + ThrI, widget_size, 10);
   widget_set_sint(1, 60 + ThrI, widget_type, widget_button);
   widget_set_sint(1, 60 + ThrI, widget_value, ThrI);
   widget_set_string(1, 60 + ThrI, widget_min, "Thr");
   widget_set_sint(1, 60 + ThrI, widget_event_rem, 0);
   widget_set_sint(1, 60 + ThrI, widget_event_add, ThrI);
   widget_set_sint(1, 60 + ThrI, widget_event, widget_runscript);
  }
 }

 while(1)
 {
  char UseEngine = 0;
  char PerformDrawing = 0;

  // Wait for user action or thread run
  stop();

  // Main thread - action depending on selected widget in the form
  if (ThreadNumber == 0)
  {
   switch (event_widget)
   {
    case 43:
     SetExample(0);
     break;
    case 44:
     SetExample(1);
     break;
    case 45:
     SetExample(2);
     break;
    case 46:
     SetExample(3);
     break;
    case 48:
    case 52:
     PerformDrawing = 1;
     break;
    case 49:
    case 53:
     PerformDrawing = 2;
     break;
   }
  }

  if ((ThreadNumber > 0))
  {
   PerformDrawing = 1;
  }

  if (PerformDrawing > 0)
  {
   // Get thread number
   ThreadCount = widget_get_uchar_v(1, 55, widget_value);
   if (ThreadCount < 1) ThreadCount = 1;
   if (ThreadCount > 8) ThreadCount = 8;

   // Operations for main thread only
   if (ThreadNumber == 0)
   {
    // Clear graphics screen
    graph_clear(0);

    // Read function parameters from form and write to the shared memory
    Xmin = widget_get_slong(1, 20, widget_value);
    Ymin = widget_get_slong(1, 21, widget_value);
    Xmax = widget_get_slong(1, 30, widget_value);
    Ymax = widget_get_slong(1, 31, widget_value);
    Xstep = widget_get_slong(1, 40, widget_value);
    Ystep = widget_get_slong(1, 41, widget_value);

    memo_set_slong(0, 0, PerformDrawing);
    memo_set_slong(0, 1, Xmin);
    memo_set_slong(0, 2, Xmax);
    memo_set_slong(0, 3, Xstep);
    memo_set_slong(0, 4, Ymin);
    memo_set_slong(0, 5, Ymax);
    memo_set_slong(0, 6, Ystep);

    // Writing thread working indicator into shared memory
    memo_set_schar(1, 10, 1);
    memo_set_schar(1, 11, 1);
    memo_set_schar(1, 12, 1);
    memo_set_schar(1, 13, 1);
    

    // Invoke other threads
    for (int ThrI = 1; ThrI < ThreadCount; ThrI++)
    {
     widget_raise_event(1, 60 + ThrI);
    }
   }

   // Read functions parameters from shared memory
   PerformDrawing = memo_get_slong(0, 0);
   Xmin = memo_get_slong(0, 1);
   Xmax = memo_get_slong(0, 2);
   Xstep = memo_get_slong(0, 3);
   Ymin = memo_get_slong(0, 4);
   Ymax = memo_get_slong(0, 5);
   Ystep = memo_get_slong(0, 6);


   // Every thread - Get drawing parameters
   Color1R = widget_get_uchar_v(1, 23, widget_value);
   Color1G = widget_get_uchar_v(1, 33, widget_value);
   Color1B = widget_get_uchar_v(1, 43, widget_value);

   Color0R = widget_get_uchar_v(1, 24, widget_value);
   Color0G = widget_get_uchar_v(1, 34, widget_value);
   Color0B = widget_get_uchar_v(1, 44, widget_value);

   ColorXR = widget_get_uchar_v(1, 25, widget_value);
   ColorXG = widget_get_uchar_v(1, 35, widget_value);
   ColorXB = widget_get_uchar_v(1, 45, widget_value);

   ToleranceP = widget_get_float(0,  8, widget_value);
   ToleranceN = 0 - ToleranceP;

   // Every thread - Get function parameters
   XXX_1 = widget_get_float(0, 20, widget_value);
   XXY_1 = widget_get_float(0, 21, widget_value);
   XYY_1 = widget_get_float(0, 22, widget_value);
   YYY_1 = widget_get_float(0, 23, widget_value);
   XX_1  = widget_get_float(0, 24, widget_value);
   XY_1  = widget_get_float(0, 25, widget_value);
   YY_1  = widget_get_float(0, 26, widget_value);
   X_1   = widget_get_float(0, 27, widget_value);
   Y_1   = widget_get_float(0, 28, widget_value);
   C_1   = widget_get_float(0, 29, widget_value);

   XXX_2 = widget_get_float(0, 30, widget_value);
   XXY_2 = widget_get_float(0, 31, widget_value);
   XYY_2 = widget_get_float(0, 32, widget_value);
   YYY_2 = widget_get_float(0, 33, widget_value);
   XX_2  = widget_get_float(0, 34, widget_value);
   XY_2  = widget_get_float(0, 35, widget_value);
   YY_2  = widget_get_float(0, 36, widget_value);
   X_2   = widget_get_float(0, 37, widget_value);
   Y_2   = widget_get_float(0, 38, widget_value);
   C_2   = widget_get_float(0, 39, widget_value);


   Y__ = 0 - ((Ymax - Ymin) / (Ystep << 1)) + ThreadNumber;
   X___= 0 - ((Xmax - Xmin) / (Xstep << 1));
   ProgressLength = (Ymax - Ymin) / Ystep;
   ProgressLength = ProgressLength / ThreadCount;
   ProgressCounter = 0;
   Ymin = Ymin + ((slong)(ThreadNumber)) * Ystep;
   Ystep = Ystep * ThreadCount;
   if (PerformDrawing == 2)
   {
    for (Y_ = Ymin; Y_ <= Ymax; Y_ += Ystep)
    {
     if (ThreadNumber == 0)
     {
      ProgressCounter++;
      string_set_slong(ProgressCounter);
      string_append_schar_t('/');
      string_append_slong(ProgressLength);
      widget_set_string(0, 48, widget_value, 0);
      widget_set_string(0, 49, widget_value, 0);
      widget_set_string(1, 52, widget_value, 0);
      widget_set_string(1, 53, widget_value, 0);
     }

     Y1 = Y_;
     Y2 = engine_mul_float(Y1, Y1);
     Y3 = engine_mul_float(Y2, Y1);
     X__ = X___;
     for (X_ = Xmin; X_ <= Xmax; X_ += Xstep)
     {
      X1 = X_;
      X2 = engine_mul_float(X1, X1);
      X3 = engine_mul_float(X2, X1);
      Val_2_1 = engine_mul_float(XXX_2, X3);
      Val_2_2 = engine_mul_float(engine_mul_float(XXY_2, X2), Y1);
      Val_2_3 = engine_mul_float(engine_mul_float(XYY_2, X1), Y2);
      Val_2_4 = engine_mul_float(YYY_2, Y3);
      Val_2_5 = engine_mul_float(XX_2, X2);
      Val_2_6 = engine_mul_float(engine_mul_float(XY_2, X1), Y1);
      Val_2_7 = engine_mul_float(YY_2, Y2);
      Val_2_8 = engine_mul_float(X_2, X1);
      Val_2_9 = engine_mul_float(Y_2, Y1);
      Val_2 = C_2;
      Val_2 = engine_add_float(Val_2, Val_2_1);
      Val_2 = engine_add_float(Val_2, Val_2_2);
      Val_2 = engine_add_float(Val_2, Val_2_3);
      Val_2 = engine_add_float(Val_2, Val_2_4);
      Val_2 = engine_add_float(Val_2, Val_2_5);
      Val_2 = engine_add_float(Val_2, Val_2_6);
      Val_2 = engine_add_float(Val_2, Val_2_7);
      Val_2 = engine_add_float(Val_2, Val_2_8);
      Val_2 = engine_add_float(Val_2, Val_2_9);
      if (Val_2 != 0.0)
      {
       Val_1_1 = engine_mul_float(XXX_1, X3);
       Val_1_2 = engine_mul_float(engine_mul_float(XXY_1, X2), Y1);
       Val_1_3 = engine_mul_float(engine_mul_float(XYY_1, X1), Y2);
       Val_1_4 = engine_mul_float(YYY_1, Y3);
       Val_1_5 = engine_mul_float(XX_1, X2);
       Val_1_6 = engine_mul_float(engine_mul_float(XY_1, X1), Y1);
       Val_1_7 = engine_mul_float(YY_1, Y2);
       Val_1_8 = engine_mul_float(X_1, X1);
       Val_1_9 = engine_mul_float(Y_1, Y1);
       Val_1 = C_1;
       Val_1 = engine_add_float(Val_1, Val_1_1);
       Val_1 = engine_add_float(Val_1, Val_1_2);
       Val_1 = engine_add_float(Val_1, Val_1_3);
       Val_1 = engine_add_float(Val_1, Val_1_4);
       Val_1 = engine_add_float(Val_1, Val_1_5);
       Val_1 = engine_add_float(Val_1, Val_1_6);
       Val_1 = engine_add_float(Val_1, Val_1_7);
       Val_1 = engine_add_float(Val_1, Val_1_8);
       Val_1 = engine_add_float(Val_1, Val_1_9);
       Val = engine_div_float(Val_1, Val_2);
       if ((Val >= ToleranceN) && (Val <= ToleranceP))
       {
        graph_plot_sint(0, X__, Y__, 0, Color1R, Color1G, Color1B);
       }
       else
       {
        graph_plot_sint(0, X__, Y__, 0, Color0R, Color0G, Color0B);
       }
      }
      else
      {
       graph_plot_sint(0, X__, Y__, 0, ColorXR, ColorXG, ColorXB);
      }
      X__++;
     }
     Y__ += ThreadCount;
    }
   }
   else
   {
    for (Y_ = Ymin; Y_ <= Ymax; Y_ += Ystep)
    {
     if (ThreadNumber == 0)
     {
      ProgressCounter++;
      string_set_slong(ProgressCounter);
      string_append_schar_t('/');
      string_append_slong(ProgressLength);
      widget_set_string(0, 48, widget_value, 0);
      widget_set_string(0, 49, widget_value, 0);
      widget_set_string(1, 52, widget_value, 0);
      widget_set_string(1, 53, widget_value, 0);
     }

     Y1 = Y_;
     Y2 = Y1 * Y1;
     Y3 = Y2 * Y1;
     X__ = X___;
     for (X_ = Xmin; X_ <= Xmax; X_ += Xstep)
     {
      X1 = X_;
      X2 = X1 * X1;
      X3 = X2 * X1;
      Val_2 = XXX_2*X3 + XXY_2*X2*Y1 + XYY_2*X1*Y2 + YYY_2*Y3 + XX_2*X2 + XY_2*X1*Y1 + YY_2*Y2 + X_2*X1 + Y_2*Y1 + C_2;
      if (Val_2 != 0.0)
      {
       Val_1 = XXX_1*X3 + XXY_1*X2*Y1 + XYY_1*X1*Y2 + YYY_1*Y3 + XX_1*X2 + XY_1*X1*Y1 + YY_1*Y2 + X_1*X1 + Y_1*Y1 + C_1;
       Val = Val_1 / Val_2;
       if ((Val >= ToleranceN) && (Val <= ToleranceP))
       {
        graph_plot_sint(0, X__, Y__, 0, Color1R, Color1G, Color1B);
       }
       else
       {
        graph_plot_sint(0, X__, Y__, 0, Color0R, Color0G, Color0B);
       }
      }
      else
      {
       graph_plot_sint(0, X__, Y__, 0, ColorXR, ColorXG, ColorXB);
      }
      X__++;
     }
     Y__ += ThreadCount;
    }
   }
    
   // Waiting for finish other threads
   if (ThreadNumber == 0)
   {
    widget_set_string(0, 48, widget_value, DrawChartLabel3);
    widget_set_string(0, 49, widget_value, DrawChartLabel3);
    widget_set_string(1, 52, widget_value, DrawChartLabel3);
    widget_set_string(1, 53, widget_value, DrawChartLabel3);

    schar T = 1;
    while (T != 0)
    {
     T = 0;
     for (int ThrI = 1; ThrI < ThreadCount; ThrI++)
     {
      T = T + memo_get_schar(1, 10 + ThrI);
     }
    }
    
    widget_set_string(0, 48, widget_value, DrawChartLabel1);
    widget_set_string(0, 49, widget_value, DrawChartLabel2);
    widget_set_string(1, 52, widget_value, DrawChartLabel1);
    widget_set_string(1, 53, widget_value, DrawChartLabel2);
   }
   memo_set_schar(1, 10 + ThreadNumber, 0);
  }
 }
}

