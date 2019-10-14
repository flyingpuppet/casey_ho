#ifndef AML_AUDIO_H
#define AML_AUDIO_H

struct buffer_status {
	void *start_add;
	int level;
	unsigned int rd;
	unsigned int wr;
};

int i2s_audio_init(void);

#endif
