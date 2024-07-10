#include "core.h"
#include "console.h"
#include "widget.h"

#include "Num/numdef.h"
#include "Num/numcore.h"
#include "Num/numbase.h"
#include "Num/numio.h"
#include "Num/numtaylor.h"
#include "Num/numround.h"
#include "Num/nummath.h"
#include "Num/numdebug.h"


#define RegWidget(X) (((X) < 13) ? (((X) * 4) + 21) : (((X) * 4) - 29))

#define NumStackSize 50

#define CONST_PI "3.1415926535897932384626433832795"
#define CONST_E "2.7182818284590452353602874713527"

char Temp[1000];
numElementType Num1[10];
numElementType Num2[10];

numDef(NumReg[26]);
numDef(NumStack[NumStackSize + 1]);
uchar NumStackI;
char DefReg = 23;

uint NumStackPointer;

#define CmdBufSize 200
uchar CmdBuf[CmdBufSize + 1];
int I, II;

char PrintRaw;
char DispRegPage;

uchar Widget0;
uchar Widget1;

void numPrint(int WidgetId, numPtr(N))
{
 if (WidgetId > 0)
 {
  if (PrintRaw)
  {
   numGetRaw(N, 0, Temp);
  }
  else
  {
   numGet(N, Temp);
  }
  widget_set_string(Widget0, WidgetId + 1, widget_value, Temp);
  if (WidgetId == RegWidget(DefReg))
  {
   widget_set_string(Widget1, 99, widget_value, Temp);
  }
 }
}

void errorPrint(uchar Test, char * Msg1, char * Msg2)
{
 widget_set_string(Widget0, RegWidget(DefReg) + 1, widget_value, Msg1);
 widget_set_string(Widget0, RegWidget(DefReg) + 1, widget_max, Msg2);
 widget_set_string(Widget1, 99, widget_value, Msg1);
 widget_set_string(Widget1, 99, widget_max, Msg2);
 if (Test)
 {
  console_clear();
  console_string(Msg1);
  console_string(Msg2);
  console_print();
 }
}

uchar CommandCompare(uchar * CmdWord)
{
 int I = 0;
 if (CmdBuf[0] == 0)
 {
  return 0;
 }
 while ((CmdBuf[I] != ' ') && (CmdBuf[I] != 0) && (CmdWord[I] != 0))
 {
  if (CmdBuf[I] != CmdWord[I])
  {
   return 0;
  }
  I++;
 }
 if ((CmdWord[I] == 0) && ((CmdBuf[I] == ' ') || (CmdBuf[I] == 0)))
 {
  return 1;
 }
 return 0;
}


void DisplayAllRegs(void)
{
 if (DispRegPage)
 {
  for (int WidgetI = 0; WidgetI < 13; WidgetI++)
  {
   widget_set_uint(Widget0, WidgetI * 4 + 21, widget_size, 0);
   widget_set_uint(Widget0, WidgetI * 4 + 22, widget_size, 0);
   widget_set_uint(Widget0, WidgetI * 4 + 23, widget_size, 10);
   widget_set_uint(Widget0, WidgetI * 4 + 24, widget_size, 90);
  }
 }
 else
 {
  for (int WidgetI = 0; WidgetI < 13; WidgetI++)
  {
   widget_set_uint(Widget0, WidgetI * 4 + 21, widget_size, 10);
   widget_set_uint(Widget0, WidgetI * 4 + 22, widget_size, 90);
   widget_set_uint(Widget0, WidgetI * 4 + 23, widget_size, 0);
   widget_set_uint(Widget0, WidgetI * 4 + 24, widget_size, 0);
  }
 }
 for (int I = 0; I < 26; I++)
 {
  numPrint(RegWidget(I), NumReg[I]);
 }
}




#define TokenBufSize 250
char TokenBuf[TokenBufSize];
uchar TokenBufI;
uchar TokenI;

#define TokenStackSize 20
char TokenStack[TokenBufSize];
char TokenStackS[TokenStackSize];
uchar TokenStackB;
uchar TokenStackI;

char TokenError;

uchar TokenCompare(uchar * TokenWord)
{
 int I = 0;
 while ((TokenBuf[I] != 0) && (TokenWord[I] != 0))
 {
  if (TokenBuf[I] != TokenWord[I])
  {
   return 0;
  }
  I++;
 }
 if ((TokenBuf[I] == 0) && (TokenWord[I] == 0))
 {
  return 1;
 }
 else
 {
  return 0;
 }
}

void CalcWork(uchar Test, uchar Op)
{
 uchar StackErr = 0;
 if (Test)
 {
  console_clear();
  console_string("                    ");
  console_uchar_t('[');
  console_uchar_v(Op);
  console_uchar_t(']');
  console_uchar_t('[');
  console_string(TokenBuf);
  console_uchar_t(']');
  console_print();
 }

 // Operator or function
 if (Op == 0)
 {
  if (TokenBuf[1] == 0)
  {
   if (NumStackI >= 2)
   {
    switch (TokenBuf[0])
    {
     case '+':
      NumStackI--;
      numAdd(NumStack[NumStackI - 1], NumStack[NumStackI], NumStack[NumStackI + 1]);
      numCopy(NumStack[NumStackI + 1], NumStack[NumStackI - 1]);
      break;
     case '-':
      NumStackI--;
      numSub(NumStack[NumStackI - 1], NumStack[NumStackI], NumStack[NumStackI + 1]);
      numCopy(NumStack[NumStackI + 1], NumStack[NumStackI - 1]);
      break;
     case '*':
      NumStackI--;
      numMul(NumStack[NumStackI - 1], NumStack[NumStackI], NumStack[NumStackI + 1]);
      numCopy(NumStack[NumStackI + 1], NumStack[NumStackI - 1]);
      break;
     case '/':
      NumStackI--;
      numDiv(NumStack[NumStackI - 1], NumStack[NumStackI], NumStack[NumStackI + 1]);
      numCopy(NumStack[NumStackI + 1], NumStack[NumStackI - 1]);
      break;
    }
   }
   else
   {
    if ((TokenBuf[0] == '+') | (TokenBuf[0] == '-') | (TokenBuf[0] == '*') | (TokenBuf[0] == '/'))
    {
     TokenBuf[1] = 0;
     TokenError = 1;
     errorPrint(Test, "Stack underflow by operator: ", TokenBuf);
    }
   }
  }
  else
  {
   StackErr = 1;
   if (NumStackI >= 1)
   {
    if (TokenCompare("SIN"))
    {
     StackErr = 0;
     numSin(NumStack[NumStackI - 1], NumStack[NumStackI]);
     numCopy(NumStack[NumStackI], NumStack[NumStackI - 1]);
    }
    if (TokenCompare("COS"))
    {
     StackErr = 0;
     numCos(NumStack[NumStackI - 1], NumStack[NumStackI]);
     numCopy(NumStack[NumStackI], NumStack[NumStackI - 1]);
    }
    if (TokenCompare("TAN"))
    {
     StackErr = 0;
     numTan(NumStack[NumStackI - 1], NumStack[NumStackI]);
     numCopy(NumStack[NumStackI], NumStack[NumStackI - 1]);
    }
    if (TokenCompare("COT"))
    {
     StackErr = 0;
     numCot(NumStack[NumStackI - 1], NumStack[NumStackI]);
     numCopy(NumStack[NumStackI], NumStack[NumStackI - 1]);
    }
    if (TokenCompare("SEC"))
    {
     StackErr = 0;
     numSec(NumStack[NumStackI - 1], NumStack[NumStackI]);
     numCopy(NumStack[NumStackI], NumStack[NumStackI - 1]);
    }
    if (TokenCompare("CSC"))
    {
     StackErr = 0;
     numCsc(NumStack[NumStackI - 1], NumStack[NumStackI]);
     numCopy(NumStack[NumStackI], NumStack[NumStackI - 1]);
    }
   }
   if (NumStackI >= 2)
   {
    if (TokenCompare("EXP"))
    {
     StackErr = 0;
     NumStackI--;
     numExp(NumStack[NumStackI - 1], NumStack[NumStackI], NumStack[NumStackI + 1]);
     numCopy(NumStack[NumStackI + 1], NumStack[NumStackI - 1]);
    }
    if (TokenCompare("ROOT"))
    {
     StackErr = 0;
     NumStackI--;
     numRoot(NumStack[NumStackI - 1], NumStack[NumStackI], NumStack[NumStackI + 1]);
     numCopy(NumStack[NumStackI + 1], NumStack[NumStackI - 1]);
    }
   }
   if (StackErr)
   {
    TokenError = 1;
    errorPrint(Test, "Stack underflow or unsupported function: ", TokenBuf);
   }
  }
 }

 // Number
 if (Op == 1)
 {
  if (NumStackI < NumStackSize)
  {
   numSet(NumStack[NumStackI], TokenBuf);
   NumStackI++;
  }
  else
  {
   TokenError = 1;
   errorPrint(Test, "Stack overflow by number: ", TokenBuf);
  }
 }

 // Variable
 if (Op == 2)
 {
  if (NumStackI < NumStackSize)
  {
   numCopy(NumReg[TokenBuf[0] - 65], NumStack[NumStackI]);
   NumStackI++;
  }
  else
  {
   TokenError = 1;
   errorPrint(Test, "Stack overflow by variable: ", TokenBuf);
  }
 }
}

void TokenStackPush(void)
{
 uchar I = 0;
 while (TokenBuf[I] != 0)
 {
  TokenStack[TokenStackB] = TokenBuf[I];
  I++;
  TokenStackB++;
 }
 TokenStackS[TokenStackI] = I;
 TokenStackI++;
}

void TokenStackPop(void)
{
 TokenStackI--;
 uchar L = TokenStackS[TokenStackI];
 uchar B = TokenStackB - L;
 uchar I = 0;
 TokenStackB -= L;
 while (L > 0)
 {
  TokenBuf[I] = TokenStack[B];
  I++;
  L--;
  B++;
 }
 TokenBuf[I] = 0;
}

uchar TokenStackTop(void)
{
 return TokenStack[TokenStackB - TokenStackS[TokenStackI - 1]];
}

void Calc(uchar Test)
{
 uchar II;
 
 uchar TokenType = 0;
 uchar TokenChar = 0;
 uchar TokenCharX = 0;
 uchar TokenWork = 1;

 NumStackI = 0;

 TokenI = 0;
 TokenBufI = 0;

 if (Test)
 {
  console_clear();
  console_string("Token               RPN formula");
  console_print();
 }

 // Convert to reverse Polish notation and process
 TokenStackB = 0;
 TokenStackI = 0;
 while (TokenType != 10)
 {
  // Get token
  TokenBufI = 0;
  TokenType = 0;
  TokenWork = 1;
  while (TokenWork)
  {
   TokenChar = 0;
   TokenCharX = 0;
   while (TokenChar == 0)
   {
    TokenI++;
    if ((CmdBuf[TokenI] >= 'A') && (CmdBuf[TokenI] <= 'Z')) { TokenChar = 1; }
    if (((CmdBuf[TokenI] >= '0') && (CmdBuf[TokenI] <= '9')) || (CmdBuf[TokenI] == '.') || (CmdBuf[TokenI] == '\\')) { TokenChar = 2; }
    if ((CmdBuf[TokenI] == ';') || (CmdBuf[TokenI] == '(') || (CmdBuf[TokenI] == ')') || (CmdBuf[TokenI] == '+') || (CmdBuf[TokenI] == '-') || (CmdBuf[TokenI] == '*') || (CmdBuf[TokenI] == '/'))  { TokenChar = 3; }
    if ((CmdBuf[TokenI] == 0))  { TokenChar = 10; }
    if (TokenChar != 10)
    {
     II = 0;
     TokenCharX = 0;
     while (TokenCharX == 0)
     {
      TokenI++;
      II++;
      if ((CmdBuf[TokenI] >= 'A') && (CmdBuf[TokenI] <= 'Z')) { TokenCharX = 1; }
      if (((CmdBuf[TokenI] >= '0') && (CmdBuf[TokenI] <= '9')) || (CmdBuf[TokenI] == '.') || (CmdBuf[TokenI] == '\\')) { TokenCharX = 2; }
      if ((CmdBuf[TokenI] == ';') || (CmdBuf[TokenI] == '(') || (CmdBuf[TokenI] == ')') || (CmdBuf[TokenI] == '+') || (CmdBuf[TokenI] == '-') || (CmdBuf[TokenI] == '*') || (CmdBuf[TokenI] == '/'))  { TokenCharX = 3; }
      if ((CmdBuf[TokenI] == 0))  { TokenCharX = 10; }
     }
     TokenI -= II;
    }
   }
   TokenBuf[TokenBufI] = CmdBuf[TokenI];
   TokenBufI++;
   TokenBuf[TokenBufI] = 0;
   switch (TokenChar)
   {
    case 1:
     if ((TokenType == 0) || (TokenType == 1))
     {
      TokenType = 1;
     }
     if (TokenCharX != 1)
     {
      TokenWork = 0;
     }
     break;
    case 2:
     if (TokenBuf[TokenBufI - 1] == '\\')
     {
      TokenBuf[TokenBufI - 1] = '-';
     }
     if ((TokenType == 0) || (TokenType == 2))
     {
      TokenType = 2;
     }
     if (TokenCharX != 2)
     {
      TokenWork = 0;
     }
     break;
    case 3:
     {
      TokenType = 3;
      TokenWork = 0;
     }
     break;
    case 10:
     {
      TokenType = 10;
      TokenWork = 0;
     }
     break;
   }
  }

  // Print token
  if (Test)
  {
   if (TokenType != 10)
   {
    console_clear();
    console_uchar_t('[');
    console_uchar_v(TokenType);
    console_uchar_t(']');
    console_uchar_t('[');
    console_string(TokenBuf);
    console_uchar_t(']');
    console_print();
   }
  }

  // ### Shunting yard algorithm ###
  
  // If token is a number then put to the output
  if (TokenType == 2)
  {
   CalcWork(Test, 1);
  }
  if ((TokenType == 1) && (TokenBufI == 1))
  {
   CalcWork(Test, 2);
  }

  // If token is a function then put onto the stack
  if ((TokenType == 1) && (TokenBufI > 1))
  {
   TokenStackPush();
  }

  // If token is a function argument separator ";", then:
  //  - While the top element on the stack is not "(", pop the element and put to the output
  //  - If the stack does not contain "(", raise syntax error
  if ((TokenType == 3) && (TokenBuf[0] == ';'))
  {
   while ((TokenStackI > 0) && (TokenStackTop() != '('))
   {
    TokenStackPop();
    CalcWork(Test, 0);
   }
  }
  
  // If token is a operator O:
  //  - While the top element on the stack is operator OX:
  //     - O priority is lower than OX priority, pop OX and put on the output
  //  - Put O on the stack
  if ((TokenType == 3) && (TokenBuf[0] != ';') && (TokenBuf[0] != '(') && (TokenBuf[0] != ')'))
  {
   II = TokenBuf[0];
   if ((II == '+') || (II == '-'))
   {
    while ((TokenStackI > 0) && ((TokenStackTop() == '*') || (TokenStackTop() == '/')))
    {
     TokenStackPop();
     CalcWork(Test, 0);
    }
   }

   TokenBuf[0] = II;
   TokenBuf[1] = 0;
   TokenStackPush();
  }

  // If token is "(", put on the stack
  if ((TokenType == 3) && (TokenBuf[0] == '('))
  {
   TokenStackPush();
  }

  // If token is ")":
  //  - Pop operator from stack and put on the output while there is not "("
  //  - If "(" does not exist on the stack, raise syntax error
  //  - Pop "(" from the stack
  //  - If the top element is function, put to the output
  if ((TokenType == 3) && (TokenBuf[0] == ')'))
  {
   while ((TokenStackI > 0) && (TokenStackTop() != '('))
   {
    TokenStackPop();
    CalcWork(Test, 0);
   }
   if (TokenStackI > 0)
   {
    TokenStackPop();
   }
   if (TokenStackI > 0)
   {
    if ((TokenStackTop() >= 'A') && (TokenStackTop() <= 'Z'))
    {
     TokenStackPop();
     CalcWork(Test, 0);
    }
   }
  }
 }

 // Pop all operators from the stack and put on the output, if there is "(" or ")" raise syntax error
 while (TokenStackI > 0)
 {
  TokenStackPop();
  if ((TokenBuf[0] != '(') && (TokenBuf[0] != ')'))
  {
   CalcWork(Test, 0);
  }
 }

 NumStackI--;
 numCopy(NumStack[NumStackI], NumReg[DefReg]);
}


schar KeypadLetterOffset = 0;

void KeypadLetters(schar Direction)
{
 if ((Direction < 0) && (KeypadLetterOffset > 0))
 {
  KeypadLetterOffset = KeypadLetterOffset - 4;
 }
 if ((Direction > 0) && (KeypadLetterOffset < 20))
 {
  KeypadLetterOffset = KeypadLetterOffset + 4;
 }

 widget_set_uchar_t(Widget1, 10, widget_value, KeypadLetterOffset + 65);
 widget_set_uchar_t(Widget1, 11, widget_value, KeypadLetterOffset + 66);
 widget_set_uchar_t(Widget1, 12, widget_value, KeypadLetterOffset + 67);
 widget_set_uchar_t(Widget1, 13, widget_value, KeypadLetterOffset + 68);
 widget_set_uchar_t(Widget1, 20, widget_value, KeypadLetterOffset + 69);
 widget_set_uchar_t(Widget1, 21, widget_value, KeypadLetterOffset + 70);
 widget_set_uchar_t(Widget1, 22, widget_value, (KeypadLetterOffset < 20) ? KeypadLetterOffset + 71 : 32);
 widget_set_uchar_t(Widget1, 23, widget_value, (KeypadLetterOffset < 20) ? KeypadLetterOffset + 72 : 32);
 
}

void KeypadInput(char * Symbol)
{
 if ((Symbol[0] >= 'a') && (Symbol[0] <= 'z'))
 {
  Temp[0] = Symbol[0] - 97 + 65 + KeypadLetterOffset;
  Temp[1] = 0;
  if (Temp[0] <= 'Z') { KeypadInput(Temp); }  
 }
 else
 {
  widget_set_string(Widget1, 1, widget_max, Symbol);
 }
}

void KeypadClear(void)
{
 widget_set_string(Widget1, 1, widget_value, "");
}

void KeypadBack(void)
{
 widget_get_string(Widget1, 1, widget_value, CmdBuf, CmdBufSize);
 int I = 0;
 while (CmdBuf[I] != 0)
 {
  I++;
 }
 if (I > 0)
 {
  I--;
  CmdBuf[I] = 0;
  widget_set_string(Widget1, 1, widget_value, CmdBuf);
 }
}

void KeypadCalc(void)
{
 CmdBuf[0] = ' ';
 widget_get_string(Widget1, 1, widget_value, CmdBuf + 1, CmdBufSize - 1);
 for (int I = 0; I < CmdBufSize; I++)
 {
  if ((CmdBuf[I] >= 97) && (CmdBuf[I] <= 122))
  {
   CmdBuf[I] = CmdBuf[I] - 32;
  }
  if (CmdBuf[I] == ',') { CmdBuf[I] = '.'; }
  if (CmdBuf[I] == '`') { CmdBuf[I] = '\\'; }
  if ((CmdBuf[I] == '[') || (CmdBuf[I] == '{')) { CmdBuf[I] = '('; }
  if ((CmdBuf[I] == ']') || (CmdBuf[I] == '}')) { CmdBuf[I] = ')'; }
 }
 TokenError = 0;
 Calc(1);
 if (!TokenError)
 {
  numPrint(RegWidget(DefReg), NumReg[DefReg]);
 }
}

void main(void)
{
 Widget0 = engine_number();
 Widget1 = Widget0 + 1;
 
 PrintRaw = 0;
 DispRegPage = 0;

 widget_clear(Widget0);

 numInit();
 numInitTaylor();

 numSet(NumReg[4], CONST_E);
 numSet(NumReg[15], CONST_PI);

 for (int WidgetI = 0; WidgetI < 13; WidgetI++)
 {
  widget_add(Widget0, WidgetI + 1, 0);
  widget_set_uint(Widget0, WidgetI + 1, widget_size, 7);
  widget_set_uint(Widget0, WidgetI + 1, widget_orientation, widget_horizontal);

  Temp[0] = WidgetI + 65;
  Temp[1] = 0;
  widget_add(Widget0, WidgetI * 4 + 21, WidgetI + 1);
  widget_set_uint(Widget0, WidgetI * 4 + 21, widget_size, 10);
  widget_set_uint(Widget0, WidgetI * 4 + 21, widget_type, widget_button);
  widget_set_string(Widget0, WidgetI * 4 + 21, widget_value, Temp);
  if ((WidgetI + 0) == DefReg)
  {
   Temp[0] = '['; widget_set_string(Widget0, WidgetI * 4 + 21, widget_min, Temp);
   Temp[0] = ']'; widget_set_string(Widget0, WidgetI * 4 + 21, widget_max, Temp);
  }
  widget_set_sint(Widget0, WidgetI * 4 + 21, widget_event, widget_runscript);
  widget_add(Widget0, WidgetI * 4 + 22, WidgetI + 1);
  widget_set_uint(Widget0, WidgetI * 4 + 22, widget_size, 40);
  widget_set_uint(Widget0, WidgetI * 4 + 22, widget_type, widget_text);

  Temp[0] = WidgetI + 78;
  Temp[1] = 0;
  widget_add(Widget0, WidgetI * 4 + 23, WidgetI + 1);
  widget_set_uint(Widget0, WidgetI * 4 + 23, widget_size, 10);
  widget_set_uint(Widget0, WidgetI * 4 + 23, widget_type, widget_button);
  widget_set_string(Widget0, WidgetI * 4 + 23, widget_value, Temp);
  if ((WidgetI + 13) == DefReg)
  {
   Temp[0] = '['; widget_set_string(Widget0, WidgetI * 4 + 23, widget_min, Temp);
   Temp[0] = ']'; widget_set_string(Widget0, WidgetI * 4 + 23, widget_max, Temp);
  }
  widget_set_sint(Widget0, WidgetI * 4 + 23, widget_event, widget_runscript);
  widget_add(Widget0, WidgetI * 4 + 24, WidgetI + 1);
  widget_set_uint(Widget0, WidgetI * 4 + 24, widget_size, 40);
  widget_set_uint(Widget0, WidgetI * 4 + 24, widget_type, widget_text);
 }

 DisplayAllRegs();

 widget_add(Widget0, 14, 0);
 widget_set_uint(Widget0, 14, widget_size, 9);
 widget_set_uint(Widget0, 14, widget_orientation, widget_horizontal);

 widget_add(Widget0, 15, 14);
 widget_set_uint(Widget0, 15, widget_size, 55);
 widget_set_uint(Widget0, 15, widget_type, widget_text);

 widget_add(Widget0, 16, 14);
 widget_set_uint(Widget0, 16, widget_size, 15);
 widget_set_uint(Widget0, 16, widget_type, widget_button);
 widget_set_string(Widget0, 16, widget_value, "Compute");
 widget_set_sint(Widget0, 16, widget_event, widget_runscript);

 widget_add(Widget0, 17, 14);
 widget_set_uint(Widget0, 17, widget_size, 15);
 widget_set_uint(Widget0, 17, widget_type, widget_button);
 widget_set_string(Widget0, 17, widget_value, "Clear");
 widget_set_sint(Widget0, 17, widget_event, widget_runscript);

 widget_add(Widget0, 18, 14);
 widget_set_uint(Widget0, 18, widget_size, 15);
 widget_set_uint(Widget0, 18, widget_type, widget_button);
 widget_set_string(Widget0, 18, widget_value, "Page");
 widget_set_sint(Widget0, 18, widget_event, widget_runscript);
 

 widget_clear(Widget1);

 widget_add(Widget1, 99, 0);
 widget_set_uint(Widget1, 99, widget_size, 10);
 widget_set_uint(Widget1, 99, widget_type, widget_text);
 
 widget_add(Widget1, 1, 0);
 widget_set_uint(Widget1, 1, widget_size, 10);
 widget_set_uint(Widget1, 1, widget_type, widget_text);
 
 for (int YY = 0; YY < 8; YY++)
 {
  widget_add(Widget1, YY + 2, 0);
  widget_set_uint(Widget1, YY + 2, widget_size, 10);
  widget_set_uint(Widget1, YY + 2, widget_orientation, widget_horizontal);

  for (int XX = 0; XX < 5; XX++)
  {
   int BtnId = (YY * 10) + XX + 10;
   widget_add(Widget1, BtnId, YY + 2);
   widget_set_uint(Widget1, BtnId, widget_size, 20);
   widget_set_uint(Widget1, BtnId, widget_type, widget_button);
   widget_set_uint(Widget1, BtnId, widget_value, BtnId);
   widget_set_sint(Widget1, BtnId, widget_event, widget_runscript);
  }
 }

 widget_set_string(Widget1, 10, widget_value,    "A"); widget_set_string(Widget1, 11, widget_value,    "B"); widget_set_string(Widget1, 12, widget_value,    "C"); widget_set_string(Widget1, 13, widget_value,    "D"); widget_set_string(Widget1, 14, widget_value, "PREV");
 widget_set_string(Widget1, 20, widget_value,    "E"); widget_set_string(Widget1, 21, widget_value,    "F"); widget_set_string(Widget1, 22, widget_value,    "G"); widget_set_string(Widget1, 23, widget_value,    "H"); widget_set_string(Widget1, 24, widget_value, "NEXT");
 widget_set_string(Widget1, 30, widget_value,  "SIN"); widget_set_string(Widget1, 31, widget_value,  "EXP"); widget_set_string(Widget1, 32, widget_value, "ROOT"); widget_set_string(Widget1, 33, widget_value,    ";"); widget_set_string(Widget1, 34, widget_value,  "CLR");
 widget_set_string(Widget1, 40, widget_value,  "COS"); widget_set_string(Widget1, 41, widget_value,   "\\"); widget_set_string(Widget1, 42, widget_value,    "("); widget_set_string(Widget1, 43, widget_value,    ")"); widget_set_string(Widget1, 44, widget_value,    "/");
 widget_set_string(Widget1, 50, widget_value,  "TAN"); widget_set_string(Widget1, 51, widget_value,    "7"); widget_set_string(Widget1, 52, widget_value,    "8"); widget_set_string(Widget1, 53, widget_value,    "9"); widget_set_string(Widget1, 54, widget_value,    "*");
 widget_set_string(Widget1, 60, widget_value,  "COT"); widget_set_string(Widget1, 61, widget_value,    "4"); widget_set_string(Widget1, 62, widget_value,    "5"); widget_set_string(Widget1, 63, widget_value,    "6"); widget_set_string(Widget1, 64, widget_value,    "-");
 widget_set_string(Widget1, 70, widget_value,  "SEC"); widget_set_string(Widget1, 71, widget_value,    "1"); widget_set_string(Widget1, 72, widget_value,    "2"); widget_set_string(Widget1, 73, widget_value,    "3"); widget_set_string(Widget1, 74, widget_value,    "+");
 widget_set_string(Widget1, 80, widget_value,  "CSC"); widget_set_string(Widget1, 81, widget_value,    "0"); widget_set_string(Widget1, 82, widget_value,    "."); widget_set_string(Widget1, 83, widget_value, "BACK"); widget_set_string(Widget1, 84, widget_value,"ENTER");

 DisplayAllRegs();

 while(1)
 {
  event_form = 255;
  event_widget = 255;
  stop();

  if (event_form == Widget0)
  {
   switch (event_widget)
   {
    case 21:
    case 23:
    case 25:
    case 27:
    case 29:
    case 31:
    case 33:
    case 35:
    case 37:
    case 39:
    case 41:
    case 43:
    case 45:
    case 47:
    case 49:
    case 51:
    case 53:
    case 55:
    case 57:
    case 59:
    case 61:
    case 63:
    case 65:
    case 67:
    case 69:
    case 71:
     {
      Temp[0] = DefReg + 65;
      Temp[1] = 0;
      widget_set_string(Widget0, RegWidget(DefReg), widget_value, Temp);

      if (((int)event_widget % 4) == 1)
      {
       DefReg = (((int)event_widget - 21) / 4);
      }
      if (((int)event_widget % 4) == 3)
      {
       DefReg = (((int)event_widget - 23) / 4) + 13;
      }

      Temp[0] = '[';
      Temp[1] = DefReg + 65;
      Temp[2] = ']';
      Temp[3] = 0;
      widget_set_string(Widget0, RegWidget(DefReg), widget_value, Temp);
      numPrint(RegWidget(DefReg), NumReg[DefReg]);
     }
     break;
    case 16:
     {
      CmdBuf[0] = ' ';
      widget_get_string(Widget0, 15, widget_value, CmdBuf + 1, CmdBufSize - 1);
      for (int I = 0; I < CmdBufSize; I++)
      {
       if ((CmdBuf[I] >= 97) && (CmdBuf[I] <= 122))
       {
        CmdBuf[I] = CmdBuf[I] - 32;
       }
       if (CmdBuf[I] == ',') { CmdBuf[I] = '.'; }
       if (CmdBuf[I] == '`') { CmdBuf[I] = '\\'; }
       if ((CmdBuf[I] == '[') || (CmdBuf[I] == '{')) { CmdBuf[I] = '('; }
       if ((CmdBuf[I] == ']') || (CmdBuf[I] == '}')) { CmdBuf[I] = ')'; }
      }
      TokenError = 0;
      Calc(1);
      if (!TokenError)
      {
       numPrint(RegWidget(DefReg), NumReg[DefReg]);
      }
     }
     break;
    case 17:
     {
      //PrintRaw = !PrintRaw;
      //DisplayAllRegs();
      widget_set_string(Widget0, 15, widget_value, "");
     }
     break;
    case 18:
     {
      DispRegPage = 1 - DispRegPage;
      DisplayAllRegs();
     }
     break;
   }
  }
  if (event_form == Widget1)
  {
   switch (event_widget)
   {
    case 10: KeypadInput("a"); break;
    case 11: KeypadInput("b"); break;
    case 12: KeypadInput("c"); break;
    case 13: KeypadInput("d"); break;
    case 14: KeypadLetters(-1); break;

    case 20: KeypadInput("e"); break;
    case 21: KeypadInput("f"); break;
    case 22: KeypadInput("g"); break;
    case 23: KeypadInput("h"); break;
    case 24: KeypadLetters( 1); break;

    case 30: KeypadInput("SIN"); break;
    case 31: KeypadInput("EXP"); break;
    case 32: KeypadInput("ROOT"); break;
    case 33: KeypadInput(";"); break;
    case 34: KeypadClear(); break;

    case 40: KeypadInput("COS"); break;
    case 41: KeypadInput("\\"); break;
    case 42: KeypadInput("("); break;
    case 43: KeypadInput(")"); break;
    case 44: KeypadInput("/"); break;

    case 50: KeypadInput("TAN"); break;
    case 51: KeypadInput("7"); break;
    case 52: KeypadInput("8"); break;
    case 53: KeypadInput("9"); break;
    case 54: KeypadInput("*"); break;

    case 60: KeypadInput("COT"); break;
    case 61: KeypadInput("4"); break;
    case 62: KeypadInput("5"); break;
    case 63: KeypadInput("6"); break;
    case 64: KeypadInput("-"); break;

    case 70: KeypadInput("SEC"); break;
    case 71: KeypadInput("1"); break;
    case 72: KeypadInput("2"); break;
    case 73: KeypadInput("3"); break;
    case 74: KeypadInput("+"); break;

    case 80: KeypadInput("CSC"); break;
    case 81: KeypadInput("0"); break;
    case 82: KeypadInput("."); break;
    case 83: KeypadBack(); break;
    case 84: KeypadCalc(); break;
   }
  }
 }
}

