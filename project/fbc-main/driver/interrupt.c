#include <register.h>
#include <stdio.h>
#include <interrupt.h>

#ifdef IN_FBC_MAIN_CONFIG
#include <task.h>
#endif

#define MAX_INT_NUMBER 128 // support interrupt source 0~31

#ifdef IN_FBC_MAIN_CONFIG
#define MAX_INT_HANDLER 4 // max 4 handlers for each source
#else
#define MAX_INT_HANDLER 2
#endif

static interrupt_handler_t int_handlers[MAX_INT_NUMBER][MAX_INT_HANDLER];

#define INTR_STAT_REG(i)	(INTR_STAT_0+(i<<3))
#define INTR_STAT_CLR_REG(i)	(INTR_STAT_CLR_0+(i<<3))
#define INTR_FIRQ_SEL_REG(i)	(INTR_FIRQ_SEL_0+(i<<3))
#define INTR_MASK_REG(i)	(INTR_MASK_0+(i<<3))






int read_int_ack(void)
{	char i=0;
	char j=0;
	int vector=0;
	int data32=0;
	int Fiq_flag =0;
	int Fiq_int=0;
//	printf("read_int_ack\n");
	for(i=0;i<(MAX_INT_NUMBER>>5);i++) {
		data32 = Rd(INTR_STAT_REG(i));
		Fiq_flag = Rd(INTR_FIRQ_SEL_REG(i));
		Fiq_int = data32 & Fiq_flag;
		if(Fiq_int) {
			j=0;
			while (!(Fiq_int & (1<<j))){
				j++;
			}
			vector = (i<<5) + j;
			Wr(INTR_STAT_CLR_REG(vector>>5), 1<<(vector & 0x1f));
			return  vector;
		}
		else if(data32) {
			j=0;
			while (!(data32 & (1<<j))){
				j++;
			}
			vector = (i<<5) + j;
			Wr(INTR_STAT_CLR_REG(vector>>5), 1<<(vector & 0x1f));
			return  vector;

		}
	}
	return  MAX_INT_NUMBER;
}

// -----------------------------------
// SLOW Interrupt
// -----------------------------------
void Process_Irq(int vector)
{
	int i;

	//printf("Process_Irq %d\n", vector);
	if (vector>=MAX_INT_NUMBER)
		return;
	for (i=0;i<MAX_INT_HANDLER;i++)
		if (int_handlers[vector][i] != NULL)
			int_handlers[vector][i]();
		
#ifdef IN_FBC_MAIN_CONFIG
	if (vector<32) 
		WakeupTaskByInterrupt(vector);
#endif

	return ;

}

// -----------------------------------
// FAST Interrupt
// -----------------------------------
void Process_Fiq(int vector)
{
	int i;
#if 1
	//printf("Process_Fiq %d\n", vector);
	if (vector>=MAX_INT_NUMBER)
		return;
	for (i=0;i<MAX_INT_HANDLER;i++)
		if (int_handlers[vector][i] != NULL)
			int_handlers[vector][i]();
		
#ifdef IN_FBC_MAIN_CONFIG
	if (vector<32) 
		WakeupTaskByInterrupt(vector);
#endif
#endif
	return ;

}

int RegisterInterrupt(int vector, int fiq_flag, interrupt_handler_t handler)
{
	int i;

	if (vector >= MAX_INT_NUMBER)
		return -1;
	for (i=0;i<MAX_INT_HANDLER;i++){
		if (int_handlers[vector][i] == NULL){
			int_handlers[vector][i] = handler;
			if (fiq_flag)
				Wr(INTR_FIRQ_SEL_REG(vector>>5), Rd(INTR_FIRQ_SEL_REG(vector>>5))|(1<<(vector&0x1f)));
			else
				Wr(INTR_FIRQ_SEL_REG(vector>>5), Rd(INTR_FIRQ_SEL_REG(vector>>5))&~(1<<(vector&0x1f)));
			return 0;
		}
	}
	return -2;
}

int UnregisterInterrupt(int vector, interrupt_handler_t handler)
{
	int i;

	if (vector >= MAX_INT_NUMBER)
		return -1;

	for (i=0;i<MAX_INT_HANDLER;i++){
		if (int_handlers[vector][i] == handler){
			int_handlers[vector][i] = NULL;			
			return 0;
		}
	}
	return -2;
}

int SetInterruptEnable(int vector, int enable){
	if(0 == enable){
		Wr(INTR_MASK_REG(vector>>5), Rd(INTR_MASK_REG(vector>>5))&~(1<<(vector&0x1f)));
	}else if(1 == enable){
		Wr(INTR_MASK_REG(vector>>5), Rd(INTR_MASK_REG(vector>>5))|(1<<(vector&0x1f)));
	}
	return 0;
}

void DisableAllInterrupt(void) {
		_disable();
}

void EnableAllInterrupt(void) {
		_enable(); 
}
