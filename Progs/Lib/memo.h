#define IOMemoCmd 20

#define memo_local_shared(N) do { _uchar[mem_swap + 1] = (N); _uchar[mem_swap + 2] = 0; _uchar[mem_swap] = IOMemoCmd + 0; } while(0)
#define memo_shared_local(N) do { _uchar[mem_swap + 1] = (N); _uchar[mem_swap + 2] = 1; _uchar[mem_swap] = IOMemoCmd + 0; } while(0)
#define memo_clear(N)        do { _uchar[mem_swap + 1] = (N); _uchar[mem_swap + 2] = 2; _uchar[mem_swap] = IOMemoCmd + 0; } while(0)

schar  memo_get_schar( uchar N, slong Pos) { core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 1; _uchar[mem_swap] = IOMemoCmd + 1; return core_io0.val_schar;  }
uchar  memo_get_uchar( uchar N, slong Pos) { core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 1; _uchar[mem_swap] = IOMemoCmd + 1; return core_io0.val_uchar;  }
sshort memo_get_sshort(uchar N, slong Pos) { core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 2; _uchar[mem_swap] = IOMemoCmd + 1; return core_io0.val_sshort; }
ushort memo_get_ushort(uchar N, slong Pos) { core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 2; _uchar[mem_swap] = IOMemoCmd + 1; return core_io0.val_ushort; }
sint   memo_get_sint(  uchar N, slong Pos) { core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 2; _uchar[mem_swap] = IOMemoCmd + 1; return core_io0.val_sint;   }
uint   memo_get_uint(  uchar N, slong Pos) { core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 2; _uchar[mem_swap] = IOMemoCmd + 1; return core_io0.val_uint;   }
slong  memo_get_slong( uchar N, slong Pos) { core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 4; _uchar[mem_swap] = IOMemoCmd + 1; return core_io0.val_slong;  }
ulong  memo_get_ulong( uchar N, slong Pos) { core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 4; _uchar[mem_swap] = IOMemoCmd + 1; return core_io0.val_ulong;  }
float  memo_get_float( uchar N, slong Pos) { core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 4; _uchar[mem_swap] = IOMemoCmd + 1; return core_io0.val_float;  }

void memo_set_schar( uchar N, slong Pos, schar  Val) { core_io0.val_schar  = Val; core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 1; _uchar[mem_swap] = IOMemoCmd + 2; }
void memo_set_uchar( uchar N, slong Pos, uchar  Val) { core_io0.val_uchar  = Val; core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 1; _uchar[mem_swap] = IOMemoCmd + 2; }
void memo_set_sshort(uchar N, slong Pos, sshort Val) { core_io0.val_sshort = Val; core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 2; _uchar[mem_swap] = IOMemoCmd + 2; }
void memo_set_ushort(uchar N, slong Pos, ushort Val) { core_io0.val_ushort = Val; core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 2; _uchar[mem_swap] = IOMemoCmd + 2; }
void memo_set_sint(  uchar N, slong Pos, sint   Val) { core_io0.val_sint   = Val; core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 2; _uchar[mem_swap] = IOMemoCmd + 2; }
void memo_set_uint(  uchar N, slong Pos, uint   Val) { core_io0.val_uint   = Val; core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 2; _uchar[mem_swap] = IOMemoCmd + 2; }
void memo_set_slong( uchar N, slong Pos, slong  Val) { core_io0.val_slong  = Val; core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 4; _uchar[mem_swap] = IOMemoCmd + 2; }
void memo_set_ulong( uchar N, slong Pos, ulong  Val) { core_io0.val_ulong  = Val; core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 4; _uchar[mem_swap] = IOMemoCmd + 2; }
void memo_set_float( uchar N, slong Pos, float  Val) { core_io0.val_float  = Val; core_io1.val_slong = Pos; _uchar[mem_swap + 1] = N; _uchar[mem_swap + 2] = 4; _uchar[mem_swap] = IOMemoCmd + 2; }

