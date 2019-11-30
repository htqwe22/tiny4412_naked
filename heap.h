#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdint.h>

void enable_mm(void);
void disable_mm(void);

void reset_mm(void);

void check_mm(void);

#define ALIGN_LEN(len, align) (((len)+(align) - 1) /(align))

void mm_init(uint32_t free_memory_start, uint32_t size);

void * malloc_align(uint32_t size, uint32_t align);

void * kv_malloc(uint32_t size);

void kv_free(void *ptr);

#endif 
