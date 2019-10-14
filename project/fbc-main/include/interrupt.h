#ifdef INTERRUPT_H
#else
#define INTERRUPT_H

#include <stdio.h>

typedef void (*interrupt_handler_t)(void);

#define  INT_TYPE_FIQ       0
#define  INT_TYPE_IRQ       0

#define INT_VECTOR_I2S_OUT_PLS_WR_IRQ     0x0
#define INT_VECTOR_I2S_IN_PLS_RD_IRQ      0x1
#define INT_VECTOR_IR_DEC                 0x2
#define INT_VECTOR_TIMERD                 0x3
#define INT_VECTOR_TIMERC                 0x4
#define INT_VECTOR_TIMERB                 0x5
#define INT_VECTOR_TIMERA                 0x6
#define INT_VECTOR_SPI                    0x7
#define INT_VECTOR_SAR_ADC                0x8
#define INT_VECTOR_UART2                  0x9
#define INT_VECTOR_UART1                  0xA
#define INT_VECTOR_UART0                  0xB
#define INT_VECTOR_I2C_1                  0xC
#define INT_VECTOR_I2C_0                  0xD
#define INT_VECTOR_WATCHDOG               0xE
#define INT_VECTOR_VPU_HSYNC              0xF
#define INT_VECTOR_VPU_VSYNC              0x10
#define INT_VECTOR_HDMIRX                 0x11
#define INT_VECTOR_AO_CEC                 0x12
#define INT_VECTOR_I2S_OUT_FIFO_SMALL0_IRQ    0x13
#define INT_VECTOR_I2S_OUT_FIFO_BIG1024_IRQ   0x14
#define INT_VECTOR_I2S_IN_FIFO_SMALL0_IRQ     0x15
#define INT_VECTOR_I2S_IN_FIFO_BIG1024_IRQ    0x16
#define INT_VECTOR_VPU_FSM_STATE_CHG_IRQ  0x17
#define INT_VECTOR_VPU_FSM_STBL_CHG_IRQ   0x18
#define INT_VECTOR_HDMI_MEAS_IRQ          0x19
#define INT_VECTOR_HDMIRX_VS_IRQ          0x1a

int RegisterInterrupt(int vector, int fiq_flag, interrupt_handler_t handler);

int UnregisterInterrupt(int vector, interrupt_handler_t handler);

int SetInterruptEnable(int vector, int enable);

void DisableAllInterrupt(void);

void EnableAllInterrupt(void);

#endif //INTERRUPT_H
