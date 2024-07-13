#include "core.h"
#include "graph.h"
#include "random.h"
#include "memo.h"
#include "graphtext.h"

void Repaint(int BoardHalfSize, int Progress)
{
 uchar Engine = engine_number();
 uchar EngineInfo = Engine + 1;

 int BoardSize = BoardHalfSize + BoardHalfSize;
 
 // Clear the graphics screen
 graph_clear(Engine);
 graph_clear(EngineInfo);
 graph_text_color_f(EngineInfo, 255, 255, 255);
 graph_text_move(EngineInfo, 0, 0, 0);

 string_set_sint(Progress);
 string_append("/16");

 graph_text_string(EngineInfo, 0);

 // Paint the board
 long BoardIdx = 0;
 for (int I = 0; I < BoardSize; I++)
 {
  char PaintPoint = I & 1;
  for (int II = 0; II < BoardSize; II++)
  {
   if (PaintPoint)
   {
    int Val = memo_get_sint(0, BoardIdx);
    graph_plot_sint(Engine, II - BoardHalfSize, I - BoardHalfSize, Val, 128, 128, 128);
   }
   PaintPoint = !PaintPoint;
   BoardIdx++;
  }
  PaintPoint = !PaintPoint;
 }
}

void main(void)
{
 // The half of board size
 int BoardHalfSize = 256;

 // Number of iterations
 long Iter = 16384; 

 // The local memo 0 will be used as path board
 memo_local_shared(128);
 memo_clear_dense(0);

 // Progress indicator
 int Progress = 1;

 // Paint blank board
 Repaint(BoardHalfSize, 0);

 long BoardSizeL = BoardHalfSize + BoardHalfSize;
 while (Iter > 0)
 {
  // Create random path
  long T = BoardHalfSize;
  for (long I = 0; I < BoardSizeL; I++)
  {
   T += (random_get_sint(0, 1) * 2) - 1;

   if ((T >= 0) && (T < BoardSizeL))
   {
    long BoardIdx = I * (BoardSizeL) + T;
    memo_set_sint(0, BoardIdx, memo_get_sint(0, BoardIdx) + 1);
   }
  }
  Iter--;

  // Repaint board every 1024 iterations
  if ((Iter & 1023) == 0)
  {
   Repaint(BoardHalfSize, Progress);
   Progress++;
  }
 }

 // Program end
 end();
}

