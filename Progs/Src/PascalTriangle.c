#include "core.h"
#include "widget.h"
#include <math.h>
#include <stdlib.h>

ulong T1[100];
ulong T2[100];
int I, J;
int Size = 31;


void main(void)
{
 uchar Form0 = engine_number();
 uchar Form1 = Form0 + 1;


 widget_clear(Form0);
 widget_add(Form0, 1, 0);
 widget_set_sint(Form0, 1, widget_type, 6);
 widget_set_string(Form0, 1, widget_value, "");

 widget_clear(Form1);
 widget_add(Form1, 1, 0);
 widget_set_sint(Form1, 1, widget_type, 6);
 widget_set_string(Form1, 1, widget_value, "");

 T1[0] = 1;
 T1[1] = 1;

 for (I = -1; I < Size; I++)
 {
  for (J = 0; J < I; J++)
  {
   T2[J] = T1[J] + T1[J + 1];
  }

  T1[0] = 1;
  T1[I + 1] = 1;
  for (J = 0; J < I; J++)
  {
   T1[J + 1] = T2[J];
  }

  for (J = 2; J <= (Size - I); J++)
  {
   widget_set_schar_t(Form1, 1, widget_max, ' ');
   widget_set_string(Form0, 1, widget_max, "      ");
  }
  for (J = 0; J <= (I + 1); J++)
  {
   widget_set_string(Form0, 1, widget_max, "  ");
   if (T1[J] < 1000000000) { widget_set_schar_t(Form0, 1, widget_max, ' '); }
   if (T1[J] < 100000000)  { widget_set_schar_t(Form0, 1, widget_max, ' '); }
   if (T1[J] < 10000000)   { widget_set_schar_t(Form0, 1, widget_max, ' '); }
   if (T1[J] < 1000000)    { widget_set_schar_t(Form0, 1, widget_max, ' '); }
   if (T1[J] < 100000)     { widget_set_schar_t(Form0, 1, widget_max, ' '); }
   if (T1[J] < 10000)      { widget_set_schar_t(Form0, 1, widget_max, ' '); }
   if (T1[J] < 1000)       { widget_set_schar_t(Form0, 1, widget_max, ' '); }
   if (T1[J] < 100)        { widget_set_schar_t(Form0, 1, widget_max, ' '); }
   if (T1[J] < 10)         { widget_set_schar_t(Form0, 1, widget_max, ' '); }

   widget_set_ulong(Form0, 1, widget_max, T1[J]);
   if ((T1[J] % 2) == 0)
   {
    widget_set_string(Form1, 1, widget_max, "  ");
   }
   else
   {
    widget_set_string(Form1, 1, widget_max, "[]");
   }
  }

  widget_set_string(Form0, 1, widget_max, "\n");
  widget_set_string(Form1, 1, widget_max, "\n");
 }
 end();
}

