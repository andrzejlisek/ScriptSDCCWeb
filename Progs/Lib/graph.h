#define IOGraphCmd 10

// Clears whole graphics
// CanvasId - Canvas number
void inline graph_clear(uchar CanvasId)
{
 _uchar[mem_swap + 1] = CanvasId;
 _uchar[mem_swap] = IOGraphCmd + 0;
}

// Sets polyline thread
// CanvasId - Canvas number
// Thr - Thread number
void inline graph_thread(uchar CanvasId, uchar Thr)
{
 _uchar[mem_swap + 1] = CanvasId;
 _uchar[mem_swap + 2] = Thr;
 _uchar[mem_swap] = IOGraphCmd + 1;
}

// Resets current polyline thread
// CanvasId - Canvas number
void inline graph_thread_reset(uchar CanvasId)
{
 _uchar[mem_swap + 1] = CanvasId;
 _uchar[mem_swap] = IOGraphCmd + 2;
}

// Sets points on screen
// CanvasId - Canvas number
// X, Y, Z - Point coordinates
// R, G, B - Point color
void graph_plot_schar( uchar CanvasId,  schar X,  schar Y,  schar Z, uchar R, uchar G, uchar B) { core_io1.val_schar  = X; core_io2.val_schar  = Y; core_io3.val_schar  = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 0;  _uchar[mem_swap + 3] = R; _uchar[mem_swap + 4] = G; _uchar[mem_swap + 5] = B; _uchar[mem_swap] = IOGraphCmd + 3; }
void graph_plot_uchar( uchar CanvasId,  uchar X,  uchar Y,  uchar Z, uchar R, uchar G, uchar B) { core_io1.val_uchar  = X; core_io2.val_uchar  = Y; core_io3.val_uchar  = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 1;  _uchar[mem_swap + 3] = R; _uchar[mem_swap + 4] = G; _uchar[mem_swap + 5] = B; _uchar[mem_swap] = IOGraphCmd + 3; }
void graph_plot_sshort(uchar CanvasId, sshort X, sshort Y, sshort Z, uchar R, uchar G, uchar B) { core_io1.val_sshort = X; core_io2.val_sshort = Y; core_io3.val_sshort = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 4;  _uchar[mem_swap + 3] = R; _uchar[mem_swap + 4] = G; _uchar[mem_swap + 5] = B; _uchar[mem_swap] = IOGraphCmd + 3; }
void graph_plot_ushort(uchar CanvasId, ushort X, ushort Y, ushort Z, uchar R, uchar G, uchar B) { core_io1.val_ushort = X; core_io2.val_ushort = Y; core_io3.val_ushort = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 5;  _uchar[mem_swap + 3] = R; _uchar[mem_swap + 4] = G; _uchar[mem_swap + 5] = B; _uchar[mem_swap] = IOGraphCmd + 3; }
void graph_plot_sint(  uchar CanvasId,   sint X,   sint Y,   sint Z, uchar R, uchar G, uchar B) { core_io1.val_sint   = X; core_io2.val_sint   = Y; core_io3.val_sint   = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 6;  _uchar[mem_swap + 3] = R; _uchar[mem_swap + 4] = G; _uchar[mem_swap + 5] = B; _uchar[mem_swap] = IOGraphCmd + 3; }
void graph_plot_uint(  uchar CanvasId,   uint X,   uint Y,   uint Z, uchar R, uchar G, uchar B) { core_io1.val_uint   = X; core_io2.val_uint   = Y; core_io3.val_uint   = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 7;  _uchar[mem_swap + 3] = R; _uchar[mem_swap + 4] = G; _uchar[mem_swap + 5] = B; _uchar[mem_swap] = IOGraphCmd + 3; }
void graph_plot_slong( uchar CanvasId,  slong X,  slong Y,  slong Z, uchar R, uchar G, uchar B) { core_io1.val_slong  = X; core_io2.val_slong  = Y; core_io3.val_slong  = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 8;  _uchar[mem_swap + 3] = R; _uchar[mem_swap + 4] = G; _uchar[mem_swap + 5] = B; _uchar[mem_swap] = IOGraphCmd + 3; }
void graph_plot_ulong( uchar CanvasId,  ulong X,  ulong Y,  ulong Z, uchar R, uchar G, uchar B) { core_io1.val_ulong  = X; core_io2.val_ulong  = Y; core_io3.val_ulong  = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 9;  _uchar[mem_swap + 3] = R; _uchar[mem_swap + 4] = G; _uchar[mem_swap + 5] = B; _uchar[mem_swap] = IOGraphCmd + 3; }
void graph_plot_float( uchar CanvasId,  float X,  float Y,  float Z, uchar R, uchar G, uchar B) { core_io1.val_float  = X; core_io2.val_float  = Y; core_io3.val_float  = Z; _uchar[mem_swap + 1] = CanvasId; _uchar[mem_swap + 2] = 10; _uchar[mem_swap + 3] = R; _uchar[mem_swap + 4] = G; _uchar[mem_swap + 5] = B; _uchar[mem_swap] = IOGraphCmd + 3; }

// Converts last points to polyline
// CanvasId - Canvas number
// Points > 0 - Number of last points to convert
// Points = 0 - Create triangle
void inline graph_line(uchar CanvasId, uchar Points)
{
 _uchar[mem_swap + 1] = CanvasId;
 _uchar[mem_swap + 2] = Points;
 _uchar[mem_swap] = IOGraphCmd + 4;
}

// Converts last three points to triangle
// CanvasId - Graph number
#define graph_triangle(CanvasId) graph_line(CanvasId, 0)

