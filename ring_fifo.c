/*
 * Author Kevin He
 * Create On May 5th, 2015
 * Modyfied On Dec 20th, 2017. support element queue, and add one interface @ring_fifo_skip
 */
#include "kv_string.h"
#include "ring_fifo.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef min
#define min(a, b) ((a) < (b) ? (a):(b))
#endif


#define fifo_memcpy		kv_memcpy

#define element_addr(n) (fifo->buffer + (n)*(fifo->element_size))
#define fifo_assert()  

//do{if(fifo->flag != HAS_INITED) ASSERT(0,0);}while(0)

/*Basic principle : maxium data size is fifo->fifo_size -1;
  in >= out && in < out + fifo_size */

uint16_t ring_fifo_space(struct ring_fifo *fifo)
{
	uint16_t out;
	if (fifo == NULL) 
		return 0;
	// when use space , we want fill in , @out may change. so
	out =  fifo->out;
	if (fifo->in < out)
		return out - fifo->in -1;
	return fifo->queue_size -1 - fifo->in + out;
}

uint16_t ring_fifo_deep(struct ring_fifo *fifo)
{
	uint16_t in;
	if (fifo == NULL) 
		return 0;
	// when use deep , we want pop , @in may change. so
	in  = fifo->in;
	if (in >= fifo->out)
		return in - fifo->out;
	return fifo->queue_size + in - fifo->out;
	// or fifo->fifo_size - 1 - hal_fifo_space();
}


void ring_fifo_reset(struct ring_fifo *fifo)
{
	if (fifo) 
	{
		fifo_assert();
		fifo->in = fifo->out = 0;
	}
}

void ring_fifo_destroy(struct ring_fifo *fifo)
{
	ring_fifo_reset(fifo);
	fifo->flag = 0;
}

int ring_fifo_init(struct ring_fifo *fifo, void *buff, uint16_t queue_size, uint16_t element_size)
{
	if (fifo)
	{
		fifo->buffer = buff;
		fifo->queue_size = queue_size;
		fifo->element_size = element_size;
		if (fifo->flag == HAS_INITED)
		{
		//	ASSERT(0, 0);
		}
		fifo->flag = HAS_INITED;
		ring_fifo_reset(fifo);
		return 0;
	}
	return -1;
}

int ring_fifo_skip(struct ring_fifo *fifo, uint16_t elements)
{
	int ret;
	uint16_t deep;
	if (fifo == NULL)
		return 0;
	fifo_assert();
	deep = ring_fifo_deep(fifo);
	ret = min(elements, deep);
	if (ret + fifo->out >= fifo->queue_size) {
		fifo->out = ret + fifo->out - fifo->queue_size;
	}else {
		fifo->out += ret; 		
	}
	return ret;
}


int ring_fifo_get(struct ring_fifo *fifo,void *outData, uint16_t elements, uint8_t no_peek)
{
	uint8_t *pdata;	
	uint16_t deep, l;
	int ret;
	if (fifo == NULL || outData == NULL) {
		return -1;
	}	
	fifo_assert();
	pdata = (uint8_t *)outData;
	deep = ring_fifo_deep(fifo);
	ret = min(elements, deep);
	l = min(ret, fifo->queue_size - fifo->out);
//	fifo_memcpy(pdata, fifo->fifo + fifo->out, l);
//	fifo_memcpy(pdata + l, fifo->fifo, ret - l);
	fifo_memcpy(pdata, element_addr(fifo->out), l*fifo->element_size);
	fifo_memcpy(pdata + l*fifo->element_size, fifo->buffer, (ret - l)*fifo->element_size);
	if (no_peek == 0) {
		if (ret + fifo->out >= fifo->queue_size) {
			fifo->out = ret + fifo->out - fifo->queue_size;
//			printf("round\r\n");
		}else {
			fifo->out += ret;			
		}
	}
	return ret;
	
}

/* Don`t use / % , that is too slow*/
int ring_fifo_put(struct ring_fifo *fifo, const void *inData, uint16_t elements)
{
	uint8_t *pdata;	
	uint16_t space, l;
	int ret;
	if (fifo == NULL || inData == NULL) {
		return -1;
	}	
	fifo_assert();
	pdata = (uint8_t *)inData;
	space = ring_fifo_space(fifo);
	ret = min(space, elements);	
	if (ret < elements)
	{
//		ASSERT(0, 0);
	}
	l = min(ret, fifo->queue_size - fifo->in);	
//	fifo_memcpy(fifo->fifo + fifo->in, pdata , l);
//	fifo_memcpy(fifo->fifo, pdata + l, ret - l);
	fifo_memcpy(element_addr(fifo->in), pdata , l*fifo->element_size);
	fifo_memcpy(fifo->buffer, pdata + l*fifo->element_size, (ret - l)*fifo->element_size);
	if (ret + fifo->in >= fifo->queue_size) {
		fifo->in = ret + fifo->in - fifo->queue_size;
	} else {
		fifo->in += ret;		
	}
	return ret;
}

int ring_fifo_put_one(struct ring_fifo *fifo, const void *inData)
{
	if (ring_fifo_full(fifo)) 
	{
//		ASSERT(0, 0);
		return 0;
	}
	fifo_assert();
	fifo_memcpy(element_addr(fifo->in),inData, fifo->element_size);
	if (1 + fifo->in >= fifo->queue_size)
		fifo->in = 0;
	else
		fifo->in++;
	return 1;
}

int ring_fifo_get_one(struct ring_fifo *fifo, void *outData)
{
	if (fifo == NULL || outData == NULL) {
		return RING_FIFO_NO_DATA;
	}	
	if (ring_fifo_empty(fifo)) 
		return RING_FIFO_NO_DATA;
	fifo_assert();
	fifo_memcpy(outData, element_addr(fifo->out), fifo->element_size);
	if (1 + fifo->out >= fifo->queue_size)
		fifo->out = 0;
	else
		fifo->out++;
	return 1;
}



