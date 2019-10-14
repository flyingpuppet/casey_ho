#ifndef _AUDIO_CONTROL_H
#define _AUDIO_CONTROL_H

#include <cmd.h>



int audio_codec_init(void);
int init_audio_nec_control_task(void);
int init_audio_cec_control_task(void);


#endif
