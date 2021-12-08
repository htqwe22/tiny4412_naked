#ifndef KV_CONSOLE__H
#define KV_CONSOLE__H

#define CONFIG_SYS_PBSIZE 512
typedef char * va_list; 


typedef int FILE;

#define stdin  (FILE*)	0
#define stdout	(FILE*)1

int fputc(int ch, FILE*f);

int fgetc(FILE *f) ;

void init_console(void);

int kv_printf(const char *fmt, ...);

int kv_sprintf(char *str, const char *fmt, ...);

int kv_vsprintf(char *buf, const char *fmt, va_list args);

#endif
