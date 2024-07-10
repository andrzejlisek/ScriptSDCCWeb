// Gets random value
// Min - Minimum value
// Max - Maximum value
schar  random_get_schar( schar  Min, schar  Max) { core_io0.val_schar  = Min; core_io1.val_schar  = Max; _uchar[mem_swap + 1] =  0; _uchar[mem_swap] = 235; return core_io0.val_schar;  }
uchar  random_get_uchar( uchar  Min, uchar  Max) { core_io0.val_uchar  = Min; core_io1.val_uchar  = Max; _uchar[mem_swap + 1] =  1; _uchar[mem_swap] = 235; return core_io0.val_uchar;  }
sshort random_get_sshort(sshort Min, sshort Max) { core_io0.val_sshort = Min; core_io1.val_sshort = Max; _uchar[mem_swap + 1] =  4; _uchar[mem_swap] = 235; return core_io0.val_sshort; }
ushort random_get_ushort(ushort Min, ushort Max) { core_io0.val_ushort = Min; core_io1.val_ushort = Max; _uchar[mem_swap + 1] =  5; _uchar[mem_swap] = 235; return core_io0.val_ushort; }
sint   random_get_sint(  sint   Min, sint   Max) { core_io0.val_sint   = Min; core_io1.val_sint   = Max; _uchar[mem_swap + 1] =  6; _uchar[mem_swap] = 235; return core_io0.val_sint;   }
uint   random_get_uint(  uint   Min, uint   Max) { core_io0.val_uint   = Min; core_io1.val_uint   = Max; _uchar[mem_swap + 1] =  7; _uchar[mem_swap] = 235; return core_io0.val_uint;   }
slong  random_get_slong( slong  Min, slong  Max) { core_io0.val_slong  = Min; core_io1.val_slong  = Max; _uchar[mem_swap + 1] =  8; _uchar[mem_swap] = 235; return core_io0.val_slong;  }
ulong  random_get_ulong( ulong  Min, ulong  Max) { core_io0.val_ulong  = Min; core_io1.val_ulong  = Max; _uchar[mem_swap + 1] =  9; _uchar[mem_swap] = 235; return core_io0.val_ulong;  }
float  random_get_float( float  Min, float  Max) { core_io0.val_float  = Min; core_io1.val_float  = Max; _uchar[mem_swap + 1] = 10; _uchar[mem_swap] = 235; return core_io0.val_float;  }

