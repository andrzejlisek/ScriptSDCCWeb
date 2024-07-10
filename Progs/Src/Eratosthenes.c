#include "core.h"
#include "graph.h"
#include "graphtext.h"

char Sieve[102];



// Frame characters in UTF-8 format
#define FrameNW "\xE2\x94\x8C"
#define FrameSW "\xE2\x94\x94"
#define FrameNE "\xE2\x94\x90"
#define FrameSE "\xE2\x94\x98"
#define FrameN  "\xE2\x94\xAC"
#define FrameS  "\xE2\x94\xB4"
#define FrameE  "\xE2\x94\xA4"
#define FrameW  "\xE2\x94\x9C"
#define FrameH  "\xE2\x94\x80"
#define FrameV  "\xE2\x94\x82"
#define FrameC  "\xE2\x94\xBC"


void main(void)
{
 // Engine number
 uchar Engine = engine_number();

 // Clear the graph screen
 graph_clear(Engine);

 // White color of text
 graph_text_color_f(Engine, 255, 255, 255);

 // Lines and crosses
 for (int Y = 0; Y < 10; Y++)
 {
  for (int X = 0; X < 10; X++)
  {
   graph_text_move(Engine, X * 6 - 24, Y * 4 - 18, 0); graph_text_string(Engine, FrameV);
   graph_text_move(Engine, X * 6 - 28, Y * 4 - 16, 0); graph_text_string(Engine, FrameH);
   graph_text_move(Engine, X * 6 - 26, Y * 4 - 16, 0); graph_text_string(Engine, FrameH);
   
   if ((Y > 0) && (X > 0))
   {
    graph_text_move(Engine, X * 6 - 30, Y * 4 - 20, 0); graph_text_string(Engine, FrameC);
   }
  }
 }

 // Additional horizontal and vertical lines
 for (int I = 0; I < 10; I++)
 {
  graph_text_move(Engine, I * 6 - 28, -20, 0); graph_text_string(Engine, FrameH);
  graph_text_move(Engine, I * 6 - 26, -20, 0); graph_text_string(Engine, FrameH);
  graph_text_move(Engine, -30, I * 4 - 18, 0); graph_text_string(Engine, FrameV);
 }

 // Edge connections
 for (int I = 0; I < 9; I++)
 {
  graph_text_move(Engine, I * 6 - 24, -20, 0); graph_text_string(Engine, FrameN);
  graph_text_move(Engine, I * 6 - 24,  20, 0); graph_text_string(Engine, FrameS);
  graph_text_move(Engine, -30, I * 4 - 16, 0); graph_text_string(Engine, FrameW);
  graph_text_move(Engine,  30, I * 4 - 16, 0); graph_text_string(Engine, FrameE);
 }

 // Corners
 graph_text_move(Engine,  30, -20, 0); graph_text_string(Engine, FrameNE);
 graph_text_move(Engine,  30,  20, 0); graph_text_string(Engine, FrameSE);
 graph_text_move(Engine, -30, -20, 0); graph_text_string(Engine, FrameNW);
 graph_text_move(Engine, -30,  20, 0); graph_text_string(Engine, FrameSW);

 // Filling in the sieve
 Sieve[1] = 0;
 for (int I = 2; I <= 100; I++)
 {
  Sieve[I] = 1;
 }

 // Creating the sieve
 for (int I = 2; I <= 10; I++)
 {
  int N = I + I;
  while (N <= 100)
  {
   Sieve[N] = 0;
   N = N + I;
  }
 }

 // Drawing the numbers
 graph_text_move(Engine, -27, -18, 0);
 for (int Y = 0; Y < 10; Y++)
 {
  for (int X = 0; X < 10; X++)
  {
   int N = Y * 10 + X + 1;
   if (Sieve[N])
   {
    graph_text_sint(Engine, N);
   }
   graph_text_move(Engine, 6, 0, 1);
  }
  graph_text_move(Engine, -60, 4, 1);
 }

 // Program end
 end();
}

