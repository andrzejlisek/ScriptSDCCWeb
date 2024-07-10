#include "core.h"
#include "console.h"
#include "widget.h"

volatile uchar Engine;

void __interrupt1(void)
{
 console_clear();
 console_string("Raised interrupt 1");
 console_print();

 uchar Temp;
 switch (event_widget)
 {
  case 21:
   Temp = widget_get_uchar_v(Engine, 22, widget_value);
   Temp = !Temp;
   widget_set_uchar_v(Engine, 22, widget_value, Temp);
   break;
  case 25:
   Temp = widget_get_uchar_v(Engine, 26, widget_value);
   Temp = !Temp;
   widget_set_uchar_v(Engine, 26, widget_value, Temp);
   break;
  case 41:
   Temp = widget_get_uchar_v(Engine, 42, widget_value);
   Temp = !Temp;
   widget_set_uchar_v(Engine, 42, widget_value, Temp);
   break;
  case 45:
   Temp = widget_get_uchar_v(Engine, 46, widget_value);
   Temp = !Temp;
   widget_set_uchar_v(Engine, 46, widget_value, Temp);
   break;
 }
}

void __interrupt2(void)
{
 console_clear();
 console_string("Raised interrupt 2");
 console_print();

 uchar Temp;
 switch (event_widget)
 {
  case 31:
   Temp = widget_get_uchar_v(Engine, 32, widget_value);
   Temp = !Temp;
   widget_set_uchar_v(Engine, 32, widget_value, Temp);
   break;
  case 35:
   Temp = widget_get_uchar_v(Engine, 36, widget_value);
   Temp = !Temp;
   widget_set_uchar_v(Engine, 36, widget_value, Temp);
   break;
  case 41:
   Temp = widget_get_uchar_v(Engine, 43, widget_value);
   Temp = !Temp;
   widget_set_uchar_v(Engine, 43, widget_value, Temp);
   break;
  case 45:
   Temp = widget_get_uchar_v(Engine, 47, widget_value);
   Temp = !Temp;
   widget_set_uchar_v(Engine, 47, widget_value, Temp);
   break;
 }
}

void main(void)
{
 Engine = engine_number();

 widget_clear(Engine);
 widget_add(Engine, 1, 0); widget_set_sint(Engine, 1, widget_size, 25); widget_set_sint(Engine, 1, widget_orientation, widget_horizontal);
 widget_add(Engine, 2, 0); widget_set_sint(Engine, 2, widget_size, 25); widget_set_sint(Engine, 2, widget_orientation, widget_horizontal);
 widget_add(Engine, 3, 0); widget_set_sint(Engine, 3, widget_size, 25); widget_set_sint(Engine, 3, widget_orientation, widget_horizontal);
 widget_add(Engine, 4, 0); widget_set_sint(Engine, 4, widget_size, 25); widget_set_sint(Engine, 4, widget_orientation, widget_horizontal);


 widget_add(Engine, 11, 1);
 widget_set_sint(Engine, 11, widget_size, 32);
 widget_set_sint(Engine, 11, widget_type, widget_label);

 widget_add(Engine, 12, 1);
 widget_set_sint(Engine, 12, widget_size, 18);
 widget_set_sint(Engine, 12, widget_type, widget_switch);

 widget_add(Engine, 15, 1);
 widget_set_sint(Engine, 15, widget_size, 32);
 widget_set_sint(Engine, 15, widget_type, widget_button);
 widget_set_string(Engine, 15, widget_value, "Run script");
 widget_set_sint(Engine, 15, widget_event, widget_runscript);

 widget_add(Engine, 16, 1);
 widget_set_sint(Engine, 16, widget_size, 18);
 widget_set_sint(Engine, 16, widget_type, widget_switch);


 widget_add(Engine, 21, 2);
 widget_set_sint(Engine, 21, widget_size, 32);
 widget_set_sint(Engine, 21, widget_type, widget_button);
 widget_set_string(Engine, 21, widget_value, "Interrupt 1");
 widget_set_sint(Engine, 21, widget_event, widget_interrupt1);

 widget_add(Engine, 22, 2);
 widget_set_sint(Engine, 22, widget_size, 18);
 widget_set_sint(Engine, 22, widget_type, widget_switch);

 widget_add(Engine, 25, 2);
 widget_set_sint(Engine, 25, widget_size, 32);
 widget_set_sint(Engine, 25, widget_type, widget_button);
 widget_set_string(Engine, 25, widget_value, "Int 1 and run");
 widget_set_sint(Engine, 25, widget_event, widget_interrupt1 | widget_runscript);

 widget_add(Engine, 26, 2);
 widget_set_sint(Engine, 26, widget_size,  9);
 widget_set_sint(Engine, 26, widget_type, widget_switch);

 widget_add(Engine, 27, 2);
 widget_set_sint(Engine, 27, widget_size,  9);
 widget_set_sint(Engine, 27, widget_type, widget_switch);


 widget_add(Engine, 31, 3);
 widget_set_sint(Engine, 31, widget_size, 32);
 widget_set_sint(Engine, 31, widget_type, widget_button);
 widget_set_string(Engine, 31, widget_value, "Interrupt 2");
 widget_set_sint(Engine, 31, widget_event, widget_interrupt2);

 widget_add(Engine, 32, 3);
 widget_set_sint(Engine, 32, widget_size, 18);
 widget_set_sint(Engine, 32, widget_type, widget_switch);

 widget_add(Engine, 35, 3);
 widget_set_sint(Engine, 35, widget_size, 32);
 widget_set_sint(Engine, 35, widget_type, widget_button);
 widget_set_string(Engine, 35, widget_value, "Int 2 and run");
 widget_set_sint(Engine, 35, widget_event, widget_interrupt2 | widget_runscript);

 widget_add(Engine, 36, 3);
 widget_set_sint(Engine, 36, widget_size,  9);
 widget_set_sint(Engine, 36, widget_type, widget_switch);

 widget_add(Engine, 37, 3);
 widget_set_sint(Engine, 37, widget_size,  9);
 widget_set_sint(Engine, 37, widget_type, widget_switch);


 widget_add(Engine, 41, 4);
 widget_set_sint(Engine, 41, widget_size, 32);
 widget_set_sint(Engine, 41, widget_type, widget_button);
 widget_set_string(Engine, 41, widget_value, "Both ints");
 widget_set_sint(Engine, 41, widget_event, widget_interrupt1 | widget_interrupt2);

 widget_add(Engine, 42, 4);
 widget_set_sint(Engine, 42, widget_size,  9);
 widget_set_sint(Engine, 42, widget_type, widget_switch);

 widget_add(Engine, 43, 4);
 widget_set_sint(Engine, 43, widget_size,  9);
 widget_set_sint(Engine, 43, widget_type, widget_switch);

 widget_add(Engine, 45, 4);
 widget_set_sint(Engine, 45, widget_size, 32);
 widget_set_sint(Engine, 45, widget_type, widget_button);
 widget_set_string(Engine, 45, widget_value, "Both ints and run");
 widget_set_sint(Engine, 45, widget_event, widget_interrupt1 | widget_interrupt2 | widget_runscript);

 widget_add(Engine, 46, 4);
 widget_set_sint(Engine, 46, widget_size,  6);
 widget_set_sint(Engine, 46, widget_type, widget_switch);

 widget_add(Engine, 47, 4);
 widget_set_sint(Engine, 47, widget_size,  6);
 widget_set_sint(Engine, 47, widget_type, widget_switch);

 widget_add(Engine, 48, 4);
 widget_set_sint(Engine, 48, widget_size,  6);
 widget_set_sint(Engine, 48, widget_type, widget_switch);


 uchar Temp;
 short LoopWidgetIterations = 0;
 uint RunIndicator = 0;
 while (1)
 {
  LoopWidgetIterations++;
  if (LoopWidgetIterations == 0)
  {
   if (widget_get_uchar_v(Engine, 12, widget_value))
   {
    console_clear();
    console_string("Script stopped");
    console_print();

    stop();
   }
  
   RunIndicator++;
   widget_set_uint(Engine, 11, widget_value, RunIndicator);
  }
 
  switch (event_widget)
  {
   case 15:
    Temp = widget_get_uchar_v(Engine, 16, widget_value);
    Temp = !Temp;
    widget_set_uchar_v(Engine, 16, widget_value, Temp);
    event_widget = 0;
    break;
   case 25:
    Temp = widget_get_uchar_v(Engine, 27, widget_value);
    Temp = !Temp;
    widget_set_uchar_v(Engine, 27, widget_value, Temp);
    event_widget = 0;
    break;
   case 35:
    Temp = widget_get_uchar_v(Engine, 37, widget_value);
    Temp = !Temp;
    widget_set_uchar_v(Engine, 37, widget_value, Temp);
    event_widget = 0;
    break;
   case 45:
    Temp = widget_get_uchar_v(Engine, 48, widget_value);
    Temp = !Temp;
    widget_set_uchar_v(Engine, 48, widget_value, Temp);
    event_widget = 0;
    break;
  }
 }
}

