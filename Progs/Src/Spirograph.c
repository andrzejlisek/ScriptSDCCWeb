#include "core.h"
#include <math.h>
#include <stdlib.h>
#include "widget.h"
#include "graph.h"
#include "graphtext.h"
#include "mathx.h"

long Counter11 = -1;
long Counter12 = -1;
long Counter21 = -1;
long Counter22 = -1;
long Counter31 = -1;
long Counter32 = -1;
long Counter41 = -1;
long Counter42 = -1;
long Counter51 = -1;
long Counter52 = -1;

uchar Engine;
uchar EngineInfo;
char UseStandard = 1;
char UseEngine = 1;
uchar DrawType;

int Delta = 50;
int Period = 28;
int Size = 100;

float PI0;
float t;
float Factor;
float X;
float Y;
float R, r, Rr;
float h1, h2, f1, f2;
float DeltaF, SizeF;

uint I, I1, I2, I1Count, I2Count;



void DrawTrochoidInfo(void)
{
 graph_clear(EngineInfo);
 graph_text_color_f(EngineInfo, 255, 255, 255);
 graph_text_xyz_sint(EngineInfo, 0, 0, 0);

 string_clear();
 string_append_float(Rr);
 int TextLength_Rr = string_get(0, 99);
 string_clear();
 string_append_float(r);
 int TextLength_r = string_get(0, 99);
 int TextLength_fraction = (TextLength_Rr > TextLength_r) ? TextLength_Rr : TextLength_r;

 string_clear();
 if (h1 < 0) string_append_float(0 - h1); else string_append_float(h1);
 int TextLength_h1 = string_get(0, 99);
 string_clear();
 if (h2 < 0) string_append_float(0 - h2); else string_append_float(h2);
 int TextLength_h2 = string_get(0, 99);
  
 int TextLength_fractionPos_1 = TextLength_h1 + TextLength_fraction + 22;
 int TextLength_fractionPos_2 = TextLength_h2 + TextLength_fraction + 22;


 string_clear();
 string_append("y = ");
 string_append_float(Rr);
 if (h1 < 0)
 {
  string_append(" * cos(t) - ");
  string_append_float(0.0 - h1);
 }
 else
 {
  string_append(" * cos(t) + ");
  string_append_float(h1);
 }
 string_append(" * cos( ");
 for (I = 0; I < (TextLength_fraction + 6); I++)
 {
  string_append_uchar_t(0xE2);
  string_append_uchar_t(0x94);
  string_append_uchar_t(0x80);
 }
 string_append(" )");
  
 graph_text_move(EngineInfo, 0, 4, 1);
 graph_text_string(EngineInfo, 0);

 graph_text_move(EngineInfo, TextLength_fractionPos_1, -2, 1);
 string_clear();
 string_append_float(Rr);
 string_append(" * t");
 graph_text_string(EngineInfo, 0);

 graph_text_move(EngineInfo, 0, 4, 1);
 string_clear();
 string_append_float(r);
 graph_text_string(EngineInfo, 0);


 string_clear();
 string_append("x = ");
 string_append_float(Rr);
 if (h2 < 0)
 {
  string_append(" * sin(t) - ");
  string_append_float(0.0 - h2);
 }
 else
 {
  string_append(" * sin(t) + ");
  string_append_float(h2);
 }
 string_append(" * sin( ");
 for (I = 0; I < (TextLength_fraction + 6); I++)
 {
  string_append_uchar_t(0xE2);
  string_append_uchar_t(0x94);
  string_append_uchar_t(0x80);
 }
 string_append(" )");
  
 graph_text_move(EngineInfo, 0 - TextLength_fractionPos_1, -10, 1);
 graph_text_string(EngineInfo, 0);

 graph_text_move(EngineInfo, TextLength_fractionPos_2, -2, 1);
 string_clear();
 string_append_float(Rr);
 string_append(" * t");
 graph_text_string(EngineInfo, 0);

 graph_text_move(EngineInfo, 0, 4, 1);
 string_clear();
 string_append_float(r);
 graph_text_string(EngineInfo, 0);

}

void DrawTrochoid(void)
{
 graph_thread(Engine, 1);

 DeltaF = Delta;
 SizeF = Size;
 Factor = SizeF / R;

 PI0 = M_PI_ / (DeltaF / 2.0);
 I = 0;
 if (Delta >= Period)
 {
  I1Count = Delta;
  I2Count = Period;
 }
 else
 {
  I1Count = Period;
  I2Count = Delta;
 }

 long Counter = -1;

 if (UseStandard)
 {
  engine_counter(0);
  for (I1 = 0; I1 <= I1Count; I1++)
  {
   string_set_uint(I1);
   string_append("/");
   string_append_uint(I1Count);
   widget_set_string(Engine, 26, widget_value, 0);
   widget_set_string(Engine, 27, widget_value, 0);
   widget_set_string(Engine, 28, widget_value, 0);
   widget_set_string(Engine, 29, widget_value, 0);
   widget_set_string(Engine, 30, widget_value, 0);
   for (I2 = 0; I2 < I2Count; I2++)
   {
    t = I;
    t = t * PI0;
    X = Rr * cosf(t) + h1 * cosf(Rr * t / r);
    Y = Rr * sinf(t) + h2 * sinf(Rr * t / r);
    graph_plot_float(Engine, Y * Factor, X * Factor, 0, 255, 255, 255);
    I++;
   }
  }
  Counter = engine_counter(0);
  switch (DrawType)
  {
   case 26: Counter11 = Counter; break;
   case 27: Counter21 = Counter; break;
   case 28: Counter31 = Counter; break;
   case 29: Counter41 = Counter; break;
  }
 }
 if (UseEngine)
 {
  engine_counter(0);
  for (I1 = 0; I1 <= I1Count; I1++)
  {
   string_set_uint(I1);
   string_append("/");
   string_append_uint(I1Count);
   widget_set_string(Engine, 26, widget_value, 0);
   widget_set_string(Engine, 27, widget_value, 0);
   widget_set_string(Engine, 28, widget_value, 0);
   widget_set_string(Engine, 29, widget_value, 0);
   widget_set_string(Engine, 30, widget_value, 0);
   for (I2 = 0; I2 < I2Count; I2++)
   {
    t = I;
    t = t * PI0;
    X = engine_mul_float(Rr, engine_cosf(t)) + engine_mul_float(h1, engine_cosf(engine_div_float(engine_mul_float(Rr, t), r)));
    Y = engine_mul_float(Rr, engine_sinf(t)) + engine_mul_float(h2, engine_sinf(engine_div_float(engine_mul_float(Rr, t), r)));
    graph_plot_float(Engine, Y * Factor, X * Factor, 0, 255, 255, 255);
    I++;
   }
  }
  Counter = engine_counter(0);
  switch (DrawType)
  {
   case 26: Counter12 = Counter; break;
   case 27: Counter22 = Counter; break;
   case 28: Counter32 = Counter; break;
   case 29: Counter42 = Counter; break;
  }
 }
}

void DrawLissajousInfo(void)
{
 graph_clear(EngineInfo);
 graph_text_color_f(EngineInfo, 255, 255, 255);
 graph_text_xyz_sint(EngineInfo, 0, 0, 0);

 string_clear();
 string_append("x = ");
 string_append("sin(");
 string_append_float(R);
 if (f1 > 0)
 {
  string_append(" * t + ");
  string_append_float(f1);
 }
 else
 {
  if (f1 < 0)
  {
   string_append(" * t - ");
   string_append_float(0 - f1);
  }
  else
  {
   string_append(" * t");
  }
 }
 string_append(")");

 graph_text_move(EngineInfo, 0, -4, 0);
 graph_text_string(EngineInfo, 0);

 if (f1 != 0.0)
 {
  string_clear();
  string_append("x = ");
  string_append("sin(");
  string_append_float(R);
  if (f1 > 0)
  {
   string_append(" * t + ");
   string_append_float(f1 * angle_rad_deg);
   string_append_uchar_t(0xC2);
   string_append_uchar_t(0xB0);
  }
  else
  {
   if (f1 < 0)
   {
    string_append(" * t - ");
    string_append_float(0 - f1 * angle_rad_deg);
    string_append_uchar_t(0xC2);
    string_append_uchar_t(0xB0);
   }
   else
   {
    string_append(" * t");
   }
  }
  string_append(")");

  graph_text_move(EngineInfo, 0, 0, 0);
  graph_text_string(EngineInfo, 0);
 }

 if (f2 != 0.0)
 {
  string_clear();
  string_append("y = ");
  string_append("sin(");
  string_append_float(r);
  if (f2 > 0)
  {
   string_append(" * t + ");
   string_append_float(f2 * angle_rad_deg);
   string_append_uchar_t(0xC2);
   string_append_uchar_t(0xB0);
  }
  else
  {
   if (f2 < 0)
   {
    string_append(" * t - ");
    string_append_float(0 - f2 * angle_rad_deg);
    string_append_uchar_t(0xC2);
    string_append_uchar_t(0xB0);
   }
   else
   {
    string_append(" * t");
   }
  }
  string_append(")");

  graph_text_move(EngineInfo, 0, 0, 0);
  graph_text_string(EngineInfo, 0);
 }

 string_clear();
 string_append("y = ");
 string_append("sin(");
 string_append_float(r);
 string_append(" * t");
 string_append(")");

 graph_text_move(EngineInfo, 0, 4, 0);
 graph_text_string(EngineInfo, 0);
}

void DrawLissajous(void)
{
 graph_thread(Engine, 1);

 DeltaF = Delta;
 SizeF = Size;
 Factor = SizeF;

 PI0 = M_PI_ / (DeltaF / 2.0);
 I = 0;
 if (Delta >= Period)
 {
  I1Count = Delta;
  I2Count = Period;
 }
 else
 {
  I1Count = Period;
  I2Count = Delta;
 }

 long Counter = -1;

 if (UseStandard)
 {
  engine_counter(0);
  for (I1 = 0; I1 <= I1Count; I1++)
  {
   string_set_uint(I1);
   string_append("/");
   string_append_uint(I1Count);
   widget_set_string(Engine, 26, widget_value, 0);
   widget_set_string(Engine, 27, widget_value, 0);
   widget_set_string(Engine, 28, widget_value, 0);
   widget_set_string(Engine, 29, widget_value, 0);
   widget_set_string(Engine, 30, widget_value, 0);
   for (I2 = 0; I2 < I2Count; I2++)
   {
    t = I;
    t = t * PI0;
    X = sinf(R * t + f1);
    Y = sinf(r * t + f2);
    graph_plot_float(Engine, X * Factor, Y * Factor, 0, 255, 255, 255);
    I++;
   }
  }
  Counter = engine_counter(0);
  switch (DrawType)
  {
   case 30: Counter51 = Counter; break;
  }
 }
 if (UseEngine)
 {
  engine_counter(0);
  for (I1 = 0; I1 <= I1Count; I1++)
  {
   string_set_uint(I1);
   string_append("/");
   string_append_uint(I1Count);
   widget_set_string(Engine, 26, widget_value, 0);
   widget_set_string(Engine, 27, widget_value, 0);
   widget_set_string(Engine, 28, widget_value, 0);
   widget_set_string(Engine, 29, widget_value, 0);
   widget_set_string(Engine, 30, widget_value, 0);
   for (I2 = 0; I2 < I2Count; I2++)
   {
    t = I;
    t = t * PI0;
    X = engine_sinf(engine_add_float(engine_mul_float(R, t), f1));
    Y = engine_sinf(engine_add_float(engine_mul_float(r, t), f2));
    graph_plot_float(Engine, X * Factor, Y * Factor, 0, 255, 255, 255);
    I++;
   }
  }
  Counter = engine_counter(0);
  switch (DrawType)
  {
   case 30: Counter52 = Counter; break;
  }
 }
}

void main(void)
{
 Delta = 50;
 Period = 28;
 Size = 100;
 R = 150;
 r = 56;
 f1 = 1;
 f2 = 1;

 UseStandard = 1;
 UseEngine = 1;
 char IsLissajous = 0;
 
 Engine = engine_number();
 EngineInfo = Engine + 1;

 widget_clear(Engine);
 widget_add(Engine, 1, 0);
 widget_add(Engine, 2, 0);
 widget_add(Engine, 3, 0);
 widget_add(Engine, 4, 0);
 widget_add(Engine, 5, 0);
 widget_add(Engine, 6, 0);
 widget_add(Engine, 7, 0);
 widget_add(Engine, 8, 0);
 widget_set_sint(Engine, 1, widget_size, 10);
 widget_set_sint(Engine, 2, widget_size, 10);
 widget_set_sint(Engine, 3, widget_size, 10);
 widget_set_sint(Engine, 4, widget_size, 10);
 widget_set_sint(Engine, 5, widget_size, 10);
 widget_set_sint(Engine, 6, widget_size, 10);
 widget_set_sint(Engine, 7, widget_size, 10);
 widget_set_sint(Engine, 8, widget_size, 30);
 widget_set_sint(Engine, 1, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 2, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 3, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 4, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 5, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 6, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 7, widget_orientation, widget_horizontal);
 widget_set_sint(Engine, 8, widget_orientation, widget_horizontal);

 widget_add(Engine, 21, 1);
 widget_add(Engine, 22, 1);
 widget_set_sint(Engine, 21, widget_size, 50);
 widget_set_sint(Engine, 22, widget_size, 50);
 widget_set_sint(Engine, 21, widget_type, widget_label);
 widget_set_sint(Engine, 22, widget_type, widget_text);
 widget_set_string(Engine, 21, widget_value, "Points per pass");
 widget_set_sint(Engine, 22, widget_value, Delta);

 widget_add(Engine, 23, 2);
 widget_add(Engine, 24, 2);
 widget_set_sint(Engine, 23, widget_size, 50);
 widget_set_sint(Engine, 24, widget_size, 50);
 widget_set_sint(Engine, 23, widget_type, widget_label);
 widget_set_sint(Engine, 24, widget_type, widget_text);
 widget_set_string(Engine, 23, widget_value, "Number of passes");
 widget_set_sint(Engine, 24, widget_value, Period);

 widget_add(Engine, 10, 3);
 widget_add(Engine, 11, 3);
 widget_set_sint(Engine, 10, widget_size, 50);
 widget_set_sint(Engine, 11, widget_size, 50);
 widget_set_sint(Engine, 10, widget_type, widget_label);
 widget_set_sint(Engine, 11, widget_type, widget_text);
 widget_set_string(Engine, 10, widget_value, "Stator radius");
 widget_set_sint(Engine, 11, widget_value, R);

 widget_add(Engine, 12, 4);
 widget_add(Engine, 13, 4);
 widget_set_sint(Engine, 12, widget_size, 50);
 widget_set_sint(Engine, 13, widget_size, 50);
 widget_set_sint(Engine, 12, widget_type, widget_label);
 widget_set_sint(Engine, 13, widget_type, widget_text);
 widget_set_string(Engine, 12, widget_value, "Rotor radius");
 widget_set_sint(Engine, 13, widget_value, r);

 widget_add(Engine, 16, 5);
 widget_add(Engine, 17, 5);
 widget_set_sint(Engine, 16, widget_size, 50);
 widget_set_sint(Engine, 17, widget_size, 50);
 widget_set_sint(Engine, 16, widget_type, widget_label);
 widget_set_sint(Engine, 17, widget_type, widget_text);
 widget_set_string(Engine, 16, widget_value, "Drawing factor x100");
 widget_set_sint(Engine, 17, widget_value, 100);

 widget_add(Engine, 14, 6);
 widget_add(Engine, 15, 6);
 widget_set_sint(Engine, 14, widget_size, 50);
 widget_set_sint(Engine, 15, widget_size, 50);
 widget_set_sint(Engine, 14, widget_type, widget_label);
 widget_set_sint(Engine, 15, widget_type, widget_text);
 widget_set_string(Engine, 14, widget_value, "Drawing size");
 widget_set_sint(Engine, 15, widget_value, Size);

 widget_add(Engine, 18, 7);
 widget_add(Engine, 19, 7);
 widget_add(Engine, 20, 7);
 widget_set_sint(Engine, 18, widget_size, 50);
 widget_set_sint(Engine, 19, widget_size, 25);
 widget_set_sint(Engine, 20, widget_size, 25);
 widget_set_sint(Engine, 18, widget_type, widget_label);
 widget_set_sint(Engine, 19, widget_type, widget_switch);
 widget_set_sint(Engine, 20, widget_type, widget_switch);
 widget_set_string(Engine, 18, widget_value, "Standard | Engine");
 widget_set_sint(Engine, 19, widget_value, 1);
 widget_set_sint(Engine, 20, widget_value, 1);

 widget_add(Engine, 31, 8);
 widget_set_sint(Engine, 31, widget_size, 34);
 widget_add(Engine, 32, 8);
 widget_set_sint(Engine, 32, widget_size, 32);
 widget_add(Engine, 33, 8);
 widget_set_sint(Engine, 33, widget_size, 34);


 widget_add(Engine, 26, 31);
 widget_set_sint(Engine, 26, widget_size, 50);
 widget_set_sint(Engine, 26, widget_type, widget_button);
 widget_set_string(Engine, 26, widget_value, "Hypotrochoid\n?\n?");
 widget_set_sint(Engine, 26, widget_event, widget_runscript);

 widget_add(Engine, 27, 31);
 widget_set_sint(Engine, 27, widget_size, 50);
 widget_set_sint(Engine, 27, widget_type, widget_button);
 widget_set_string(Engine, 27, widget_value, "Other inner\n?\n?");
 widget_set_sint(Engine, 27, widget_event, widget_runscript);

 widget_add(Engine, 28, 33);
 widget_set_sint(Engine, 28, widget_size, 50);
 widget_set_sint(Engine, 28, widget_type, widget_button);
 widget_set_string(Engine, 28, widget_value, "Epitrochoid\n?\n?");
 widget_set_sint(Engine, 28, widget_event, widget_runscript);

 widget_add(Engine, 29, 33);
 widget_set_sint(Engine, 29, widget_size, 50);
 widget_set_sint(Engine, 29, widget_type, widget_button);
 widget_set_string(Engine, 29, widget_value, "Other outer\n?\n?");
 widget_set_sint(Engine, 29, widget_event, widget_runscript);

 widget_add(Engine, 30, 32);
 widget_set_sint(Engine, 30, widget_size, 100);
 widget_set_sint(Engine, 30, widget_type, widget_button);
 widget_set_string(Engine, 30, widget_value, "Lissajous\n?\n?");
 widget_set_sint(Engine, 30, widget_event, widget_runscript);

 Counter11 = -1;
 Counter12 = -1;
 Counter21 = -1;
 Counter22 = -1;
 Counter31 = -1;
 Counter32 = -1;
 Counter41 = -1;
 Counter42 = -1;
 Counter51 = -1;
 Counter52 = -1;

 while (1)
 {
  stop();

  graph_clear(Engine);

  Delta = widget_get_sint(Engine, 22, widget_value);
  Period = widget_get_sint(Engine, 24, widget_value);
  R = widget_get_float(Engine, 11, widget_value);
  r = widget_get_float(Engine, 13, widget_value);
  f1 = widget_get_float(Engine, 17, widget_value) / 100.0;
  f2 = widget_get_float(Engine, 17, widget_value) / 100.0;
  Rr = 0;

  DrawType = event_widget;
  
  IsLissajous = 0;
  
  switch (DrawType)
  {
   case 26:
    Rr = R - r;
    f2 = 0.0 - f2;
    break;
   case 27:
    Rr = R - r;
    f1 = 0.0 - f1;
    f2 = 0.0 - f2;
    break;
   case 28:
    Rr = R + r;
    f1 = 0.0 - f1;
    f2 = 0.0 - f2;
    break;
   case 29:
    Rr = R + r;
    f2 = 0.0 - f2;
    break;
   case 30:
    IsLissajous = 1;
    f1 = f1 * 100.0;
    f2 = 0;
    if (f1 < 0)
    {
     f2 = 0 - f1;
     f1 = 0;
    }
    while (f1 > 180) f1 -= 360;
    while (f2 > 180) f2 -= 360;
    f1 = f1 * angle_deg_rad;
    f2 = f2 * angle_deg_rad;
    break;
  }

  h1 = r * f1;
  h2 = r * f2;

  Size = widget_get_sint(Engine, 15, widget_value);

  UseStandard = widget_get_sint(Engine, 19, widget_value);
  UseEngine = widget_get_sint(Engine, 20, widget_value);

  if (IsLissajous)
  {
   DrawLissajousInfo();
   DrawLissajous();
  }
  else
  {
   DrawTrochoidInfo();
   DrawTrochoid();
  }

  widget_set_string(Engine, 26, widget_value, "Hypotrochoid\n");
  if (Counter11 >= 0)
  {
   widget_set_ulong(Engine, 26, widget_max, Counter11);
   widget_set_string(Engine, 26, widget_max, "\n");
  }
  else
  {
   widget_set_string(Engine, 26, widget_max, "?\n");
  }
  if (Counter12 >= 0)
  {
   widget_set_ulong(Engine, 26, widget_max, Counter12);
  }
  else
  {
   widget_set_string(Engine, 26, widget_max, "?");
  }
  
  widget_set_string(Engine, 27, widget_value, "Other inner\n");
  if (Counter21 >= 0)
  {
   widget_set_ulong(Engine, 27, widget_max, Counter21);
   widget_set_string(Engine, 27, widget_max, "\n");
  }
  else
  {
   widget_set_string(Engine, 27, widget_max, "?\n");
  }
  if (Counter22 >= 0)
  {
   widget_set_ulong(Engine, 27, widget_max, Counter22);
  }
  else
  {
   widget_set_string(Engine, 27, widget_max, "?");
  }

  widget_set_string(Engine, 28, widget_value, "Epitrochoid\n");
  if (Counter31 >= 0)
  {
   widget_set_ulong(Engine, 28, widget_max, Counter31);
   widget_set_string(Engine, 28, widget_max, "\n");
  }
  else
  {
   widget_set_string(Engine, 28, widget_max, "?\n");
  }
  if (Counter32 >= 0)
  {
   widget_set_ulong(Engine, 28, widget_max, Counter32);
  }
  else
  {
   widget_set_string(Engine, 28, widget_max, "?");
  }

  widget_set_string(Engine, 29, widget_value, "Other outer\n");
  if (Counter41 >= 0)
  {
   widget_set_ulong(Engine, 29, widget_max, Counter41);
   widget_set_string(Engine, 29, widget_max, "\n");
  }
  else
  {
   widget_set_string(Engine, 29, widget_max, "?\n");
  }
  if (Counter42 >= 0)
  {
   widget_set_ulong(Engine, 29, widget_max, Counter42);
  }
  else
  {
   widget_set_string(Engine, 29, widget_max, "?");
  }

  widget_set_string(Engine, 30, widget_value, "Lissajous\n");
  if (Counter51 >= 0)
  {
   widget_set_ulong(Engine, 30, widget_max, Counter51);
   widget_set_string(Engine, 30, widget_max, "\n");
  }
  else
  {
   widget_set_string(Engine, 30, widget_max, "?\n");
  }
  if (Counter52 >= 0)
  {
   widget_set_ulong(Engine, 30, widget_max, Counter52);
  }
  else
  {
   widget_set_string(Engine, 30, widget_max, "?");
  }
 }
}

