#ifndef KV_CONSOLE__H
#define KV_CONSOLE__H

#define CONFIG_SYS_PBSIZE 512
typedef char * va_list; 


typedef int FILE;

#define stdin  	0
#define stdout	1


void init_console(void);

int kv_printf(const char *fmt, ...);
int kv_vsprintf(char *buf, const char *fmt, va_list args);

#endif
