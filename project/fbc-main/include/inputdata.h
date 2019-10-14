
#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <listop.h>

#define INPUT_VALID             0xFF
#define INPUT_REPEAT_FLAG       0x02

#define KEY_DOWN                0x00
#define KEY_UP                  0x01
#define MOUSE_MOVE              0x02
#define MOUSE_L_BUTTON_DOWN     0x03
#define MOUSE_L_BUTTON_UP       0x04
#define MOUSE_R_BUTTON_DOWN     0x05
#define MOUSE_R_BUTTON_UP       0x06
#define MOUSE_M_BUTTON_DOWN     0x07
#define MOUSE_M_BUTTON_UP       0x08
#define MOUSE_SCROLL_UP         0x09
#define MOUSE_SCROLL_DOWN       0x0A
#define TOUCH_SCANNER_GENERAL   0x0B
#define TOUCH_SLIDE_CAPTURE     0x0C

#define INPUT_REMOTE            (0x1<<0)
#define INPUT_SARADC            (0x1<<1)
#define INPUT_UART_CONSOLE			(0x1<<2)
#define INPUT_UART_HOST         (0x1<<3)
#define INPUT_CEC               (0x1<<4)
#define INPUT_VPP_DEBUG         (0x1<<5)

#define INPUT_CALL_TASK_MAX   1

typedef struct {
	list_t *     cmd_list;
	unsigned int task_id;
	unsigned int input_mask;
	int (*func)(int key_value);
}input_call_task_t;

typedef struct {
    int      input_type ; //to define which type we get, key up, key down, or mouse move, and so on
    int      input_flag ; //to define input if valide or if it repeat key
    int      input_data ; //input value
    int      input_modifers ; //special key, like shift, ctrl, alt and so on
} INPUTDATA ;

typedef struct {
	  unsigned int      cmd_owner ;
	  unsigned int      data ;
}INPUT_MODULE_DATA;

typedef struct {
	  list_t                  list;
	  INPUT_MODULE_DATA       input_data ;
}INPUT_LIST;

#endif /* INPUTDATA_H */
