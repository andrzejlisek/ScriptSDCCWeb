#define IOGraphTextCmd 15

// Sets text color
// CanvasId - Canvas number
// DispBackFore - 0 => Transparent background and foreground
//                1 => Transparent background, opaque foreground
//                2 => Opaque background, transparent foreground
//                3 => Opaque background and foreground
// ColorBackR, ColorBackG, ColorBackB - Background color
// ColorForeR, ColorForeG, ColorForeB - Foreground color
void graph_text_color(uchar CanvasId, uchar DispBackFore, uchar ColorBackR, uchar ColorBackG, uchar ColorBackB, uchar ColorForeR, uchar ColorForeG, uchar ColorForeB)
{
 _uchar[mem_swap + 1] = CanvasId;
 _uchar[mem_swap + 2] = DispBackFore;
 _uchar[mem_swap + 3] = ColorBackR;
 _uchar[mem_swap + 4] = ColorBackG;
 _uchar[mem_swap + 5] = ColorBackB;
 _uchar[mem_swap + 6] = ColorForeR;
 _uchar[mem_swap + 7] = ColorForeG;
 _uchar[mem_swap + 8] = ColorForeB;
 _uchar[mem_swap] = IOGraphTextCmd + 0;
}

// Allows to simplify define colors when only background or only foreground color is needed
// CanvasId - Canvas number
// R, G, B - Text color
#define graph_text_color_f(CanvasId, R, G, B) graph_text_color(CanvasId, 1, 0, 0, 0, R, G, B)
#define graph_text_color_b(CanvasId, R, G, B) graph_text_color(CanvasId, 2, R, G, B, 0, 0, 0)

// Sets text paint coordinates
// CanvasId - Canvas number
// X, Y, Z - Text base point coordinates
void graph_text_xyz_schar( uchar CanvasId,  schar X,  schar Y,  schar Z) { core_io1.val_schar  = X; core_io2.val_schar  = Y; core_io3.val_schar  = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 0;  _uchar[mem_swap] = IOGraphTextCmd + 1; }
void graph_text_xyz_uchar( uchar CanvasId,  uchar X,  uchar Y,  uchar Z) { core_io1.val_uchar  = X; core_io2.val_uchar  = Y; core_io3.val_uchar  = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 1;  _uchar[mem_swap] = IOGraphTextCmd + 1; }
void graph_text_xyz_sshort(uchar CanvasId, sshort X, sshort Y, sshort Z) { core_io1.val_sshort = X; core_io2.val_sshort = Y; core_io3.val_sshort = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 4;  _uchar[mem_swap] = IOGraphTextCmd + 1; }
void graph_text_xyz_ushort(uchar CanvasId, ushort X, ushort Y, ushort Z) { core_io1.val_ushort = X; core_io2.val_ushort = Y; core_io3.val_ushort = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 5;  _uchar[mem_swap] = IOGraphTextCmd + 1; }
void graph_text_xyz_sint(  uchar CanvasId,   sint X,   sint Y,   sint Z) { core_io1.val_sint   = X; core_io2.val_sint   = Y; core_io3.val_sint   = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 6;  _uchar[mem_swap] = IOGraphTextCmd + 1; }
void graph_text_xyz_uint(  uchar CanvasId,   uint X,   uint Y,   uint Z) { core_io1.val_uint   = X; core_io2.val_uint   = Y; core_io3.val_uint   = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 7;  _uchar[mem_swap] = IOGraphTextCmd + 1; }
void graph_text_xyz_slong( uchar CanvasId,  slong X,  slong Y,  slong Z) { core_io1.val_slong  = X; core_io2.val_slong  = Y; core_io3.val_slong  = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 8;  _uchar[mem_swap] = IOGraphTextCmd + 1; }
void graph_text_xyz_ulong( uchar CanvasId,  ulong X,  ulong Y,  ulong Z) { core_io1.val_ulong  = X; core_io2.val_ulong  = Y; core_io3.val_ulong  = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 9;  _uchar[mem_swap] = IOGraphTextCmd + 1; }
void graph_text_xyz_float( uchar CanvasId,  float X,  float Y,  float Z) { core_io1.val_float  = X; core_io2.val_float  = Y; core_io3.val_float  = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 10; _uchar[mem_swap] = IOGraphTextCmd + 1; }

// Paints value as text
// CanvasId - Canvas number
// V - Value to paint
// graph_text_schar_v, graph_text_uchar_v - paints value as number
// graph_text_schar_t, graph_text_uchar_t - paints value as 1-character text
void graph_text_schar_v(uchar CanvasId, schar V)  { schar V_ = V;  _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] =  0; core_io0.val_schar  = V_; _uchar[mem_swap] = IOGraphTextCmd + 2; }
void graph_text_uchar_v(uchar CanvasId, uchar V)  { uchar V_ = V;  _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] =  1; core_io0.val_uchar  = V_; _uchar[mem_swap] = IOGraphTextCmd + 2; }
void graph_text_schar_t(uchar CanvasId, schar V)  { schar V_ = V;  _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] =  2; core_io0.val_schar  = V_; _uchar[mem_swap] = IOGraphTextCmd + 2; }
void graph_text_uchar_t(uchar CanvasId, uchar V)  { uchar V_ = V;  _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] =  3; core_io0.val_uchar  = V_; _uchar[mem_swap] = IOGraphTextCmd + 2; }
void graph_text_sshort( uchar CanvasId, sshort V) { sshort V_ = V; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] =  4; core_io0.val_sshort = V_; _uchar[mem_swap] = IOGraphTextCmd + 2; }
void graph_text_ushort( uchar CanvasId, ushort V) { ushort V_ = V; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] =  5; core_io0.val_ushort = V_; _uchar[mem_swap] = IOGraphTextCmd + 2; }
void graph_text_sint(   uchar CanvasId, sint V)   { sint V_ = V;   _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] =  6; core_io0.val_sint   = V_; _uchar[mem_swap] = IOGraphTextCmd + 2; }
void graph_text_uint(   uchar CanvasId, uint V)   { uint V_ = V;   _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] =  7; core_io0.val_uint   = V_; _uchar[mem_swap] = IOGraphTextCmd + 2; }
void graph_text_slong(  uchar CanvasId, slong V)  { slong V_ = V;  _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] =  8; core_io0.val_slong  = V_; _uchar[mem_swap] = IOGraphTextCmd + 2; }
void graph_text_ulong(  uchar CanvasId, ulong V)  { ulong V_ = V;  _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] =  9; core_io0.val_ulong  = V_; _uchar[mem_swap] = IOGraphTextCmd + 2; }
void graph_text_float(  uchar CanvasId, float V)  { float V_ = V;  _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 10; core_io0.val_float  = V_; _uchar[mem_swap] = IOGraphTextCmd + 2; }

// Paints specified string
// CanvasId - Canvas number
// V - Null-terminated string to paint
void graph_text_string(uchar CanvasId, char * V)
{
 if (V != 0) string_set(V);
 _uchar[mem_swap + 1] = CanvasId;
 _uchar[mem_swap + 2] = 11;
 _uchar[mem_swap] = IOGraphTextCmd + 2;
}

// Moves text cursor across the screen
// CanvasId - Canvas number
// X - Horizontal movement by halves of character width
// Y - Vertical movement by halves of character height
// Mode=0 - Absolute
// Mode=1 - Relative
void graph_text_move(uchar CanvasId, short X, short Y, uchar Mode)
{
 _uchar[mem_swap + 1] = CanvasId;
 core_io0.val_sshort = X;
 core_io1.val_sshort = Y;
 _uchar[mem_swap + 2] = Mode;
 _uchar[mem_swap] = IOGraphTextCmd + 3;
}

