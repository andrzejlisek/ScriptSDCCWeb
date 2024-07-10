#include "core.h"
#include "graph.h"
#include "mathx.h"
#include <math.h>

void main(void)
{
 int I;
 float Radius = 50.0;
 float T1, T2, T3, X, Y, Z;
 uchar Engine0 = engine_number();
 uchar Engine1 = Engine0 + 1;

 // Clear graphs
 graph_clear(Engine0);
 graph_clear(Engine1);
 graph_thread(Engine0, 1);
 graph_thread(Engine1, 1);

 for (I = 0; I <= 360; I++)
 {
  T3 = I;
  T1 = (T3 * M_PI_) / 180.0;
  T2 = (T3 * M_PI_) / 90.0;
  T3 = (T3 * M_PI_) / 60.0;

  // First knot parametric formula
  X = sinf(T1) + 2.0 * sinf(T2);
  Y = cosf(T1) - 2.0 * cosf(T2);
  Z = 0.0 - sinf(T3);
  graph_plot_float(Engine0, X * Radius, Y * Radius, Z * Radius, 128, 128, 128);

  // Second knot parametric formula
  X = (2.0 + cosf(T3)) * sinf(T2);
  Y = (2.0 + cosf(T3)) * cosf(T2) * (-1);
  Z = sinf(T3);
  graph_plot_float(Engine1, X * Radius, Y * Radius, Z * Radius, 128, 128, 128);

 } 
 end();
}

