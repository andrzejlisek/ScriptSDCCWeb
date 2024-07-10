#include "_.h"

// Integer number type one-word names
#define schar signed char
#define uchar unsigned char
#define sshort signed short
#define ushort unsigned short
#define sint signed int
#define uint unsigned int
#define slong signed long
#define ulong unsigned long
#define llong long long
#define sllong signed long long
#define ullong unsigned long long

// Arrays giving absolute data memory access
#define _char ((char volatile *)0)
#define _schar ((schar volatile *)0)
#define _uchar ((uchar volatile *)0)
#define _short ((short volatile *)0)
#define _sshort ((sshort volatile *)0)
#define _ushort ((ushort volatile *)0)
#define _int ((int volatile *)0)
#define _sint ((sint volatile *)0)
#define _uint ((uint volatile *)0)
#define _long ((long volatile *)0)
#define _slong ((slong volatile *)0)
#define _ulong ((ulong volatile *)0)

// Unified keywords "__near" and "__far"
// Interrupt routine universal names
#ifdef engine_mcs51
 #define __interrupt1(_) MCS51_isr0(void) __interrupt(0)
 #define __interrupt2(_) MCS51_isr2(void) __interrupt(2)
#endif
#ifdef engine_z180
 #define __near
 #define __far
 #define __reentrant
 #define __interrupt1(_) NMI_InterruptHandler(void) __critical __interrupt 
 #define __interrupt2(_) IM1_InterruptHandler(void) __interrupt
#endif
#ifdef engine_mos65c02
 #define __interrupt1(_) NMI_InterruptHandler(void) __critical __interrupt 
 #define __interrupt2(_) INT_InterruptHandler(void) __interrupt
#endif


// Union for every data type, which is used to set and get values in swap memory
union core_io_union
{
 schar raw_s[8];
 uchar raw_u[8];
 schar val_schar;
 uchar val_uchar;
 sshort val_sshort;
 ushort val_ushort;
 sint val_sint;
 uint val_uint;
 slong val_slong;
 ulong val_ulong;
 float val_float;
};

__far __at (mem_swap +   8) union core_io_union core_io0;
__far __at (mem_swap +  16) union core_io_union core_io1;
__far __at (mem_swap +  24) union core_io_union core_io2;
__far __at (mem_swap +  32) union core_io_union core_io3;
__far __at (mem_swap +  40) union core_io_union core_io4;
__far __at (mem_swap +  48) union core_io_union core_io5;
__far __at (mem_swap +  56) union core_io_union core_io6;
__far __at (mem_swap +  64) union core_io_union core_io7;
__far __at (mem_swap +  72) union core_io_union core_io8;
__far __at (mem_swap +  80) union core_io_union core_io9;
__far __at (mem_swap +  88) union core_io_union core_ioA;
__far __at (mem_swap +  96) union core_io_union core_ioB;
__far __at (mem_swap + 104) union core_io_union core_ioC;
__far __at (mem_swap + 112) union core_io_union core_ioD;
__far __at (mem_swap + 120) union core_io_union core_ioE;
__far __at (mem_swap + 128) union core_io_union core_ioF;


// Stops script and allows user to continue by clicking "Run" button
#define stop() _uchar[mem_swap] = 254

// Stops script without continuation possibility
#define end() _uchar[mem_swap] = 253

// Gets the number of current engine
uchar engine_number(void)
{
 _uchar[mem_swap] = 247;
 return core_io0.val_uchar;
}

// Gets the current instruction conter number or reset the counter
ulong engine_counter(uchar div)
{
 _uchar[mem_swap + 1] = div;
 _uchar[mem_swap] = 252;
 return core_io0.val_ulong;
}

// Clears string in string buffer
void string_clear(void)
{
 _uchar[mem_swap] = 250;
}

// Appends specified string to string buffer
// V - Pointer to null-terminated string
void string_append(char * V)
{
 uchar I = 0;
 _uchar[mem_swap + 1] = 11;
 while (V[I] != 0)
 {
  core_io0.val_schar = V[I];
  _uchar[mem_swap] = 251;
  I++;
 }
}

void string_append_schar_v(schar V) { core_io0.val_schar  = V; _uchar[mem_swap + 1] =  0; _uchar[mem_swap] = 251; }
void string_append_uchar_v(uchar V) { core_io0.val_uchar  = V; _uchar[mem_swap + 1] =  1; _uchar[mem_swap] = 251; }
void string_append_schar_t(schar V) { core_io0.val_schar  = V; _uchar[mem_swap + 1] =  2; _uchar[mem_swap] = 251; }
void string_append_uchar_t(uchar V) { core_io0.val_uchar  = V; _uchar[mem_swap + 1] =  3; _uchar[mem_swap] = 251; }
void string_append_sshort(sshort V) { core_io0.val_sshort = V; _uchar[mem_swap + 1] =  4; _uchar[mem_swap] = 251; }
void string_append_ushort(ushort V) { core_io0.val_ushort = V; _uchar[mem_swap + 1] =  5; _uchar[mem_swap] = 251; }
void string_append_sint(  sint   V) { core_io0.val_sint   = V; _uchar[mem_swap + 1] =  6; _uchar[mem_swap] = 251; }
void string_append_uint(  uint   V) { core_io0.val_uint   = V; _uchar[mem_swap + 1] =  7; _uchar[mem_swap] = 251; }
void string_append_slong( slong  V) { core_io0.val_slong  = V; _uchar[mem_swap + 1] =  8; _uchar[mem_swap] = 251; }
void string_append_ulong( ulong  V) { core_io0.val_ulong  = V; _uchar[mem_swap + 1] =  9; _uchar[mem_swap] = 251; }
void string_append_float( float  V) { core_io0.val_float  = V; _uchar[mem_swap + 1] = 10; _uchar[mem_swap] = 251; }

// Sets specified string or value to string buffer
// V - Pointer to null-terminated string or value
#define string_set(V)         { string_clear(); string_append(V);         }
#define string_set_schar_v(V) { string_clear(); string_append_schar_v(V); }
#define string_set_uchar_v(V) { string_clear(); string_append_uchar_v(V); }
#define string_set_schar_t(V) { string_clear(); string_append_schar_t(V); }
#define string_set_uchar_t(V) { string_clear(); string_append_uchar_t(V); }
#define string_set_sshort(V)  { string_clear(); string_append_sshort(V);  }
#define string_set_ushort(V)  { string_clear(); string_append_ushort(V);  }
#define string_set_sint(V)    { string_clear(); string_append_sint(V);    }
#define string_set_uint(V)    { string_clear(); string_append_uint(V);    }
#define string_set_slong(V)   { string_clear(); string_append_slong(V);   }
#define string_set_ulong(V)   { string_clear(); string_append_ulong(V);   }
#define string_set_float(V)   { string_clear(); string_append_float(V);   }

// Gets string buffer contents to specified string
// V - Pointer to null-terminated string
// S - Maximum string length, the longer string will be truncated
ushort string_get(char * V, ushort S)
{
 ushort I, N;
 _uchar[mem_swap + 1] = 11;
 _uchar[mem_swap] = 248;
 N = core_io0.val_ushort;
 if (N > S)
 {
  N = S;
 }
 if (V != 0)
 {
  for (I = 0; I < N; I++)
  {
   _uchar[mem_swap] = 249;
   V[I] = core_io0.val_schar;
  }
  V[N] = 0;
 }
 return N;
}

schar  string_get_schar_v(void) { _uchar[mem_swap + 1] =  0; _uchar[mem_swap] = 248; return core_io0.val_schar;  }
uchar  string_get_uchar_v(void) { _uchar[mem_swap + 1] =  1; _uchar[mem_swap] = 248; return core_io0.val_uchar;  }
schar  string_get_schar_t(void) { _uchar[mem_swap + 1] =  2; _uchar[mem_swap] = 248; return core_io0.val_schar;  }
uchar  string_get_uchar_t(void) { _uchar[mem_swap + 1] =  3; _uchar[mem_swap] = 248; return core_io0.val_uchar;  }
sshort string_get_sshort(void)  { _uchar[mem_swap + 1] =  4; _uchar[mem_swap] = 248; return core_io0.val_sshort; }
ushort string_get_ushort(void)  { _uchar[mem_swap + 1] =  5; _uchar[mem_swap] = 248; return core_io0.val_ushort; }
sint   string_get_sint(void)    { _uchar[mem_swap + 1] =  6; _uchar[mem_swap] = 248; return core_io0.val_sint;   }
uint   string_get_uint(void)    { _uchar[mem_swap + 1] =  7; _uchar[mem_swap] = 248; return core_io0.val_uint;   }
slong  string_get_slong(void)   { _uchar[mem_swap + 1] =  8; _uchar[mem_swap] = 248; return core_io0.val_slong;  }
ulong  string_get_ulong(void)   { _uchar[mem_swap + 1] =  9; _uchar[mem_swap] = 248; return core_io0.val_ulong;  }
float  string_get_float(void)   { _uchar[mem_swap + 1] = 10; _uchar[mem_swap] = 248; return core_io0.val_float;  }

