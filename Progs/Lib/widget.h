#define IOWidgetCmd 4

// Clear the form
void widget_clear(uchar FormId)
{
 _uchar[mem_swap + 1] = FormId;
 _uchar[mem_swap] = IOWidgetCmd + 0;
}

// Add widget to the form
void widget_add(uchar FormId, uchar WidgetId, uchar ParentWidgetId)
{
 _uchar[mem_swap + 1] = FormId;
 _uchar[mem_swap + 2] = WidgetId;
 _uchar[mem_swap + 3] = ParentWidgetId;
 _uchar[mem_swap] = IOWidgetCmd + 1;
}

// Remove widget from the form
void widget_remove(uchar FormId, uchar WidgetId)
{
 _uchar[mem_swap + 1] = FormId;
 _uchar[mem_swap + 2] = WidgetId;
 _uchar[mem_swap] = IOWidgetCmd + 2;
}

// Widget types
#define widget_group 0
#define widget_label 1
#define widget_button 2
#define widget_switch 3
#define widget_text 4
#define widget_slider 5
#define widget_multiline 6

// Widget parameters
#define widget_type 127
#define widget_size 126
#define widget_event 125
#define widget_event_add 124
#define widget_event_rem 123
#define widget_value 0
#define widget_orientation 1
#define widget_min 2
#define widget_max 3

// Widget orientation values
#define widget_vertical 0
#define widget_horizontal 1

// Widget event types
#define widget_interrupt1 1
#define widget_interrupt2 2
#define widget_runscript 4

// Form and widget identifier after raising event
#define event_form _uchar[mem_swap + 255]
#define event_widget _uchar[mem_swap + 254]

// Set widget property as number
void widget_set_schar_v(uchar FormId, uchar WidgetId, uchar Param, schar  Value) { schar  Value_ = Value; _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  0; core_io0.val_schar  = Value_; _uchar[mem_swap] = IOWidgetCmd + 3; }
void widget_set_uchar_v(uchar FormId, uchar WidgetId, uchar Param, uchar  Value) { uchar  Value_ = Value; _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  1; core_io0.val_uchar  = Value_; _uchar[mem_swap] = IOWidgetCmd + 3; }
void widget_set_schar_t(uchar FormId, uchar WidgetId, uchar Param, schar  Value) { schar  Value_ = Value; _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  2; core_io0.val_schar  = Value_; _uchar[mem_swap] = IOWidgetCmd + 3; }
void widget_set_uchar_t(uchar FormId, uchar WidgetId, uchar Param, uchar  Value) { uchar  Value_ = Value; _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  3; core_io0.val_uchar  = Value_; _uchar[mem_swap] = IOWidgetCmd + 3; }
void widget_set_sshort( uchar FormId, uchar WidgetId, uchar Param, sshort Value) { sshort Value_ = Value; _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  4; core_io0.val_sshort = Value_; _uchar[mem_swap] = IOWidgetCmd + 3; }
void widget_set_ushort( uchar FormId, uchar WidgetId, uchar Param, ushort Value) { ushort Value_ = Value; _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  5; core_io0.val_ushort = Value_; _uchar[mem_swap] = IOWidgetCmd + 3; }
void widget_set_sint(   uchar FormId, uchar WidgetId, uchar Param, sint   Value) { sint   Value_ = Value; _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  6; core_io0.val_sint   = Value_; _uchar[mem_swap] = IOWidgetCmd + 3; }
void widget_set_uint(   uchar FormId, uchar WidgetId, uchar Param, uint   Value) { uint   Value_ = Value; _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  7; core_io0.val_uint   = Value_; _uchar[mem_swap] = IOWidgetCmd + 3; }
void widget_set_slong(  uchar FormId, uchar WidgetId, uchar Param, slong  Value) { slong  Value_ = Value; _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  8; core_io0.val_slong  = Value_; _uchar[mem_swap] = IOWidgetCmd + 3; }
void widget_set_ulong(  uchar FormId, uchar WidgetId, uchar Param, ulong  Value) { ulong  Value_ = Value; _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  9; core_io0.val_ulong  = Value_; _uchar[mem_swap] = IOWidgetCmd + 3; }
void widget_set_float(  uchar FormId, uchar WidgetId, uchar Param, float  Value) { float  Value_ = Value; _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] = 10; core_io0.val_float  = Value_; _uchar[mem_swap] = IOWidgetCmd + 3; }

// Set widget property as string using string buffer
void widget_set_string(uchar FormId, uchar WidgetId, uchar Param, char * Value)
{
 if (Value != 0) string_set(Value);
 _uchar[mem_swap + 1] = FormId;
 _uchar[mem_swap + 2] = WidgetId;
 _uchar[mem_swap + 3] = Param;
 _uchar[mem_swap + 4] = 11;
 _uchar[mem_swap] = IOWidgetCmd + 3;
}

// Get widget property as number
schar  widget_get_schar_v(uchar FormId, uchar WidgetId, uchar Param) { _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  0; _uchar[mem_swap] = IOWidgetCmd + 4; return core_io0.val_schar;  }
uchar  widget_get_uchar_v(uchar FormId, uchar WidgetId, uchar Param) { _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  1; _uchar[mem_swap] = IOWidgetCmd + 4; return core_io0.val_uchar;  }
schar  widget_get_schar_t(uchar FormId, uchar WidgetId, uchar Param) { _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  2; _uchar[mem_swap] = IOWidgetCmd + 4; return core_io0.val_schar;  }
uchar  widget_get_uchar_t(uchar FormId, uchar WidgetId, uchar Param) { _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  3; _uchar[mem_swap] = IOWidgetCmd + 4; return core_io0.val_uchar;  }
sshort widget_get_sshort( uchar FormId, uchar WidgetId, uchar Param) { _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  4; _uchar[mem_swap] = IOWidgetCmd + 4; return core_io0.val_sshort; }
ushort widget_get_ushort( uchar FormId, uchar WidgetId, uchar Param) { _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  5; _uchar[mem_swap] = IOWidgetCmd + 4; return core_io0.val_ushort; }
sint   widget_get_sint(   uchar FormId, uchar WidgetId, uchar Param) { _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  6; _uchar[mem_swap] = IOWidgetCmd + 4; return core_io0.val_sint;   }
uint   widget_get_uint(   uchar FormId, uchar WidgetId, uchar Param) { _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  7; _uchar[mem_swap] = IOWidgetCmd + 4; return core_io0.val_uint;   }
slong  widget_get_slong(  uchar FormId, uchar WidgetId, uchar Param) { _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  8; _uchar[mem_swap] = IOWidgetCmd + 4; return core_io0.val_slong;  }
ulong  widget_get_ulong(  uchar FormId, uchar WidgetId, uchar Param) { _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] =  9; _uchar[mem_swap] = IOWidgetCmd + 4; return core_io0.val_ulong;  }
float  widget_get_float(  uchar FormId, uchar WidgetId, uchar Param) { _uchar[mem_swap + 1] = FormId; _uchar[mem_swap + 2] = WidgetId; _uchar[mem_swap + 3] = Param; _uchar[mem_swap + 4] = 10; _uchar[mem_swap] = IOWidgetCmd + 4; return core_io0.val_float;  }

// Get widget property as string using string buffer
ushort widget_get_string(uchar FormId, uchar WidgetId, uchar Param, char * Value, ushort ValueLen)
{
 _uchar[mem_swap + 1] = FormId;
 _uchar[mem_swap + 2] = WidgetId;
 _uchar[mem_swap + 3] = Param;
 _uchar[mem_swap + 4] = 11;
 _uchar[mem_swap] = IOWidgetCmd + 4;
 return string_get(Value, ValueLen);
}

// Raise the event of specified form and widget
void widget_raise_event(uchar FormId, uchar WidgetId)
{
 _uchar[mem_swap + 1] = FormId;
 _uchar[mem_swap + 2] = WidgetId;
 _uchar[mem_swap] = IOWidgetCmd + 5;
}

