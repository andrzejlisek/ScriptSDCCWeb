/*
Draws paraboloid on Graph 1 using lines, on Graph 2 and Graph 3 using triangles.
*/

#include "core.h"
#include "graph.h"
#include "mathx.h"

void main(void)
{
 float X1, Y1, X2, Y2, Z11, Z12, Z21, Z22, X0, Y0, Z0;
 int XI, YI;
 uchar ColorR = 128;
 uchar ColorG = 128;
 uchar ColorB = 128;

 uchar Graph0 = engine_number();
 uchar Graph1 = (Graph0 + 1) & 15;
 uchar Graph2 = (Graph0 + 2) & 15;

 graph_clear(Graph0);
 graph_clear(Graph1);
 graph_clear(Graph2);

 for (YI = -10; YI < 10; YI++)
 {
  for (XI = -10; XI < 10; XI++)
  {
   X1 = XI;
   Y1 = YI;
   X2 = XI + 1;
   Y2 = YI + 1;
   Z11 = (X1 * X1) + (Y1 * Y1) - 100.0;
   Z12 = (X1 * X1) + (Y2 * Y2) - 100.0;
   Z21 = (X2 * X2) + (Y1 * Y1) - 100.0;
   Z22 = (X2 * X2) + (Y2 * Y2) - 100.0;
   X1 = X1 * 10;
   Y1 = Y1 * 10;
   X2 = X2 * 10;
   Y2 = Y2 * 10;

   graph_plot_float(Graph0, X1, Y1, Z11, ColorR, ColorG, ColorB);
   graph_plot_float(Graph0, X1, Y2, Z12, ColorR, ColorG, ColorB);
   graph_plot_float(Graph0, X2, Y2, Z22, ColorR, ColorG, ColorB);
   graph_plot_float(Graph0, X2, Y1, Z21, ColorR, ColorG, ColorB);
   graph_plot_float(Graph0, X1, Y1, Z11, ColorR, ColorG, ColorB);
   graph_line(Graph0, 4);

   graph_plot_float(Graph1, X1, Y1, Z11, ColorR, ColorG, ColorB);
   graph_plot_float(Graph1, X1, Y2, Z12, ColorR, ColorG, ColorB);
   graph_plot_float(Graph1, X2, Y1, Z21, ColorR, ColorG, ColorB);
   graph_triangle(Graph1);
   graph_plot_float(Graph1, X2, Y2, Z22, ColorR, ColorG, ColorB);
   graph_triangle(Graph1);

   X0 = (X1 + X2) / 2.0;
   Y0 = (Y1 + Y2) / 2.0;
   Z0 = (Z11 + Z12 + Z21 + Z22) / 4.0;

   graph_plot_float(Graph2, X1, Y2, Z12, ColorR, ColorG, ColorB);
   graph_plot_float(Graph2, X1, Y1, Z11, ColorR, ColorG, ColorB);
   graph_plot_float(Graph2, X0, Y0, Z0,  ColorR, ColorG, ColorB);
   graph_triangle(Graph2);
   graph_plot_float(Graph2, X2, Y1, Z21, ColorR, ColorG, ColorB);
   graph_triangle(Graph2);
   graph_plot_float(Graph2, X2, Y2, Z22, ColorR, ColorG, ColorB);
   graph_plot_float(Graph2, X0, Y0, Z0,  ColorR, ColorG, ColorB);
   graph_triangle(Graph2);
   graph_plot_float(Graph2, X1, Y2, Z12, ColorR, ColorG, ColorB);
   graph_triangle(Graph2);
  }
 }

 end();
}

