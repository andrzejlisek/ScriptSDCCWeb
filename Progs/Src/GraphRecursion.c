#include "core.h"
#include "graph.h"
#include "mathx.h"
#include "console.h"

uchar Graph;

void printnum(short N)
{
 if (abs_(N) < 100) { console_schar_t(' '); }
 if (abs_(N) < 10) { console_schar_t(' '); }
 if (N >= 0) { console_schar_t(' '); }
 console_sshort(N);
}

void draw(char T, short X1, short Y1, short X2, short Y2) __reentrant
{
 console_clear();
 console_string("Call    T=");
 console_schar_v(T);
 console_string("      X1=");
 printnum(X1);
 console_string("      Y1=");
 printnum(Y1);
 console_string("      X2=");
 printnum(X2);
 console_string("      Y2=");
 printnum(Y2);
 console_print();
 if (T == 0)
 {
  short DX = (X2 - X1) / 8;
  short DY = (Y2 - Y1) / 8;
  short X_ = abs_(X1) + abs_(X2);
  short Y_ = abs_(Y1) + abs_(Y2);
  short Z = (X_ > Y_) ? X_ : Y_;
  graph_thread_reset(Graph);
  graph_plot_sshort(Graph, X1 + DX, Y1 + DY, Z, 255, 255, 255);
  graph_plot_sshort(Graph, X1 + DX, Y2 - DY, Z, 255, 255, 255);
  graph_plot_sshort(Graph, X2 - DX, Y2 - DY, Z, 255, 255, 255);
  graph_plot_sshort(Graph, X2 - DX, Y1 + DY, Z, 255, 255, 255);
  graph_plot_sshort(Graph, X1 + DX, Y1 + DY, Z, 255, 255, 255);
 }
 else
 {
  short XS1 = X1 + (X2 - X1) / 2;
  short YS1 = Y1 + (Y2 - Y1) / 2;
  draw(T - 1, X1,  Y1,  XS1, YS1);
  draw(T - 1, XS1, Y1,  X2,  YS1);
  draw(T - 1, X1,  YS1, XS1, Y2);
  draw(T - 1, XS1, YS1, X2,  Y2);
 }
 console_clear();
 console_string("Return  T=");
 console_schar_v(T);
 console_string("      X1=");
 printnum(X1);
 console_string("      Y1=");
 printnum(Y1);
 console_string("      X2=");
 printnum(X2);
 console_string("      Y2=");
 printnum(Y2);
 console_print();
}

void main(void)
{
 Graph = engine_number();
 graph_clear(Graph);
 graph_thread(Graph, 1);
 draw(4, -128, -128, 128, 128);
 end();
}

