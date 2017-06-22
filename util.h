#ifndef KV_UTIL__H
#define KV_UTIL__H

#define DEBUG

int kv_printf(const char *fmt, ...);
extern void putc(const char c);
typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef signed long long int64_t;
typedef signed int int32_t;
typedef signed short int16_t;
typedef signed char int8_t;

typedef unsigned int size_t;

#define ibug(fmt, ...) kv_printf(fmt, ##__VA_ARGS__)
#ifdef DEBUG
#define debug(fmt, ...) kv_printf("[%d] "fmt,__LINE__, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif
#define ebug(fmt, ...) kv_printf("[%d] ERR "fmt,__LINE__, ##__VA_ARGS__)

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
#endif

#ifndef min
#define min(a, b) ((a) < (b) ? (a):(b))
#define max(a, b) ((a) > (b) ? (a):(b))
#endif

#endif

