#define IOConsoleCmd 1

// Clears console
#define console_clear() _uchar[mem_swap] = IOConsoleCmd + 0

// Prints value
void console_schar_v(schar  V) { core_io0.val_schar  = V; _uchar[mem_swap + 1] =  0; _uchar[mem_swap] = IOConsoleCmd + 1; }
void console_uchar_v(uchar  V) { core_io0.val_uchar  = V; _uchar[mem_swap + 1] =  1; _uchar[mem_swap] = IOConsoleCmd + 1; }
void console_schar_t(schar  V) { core_io0.val_schar  = V; _uchar[mem_swap + 1] =  2; _uchar[mem_swap] = IOConsoleCmd + 1; }
void console_uchar_t(uchar  V) { core_io0.val_uchar  = V; _uchar[mem_swap + 1] =  3; _uchar[mem_swap] = IOConsoleCmd + 1; }
void console_sshort( sshort V) { core_io0.val_sshort = V; _uchar[mem_swap + 1] =  4; _uchar[mem_swap] = IOConsoleCmd + 1; }
void console_ushort( ushort V) { core_io0.val_ushort = V; _uchar[mem_swap + 1] =  5; _uchar[mem_swap] = IOConsoleCmd + 1; }
void console_sint(   sint   V) { core_io0.val_sint   = V; _uchar[mem_swap + 1] =  6; _uchar[mem_swap] = IOConsoleCmd + 1; }
void console_uint(   uint   V) { core_io0.val_uint   = V; _uchar[mem_swap + 1] =  7; _uchar[mem_swap] = IOConsoleCmd + 1; }
void console_slong(  slong  V) { core_io0.val_slong  = V; _uchar[mem_swap + 1] =  8; _uchar[mem_swap] = IOConsoleCmd + 1; }
void console_ulong(  ulong  V) { core_io0.val_ulong  = V; _uchar[mem_swap + 1] =  9; _uchar[mem_swap] = IOConsoleCmd + 1; }
void console_float(  float  V) { core_io0.val_float  = V; _uchar[mem_swap + 1] = 10; _uchar[mem_swap] = IOConsoleCmd + 1; }

// Prints null-terminated string
void console_string(char * V)
{
 uint I = 0;
 while (V[I] != 0)
 {
  console_uchar_t(V[I]);
  I++;
 }
}

// Prints buffer contents
#define console_print() _uchar[mem_swap] = IOConsoleCmd + 2

