#ifdef NEC_REMOTE_H
#else
#define NEC_REMOTE_H

#ifdef IN_FBC_MAIN_CONFIG
int remote_init(void);
int set_remote_mode(int mode);
#else
int resume_remote(int mode);
unsigned query_key_value();

#endif

#endif //NEC_REMOTE_H
