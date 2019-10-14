// Virage Logic Corporation or their respective owners and are
// protected herein. All Rights Reserved.
// Copyright 2003-2010 Virage Logic Corporation
//
// This document, material and/or software contains confidential
// and proprietary information of Virage Logic and is
// protected by copyright, trade secret and other state, federal,
// and international laws, and may be embodied in patents issued
// or pending.  Its receipt or possession does not convey any
// rights to use, reproduce, disclose its contents, or to
// manufacture, or sell anything it may describe.  Reverse
// engineering is prohibited, and reproduction, disclosure or use
// without specific written authorization of Virage Logic is
// strictly forbidden.
//
// ARC Product:  ARC 600 Library

///////////////////////////////////////////////////////////////////////////////
// Name:        arc600.h
// See also:    arc600.cpp, arc600_types.h
//
// Description: ARC600 instruction set simulation in form of
//              intrinsics and assembler macros (pseudo-assembler)
//
// Copyright (c) ARC International
//
// Created:  14-Nov-2007 Edward Abramian      V1.00
// Modified: 26-Mar-2008 Alexander Pisarevsky V1.01 (added intrinsics sections)
// Modified: 25-May-2008 Edward Abramian      V1.02 (updates and bugfixes)
// Modified: 14-Oct-2009 Oleg Prosekov        V1.03 (updates and bugfixes)
// Modified: 12-Apr-2010 Alexander Pisarevsky V1.04 (updates and optimizations)
// Modified: 19-Apr-2010 Roman Gomulin        V1.05 combining updates from
//                                                  multiple ARC codecs. Preparing to
//                                                  release the library
// Modified: 18-Oct-2010 Edward Abramian      V1.06 Corrected definition of __mulhflw_c, __mulhflw_lt, __mulhflw_ge
//
// Revision history:
//
// V1.03:
// - added new ops: _ror, _rsub, _mululw, _mult_0, _mult, _mact_0, _msubt_0, _msubt,
// - modified ops: _CopySMemToXMem16, _CopyXMemToSMem16, _CopyYMemToSMem16, _CopyYMemToSMem32
// - added LD/ST Access for XY Memory
// - fixed definition of int32xy_t
//
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARC600_H
#define __ARC600_H

// for compatibility with previous versions of ARC600_lib
#ifndef BURST_WAIT_AT_END
  #define BURST_WAIT_AT_BEGIN
#endif

#if 0
#define _DISABLE_INT() _disable()
#define _ENABLE_INT() _enable()
#else
#define _DISABLE_INT()
#define _ENABLE_INT()
#endif

#ifdef _MSC_VER

/* dummy defines for PC compilation */
/* Added by Simeon */
#define START_CALC_TCYCLES()
#define READ_TIMER_CYCLES(n)
#define START_TIMER_0()
#define START_TIMER_1()
#define READ_TIMER_0(timer_value)               /* read timer0 value and store it in timer_value */
#define READ_TIMER_1(timer_value)               /* read timer1 value and store it in timer_value */
#define READ_TIMER0_PRINT(text)                 /* print the message with timer0 value */
#define READ_TIMER1_PRINT(text)                 /* print the message with timer1 value */
#define _Uncached
#define _Rarely
#define _Usually

#else /* !_MSC_VER */

#define START_TIMER_0()\
    do\
    {\
    _sr(0xffffffff, 0x23);\
    _sr(3, 0x22);\
    _sr(0, 0x21);\
    }\
    while (0);


#define READ_TIMER_0(timer_value)\
    do\
    {\
    timer_value = _lr(0x21);\
    }\
    while (0);


#define READ_TIMER0_PRINT(text)\
    do\
    {\
    int32_t timer_value = _lr(0x21);\
    fprintf(stderr,"\n>>T0 -- %s  %d\n",text, timer_value);\
    }\
    while (0);


#define START_TIMER_1()\
    do\
    {\
    _sr(0xffffffff, 0x102);\
    _sr(3, 0x101);\
    _sr(0, 0x100);\
    }\
    while (0);


#define READ_TIMER_1(timer_value)\
    do\
    {\
    timer_value = _lr(0x100);\
    }\
    while (0);


#define READ_TIMER1_PRINT(text)\
    do\
    {\
    int32_t timer_value = _lr(0x100);\
    fprintf(stderr,"\n>>T1 -- %s  %d\n",text, timer_value);\
    }\
    while (0);

#endif //_MSC_VER

typedef int* pint32_t;
typedef short* pint16_t;
typedef short int16_t;
typedef unsigned long timer_t;

#ifdef    _MSC_VER
  #define  _Inline _inline
  #pragma warning(disable: 4068)
#endif // _MSC_VER

#ifndef _MSC_VER
#include <arc/arc_reg.h>
#endif

//#include "arc600_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __max
#undef __max
#endif
#ifdef __min
#undef __min
#endif

///////////////////////////////////////////////////////////////////////////////
// Instructions' aliases
//
// NOTE: Define ARC600_OLD_NAMES to use old style naming for instruction
//       simulation set
//
///////////////////////////////////////////////////////////////////////////////

#define Q24         (1UL<<16)           /* Simeon */
#define P24         (1UL<<17)           /* ... */
#define RM24        (1UL<<18)           /* ... */
#define M24         ((1UL <<24)-1)      /* ... */
#define M32         ((1UL <<32)-1)      /* ... */
#define M48         ((1ULL<<48)-1)      /* ... */
#define M56         ((1ULL<<56)-1)      /* ... */

#define XY_BANK_SIZE      (2048)        /* ... */
#define Y_BANK            (1)           /* ... */
#define X_BANK            (0)           /* ... */

#ifndef ARC600_OLD_NAMES
//
// Core instruction set simulation
//

// Intrinsics
#if _MSC_VER < 1400 // do not define "__nop()" in MSVC 2008 and higher
#define _nop()              __nop()
#else
#define _nop()
#endif

#if defined _MSC_VER
    uint32_t __aux_crc_poly();
    uint32_t __aux_crc_mode();
    void __set_aux_crc_poly(uint32_t x);
    void __set_aux_crc_mode(uint32_t x);
    uint32_t __crc(uint32_t a, uint32_t b);
#endif


#define _mov(b, c)          __mov(b, c)
#define _mov_f(b, c)        __mov_f(b, c)
#define _asl(a, s)          __asl(a, s)
#define _asl_f(a, s)        __asl_f(a, s)
#define _asr(x, s)          __asr(x, s)
#define _asr_f(x, s)        __asr_f(x, s)
#define _lsr(a, s)          __lsr(a, s)
#define _lsr_f(a, s)        __lsr_f(a, s)
#define _asls(a, s)         __asls(a, s)
#define _asls_f(a, s)       __asls_f(a, s)
#define _asrs(a, s)         __asrs(a, s)
#define _asrs_f(a, s)       __asrs_f(a, s)
#define _ror(a, b)           __ror(a, b)
#define _rlc(a)             __rlc(a)
#define _rlc_f(a)           __rlc_f(a)
#define _or(a, b)           __or(a, b)
#define _or_f(a, b)         __or_f(a, b)
#define _and(a, b)          __and(a, b)
#define _and_f(a, b)        __and_f(a, b)
#define _adds(a, b)         __adds(a, b)
#define _adds_f(a, b)       __adds_f(a, b)
#define _subs(a, b)         __subs(a, b)
#define _subs_f(a, b)       __subs_f(a, b)
#define _negs(a)            __negs(a)
#define _negs_f(a)          __negs_f(a)
#define _negsw(a)           __negsw(a)
#define _negsw_f(a)         __negsw_f(a)
#define _add(src1, src2)    __add(src1, src2)
#define _add_f(src1, src2)  __add_f(src1, src2)
#define _sub(src1, src2)    __sub(src1, src2)
#define _rsub(src1, src2)   __rsub(src1, src2)
#define _sub_f(src1, src2)  __sub_f(src1, src2)
#define _rsub_f(src1, src2) __rsub_f(src1, src2)
#define _add1(src1, src2)   __add1(src1, src2)
#define _add1_f(src1, src2) __add1_f(src1, src2)
#define _sub1(src1, src2)   __sub1(src1, src2)
#define _sub1_f(src1, src2) __sub1_f(src1, src2)
#define _add2(src1, src2)   __add2(src1, src2)
#define _add2_f(src1, src2) __add2_f(src1, src2)
#define _sub2(src1, src2)   __sub2(src1, src2)
#define _sub2_f(src1, src2) __sub2_f(src1, src2)
#define _add3(src1, src2)   __add3(src1, src2)
#define _add3_f(src1, src2) __add3_f(src1, src2)
#define _sub3(src1, src2)   __sub3(src1, src2)
#define _sub3_f(src1, src2) __sub3_f(src1, src2)
#define _abss(a)            __abss(a)
#define _abss_f(a)          __abss_f(a)
#define _max(a, b)          __max(a, b)
#define _max_f(a, b)        __max_f(a, b)
#define _min(a, b)          __min(a, b)
#define _min_f(a, b)        __min_f(a, b)
#define _abssw(a)           __abssw(a)
#define _abssw_f(a)         __abssw_f(a)
#define _bmsk(x, m)         __bmsk(x, m)
#define _bmsk_f(x, m)       __bmsk_f(x, m)
#define _bset(x, m)         __bset(x, m)
#define _btst(x, m)         __btst(x, m)
#define _btst_f(x, m)       __btst_f(x, m)
#define _bclr(x, m)         __bclr(x, m)
#define _bclr_f(x, m)       __bclr_f(x, m)
#define _bxor(x, m)         __bxor(x, m)
#define _bxor_f(x, m)       __bxor_f(x, m)
#define _norm(x)            __norm(x)
#define _norm_f(x)          __norm_f(x)
#define _normw(x)           __normw(x)
#define _normw_f(x)         __normw_f(x)
#define _swap(a)            __swap(a)
#define _swap_f(a)          __swap_f(a)
#define _sat16(a)           __sat16(a)
#define _sat16_f(a)         __sat16_f(a)
#define _rnd16(a)           __rnd16(a)
#define _rnd16_f(a)         __rnd16_f(a)
#define _divaw(src1, src2)  __divaw(src1, src2)
#define _push(src)          __push(src)
#define _pop()              __pop()
#define _subsdw(a, b)       __subsdw(a, b)
#define _addsdw(a, b)       __addsdw(a, b)

// Assembler macros (value is passed and returned in r0 register)
#define _Nop()              __Nop()
#define _Mov(b, c)          __Mov(b, c)
#define _Mov_f(b, c)        __Mov_f(b, c)
#define _Asl(a, s)          __Asl(a, s)
#define _Asl_f(a, s)        __Asl_f(a, s)
#define _Asr(x, s)          __Asr(x, s)
#define _Asr_f(x, s)        __Asr_f(x, s)
#define _Lsr(a, s)          __Lsr(a, s)
#define _Lsr_f(a, s)        __Lsr_f(a, s)
#define _Asls(a, s)         __Asls(a, s)
#define _Asls_f(a, s)       __Asls_f(a, s)
#define _Asrs(a, s)         __Asrs(a, s)
#define _Asrs_f(a, s)       __Asrs_f(a, s)
#define _Ror(a, b)          __Ror(a, b)
#define _Rlc(a)             __Rlc(a)
#define _Rlc_f(a)           __Rlc_f(a)
#define _Or(a, b)           __Or(a, b)
#define _Or_f(a, b)         __Or_f(a, b)
#define _And(a, b)          __And(a, b)
#define _And_f(a, b)        __And_f(a, b)
#define _Adds(a, b)         __Adds(a, b)
#define _Adds_f(a, b)       __Adds_f(a, b)
#define _Subs(a, b)         __Subs(a, b)
#define _Subs_f(a, b)       __Subs_f(a, b)
#define _Negs(a)            __Negs(a)
#define _Negs_f(a)          __Negs_f(a)
#define _Negsw(a)           __Negsw(a)
#define _Negsw_f(a)         __Negsw_f(a)
#define _Add(src1, src2)    __Add(src1, src2)
#define _Add_f(src1, src2)  __Add_f(src1, src2)
#define _Sub(src1, src2)    __Sub(src1, src2)
#define _Sub_f(src1, src2)  __Sub_f(src1, src2)
#define _Add1(src1, src2)   __Add1(src1, src2)
#define _Add1_f(src1, src2) __Add1_f(src1, src2)
#define _Sub1(src1, src2)   __Sub1(src1, src2)
#define _Sub1_f(src1, src2) __Sub1_f(src1, src2)
#define _Add2(src1, src2)   __Add2(src1, src2)
#define _Add2_f(src1, src2) __Add2_f(src1, src2)
#define _Sub2(src1, src2)   __Sub2(src1, src2)
#define _Sub2_f(src1, src2) __Sub2_f(src1, src2)
#define _Add3(src1, src2)   __Add3(src1, src2)
#define _Add3_f(src1, src2) __Add3_f(src1, src2)
#define _Sub3(src1, src2)   __Sub3(src1, src2)
#define _Sub3_f(src1, src2) __Sub3_f(src1, src2)
#define _Abss(a)            __Abss(a)
#define _Abss_f(a)          __Abss_f(a)
#define _Max(a, b)          __Max(a, b)
#define _Max_f(a, b)        __Max_f(a, b)
#define _Min(a, b)          __Min(a, b)
#define _Min_f(a, b)        __Min_f(a, b)
#define _Abssw(a)           __Abssw(a)
#define _Abssw_f(a)         __Abssw_f(a)
#define _Bmsk(x, m)         __Bmsk(x, m)
#define _Bmsk_f(x, m)       __Bmsk_f(x, m)
#define _Bset(x, m)         __Bset(x, m)
#define _Bset_f(x, m)       __Bset_f(x, m)
#define _Btst(x, m)         __Btst(x, m)
#define _Bclr(x, m)         __Bclr(x, m)
#define _Bclr_f(x, m)       __Bclr_f(x, m)
#define _Bxor(x, m)         __Bxor(x, m)
#define _Bxor_f(x, m)       __Bxor_f(x, m)
#define _Normw(x)           __Normw(x)
#define _Normw_f(x)         __Normw_f(x)
#define _Norm(x)            __Norm(x)
#define _Norm_f(x)          __Norm_f(x)
#define _Swap(a)            __Swap(a)
#define _Swap_f(a)          __Swap_f(a)
#define _Sat16(a)           __Sat16(a)
#define _Sat16_f(a)         __Sat16_f(a)
#define _Rnd16(a)           __Rnd16(a)
#define _Rnd16_f(a)         __Rnd16_f(a)
#define _Divaw(src1, src2)  __Divaw(src1, src2)
#define _Push(src)          __Push(src)
#define _Pop()              __Pop()
#define _Subsdw(a, b)       __Subsdw(a, b)
#define _Addsdw(a, b)       __Addsdw(a, b)

//
// Extension multiply/accumulate
//

// Intrinsics
#define _mult_0(src1, src2)         __mult_0(src1, src2)
#define _mult(src1, src2)           __mult(src1, src2)
/* Simeon */
#define _mulrt(src1, src2)          __mulrt(src1, src2)
#define _mact_0(src1, src2)         __mact_0(src1, src2)
#define _mact(src1, src2)           __mact(src1, src2)
/* Simeon */
#define _macrt(src1, src2)          __macrt(src1, src2)
#define _msubt_0(src1, src2)        __msubt_0(src1, src2)
#define _msubt(src1, src2)          __msubt(src1, src2)
#define _mulflw_0(src1, src2)       __mulflw_0(src1, src2)
#define _mulflw_f_0(src1, src2)     __mulflw_f_0(src1, src2)
#define _mulflw(src1, src2)         __mulflw(src1, src2)
#define _mulflw_f(src1, src2)       __mulflw_f(src1, src2)
#define _macflw_0(src1, src2)       __macflw_0(src1, src2)
#define _macflw_f_0(src1, src2)     __macflw_f_0(src1, src2)
#define _macflw(src1, src2)         __macflw(src1, src2)
#define _macflw_f(src1, src2)       __macflw_f(src1, src2)
#define _mulhflw_0(src1, src2)      __mulhflw_0(src1, src2)
#define _mulhflw_f_0(src1, src2)    __mulhflw_f_0(src1, src2)
#define _mulhflw(src1, src2)        __mulhflw(src1, src2)

/* AndreiMi */
/* EdwardA */
#define _mulhflw_lt(dst, src1, src2)     __mulhflw_lt(dst, src1, src2)
#define _mulhflw_ge(dst, src1, src2)     __mulhflw_ge(dst, src1, src2)
#define _mulhflw_c(dst, src1, src2)      __mulhflw_c(dst, src1, src2)

#define _mulhflw_f(src1, src2)      __mulhflw_f(src1, src2)
#define _machflw_0(src1, src2)      __machflw_0(src1, src2)
#define _machflw_f_0(src1, src2)    __machflw_f_0(src1, src2)
#define _machflw(src1, src2)        __machflw(src1, src2)
#define _machflw_f(src1, src2)      __machflw_f(src1, src2)
#define _mullw_0(src1, src2)        __mullw_0(src1, src2)
#define _mullw_f_0(src1, src2)      __mullw_f_0(src1, src2)
#define _mullw(src1, src2)          __mullw(src1, src2)
#define _mululw_0(src1, src2)       __mululw_0(src1, src2)
#define _mululw(src1, src2)         __mululw(src1, src2)
#define _mullw_f(src1, src2)        __mullw_f(src1, src2)
#define _mulhlw_0(src1, src2)       __mulhlw_0(src1, src2)
#define _mulhlw_f_0(src1, src2)     __mulhlw_f_0(src1, src2)
#define _mulhlw(src1, src2)         __mulhlw(src1, src2)
#define _mulhlw_f(src1, src2)       __mulhlw_f(src1, src2)
#define _maclw_0(src1, src2)        __maclw_0(src1, src2)
#define _maclw_f_0(src1, src2)      __maclw_f_0(src1, src2)
#define _maclw(src1, src2)          __maclw(src1, src2)
#define _maclw_f(src1, src2)        __maclw_f(src1, src2)
#define _machlw_0(src1, src2)       __machlw_0(src1, src2)
#define _machlw_f_0(src1, src2)     __machlw_f_0(src1, src2)
#define _machlw(src1, src2)         __machlw(src1, src2)
#define _machlw_f(src1, src2)       __machlw_f(src1, src2)
#define _machulw(src1, src2)        __machulw(src1, src2)
#define _machulw_f(src1, src2)      __machulw_f(src1, src2)
#define _machulw_0(src1, src2)      __machulw_0(src1, src2)
#define _machulw_f_0(src1, src2)    __machulw_f_0(src1, src2)
#define _muldw(src1, src2)          __muldw(src1, src2)
#define _muldw_0(src1, src2)        __muldw_0(src1, src2)
#define _mulrdw(src1, src2)         __mulrdw(src1, src2)
#define _macdw(src1, src2)          __macdw(src1, src2)
#define _macdw_0(src1, src2)        __macdw_0(src1, src2)
#define _msubdw_0(src1, src2)       __msubdw_0(src1, src2)
#define _dmulpf_xy(src1, src2)      __dmulpf_xy(src1, src2)
#define _dmulpf_xy_0(src1, src2)    __dmulpf_xy_0(src1, src2)
#define _dmacpf_xy(src1, src2)      __dmacpf_xy(src1, src2)
#define _dmacpf_xy_0(src1, src2)    __dmacpf_xy_0(src1, src2)

#define _get_ACC1()                 __get_ACC1()
#define _get_ACC2()                 __get_ACC2()

/* AndreiMi */
#define _get_ACC1_H()               __get_ACC1_H()
#define _get_ACC2_H()               __get_ACC2_H()

//AndreyM
#define _get_xbase()              __get_xbase()
#define _get_ybase()              __get_ybase()

#define _get_AAh()                  __get_AAh()
#define _get_AAl()                  __get_AAl()

/* Simeon: added get_aux_* macros */
#define _get_AUX_XMAC0_24()         __get_AUX_XMAC0_24()
#define _get_AUX_XMAC1_24()         __get_AUX_XMAC1_24()
#define _get_AUX_XMAC2_24()         __get_AUX_XMAC2_24()

// Assembler macros (value is passed and returned in r0 register)
#define _Mult_0(src1, src2)         __Mult_0(src1, src2)
#define _Mult(src1, src2)           __Mult(src1, src2)
/* Simeon: added _Mulrt */
#define _Mulrt(src1, src2)          __Mulrt(src1, src2)
#define _Mact_0(src1, src2)         __Mact_0(src1, src2)
#define _Mact(src1, src2)           __Mact(src1, src2)
/* Simeon: added _Macrt */
#define _Macrt(src1, src2)          __Macrt(src1, src2)
#define _Msubt_0(src1, src2)        __Msubt_0(src1, src2)
#define _Msubt(src1, src2)          __Msubt(src1, src2)
#define _Mulflw_0(src1, src2)       __Mulflw_0(src1, src2)
#define _Mulflw_f_0(src1, src2)     __Mulflw_f_0(src1, src2)
#define _Mulflw(src1, src2)         __Mulflw(src1, src2)
#define _Mulflw_f(src1, src2)       __Mulflw_f(src1, src2)
#define _Macflw_0(src1, src2)       __Macflw_0(src1, src2)
#define _Macflw_f_0(src1, src2)     __Macflw_f_0(src1, src2)
#define _Macflw(src1, src2)         __Macflw(src1, src2)
#define _Macflw_f(src1, src2)       __Macflw_f(src1, src2)
#define _Mulhflw_0(src1, src2)      __Mulhflw_0(src1, src2)
#define _Mulhflw_f_0(src1, src2)    __Mulhflw_f_0(src1, src2)
#define _Mulhflw(src1, src2)        __Mulhflw(src1, src2)
#define _Mulhflw_f(src1, src2)      __Mulhflw_f(src1, src2)
#define _Machflw_0(src1, src2)      __Machflw_0(src1, src2)
#define _Machflw_f_0(src1, src2)    __Machflw_f_0(src1, src2)
#define _Machflw(src1, src2)        __Machflw(src1, src2)
#define _Machflw_f(src1, src2)      __Machflw_f(src1, src2)
#define _Mullw_0(src1, src2)        __Mullw_0(src1, src2)
#define _Mullw_f_0(src1, src2)      __Mullw_f_0(src1, src2)
#define _Mullw(src1, src2)          __Mullw(src1, src2)
#define _Mululw_0(src1, src2)       __Mululw_0(src1, src2)
#define _Mululw(src1, src2)         __Mululw(src1, src2)
#define _Mullw_f(src1, src2)        __Mullw_f(src1, src2)
#define _Mulhlw_0(src1, src2)       __Mulhlw_0(src1, src2)
#define _Mulhlw_f_0(src1, src2)     __Mulhlw_f_0(src1, src2)
#define _Mulhlw(src1, src2)         __Mulhlw(src1, src2)
#define _Mulhlw_f(src1, src2)       __Mulhlw_f(src1, src2)
#define _Maclw_0(src1, src2)        __Maclw_0(src1, src2)
#define _Maclw_f_0(src1, src2)      __Maclw_f_0(src1, src2)
#define _Maclw(src1, src2)          __Maclw(src1, src2)
#define _Maclw_f(src1, src2)        __Maclw_f(src1, src2)
#define _Machlw_0(src1, src2)       __Machlw_0(src1, src2)
#define _Machlw_f_0(src1, src2)     __Machlw_f_0(src1, src2)
#define _Machlw(src1, src2)         __Machlw(src1, src2)
#define _Machlw_f(src1, src2)       __Machlw_f(src1, src2)
#define _Machulw(src1, src2)        __Machulw(src1, src2)
#define _Machulw_f(src1, src2)      __Machulw_f(src1, src2)
#define _Machulw_0(src1, src2)      __Machulw_0(src1, src2)
#define _Machulw_f_0(src1, src2)    __Machulw_f_0(src1, src2)
#define _Muldw(src1, src2)          __Muldw(src1, src2)
#define _Muldw_0(src1, src2)        __Muldw_0(src1, src2)
#define _Mulrdw(src1, src2)         __Mulrdw(src1, src2)
#define _Macdw(src1, src2)          __Macdw(src1, src2)
#define _Macdw_0(src1, src2)        __Macdw_0(src1, src2)
#define _Msubdw_0(src1, src2)       __Msubdw_0(src1, src2)

#define _Get_AUX_XMAC0_24()           __Get_AUX_XMAC0_24()
#define _Get_AUX_XMAC1_24()           __Get_AUX_XMAC1_24()
#define _Get_AUX_XMAC2_24()           __Get_AUX_XMAC2_24(

#define _Get_ACC1()                 __Get_ACC1()
#define _Get_ACC2()                 __Get_ACC2()
#define _Get_AAh()                  __Get_AAh()
#define _Get_AAl()                  __Get_AAl()

#define _crc(src1, src2)            __crc(src1, src2)

//
// XY memory addressing
//

// Intrinsics
#define _ax0()      __ax0()
#define _ax1()      __ax1()
#define _ax2()      __ax2()
#define _ax3()      __ax3()

#define _ay0()      __ay0()
#define _ay1()      __ay1()
#define _ay2()      __ay2()
#define _ay3()      __ay3()

// Assembler macros (value is passed and returned in r0 register)
#define _Ax0()      __Ax0()
#define _Ax1()      __Ax1()
#define _Ax2()      __Ax2()
#define _Ax3()      __Ax3()

#define _Ay0()      __Ay0()
#define _Ay1()      __Ay1()
#define _Ay2()      __Ay2()
#define _Ay3()      __Ay3()

// Intrinsics
#define _set_ax0(a)     __set_ax0(a)
#define _set_ax1(a)     __set_ax1(a)
#define _set_ax2(a)     __set_ax2(a)
#define _set_ax3(a)     __set_ax3(a)

#define _set_ay0(a)     __set_ay0(a)
#define _set_ay1(a)     __set_ay1(a)
#define _set_ay2(a)     __set_ay2(a)
#define _set_ay3(a)     __set_ay3(a)

// Assembler macros (value is passed and returned in r0 register)
#define _Set_ax0(a)     __Set_ax0(a)
#define _Set_ax1(a)     __Set_ax1(a)
#define _Set_ax2(a)     __Set_ax2(a)
#define _Set_ax3(a)     __Set_ax3(a)

#define _Set_ay0(a)     __Set_ay0(a)
#define _Set_ay1(a)     __Set_ay1(a)
#define _Set_ay2(a)     __Set_ay2(a)
#define _Set_ay3(a)     __Set_ay3(a)

// Intrinsics
#define _mx00()    __mx00()
#define _mx01()    __mx01()
#define _mx10()    __mx10()
#define _mx11()    __mx11()
#define _mx20()    __mx20()
#define _mx21()    __mx21()
#define _mx30()    __mx30()
#define _mx31()    __mx31()

#define _my00()    __my00()
#define _my01()    __my01()
#define _my10()    __my10()
#define _my11()    __my11()
#define _my20()    __my20()
#define _my21()    __my21()
#define _my30()    __my30()
#define _my31()    __my31()

// Assembler macros (value is passed and returned in r0 register)
#define _Mx00()    __Mx00()
#define _Mx01()    __Mx01()
#define _Mx10()    __Mx10()
#define _Mx11()    __Mx11()
#define _Mx20()    __Mx20()
#define _Mx21()    __Mx21()
#define _Mx30()    __Mx30()
#define _Mx31()    __Mx31()

#define _My00()    __My00()
#define _My01()    __My01()
#define _My10()    __My10()
#define _My11()    __My11()
#define _My20()    __My20()
#define _My21()    __My21()
#define _My30()    __My30()
#define _My31()    __My31()

// Intrinsics
#define _set_mx00(a)    __set_mx00(a)
#define _set_mx01(a)    __set_mx01(a)
#define _set_mx10(a)    __set_mx10(a)
#define _set_mx11(a)    __set_mx11(a)
#define _set_mx20(a)    __set_mx20(a)
#define _set_mx21(a)    __set_mx21(a)
#define _set_mx30(a)    __set_mx30(a)
#define _set_mx31(a)    __set_mx31(a)

#define _set_my00(a)    __set_my00(a)
#define _set_my01(a)    __set_my01(a)
#define _set_my10(a)    __set_my10(a)
#define _set_my11(a)    __set_my11(a)
#define _set_my20(a)    __set_my20(a)
#define _set_my21(a)    __set_my21(a)
#define _set_my30(a)    __set_my30(a)
#define _set_my31(a)    __set_my31(a)

// Assembler macros (value is passed and returned in r0 register)
#define _Set_mx00(a)    __Set_mx00(a)
#define _Set_mx01(a)    __Set_mx01(a)
#define _Set_mx10(a)    __Set_mx10(a)
#define _Set_mx11(a)    __Set_mx11(a)
#define _Set_mx20(a)    __Set_mx20(a)
#define _Set_mx21(a)    __Set_mx21(a)
#define _Set_mx30(a)    __Set_mx30(a)
#define _Set_mx31(a)    __Set_mx31(a)

#define _Set_my00(a)    __Set_my00(a)
#define _Set_my01(a)    __Set_my01(a)
#define _Set_my10(a)    __Set_my10(a)
#define _Set_my11(a)    __Set_my11(a)
#define _Set_my20(a)    __Set_my20(a)
#define _Set_my21(a)    __Set_my21(a)
#define _Set_my30(a)    __Set_my30(a)
#define _Set_my31(a)    __Set_my31(a)

// Intrinsics
#define _x0_u0()        __x0_u0()
#define _x0_u1()        __x0_u1()
#define _x0_nu()        __x0_nu()
#define _x1_u0()        __x1_u0()
#define _x1_u1()        __x1_u1()
#define _x1_nu()        __x1_nu()
#define _x2_u0()        __x2_u0()
#define _x2_u1()        __x2_u1()
#define _x2_nu()        __x2_nu()
#define _x3_u0()        __x3_u0()
#define _x3_u1()        __x3_u1()
#define _x3_nu()        __x3_nu()
#define _y0_u0()        __y0_u0()
#define _y0_u1()        __y0_u1()
#define _y0_nu()        __y0_nu()
#define _y1_u0()        __y1_u0()
#define _y1_u1()        __y1_u1()
#define _y1_nu()        __y1_nu()
#define _y2_u0()        __y2_u0()
#define _y2_u1()        __y2_u1()
#define _y2_nu()        __y2_nu()
#define _y3_u0()        __y3_u0()
#define _y3_u1()        __y3_u1()
#define _y3_nu()        __y3_nu()

#define _xy0_u0()       __xy0_u0()
#define _xy0_u1()       __xy0_u1()
#define _xy0_nu()       __xy0_nu()
#define _xy1_u0()       __xy1_u0()
#define _xy1_u1()       __xy1_u1()
#define _xy1_nu()       __xy1_nu()
#define _xy2_u0()       __xy2_u0()
#define _xy2_u1()       __xy2_u1()
#define _xy2_nu()       __xy2_nu()
#define _xy3_u0()       __xy3_u0()
#define _xy3_u1()       __xy3_u1()
#define _xy3_nu()       __xy3_nu()
#define _yx0_u0()       __yx0_u0()
#define _yx0_u1()       __yx0_u1()
#define _yx0_nu()       __yx0_nu()
#define _yx1_u0()       __yx1_u0()
#define _yx1_u1()       __yx1_u1()
#define _yx1_nu()       __yx1_nu()
#define _yx2_u0()       __yx2_u0()
#define _yx2_u1()       __yx2_u1()
#define _yx2_nu()       __yx2_nu()
#define _yx3_u0()       __yx3_u0()
#define _yx3_u1()       __yx3_u1()
#define _yx3_nu()       __yx3_nu()

// Assembler macros (value is passed and returned in r0 register)
#define _X0_u0()        __X0_u0()
#define _X0_u1()        __X0_u1()
#define _X0_nu()        __X0_nu()
#define _X1_u0()        __X1_u0()
#define _X1_u1()        __X1_u1()
#define _X1_nu()        __X1_nu()
#define _X2_u0()        __X2_u0()
#define _X2_u1()        __X2_u1()
#define _X2_nu()        __X2_nu()
#define _X3_u0()        __X3_u0()
#define _X3_u1()        __X3_u1()
#define _X3_nu()        __X3_nu()
#define _Y0_u0()        __Y0_u0()
#define _Y0_u1()        __Y0_u1()
#define _Y0_nu()        __Y0_nu()
#define _Y1_u0()        __Y1_u0()
#define _Y1_u1()        __Y1_u1()
#define _Y1_nu()        __Y1_nu()
#define _Y2_u0()        __Y2_u0()
#define _Y2_u1()        __Y2_u1()
#define _Y2_nu()        __Y2_nu()
#define _Y3_u0()        __Y3_u0()
#define _Y3_u1()        __Y3_u1()
#define _Y3_nu()        __Y3_nu()

#define _Xy0_u0()       __Xy0_u0()
#define _Xy0_u1()       __Xy0_u1()
#define _Xy0_nu()       __Xy0_nu()
#define _Xy1_u0()       __Xy1_u0()
#define _Xy1_u1()       __Xy1_u1()
#define _Xy1_nu()       __Xy1_nu()
#define _Xy2_u0()       __Xy2_u0()
#define _Xy2_u1()       __Xy2_u1()
#define _Xy2_nu()       __Xy2_nu()
#define _Xy3_u0()       __Xy3_u0()
#define _Xy3_u1()       __Xy3_u1()
#define _Xy3_nu()       __Xy3_nu()
#define _Yx0_u0()       __Yx0_u0()
#define _Yx0_u1()       __Yx0_u1()
#define _Yx0_nu()       __Yx0_nu()
#define _Yx1_u0()       __Yx1_u0()
#define _Yx1_u1()       __Yx1_u1()
#define _Yx1_nu()       __Yx1_nu()
#define _Yx2_u0()       __Yx2_u0()
#define _Yx2_u1()       __Yx2_u1()
#define _Yx2_nu()       __Yx2_nu()
#define _Yx3_u0()       __Yx3_u0()
#define _Yx3_u1()       __Yx3_u1()
#define _Yx3_nu()       __Yx3_nu()


#define _aux_crc_poly()    __aux_crc_poly()
#define _aux_crc_mode()    __aux_crc_mode()

#define _set_aux_crc_poly(x)    __set_aux_crc_poly(x)
#define _set_aux_crc_mode(x)    __set_aux_crc_mode(x)

// Intrinsics
#define _set_x0_u0(x)   __set_x0_u0(x)
#define _set_x0_u1(x)   __set_x0_u1(x)
#define _set_x0_nu(x)   __set_x0_nu(x)
#define _set_x1_u0(x)   __set_x1_u0(x)
#define _set_x1_u1(x)   __set_x1_u1(x)
#define _set_x1_nu(x)   __set_x1_nu(x)
#define _set_x2_u0(x)   __set_x2_u0(x)
#define _set_x2_u1(x)   __set_x2_u1(x)
#define _set_x2_nu(x)   __set_x2_nu(x)
#define _set_x3_u0(x)   __set_x3_u0(x)
#define _set_x3_u1(x)   __set_x3_u1(x)
#define _set_x3_nu(x)   __set_x3_nu(x)

#define _set_y0_u0(x)   __set_y0_u0(x)
#define _set_y0_u1(x)   __set_y0_u1(x)
#define _set_y0_nu(x)   __set_y0_nu(x)
#define _set_y1_u0(x)   __set_y1_u0(x)
#define _set_y1_u1(x)   __set_y1_u1(x)
#define _set_y1_nu(x)   __set_y1_nu(x)
#define _set_y2_u0(x)   __set_y2_u0(x)
#define _set_y2_u1(x)   __set_y2_u1(x)
#define _set_y2_nu(x)   __set_y2_nu(x)
#define _set_y3_u0(x)   __set_y3_u0(x)
#define _set_y3_u1(x)   __set_y3_u1(x)
#define _set_y3_nu(x)   __set_y3_nu(x)

#define _set_xy0_u0(x)  __set_xy0_u0(x)
#define _set_xy0_u1(x)  __set_xy0_u1(x)
#define _set_xy0_nu(x)  __set_xy0_nu(x)
#define _set_xy1_u0(x)  __set_xy1_u0(x)
#define _set_xy1_u1(x)  __set_xy1_u1(x)
#define _set_xy1_nu(x)  __set_xy1_nu(x)
#define _set_xy2_u0(x)  __set_xy2_u0(x)
#define _set_xy2_u1(x)  __set_xy2_u1(x)
#define _set_xy2_nu(x)  __set_xy2_nu(x)
#define _set_xy3_u0(x)  __set_xy3_u0(x)
#define _set_xy3_u1(x)  __set_xy3_u1(x)
#define _set_xy3_nu(x)  __set_xy3_nu(x)

#define _set_yx0_u0(x)  __set_yx0_u0(x)
#define _set_yx0_u1(x)  __set_yx0_u1(x)
#define _set_yx0_nu(x)  __set_yx0_nu(x)
#define _set_yx1_u0(x)  __set_yx1_u0(x)
#define _set_yx1_u1(x)  __set_yx1_u1(x)
#define _set_yx1_nu(x)  __set_yx1_nu(x)
#define _set_yx2_u0(x)  __set_yx2_u0(x)
#define _set_yx2_u1(x)  __set_yx2_u1(x)
#define _set_yx2_nu(x)  __set_yx2_nu(x)
#define _set_yx3_u0(x)  __set_yx3_u0(x)
#define _set_yx3_u1(x)  __set_yx3_u1(x)
#define _set_yx3_nu(x)  __set_yx3_nu(x)

#ifdef _MSC_VER
#define _mov_x0_u0(x)   __set_x0_u0(x)
#define _mov_x0_u1(x)   __set_x0_u1(x)
#define _mov_x0_nu(x)   __set_x0_nu(x)
#define _mov_x1_u0(x)   __set_x1_u0(x)
#define _mov_x1_u1(x)   __set_x1_u1(x)
#define _mov_x1_nu(x)   __set_x1_nu(x)
#define _mov_x2_u0(x)   __set_x2_u0(x)
#define _mov_x2_u1(x)   __set_x2_u1(x)
#define _mov_x2_nu(x)   __set_x2_nu(x)
#define _mov_x3_u0(x)   __set_x3_u0(x)
#define _mov_x3_u1(x)   __set_x3_u1(x)
#define _mov_x3_nu(x)   __set_x3_nu(x)

#define _mov_y0_u0(x)   __set_y0_u0(x)
#define _mov_y0_u1(x)   __set_y0_u1(x)
#define _mov_y0_nu(x)   __set_y0_nu(x)
#define _mov_y1_u0(x)   __set_y1_u0(x)
#define _mov_y1_u1(x)   __set_y1_u1(x)
#define _mov_y1_nu(x)   __set_y1_nu(x)
#define _mov_y2_u0(x)   __set_y2_u0(x)
#define _mov_y2_u1(x)   __set_y2_u1(x)
#define _mov_y2_nu(x)   __set_y2_nu(x)
#define _mov_y3_u0(x)   __set_y3_u0(x)
#define _mov_y3_u1(x)   __set_y3_u1(x)
#define _mov_y3_nu(x)   __set_y3_nu(x)
#else
#define _mov_x0_u0(x)   __mov(_x0_u0(), x)
#define _mov_x0_u1(x)   __mov(_x0_u1(), x)
#define _mov_x0_nu(x)   __mov(_x0_nu(), x)
#define _mov_x1_u0(x)   __mov(_x1_u0(), x)
#define _mov_x1_u1(x)   __mov(_x1_u1(), x)
#define _mov_x1_nu(x)   __mov(_x1_nu(), x)
#define _mov_x2_u0(x)   __mov(_x2_u0(), x)
#define _mov_x2_u1(x)   __mov(_x2_u1(), x)
#define _mov_x2_nu(x)   __mov(_x2_nu(), x)
#define _mov_x3_u0(x)   __mov(_x3_u0(), x)
#define _mov_x3_u1(x)   __mov(_x3_u1(), x)
#define _mov_x3_nu(x)   __mov(_x3_nu(), x)

#define _mov_y0_u0(x)   __mov(_y0_u0(), x)
#define _mov_y0_u1(x)   __mov(_y0_u1(), x)
#define _mov_y0_nu(x)   __mov(_y0_nu(), x)
#define _mov_y1_u0(x)   __mov(_y1_u0(), x)
#define _mov_y1_u1(x)   __mov(_y1_u1(), x)
#define _mov_y1_nu(x)   __mov(_y1_nu(), x)
#define _mov_y2_u0(x)   __mov(_y2_u0(), x)
#define _mov_y2_u1(x)   __mov(_y2_u1(), x)
#define _mov_y2_nu(x)   __mov(_y2_nu(), x)
#define _mov_y3_u0(x)   __mov(_y3_u0(), x)
#define _mov_y3_u1(x)   __mov(_y3_u1(), x)
#define _mov_y3_nu(x)   __mov(_y3_nu(), x)
#endif

// Assembler macros (value is passed and returned in r0 register)
#define _Set_x0_u0(x)   __Set_x0_u0(x)
#define _Set_x0_u1(x)   __Set_x0_u1(x)
#define _Set_x0_nu(x)   __Set_x0_nu(x)
#define _Set_x1_u0(x)   __Set_x1_u0(x)
#define _Set_x1_u1(x)   __Set_x1_u1(x)
#define _Set_x1_nu(x)   __Set_x1_nu(x)
#define _Set_x2_u0(x)   __Set_x2_u0(x)
#define _Set_x2_u1(x)   __Set_x2_u1(x)
#define _Set_x2_nu(x)   __Set_x2_nu(x)
#define _Set_x3_u0(x)   __Set_x3_u0(x)
#define _Set_x3_u1(x)   __Set_x3_u1(x)
#define _Set_x3_nu(x)   __Set_x3_nu(x)

#define _Set_y0_u0(x)   __Set_y0_u0(x)
#define _Set_y0_u1(x)   __Set_y0_u1(x)
#define _Set_y0_nu(x)   __Set_y0_nu(x)
#define _Set_y1_u0(x)   __Set_y1_u0(x)
#define _Set_y1_u1(x)   __Set_y1_u1(x)
#define _Set_y1_nu(x)   __Set_y1_nu(x)
#define _Set_y2_u0(x)   __Set_y2_u0(x)
#define _Set_y2_u1(x)   __Set_y2_u1(x)
#define _Set_y2_nu(x)   __Set_y2_nu(x)
#define _Set_y3_u0(x)   __Set_y3_u0(x)
#define _Set_y3_u1(x)   __Set_y3_u1(x)
#define _Set_y3_nu(x)   __Set_y3_nu(x)

#define _Set_xy0_u0(x)  __Set_xy0_u0(x)
#define _Set_xy0_u1(x)  __Set_xy0_u1(x)
#define _Set_xy0_nu(x)  __Set_xy0_nu(x)
#define _Set_xy1_u0(x)  __Set_xy1_u0(x)
#define _Set_xy1_u1(x)  __Set_xy1_u1(x)
#define _Set_xy1_nu(x)  __Set_xy1_nu(x)
#define _Set_xy2_u0(x)  __Set_xy2_u0(x)
#define _Set_xy2_u1(x)  __Set_xy2_u1(x)
#define _Set_xy2_nu(x)  __Set_xy2_nu(x)
#define _Set_xy3_u0(x)  __Set_xy3_u0(x)
#define _Set_xy3_u1(x)  __Set_xy3_u1(x)
#define _Set_xy3_nu(x)  __Set_xy3_nu(x)

#define _Set_yx0_u0(x)  __Set_yx0_u0(x)
#define _Set_yx0_u1(x)  __Set_yx0_u1(x)
#define _Set_yx0_nu(x)  __Set_yx0_nu(x)
#define _Set_yx1_u0(x)  __Set_yx1_u0(x)
#define _Set_yx1_u1(x)  __Set_yx1_u1(x)
#define _Set_yx1_nu(x)  __Set_yx1_nu(x)
#define _Set_yx2_u0(x)  __Set_yx2_u0(x)
#define _Set_yx2_u1(x)  __Set_yx2_u1(x)
#define _Set_yx2_nu(x)  __Set_yx2_nu(x)
#define _Set_yx3_u0(x)  __Set_yx3_u0(x)
#define _Set_yx3_u1(x)  __Set_yx3_u1(x)
#define _Set_yx3_nu(x)  __Set_yx3_nu(x)

#endif // !ARC600_OLD_NAMES

///////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
    #define reg_var(t, x, n)    t x
#else
    #define reg_var(t, x, n)    t x == n;
#endif // _MSC_VER

#ifdef _MSC_VER
///////////////////////////////////////////////////////////////////////////////
// PC branch
///////////////////////////////////////////////////////////////////////////////
extern BOOL _Z;
extern BOOL _N;
extern BOOL _C;
extern BOOL _V;


//
// Condition codes checking
//
#define _condition_z        (_Z)    // Zero
#define _condition_nz       (!_Z)   // Non-Zero
#define _condition_p        (!_N)   // Positive
#define _condition_n        (_N)    // Negative
#define _condition_c        (_C)    // Carry set, lower than (unsigned)
#define _condition_cc       (!_C)   // Carry clear, higher or same (unsigned)
#define _condition_v        (_V)    // Over-flow set
#define _condition_nv       (!_V)   // Over-flow clear
#define _condition_gt       ((_N && _V && !_Z) || (!_N && !_V && !_Z))  // Greater than (signed)
#define _condition_ge       ((_N && _V) || (!_N && !_V))                // Greater than or equal to (signed)
#define _condition_lt       ((_N && !_V) || (!_N && _V))                // Less than (signed)
#define _condition_le       (_Z || (_N && !_V) || (!_N && _V))          // Less than or equal to (signed)
#define _condition_hi       (!_C && !_Z)                                // Higher than (unsigned)
#define _condition_ls       (_C || _Z)                                  // Lower than or same (unsigned)
#define _condition_pnz      (!_N && !_Z)                                // Positive non-zero

//
// Core instruction set simulation
//

// Core basic ops and arithmetics
void     __nop      ();
#define  __mov(b, c)    { b = c; }
#define  __mov_f(b, c)  { _Z = c == 0; _N = c < 0; __mov(b, c); }
int32_t  __asl      (int32_t a, unsigned s);
int32_t  __asl_f    (int32_t a, unsigned s);
int32_t  __asr      (int32_t x, unsigned s);
int32_t  __asr_f    (int32_t x, unsigned s);
uint32_t __lsr      (int32_t a, unsigned s);
uint32_t __lsr_f    (int32_t a, unsigned s);
int32_t  __asls     (int32_t a, signed s);
int32_t  __asls_f   (int32_t a, signed s);
int32_t  __asrs     (int32_t a, signed s);
int32_t  __asrs_f   (int32_t a, signed s);
uint32_t __ror      (int32_t a, unsigned s);
int32_t  __rlc      (int32_t a);
int32_t  __rlc_f    (int32_t a);
int32_t  __or       (int32_t a, int32_t b);
int32_t  __or_f     (int32_t a, int32_t b);
int32_t  __and      (int32_t a, int32_t b);
int32_t  __and_f    (int32_t a, int32_t b);
int32_t  __adds     (int32_t a, int32_t b);
int32_t  __adds_f   (int32_t a, int32_t b);
int32_t  __subs     (int32_t a, int32_t b);
int32_t  __subs_f   (int32_t a, int32_t b);
int32_t  __negs     (int32_t a);
int32_t  __negs_f   (int32_t a);
int16_t  __negsw    (int32_t src1);
int16_t  __negsw_f  (int32_t src1);
int32_t  __add      (int32_t src1, int32_t src2);
int32_t  __add_f    (int32_t src1, int32_t src2);
int32_t  __sub      (int32_t src1, int32_t src2);
int32_t  __rsub     (int32_t src1, int32_t src2);
int32_t  __sub_f    (int32_t src1, int32_t src2);
int32_t  __add1     (int32_t src1, int32_t src2);
int32_t  __add1_f   (int32_t src1, int32_t src2);
int32_t  __sub1     (int32_t src1, int32_t src2);
int32_t  __sub1_f   (int32_t src1, int32_t src2);
int32_t  __add2     (int32_t src1, int32_t src2);
int32_t  __add2_f   (int32_t src1, int32_t src2);
int32_t  __sub2     (int32_t src1, int32_t src2);
int32_t  __sub2_f   (int32_t src1, int32_t src2);
int32_t  __add3     (int32_t src1, int32_t src2);
int32_t  __add3_f   (int32_t src1, int32_t src2);
int32_t  __sub3     (int32_t src1, int32_t src2);
int32_t  __sub3_f   (int32_t src1, int32_t src2);
int32_t  __abss     (int32_t a);
int32_t  __abss_f   (int32_t a);
int32_t  __max      (int32_t a, int32_t b);
int32_t  __max_f    (int32_t a, int32_t b);
int32_t  __min      (int32_t a, int32_t b);
int32_t  __min_f    (int32_t a, int32_t b);
int16_t  __abssw    (int32_t a);
int16_t  __abssw_f  (int32_t a);
uint32_t __bmsk     (uint32_t x, int m);
uint32_t __bmsk_f   (uint32_t x, int m);
uint32_t __bset     (uint32_t x, int m);
uint32_t __bset_f   (uint32_t x, int m);
void     __btst     (uint32_t x, int m);
uint32_t __bclr     (uint32_t x, int m);
uint32_t __bclr_f   (uint32_t x, int m);
uint32_t __bxor     (uint32_t x, int m);
uint32_t __bxor_f   (uint32_t x, int m);
int      __normw    (int32_t x);
int      __normw_f  (int32_t x);
int      __norm     (int32_t x);
int      __norm_f   (int32_t x);
int32_t  __swap     (int32_t a);
int32_t  __swap_f   (int32_t a);
int32_t  __sat16    (int32_t a);
int32_t  __sat16_f  (int32_t a);
int32_t  __rnd16    (int32_t a);
int32_t  __rnd16_f  (int32_t a);
uint32_t __divaw    (uint32_t src1, uint32_t src2);
void     __push     (int32_t src);
int32_t  __pop      ();
uint32_t __subsdw   (uint32_t a, uint32_t b);
uint32_t __addsdw   (uint32_t a, uint32_t b);

#define __Nop()              __nop()
#define __Mov(b, c)          __mov(b, c)
#define __Mov_f(b, c)        __mov_f(b, c)
#define __Asl(a, s)          __asl(a, s)
#define __Asl_f(a, s)        __asl_f(a, s)
#define __Asr(x, s)          __asr(x, s)
#define __Asr_f(x, s)        __asr_f(x, s)
#define __Lsr(a, s)          __lsr(a, s)
#define __Lsr_f(a, s)        __lsr_f(a, s)
#define __Asls(a, s)         __asls(a, s)
#define __Asls_f(a, s)       __asls_f(a, s)
#define __Asrs(a, s)         __asrs(a, s)
#define __Asrs_f(a, s)       __asrs_f(a, s)
#define __Ror(a, b)          __ror(a, b)
#define __Rlc(a)             __rlc(a)
#define __Rlc_f(a)           __rlc_f(a)
#define __Or(a, b)           __or(a, b)
#define __Or_f(a, b)         __or_f(a, b)
#define __And(a, b)          __and(a, b)
#define __And_f(a, b)        __and_f(a, b)
#define __Adds(a, b)         __adds(a, b)
#define __Adds_f(a, b)       __adds_f(a, b)
#define __Subs(a, b)         __subs(a, b)
#define __Subs_f(a, b)       __subs_f(a, b)
#define __Negs(a)            __negs(a)
#define __Negs_f(a)          __negs_f(a)
#define __Negsw(a)           __negsw(a)
#define __Negsw_f(a)         __negsw_f(a)
#define __Add(src1, src2)    __add(src1, src2)
#define __Add_f(src1, src2)  __add_f(src1, src2)
#define __Sub(src1, src2)    __sub(src1, src2)
#define __Rsub(src1, src2)   __rsub(src1, src2)
#define __Sub_f(src1, src2)  __sub_f(src1, src2)
#define __Rsub_f(src1, src2) __rsub_f(src1, src2)
#define __Add1(src1, src2)   __add1(src1, src2)
#define __Add1_f(src1, src2) __add1_f(src1, src2)
#define __Sub1(src1, src2)   __sub1(src1, src2)
#define __Sub1_f(src1, src2) __sub1_f(src1, src2)
#define __Add2(src1, src2)   __add2(src1, src2)
#define __Add2_f(src1, src2) __add2_f(src1, src2)
#define __Sub2(src1, src2)   __sub2(src1, src2)
#define __Sub2_f(src1, src2) __sub2_f(src1, src2)
#define __Add3(src1, src2)   __add3(src1, src2)
#define __Add3_f(src1, src2) __add3_f(src1, src2)
#define __Sub3(src1, src2)   __sub3(src1, src2)
#define __Sub3_f(src1, src2) __sub3_f(src1, src2)
#define __Abss(a)            __abss(a)
#define __Abss_f(a)          __abs_f(a)
#define __Max(a, b)          __max(a, b)
#define __Max_f(a, b)        __max_f(a, b)
#define __Min(a, b)          __min(a, b)
#define __Min_f(a, b)        __min_f(a, b)
#define __Abssw(a)           __abssw(a)
#define __Abssw_f(a)         __abssw_f(a)
#define __Bmsk(x, m)         __bmsk(x, m)
#define __Bmsk_f(x, m)       __bmsk_f(x, m)
#define __Bset(x, m)         __bset(x, m)
#define __Bset_f(x, m)       __bset_f(x, m)
#define __Btst(x, m)         __btst(x, m)
#define __Bclr(x, m)         __bclr(x, m)
#define __Bclr_f(x, m)       __bclr_f(x, m)
#define __Bxor(x, m)         __bxor(x, m)
#define __Bxor_f(x, m)       __bxor_f(x, m)
#define __Normw(x)           __normw(x)
#define __Normw_f(x)         __normw_f(x)
#define __Norm(x)            __norm(x)
#define __Norm_f(x)          __norm_f(x)
#define __Swap(a)            __swap(a)
#define __Swap_f(a)          __swap_f(a)
#define __Sat16(a)           __sat16(a)
#define __Sat16_f(a)         __sat16_f(a)
#define __Rnd16(a)           __rnd16(a)
#define __Rnd16_f(a)         __rnd16_f(a)
#define __Divaw(src1, src2)  __divaw(src1, src2)
#define __Push(src)          __push(src)
#define __Pop()              __pop()
#define __Subsdw(a, b)       __subsdw(a, b)
#define __Addsdw(a, b)       __addsdw(a, b)

// Extension multiply/accumulate
void      __mult_0     (int32_t src1, int32_t src2);
int32_t   __mult       (int32_t src1, int32_t src2);
/* Simeon */
int32_t   __mulrt      (int32_t src1, int32_t src2);
void      __mact_0     (int32_t src1, int32_t src2);
int32_t   __mact       (int32_t src1, int32_t src2);
/* Simeon */
int32_t   __macrt      (int32_t src1, int32_t src2);
void      __msubt_0    (int32_t src1, int32_t src2);
int32_t   __msubt      (int32_t src1, int32_t src2);
int32_t   __mulflw     (int32_t src1, uint32_t src2);
int32_t   __mulflw_f   (int32_t src1, uint32_t src2);
void      __mulflw_0   (int32_t src1, uint32_t src2);
void      __mulflw_f_0 (int32_t src1, uint32_t src2);
int32_t   __macflw     (int32_t src1, uint32_t src2);
int32_t   __macflw_f   (int32_t src1, uint32_t src2);
void      __macflw_0   (int32_t src1, uint32_t src2);
void      __macflw_f_0 (int32_t src1, uint32_t src2);
int32_t   __mulhflw    (int32_t src1, int32_t src2);

/* AndreiMi */
/* EdwardA */
#define __mulhflw_lt(dst, src1, src2)   __mulhflw_lt_(&dst, src1, src2)
#define __mulhflw_ge(dst, src1, src2)   __mulhflw_ge_(&dst, src1, src2)
#define __mulhflw_c(dst, src1, src2)    __mulhflw_c_(&dst, src1, src2)

void      __mulhflw_lt_ (int32_t* dst, int32_t src1, int32_t src2);
void      __mulhflw_ge_ (int32_t* dst, int32_t src1, int32_t src2);
void      __mulhflw_c_  (int32_t* dst, int32_t src1, int32_t src2);

int32_t   __mulhflw_f  (int32_t src1, int32_t src2);
void      __mulhflw_0  (int32_t src1, int32_t src2);
void      __mulhflw_f_0(int32_t src1, int32_t src2);
int32_t   __machflw    (int32_t src1, int32_t src2);
int32_t   __machflw_f  (int32_t src1, int32_t src2);
void      __machflw_0  (int32_t src1, int32_t src2);
void      __machflw_f_0(int32_t src1, int32_t src2);
int32_t   __mullw      (int32_t src1, uint32_t src2);
void      __mululw_0   (uint32_t src1, uint32_t src2);
uint32_t  __mululw     (uint32_t src1, uint32_t src2);
int32_t   __mullw_f    (int32_t src1, uint32_t src2);
void      __mullw_0    (int32_t src1, uint32_t src2);
void      __mullw_f_0  (int32_t src1, uint32_t src2);
int32_t   __mulhlw     (int32_t src1, int32_t src2);
int32_t   __mulhlw_f   (int32_t src1, int32_t src2);
void      __mulhlw_0   (int32_t src1, int32_t src2);
void      __mulhlw_f_0 (int32_t src1, int32_t src2);
int32_t   __maclw      (int32_t src1, uint32_t src2);
int32_t   __maclw_f    (int32_t src1, uint32_t src2);
void      __maclw_0    (int32_t src1, uint32_t src2);
void      __maclw_f_0  (int32_t src1, uint32_t src2);
int32_t   __machlw     (int32_t src1, int32_t src2);
int32_t   __machlw_f   (int32_t src1, int32_t src2);
void      __machlw_0   (int32_t src1, int32_t src2);
void      __machlw_f_0 (int32_t src1, int32_t src2);
uint32_t  __machulw    (uint32_t src1, uint32_t src2);
uint32_t  __machulw_f  (uint32_t src1, uint32_t src2);
void      __machulw_0  (uint32_t src1, uint32_t src2);
void      __machulw_f_0  (uint32_t src1, uint32_t src2);
int32_t   __muldw      (int32_t src1, int32_t src2);
void      __muldw_0    (int32_t src1, int32_t src2);
int32_t   __mulrdw     (int32_t src1, int32_t src2);
int32_t   __macdw      (int32_t src1, int32_t src2);
void      __macdw_0    (int32_t src1, int32_t src2);
void      __msubdw_0   (int32_t src1, int32_t src2);
int32xy_t __dmulpf_xy  (int32xy_t src1, int32_t src2);
void      __dmulpf_xy_0(int32xy_t src1, int32_t src2);
int32xy_t __dmacpf_xy  (int32xy_t src1, int32_t src2);
void      __dmacpf_xy_0(int32xy_t src1, int32_t src2);


uint32_t __get_xbase();
uint32_t __get_ybase();

int32_t  __get_AAh();
uint32_t __get_AAl();
int32_t  __get_ACC1();
uint32_t __get_ACC2();

/* Simeon */
int32_t  __get_AUX_XMAC0_24();
//AndreM
uint32_t __get_AUX_XMAC1_24();
uint32_t __get_AUX_XMAC2_24();

/* AndreiMi */
int32_t  __get_ACC1_H();
int32_t  __get_ACC2_H();

#define __Mult_0(src1, src2)        __mult_0(src1, src2)
#define __Mult(src1, src2)          __mult(src1, src2)
/* Simeon */
#define __Mulrt(src1, src2)         __mulrt(src1, src2)
#define __Mact_0(src1, src2)        __mact_0(src1, src2)
/* Simeon */
#define __Mact(src1, src2)          __mact(src1, src2)
#define __Macrt(src1, src2)         __macrt(src1, src2)
#define __Msubt_0(src1, src2)       __msubt_0(src1, src2)
#define __Msubt(src1, src2)         __msubt(src1, src2)
#define __Mulflw(src1, src2)        __mulflw(src1, src2)
#define __Mulflw_f(src1, src2)      __mulflw_f(src1, src2)
#define __Mulflw_0(src1, src2)      __mulflw_0(src1, src2)
#define __Mulflw_f_0(src1, src2)    __mulflw_f_0(src1, src2)
#define __Macflw(src1, src2)        __macflw(src1, src2)
#define __Macflw_f(src1, src2)      __macflw_f(src1, src2)
#define __Macflw_0(src1, src2)      __macflw_0(src1, src2)
#define __Macflw_f_0(src1, src2)    __macflw_f_0(src1, src2)
#define __Mulhflw(src1, src2)       __mulhflw(src1, src2)
#define __Mulhflw_f(src1, src2)     __mulhflw_f(src1, src2)
#define __Mulhflw_0(src1, src2)     __mulhflw_0(src1, src2)
#define __Mulhflw_f_0(src1, src2)   __mulhflw_f_0(src1, src2)
#define __Machflw(src1, src2)       __machflw(src1, src2)
#define __Machflw_f(src1, src2)     __machflw_f(src1, src2)
#define __Machflw_0(src1, src2)     __machflw_0(src1, src2)
#define __Machflw_f_0(src1, src2)   __machflw_f_0(src1, src2)
#define __Mullw(src1, src2)         __mullw(src1, src2)
#define __Mululw_0(src1, src2)      __mululw_0(src1, src2)
#define __Mululw(src1, src2)        __mululw(src1, src2)
#define __Mullw_f(src1, src2)       __mullw_f(src1, src2)
#define __Mullw_0(src1, src2)       __mullw_0(src1, src2)
#define __Mullw_f_0(src1, src2)     __mullw_f_0(src1, src2)
#define __Mulhlw(src1, src2)        __mulhlw(src1, src2)
#define __Mulhlw_f(src1, src2)      __mulhlw_f(src1, src2)
#define __Mulhlw_0(src1, src2)      __mulhlw_0(src1, src2)
#define __Mulhlw_f_0(src1, src2)    __mulhlw_f_0(src1, src2)
#define __Maclw(src1, src2)         __maclw(src1, src2)
#define __Maclw_f(src1, src2)       __maclw_f(src1, src2)
#define __Maclw_0(src1, src2)       __maclw_0(src1, src2)
#define __Maclw_f_0(src1, src2)     __maclw_f_0(src1, src2)
#define __Machlw(src1, src2)        __machlw(src1, src2)
#define __Machlw_f(src1, src2)      __machlw_f(src1, src2)
#define __Machlw_0(src1, src2)      __machlw_0(src1, src2)
#define __Machlw_f_0(src1, src2)    __machlw_f_0(src1, src2)
#define __Machulw(src1, src2)       __machulw(src1, src2)
#define __Machulw_f(src1, src2)     __machulw_f(src1, src2)
#define __Machulw_0(src1, src2)     __machulw_0(src1, src2)
#define __Machulw_f_0(src1, src2)   __machulw_f_0(src1, src2)
#define __Muldw(src1, src2)         __muldw(src1, src2)
#define __Muldw_0(src1, src2)       __muldw_0(src1, src2)
#define __Mulrdw(src1, src2)        __mulrdw(src1, src2)
#define __Macdw(src1, src2)         __macdw(src1, src2)
#define __Macdw_0(src1, src2)       __macdw_0(src1, src2)
#define __Msubdw_0(src1, src2)      __msubdw_0(src1, src2)

#define __Get_ACC1()                __get_ACC1()
#define __Get_ACC2()                __get_ACC2()

//AndreyM
#define __Get_xbase()               __get_xbase()
#define __Get_ybase()               __get_ybase()

/* AndreiMi */
#define __Get_ACC1_H()              __get_ACC1_H()
#define __Get_ACC2_H()              __get_ACC2_H()

#define __Get_AAh()                 __get_AAh()
#define __Get_AAl()                 __get_AAl()

/* Simeon */
#define __get_AUX_XMAC0_24()          __get_AUX_XMAC0_24()
#define __get_AUX_XMAC1_24()          __get_AUX_XMAC1_24()
#define __get_AUX_XMAC2_24()          __get_AUX_XMAC2_24()

int32_t saturate32(int64_t L_var1);

void set_MACMODE(uint32_t mode);
uint32_t get_MACMODE(void);

void sat_aa(int bits);
void sr_aa1(int32_t aa);
void sr_xmac1(int32_t src);
int32_t lr_xmac1();

#endif

///////////////////////////////////////////////////////////////////////////////
// XY-memory simulation
//
// Use the following global variables in debugger to see xy-memory parameters:
//
//-----------------------------------------------------------------------------
// XMEM, YMEM
// XY-Memory data buffers for x bank and y bank respectively
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// AX0..AX3, AY0..AY3
// Address (offset) registers
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// MX00,MX01..MX30,MX31, MY00,MY01..MY30,MY31
// Modifiers for the respective address registers
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// MODX00,MODX01..MODX30,MODX31, MODY00,MODY01..MODY30,MODY31
// Modulo extracted from the respective modifier
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// INCX00,INCX01..INCX30,INCX31, INCY00,INCY01..INCY30,INCY31
// Increment extracted from the respective modifier
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// ADDR16X0..ADDR16X3, ADDR16Y0..ADDR16Y3
// Indicates 16-bit addressing mode (=1)
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
// DUAL16X0..DUAL16X3, DUAL16Y0..DUAL16Y3
// Indicates dual mode (=1) when 16-bit addressing mode is on
//-----------------------------------------------------------------------------
//
///////////////////////////////////////////////////////////////////////////////
#define XYMEM_MAX_OFFSET8       (8192)
#define XYMEM_MAX_OFFSET16      (XYMEM_MAX_OFFSET8/2)
#define XYMEM_MAX_OFFSET32      (XYMEM_MAX_OFFSET16/2)

#define XYMEM_XY_NUM            (2)
#define XYMEM_XY_SIZE           (XYMEM_MAX_OFFSET32)
#define XYMEM_ADDR_NUM          (4)
#define XYMEM_MOD_NUM           (2)

#ifdef _MSC_VER

typedef int32_t XYBank[XYMEM_XY_SIZE];

#ifdef __cplusplus
extern int32_t& AX0;
extern int32_t& AX1;
extern int32_t& AX2;
extern int32_t& AX3;

extern int32_t& AY0;
extern int32_t& AY1;
extern int32_t& AY2;
extern int32_t& AY3;

#ifdef SAVE_PREV_XYADDR
extern int32_t& AX0_PREV;
extern int32_t& AX1_PREV;
extern int32_t& AX2_PREV;
extern int32_t& AX3_PREV;

extern int32_t& AY0_PREV;
extern int32_t& AY1_PREV;
extern int32_t& AY2_PREV;
extern int32_t& AY3_PREV;
#endif

extern uint32_t& MX00;
extern uint32_t& MX01;
extern uint32_t& MX10;
extern uint32_t& MX11;
extern uint32_t& MX20;
extern uint32_t& MX21;
extern uint32_t& MX30;
extern uint32_t& MX31;

extern uint32_t& MY00;
extern uint32_t& MY01;
extern uint32_t& MY10;
extern uint32_t& MY11;
extern uint32_t& MY20;
extern uint32_t& MY21;
extern uint32_t& MY30;
extern uint32_t& MY31;

extern XYBank& pXMEM;
extern XYBank& pYMEM;

extern uint32_t& MODX00;
extern uint32_t& MODX01;
extern uint32_t& MODX10;
extern uint32_t& MODX11;
extern uint32_t& MODX20;
extern uint32_t& MODX21;
extern uint32_t& MODX30;
extern uint32_t& MODX31;

extern uint32_t& MODY00;
extern uint32_t& MODY01;
extern uint32_t& MODY10;
extern uint32_t& MODY11;
extern uint32_t& MODY20;
extern uint32_t& MODY21;
extern uint32_t& MODY30;
extern uint32_t& MODY31;

extern int32_t& INCX00;
extern int32_t& INCX01;
extern int32_t& INCX10;
extern int32_t& INCX11;
extern int32_t& INCX20;
extern int32_t& INCX21;
extern int32_t& INCX30;
extern int32_t& INCX31;

extern int32_t& INCY00;
extern int32_t& INCY01;
extern int32_t& INCY10;
extern int32_t& INCY11;
extern int32_t& INCY20;
extern int32_t& INCY21;
extern int32_t& INCY30;
extern int32_t& INCY31;

extern int& ADDR16X0;
extern int& ADDR16X1;
extern int& ADDR16X2;
extern int& ADDR16X3;

extern int& ADDR16Y0;
extern int& ADDR16Y1;
extern int& ADDR16Y2;
extern int& ADDR16Y3;

extern int& DUALY0;
extern int& DUALY1;
extern int& DUALY2;
extern int& DUALY3;

extern int& DUALX0;
extern int& DUALX1;
extern int& DUALX2;
extern int& DUALX3;
#endif // #ifdef __cplusplus

#define DECLARE_XYMEM_ACCESSOR_X(I)   \
uint32_t __ax##I##();                 \
void __set_ax##I(unsigned n);         \
uint32_t __mx##I##0();                \
uint32_t __mx##I##1();                \
void __set_mx##I##0(uint32_t m);      \
void __set_mx##I##1(uint32_t m);      \
int32_t __x##I##_u0();                \
int32xy_t __xy##I##_u0();             \
int32_t __x##I##_u1();                \
int32xy_t __xy##I##_u1();             \
int32_t __x##I##_nu();                \
int32xy_t __xy##I##_nu();             \
void __set_x##I##_u0(int32_t a);      \
void __set_xy##I##_u0(int32xy_t a);   \
void __set_x##I##_u1(int32_t a);      \
void __set_xy##I##_u1(int32xy_t a);   \
void __set_x##I##_nu(int32_t a);      \
void __set_xy##I##_nu(int32xy_t a);

#define DECLARE_XYMEM_ACCESSOR_Y(I)   \
uint32_t __ay##I##();                 \
void __set_ay##I(unsigned n);         \
uint32_t __my##I##0();                \
uint32_t __my##I##1();                \
void __set_my##I##0(uint32_t m);      \
void __set_my##I##1(uint32_t m);      \
int32_t __y##I##_u0();                \
int32xy_t __yx##I##_u0();             \
int32_t __y##I##_u1();                \
int32xy_t __yx##I##_u1();             \
int32_t __y##I##_nu();                \
int32xy_t __yx##I##_nu();             \
void __set_y##I##_u0(int32_t a);      \
void __set_yx##I##_u0(int32xy_t a);   \
void __set_y##I##_u1(int32_t a);      \
void __set_yx##I##_u1(int32xy_t a);   \
void __set_y##I##_nu(int32_t a);      \
void __set_yx##I##_nu(int32xy_t a);

DECLARE_XYMEM_ACCESSOR_X(0)
DECLARE_XYMEM_ACCESSOR_X(1)
DECLARE_XYMEM_ACCESSOR_X(2)
DECLARE_XYMEM_ACCESSOR_X(3)
DECLARE_XYMEM_ACCESSOR_Y(0)
DECLARE_XYMEM_ACCESSOR_Y(1)
DECLARE_XYMEM_ACCESSOR_Y(2)
DECLARE_XYMEM_ACCESSOR_Y(3)

#define __Ax0()     __ax0()
#define __Ax1()     __ax1()
#define __Ax2()     __ax2()
#define __Ax3()     __ax3()

#define __Ay0()     __ay0()
#define __Ay1()     __ay1()
#define __Ay2()     __ay2()
#define __Ay3()     __ay3()

#define __Set_ax0(a)        __set_ax0(a)
#define __Set_ax1(a)        __set_ax1(a)
#define __Set_ax2(a)        __set_ax2(a)
#define __Set_ax3(a)        __set_ax3(a)

#define __Set_ay0(a)        __set_ay0(a)
#define __Set_ay1(a)        __set_ay1(a)
#define __Set_ay2(a)        __set_ay2(a)
#define __Set_ay3(a)        __set_ay3(a)

#define __Mx00()    __mx00()
#define __Mx01()    __mx01()
#define __Mx10()    __mx10()
#define __Mx11()    __mx11()
#define __Mx20()    __mx20()
#define __Mx21()    __mx21()
#define __Mx30()    __mx30()
#define __Mx31()    __mx31()

#define __My00()    __my00()
#define __My01()    __my01()
#define __My10()    __my10()
#define __My11()    __my11()
#define __My20()    __my20()
#define __My21()    __my21()
#define __My30()    __my30()
#define __My31()    __my31()

#define __Set_mx00(a)    __set_mx00(a)
#define __Set_mx01(a)    __set_mx01(a)
#define __Set_mx10(a)    __set_mx10(a)
#define __Set_mx11(a)    __set_mx11(a)
#define __Set_mx20(a)    __set_mx20(a)
#define __Set_mx21(a)    __set_mx21(a)
#define __Set_mx30(a)    __set_mx30(a)
#define __Set_mx31(a)    __set_mx31(a)

#define __Set_my00(a)    __set_my00(a)
#define __Set_my01(a)    __set_my01(a)
#define __Set_my10(a)    __set_my10(a)
#define __Set_my11(a)    __set_my11(a)
#define __Set_my20(a)    __set_my20(a)
#define __Set_my21(a)    __set_my21(a)
#define __Set_my30(a)    __set_my30(a)
#define __Set_my31(a)    __set_my31(a)

#define __X0_u0()       __x0_u0()
#define __X0_u1()       __x0_u1()
#define __X0_nu()       __x0_nu()
#define __X1_u0()       __x1_u0()
#define __X1_u1()       __x1_u1()
#define __X1_nu()       __x1_nu()
#define __X2_u0()       __x2_u0()
#define __X2_u1()       __x2_u1()
#define __X2_nu()       __x2_nu()
#define __X3_u0()       __x3_u0()
#define __X3_u1()       __x3_u1()
#define __X3_nu()       __x3_nu()
#define __Y0_u0()       __y0_u0()
#define __Y0_u1()       __y0_u1()
#define __Y0_nu()       __y0_nu()
#define __Y1_u0()       __y1_u0()
#define __Y1_u1()       __y1_u1()
#define __Y1_nu()       __y1_nu()
#define __Y2_u0()       __y2_u0()
#define __Y2_u1()       __y2_u1()
#define __Y2_nu()       __y2_nu()
#define __Y3_u0()       __y3_u0()
#define __Y3_u1()       __y3_u1()
#define __Y3_nu()       __y3_nu()

#define __Xy0_u0()      __xy0_u0()
#define __Xy0_u1()      __xy0_u1()
#define __Xy0_nu()      __xy0_nu()
#define __Xy1_u0()      __xy1_u0()
#define __Xy1_u1()      __xy1_u1()
#define __Xy1_nu()      __xy1_nu()
#define __Xy2_u0()      __xy2_u0()
#define __Xy2_u1()      __xy2_u1()
#define __Xy2_nu()      __xy2_nu()
#define __Xy3_u0()      __xy3_u0()
#define __Xy3_u1()      __xy3_u1()
#define __Xy3_nu()      __xy3_nu()
#define __Yx0_u0()      __yx0_u0()
#define __Yx0_u1()      __yx0_u1()
#define __Yx0_nu()      __yx0_nu()
#define __Yx1_u0()      __yx1_u0()
#define __Yx1_u1()      __yx1_u1()
#define __Yx1_nu()      __yx1_nu()
#define __Yx2_u0()      __yx2_u0()
#define __Yx2_u1()      __yx2_u1()
#define __Yx2_nu()      __yx2_nu()
#define __Yx3_u0()      __yx3_u0()
#define __Yx3_u1()      __yx3_u1()
#define __Yx3_nu()      __yx3_nu()

#define __Set_x0_u0(x)  __set_x0_u0(x)
#define __Set_x0_u1(x)  __set_x0_u1(x)
#define __Set_x0_nu(x)  __set_x0_nu(x)
#define __Set_x1_u0(x)  __set_x1_u0(x)
#define __Set_x1_u1(x)  __set_x1_u1(x)
#define __Set_x1_nu(x)  __set_x1_nu(x)
#define __Set_x2_u0(x)  __set_x2_u0(x)
#define __Set_x2_u1(x)  __set_x2_u1(x)
#define __Set_x2_nu(x)  __set_x2_nu(x)
#define __Set_x3_u0(x)  __set_x3_u0(x)
#define __Set_x3_u1(x)  __set_x3_u1(x)
#define __Set_x3_nu(x)  __set_x3_nu(x)

#define __Set_y0_u0(x)  __set_y0_u0(x)
#define __Set_y0_u1(x)  __set_y0_u1(x)
#define __Set_y0_nu(x)  __set_y0_nu(x)
#define __Set_y1_u0(x)  __set_y1_u0(x)
#define __Set_y1_u1(x)  __set_y1_u1(x)
#define __Set_y1_nu(x)  __set_y1_nu(x)
#define __Set_y2_u0(x)  __set_y2_u0(x)
#define __Set_y2_u1(x)  __set_y2_u1(x)
#define __Set_y2_nu(x)  __set_y2_nu(x)
#define __Set_y3_u0(x)  __set_y3_u0(x)
#define __Set_y3_u1(x)  __set_y3_u1(x)
#define __Set_y3_nu(x)  __set_y3_nu(x)

#define __Set_xy0_u0(x) __set_xy0_u0(x)
#define __Set_xy0_u1(x) __set_xy0_u1(x)
#define __Set_xy0_nu(x) __set_xy0_nu(x)
#define __Set_xy1_u0(x) __set_xy1_u0(x)
#define __Set_xy1_u1(x) __set_xy1_u1(x)
#define __Set_xy1_nu(x) __set_xy1_nu(x)
#define __Set_xy2_u0(x) __set_xy2_u0(x)
#define __Set_xy2_u1(x) __set_xy2_u1(x)
#define __Set_xy2_nu(x) __set_xy2_nu(x)
#define __Set_xy3_u0(x) __set_xy3_u0(x)
#define __Set_xy3_u1(x) __set_xy3_u1(x)
#define __Set_xy3_nu(x) __set_xy3_nu(x)

#define __Set_yx0_u0(x) __set_yx0_u0(x)
#define __Set_yx0_u1(x) __set_yx0_u1(x)
#define __Set_yx0_nu(x) __set_yx0_nu(x)
#define __Set_yx1_u0(x) __set_yx1_u0(x)
#define __Set_yx1_u1(x) __set_yx1_u1(x)
#define __Set_yx1_nu(x) __set_yx1_nu(x)
#define __Set_yx2_u0(x) __set_yx2_u0(x)
#define __Set_yx2_u1(x) __set_yx2_u1(x)
#define __Set_yx2_nu(x) __set_yx2_nu(x)
#define __Set_yx3_u0(x) __set_yx3_u0(x)
#define __Set_yx3_u1(x) __set_yx3_u1(x)
#define __Set_yx3_nu(x) __set_yx3_nu(x)

// Aux variables to store/restore all general purpose registers
void push_all_regs();
void pop_all_regs();

// Getting and setting timer value
timer_t _GetTimer();
void _SetTimer(timer_t t);

// System and XY memory bursting/copying routines
/* AndreiMi */
void _CopyXMemToXMem(uint32_t dest, uint32_t src, int n);
void _CopyYMemToXMem(uint32_t dest, uint32_t src, int n);
void _CopyXMemToYMem(uint32_t dest, uint32_t src, int n);
void _CopyYMemToYMem(uint32_t dest, uint32_t src, int n);

void _SetXMem(uint32_t dest, int32_t val, int n);
void _SetYMem(uint32_t dest, int32_t val, int n);
void _BurstXMem(uint32_t dest, int32_t val, int n);
void _BurstYMem(uint32_t dest, int32_t val, int n);
void _SetSMem(pint32_t dest, int32_t val, int n);
void _BurstSMem(pint32_t dest, int32_t val, int n);
void _CopyXMemToSMem24(pint32_t dest, uint32_t src, int n);
void _CopyYMemToSMem24(pint32_t dest, uint32_t src, int n);
void _CopySMemToXMem24(uint32_t dest, const pint32_t src, int n);
void _CopySMemToYMem24(uint32_t dest, const pint32_t src, int n);
void _CopySMemToXMem16(uint32_t dest, const pint16_t src, int n);
void _CopySMemToYMem16(uint32_t dest, const pint16_t src, int n);
void _CopySMemToXMem32(uint32_t dest, const pint32_t src, int n);
void _CopySMemToYMem32(uint32_t dest, const pint32_t src, int n);
void _CopySMemToXMem16_CacheBypass(uint32_t dest, const pint16_t src, int n);
void _CopySMemToYMem16_CacheBypass(uint32_t dest, const pint16_t src, int n);
void _CopySMemToXMem32_CacheBypass(uint32_t dest, const pint32_t src, int n);
void _CopySMemToYMem32_CacheBypass(uint32_t dest, const pint32_t src, int n);
void _PackYMemToSMem(pint32_t dest, const uint32_t src, int n);
void _PackXMemToSMem(pint32_t dest, uint32_t src, int n);
void _UnpackSMemToYMem(uint32_t dest, const pint32_t src, int n);
void _UnpackSMemToXMem(uint32_t dest, const pint32_t src, int n);
void _BurstSMemToXMem(uint32_t dest, const pint32_t src, int n);
void _BurstSMemToXMem_nowait(uint32_t dest, const pint32_t src, int n);
void _BurstSMemToYMem(uint32_t dest, const pint32_t src, int n);
void _BurstSMemToYMem_nowait(uint32_t dest, const pint32_t src, int n);
void _BurstSMemToAny_nowait(uint32_t dest, const pint32_t src, int formatted_n); /* AlexanderP: added BurstSMemToAny */
void _CopyXMemToSMem16(pint16_t dest, uint32_t src, int n);
void _CopyYMemToSMem16(pint16_t dest, uint32_t src, int n);
void _CopyXMemToSMem32(pint32_t dest, uint32_t src, int n);
void _CopyYMemToSMem32(pint32_t dest, uint32_t src, int n);
void _CopyXMemToSMem16_CacheBypass(pint16_t dest, uint32_t src, int n);
void _CopyYMemToSMem16_CacheBypass(pint16_t dest, uint32_t src, int n);
void _CopyXMemToSMem32_CacheBypass(pint32_t dest, uint32_t src, int n);
void _CopyYMemToSMem32_CacheBypass(pint32_t dest, uint32_t src, int n);
void _BurstXMemToSMem(pint32_t dest, const unsigned src, int n);
void _BurstXMemToSMem_nowait(pint32_t dest, const unsigned src, int n);
void _BurstYMemToSMem(pint32_t dest, const unsigned src, int n);
void _BurstYMemToSMem_nowait(pint32_t dest, const unsigned src, int n);
void _WaitTillBurstComplete();

void ResetBurstBandWidth(void); /* BurstBandWidth management added by Simeon */
int  GetBurstBandWidth(void);   /* ... */

extern XYBank* XMEM;
extern XYBank* YMEM;

// Entire d-cache invalidating
void InvalidateDCache();
void InvalidateDCacheChunk(void* addr, int size);
void FlushDCache();
void FlushDCacheChunk(void* addr, int size);
void LockDCacheChunk(void* addr, int size);

#else   // ARC600 architecture

///////////////////////////////////////////////////////////////////////////////
// ARC600 branch
///////////////////////////////////////////////////////////////////////////////

#define XMEM _lr(REG_XYLSBASEX)
#define YMEM _lr(REG_XYLSBASEY)

//
// Condition codes checking
//
#define _condition_z        _condition(0x01) // Zero _Z
#define _condition_nz       _condition(0x02) // Non-Zero
#define _condition_p        _condition(0x03) // Positive
#define _condition_n        _condition(0x04) // Negative
#define _condition_c        _condition(0x05) // Carry set, lower than (unsigned)
#define _condition_cc       _condition(0x06) // Carry clear, higher or same (unsigned)
#define _condition_v        _condition(0x07) // Over-flow set
#define _condition_nv       _condition(0x08) // Over-flow clear
#define _condition_gt       _condition(0x09) // Greater than (signed) (_N and _V and /_Z) or (/_N and /_V and /_Z)
#define _condition_ge       _condition(0x0A) // Greater than or equal to (signed) (_N and _V) or (/_N and /_V)
#define _condition_lt       _condition(0x0B) // Less than (signed) (_N and /_V) or (/_N and _V)
#define _condition_le       _condition(0x0C) // Less than or equal to (signed) _Z or (_N and /_V) or (/_N and _V)
#define _condition_hi       _condition(0x0D) // Higher than (unsigned) /_C and /_Z
#define _condition_ls       _condition(0x0E) // Lower than or same (unsigned) _C or _Z
#define _condition_pnz      _condition(0x0F) // Positive non-zero /_N and /_Z

//
// Instruction set in intrinsics
//

#define  __nop() _nop() // _nop() is built-in intrinsic

// fix warnings in MWDT 8.5.0
#if !defined AX0

#define AX0 0x80
#define AX1 0x81
#define AX2 0x82
#define AX3 0x83
#define AY0 0x84
#define AY1 0x85
#define AY2 0x86
#define AY3 0x87

#define MX00 0x88
#define MX01 0x89
#define MX10 0x8a
#define MX11 0x8b
#define MX20 0x8c
#define MX21 0x8d
#define MX30 0x8e
#define MX31 0x8f
#define MY00 0x90
#define MY01 0x91
#define MY10 0x92
#define MY11 0x93
#define MY20 0x94
#define MY21 0x95
#define MY30 0x96
#define MY31 0x97

#define AUX_CRC_POLY 0x32
#define AUX_CRC_MODE 0x33
#define AUX_MACMODE  0x41
#endif

#ifndef ARC600_NO_INTRINSICS

#define __aux_crc_poly()    _lr(AUX_CRC_POLY)
#define __aux_crc_mode()    _lr(AUX_CRC_MODE)

#define __set_aux_crc_poly(x)    _sr(x, AUX_CRC_POLY)
#define __set_aux_crc_mode(x)    _sr(x, AUX_CRC_MODE)

#pragma aux_register(AUX_CRC_POLY, name => "aux_crc_poly"/*, side_effects => "rw"*/)
#pragma aux_register(AUX_CRC_MODE, name => "aux_crc_mode"/*, side_effects => "rw"*/)

#define LP_COUNT_REG 60
#pragma core_register(LP_COUNT_REG, side_effects => "rw")
#define _lp_count()      _core_read(LP_COUNT_REG)
#define _set_lp_count(x) _core_write(x, LP_COUNT_REG)

#define __ax0()    _lr(AX0)
#define __ax1()    _lr(AX1)
#define __ax2()    _lr(AX2)
#define __ax3()    _lr(AX3)
#define __ay0()    _lr(AY0)
#define __ay1()    _lr(AY1)
#define __ay2()    _lr(AY2)
#define __ay3()    _lr(AY3)

#define __set_ax0(a)       _sr(a, AX0)
#define __set_ax1(a)       _sr(a, AX1)
#define __set_ax2(a)       _sr(a, AX2)
#define __set_ax3(a)       _sr(a, AX3)
#define __set_ay0(a)       _sr(a, AY0)
#define __set_ay1(a)       _sr(a, AY1)
#define __set_ay2(a)       _sr(a, AY2)
#define __set_ay3(a)       _sr(a, AY3)

#define __mx00()   _lr(MX00)
#define __mx01()   _lr(MX01)
#define __mx10()   _lr(MX10)
#define __mx11()   _lr(MX11)
#define __mx20()   _lr(MX20)
#define __mx21()   _lr(MX21)
#define __mx30()   _lr(MX30)
#define __mx31()   _lr(MX31)
#define __my00()   _lr(MY00)
#define __my01()   _lr(MY01)
#define __my10()   _lr(MY10)
#define __my11()   _lr(MY11)
#define __my20()   _lr(MY20)
#define __my21()   _lr(MY21)
#define __my30()   _lr(MY30)
#define __my31()   _lr(MY31)

#define __set_mx00(m)   _sr(m, MX00)
#define __set_mx01(m)   _sr(m, MX01)
#define __set_mx10(m)   _sr(m, MX10)
#define __set_mx11(m)   _sr(m, MX11)
#define __set_mx20(m)   _sr(m, MX20)
#define __set_mx21(m)   _sr(m, MX21)
#define __set_mx30(m)   _sr(m, MX30)
#define __set_mx31(m)   _sr(m, MX31)
#define __set_my00(m)   _sr(m, MY00)
#define __set_my01(m)   _sr(m, MY01)
#define __set_my10(m)   _sr(m, MY10)
#define __set_my11(m)   _sr(m, MY11)
#define __set_my20(m)   _sr(m, MY20)
#define __set_my21(m)   _sr(m, MY21)
#define __set_my30(m)   _sr(m, MY30)
#define __set_my31(m)   _sr(m, MY31)

#define X0_u0   32  // X0 with update 0
#define X0_u1   33  // X0 with update 1
#define X0_nu   48  // X0 without update
#define X1_u0   34  // X1 with update 0
#define X1_u1   35  // X1 with update 1
#define X1_nu   49  // X1 without update
#define X2_u0   36  // X2 with update 0
#define X2_u1   37  // X2 with update 1
#define X2_nu   50  // X2 without update
#define X3_u0   38  // X3 with update 0
#define X3_u1   39  // X3 with update 1
#define X3_nu   51  // X3 without update

#define Y0_u0   40  // Y0 with update 0
#define Y0_u1   41  // Y0 with update 1
#define Y0_nu   52  // Y0 without update
#define Y1_u0   42  // Y1 with update 0
#define Y1_u1   43  // Y1 with update 1
#define Y1_nu   53  // Y1 without update
#define Y2_u0   44  // Y2 with update 0
#define Y2_u1   45  // Y2 with update 1
#define Y2_nu   54  // Y2 without update
#define Y3_u0   46  // Y3 with update 0
#define Y3_u1   47  // Y3 with update 1
#define Y3_nu   55  // Y3 without update

#pragma core_register(X0_u0, side_effects => "rw")
#pragma core_register(X0_u1, side_effects => "rw")
#pragma core_register(X1_u0, side_effects => "rw")
#pragma core_register(X1_u1, side_effects => "rw")
#pragma core_register(X2_u0, side_effects => "rw")
#pragma core_register(X2_u1, side_effects => "rw")
#pragma core_register(X3_u0, side_effects => "rw")
#pragma core_register(X3_u1, side_effects => "rw")

#pragma core_register(Y0_u0, side_effects => "rw")
#pragma core_register(Y0_u1, side_effects => "rw")
#pragma core_register(Y1_u0, side_effects => "rw")
#pragma core_register(Y1_u1, side_effects => "rw")
#pragma core_register(Y2_u0, side_effects => "rw")
#pragma core_register(Y2_u1, side_effects => "rw")
#pragma core_register(Y3_u0, side_effects => "rw")
#pragma core_register(Y3_u1, side_effects => "rw")

#define ACC1    56
#define ACC2    57
#define ACC1_H  58      /* AndreiMi */
#define ACC2_H  59      /* AndreiMi */

#define AUX_XMACLW_H    0x9F    // r/w 32 32x16 accumulator (high)
#define AUX_XMACLW_L    0xA0    // r/w 32 32x16 accumulator (low)

/* Simeon */
// fix warnings in MWDT 8.5.0
#if !defined AUX_XMAC0_24
#define AUX_XMAC0_24    0x2C    // r/w 32 24x24 accumulator guard register
#define AUX_XMAC1_24    0x2D    // r/w 32 24x24 accumulator MSP
#define AUX_XMAC2_24    0x2E    // r/w 32 24x24 accumulator LSP
#endif

#pragma aux_register(AUX_XMAC0_24, name => "aux_xmac0_24"/*, effects => "%r56:is_written", side_effects => "w"*/)
#pragma aux_register(AUX_XMAC1_24, name => "aux_xmac1_24"/*, effects => "%r56:is_written", side_effects => "w"*/)
#pragma aux_register(AUX_XMAC2_24, name => "aux_xmac2_24"/*, effects => "%r56:is_written", side_effects => "w"*/)

#pragma aux_register(AUX_XMACLW_H, name => "aux_xmaclw_h", effects => "%r56:is_written", side_effects => "w")
#pragma aux_register(AUX_XMACLW_L, name => "aux_xmaclw_l", effects => "%r57:is_written", side_effects => "w")

#define __x0_u0()   _core_read(X0_u0)
#define __x0_u1()   _core_read(X0_u1)
#define __x0_nu()   _core_read(X0_nu)
#define __x1_u0()   _core_read(X1_u0)
#define __x1_u1()   _core_read(X1_u1)
#define __x1_nu()   _core_read(X1_nu)
#define __x2_u0()   _core_read(X2_u0)
#define __x2_u1()   _core_read(X2_u1)
#define __x2_nu()   _core_read(X2_nu)
#define __x3_u0()   _core_read(X3_u0)
#define __x3_u1()   _core_read(X3_u1)
#define __x3_nu()   _core_read(X3_nu)
#define __y0_u0()   _core_read(Y0_u0)
#define __y0_u1()   _core_read(Y0_u1)
#define __y0_nu()   _core_read(Y0_nu)
#define __y1_u0()   _core_read(Y1_u0)
#define __y1_u1()   _core_read(Y1_u1)
#define __y1_nu()   _core_read(Y1_nu)
#define __y2_u0()   _core_read(Y2_u0)
#define __y2_u1()   _core_read(Y2_u1)
#define __y2_nu()   _core_read(Y2_nu)
#define __y3_u0()   _core_read(Y3_u0)
#define __y3_u1()   _core_read(Y3_u1)
#define __y3_nu()   _core_read(Y3_nu)

#define __xy0_u0()  __x0_u0()
#define __xy0_u1()  __x0_u1()
#define __xy0_nu()  __x0_nu()
#define __xy1_u0()  __x1_u0()
#define __xy1_u1()  __x1_u1()
#define __xy1_nu()  __x1_nu()
#define __xy2_u0()  __x2_u0()
#define __xy2_u1()  __x2_u1()
#define __xy2_nu()  __x2_nu()
#define __xy3_u0()  __x3_u0()
#define __xy3_u1()  __x3_u1()
#define __xy3_nu()  __x3_nu()
#define __yx0_u0()  __y0_u0()
#define __yx0_u1()  __y0_u1()
#define __yx0_nu()  __y0_nu()
#define __yx1_u0()  __y1_u0()
#define __yx1_u1()  __y1_u1()
#define __yx1_nu()  __y1_nu()
#define __yx2_u0()  __y2_u0()
#define __yx2_u1()  __y2_u1()
#define __yx2_nu()  __y2_nu()
#define __yx3_u0()  __y3_u0()
#define __yx3_u1()  __y3_u1()
#define __yx3_nu()  __y3_nu()

#define __set_x0_u0(x)  _core_write(x, X0_u0)
#define __set_x0_u1(x)  _core_write(x, X0_u1)
#define __set_x0_nu(x)  _core_write(x, X0_nu)
#define __set_x1_u0(x)  _core_write(x, X1_u0)
#define __set_x1_u1(x)  _core_write(x, X1_u1)
#define __set_x1_nu(x)  _core_write(x, X1_nu)
#define __set_x2_u0(x)  _core_write(x, X2_u0)
#define __set_x2_u1(x)  _core_write(x, X2_u1)
#define __set_x2_nu(x)  _core_write(x, X2_nu)
#define __set_x3_u0(x)  _core_write(x, X3_u0)
#define __set_x3_u1(x)  _core_write(x, X3_u1)
#define __set_x3_nu(x)  _core_write(x, X3_nu)

#define __set_y0_u0(x)  _core_write(x, Y0_u0)
#define __set_y0_u1(x)  _core_write(x, Y0_u1)
#define __set_y0_nu(x)  _core_write(x, Y0_nu)
#define __set_y1_u0(x)  _core_write(x, Y1_u0)
#define __set_y1_u1(x)  _core_write(x, Y1_u1)
#define __set_y1_nu(x)  _core_write(x, Y1_nu)
#define __set_y2_u0(x)  _core_write(x, Y2_u0)
#define __set_y2_u1(x)  _core_write(x, Y2_u1)
#define __set_y2_nu(x)  _core_write(x, Y2_nu)
#define __set_y3_u0(x)  _core_write(x, Y3_u0)
#define __set_y3_u1(x)  _core_write(x, Y3_u1)
#define __set_y3_nu(x)  _core_write(x, Y3_nu)

#define __set_xy0_u0(x) __set_x0_u0(x)
#define __set_xy0_u1(x) __set_x0_u1(x)
#define __set_xy0_nu(x) __set_x0_nu(x)
#define __set_xy1_u0(x) __set_x1_u0(x)
#define __set_xy1_u1(x) __set_x1_u1(x)
#define __set_xy1_nu(x) __set_x1_nu(x)
#define __set_xy2_u0(x) __set_x2_u0(x)
#define __set_xy2_u1(x) __set_x2_u1(x)
#define __set_xy2_nu(x) __set_x2_nu(x)
#define __set_xy3_u0(x) __set_x3_u0(x)
#define __set_xy3_u1(x) __set_x3_u1(x)
#define __set_xy3_nu(x) __set_x3_nu(x)

#define __set_yx0_u0(x) __set_y0_u0(x)
#define __set_yx0_u1(x) __set_y0_u1(x)
#define __set_yx0_nu(x) __set_y0_nu(x)
#define __set_yx1_u0(x) __set_y1_u0(x)
#define __set_yx1_u1(x) __set_y1_u1(x)
#define __set_yx1_nu(x) __set_y1_nu(x)
#define __set_yx2_u0(x) __set_y2_u0(x)
#define __set_yx2_u1(x) __set_y2_u1(x)
#define __set_yx2_nu(x) __set_y2_nu(x)
#define __set_yx3_u0(x) __set_y3_u0(x)
#define __set_yx3_u1(x) __set_y3_u1(x)
#define __set_yx3_nu(x) __set_y3_nu(x)

#define __get_ACC1() _core_read(ACC1)
#define __get_ACC2() _core_read(ACC2)
#define __get_ACC1_H() _core_read(ACC1_H)   /* AndreiMi */
#define __get_ACC2_H() _core_read(ACC2_H)   /* AndreiMi */
#define XYLSBASEX_REGISTER          0x9D
#define XYLSBASEY_REGISTER          0x9E
#define __get_xbase()             _lr(XYLSBASEX_REGISTER)
#define __get_ybase()             _lr(XYLSBASEY_REGISTER)
#define __get_AAh() _lr(AUX_XMACLW_H)
#define __get_AAl() _lr(AUX_XMACLW_L)

/* Simeon */
#define __get_AUX_XMAC0_24() _lr(AUX_XMAC0_24)
#define __get_AUX_XMAC1_24() _lr(AUX_XMAC1_24)
#define __get_AUX_XMAC2_24() _lr(AUX_XMAC2_24)

#define __x0_u0()   _core_read(X0_u0)
#define __x0_u1()   _core_read(X0_u1)
#define __x0_nu()   _core_read(X0_nu)
#define __x1_u0()   _core_read(X1_u0)
#define __x1_u1()   _core_read(X1_u1)
#define __x1_nu()   _core_read(X1_nu)
#define __x2_u0()   _core_read(X2_u0)
#define __x2_u1()   _core_read(X2_u1)
#define __x2_nu()   _core_read(X2_nu)
#define __x3_u0()   _core_read(X3_u0)
#define __x3_u1()   _core_read(X3_u1)
#define __x3_nu()   _core_read(X3_nu)
#define __y0_u0()   _core_read(Y0_u0)
#define __y0_u1()   _core_read(Y0_u1)
#define __y0_nu()   _core_read(Y0_nu)
#define __y1_u0()   _core_read(Y1_u0)
#define __y1_u1()   _core_read(Y1_u1)
#define __y1_nu()   _core_read(Y1_nu)
#define __y2_u0()   _core_read(Y2_u0)
#define __y2_u1()   _core_read(Y2_u1)
#define __y2_nu()   _core_read(Y2_nu)
#define __y3_u0()   _core_read(Y3_u0)
#define __y3_u1()   _core_read(Y3_u1)
#define __y3_nu()   _core_read(Y3_nu)

#define __set_x0_u0(x)  _core_write(x, X0_u0)
#define __set_x0_u1(x)  _core_write(x, X0_u1)
#define __set_x1_nu(x)  _core_write(x, X1_nu)
#define __set_x1_u0(x)  _core_write(x, X1_u0)
#define __set_x1_u1(x)  _core_write(x, X1_u1)
#define __set_x2_nu(x)  _core_write(x, X2_nu)
#define __set_x2_u0(x)  _core_write(x, X2_u0)
#define __set_x2_u1(x)  _core_write(x, X2_u1)
#define __set_x3_nu(x)  _core_write(x, X3_nu)
#define __set_x3_u0(x)  _core_write(x, X3_u0)
#define __set_x3_u1(x)  _core_write(x, X3_u1)

#define __set_y0_u0(x)  _core_write(x, Y0_u0)
#define __set_y0_u1(x)  _core_write(x, Y0_u1)
#define __set_y0_nu(x)  _core_write(x, Y0_nu)
#define __set_y1_u0(x)  _core_write(x, Y1_u0)
#define __set_y2_nu(x)  _core_write(x, Y2_nu)
#define __set_y2_u0(x)  _core_write(x, Y2_u0)
#define __set_y2_u1(x)  _core_write(x, Y2_u1)
#define __set_y3_nu(x)  _core_write(x, Y3_nu)
#define __set_y3_u0(x)  _core_write(x, Y3_u0)
#define __set_y3_u1(x)  _core_write(x, Y3_u1)

/* Simeon */
extern void __nop();
#pragma intrinsic(__nop, opcode => 0x0F, sub_opcode => 0x00);

extern int32_t __lr(int32_t);
#pragma intrinsic(__lr, opcode => 0x04, sub_opcode => 0x2A);

extern int32_t __add(int32_t, int32_t);
#pragma intrinsic(__add, opcode => 0x04, sub_opcode => 0x00);

extern int32_t __add_f(int32_t, int32_t);
#pragma intrinsic(__add_f, opcode => 0x04, sub_opcode => 0x00, set_flags => 1, flags => "zcnv");

extern int32_t __sub(int32_t, int32_t);
#pragma intrinsic(__sub, opcode => 0x04, sub_opcode => 0x02);

extern int32_t __rsub(int32_t, int32_t);
#pragma intrinsic(__rsub, opcode => 0x04, sub_opcode => 0x0E);

extern int32_t __sub_f(int32_t, int32_t);
#pragma intrinsic(__sub_f, opcode => 0x04, sub_opcode => 0x02, set_flags => 1, flags => "zcnv");

extern int32_t __rsub_f(int32_t, int32_t);
#pragma intrinsic(__rsub_f, opcode => 0x04, sub_opcode => 0x0E, set_flags => 1, flags => "zcnv");

extern int32_t __add1(int32_t, int32_t);
#pragma intrinsic(__add1, opcode => 0x04, sub_opcode => 0x14);

extern int32_t __add1_f(int32_t, int32_t);
#pragma intrinsic(__add1_f, opcode => 0x04, sub_opcode => 0x14, set_flags => 1, flags => "zcnv");

extern int32_t __add2(int32_t, int32_t);
#pragma intrinsic(__add2, opcode => 0x04, sub_opcode => 0x15);

extern int32_t __add2_f(int32_t, int32_t);
#pragma intrinsic(__add2_f, opcode => 0x04, sub_opcode => 0x15, set_flags => 1, flags => "zcnv");

extern int32_t __add3(int32_t, int32_t);
#pragma intrinsic(__add3, opcode => 0x04, sub_opcode => 0x16);

extern int32_t __add3_f(int32_t, int32_t);
#pragma intrinsic(__add3_f, opcode => 0x04, sub_opcode => 0x16, set_flags => 1, flags => "zcnv");

extern int32_t __sub1(int32_t, int32_t);
#pragma intrinsic(__sub1, opcode => 0x04, sub_opcode => 0x17);

extern int32_t __sub1_f(int32_t, int32_t);
#pragma intrinsic(__sub1_f, opcode => 0x04, sub_opcode => 0x17, set_flags => 1, flags => "zcnv");

extern int32_t __sub2(int32_t, int32_t);
#pragma intrinsic(__sub2, opcode => 0x04, sub_opcode => 0x18);

extern int32_t __sub2_f(int32_t, int32_t);
#pragma intrinsic(__sub2_f, opcode => 0x04, sub_opcode => 0x18, set_flags => 1, flags => "zcnv");

extern int32_t __sub3(int32_t, int32_t);
#pragma intrinsic(__sub3, opcode => 0x04, sub_opcode => 0x19);

extern int32_t __sub3_f(int32_t, int32_t);
#pragma intrinsic(__sub3_f, opcode => 0x04, sub_opcode => 0x19, set_flags => 1, flags => "zcnv");

extern uint32_t __ror(uint32_t, int32_t);
#pragma intrinsic(__ror, opcode => 0x05, sub_opcode => 0x03);

extern uint32_t __ror_f(uint32_t, int32_t);
#pragma intrinsic(__ror_f, opcode => 0x05, sub_opcode => 0x03, set_flags => 1, flags => "zcn");

extern int32_t __rlc(int32_t);
#pragma intrinsic(__rlc, opcode => 0x04, sub_opcode => 0x0B);

extern int32_t __rlc_f(int32_t);
#pragma intrinsic(__rlc_f, opcode => 0x04, sub_opcode => 0x0B, set_flags => 1, flags => "zcn");

extern uint32_t __or(uint32_t, int32_t);
#pragma intrinsic(__or, opcode => 0x04, sub_opcode => 0x05);

extern uint32_t __or_f(uint32_t, int32_t);
#pragma intrinsic(__or_f, opcode => 0x04, sub_opcode => 0x05, set_flags => 1, flags => "zn");

extern int32_t __sat16(int32_t);
#pragma intrinsic(__sat16, opcode => 0x05, sub_opcode => 0x02);

extern int32_t __sat16_f(int32_t);
#pragma intrinsic(__sat16_f, opcode => 0x05, sub_opcode => 0x02, set_flags => 1, flags => "znv");

extern int32_t __rnd16(int32_t);
#pragma intrinsic(__rnd16, opcode => 0x05, sub_opcode => 0x03);

extern int32_t __rnd16_f(int32_t);
#pragma intrinsic(__rnd16_f, opcode => 0x05, sub_opcode => 0x03, set_flags => 1, flags => "znv");

extern uint32_t __swap(uint32_t);
#pragma intrinsic(__swap, opcode => 0x05, sub_opcode => 0x00);

extern uint32_t __swap_f(uint32_t);
#pragma intrinsic(__swap_f, opcode => 0x05, sub_opcode => 0x00, set_flags => 1, flags => "zn");

extern int32_t __bmsk(int32_t, int32_t);
#pragma intrinsic(__bmsk, opcode => 0x04, sub_opcode => 0x13);

extern int32_t __bmsk_f(int32_t, int32_t);
#pragma intrinsic(__bmsk_f, opcode => 0x04, sub_opcode => 0x13, set_flags => 1, flags => "zn");

extern int32_t __bset(int32_t, int32_t);
#pragma intrinsic(__bset, opcode => 0x04, sub_opcode => 0x0F);

extern int32_t __bset_f(int32_t, int32_t);
#pragma intrinsic(__bset_f, opcode => 0x04, sub_opcode => 0x0F, set_flags => 1, flags => "zn");

extern int32_t __btst(int32_t, int32_t);
#pragma intrinsic(__btst, opcode => 0x04, sub_opcode => 0x11, set_flags => 1, flags => "zn");

extern int32_t __bclr(int32_t, int32_t);
#pragma intrinsic(__bclr, opcode => 0x04, sub_opcode => 0x10);

extern int32_t __bclr_f(int32_t, int32_t);
#pragma intrinsic(__bclr_f, opcode => 0x04, sub_opcode => 0x10, set_flags => 1, flags => "zn");

extern int32_t __bxor(int32_t, int32_t);
#pragma intrinsic(__bxor, opcode => 0x04, sub_opcode => 0x12);

extern int32_t __bxor_f(int32_t, int32_t);
#pragma intrinsic(__bxor_f, opcode => 0x04, sub_opcode => 0x12, set_flags => 1, flags => "zn");

extern int32_t __asr(int32_t, int32_t);
#pragma intrinsic(__asr, opcode => 0x05, sub_opcode => 0x02);

extern int32_t __asr_f(int32_t, int32_t);
#pragma intrinsic(__asr_f, opcode => 0x05, sub_opcode => 0x02, set_flags => 1, flags => "zcn");

extern int32_t __mov(int32_t, int32_t);
#pragma intrinsic(__mov, opcode => 0x04, sub_opcode => 0x0A, assume_volatile => 1);

extern int32_t __mov_f(int32_t, int32_t);
#pragma intrinsic(__mov_f, opcode => 0x04, sub_opcode => 0x0A, set_flags => 1, flags => "zn", assume_volatile => 1);

extern int32_t __asl(int32_t, int32_t);
#pragma intrinsic(__asl, opcode => 0x05, sub_opcode => 0x00);

extern int32_t __asl_f(int32_t, int32_t);
#pragma intrinsic(__asl_f, opcode => 0x05, sub_opcode => 0x00, set_flags => 1, flags => "zcnv");

extern int32_t __lsr(int32_t, int32_t);
#pragma intrinsic(__lsr, opcode => 0x05, sub_opcode => 0x01);

extern int32_t __lsr_f(int32_t, int32_t);
#pragma intrinsic(__lsr_f, opcode => 0x05, sub_opcode => 0x01, set_flags => 1, flags => "zcn");

extern int32_t __asls(int32_t, int32_t);
#pragma intrinsic(__asls, opcode => 0x05, sub_opcode => 0x0A);

extern int32_t __asls_f(int32_t, int32_t);
#pragma intrinsic(__asls_f, opcode => 0x05, sub_opcode => 0x0A, set_flags => 1, flags => "znv");

extern int32_t __asrs(int32_t, int32_t);
#pragma intrinsic(__asrs, opcode => 0x05, sub_opcode => 0x0B);

extern int32_t __asrs_f(int32_t, int32_t);
#pragma intrinsic(__asrs_f, opcode => 0x05, sub_opcode => 0x0B, set_flags => 1, flags => "znv");

extern void __mululw_0(int32_t, int32_t);
#pragma intrinsic(__mululw_0, opcode => 0x05, sub_opcode => 0x30, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __mululw_f_0(int32_t, int32_t);
#pragma intrinsic(__mululw_f_0, opcode => 0x05, sub_opcode => 0x30, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern uint32_t __mululw(uint32_t, uint32_t);
#pragma intrinsic(__mululw, opcode => 0x05, sub_opcode => 0x30, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __mullw_0(int32_t, int32_t);
#pragma intrinsic(__mullw_0, opcode => 0x05, sub_opcode => 0x31, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __maclw_0(int32_t, int32_t);
#pragma intrinsic(__maclw_0, opcode => 0x05, sub_opcode => 0x33, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __mullw_f_0(int32_t, int32_t);
#pragma intrinsic(__mullw_f_0, opcode => 0x05, sub_opcode => 0x31, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __mullw(int32_t, int32_t);
#pragma intrinsic(__mullw, opcode => 0x05, sub_opcode => 0x31, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

//
// MUL/MAC 24x24 fractional multiply/accumulate with 48-bit saturation
//

extern int32_t __maclw(int32_t, int32_t);
#pragma intrinsic(__maclw, opcode => 0x05, sub_opcode => 0x33, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __mullw_f(int32_t, int32_t);
#pragma intrinsic(__mullw_f, opcode => 0x05, sub_opcode => 0x31, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __mult_0(int32_t src1, int32_t src2);
#pragma intrinsic(__mult_0, opcode => 0x05, sub_opcode => 0x18, latency_cycles => 2, effects => "aux_xmac0_24:is_written;aux_xmac1_24:is_written;aux_xmac2_24:is_written;");

extern int32_t __mult(int32_t src1, int32_t src2);
#pragma intrinsic(__mult, opcode => 0x05, sub_opcode => 0x18, latency_cycles => 2, effects => "aux_xmac0_24:is_written;aux_xmac1_24:is_written;aux_xmac2_24:is_written;");

extern void __mact_0(int32_t src1, int32_t src2);
#pragma intrinsic(__mact_0, opcode => 0x05, sub_opcode => 0x1C, latency_cycles => 2, effects => "aux_xmac0_24:is_written:is_read;aux_xmac1_24:is_written:is_read;aux_xmac2_24:is_written:is_read;");

extern int32_t __mact(int32_t src1, int32_t src2);
#pragma intrinsic(__mact, opcode => 0x05, sub_opcode => 0x1C, latency_cycles => 2, effects => "aux_xmac0_24:is_written:is_read;aux_xmac1_24:is_written:is_read;aux_xmac2_24:is_written:is_read;");

extern int32_t __mulrt(int32_t src1, int32_t src2);
#pragma intrinsic(__mulrt, opcode => 0x05, sub_opcode => 0x1A, latency_cycles => 2);

extern int32_t __macrt(int32_t src1, int32_t src2);
#pragma intrinsic(__macrt, opcode => 0x05, sub_opcode => 0x1E, latency_cycles => 2);

extern void __msubt_0(int32_t src1, int32_t src2);
#pragma intrinsic(__msubt_0, opcode => 0x05, sub_opcode => 0x20, latency_cycles => 2, effects => "aux_xmac0_24:is_written:is_read;aux_xmac1_24:is_written:is_read;aux_xmac2_24:is_written:is_read;");

extern int32_t __msubt(int32_t src1, int32_t src2);
#pragma intrinsic(__msubt, opcode => 0x05, sub_opcode => 0x20, latency_cycles => 2, effects => "aux_xmac0_24:is_written:is_read;aux_xmac1_24:is_written:is_read;aux_xmac2_24:is_written:is_read;");

extern void __mulflw_0(int32_t src1, uint32_t src2);
#pragma intrinsic(__mulflw_0, opcode => 0x05, sub_opcode => 0x32, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __mulflw_f_0(int32_t src1, uint32_t src2);
#pragma intrinsic(__mulflw_f_0, opcode => 0x05, sub_opcode => 0x32, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __mulflw(int32_t src1, uint32_t src2);
#pragma intrinsic(__mulflw, opcode => 0x05, sub_opcode => 0x32, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __mulflw_f(int32_t src1, uint32_t src2);
#pragma intrinsic(__mulflw_f, opcode => 0x05, sub_opcode => 0x32, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __machlw_0(int32_t, int32_t);
#pragma intrinsic(__machlw_0, opcode => 0x05, sub_opcode => 0x36, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __machlw_f_0(int32_t, int32_t);
#pragma intrinsic(__machlw_f_0, opcode => 0x05, sub_opcode => 0x36, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __machlw(int32_t, int32_t);
#pragma intrinsic(__machlw, opcode => 0x05, sub_opcode => 0x36, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __machlw_f(int32_t, int32_t);
#pragma intrinsic(__machlw_f, opcode => 0x05, sub_opcode => 0x36, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __macflw_0(int32_t, int32_t);
#pragma intrinsic(__macflw_0, opcode => 0x05, sub_opcode => 0x34, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __macflw_f_0(int32_t, int32_t);
#pragma intrinsic(__macflw_f_0, opcode => 0x05, sub_opcode => 0x34, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

/* DenisY: added macflw intrinsic */
extern int32_t __macflw(int32_t, int32_t);
#pragma intrinsic(__macflw, opcode => 0x05, sub_opcode => 0x34, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __machflw_0(int32_t, int32_t);
#pragma intrinsic(__machflw_0, opcode => 0x05, sub_opcode => 0x37, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __machflw_f_0(int32_t, int32_t);
#pragma intrinsic(__machflw_f_0, opcode => 0x05, sub_opcode => 0x37, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __machflw(int32_t, int32_t);
#pragma intrinsic(__machflw, opcode => 0x05, sub_opcode => 0x37, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __machflw_f(int32_t, int32_t);
#pragma intrinsic(__machflw_f, opcode => 0x05, sub_opcode => 0x37, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __machulw(uint32_t, uint32_t);
#pragma intrinsic(__machulw, opcode => 0x05, sub_opcode => 0x35, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __machulw_f(uint32_t, uint32_t);
#pragma intrinsic(__machulw_f, opcode => 0x05, sub_opcode => 0x35, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __machulw_0(uint32_t, uint32_t);
#pragma intrinsic(__machulw_0, opcode => 0x05, sub_opcode => 0x35, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __machulw_f_0(uint32_t, uint32_t);
#pragma intrinsic(__machulw_f_0, opcode => 0x05, sub_opcode => 0x35, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __mulhlw_0(int32_t, int32_t);
#pragma intrinsic(__mulhlw_0, opcode => 0x05, sub_opcode => 0x38, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern void __mulhlw_f_0(int32_t, int32_t);
#pragma intrinsic(__mulhlw_f_0, opcode => 0x05, sub_opcode => 0x38, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __mulhlw(int32_t, int32_t);
#pragma intrinsic(__mulhlw, opcode => 0x05, sub_opcode => 0x38, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __mulhlw_f(int32_t, int32_t);
#pragma intrinsic(__mulhlw_f, opcode => 0x05, sub_opcode => 0x38, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __mulhflw_0(int32_t, int32_t);
#pragma intrinsic(__mulhflw_0, opcode => 0x05, sub_opcode => 0x39, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __mulhflw_f_0(int32_t, int32_t);
#pragma intrinsic(__mulhflw_f_0, opcode => 0x05, sub_opcode => 0x39, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __mulhflw(int32_t, int32_t);
#pragma intrinsic(__mulhflw, opcode => 0x05, sub_opcode => 0x39, latency_cycles => 2, effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

/* AndreiMi */
#define __mulhflw_lt(dst, src1, src2) asm("mulhflw.lt %0, %1, %2" : "+r"(dst) : "r"(src1), "r"(src2));
#define __mulhflw_ge(dst, src1, src2) asm("mulhflw.ge %0, %1, %2" : "+r"(dst) : "r"(src1), "r"(src2));
#define __mulhflw_c(dst, src1, src2) asm("mulhflw.c %0, %1, %2" : "+r"(dst) : "r"(src1), "r"(src2));

extern int32_t __mulhflw_f(int32_t, int32_t);
#pragma intrinsic(__mulhflw_f, opcode => 0x05, sub_opcode => 0x39, latency_cycles => 2, set_flags => 1, flags => "znv", effects => "aux_xmaclw_h:is_written:is_read;aux_xmaclw_l:is_written:is_read");

extern int32_t __muldw(int32_t, int32_t);
#pragma intrinsic(__muldw, opcode => 0x05, sub_opcode => 0x0C, latency_cycles => 2);

extern void __muldw_0(int32_t, int32_t);
#pragma intrinsic(__muldw_0, opcode => 0x05, sub_opcode => 0x0C, latency_cycles => 2);

extern int32_t __mulrdw(int32_t, int32_t);
#pragma intrinsic(__mulrdw, opcode => 0x05, sub_opcode => 0x0E, latency_cycles => 2);

extern int32_t __macdw(int32_t, int32_t);
#pragma intrinsic(__macdw, opcode => 0x05, sub_opcode => 0x10, latency_cycles => 2);

extern void __macdw_0(int32_t, int32_t);
#pragma intrinsic(__macdw_0, opcode => 0x05, sub_opcode => 0x10, latency_cycles => 2);

extern void __msubdw_0(int32_t, int32_t);
#pragma intrinsic(__msubdw_0, opcode => 0x05, sub_opcode => 0x14, latency_cycles => 2);

extern int32_t __dmulpf_xy(int32_t, int32_t);
#pragma intrinsic(__dmulpf_xy, opcode => 0x05, sub_opcode => 0x3A, latency_cycles => 2);

extern void __dmulpf_xy_0(int32_t, int32_t);
#pragma intrinsic(__dmulpf_xy_0, opcode => 0x05, sub_opcode => 0x3A, latency_cycles => 2);

extern int32_t __dmacpf_xy(int32_t, int32_t);
#pragma intrinsic(__dmacpf_xy, opcode => 0x05, sub_opcode => 0x3B, latency_cycles => 2);

extern void __dmacpf_xy_0(int32_t, int32_t);
#pragma intrinsic(__dmacpf_xy_0, opcode => 0x05, sub_opcode => 0x3B, latency_cycles => 2);

extern int32_t __addsdw(int32_t, int32_t);
#pragma intrinsic(__addsdw, opcode => 0x05, sub_opcode => 0x28);

extern int32_t __subsdw(int32_t, int32_t);
#pragma intrinsic(__subsdw, opcode => 0x05, sub_opcode => 0x29);

extern uint32_t __and(uint32_t, int32_t);
#pragma intrinsic(__and, opcode => 0x04, sub_opcode => 0x04);

extern uint32_t __and_f(uint32_t, int32_t);
#pragma intrinsic(__and_f, opcode => 0x04, sub_opcode => 0x04, set_flags => 1, flags => "zn");

extern int32_t __normw(int32_t);
#pragma intrinsic(__normw, opcode => 0x05, sub_opcode => 0x08);

extern int32_t __normw_f(int32_t);
#pragma intrinsic(__normw_f, opcode => 0x05, sub_opcode => 0x08, set_flags => 1, flags => "zn");

extern int32_t __norm(int32_t);
#pragma intrinsic(__norm, opcode => 0x05, sub_opcode => 0x01);

extern int32_t __norm_f(int32_t);
#pragma intrinsic(__norm_f, opcode => 0x05, sub_opcode => 0x01, set_flags => 1, flags => "zn");

extern int16_t __abssw(int32_t);
#pragma intrinsic(__abssw, opcode => 0x05, sub_opcode => 0x04);

extern int16_t __abssw_f(int32_t);
#pragma intrinsic(__abssw_f, opcode => 0x05, sub_opcode => 0x04, set_flags => 1, flags => "znv");

extern int32_t __abss(int32_t);
#pragma intrinsic(__abss, opcode => 0x05, sub_opcode => 0x05);

extern int32_t __abss_f(int32_t);
#pragma intrinsic(__abss_f, opcode => 0x05, sub_opcode => 0x05, set_flags => 1, flags => "znv");

extern int32_t __max(int32_t, int32_t);
#pragma intrinsic(__max, opcode => 0x04, sub_opcode => 0x08);

extern int32_t __max_f(int32_t, int32_t);
#pragma intrinsic(__max_f, opcode => 0x04, sub_opcode => 0x08, set_flags => 1, flags => "zcnv");

extern int32_t __min(int32_t, int32_t);
#pragma intrinsic(__min, opcode => 0x04, sub_opcode => 0x09);

extern int32_t __min_f(int32_t, int32_t);
#pragma intrinsic(__min_f, opcode => 0x04, sub_opcode => 0x09, set_flags => 1, flags => "zcnv");

extern int32_t __adds(int32_t, int32_t);
#pragma intrinsic(__adds, opcode => 0x05, sub_opcode => 0x06);

extern int32_t __adds_f(int32_t, int32_t);
#pragma intrinsic(__adds_f, opcode => 0x05, sub_opcode => 0x06, set_flags => 1, flags => "zcnv");

extern int32_t __subs(int32_t, int32_t);
#pragma intrinsic(__subs, opcode => 0x05, sub_opcode => 0x07);

extern int32_t __subs_f(int32_t, int32_t);
#pragma intrinsic(__subs_f, opcode => 0x05, sub_opcode => 0x07, set_flags => 1, flags => "zcnv");

extern int32_t __divaw(int32_t src1, int32_t src2);
#pragma intrinsic(__divaw, opcode => 0x05, sub_opcode => 0x08);

extern int32_t __negs(int32_t);
#pragma intrinsic(__negs, opcode => 0x05, sub_opcode => 0x07);

extern int32_t __negs_f(int32_t);
#pragma intrinsic(__negs_f, opcode => 0x05, sub_opcode => 0x07, set_flags => 1, flags => "znv");

extern int32_t __negsw(int32_t);
#pragma intrinsic(__negsw, opcode => 0x05, sub_opcode => 0x06);

extern int32_t __negsw_f(int32_t);
#pragma intrinsic(__negsw_f, opcode => 0x05, sub_opcode => 0x06, set_flags => 1, flags => "znv");


extern uint32_t __crc(uint32_t, uint32_t);
#pragma intrinsic(__crc, opcode => 0x05, sub_opcode => 0x2C, latency_cycles => 2);

#else   // ARC600_NO_INTRINSICS

#ifdef ARC600_INTRINSICS_ONLY
#error Define either ARC600_NO_INTRINSICS or ARC600_INTRINSICS_ONLY, not both
#endif

#define __nop()             __Nop()                 /* Simeon */
#define __mov(b, c)         __Mov(b, c)
#define __mov_f(b, c)       __Mov_f(b, c)
#define __asl(a, s)         __Asl(a, s)
#define __asl_f(a, s)       __Asl_f(a, s)
#define __asr(x, s)         __Asr(x, s)
#define __asr_f(x, s)       __Asr_f(x, s)
#define __lsr(a, s)         __Lsr(a, s)
#define __lsr_f(a, s)       __Lsr_f(a, s)
#define __asls(a, s)        __Asls(a, s)
#define __asls_f(a, s)      __Asls_f(a, s)
#define __asrs(a, s)        __Asrs(a, s)
#define __asrs_f(a, s)      __Asrs_f(a, s)
#define __ror(a, b)         __Ror(a, b)
#define __rlc(a)            __Rlc(a)
#define __rlc_f(a)          __Rlc_f(a)
#define __or(a, b)          __Or(a, b)
#define __or_f(a, b)        __Or_f(a, b)
#define __and(a, b)         __And(a, b)
#define __and_f(a, b)       __And_f(a, b)
#define __adds(a, b)        __Adds(a, b)
#define __adds_f(a, b)      __Adds_f(a, b)
#define __subs(a, b)        __Subs(a, b)
#define __subs_f(a, b)      __Subs_f(a, b)
#define __negs(a)           __Negs(a)
#define __negs_f(a)         __Negs_f(a)
#define __negsw(a)          __Negsw(a)
#define __negsw_f(a)        __Negsw_f(a)
#define __add(src1, src2)   __Add(src1, src2)
#define __add_f(src1, src2) __Add_f(src1, src2)
#define __sub(src1, src2)   __Sub(src1, src2)
#define __sub_f(src1, src2) __Sub_f(src1, src2)
#define __add1(src1, src2)  __Add1(src1, src2)
#define __add1_f(src1, src2)__Add1_f(src1, src2)
#define __sub1(src1, src2)  __Sub1(src1, src2)
#define __sub1_f(src1, src2)__Sub1_f(src1, src2)
#define __add2(src1, src2)  __Add2(src1, src2)
#define __add2_f(src1, src2)__Add2_f(src1, src2)
#define __sub2(src1, src2)  __Sub2(src1, src2)
#define __sub2_f(src1, src2)__Sub2_f(src1, src2)
#define __add3(src1, src2)  __Add3(src1, src2)
#define __add3_f(src1, src2)__Add3_f(src1, src2)
#define __sub3(src1, src2)  __Sub3(src1, src2)
#define __sub3_f(src1, src2)__Sub3_f(src1, src2)
#define __abss(a)           __Abss (a)
#define __abss_f(a)         __Abss_f(a)
#define __max(a, b)         __Max(a, b)
#define __max_f(a, b)       __Max_f(a, b)
#define __min(a, b)         __Min(a, b)
#define __min_f(a, b)       __Min_f(a, b)
#define __abssw(a)          __Abssw(a)
#define __abssw_f(a)        __Abssw_f(a)
#define __bmsk(x, m)        __Bmsk(x, m)
#define __bmsk_f(x, m)      __Bmsk_f(x, m)
#define __bset(x, m)        __Bset(x, m)
#define __bset_f(x, m)      __Bset_f(x, m)
#define __btst(x, m)        __Btst(x, m)
#define __bclr(x, m)        __Bclr(x, m)
#define __bclr_f(x, m)      __Bclr_f(x, m)
#define __bxor(x, m)        __Bxor(x, m)
#define __bxor_f(x, m)      __Bxor_f(x, m)
#define __normw(x)          __Normw(x)
#define __normw_f(x)        __Normw_f(x)
#define __norm(x)           __Norm(x)
#define __norm_f(x)         __Norm_f(x)
#define __swap(a)           __Swap(a)
#define __swap_f(a)         __Swap_f(a)
#define __sat16(a)          __Sat16(a)
#define __sat16_f(a)        __Sat16_f(a)
#define __rnd16(a)          __Rnd16(a)
#define __rnd16_f(a)        __Rnd16_f(a)
#define __divaw(src1, src2) __Divaw(src1, src2)
#define __push(src)         __Push(src)
#define __pop()             __Pop()
#define __subsdw(a, b)      __Subsdw(a, b)
#define __addsdw(a, b)      __Addsdw(a, b)

#define __mulflw_0(src1, src2)  __Mulflw_0(src1, src2)
#define __mulflw_f_0(src1, src2)__Mulflw_f_0(src1, src2)
#define __mulflw(src1, src2)    __Mulflw(src1, src2)
#define __mulflw_f(src1, src2)  __Mulflw_f(src1, src2)
#define __macflw_0(src1, src2)  __Macflw_0(src1, src2)
#define __macflw_f_0(src1, src2)__Macflw_f_0(src1, src2)
#define __macflw(src1, src2)    __Macflw(src1, src2)
#define __macflw_f(src1, src2)  __Macflw_f(src1, src2)
#define __mulhflw_0(src1, src2) __Mulhflw_0(src1, src2)
#define __mulhflw_f_0(src1, src2__Mulhflw_f_0(src1, src2)
#define __mulhflw(src1, src2)   __Mulhflw(src1, src2)
#define __mulhflw_f(src1, src2) __Mulhflw_f(src1, src2)
#define __machflw_0(src1, src2) __Machflw_0(src1, src2)
#define __machflw_f_0(src1, src2__Machflw_f_0(src1, src2)
#define __machflw(src1, src2)   __Machflw(src1, src2)
#define __machflw_f(src1, src2) __Machflw_f(src1, src2)
#define __mullw_0(src1, src2)   __Mullw_0(src1, src2)
#define __mullw_f_0(src1, src2) __Mullw_f_0(src1, src2)
#define __mullw(src1, src2)     __Mullw(src1, src2)
#define __mululw(src1, src2)    __Mululw(src1, src2)
#define __mullw_f(src1, src2)   __Mullw_f(src1, src2)
#define __mulhlw_0(src1, src2)  __Mulhlw_0(src1, src2)
#define __mulhlw_f_0(src1, src2)__Mulhlw_f_0(src1, src2)
#define __mulhlw(src1, src2)    __Mulhlw(src1, src2)
#define __mulhlw_f(src1, src2)  __Mulhlw_f(src1, src2)
#define __maclw_0(src1, src2)   __Maclw_0(src1, src2)
#define __maclw_f_0(src1, src2) __Maclw_f_0(src1, src2)
#define __maclw(src1, src2)     __Maclw(src1, src2)
#define __maclw_f(src1, src2)   __Maclw_f(src1, src2)
#define __machlw_0(src1, src2)  __Machlw_0(src1, src2)
#define __machlw_f_0(src1, src2)__Machlw_f_0(src1, src2)
#define __machlw(src1, src2)    __Machlw(src1, src2)
#define __machlw_f(src1, src2)  __Machlw_f(src1, src2)
#define __machulw(src1, src2)   __Machulw(src1, src2)
#define __machulw_f(src1, src2) __Machulw_f(src1, src2)
#define __machulw_0(src1, src2) __Machulw_0(src1, src2)
#define __machulw_f_0(src1, src2) __Machulw_f_0(src1, src2)
#define __muldw(src1, src2)     __Muldw(src1, src2)
#define __muldw_0(src1, src2)   __Muldw_0(src1, src2)
#define __mulrdw(src1, src2)    __Mulrdw(src1, src2)
#define __macdw(src1, src2)     __Macdw(src1, src2)
#define __macdw_0(src1, src2)   __Macdw_0(src1, src2)
#define __msubdw_0(src1, src2)  __Msubdw_0(src1, src2)

#define __get_ACC1()            __Get_ACC1()
#define __get_ACC2()            __Get_ACC2()

/* AndreiMi */
#define __get_ACC1_H()          __Get_ACC1_H()
#define __get_ACC2_H()          __Get_ACC2_H()

//AndreM
#define __get_xbase()           __Get_xbase()
#define __get_ybase()           __Get_ybase()

#define __get_AAh()             __Get_AAh()
#define __get_AAl()             __Get_AAl()

/* Simeon */
#define __get_AUX_XMAC0_24()      __get_AUX_XMAC0_24()
#define __get_AUX_XMAC1_24()      __get_AUX_XMAC1_24()
#define __get_AUX_XMAC2_24()      __get_AUX_XMAC2_24()

#define __ax0()    __Ax0()
#define __ax1()    __Ax1()
#define __ax2()    __Ax2()
#define __ax3()    __Ax3()

#define __ay0()    __Ay0()
#define __ay1()    __Ay1()
#define __ay2()    __Ay2()
#define __ay3()    __Ay3()

#define __set_ax0(a)       __Set_ax0(a)
#define __set_ax1(a)       __Set_ax1(a)
#define __set_ax2(a)       __Set_ax2(a)
#define __set_ax3(a)       __Set_ax3(a)

#define __set_ay0(a)       __Set_ay0(a)
#define __set_ay1(a)       __Set_ay1(a)
#define __set_ay2(a)       __Set_ay2(a)
#define __set_ay3(a)       __Set_ay3(a)

#define __mx00()   __Mx00()
#define __mx01()   __Mx01()
#define __mx10()   __Mx10()
#define __mx11()   __Mx11()
#define __mx20()   __Mx20()
#define __mx21()   __Mx21()
#define __mx30()   __Mx30()
#define __mx31()   __Mx31()

#define __my00()   __My00()
#define __my01()   __My01()
#define __my10()   __My10()
#define __my11()   __My11()
#define __my20()   __My20()
#define __my21()   __My21()
#define __my30()   __My30()
#define __my31()   __My31()

#define __set_mx00(a)   __Set_mx00(a)
#define __set_mx01(a)   __Set_mx01(a)
#define __set_mx10(a)   __Set_mx10(a)
#define __set_mx11(a)   __Set_mx11(a)
#define __set_mx20(a)   __Set_mx20(a)
#define __set_mx21(a)   __Set_mx21(a)
#define __set_mx30(a)   __Set_mx30(a)
#define __set_mx31(a)   __Set_mx31(a)

#define __set_my00(a)   __Set_my00(a)
#define __set_my01(a)   __Set_my01(a)
#define __set_my10(a)   __Set_my10(a)
#define __set_my11(a)   __Set_my11(a)
#define __set_my20(a)   __Set_my20(a)
#define __set_my21(a)   __Set_my21(a)
#define __set_my30(a)   __Set_my30(a)
#define __set_my31(a)   __Set_my31(a)

#define __x0_u0()      __X0_u0()
#define __x0_u1()      __X0_u1()
#define __x0_nu()      __X0_nu()
#define __x1_u0()      __X1_u0()
#define __x1_u1()      __X1_u1()
#define __x1_nu()      __X1_nu()
#define __x2_u0()      __X2_u0()
#define __x2_u1()      __X2_u1()
#define __x2_nu()      __X2_nu()
#define __x3_u0()      __X3_u0()
#define __x3_u1()      __X3_u1()
#define __x3_nu()      __X3_nu()
#define __y0_u0()      __Y0_u0()
#define __y0_u1()      __Y0_u1()
#define __y0_nu()      __Y0_nu()
#define __y1_u0()      __Y1_u0()
#define __y1_u1()      __Y1_u1()
#define __y1_nu()      __Y1_nu()
#define __y2_u0()      __Y2_u0()
#define __y2_u1()      __Y2_u1()
#define __y2_nu()      __Y2_nu()
#define __y3_u0()      __Y3_u0()
#define __y3_u1()      __Y3_u1()
#define __y3_nu()      __Y3_nu()

#define __set_x0_u0(x)  __Set_x0_u0(x)
#define __set_x0_u1(x)  __Set_x0_u1(x)
#define __set_x0_nu(x)  __Set_x0_nu(x)
#define __set_x1_u0(x)  __Set_x1_u0(x)
#define __set_x1_u1(x)  __Set_x1_u1(x)
#define __set_x1_nu(x)  __Set_x1_nu(x)
#define __set_x2_u0(x)  __Set_x2_u0(x)
#define __set_x2_u1(x)  __Set_x2_u1(x)
#define __set_x2_nu(x)  __Set_x2_nu(x)
#define __set_x3_u0(x)  __Set_x3_u0(x)
#define __set_x3_u1(x)  __Set_x3_u1(x)
#define __set_x3_nu(x)  __Set_x3_nu(x)

#define __set_y0_u0(x)  __Set_y0_u0(x)
#define __set_y0_u1(x)  __Set_y0_u1(x)
#define __set_y0_nu(x)  __Set_y0_nu(x)
#define __set_y1_u0(x)  __Set_y1_u0(x)
#define __set_y1_u1(x)  __Set_y1_u1(x)
#define __set_y1_nu(x)  __Set_y1_nu(x)
#define __set_y2_u0(x)  __Set_y2_u0(x)
#define __set_y2_u1(x)  __Set_y2_u1(x)
#define __set_y2_nu(x)  __Set_y2_nu(x)
#define __set_y3_u0(x)  __Set_y3_u0(x)
#define __set_y3_u1(x)  __Set_y3_u1(x)
#define __set_y3_nu(x)  __set_y3_nu(x)

#endif // !ARC600_NO_INTRINSICS

//
// Instruction set in assembler macros (pseudo-assembler)
//
#ifndef ARC600_INTRINSICS_ONLY

/* Simeon */
_Asm void __Nop()
{
    nop
}

_Asm int32_t __Sat16(int32_t a)
{
    %reg a

    sat16  %r0, a
}

_Asm int32_t __Sat16_f(int32_t a)
{
    %reg a

    sat16.f  %r0, a
}

_Asm int32_t __Rnd16(int32_t a)
{
    %reg a

    rnd16  %r0, a
}

_Asm int32_t __Rnd16_f(int32_t a)
{
    %reg a

    rnd16.f  %r0, a
}

_Asm int16_t __Abssw(int32_t a)
{
    %reg a

    abssw  %r0, a
}

_Asm int16_t __Abssw_f(int32_t a)
{
    %reg a

    abssw.f  %r0, a
}

_Asm int32_t __Abss(int32_t a)
{
    %reg a

    abss  %r0, a
}

_Asm int32_t __Abss_f(int32_t a)
{
    %reg a

    abss.f  %r0, a
}

/* Simeon: b declared as register */
_Asm int32_t __Max(int32_t a, int32_t b)
{
    %reg a, b

    max  %r0, a, b
}

/* Simeon: b declared as register */
_Asm int32_t __Max_f(int32_t a, int32_t b)
{
    %reg a, b

    max.f  %r0, a, b
}

_Asm int32_t __Min(int32_t a, int32_t b)
{
    %reg a

    min  %r0, a, b
}

_Asm int32_t __Min_f(int32_t a, int32_t b)
{
    %reg a

    min.f  %r0, a, b
}

_Asm int32_t __Negs(int32_t a)
{
    %reg a

    negs   %r0, a
}

_Asm int32_t __Negs_f(int32_t a)
{
    %reg a

    negs.f   %r0, a
}

_Asm int16_t __Negsw(int32_t a)
{
    %reg a

    negsw   %r0, a
}

_Asm int16_t __Negsw_f(int32_t a)
{
    %reg a

    negsw.f   %r0, a
}

_Asm int32_t __Mov(int32_t a)
{
    %reg a

    mov    %r0, a
}

_Asm int32_t __Mov_f(int32_t a)
{
    %reg a

    mov.f    %r0, a
}

_Asm int32_t __Lsr(int32_t a, unsigned s)
{
    %reg a, s

    lsr   %r0, a, s
}

_Asm int32_t __Lsr_f(int32_t a, unsigned s)
{
    %reg a, s

    lsr.f   %r0, a, s
}

_Asm int32_t __Asls(int32_t a, signed s)
{
    %reg a, s

    asls   %r0, a, s
}

_Asm int32_t __Asls_f(int32_t a, signed s)
{
    %reg a, s

    asls.f   %r0, a, s
}

_Asm int32_t __Asrs(int32_t a, signed s)
{
    %reg a, s

    asrs   %r0, a, s
}

_Asm int32_t __Asrs_f(int32_t a, signed s)
{
    %reg a, s

    asrs.f   %r0, a, s
}

_Asm int32_t __Asl(int32_t a, signed s)
{
    %reg a, s

    asl   %r0, a, s
}

_Asm int32_t __Asl_f(int32_t a, signed s)
{
    %reg a, s

    asl.f   %r0, a, s
}

_Asm int32_t __Asr(int32_t a, signed s)
{
    %reg a, s

    asr   %r0, a, s
}

_Asm int32_t __Asr_f(int32_t a, signed s)
{
    %reg a, s

    asr.f   %r0, a, s
}

/* Simeon */
_Asm int32_t __Or(int32_t src1, int32_t src2)
{
    %reg src1, src2

    or   %r0, src1, src2
}

_Asm int32_t __Add(int32_t src1, int32_t src2)
{
    %reg src1, src2

    add    %r0, src1, src2
}

_Asm int32_t __Add_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    add.f    %r0, src1, src2
}

_Asm int32_t __Add1(int32_t src1, int32_t src2)
{
    %reg src1, src2

    add1    %r0, src1, src2
}

_Asm int32_t __Add1_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    add1.f    %r0, src1, src2
}

_Asm int32_t __Add2(int32_t src1, int32_t src2)
{
    %reg src1, src2

    add2    %r0, src1, src2
}

_Asm int32_t __Add2_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    add2.f    %r0, src1, src2
}

_Asm int32_t __Add3(int32_t src1, int32_t src2)
{
    %reg src1, src2

    add3    %r0, src1, src2
}

_Asm int32_t __Add3_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    add3.f    %r0, src1, src2
}

_Asm int32_t __Adds(int32_t src1, int32_t src2)
{
    %reg src1, src2

    adds    %r0, src1, src2
}

_Asm int32_t __Adds_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    adds.f    %r0, src1, src2
}

_Asm int32_t __Subs(int32_t src1, int32_t src2)
{
    %reg src1, src2

    subs    %r0, src1, src2
}

_Asm int32_t __Subs_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    subs.f    %r0, src1, src2
}

_Asm int32_t __Sub1(int32_t src1, int32_t src2)
{
    %reg src1, src2

    sub1    %r0, src1, src2
}

_Asm int32_t __Sub1_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    sub1.f    %r0, src1, src2
}

_Asm int32_t __Sub(int32_t src1, int32_t src2)
{
    %reg src1, src2

    sub    %r0, src1, src2
}

_Asm int32_t __Sub_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    sub.f    %r0, src1, src2
}

_Asm int32_t __Rsub_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    rsub.f   %r0, src1, src2
}

_Asm int32_t __Sub2(int32_t src1, int32_t src2)
{
    %reg src1, src2

    sub2    %r0, src1, src2
}

_Asm int32_t __Sub2_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    sub2.f    %r0, src1, src2
}

//
// MUL/MAC 24x24 fractional multiply/accumulate with 48-bit saturation
//


_Asm _CC(_SAVE_ALL_REGS) void __Mult_0(int32_t src1, int32_t src2) {
%reg src1, src2

    mult    0,   src1, src2

} /* __Mult_0 */

_Asm _CC(_SAVE_ALL_REGS) int32_t __Mult(int32_t src1, int32_t src2) {
%reg src1, src2

    mult    %r0, src1, src2

} /* __Mult */

/* Simeon: added __Mulrt */
_Asm _CC(_SAVE_ALL_REGS) int32_t __Mulrt(int32_t src1, int32_t src2) {
    %reg src1, src2

        mulrt    %r0, src1, src2

} /* __Mulrt */

_Asm _CC(_SAVE_ALL_REGS) void __Mact_0(int32_t src1, int32_t src2) {
%reg src1, src2

    mact    0,   src1, src2

} /* __Mact_0 */

_Asm _CC(_SAVE_ALL_REGS) int32_t __Mact(int32_t src1, int32_t src2) {
%reg src1, src2

    mact    %r0, src1, src2

} /* __Mact */

/* Simeon: added __Macrt */
_Asm _CC(_SAVE_ALL_REGS) int32_t __Macrt(int32_t src1, int32_t src2) {
    %reg src1, src2

        macrt    %r0, src1, src2

} /* __Macrt */

_Asm _CC(_SAVE_ALL_REGS) void __Msubt_0(int32_t src1, int32_t src2) {
%reg src1, src2

    msubt   0,   src1, src2

} /* __Msubt_0 */

_Asm _CC(_SAVE_ALL_REGS) int32_t __Msubt(int32_t src1, int32_t src2) {
%reg src1, src2

    msubt   %r0, src1, src2

} /* __Msubt */




_Asm int32_t __Machlw(int32_t src1, int32_t src2)
{
    %reg src1, src2

    machlw    %r0, src1, src2
}

_Asm uint32_t __Mululw_0(uint32_t src1, uint32_t src2)
{
    %reg src1, src2

    mululw    0,   src1, src2
}

_Asm uint32_t __Mululw(uint32_t src1, uint32_t src2)
{
    %reg src1, src2

    mululw    %r0, src1, src2
}

_Asm int32_t __Machlw_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    machlw.f    %r0, src1, src2
}

_Asm void __Machlw_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    machlw    0, src1, src2
}

_Asm void __Machlw_f_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    machlw.f    0, src1, src2
}

_Asm uint32_t __Machulw(uint32_t src1, uint32_t src2)
{
    %reg src1, src2

    machulw    %r0, src1, src2
}

_Asm void __Machulw_0(uint32_t src1, uint32_t src2)
{
    %reg src1, src2

    machulw    0, src1, src2
}

_Asm uint32_t __Machulw_f(uint32_t src1, uint32_t src2)
{
    %reg src1, src2

    machulw.f    %r0, src1, src2
}

_Asm uint32_t __Machulw_f_0(uint32_t src1, uint32_t src2)
{
    %reg src1, src2

    machulw.f    0, src1, src2
}

_Asm void __Mulflw_0(int32_t src1, uint32_t src2)
{
    %reg src1, src2

    mulflw    0, src1, src2
}

_Asm void __Mulflw_f_0(int32_t src1, uint32_t src2)
{
    %reg src1, src2

    mulflw.f    0, src1, src2
}

_Asm int32_t __Mulflw(int32_t src1, uint32_t src2)
{
    %reg src1, src2

    mulflw    %r0, src1, src2
}

_Asm int32_t __Mulflw_f(int32_t src1, uint32_t src2)
{
    %reg src1, src2

    mulflw.f    %r0, src1, src2
}

_Asm void __Mulhlw_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    mulhlw    0, src1, src2
}

_Asm void __Mulhlw_f_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    mulhlw.f    0, src1, src2
}

_Asm void __Mulhflw_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    mulhflw    0, src1, src2
}

_Asm void __Mulhflw_f_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    mulhflw.f    0, src1, src2
}

_Asm int32_t __Mulhflw(int32_t src1, int32_t src2)
{
    %reg src1, src2

    mulhflw    %r0, src1, src2
}

_Asm int32_t __Mulhflw_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    mulhflw.f    %r0, src1, src2
}

/* AndreyMi */
_Asm int32_t __Mullw(int32_t src1, int32_t src2)
{
    %reg src1, src2

    mullw    %r0, src1, src2
}

_Asm void __Macflw_0(int32_t src1, uint32_t src2)
{
    %reg src1, src2

    macflw    0, src1, src2
}

_Asm void __Macflw_f_0(int32_t src1, uint32_t src2)
{
    %reg src1, src2

    macflw.f    0, src1, src2
}

_Asm int32_t __Macflw(int32_t src1, uint32_t src2)
{
    %reg src1, src2

    macflw    %r0, src1, src2
}

_Asm int32_t __Macflw_f(int32_t src1, uint32_t src2)
{
    %reg src1, src2

    macflw.f    %r0, src1, src2
}

_Asm void __Machflw_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    machflw    0, src1, src2
}

_Asm void __Machflw_f_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    machflw.f    0, src1, src2
}

_Asm int32_t __Muldw(int32_t src1, int32_t src2)
{
    %reg src1, src2

    muldw    %r0, src1, src2
}

_Asm void __Muldw_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    muldw    0, src1, src2
}

_Asm int32_t __Mulrdw(int32_t src1, int32_t src2)
{
    %reg src1, src2

    mulrdw    %r0, src1, src2
}

/* Simeon */
_Asm int32_t __Mulhlw(int32_t src1, int32_t src2)
{
    %reg src1, src2

     mulhlw    %r0, src1, src2
}

/* Simeon */
_Asm int32_t __Maclw(int32_t src1, int32_t src2)
{
    %reg src1, src2

     maclw    %r0, src1, src2
}

/* Simeon */
_Asm int32_t __Maclw_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    maclw    0, src1, src2
}


_Asm int32_t __Macdw(int32_t src1, int32_t src2)
{
    %reg src1, src2

    macdw    %r0, src1, src2
}

_Asm void __Macdw_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    macdw    0, src1, src2
}

_Asm void __Msubdw_0(int32_t src1, int32_t src2)
{
    %reg src1, src2

    msubdw    0, src1, src2
}

_Asm int32_t __Divaw(int32_t src1, int32_t src2)
{
    %reg src1, src2

    divaw  %r0, src1, src2
}

_Asm int32_t __Machflw(int32_t src1, int32_t src2)
{
    %reg src1, src2

    machflw    %r0, src1, src2
}

_Asm int32_t __Machflw_f(int32_t src1, int32_t src2)
{
    %reg src1, src2

    machflw.f    %r0, src1, src2
}

_Asm uint32_t __Bmsk(uint32_t x, int m)
{
    %reg x, m

    bmsk    %r0, x, m
}

_Asm uint32_t __Bmsk_f(uint32_t x, int m)
{
    %reg x, m

    bmsk.f    %r0, x, m
}

_Asm uint32_t __Bset(uint32_t x, int m)
{
    %reg x, m

    bset    %r0, x, m
}

_Asm uint32_t __Bset_f(uint32_t x, int m)
{
    %reg x, m

    bset.f    %r0, x, m
}

_Asm void __Btst(uint32_t x, int m)
{
    %reg x, m

    btst    %r0, x, m
}

_Asm uint32_t __Bclr(uint32_t x, int m)
{
    %reg x, m

    bclr    %r0, x, m
}

_Asm uint32_t __Bclr_f(uint32_t x, int m)
{
    %reg x, m

    bclr.f    %r0, x, m
}

_Asm uint32_t __Bxor(uint32_t x, int m)
{
    %reg x, m

    bxor    %r0, x, m
}

_Asm uint32_t __Bxor_f(uint32_t x, int m)
{
    %reg x, m

    bxor.f    %r0, x, m
}

_Asm int32_t lr_xmac1()
{
    lr    %r0, [%aux_xmac1632h]
}


_Asm int __Normw(int32_t x)
{
    %reg x

    normw   %r0, x
}

_Asm int __Normw_f(int32_t x)
{
    %reg x

    normw.f   %r0, x
}

_Asm int __Norm(int32_t x)
{
    %reg x

    norm    %r0, x
}

_Asm int __Norm_f(int32_t x)
{
    %reg x

    norm.f    %r0, x
}

#define XYMEMORY_SLOT(xy, XY, I)    \
_Asm int32_t __##XY##I##_u0()        \
{    \
    mov    %r0, %xy##I##_u0         \
}    \
\
_Asm int32_t __##XY##I##_u1()        \
{    \
    mov    %r0, %xy##I##_u1         \
}    \
\
_Asm int32_t __##XY##I##_nu()        \
{    \
    mov    %r0, %xy##I##_nu         \
}

 // x0

_Asm void __Set_x0_u0(int32_t a)
{
    %reg a

    mov    %x0_u0, a
}

_Asm void __Set_x0_u1(int32_t a)
{
    %reg a

    mov    %x0_u1, a
}

_Asm void __Set_x0_nu(int32_t a)
{
    %reg a

    mov    %x0_nu, a
}

// x1

_Asm void __Set_x1_u0(int32_t a)
{
    %reg a

    mov    %x1_u0, a
}

_Asm void __Set_x1_u1(int32_t a)
{
    %reg a

    mov    %x1_u1, a
}

_Asm void __Set_x1_nu(int32_t a)
{
    %reg a

    mov    %x1_nu, a
}

// x2

_Asm void __Set_x2_u0(int32_t a)
{
    %reg a

    mov    %x2_u0, a
}

_Asm void __Set_x2_u1(int32_t a)
{
    %reg a

    mov    %x2_u1, a
}

_Asm void __Set_x2_nu(int32_t a)
{
    %reg a

    mov    %x2_nu, a
}

// x3

_Asm void __Set_x3_u0(int32_t a)
{
    %reg a

    mov    %x3_u0, a
}

_Asm void __Set_x3_u1(int32_t a)
{
    %reg a

    mov    %x3_u1, a
}

_Asm void __Set_x3_nu(int32_t a)
{
    %reg a

    mov    %x3_nu, a
}

// y0

_Asm void __Set_y0_u0(int32_t a)
{
    %reg a

    mov    %y0_u0, a
}

_Asm void __Set_y0_u1(int32_t a)
{
    %reg a

    mov    %y0_u1, a
}

_Asm void __Set_y0_nu(int32_t a)
{
    %reg a

    mov    %y0_nu, a
}

// y1

_Asm void __Set_y1_u0(int32_t a)
{
    %reg a

    mov    %y1_u0, a
}

_Asm void __Set_y1_u1(int32_t a)
{
    %reg a

    mov    %y1_u1, a
}

_Asm void __Set_y1_nu(int32_t a)
{
    %reg a

    mov    %y1_nu, a
}

// y2

_Asm void __Set_y2_u0(int32_t a)
{
    %reg a

    mov    %y2_u0, a
}

_Asm void __Set_y2_u1(int32_t a)
{
    %reg a

    mov    %y2_u1, a
}

_Asm void __Set_y2_nu(int32_t a)
{
    %reg a

    mov    %y2_nu, a
}

// y3

_Asm void __Set_y3_u0(int32_t a)
{
    %reg a

    mov    %y3_u0, a
}

_Asm void __Set_y3_u1(int32_t a)
{
    %reg a

    mov    %y3_u1, a
}

_Asm void __Set_y3_nu(int32_t a)
{
    %reg a

    mov    %y3_nu, a
}

_Asm int32_t __Get_AUX_XMAC0_24()
{
    lr  %r0, [AUX_XMAC0_24]
}

_Asm int32_t __Get_AUX_XMAC1_24()
{
    lr  %r0, [AUX_XMAC1_24]
}

_Asm int32_t __Get_AUX_XMAC2_24()
{
    lr  %r0, [AUX_XMAC2_24]
}

_Asm int32_t __Get_ACC1()
{
    mov %r0, %acc1
}

_Asm int32_t __Get_ACC2()
{
    mov %r0, %acc2
}

_Asm int32_t __Get_AAh()
{
    lr  %r0, [AUX_XMACLW_H]
}

_Asm uint32_t __Get_AAl()
{
    lr  %r0, [AUX_XMACLW_L]
}
_Asm uint32_t get_MACMODE(void)
{
    lr  %r0, [AUX_MACMODE]
}
_Asm void set_MACMODE(uint32_t mode)
{
    %reg mode

    sr    mode, [AUX_MACMODE]

    %con mode

    sr    mode, [AUX_MACMODE]

    %error
}

_Asm timer_t _GetTimer()
{
    lr %r0, [%t1_count]
}

_Asm void _SetTimer(uint32_t t)
{
    %reg t

        sr    0xFFFFFFFF, [%t1_limit]
        sr    t, [%t1_count]
}

_Asm void push(int32_t src)
{
    %reg src

    push    src
}

_Asm int32_t pop()
{
    pop     %r0
}

XYMEMORY_SLOT(x, X, 0)
XYMEMORY_SLOT(x, X, 1)
XYMEMORY_SLOT(x, X, 2)
XYMEMORY_SLOT(x, X, 3)

XYMEMORY_SLOT(y, Y, 0)
XYMEMORY_SLOT(y, Y, 1)
XYMEMORY_SLOT(y, Y, 2)
XYMEMORY_SLOT(y, Y, 3)

#else // ARC600_INTRINSICS_ONLY

#ifdef ARC600_NO_INTRINSICS
#error Define either ARC600_INTRINSICS_ONLY or ARC600_NO_INTRINSICS, not both
#endif

#define __Nop()                 __asl()                 /* Simeon */
#define __Asl(a, s)             __asl(a, s)
#define __Asl_f(a, s)           __asl_f(a, s)
#define __Asr(x, s)             __asr(x, s)
#define __Asr_f(x, s)           __asr_f(x, s)
#define __Lsr(a, s)             __lsr(a, s)
#define __Lsr_f(a, s)           __lsr_f(a, s)
#define __Asls(a, s)            __asls(a, s)
#define __Asls_f(a, s)          __asls_f(a, s)
#define __Asrs(a, s)            __asrs(a, s)
#define __Asrs_f(a, s)          __asrs_f(a, s)
#define __Ror(a, b)             __ror(a, b)
#define __Rlc(a)                __rlc(a)
#define __Rlc_f(a)              __rlc_f(a)
#define __Or(a, b)              __or(a, b)
#define __Or_f(a, b)            __or_f(a, b)
#define __And(a, b)             __and(a, b)
#define __And_f(a, b)           __and_f(a, b)
#define __Adds(a, b)            __adds(a, b)
#define __Adds_f(a, b)          __adds_f(a, b)
#define __Subs(a, b)            __subs(a, b)
#define __Subs_f(a, b)          __subs_f(a, b)
#define __Negs(a)               __negs(a)
#define __Negs_f(a)             __negs_f(a)
#define __Negsw(a)              __negsw(a)
#define __Negsw_f(a)            __negsw_f(a)
#define __Add(src1, src2)       __add(src1, src2)
#define __Add_f(src1, src2)     __add_f(src1, src2)
#define __Sub(src1, src2)       __sub(src1, src2)
#define __Sub_f(src1, src2)     __sub_f(src1, src2)
#define __Add1(src1, src2)      __add1(src1, src2)
#define __Add1_f(src1, src2)    __add1_f(src1, src2)
#define __Sub1(src1, src2)      __sub1(src1, src2)
#define __Sub1_f(src1, src2)    __sub1_f(src1, src2)
#define __Add2(src1, src2)      __add2(src1, src2)
#define __Add2_f(src1, src2)    __add2_f(src1, src2)
#define __Sub2(src1, src2)      __sub2(src1, src2)
#define __Sub2_f(src1, src2)    __sub2_f(src1, src2)
#define __Add3(src1, src2)      __add3(src1, src2)
#define __Add3_f(src1, src2)    __add3_f(src1, src2)
#define __Sub3(src1, src2)      __sub3(src1, src2)
#define __Sub3_f(src1, src2)    __sub3_f(src1, src2)
#define __Abss(a)               __abss(a)
#define __Abss_f(a)             __abss_f(a)
#define __Max(a, b)             __max(a, b)
#define __Max_f(a, b)           __max_f(a, b)
#define __Min(a, b)             __min(a, b)
#define __Min_f(a, b)           __min_f(a, b)
#define __Abssw(a)              __abssw(a)
#define __Abssw_f(a)            __abssw_f(a)
#define __Bmsk(x, m)            __bmsk(x, m)
#define __Bmsk_f(x, m)          __bmsk_f(x, m)
#define __Bset(x, m)            __bset(x, m)
#define __Bset_f(x, m)          __bset_f(x, m)
#define __Btst(x, m)            __btst(x, m)
#define __Bclr(x, m)            __bclr(x, m)
#define __Bclr_f(x, m)          __bclr_f(x, m)
#define __Bxor(x, m)            __bxor(x, m)
#define __Bxor_f(x, m)          __bxor_f(x, m)
#define __Normw(x)              __normw(x)
#define __Normw_f(x)            __normw_f(x)
#define __Norm(x)               __norm(x)
#define __Norm_f(x)             __norm_f(x)
#define __Swap(a)               __swap(a)
#define __Swap_f(a)             __swap_f(a)
#define __Sat16(a)              __sat16(a)
#define __Sat16_f(a)            __sat16_f(a)
#define __Rnd16(a)              __rnd16(a)
#define __Rnd16_f(a)            __rnd16_f(a)
#define __Divaw(src1, src2)     __divaw(src1, src2)
#define __Push(src)             __push(src)
#define __Pop()                 __pop()
#define __Subsdw(a, b)          __subsdw(a, b)
#define __Addsdw(a, b)          __addsdw(a, b)

#define __Mulflw_0(src1, src2)      __mulflw_0(src1, src2)
#define __Mulflw_f_0(src1, src2)    __mulflw_f_0(src1, src2)
#define __Mulflw(src1, src2)        __mulflw(src1, src2)
#define __Mulflw_f(src1, src2)      __mulflw_f(src1, src2)
#define __Macflw_0(src1, src2)      __macflw_0(src1, src2)
#define __Macflw_f_0(src1, src2)    __macflw_f_0(src1, src2)
#define __Macflw(src1, src2)        __macflw(src1, src2)
#define __Macflw_f(src1, src2)      __macflw_f(src1, src2)
#define __Mulhflw_0(src1, src2)     __mulhflw_0(src1, src2)
#define __Mulhflw_f_0(src1, src2)   __mulhflw_f_0(src1, src2)
#define __Mulhflw(src1, src2)       __mulhflw(src1, src2)
#define __Mulhflw_f(src1, src2)     __mulhflw_f(src1, src2)
#define __Machflw_0(src1, src2)     __machflw_0(src1, src2)
#define __Machflw_f_0(src1, src2)   __machflw_f_0(src1, src2)
#define __Machflw(src1, src2)       __machflw(src1, src2)
#define __Machflw_f(src1, src2)     __machflw_f(src1, src2)
#define __Mullw_0(src1, src2)       __mullw_0(src1, src2)
#define __Mullw_f_0(src1, src2)     __mullw_f_0(src1, src2)
#define __Mullw(src1, src2)         __mullw(src1, src2)
#define __Mululw_0(src1, src2)        __mululw_0(src1, src2)
#define __Mululw(src1, src2)        __mululw(src1, src2)
#define __Mullw_f(src1, src2)       __mullw_f(src1, src2)
#define __Mulhlw_0(src1, src2)      __mulhlw_0(src1, src2)
#define __Mulhlw_f_0(src1, src2)    __mulhlw_f_0(src1, src2)
#define __Mulhlw(src1, src2)        __mulhlw(src1, src2)
#define __Mulhlw_f(src1, src2)      __mulhlw_f(src1, src2)
#define __Maclw_0(src1, src2)       __maclw_0(src1, src2)
#define __Maclw_f_0(src1, src2)     __maclw_f_0(src1, src2)
#define __Maclw(src1, src2)         __maclw(src1, src2)
#define __Maclw_f(src1, src2)       __maclw_f(src1, src2)
#define __Machlw_0(src1, src2)      __machlw_0(src1, src2)
#define __Machlw_f_0(src1, src2)    __machlw_f_0(src1, src2)
#define __Machlw(src1, src2)        __machlw(src1, src2)
#define __Machlw_f(src1, src2)      __machlw_f(src1, src2)
#define __Machulw(src1, src2)       __machulw(src1, src2)
#define __Machulw_f(src1, src2)     __machulw_f(src1, src2)
#define __Machulw_0(src1, src2)     __machulw_0(src1, src2)
#define __Machulw_f_0(src1, src2)   __machulw_f_0(src1, src2)
#define __Muldw(src1, src2)         __muldw(src1, src2)
#define __Muldw_0(src1, src2)       __muldw_0(src1, src2)
#define __Mulrdw(src1, src2)        __mulrdw(src1, src2)
#define __Macdw(src1, src2)         __macdw(src1, src2)
#define __Macdw_0(src1, src2)       __macdw_0(src1, src2)
#define __Msubdw_0(src1, src2)      __msubdw_0(src1, src2)

#define __Get_ACC1()                __get_ACC1()
#define __Get_ACC2()                __get_ACC2()

/* AndreiMi */
#define __Get_ACC1_H()              __get_ACC1_H()
#define __Get_ACC2_H()              __get_ACC2_H()

#define __Get_AAh()                 __get_AAh()
#define __Get_AAl()                 __get_AAl()

/* Simeon */
#define __get_AUX_XMAC0_24()          __get_AUX_XMAC0_24()
#define __get_AUX_XMAC1_24()          __get_AUX_XMAC1_24()
#define __get_AUX_XMAC2_24()          __get_AUX_XMAC2_24()

#define __Ax0()    __ax0()
#define __Ax1()    __ax1()
#define __Ax2()    __ax2()
#define __Ax3()    __ax3()

#define __Ay0()    __ay0()
#define __Ay1()    __ay1()
#define __Ay2()    __ay2()
#define __Ay3()    __ay3()

#define __Set_ax0(a)       __set_ax0(a)
#define __Set_ax1(a)       __set_ax1(a)
#define __Set_ax2(a)       __set_ax2(a)
#define __Set_ax3(a)       __set_ax3(a)

#define __Set_ay0(a)       __set_ay0(a)
#define __Set_ay1(a)       __set_ay1(a)
#define __Set_ay2(a)       __set_ay2(a)
#define __Set_ay3(a)       __set_ay3(a)

#define __Mx00()   __mx00()
#define __Mx01()   __mx01()
#define __Mx10()   __mx10()
#define __Mx11()   __mx11()
#define __Mx20()   __mx20()
#define __Mx21()   __mx21()
#define __Mx30()   __mx30()
#define __Mx31()   __mx31()

#define __My00()   __my00()
#define __My01()   __my01()
#define __My10()   __my10()
#define __My11()   __my11()
#define __My20()   __my20()
#define __My21()   __my21()
#define __My30()   __my30()
#define __My31()   __my31()

#define __Set_mx00(a)   __set_mx00(a)
#define __Set_mx01(a)   __set_mx01(a)
#define __Set_mx10(a)   __set_mx10(a)
#define __Set_mx11(a)   __set_mx11(a)
#define __Set_mx20(a)   __set_mx20(a)
#define __Set_mx21(a)   __set_mx21(a)
#define __Set_mx30(a)   __set_mx30(a)
#define __Set_mx31(a)   __set_mx31(a)

#define __Set_my00(a)   __set_my00(a)
#define __Set_my01(a)   __set_my01(a)
#define __Set_my10(a)   __set_my10(a)
#define __Set_my11(a)   __set_my11(a)
#define __Set_my20(a)   __set_my20(a)
#define __Set_my21(a)   __set_my21(a)
#define __Set_my30(a)   __set_my30(a)
#define __Set_my31(a)   __set_my31(a)

#define __X0_u0()      __x0_u0()
#define __X0_u1()      __x0_u1()
#define __X0_nu()      __x0_nu()
#define __X1_u0()      __x1_u0()
#define __X1_u1()      __x1_u1()
#define __X1_nu()      __x1_nu()
#define __X2_u0()      __x2_u0()
#define __X2_u1()      __x2_u1()
#define __X2_nu()      __x2_nu()
#define __X3_u0()      __x3_u0()
#define __X3_u1()      __x3_u1()
#define __X3_nu()      __x3_nu()
#define __Y0_u0()      __y0_u0()
#define __Y0_u1()      __y0_u1()
#define __Y0_nu()      __y0_nu()
#define __Y1_u0()      __y1_u0()
#define __Y1_u1()      __y1_u1()
#define __Y1_nu()      __y1_nu()
#define __Y2_u0()      __y2_u0()
#define __Y2_u1()      __y2_u1()
#define __Y2_nu()      __y2_nu()
#define __Y3_u0()      __y3_u0()
#define __Y3_u1()      __y3_u1()
#define __Y3_nu()      __y3_nu()

#define __Set_x0_u0(x)  __set_x0_u0(x)
#define __Set_x0_u1(x)  __set_x0_u1(x)
#define __Set_x0_nu(x)  __set_x0_nu(x)
#define __Set_x1_u0(x)  __set_x1_u0(x)
#define __Set_x1_u1(x)  __set_x1_u1(x)
#define __Set_x1_nu(x)  __set_x1_nu(x)
#define __Set_x2_u0(x)  __set_x2_u0(x)
#define __Set_x2_u1(x)  __set_x2_u1(x)
#define __Set_x2_nu(x)  __set_x2_nu(x)
#define __Set_x3_u0(x)  __set_x3_u0(x)
#define __Set_x3_u1(x)  __set_x3_u1(x)
#define __Set_x3_nu(x)  __set_x3_nu(x)

#define __Set_y0_u0(x)  __set_y0_u0(x)
#define __Set_y0_u1(x)  __set_y0_u1(x)
#define __Set_y0_nu(x)  __set_y0_nu(x)
#define __Set_y1_u0(x)  __set_y1_u0(x)
#define __Set_y1_u1(x)  __set_y1_u1(x)
#define __Set_y1_nu(x)  __set_y1_nu(x)
#define __Set_y2_u0(x)  __set_y2_u0(x)
#define __Set_y2_u1(x)  __set_y2_u1(x)
#define __Set_y2_nu(x)  __set_y2_nu(x)
#define __Set_y3_u0(x)  __set_y3_u0(x)
#define __Set_y3_u1(x)  __set_y3_u1(x)
#define __Set_y3_nu(x)  __set_y3_nu(x)

#endif // !ARC600_INTRINSICS_ONLY

_Asm uint32_t __Ax0()
{
    lr    %r0, [%ax0]
}

_Asm void __Set_ax0(unsigned n)
{
    %reg n

    sr    n, [%ax0]
}

_Asm uint32_t __Mx00()
{
    lr    %r0, [%mx00]
}

_Asm void __Set_mx00(uint32_t m)
{
    %reg m

    sr    m, [%mx00]
}

_Asm uint32_t __Mx01()
{
    lr    %r0, [%mx01]
}

_Asm void __Set_mx01(uint32_t m)
{
    %reg m

    sr    m, [%mx01]
}

_Asm uint32_t __Ax1()
{
    lr    %r0, [%ax1]
}

_Asm void __Set_ax1(unsigned n)
{
    %reg n

    sr    n, [%ax1]
}

_Asm uint32_t __Mx10()
{
    lr    %r0, [%mx10]
}

_Asm void __Set_mx10(uint32_t m)
{
    %reg m

    sr    m, [%mx10]
}

_Asm uint32_t __Mx11()
{
    lr    %r0, [%mx11]
}

_Asm void __Set_mx11(uint32_t m)
{
    %reg m

    sr    m, [%mx11]
}

_Asm uint32_t __Ax2()
{
    lr    %r0, [%ax2]
}

_Asm void __Set_ax2(unsigned n)
{
    %reg n

    sr    n, [%ax2]
}

_Asm uint32_t __Mx20()
{
    lr    %r0, [%mx20]
}

_Asm void __Set_mx20(uint32_t m)
{
    %reg m

    sr    m, [%mx20]
}

_Asm uint32_t __Mx21()
{
    lr    %r0, [%mx21]
}

_Asm void __Set_mx21(uint32_t m)
{
    %reg m

    sr    m, [%mx21]
}

_Asm uint32_t __Ax3()
{
    lr    %r0, [%ax3]
}

_Asm void __Set_ax3(unsigned n)
{
    %reg n

    sr    n, [%ax3]
}

_Asm uint32_t __Mx30()
{
    lr    %r0, [%mx30]
}

_Asm void __Set_mx30(uint32_t m)
{
    %reg m

    sr    m, [%mx30]
}

_Asm uint32_t __Mx31()
{
    lr    %r0, [%mx31]
}

_Asm void __Set_mx31(uint32_t m)
{
    %reg m

    sr    m, [%mx31]
}

_Asm uint32_t __Ay0()
{
    lr    %r0, [%ay0]
}

_Asm void __Set_ay0(unsigned n)
{
    %reg n

    sr    n, [%ay0]
}

_Asm uint32_t __My00()
{
    lr    %r0, [%my00]
}

_Asm void __Set_my00(uint32_t m)
{
    %reg m

    sr    m, [%my00]
}

_Asm uint32_t __My01()
{
    lr    %r0, [%my01]
}

_Asm void __Set_my01(uint32_t m)
{
    %reg m

    sr    m, [%my01]
}

_Asm uint32_t __Ay1()
{
    lr    %r0, [%ay1]
}

_Asm void __Set_ay1(unsigned n)
{
    %reg n

    sr    n, [%ay1]
}

_Asm uint32_t __My10()
{
    lr    %r0, [%my10]
}

_Asm void __Set_my10(uint32_t m)
{
    %reg m

    sr    m, [%my10]
}

_Asm uint32_t __My11()
{
    lr    %r0, [%my11]
}

_Asm void __Set_my11(uint32_t m)
{
    %reg m

    sr    m, [%my11]
}

_Asm uint32_t __Ay2()
{
    lr    %r0, [%ay2]
}

_Asm void __Set_ay2(unsigned n)
{
    %reg n

    sr    n, [%ay2]
}

_Asm uint32_t __My20()
{
    lr    %r0, [%my20]
}

_Asm void __Set_my20(uint32_t m)
{
    %reg m

    sr    m, [%my20]
}

_Asm uint32_t __My21()
{
    lr    %r0, [%my21]
}

_Asm void __Set_my21(uint32_t m)
{
    %reg m

    sr    m, [%my21]
}

_Asm uint32_t __Ay3()
{
    lr    %r0, [%ay3]
}

_Asm void __Set_ay3(unsigned n)
{
    %reg n

    sr    n, [%ay3]
}

_Asm uint32_t __My30()
{
    lr    %r0, [%my30]
}

_Asm void __Set_my30(uint32_t m)
{
    %reg m

    sr    m, [%my30]
}

_Asm uint32_t __My31()
{
    lr    %r0, [%my31]
}

_Asm void __Set_my31(uint32_t m)
{
    %reg m

    sr    m, [%my31]
}

//
// Aux routines
//

_Asm void push_all_regs()
{
    push    %r0
    push    %r1
    push    %r2
    push    %r3
    push    %r4
    push    %r5
    push    %r6
    push    %r7
    push    %r8
    push    %r9
    push    %r10
    push    %r11
    push    %r12
    push    %r13
    push    %r14
    push    %r15
    push    %r16
    push    %r17
    push    %r18
    push    %r19
    push    %r20
    push    %r21
    push    %r22
    push    %r23
    push    %r24
    push    %r25
}

_Asm void pop_all_regs()
{
    pop     %r25
    pop     %r24
    pop     %r23
    pop     %r22
    pop     %r21
    pop     %r20
    pop     %r19
    pop     %r18
    pop     %r17
    pop     %r16
    pop     %r15
    pop     %r14
    pop     %r13
    pop     %r12
    pop     %r11
    pop     %r10
    pop     %r9
    pop     %r8
    pop     %r7
    pop     %r6
    pop     %r5
    pop     %r4
    pop     %r3
    pop     %r2
    pop     %r1
    pop     %r0
}

///////////////////////////////////////////////////////////////////////////////
// Filling xy memory with a value
//
_Asm void _SetXMem(uint32_t dest, int32_t val, int n)
{
    %reg dest, val, n
    %lab _loop_start, _loop_end

    mov     %lp_count, n

    push    n

    // Save mx00 and ax0
    lr      n, [%ax0]
    push    n
    lr      n, [%mx00]
    push    n

    sr      dest, [%ax0]
    sr      1, [%mx00]

    mov     n, _loop_start
    sr      n, [0x2]
    mov     n, _loop_end
    sr      n, [0x3]
    nop
    nop
_loop_start:
    mov     %x0_u0, val
_loop_end:

    pop     n
    sr      n, [%mx00]
    pop     n
    sr      n, [%ax0]

    nop

    pop     n
}

_Asm void _SetYMem(uint32_t dest, int32_t val, int n)
{
    %reg dest, val, n
    %lab _loop_start, _loop_end

    mov     %lp_count, n

    push    n

    // Save my00 and ay0
    lr      n, [%ay0]
    push    n
    lr      n, [%my00]
    push    n

    sr      dest, [%ay0]
    sr      1, [%my00]

    mov     n, _loop_start
    sr      n, [0x2]
    mov     n, _loop_end
    sr      n, [0x3]
    nop
    nop
_loop_start:
    mov     %y0_u0, val
_loop_end:

    pop     n
    sr      n, [%my00]
    pop     n
    sr      n, [%ay0]

    nop

    pop     n
}

_Asm void _BurstXMem_nowait(uint32_t dest, int32_t val, int n)
{
    %reg dest, val, n
    // Initiate bursting
    sr      dest, [0x9a]
    sr      val, [0x9C]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    or      %r10, %r10, 0x50000000
    sr      %r10, [0x9b]
}

_Asm void _BurstYMem_nowait(uint32_t dest, int32_t val, int n)
{
    %reg dest, val, n
    // Initiate bursting
    sr      dest, [0x9a]
    sr      val, [0x9C]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    or      %r10, %r10, 0x70000000
    sr      %r10, [0x9b]
}

_Asm void _BurstXYMem_nowait(uint32_t dest, int32_t val, int formatted_n)
{
    %reg dest, val, formatted_n

    // Initiate bursting
    sr      dest, [0x9a]
    sr      val, [0x9C]
    sr      0x100, [0x98]
    sr      formatted_n, [0x9b]
}

#ifdef BURST_WAIT_AT_BEGIN

_Asm void _BurstXMem(uint32_t dest, int32_t val, int n)
{
    %reg dest, val, n
    %lab _wait

    push    n

    // Wait till previous burst complete
    push    n
_wait:
    lr      n, [0x98]
    and.f   0, n, 0x10
    bne     _wait
    pop     n

    // Initiate bursting
    sr      dest, [0x9a]
    sr      val, [0x9C]
    sr      0x100, [0x98]
    asl     n, n, 2
    sub     n, n, 1
    or      n, n, 0x50000000
    sr      n, [0x9b]

    pop     n
}

_Asm void _BurstYMem(uint32_t dest, int32_t val, int n)
{
    %reg dest, val, n
    %lab _wait

    push    n

    // Wait till previous burst complete
    push    n
_wait:
    lr      n, [0x98]
    and.f   0, n, 0x10
    bne     _wait
    pop     n

    // Initiate bursting
    sr      dest, [0x9a]
    sr      val, [0x9C]
    sr      0x100, [0x98]
    asl     n, n, 2
    sub     n, n, 1
    or      n, n, 0x70000000
    sr      n, [0x9b]

    pop     n
}

#else // BURST_WAIT_AT_END

#ifdef    BURST_NO_ASM

static _Inline void _BurstXMem(uint32_t dest, int32_t val, int n) {

    _DISABLE_INT();
    // Initiate bursting
    _sr(dest,                      0x9a);
    _sr(val,                       0x9c);
    _sr(0x100,                     0x98);
    _sr((((n<<2)-1) | 0x50000000), 0x9b);

    // Wait till burst complete
    while (_lr(0x98) & 0x10);

    _ENABLE_INT();
} /* _BurstXMem */

static _Inline void _BurstYMem(uint32_t dest, int32_t val, int n) {

    _DISABLE_INT();
    
    // Initiate bursting
    _sr(dest,                      0x9a);
    _sr(val,                       0x9c);
    _sr(0x100,                     0x98);
    _sr((((n<<2)-1) | 0x70000000), 0x9b);

    // Wait till burst complete
    while (_lr(0x98) & 0x10);
    
    _ENABLE_INT();

} /* _BurstYMem */

#endif // BURST_NO_ASM

#endif // BURST_WAIT_AT_BEGIN

_Asm void _SetSMem(pint32_t dest, int32_t val, int n)
{
    %reg dest, val, n
    %lab _loop

    push    dest

    asr     %lp_count, n, 1
    lp      _loop
    st.ab   val, [dest, 4]
    st.ab   val, [dest, 4]
_loop:

    pop     dest
}

#ifdef BURST_WAIT_AT_BEGIN

_Asm void _BurstSMem(pint32_t dest, int32_t val, int n)
{
    %reg dest, val, n
    %lab _wait

    push    n

    // Wait till previous burst complete
    push    n
_wait:
    lr      n, [0x98]
    and.f   0, n, 0x10
    bne     _wait
    pop     n

    sr      dest, [0x99]
    sr      val, [0x9C]
    sr      0x100, [0x98]
    asl     n, n, 2
    sub     n, n, 1
    or      n, n, 0x10000000
    sr      n, [0x9b]

    pop     n
}

#else // BURST_WAIT_AT_END

#ifdef    BURST_NO_ASM

static _Inline void _BurstSMem(pint32_t dest, int32_t val, int n) {

    _DISABLE_INT();
    
    // Initiate bursting
    _sr((uint32_t)dest,            0x99);
    _sr(val,                       0x9c);
    _sr(0x100,                     0x98);
    _sr((((n<<2)-1) | 0x10000000), 0x9b);

    // Wait till burst complete
    while (_lr(0x98) & 0x10);
    
    _ENABLE_INT();

} /* _BurstSMem */

#endif // BURST_NO_ASM

#endif // BURST_WAIT_AT_BEGIN

///////////////////////////////////////////////////////////////////////////////
// Copying from system memory to xy memory
//
_Asm void _CopySMemToXMem16(uint32_t dest, const pint16_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    sr      dest, [%ax0]
    sr      (1 << 29) + 1, [%mx00]

    mov     %lp_count, n

    lp      _loop
    ldw.ab   %r10, [src, 2]
    asl     %x0_u0, %r10, 16
_loop:

}

_Asm void _CopySMemToYMem16(uint32_t dest, const pint16_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    src

    // Save my00 and ay0
    lr      n, [%ay0]
    push    n
    lr      n, [%my00]
    push    n

    sr      dest, [%ay0]
    sr      (1 << 29) + 1, [%my00]

    nop
    nop

    lp      _loop
    ldw.ab   n, [src, 2]
    asl     %y0_u0, n, 16
_loop:

    pop     n
    sr      n, [%my00]
    pop     n
    sr      n, [%ay0]

    pop     src
    pop     n
}

_Asm void _CopySMemToXMem32(uint32_t dest, const pint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    src

    // Save mx00 and ax0
    lr      n, [%ax0]
    push    n
    lr      n, [%mx00]
    push    n

    sr      dest, [%ax0]
    sr      1, [%mx00]

    nop
    nop

    lp      _loop
    ld.ab   n, [src, 4]
    mov     %x0_u0, n
_loop:

    pop     n
    sr      n, [%mx00]
    pop     n
    sr      n, [%ax0]

    pop     src
    pop     n
}

_Asm void _CopySMemToYMem32(uint32_t dest, const pint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    src

    // Save my00 and ay0
    lr      n, [%ay0]
    push    n
    lr      n, [%my00]
    push    n

    sr      dest, [%ay0]
    sr      1, [%my00]

    nop
    nop

    lp      _loop
    ld.ab   n, [src, 4]
    mov     %y0_u0, n
_loop:

    pop     n
    sr      n, [%my00]
    pop     n
    sr      n, [%ay0]

    pop     src
    pop     n
}

_Asm void _CopySMemToXMem16_CacheBypass(uint32_t dest, const pint16_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    src

    // Save mx00 and ax0
    lr      n, [%ax0]
    push    n
    lr      n, [%mx00]
    push    n

    sr      dest, [%ax0]
    sr      (1 << 29) + 1, [%mx00]

    nop
    nop

    lp      _loop
    ldw.ab.di n, [src, 2]
    asl     %x0_u0, n, 16
_loop:

    pop     n
    sr      n, [%mx00]
    pop     n
    sr      n, [%ax0]

    pop     src
    pop     n
}

_Asm void _CopySMemToYMem16_CacheBypass(uint32_t dest, const pint16_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    src

    // Save my00 and ay0
    lr      n, [%ay0]
    push    n
    lr      n, [%my00]
    push    n

    sr      dest, [%ay0]
    sr      (1 << 29) + 1, [%my00]

    nop
    nop

    lp      _loop
    ldw.ab.di n, [src, 2]
    asl     %y0_u0, n, 16
_loop:

    pop     n
    sr      n, [%my00]
    pop     n
    sr      n, [%ay0]

    pop     src
    pop     n
}

_Asm void _CopySMemToXMem32_CacheBypass(uint32_t dest, const pint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    src

    // Save mx00 and ax0
    lr      n, [%ax0]
    push    n
    lr      n, [%mx00]
    push    n

    sr      dest, [%ax0]
    sr      1, [%mx00]

    nop
    nop

    lp      _loop
    ld.ab.di n, [src, 4]
    mov     %x0_u0, n
_loop:

    pop     n
    sr      n, [%mx00]
    pop     n
    sr      n, [%ax0]

    pop     src
    pop     n
}

_Asm void _CopySMemToYMem32_CacheBypass(uint32_t dest, const pint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    src

    // Save my00 and ay0
    lr      n, [%ay0]
    push    n
    lr      n, [%my00]
    push    n

    sr      dest, [%ay0]
    sr      1, [%my00]

    nop
    nop

    lp      _loop
    ld.ab.di n, [src, 4]
    mov     %y0_u0, n
_loop:

    pop     n
    sr      n, [%my00]
    pop     n
    sr      n, [%ay0]

    pop     src
    pop     n
}

_Asm void _BurstSMemToXMem_nowait(unsigned dest, const pint32_t src, int n)
{
    %reg dest, src, n

    // Initiate bursting
    sr      dest, [0x9a]
    sr      src, [0x99]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    or      %r10, %r10, 0x40000000
    sr      %r10, [0x9b]
}

_Asm void _BurstSMemToYMem_nowait(unsigned dest, const pint32_t src, int n)
{
    %reg dest, src, n

    // Initiate bursting
    sr      dest, [0x9a]
    sr      src, [0x99]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    or      %r10, %r10, 0x60000000
    sr      %r10, [0x9b]
}

_Asm void _BurstSMemToAny_nowait(unsigned dest, const pint32_t src, int formatted_n)
{
    %reg dest, src, formatted_n

    // Initiate bursting
    sr      dest, [0x9a]
    sr      src, [0x99]
    sr      0x100, [0x98]
    sr      formatted_n, [0x9b]
}

#ifdef BURST_WAIT_AT_BEGIN

_Asm _CC(_SAVE_ALL_REGS) void _BurstSMemToXMem(unsigned dest, const pint32_t src, int n) {

%con dest, n; reg src; lab _wait;

    ; Wait till burst complete

_wait:

    lr          %r10,  [0x98]
    and.f       0,      %r10,   0x10
    bne     _wait

    ; Initiate bursting

    sr          dest,  [0x9a]
    sr          src,   [0x99]
    sr          0x100, [0x98]
    sr          (((n<<2)-1) | 0x40000000), [0x9b]

%con n; reg dest, src; lab _wait;

    ; Wait till burst complete

_wait:

    lr          %r10,  [0x98]
    and.f       0,      %r10,   0x10
    bne     _wait

    ; Initiate bursting

    sr          dest,  [0x9a]
    sr          src,   [0x99]
    sr          0x100, [0x98]
    sr          (((n<<2)-1) | 0x40000000), [0x9b]

%reg dest, src, n; lab _wait;

    ; Wait till burst complete

_wait:

    lr          %r10,  [0x98]
    and.f       0,      %r10,   0x10
    bne     _wait

    ; Initiate bursting

    sr          dest,  [0x9a]
    sr          src,   [0x99]
    sr          0x100, [0x98]
    asl         %r10,   n,      2
    sub         %r10,   %r10,   1
    or          %r10,   %r10,   0x40000000
    sr          %r10,  [0x9b]

%error

} /* _BurstSMemToXMem */

_Asm _CC(_SAVE_ALL_REGS) void _BurstSMemToYMem(unsigned dest, const pint32_t src, int n)
{
%con dest, n; reg src; lab _wait

_wait:

    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

    ; Initiate bursting
    sr      dest, [0x9a]
    sr      src, [0x99]
    sr      0x100, [0x98]
    sr      (((n<<2)-1) | 0x60000000), [0x9b]

    ; Wait till burst complete

%con n; reg dest, src; lab _wait

_wait:

    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

    ; Initiate bursting
    sr      dest, [0x9a]
    sr      src, [0x99]
    sr      0x100, [0x98]
    sr      (((n<<2)-1) | 0x60000000), [0x9b]

    ; Wait till burst complete

%reg dest, src, n; lab _wait

_wait:

    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

    ; Initiate bursting
    sr      dest, [0x9a]
    sr      src, [0x99]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    or      %r10, %r10, 0x60000000
    sr      %r10, [0x9b]

    ; Wait till burst complete

%error

} /* _BurstSMemToYMem */

#else // BURST_WAIT_AT_END

#ifdef    BURST_NO_ASM

static _Inline void _BurstSMemToXMem(unsigned dest, const pint32_t src, int n) {

    _DISABLE_INT();
    
    // Initiate bursting
    _sr(dest,                      0x9a);
    _sr((uint32_t)src,             0x99);
    _sr(0x100,                     0x98);
    _sr((((n<<2)-1) | 0x40000000), 0x9b);

    // Wait till burst complete
    while (_lr(0x98) & 0x10);
    
    _ENABLE_INT();

} /* _BurstSMemToXMem */

static _Inline void _BurstSMemToYMem(unsigned dest, const pint32_t src, int n) {

    _DISABLE_INT();
    
    // Initiate bursting
    _sr(dest,                      0x9a);
    _sr((uint32_t)src,             0x99);
    _sr(0x100,                     0x98);
    _sr((((n<<2)-1) | 0x60000000), 0x9b);

    // Wait till burst complete
    while (_lr(0x98) & 0x10);
    
    _ENABLE_INT();
    

} /* _BurstSMemToYMem */

#else // !BURST_NO_ASM

_Asm _CC(_SAVE_ALL_REGS) void _BurstSMemToXMem(unsigned dest, const pint32_t src, int n) {

%con dest, n; reg src; lab _wait;

    ; Initiate bursting

    sr          dest,  [0x9a]
    sr          src,   [0x99]
    sr          0x100, [0x98]
    sr          (((n<<2)-1) | 0x40000000), [0x9b]

    ; Wait till burst complete

_wait:

    lr          %r10,  [0x98]
    and.f       0,      %r10,   0x10
    bne     _wait

%con n; reg dest, src; lab _wait;

    ; Initiate bursting

    sr          dest,  [0x9a]
    sr          src,   [0x99]
    sr          0x100, [0x98]
    sr          (((n<<2)-1) | 0x40000000), [0x9b]

    ; Wait till burst complete

_wait:

    lr          %r10,  [0x98]
    and.f       0,      %r10,   0x10
    bne     _wait

%reg dest, src, n; lab _wait;

    ; Initiate bursting

    sr          dest,  [0x9a]
    sr          src,   [0x99]
    sr          0x100, [0x98]
    asl         %r10,   n,      2
    sub         %r10,   %r10,   1
    or          %r10,   %r10,   0x40000000
    sr          %r10,  [0x9b]

    ; Wait till burst complete

_wait:

    lr          %r10,  [0x98]
    and.f       0,      %r10,   0x10
    bne     _wait

%error

} /* _BurstSMemToXMem */

_Asm _CC(_SAVE_ALL_REGS) void _BurstSMemToYMem(unsigned dest, const pint32_t src, int n)
{
%con dest, n; reg src; lab _wait

    ; Initiate bursting
    sr      dest, [0x9a]
    sr      src, [0x99]
    sr      0x100, [0x98]
    sr      (((n<<2)-1) | 0x60000000), [0x9b]

    ; Wait till burst complete

_wait:

    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

%con n; reg dest, src; lab _wait

    ; Initiate bursting
    sr      dest, [0x9a]
    sr      src, [0x99]
    sr      0x100, [0x98]
    sr      (((n<<2)-1) | 0x60000000), [0x9b]

    ; Wait till burst complete

_wait:

    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

%reg dest, src, n; lab _wait

    ; Initiate bursting
    sr      dest, [0x9a]
    sr      src, [0x99]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    or      %r10, %r10, 0x60000000
    sr      %r10, [0x9b]

    ; Wait till burst complete

_wait:

    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

%error

} /* _BurstSMemToYMem */

#endif // BURST_NO_ASM

#endif // BURST_WAIT_AT_BEGIN

_Asm void _UnpackSMemToXMem(unsigned dest, const pint32_t src, int n)
{
    %reg dest, src, n
    %lab _wait

    push    n

    breq n, 0, 1f

    and %r10, src, 0xFFFFFFFC
    sr %r10, [0x4C]
    add1 %r10, src, n
    add  %r10, %r10, n
    and  %r10, %r10, 0xFFFFFFFC
    sr   %r10, [0x4C]

    // Initiate bursting
    sr      dest, [0x9a]
    sr      src, [0x99]
    sr      0x100, [0x98]
    asl     n, n, 2
    sub     n, n, 1
    or      n, n, 0x40000000
    or      n, n, 0x00080000
    sr      n, [0x9b]

    // Wait till burst complete
_wait:
    lr      n, [0x98]
    and.f   0, n, 0x10
    bne     _wait
1:
    pop     n
}



_Asm void _UnpackSMemToYMem(unsigned dest, const pint32_t src, int n)
{
    %reg dest, src, n
    %lab _wait

    push    n

    breq n, 0, 1f

    and %r10, src, 0xFFFFFFFC
    sr %r10, [0x4C]
    add1 %r10, src, n
    add  %r10, %r10, n
    and  %r10, %r10, 0xFFFFFFFC
    sr   %r10, [0x4C]

    // Initiate bursting
    sr      dest, [0x9a]
    sr      src, [0x99]
    sr      0x100, [0x98]
    asl     n, n, 2
    sub     n, n, 1
    or      n, n, 0x60000000
    or      n, n, 0x00080000
    sr      n, [0x9b]

    // Wait till burst complete
_wait:
    lr      n, [0x98]
    and.f   0, n, 0x10
    bne     _wait
1:
    pop     n
}


_Asm void _PackXMemToSMem(pint32_t dest, const unsigned src, int n)
{
    %reg dest, src, n
    %lab _wait

    push    n

    breq n, 0, 1f

    and %r10, dest, 0xFFFFFFFC
    sr %r10, [0x4C]
    sr %r10, [0x4A]
    add1 %r10, dest, n
    add  %r10, %r10, n
    and  %r10, %r10, 0xFFFFFFFC
    sr   %r10, [0x4C]
    sr   %r10, [0x4A]

    // Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    asl     n, n, 2
    sub     n, n, 1
    or      n, n, 0x00080000
    sr      n, [0x9b]

    // Wait till burst complete
_wait:
    lr      n, [0x98]
    and.f   0, n, 0x10
    bne     _wait
1:
    pop     n
}

_Asm void _PackYMemToSMem(pint32_t dest, const unsigned src, int n)
{
    %reg dest, src, n
    %lab _wait

    push    n

    breq n, 0, 1f

    and %r10, dest, 0xFFFFFFFC
    sr %r10, [0x4C]
    sr %r10, [0x4A]
    add1 %r10, dest, n
    add  %r10, %r10, n
    and  %r10, %r10, 0xFFFFFFFC
    sr   %r10, [0x4C]
    sr   %r10, [0x4A]

    // Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    asl     n, n, 2
    sub     n, n, 1
    or      n, n, 0x20000000
    or      n, n, 0x00080000
    sr      n, [0x9b]

    // Wait till burst complete
_wait:
    lr      n, [0x98]
    and.f   0, n, 0x10
    bne     _wait

1:
    pop     n
}


_Asm void _CopyXMemToSMem16(pint16_t dest, uint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    sr      src, [%ax0]
    sr      (1 << 29) + 1, [%mx00]

    mov     %lp_count, n

    lp      _loop
    lsr     %r10, %x0_u0, 16
    stw.ab  %r10, [dest, 2]
_loop:

}

_Asm void _CopyYMemToSMem16(pint16_t dest, uint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    dest

    // Save my00 and ay0
    lr      n, [%ay0]
    push    n
    lr      n, [%my00]
    push    n

    sr      src, [%ay0]
    sr      (1 << 29) + 1, [%my00]

    nop
    nop

    lp      _loop
    asr     n, %y0_u0, 16
    and     n, n, 0xFFFF
    stw.ab  n, [dest, 2]
_loop:

    pop     n
    sr      n, [%my00]
    pop     n
    sr      n, [%ay0]

    pop     dest
    pop     n
}

_Asm void _CopyXMemToSMem32(pint32_t dest, uint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    dest

    // Save mx00 and ax0
    lr      n, [%ax0]
    push    n
    lr      n, [%mx00]
    push    n

    sr      src, [%ax0]
    sr      1, [%mx00]

    nop
    nop

    lp      _loop
    mov     n, %x0_u0
    st.ab   n, [dest, 4]
_loop:

    pop     n
    sr      n, [%mx00]
    pop     n
    sr      n, [%ax0]

    pop     dest
    pop     n
}

_Asm void _CopyYMemToSMem32(pint32_t dest, uint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    sr      src, [%ay0]
    sr      1, [%my00]

    mov     %lp_count, n

    lp      _loop
    mov     %r10, %y0_u0
    st.ab   %r10, [dest, 4]
_loop:

}

_Asm void _CopyXMemToSMem16_CacheBypass(pint16_t dest, uint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    dest

    // Save mx00 and ax0
    lr      n, [%ax0]
    push    n
    lr      n, [%mx00]
    push    n

    sr      src, [%ax0]
    sr      (1 << 29) + 1, [%mx00]

    nop
    nop

    lp      _loop
    asr     n, %x0_u0, 16
    and     n, n, 0xFFFF
    stw.ab.di n, [dest, 2]
_loop:

    pop     n
    sr      n, [%mx00]
    pop     n
    sr      n, [%ax0]

    pop     dest
    pop     n
}

_Asm void _CopyYMemToSMem16_CacheBypass(pint16_t dest, uint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    dest

    // Save my00 and ay0
    lr      n, [%ay0]
    push    n
    lr      n, [%my00]
    push    n

    sr      src, [%ay0]
    sr      (1 << 29) + 1, [%my00]

    nop
    nop

    lp      _loop
    asr     n, %x0_u0, 16
    and     n, n, 0xFFFF
    stw.ab.di n, [dest, 2]
_loop:

    pop     n
    sr      n, [%my00]
    pop     n
    sr      n, [%ay0]

    pop     dest
    pop     n
}

_Asm void _CopyXMemToSMem32_CacheBypass(pint32_t dest, uint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    dest

    // Save mx00 and ax0
    lr      n, [%ax0]
    push    n
    lr      n, [%mx00]
    push    n

    sr      src, [%ax0]
    sr      1, [%mx00]

    nop
    nop

    lp      _loop
    mov     n, %x0_u0
    st.ab.di n, [dest, 4]
_loop:

    pop     n
    sr      n, [%mx00]
    pop     n
    sr      n, [%ax0]

    pop     dest
    pop     n
}

_Asm void _CopyYMemToSMem32_CacheBypass(pint32_t dest, uint32_t src, int n)
{
    %reg dest, src, n
    %lab _loop

    mov     %lp_count, n

    push    n
    push    dest

    // Save my00 and ay0
    lr      n, [%ay0]
    push    n
    lr      n, [%my00]
    push    n

    sr      src, [%ay0]
    sr      1, [%my00]

    nop
    nop

    lp      _loop
    mov     n, %y0_u0
    st.ab.di n, [dest, 4]
_loop:

    pop     n
    sr      n, [%my00]
    pop     n
    sr      n, [%ay0]

    pop     dest
    pop     n
}

_Asm void _BurstXMemToSMem_nowait(pint32_t dest, const unsigned src, int n)
{
    %reg dest, src, n
    %lab _wait

    // Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    sr      %r10, [0x9b]
}

_Asm void _BurstYMemToSMem_nowait(pint32_t dest, const unsigned src, int n)
{
    %reg dest, src, n
    %lab _wait

    // Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    or      %r10, %r10, 0x20000000
    sr      %r10, [0x9b]
}

#ifdef BURST_WAIT_AT_BEGIN

_Asm _CC(_SAVE_ALL_REGS) void _BurstXMemToSMem(pint32_t dest, const unsigned src, int n)
{
%con src, n; reg dest; lab _wait

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    sr      ((n<<2)-1), [0x9b]

%con n; reg dest, src; lab _wait

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    sr      ((n<<2)-1), [0x9b]

%reg dest, src, n; lab _wait

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    sr      %r10, [0x9b]

%error

} /* _BurstXMemToSMem */

_Asm _CC(_SAVE_ALL_REGS) void _BurstYMemToSMem(pint32_t dest, const unsigned src, int n)
{
%con src, n; reg dest; lab _wait

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    sr      (((n<<2)-1) | 0x20000000), [0x9b]

%con n; reg dest, src; lab _wait

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    sr      (((n<<2)-1) | 0x20000000), [0x9b]

%reg dest, src, n; lab _wait

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    or      %r10, %r10, 0x20000000
    sr      %r10, [0x9b]

}

#else // BURST_WAIT_AT_END

#ifdef    BURST_NO_ASM

static _Inline void _BurstXMemToSMem(pint32_t dest, const unsigned src, int n) {

    _DISABLE_INT();
    
    // Initiate bursting
    _sr(src,                       0x9a);
    _sr((uint32_t)dest,            0x99);
    _sr(0x100,                     0x98);
    _sr((((n<<2)-1) | 0x00000000), 0x9b);

    // Wait till burst complete
    while (_lr(0x98) & 0x10);

    _ENABLE_INT();
    
} /* _BurstXMemToSMem */

static _Inline void _BurstYMemToSMem(pint32_t dest, const unsigned src, int n) {

    _DISABLE_INT();
    
    // Initiate bursting
    _sr(src,                       0x9a);
    _sr((uint32_t)dest,            0x99);
    _sr(0x100,                     0x98);
    _sr((((n<<2)-1) | 0x20000000), 0x9b);

    // Wait till burst complete
    while (_lr(0x98) & 0x10);
    
    _ENABLE_INT();
    

} /* _BurstYMemToSMem */

#else // !BURST_NO_ASM

_Asm _CC(_SAVE_ALL_REGS) void _BurstXMemToSMem(pint32_t dest, const unsigned src, int n)
{
%con src, n; reg dest; lab _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    sr      ((n<<2)-1), [0x9b]

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

%con n; reg dest, src; lab _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    sr      ((n<<2)-1), [0x9b]

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

%reg dest, src, n; lab _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    sr      %r10, [0x9b]

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

%error

} /* _BurstXMemToSMem */

_Asm _CC(_SAVE_ALL_REGS) void _BurstYMemToSMem(pint32_t dest, const unsigned src, int n)
{
%con src, n; reg dest; lab _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    sr      (((n<<2)-1) | 0x20000000), [0x9b]

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

%con n; reg dest, src; lab _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    sr      (((n<<2)-1) | 0x20000000), [0x9b]

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

%reg dest, src, n; lab _wait

    ; Initiate bursting
    sr      src, [0x9a]
    sr      dest, [0x99]
    sr      0x100, [0x98]
    asl     %r10, n, 2
    sub     %r10, %r10, 1
    or      %r10, %r10, 0x20000000
    sr      %r10, [0x9b]

    ; Wait till burst complete
_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait

}

#endif // BURST_NO_ASM

#endif // BURST_WAIT_AT_BEGIN

_Asm void _WaitTillBurstComplete()
{
    %lab _wait

_wait:
    lr      %r10, [0x98]
    and.f   0, %r10, 0x10
    bne     _wait
}

_Asm void InvalidateDCache()
{
    sr      1, [0x47]
    nop
    nop
}

_Asm void InvalidateDCacheChunk(void* addr, int size)
{
    %reg addr, size
    %lab _loop, _not_locked_error, _exit

    push    %r0
    push    %r1
    push    addr
    push    size
    push    %r3
    push    %r4

    // Check if D-cache is enabled and not bypassed
    lr      %r0, [0x48]
    btst    %r0, 0              // Check if cache is enabled
    bnz     _exit
    btst    %r0, 1              // Check if cache is not bypassed
    bnz     _exit

    // Iterate through the cache lines lying within the specified address range
    mov     %r0, 0

    add     %r1, addr, size
    lr      %r4, [0x72]         // Get cache line size
    asr     %r4, %r4, 16
    bmsk    %r4, %r4, 0xF
    asl     %r4, 16, %r4

_loop:
    sr      addr, [0x4A]        // Invalidate using addr contents
    lr      %r3, [0x48]         // Read control register
    and.f   0, %r3, (1 << 2)    // Was lock successful?
    jeq     _not_locked_error   // Not locked. Goto error
    add     addr, addr, %r4     // Move onto next line
    sub.f   0, addr, %r1        // Reached the end?
    blt     _loop               // Not complete. Continue

    mov     %r0, 1              // Indicate success

_not_locked_error:

_exit:

    pop     %r4
    pop     %r3
    pop     size
    pop     addr
    pop     %r1
    pop     %r0
}

_Asm void FlushDCache()
{
    sr      1, [0x4B]
    nop
    nop
}

_Asm void FlushDCacheChunk(void* addr, int size)
{
    %reg addr, size
    %lab _loop, _not_locked_error, _exit

    push    %r0
    push    %r1
    push    addr
    push    size
    push    %r3
    push    %r4

    // Check if D-cache is enabled and not bypassed
    lr      %r0, [0x48]
    btst    %r0, 0              // Check if cache is enabled
    bnz     _exit
    btst    %r0, 1              // Check if cache is not bypassed
    bnz     _exit

    // Iterate through the cache lines lying within the specified address range
    mov     %r0, 0

    add     %r1, addr, size
    lr      %r4, [0x72]         // Get cache line size
    asr     %r4, %r4, 16
    bmsk    %r4, %r4, 0xF
    asl     %r4, 16, %r4

_loop:
    sr      addr, [0x4C]        // Flush using addr contents
    lr      %r3, [0x48]         // Read control register
    and.f   0, %r3, (1 << 2)    // Was lock successful?
    jeq     _not_locked_error   // Not locked. Goto error
    add     addr, addr, %r4     // Move onto next line
    sub.f   0, addr, %r1        // Reached the end?
    blt     _loop               // Not complete. Continue

    mov     %r0, 1              // Indicate success

_not_locked_error:

_exit:

    pop     %r4
    pop     %r3
    pop     size
    pop     addr
    pop     %r1
    pop     %r0
}

_Asm void LockDCacheChunk(void* addr, int size)
{
    %reg addr, size
    %lab _loop, _not_locked_error, _exit

    push    %r0
    push    %r1
    push    addr
    push    size
    push    %r3
    push    %r4

    // Check if D-cache is enabled and not bypassed
    lr      %r0, [0x48]
    btst    %r0, 0              // Check if cache is enabled
    bnz     _exit
    btst    %r0, 1              // Check if cache is not bypassed
    bnz     _exit

    // Iterate through the cache lines lying within the specified address range
    mov     %r0, 0

    add     %r1, addr, size
    lr      %r4, [0x72]         // Get cache line size
    asr     %r4, %r4, 16
    bmsk    %r4, %r4, 0xF
    asl     %r4, 16, %r4

_loop:
    sr      addr, [0x49]        // Lock using addr contents
    lr      %r3, [0x48]         // Read control register
    and.f   0, %r3, (1 << 2)    // Was lock successful?
    jeq     _not_locked_error   // Not locked. Goto error
    add     addr, addr, %r4     // Move onto next line
    sub.f   0, addr, %r1        // Reached the end?
    blt     _loop               // Not complete. Continue

    mov     %r0, 1              // Indicate success

_not_locked_error:

_exit:

    pop     %r4
    pop     %r3
    pop     size
    pop     addr
    pop     %r1
    pop     %r0
}

#endif

///////////////////////////////////////////////////////////////////////////////
// Nested functions
///////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
//
// PC
//
#define __declare_nestedfunc1(name, t1, v1) \
    void name(t1* p##v1);
#define __declare_nestedfunc2(name, t1, v1, t2, v2) \
    void name(t1* p##v1, t2* p##v2);
#define __declare_nestedfunc3(name, t1, v1, t2, v2, t3, v3) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3);
#define __declare_nestedfunc4(name, t1, v1, t2, v2, t3, v3, t4, v4) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4);
#define __declare_nestedfunc5(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5);
#define __declare_nestedfunc6(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6);
#define __declare_nestedfunc7(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7);
#define __declare_nestedfunc8(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8);
#define __declare_nestedfunc9(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9);
#define __declare_nestedfunc10(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10);
#define __declare_nestedfunc11(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11);
#define __declare_nestedfunc12(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12);
#define __declare_nestedfunc13(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13);
#define __declare_nestedfunc14(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14);
#define __declare_nestedfunc15(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15);
#define __declare_nestedfunc16(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16);
#define __declare_nestedfunc17(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17);
#define __declare_nestedfunc18(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18);
#define __declare_nestedfunc19(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19);
#define __declare_nestedfunc20(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20);
#define __declare_nestedfunc21(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21);
#define __declare_nestedfunc22(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21, t22* p##v22);
#define __declare_nestedfunc23(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21, t22* p##v22, t23* p##v23);
#define __declare_nestedfunc24(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21, t22* p##v22, t23* p##v23, t24* p##v24);
#define __declare_nestedfunc25(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24, t25, v25) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21, t22* p##v22, t23* p##v23, t24* p##v24, t25* p##v25);
#define __declare_nestedfunc26(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24, t25, v25, t26, v26) \
    void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21, t22* p##v22, t23* p##v23, t24* p##v24, t25* p##v25, t26* p##v26);

#define __call_nestedfunc1(name, v1) \
    name(&v1);
#define __call_nestedfunc2(name, v1, v2) \
    name(&v1, &v2);
#define __call_nestedfunc3(name, v1, v2, v3) \
    name(&v1, &v2, &v3);
#define __call_nestedfunc4(name, v1, v2, v3, v4) \
    name(&v1, &v2, &v3, &v4);
#define __call_nestedfunc5(name, v1, v2, v3, v4, v5) \
    name(&v1, &v2, &v3, &v4, &v5);
#define __call_nestedfunc6(name, v1, v2, v3, v4, v5, v6) \
    name(&v1, &v2, &v3, &v4, &v5, &v6);
#define __call_nestedfunc7(name, v1, v2, v3, v4, v5, v6, v7) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7);
#define __call_nestedfunc8(name, v1, v2, v3, v4, v5, v6, v7, v8) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8);
#define __call_nestedfunc9(name, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9);
#define __call_nestedfunc10(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10);
#define __call_nestedfunc11(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11);
#define __call_nestedfunc12(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12);
#define __call_nestedfunc13(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13);
#define __call_nestedfunc14(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14);
#define __call_nestedfunc15(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15);
#define __call_nestedfunc16(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16);
#define __call_nestedfunc17(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17);
#define __call_nestedfunc18(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18);
#define __call_nestedfunc19(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18, &v19);
#define __call_nestedfunc20(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18, &v19, &v20);
#define __call_nestedfunc21(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18, &v19, &v20, &v21);
#define __call_nestedfunc22(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18, &v19, &v20, &v21, &v22);
#define __call_nestedfunc23(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18, &v19, &v20, &v21, &v22, &v23);
#define __call_nestedfunc24(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18, &v19, &v20, &v21, &v22, &v23, &v24);
#define __call_nestedfunc25(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18, &v19, &v20, &v21, &v22, &v23, &v24, &v25);
#define __call_nestedfunc26(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) \
    name(&v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18, &v19, &v20, &v21, &v22, &v23, &v24, &v25, &v26);

#define __nestedfunc_start1(name, t1, v1) \
    } void name(t1* p##v1) { \
    t1 v1 = *p##v1;
#define __nestedfunc_start2(name, t1, v1, t2, v2) \
    } void name(t1* p##v1, t2* p##v2) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2;
#define __nestedfunc_start3(name, t1, v1, t2, v2, t3, v3) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3;
#define __nestedfunc_start4(name, t1, v1, t2, v2, t3, v3, t4, v4) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4;
#define __nestedfunc_start5(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5;
#define __nestedfunc_start6(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6;
#define __nestedfunc_start7(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7;
#define __nestedfunc_start8(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8;
#define __nestedfunc_start9(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9;
#define __nestedfunc_start10(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10;
#define __nestedfunc_start11(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11;
#define __nestedfunc_start12(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12;
#define __nestedfunc_start13(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13;
#define __nestedfunc_start14(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14;
#define __nestedfunc_start15(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15;
#define __nestedfunc_start16(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15; t16 v16 = *p##v16;
#define __nestedfunc_start17(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15; t16 v16 = *p##v16; t17 v17 = *p##v17;
#define __nestedfunc_start18(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15; t16 v16 = *p##v16; t17 v17 = *p##v17; t18 v18 = *p##v18;
#define __nestedfunc_start19(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15; t16 v16 = *p##v16; t17 v17 = *p##v17; t18 v18 = *p##v18; t19 v19 = *p##v19;
#define __nestedfunc_start20(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15; t16 v16 = *p##v16; t17 v17 = *p##v17; t18 v18 = *p##v18; t19 v19 = *p##v19; t20 v20 = *p##v20;
#define __nestedfunc_start21(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15; t16 v16 = *p##v16; t17 v17 = *p##v17; t18 v18 = *p##v18; t19 v19 = *p##v19; t20 v20 = *p##v20; t21 v21 = *p##v21;
#define __nestedfunc_start22(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21, t22* p##v22) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15; t16 v16 = *p##v16; t17 v17 = *p##v17; t18 v18 = *p##v18; t19 v19 = *p##v19; t20 v20 = *p##v20; t21 v21 = *p##v21; t22 v22 = *p##v22;
#define __nestedfunc_start23(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21, t22* p##v22, t23* p##v23) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15; t16 v16 = *p##v16; t17 v17 = *p##v17; t18 v18 = *p##v18; t19 v19 = *p##v19; t20 v20 = *p##v20; t21 v21 = *p##v21; t22 v22 = *p##v22; t23 v23 = *p##v23;
#define __nestedfunc_start24(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21, t22* p##v22, t23* p##v23, t24* p##v24) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15; t16 v16 = *p##v16; t17 v17 = *p##v17; t18 v18 = *p##v18; t19 v19 = *p##v19; t20 v20 = *p##v20; t21 v21 = *p##v21; t22 v22 = *p##v22; t23 v23 = *p##v23; t24 v24 = *p##v24;
#define __nestedfunc_start25(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24, t25, v25) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21, t22* p##v22, t23* p##v23, t24* p##v24, t25* p##v25) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15; t16 v16 = *p##v16; t17 v17 = *p##v17; t18 v18 = *p##v18; t19 v19 = *p##v19; t20 v20 = *p##v20; t21 v21 = *p##v21; t22 v22 = *p##v22; t23 v23 = *p##v23; t24 v24 = *p##v24; t25 v25 = *p##v25;
#define __nestedfunc_start26(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24, t25, v25, t26, v26) \
    } void name(t1* p##v1, t2* p##v2, t3* p##v3, t4* p##v4, t5* p##v5, t6* p##v6, t7* p##v7, t8* p##v8, t9* p##v9, t10* p##v10, t11* p##v11, t12* p##v12, t13* p##v13, t14* p##v14, t15* p##v15, t16* p##v16, t17* p##v17, t18* p##v18, t19* p##v19, t20* p##v20, t21* p##v21, t22* p##v22, t23* p##v23, t24* p##v24, t25* p##v25, t26* p##v26) { \
    t1 v1 = *p##v1; t2 v2 = *p##v2; t3 v3 = *p##v3; t4 v4 = *p##v4; t5 v5 = *p##v5; t6 v6 = *p##v6; t7 v7 = *p##v7; t8 v8 = *p##v8; t9 v9 = *p##v9; t10 v10 = *p##v10; t11 v11 = *p##v11; t12 v12 = *p##v12; t13 v13 = *p##v13; t14 v14 = *p##v14; t15 v15 = *p##v15; t16 v16 = *p##v16; t17 v17 = *p##v17; t18 v18 = *p##v18; t19 v19 = *p##v19; t20 v20 = *p##v20; t21 v21 = *p##v21; t22 v22 = *p##v22; t23 v23 = *p##v23; t24 v24 = *p##v24; t25 v25 = *p##v25; t26 v26 = *p##v26;

#define __nestedfunc_end1(name, v1) \
    *p##v1 = v1;
#define __nestedfunc_end2(name, v1, v2) \
    *p##v1 = v1; *p##v2 = v2;
#define __nestedfunc_end3(name, v1, v2, v3) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3;
#define __nestedfunc_end4(name, v1, v2, v3, v4) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4;
#define __nestedfunc_end5(name, v1, v2, v3, v4, v5) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5;
#define __nestedfunc_end6(name, v1, v2, v3, v4, v5, v6) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6;
#define __nestedfunc_end7(name, v1, v2, v3, v4, v5, v6, v7) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7;
#define __nestedfunc_end8(name, v1, v2, v3, v4, v5, v6, v7, v8) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8;
#define __nestedfunc_end9(name, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9;
#define __nestedfunc_end10(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10;
#define __nestedfunc_end11(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11;
#define __nestedfunc_end12(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12;
#define __nestedfunc_end13(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13;
#define __nestedfunc_end14(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14;
#define __nestedfunc_end15(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15;
#define __nestedfunc_end16(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15; *p##v16 = v16;
#define __nestedfunc_end17(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15; *p##v16 = v16; *p##v17 = v17;
#define __nestedfunc_end18(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15; *p##v16 = v16; *p##v17 = v17; *p##v18 = v18;
#define __nestedfunc_end19(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15; *p##v16 = v16; *p##v17 = v17; *p##v18 = v18; *p##v19 = v19;
#define __nestedfunc_end20(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15; *p##v16 = v16; *p##v17 = v17; *p##v18 = v18; *p##v19 = v19; *p##v20 = v20;
#define __nestedfunc_end21(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15; *p##v16 = v16; *p##v17 = v17; *p##v18 = v18; *p##v19 = v19; *p##v20 = v20; *p##v21 = v21;
#define __nestedfunc_end22(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15; *p##v16 = v16; *p##v17 = v17; *p##v18 = v18; *p##v19 = v19; *p##v20 = v20; *p##v21 = v21; *p##v22 = v22;
#define __nestedfunc_end23(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15; *p##v16 = v16; *p##v17 = v17; *p##v18 = v18; *p##v19 = v19; *p##v20 = v20; *p##v21 = v21; *p##v22 = v22; *p##v23 = v23;
#define __nestedfunc_end24(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15; *p##v16 = v16; *p##v17 = v17; *p##v18 = v18; *p##v19 = v19; *p##v20 = v20; *p##v21 = v21; *p##v22 = v22; *p##v23 = v23; *p##v24 = v24;
#define __nestedfunc_end25(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15; *p##v16 = v16; *p##v17 = v17; *p##v18 = v18; *p##v19 = v19; *p##v20 = v20; *p##v21 = v21; *p##v22 = v22; *p##v23 = v23; *p##v24 = v24; *p##v25 = v25;
#define __nestedfunc_end26(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) \
    *p##v1 = v1; *p##v2 = v2; *p##v3 = v3; *p##v4 = v4; *p##v5 = v5; *p##v6 = v6; *p##v7 = v7; *p##v8 = v8; *p##v9 = v9; *p##v10 = v10; *p##v11 = v11; *p##v12 = v12; *p##v13 = v13; *p##v14 = v14; *p##v15 = v15; *p##v16 = v16; *p##v17 = v17; *p##v18 = v18; *p##v19 = v19; *p##v20 = v20; *p##v21 = v21; *p##v22 = v22; *p##v23 = v23; *p##v24 = v24; *p##v25 = v25; *p##v26 = v26;

#else

//
// AS210
//
#define __declare_nestedfunc1(name, t1, v1) void name();
#define __declare_nestedfunc2(name, t1, v1, t2, v2) void name();
#define __declare_nestedfunc3(name, t1, v1, t2, v2, t3, v3) void name();
#define __declare_nestedfunc4(name, t1, v1, t2, v2, t3, v3, t4, v4) void name();
#define __declare_nestedfunc5(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5) void name();
#define __declare_nestedfunc6(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6) void name();
#define __declare_nestedfunc7(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7) void name();
#define __declare_nestedfunc8(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8) void name();
#define __declare_nestedfunc9(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9) void name();
#define __declare_nestedfunc10(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10) void name();
#define __declare_nestedfunc11(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11) void name();
#define __declare_nestedfunc12(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12) void name();
#define __declare_nestedfunc13(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13) void name();
#define __declare_nestedfunc14(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14) void name();
#define __declare_nestedfunc15(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15) void name();
#define __declare_nestedfunc16(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16) void name();
#define __declare_nestedfunc17(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17) void name();
#define __declare_nestedfunc18(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18) void name();
#define __declare_nestedfunc19(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19) void name();
#define __declare_nestedfunc20(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20) void name();
#define __declare_nestedfunc21(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21) void name();
#define __declare_nestedfunc22(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22) void name();
#define __declare_nestedfunc23(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23) void name();
#define __declare_nestedfunc24(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24) void name();
#define __declare_nestedfunc25(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24, t25, v25) void name();
#define __declare_nestedfunc26(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24, t25, v25, t26, v26) void name();

#define __call_nestedfunc1(name, v1) name();
#define __call_nestedfunc2(name, v1, v2) name();
#define __call_nestedfunc3(name, v1, v2, v3) name();
#define __call_nestedfunc4(name, v1, v2, v3, v4) name();
#define __call_nestedfunc5(name, v1, v2, v3, v4, v5) name();
#define __call_nestedfunc6(name, v1, v2, v3, v4, v5, v6) name();
#define __call_nestedfunc7(name, v1, v2, v3, v4, v5, v6, v7) name();
#define __call_nestedfunc8(name, v1, v2, v3, v4, v5, v6, v7, v8) name();
#define __call_nestedfunc9(name, v1, v2, v3, v4, v5, v6, v7, v8, v9) name();
#define __call_nestedfunc10(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) name();
#define __call_nestedfunc11(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) name();
#define __call_nestedfunc12(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) name();
#define __call_nestedfunc13(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) name();
#define __call_nestedfunc14(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) name();
#define __call_nestedfunc15(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) name();
#define __call_nestedfunc16(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) name();
#define __call_nestedfunc17(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) name();
#define __call_nestedfunc18(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) name();
#define __call_nestedfunc19(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) name();
#define __call_nestedfunc20(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) name();
#define __call_nestedfunc21(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) name();
#define __call_nestedfunc22(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) name();
#define __call_nestedfunc23(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) name();
#define __call_nestedfunc24(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) name();
#define __call_nestedfunc25(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) name();
#define __call_nestedfunc26(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) name();

#define __nestedfunc_start1(name, t1, v1) void name() {
#define __nestedfunc_start2(name, t1, v1, t2, v2) void name() {
#define __nestedfunc_start3(name, t1, v1, t2, v2, t3, v3) void name() {
#define __nestedfunc_start4(name, t1, v1, t2, v2, t3, v3, t4, v4) void name() {
#define __nestedfunc_start5(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5) void name() {
#define __nestedfunc_start6(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6) void name() {
#define __nestedfunc_start7(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7) void name() {
#define __nestedfunc_start8(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8) void name() {
#define __nestedfunc_start9(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9) void name() {
#define __nestedfunc_start10(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10) void name() {
#define __nestedfunc_start11(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11) void name() {
#define __nestedfunc_start12(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12) void name() {
#define __nestedfunc_start13(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13) void name() {
#define __nestedfunc_start14(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14) void name() {
#define __nestedfunc_start15(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15) void name() {
#define __nestedfunc_start16(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16) void name() {
#define __nestedfunc_start17(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17) void name() {
#define __nestedfunc_start18(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18) void name() {
#define __nestedfunc_start19(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19) void name() {
#define __nestedfunc_start20(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20) void name() {
#define __nestedfunc_start21(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21) void name() {
#define __nestedfunc_start22(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22) void name() {
#define __nestedfunc_start23(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23) void name() {
#define __nestedfunc_start24(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24) void name() {
#define __nestedfunc_start25(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24, t25, v25) void name() {
#define __nestedfunc_start26(name, t1, v1, t2, v2, t3, v3, t4, v4, t5, v5, t6, v6, t7, v7, t8, v8, t9, v9, t10, v10, t11, v11, t12, v12, t13, v13, t14, v14, t15, v15, t16, v16, t17, v17, t18, v18, t19, v19, t20, v20, t21, v21, t22, v22, t23, v23, t24, v24, t25, v25, t26, v26) void name() {

#define __nestedfunc_end1(name, v1) }
#define __nestedfunc_end2(name, v1, v2) }
#define __nestedfunc_end3(name, v1, v2, v3) }
#define __nestedfunc_end4(name, v1, v2, v3, v4) }
#define __nestedfunc_end5(name, v1, v2, v3, v4, v5) }
#define __nestedfunc_end6(name, v1, v2, v3, v4, v5, v6) }
#define __nestedfunc_end7(name, v1, v2, v3, v4, v5, v6, v7) }
#define __nestedfunc_end8(name, v1, v2, v3, v4, v5, v6, v7, v8) }
#define __nestedfunc_end9(name, v1, v2, v3, v4, v5, v6, v7, v8, v9) }
#define __nestedfunc_end10(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) }
#define __nestedfunc_end11(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) }
#define __nestedfunc_end12(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12) }
#define __nestedfunc_end13(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13) }
#define __nestedfunc_end14(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14) }
#define __nestedfunc_end15(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15) }
#define __nestedfunc_end16(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16) }
#define __nestedfunc_end17(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17) }
#define __nestedfunc_end18(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18) }
#define __nestedfunc_end19(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19) }
#define __nestedfunc_end20(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20) }
#define __nestedfunc_end21(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21) }
#define __nestedfunc_end22(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22) }
#define __nestedfunc_end23(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23) }
#define __nestedfunc_end24(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24) }
#define __nestedfunc_end25(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25) }
#define __nestedfunc_end26(name, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20, v21, v22, v23, v24, v25, v26) }

#endif

#ifdef ARC600_OLD_NAMES
///////////////////////////////////////////////////////////////////////////////
// Old style naming for instruction simulation set
///////////////////////////////////////////////////////////////////////////////

// Core basic ops and arithmetics
#define nop()               __Nop()
#define mov(a)              __Mov(a)
#define asl(a, s)           __Asl(a, s)
#define asr(x, s)           __Asr(x, s)
#define lsr(a, s)           __Lsr(a, s)
#define asls(a, s)          __Asls(a, s)
#define asrs(a, s)          __Asrs(a, s)
#define ror(a, b)           __Ror(a, b)
#define or(a, b)            __Or(a, b)
#define and(a, b)           __And(a, b)
#define adds(a, b)          __Adds(a, b)
#define subs(a, b)          __Subs(a, b)
#define negs(a)             __Negs(a)
#define negsw(a)            __Negsw(a)
#define add(src1, src2)     __Add(src1, src2)
#define sub(src1, src2)     __Sub(src1, src2)
#define add1(src1, src2)    __Add1(src1, src2)
#define sub1(src1, src2)    __Sub1(src1, src2)
#define add2(src1, src2)    __Add2(src1, src2)
#define sub2(src1, src2)    __Sub2(src1, src2)
#define add3(src1, src2)    __Add3(src1, src2)
#define sub3(src1, src2)    __Sub3(src1, src2)
#define abss(a)             __Abss (a)
#define abssw(a)            __Abssw(a)
#define max(a, b)           __Max(a, b)
#define min(a, b)           __Min(a, b)
#define bmsk(x, m)          __Bmsk(x, m)
#define bset(x, m)          __Bset(x, m)
#define btst(x, m)          __Btst(x, m)
#define bclr(x, m)          __Bclr(x, m)
#define bxor(x, m)          __Bxor(x, m)
#define normw(x)            __Normw(x)
#define norm(x)             __Norm(x)
#define swap(a)             __Swap(a)
#define sat16(a)            __Sat16(a)
#define rnd16(a)            __Rnd16(a)
#define divaw(src1, src2)   __Divaw(src1, src2)
#define push(src)           __Push(src)
#define pop()               __Pop()
#define subsdw(a, b)        __Subsdw(a, b)
#define addsdw(a, b)        __Addsdw(a, b)

#define _nop()              __nop()
#define _mov(b, c)          __mov(b, c)
#define _asl(a, s)          __asl(a, s)
#define _asr(x, s)          __asr(x, s)
#define _lsr(x, s)          __lsr(x, s)
#define _asls(a, s)         __asls(a, s)
#define _asrs(a, s)         __asrs(a, s)
#define _ror(a, b)          __ror(a, b)
#define _rlc(a)             __rlc(a)
#define _rlc_f(a)           __rlc_f(a)
#define _or(a, b)           __or(a, b)
#define _and(a, b)          __and(a, b)
#define _adds(a, b)         __adds(a, b)
#define _subs(a, b)         __subs(a, b)
#define _negs(a)            __negs(a)
#define _negsw(a)           __negsw(a)
#define _add(src1, src2)    __add(src1, src2)
#define _sub(src1, src2)    __sub(src1, src2)
#define _rsub(src1, src2)   __rsub(src1, src2)
#define _add1(src1, src2)   __add1(src1, src2)
#define _sub1(src1, src2)   __sub1(src1, src2)
#define _add2(src1, src2)   __add2(src1, src2)
#define _sub2(src1, src2)   __sub2(src1, src2)
#define _add3(src1, src2)   __add3(src1, src2)
#define _sub3(src1, src2)   __sub3(src1, src2)
#define _abss(a)            __abss(a)
#define _max(a, b)          __max(a, b)
#define _min(a, b)          __min(a, b)
#define _abssw(a)           __abssw(a)
#define _bmsk(x, m)         __bmsk(x, m)
#define _bset(x, m)         __bset(x, m)
#define _btst(x, m)         __btst(x, m)
#define _bclr(x, m)         __bclr(x, m)
#define _bxor(x, m)         __bxor(x, m)
#define _normw(x)           __normw(x)
#define _norm(x)            __norm(x)
#define _swap(a)            __swap(a)
#define _sat16(a)           __sat16(a)
#define _rnd16(a)           __rnd16(a)
#define _divaw(src1, src2)  __divaw(src1, src2)
#define _push(src)          __push(src)
#define _pop()              __pop()
#define _subsdw(a, b)       __subsdw(a, b)
#define _addsdw(a, b)       __addsdw(a, b)

// Extension multiply/accumulate
#define mulflw(src1, src2)          __Mulflw_0(src1, src2)
#define mulflw_r0(src1, src2)       __Mulflw(src1, src2)
#define macflw(src1, src2)          __Macflw_0(src1, src2)
#define macflw_r0(src1, src2)       __Macflw(src1, src2)
#define mulhflw(src1, src2)         __Mulhflw_0(src1, src2)
#define mulhflw_r0(src1, src2)      __Mulhflw(src1, src2)
#define machflw(src1, src2)         __Machflw_0(src1, src2)
#define machflw_r0(src1, src2)      __Machflw(src1, src2)
#define mullw(src1, src2)           __Mullw_0(src1, src2)
#define mullw_r0(src1, src2)        __Mullw(src1, src2)
#define mulhlw(src1, src2)          __Mulhlw_0(src1, src2)
#define mulhlw_r0(src1, src2)       __Mulhlw(src1, src2)
#define maclw(src1, src2)           __Maclw_0(src1, src2)
#define maclw_r0(src1, src2)        __Maclw(src1, src2)
#define machlw(src1, src2)          __Machlw_0(src1, src2)
#define machlw_r0(src1, src2)       __Machlw(src1, src2)
#define muldw_r0(src1, src2)        __Muldw(src1, src2)
#define muldw(src1, src2)           __Muldw_0(src1, src2)
#define mulrdw_r0(src1, src2)       __Mulrdw(src1, src2)
#define macdw_r0(src1, src2)        __Macdw(src1, src2)
#define macdw(src1, src2)           __Macdw_0(src1, src2)
#define msubdw(src1, src2)          __Msubdw_0(src1, src2)

#define get_AUX_XMAC0_24           __Get_AUX_XMAC0_24
#define get_AUX_XMAC1_24           __Get_AUX_XMAC1_24
#define get_AUX_XMAC2_24           __Get_AUX_XMAC2_24

#define get_ACC1()                  __Get_ACC1()
#define get_ACC2()                  __Get_ACC2()
#define get_AAh()                   __Get_AAh()
#define get_AAl()                   __Get_AAl()

#define _mulflw(src1, src2)         __mulflw_0(src1, src2)
#define _mulflw_r0(src1, src2)      __mulflw(src1, src2)
#define _macflw(src1, src2)         __macflw_0(src1, src2)
#define _macflw_r0(src1, src2)      __macflw(src1, src2)
#define _mulhflw(src1, src2)        __mulhflw_0(src1, src2)
#define _mulhflw_r0(src1, src2)     __mulhflw(src1, src2)
#define _machflw(src1, src2)        __machflw_0(src1, src2)
#define _machflw_r0(src1, src2)     __machflw(src1, src2)
#define _mullw(src1, src2)          __mullw_0(src1, src2)
#define _mullw_r0(src1, src2)       __mullw(src1, src2)
#define _mulhlw(src1, src2)         __mulhlw_0(src1, src2)
#define _mulhlw_r0(src1, src2)      __mulhlw(src1, src2)
#define _maclw(src1, src2)          __maclw_0(src1, src2)
#define _maclw_r0(src1, src2)       __maclw(src1, src2)
#define _machlw(src1, src2)         __machlw_0(src1, src2)
#define _machlw_r0(src1, src2)      __machlw(src1, src2)
#define _muldw_r0(src1, src2)       __muldw(src1, src2)
#define _muldw(src1, src2)          __muldw_0(src1, src2)
#define _mulrdw_r0(src1, src2)      __mulrdw(src1, src2)
#define _macdw_r0(src1, src2)       __macdw(src1, src2)
#define _macdw(src1, src2)          __macdw_0(src1, src2)
#define _msubdw(src1, src2)         __msubdw_0(src1, src2)
#define _dmulpf_xy(src1, src2)      __dmulpf_xy(src1, src2)
#define _dmulpf_xy_0(src1, src2)    __dmulpf_xy_0(src1, src2)
#define _dmacpf_xy(src1, src2)      __dmacpf_xy(src1, src2)
#define _dmacpf_xy_0(src1, src2)    __dmacpf_xy_0(src1, src2)

#define _get_ACC1()                 __get_ACC1()
#define _get_ACC2()                 __get_ACC2()

/* AndreiMi */
#define _get_ACC1_H()               __get_ACC1_H()
#define _get_ACC2_H()               __get_ACC2_H()

// AndreyM
#define _get_xbase()                __get_xbase()
#define _get_ybase()                __get_ybase()
#define _get_AAh()                  __get_AAh()
#define _get_AAl()                  __get_AAl()

/* Simeon */
#define _get_AUXMAC0_24()           __get_AUX_XMAC0_24()
#define _get_AUX_XMAC1_24()         __get_AUX_XMAC1_24()
#define _get_AUXMAC2_24()           __get_AUX_XMAC2_24()


// XY memory addressing
#define ax0()       __Ax0()
#define ax1()       __Ax1()
#define ax2()       __Ax2()
#define ax3()       __Ax3()

#define ay0()       __Ay0()
#define ay1()       __Ay1()
#define ay2()       __Ay2()
#define ay3()       __Ay3()

#define _ax0()      __ax0()
#define _ax1()      __ax1()
#define _ax2()      __ax2()
#define _ax3()      __ax3()

#define _ay0()      __ay0()
#define _ay1()      __ay1()
#define _ay2()      __ay2()
#define _ay3()      __ay3()

#define set_ax0(a)        __Set_ax0(a)
#define set_ax1(a)        __Set_ax1(a)
#define set_ax2(a)        __Set_ax2(a)
#define set_ax3(a)        __Set_ax3(a)

#define set_ay0(a)        __Set_ay0(a)
#define set_ay1(a)        __Set_ay1(a)
#define set_ay2(a)        __Set_ay2(a)
#define set_ay3(a)        __Set_ay3(a)

#define _set_ax0(a)       __set_ax0(a)
#define _set_ax1(a)       __set_ax1(a)
#define _set_ax2(a)       __set_ax2(a)
#define _set_ax3(a)       __set_ax3(a)

#define _set_ay0(a)       __set_ay0(a)
#define _set_ay1(a)       __set_ay1(a)
#define _set_ay2(a)       __set_ay2(a)
#define _set_ay3(a)       __set_ay3(a)

#define mx00()    __Mx00()
#define mx01()    __Mx01()
#define mx10()    __Mx10()
#define mx11()    __Mx11()
#define mx20()    __Mx20()
#define mx21()    __Mx21()
#define mx30()    __Mx30()
#define mx31()    __Mx31()

#define my00()    __My00()
#define my01()    __My01()
#define my10()    __My10()
#define my11()    __My11()
#define my20()    __My20()
#define my21()    __My21()
#define my30()    __My30()
#define my31()    __My31()

#define _mx00()   __mx00()
#define _mx01()   __mx01()
#define _mx10()   __mx10()
#define _mx11()   __mx11()
#define _mx20()   __mx20()
#define _mx21()   __mx21()
#define _mx30()   __mx30()
#define _mx31()   __mx31()

#define _my00()   __my00()
#define _my01()   __my01()
#define _my10()   __my10()
#define _my11()   __my11()
#define _my20()   __my20()
#define _my21()   __my21()
#define _my30()   __my30()
#define _my31()   __my31()

#define set_mx00(a)    __Set_mx00(a)
#define set_mx01(a)    __Set_mx01(a)
#define set_mx10(a)    __Set_mx10(a)
#define set_mx11(a)    __Set_mx11(a)
#define set_mx20(a)    __Set_mx20(a)
#define set_mx21(a)    __Set_mx21(a)
#define set_mx30(a)    __Set_mx30(a)
#define set_mx31(a)    __Set_mx31(a)

#define set_my00(a)    __Set_my00(a)
#define set_my01(a)    __Set_my01(a)
#define set_my10(a)    __Set_my10(a)
#define set_my11(a)    __Set_my11(a)
#define set_my20(a)    __Set_my20(a)
#define set_my21(a)    __Set_my21(a)
#define set_my30(a)    __Set_my30(a)
#define set_my31(a)    __Set_my31(a)

#define _set_mx00(a)   __set_mx00(a)
#define _set_mx01(a)   __set_mx01(a)
#define _set_mx10(a)   __set_mx10(a)
#define _set_mx11(a)   __set_mx11(a)
#define _set_mx20(a)   __set_mx20(a)
#define _set_mx21(a)   __set_mx21(a)
#define _set_mx30(a)   __set_mx30(a)
#define _set_mx31(a)   __set_mx31(a)

#define _set_my00(a)   __set_my00(a)
#define _set_my01(a)   __set_my01(a)
#define _set_my10(a)   __set_my10(a)
#define _set_my11(a)   __set_my11(a)
#define _set_my20(a)   __set_my20(a)
#define _set_my21(a)   __set_my21(a)
#define _set_my30(a)   __set_my30(a)
#define _set_my31(a)   __set_my31(a)

#define x0_u0()        __X0_u0()
#define x0_u1()        __X0_u1()
#define x0_nu()        __X0_nu()
#define x1_u0()        __X1_u0()
#define x1_u1()        __X1_u1()
#define x1_nu()        __X1_nu()
#define x2_u0()        __X2_u0()
#define x2_u1()        __X2_u1()
#define x2_nu()        __X2_nu()
#define x3_u0()        __X3_u0()
#define x3_u1()        __X3_u1()
#define x3_nu()        __X3_nu()
#define y0_u0()        __Y0_u0()
#define y0_u1()        __Y0_u1()
#define y0_nu()        __Y0_nu()
#define y1_u0()        __Y1_u0()
#define y1_u1()        __Y1_u1()
#define y1_nu()        __Y1_nu()
#define y2_u0()        __Y2_u0()
#define y2_u1()        __Y2_u1()
#define y2_nu()        __Y2_nu()
#define y3_u0()        __Y3_u0()
#define y3_u1()        __Y3_u1()
#define y3_nu()        __Y3_nu()

#define _x0_u0()       __x0_u0()
#define _x0_u1()       __x0_u1()
#define _x0_nu()       __x0_nu()
#define _x1_u0()       __x1_u0()
#define _x1_u1()       __x1_u1()
#define _x1_nu()       __x1_nu()
#define _x2_u0()       __x2_u0()
#define _x2_u1()       __x2_u1()
#define _x2_nu()       __x2_nu()
#define _x3_u0()       __x3_u0()
#define _x3_u1()       __x3_u1()
#define _x3_nu()       __x3_nu()
#define _y0_u0()       __y0_u0()
#define _y0_u1()       __y0_u1()
#define _y0_nu()       __y0_nu()
#define _y1_u0()       __y1_u0()
#define _y1_u1()       __y1_u1()
#define _y1_nu()       __y1_nu()
#define _y2_u0()       __y2_u0()
#define _y2_u1()       __y2_u1()
#define _y2_nu()       __y2_nu()
#define _y3_u0()       __y3_u0()
#define _y3_u1()       __y3_u1()
#define _y3_nu()       __y3_nu()

#define set_x0_u0(x)    __Set_x0_u0(x)
#define set_x0_u1(x)    __Set_x0_u1(x)
#define set_x0_nu(x)    __Set_x0_nu(x)
#define set_x1_u0(x)    __Set_x1_u0(x)
#define set_x1_u1(x)    __Set_x1_u1(x)
#define set_x1_nu(x)    __Set_x1_nu(x)
#define set_x2_u0(x)    __Set_x2_u0(x)
#define set_x2_u1(x)    __Set_x2_u1(x)
#define set_x2_nu(x)    __Set_x2_nu(x)
#define set_x3_u0(x)    __Set_x3_u0(x)
#define set_x3_u1(x)    __Set_x3_u1(x)
#define set_x3_nu(x)    __Set_x3_nu(x)

#define set_y0_u0(x)    __Set_y0_u0(x)
#define set_y0_u1(x)    __Set_y0_u1(x)
#define set_y0_nu(x)    __Set_y0_nu(x)
#define set_y1_u0(x)    __Set_y1_u0(x)
#define set_y1_u1(x)    __Set_y1_u1(x)
#define set_y1_nu(x)    __Set_y1_nu(x)
#define set_y2_u0(x)    __Set_y2_u0(x)
#define set_y2_u1(x)    __Set_y2_u1(x)
#define set_y2_nu(x)    __Set_y2_nu(x)
#define set_y3_u0(x)    __Set_y3_u0(x)
#define set_y3_u1(x)    __Set_y3_u1(x)
#define set_y3_nu(x)    __Set_y3_nu(x)

#define _set_x0_u0(x)   __set_x0_u0(x)
#define _set_x0_u1(x)   __set_x0_u1(x)
#define _set_x0_nu(x)   __set_x0_nu(x)
#define _set_x1_u0(x)   __set_x1_u0(x)
#define _set_x1_u1(x)   __set_x1_u1(x)
#define _set_x1_nu(x)   __set_x1_nu(x)
#define _set_x2_u0(x)   __set_x2_u0(x)
#define _set_x2_u1(x)   __set_x2_u1(x)
#define _set_x2_nu(x)   __set_x2_nu(x)
#define _set_x3_u0(x)   __set_x3_u0(x)
#define _set_x3_u1(x)   __set_x3_u1(x)
#define _set_x3_nu(x)   __set_x3_nu(x)

#define _set_y0_u0(x)   __set_y0_u0(x)
#define _set_y0_u1(x)   __set_y0_u1(x)
#define _set_y0_nu(x)   __set_y0_nu(x)
#define _set_y1_u0(x)   __set_y1_u0(x)
#define _set_y1_u1(x)   __set_y1_u1(x)
#define _set_y1_nu(x)   __set_y1_nu(x)
#define _set_y2_u0(x)   __set_y2_u0(x)
#define _set_y2_u1(x)   __set_y2_u1(x)
#define _set_y2_nu(x)   __set_y2_nu(x)
#define _set_y3_u0(x)   __set_y3_u0(x)
#define _set_y3_u1(x)   __set_y3_u1(x)
#define _set_y3_nu(x)   __set_y3_nu(x)

#endif // ARC600_OLD_NAMES

#ifdef __cplusplus
}
#endif

#endif // __ARC600_H

