#define M_E_  2.7182818284590452353602874713527
#define M_PI_ 3.1415926535897932384626433832795

// PI/180
#define angle_deg_rad 0.017453292519943295769236907684886

// 180/PI
#define angle_rad_deg 57.295779513082320876798154814105223

#define abs_(X) ((X) >= 0 ? (X) : (0 - (X)))

#define equal_(A, B, T) ((((A) < (B)) && (((B) - (A)) <= (T))) ? 1 : ((((A) > (B)) && (((A) - (B)) <= (T))) ? 1 : 0))

#define roundf_(V) (((V) < 0) ? ceilf((V) - 0.5) : floorf((V) + 0.5))

schar  engine_compute_schar( uchar Op, schar  Arg1, schar  Arg2) { core_io1.val_schar  = Arg1; core_io2.val_schar  = Arg2; _uchar[mem_swap + 1] =  0; _uchar[mem_swap + 2] = Op; _uchar[mem_swap] = 246; return core_io0.val_schar;  }
uchar  engine_compute_uchar( uchar Op, uchar  Arg1, uchar  Arg2) { core_io1.val_uchar  = Arg1; core_io2.val_uchar  = Arg2; _uchar[mem_swap + 1] =  1; _uchar[mem_swap + 2] = Op; _uchar[mem_swap] = 246; return core_io0.val_uchar;  }
sshort engine_compute_sshort(uchar Op, sshort Arg1, sshort Arg2) { core_io1.val_sshort = Arg1; core_io2.val_sshort = Arg2; _uchar[mem_swap + 1] =  4; _uchar[mem_swap + 2] = Op; _uchar[mem_swap] = 246; return core_io0.val_sshort; }
ushort engine_compute_ushort(uchar Op, ushort Arg1, ushort Arg2) { core_io1.val_ushort = Arg1; core_io2.val_ushort = Arg2; _uchar[mem_swap + 1] =  5; _uchar[mem_swap + 2] = Op; _uchar[mem_swap] = 246; return core_io0.val_ushort; }
sint   engine_compute_sint(  uchar Op, sint   Arg1, sint   Arg2) { core_io1.val_sint   = Arg1; core_io2.val_sint   = Arg2; _uchar[mem_swap + 1] =  6; _uchar[mem_swap + 2] = Op; _uchar[mem_swap] = 246; return core_io0.val_sint;   }
uint   engine_compute_uint(  uchar Op, uint   Arg1, uint   Arg2) { core_io1.val_uint   = Arg1; core_io2.val_uint   = Arg2; _uchar[mem_swap + 1] =  7; _uchar[mem_swap + 2] = Op; _uchar[mem_swap] = 246; return core_io0.val_uint;   }
slong  engine_compute_slong( uchar Op, slong  Arg1, slong  Arg2) { core_io1.val_slong  = Arg1; core_io2.val_slong  = Arg2; _uchar[mem_swap + 1] =  8; _uchar[mem_swap + 2] = Op; _uchar[mem_swap] = 246; return core_io0.val_slong;  }
ulong  engine_compute_ulong( uchar Op, ulong  Arg1, ulong  Arg2) { core_io1.val_ulong  = Arg1; core_io2.val_ulong  = Arg2; _uchar[mem_swap + 1] =  9; _uchar[mem_swap + 2] = Op; _uchar[mem_swap] = 246; return core_io0.val_ulong;  }
float  engine_compute_float( uchar Op, float  Arg1, float  Arg2) { core_io1.val_float  = Arg1; core_io2.val_float  = Arg2; _uchar[mem_swap + 1] = 10; _uchar[mem_swap + 2] = Op; _uchar[mem_swap] = 246; return core_io0.val_float;  }

#define engine_add_schar( Arg1, Arg2) engine_compute_schar( 1, (Arg1), (Arg2))
#define engine_add_uchar( Arg1, Arg2) engine_compute_uchar( 1, (Arg1), (Arg2))
#define engine_add_sshort(Arg1, Arg2) engine_compute_sshort(1, (Arg1), (Arg2))
#define engine_add_ushort(Arg1, Arg2) engine_compute_ushort(1, (Arg1), (Arg2))
#define engine_add_sint(  Arg1, Arg2) engine_compute_sint(  1, (Arg1), (Arg2))
#define engine_add_uint(  Arg1, Arg2) engine_compute_uint(  1, (Arg1), (Arg2))
#define engine_add_slong( Arg1, Arg2) engine_compute_slong( 1, (Arg1), (Arg2))
#define engine_add_ulong( Arg1, Arg2) engine_compute_ulong( 1, (Arg1), (Arg2))
#define engine_add_float( Arg1, Arg2) engine_compute_float( 1, (Arg1), (Arg2))

#define engine_sub_schar( Arg1, Arg2) engine_compute_schar( 2, (Arg1), (Arg2))
#define engine_sub_uchar( Arg1, Arg2) engine_compute_uchar( 2, (Arg1), (Arg2))
#define engine_sub_sshort(Arg1, Arg2) engine_compute_sshort(2, (Arg1), (Arg2))
#define engine_sub_ushort(Arg1, Arg2) engine_compute_ushort(2, (Arg1), (Arg2))
#define engine_sub_sint(  Arg1, Arg2) engine_compute_sint(  2, (Arg1), (Arg2))
#define engine_sub_uint(  Arg1, Arg2) engine_compute_uint(  2, (Arg1), (Arg2))
#define engine_sub_slong( Arg1, Arg2) engine_compute_slong( 2, (Arg1), (Arg2))
#define engine_sub_ulong( Arg1, Arg2) engine_compute_ulong( 2, (Arg1), (Arg2))
#define engine_sub_float( Arg1, Arg2) engine_compute_float( 2, (Arg1), (Arg2))

#define engine_mul_schar( Arg1, Arg2) engine_compute_schar( 3, (Arg1), (Arg2))
#define engine_mul_uchar( Arg1, Arg2) engine_compute_uchar( 3, (Arg1), (Arg2))
#define engine_mul_sshort(Arg1, Arg2) engine_compute_sshort(3, (Arg1), (Arg2))
#define engine_mul_ushort(Arg1, Arg2) engine_compute_ushort(3, (Arg1), (Arg2))
#define engine_mul_sint(  Arg1, Arg2) engine_compute_sint(  3, (Arg1), (Arg2))
#define engine_mul_uint(  Arg1, Arg2) engine_compute_uint(  3, (Arg1), (Arg2))
#define engine_mul_slong( Arg1, Arg2) engine_compute_slong( 3, (Arg1), (Arg2))
#define engine_mul_ulong( Arg1, Arg2) engine_compute_ulong( 3, (Arg1), (Arg2))
#define engine_mul_float( Arg1, Arg2) engine_compute_float( 3, (Arg1), (Arg2))

#define engine_div_schar( Arg1, Arg2) engine_compute_schar( 4, (Arg1), (Arg2))
#define engine_div_uchar( Arg1, Arg2) engine_compute_uchar( 4, (Arg1), (Arg2))
#define engine_div_sshort(Arg1, Arg2) engine_compute_sshort(4, (Arg1), (Arg2))
#define engine_div_ushort(Arg1, Arg2) engine_compute_ushort(4, (Arg1), (Arg2))
#define engine_div_sint(  Arg1, Arg2) engine_compute_sint(  4, (Arg1), (Arg2))
#define engine_div_uint(  Arg1, Arg2) engine_compute_uint(  4, (Arg1), (Arg2))
#define engine_div_slong( Arg1, Arg2) engine_compute_slong( 4, (Arg1), (Arg2))
#define engine_div_ulong( Arg1, Arg2) engine_compute_ulong( 4, (Arg1), (Arg2))
#define engine_div_float( Arg1, Arg2) engine_compute_float( 4, (Arg1), (Arg2))

#define engine_mod_schar( Arg1, Arg2) engine_compute_schar( 5, (Arg1), (Arg2))
#define engine_mod_uchar( Arg1, Arg2) engine_compute_uchar( 5, (Arg1), (Arg2))
#define engine_mod_sshort(Arg1, Arg2) engine_compute_sshort(5, (Arg1), (Arg2))
#define engine_mod_ushort(Arg1, Arg2) engine_compute_ushort(5, (Arg1), (Arg2))
#define engine_mod_sint(  Arg1, Arg2) engine_compute_sint(  5, (Arg1), (Arg2))
#define engine_mod_uint(  Arg1, Arg2) engine_compute_uint(  5, (Arg1), (Arg2))
#define engine_mod_slong( Arg1, Arg2) engine_compute_slong( 5, (Arg1), (Arg2))
#define engine_mod_ulong( Arg1, Arg2) engine_compute_ulong( 5, (Arg1), (Arg2))
#define engine_mod_float( Arg1, Arg2) engine_compute_float( 5, (Arg1), (Arg2))

#define engine_roundf(Arg) engine_compute_float(6, (Arg), 0)
#define engine_floorf(Arg) engine_compute_float(7, (Arg), 0)
#define engine_ceilf(Arg) engine_compute_float(8, (Arg), 0)
#define engine_truncf(Arg) engine_compute_float(9, (Arg), 0)

#define engine_cosf(Arg) engine_compute_float(11, (Arg), 0)
#define engine_sinf(Arg) engine_compute_float(12, (Arg), 0)
#define engine_tanf(Arg) engine_compute_float(13, (Arg), 0)
#define engine_acosf(Arg) engine_compute_float(14, (Arg), 0)
#define engine_asinf(Arg) engine_compute_float(15, (Arg), 0)
#define engine_atanf(Arg) engine_compute_float(16, (Arg), 0)
#define engine_atan2f(Arg1, Arg2) engine_compute_float(17, (Arg1), (Arg2))

#define engine_expm1f(Arg) engine_compute_float(18, (Arg), 0)
#define engine_log1pf(Arg) engine_compute_float(19, (Arg), 0)

#define engine_coshf(Arg) engine_compute_float(21, (Arg), 0)
#define engine_sinhf(Arg) engine_compute_float(22, (Arg), 0)
#define engine_tanhf(Arg) engine_compute_float(23, (Arg), 0)
#define engine_acoshf(Arg) engine_compute_float(24, (Arg), 0)
#define engine_asinhf(Arg) engine_compute_float(25, (Arg), 0)
#define engine_atanhf(Arg) engine_compute_float(26, (Arg), 0)

#define engine_erff(Arg) engine_compute_float(31, (Arg), 0)
#define engine_erfcf(Arg) engine_compute_float(32, (Arg), 0)
#define engine_tgammaf(Arg) engine_compute_float(33, (Arg), 0)
#define engine_lgammaf(Arg) engine_compute_float(34, (Arg), 0)

#define engine_logf(Arg) engine_compute_float(35, (Arg), 0)
#define engine_log10f(Arg) engine_compute_float(36, (Arg), 0)
#define engine_log2f(Arg) engine_compute_float(37, (Arg), 0)
#define engine_expf(Arg) engine_compute_float(38, (Arg), 0)
#define engine_exp2f(Arg) engine_compute_float(39, (Arg), 0)

#define engine_powf(Arg1, Arg2) engine_compute_float(41, (Arg1), (Arg2))
#define engine_sqrtf(Arg) engine_compute_float(42, (Arg), 0)
#define engine_cbrtf(Arg) engine_compute_float(43, (Arg), 0)
#define engine_hypotf(Arg1, Arg2) engine_compute_float(44, (Arg1), (Arg2))

