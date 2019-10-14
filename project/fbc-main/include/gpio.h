// ----------------------------------------------------------------------
//
// This file is from c_arc_pointer_reg.h
//
// ----------------------------------------------------------------------
//
#ifndef GPIO_H
#define GPIO_H
// ----------------------------
// Pad conntrols
// ----------------------------
#define P_PAD_PULL_UP_REG2                         (volatile unsigned long *)0x80030540
#define P_PAD_PULL_UP_REG3                         (volatile unsigned long *)0x80030544
#define P_PAD_PULL_UP_REG4                         (volatile unsigned long *)0x80030548
#define P_PAD_PULL_UP_EN_REG2                      (volatile unsigned long *)0x80030560
#define P_PAD_PULL_UP_EN_REG3                      (volatile unsigned long *)0x80030564
#define P_PAD_PULL_UP_EN_REG4                      (volatile unsigned long *)0x80030568
// ----------------------------
// GPIO
// ----------------------------
#define P_PREG_PAD_GPIO2_EN_N                      (volatile unsigned long *)0x80030580
#define P_PREG_PAD_GPIO2_O                         (volatile unsigned long *)0x80030584
#define P_PREG_PAD_GPIO2_I                         (volatile unsigned long *)0x80030588
// ----------------------------
#define P_PREG_PAD_GPIO3_EN_N                      (volatile unsigned long *)0x8003058c
#define P_PREG_PAD_GPIO3_O                         (volatile unsigned long *)0x80030590
#define P_PREG_PAD_GPIO3_I                         (volatile unsigned long *)0x80030594
// ----------------------------
#define P_PREG_PAD_GPIO4_EN_N                      (volatile unsigned long *)0x80030598
#define P_PREG_PAD_GPIO4_O                         (volatile unsigned long *)0x8003059c
#define P_PREG_PAD_GPIO4_I                         (volatile unsigned long *)0x800305a0
// ----------------------------
// Pin Mux
// ----------------------------
#define P_PERIPHS_PIN_MUX_2                        (volatile unsigned long *)0x800305a8
#define P_PERIPHS_PIN_MUX_3                        (volatile unsigned long *)0x800305ac
#define P_PERIPHS_PIN_MUX_4                        (volatile unsigned long *)0x800305b0
#define P_PERIPHS_PIN_MUX_5                        (volatile unsigned long *)0x800305b4

// ----------------------------
// Pad conntrols
// ----------------------------
#define P_PAD_PULL_UP_REG0                         (volatile unsigned long *)0x80030840
#define P_PAD_PULL_UP_REG1                         (volatile unsigned long *)0x80030844
#define P_PAD_PULL_UP_EN_REG0                      (volatile unsigned long *)0x80030860
#define P_PAD_PULL_UP_EN_REG1                      (volatile unsigned long *)0x80030864
// ----------------------------
// GPIO
// ----------------------------
#define P_PREG_PAD_GPIO0_EN_N                      (volatile unsigned long *)0x80030880
#define P_PREG_PAD_GPIO0_O                         (volatile unsigned long *)0x80030884
#define P_PREG_PAD_GPIO0_I                         (volatile unsigned long *)0x80030888
// ----------------------------
#define P_PREG_PAD_GPIO1_EN_N                      (volatile unsigned long *)0x8003088c
#define P_PREG_PAD_GPIO1_O                         (volatile unsigned long *)0x80030890
#define P_PREG_PAD_GPIO1_I                         (volatile unsigned long *)0x80030894
// ----------------------------
// Pin Mux
// ----------------------------
#define P_PERIPHS_PIN_MUX_0                        (volatile unsigned long *)0x800308a0
#define P_PERIPHS_PIN_MUX_1                        (volatile unsigned long *)0x800308a4

#endif // GPIO_H

