#ifndef RING_FIFO__H
#define RING_FIFO__H

/*
 * Author Kevin He
 * Create On May 5th, 2015
 */


#include <stdint.h>
//#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#define HAS_INITED 0XA5A5

struct ring_fifo
{
	uint8_t *buffer;
	uint16_t queue_size;
	volatile uint16_t in;
	volatile uint16_t out;
	uint16_t element_size;
	uint16_t  flag; //0XA5A5 inited, 0, destored
};
#define RING_FIFO_NO_DATA (-1)
#define RING_FIFO_OUT_SIZE_SMALL (-2)

#define ring_fifo_empty(fifo) ((fifo)->in == (fifo)->out)
#define ring_fifo_full(fifo) ((fifo)->in + 1 == (fifo)->out || \
							(fifo)->in + 1 == (fifo)->out + (fifo)->queue_size)

#define ring_fifo_almost_full(fifo) ((fifo)->in + 8 == (fifo)->out || \
							(fifo)->in + 8 == (fifo)->out + (fifo)->queue_size)

#define ring_fifo_vaild(fifo) ((fifo)->flag == HAS_INITED)

/*
 * @queue_size is the max number of elements the ring fifo can store.
 * @element_size is the size of each element in bytes.
 * so the size of @buff (BYTE) is (queue_size * element_size)
 */
int ring_fifo_init(struct ring_fifo *fifo, void *buff, uint16_t queue_size, uint16_t element_size);

void ring_fifo_destroy(struct ring_fifo *fifo);

/*
 * return how many elements we really get.
 * @elements is how many elements we want to get
 * @no_pek : 0 means after we get the data, date no longer exists in ringfifo. if 1, data is still in ringfifo.
 */
int ring_fifo_get(struct ring_fifo *fifo,void *outData, uint16_t elements, uint8_t no_peek);

/* Don`t use / % , that is too slow*/
/*
 * @elements how many elements we want to put into the ring fifo.
 * return the real number of elements we put in.
 */
int ring_fifo_put(struct ring_fifo *fofo, const void *inData, uint16_t elements);

/*
 * A faster interface to put one element
 * @inData (MUST: the size of @inData should be at least @element_size bytes)
 */
int ring_fifo_put_one(struct ring_fifo *fifo, const void *inData);

/*if return NO_DATA then get failed*/
/*
 * A faster interface to get one element
 * @inData (MUST: the size of @outData should be at least @element_size bytes)
 */
int ring_fifo_get_one(struct ring_fifo *fifo, void *outData);


/*
 * just skip @elements data, return the real num skiped.
 */
int ring_fifo_skip(struct ring_fifo *fifo, uint16_t elements);


uint16_t ring_fifo_space(struct ring_fifo *fifo);

uint16_t ring_fifo_deep(struct ring_fifo *fifo);

void ring_fifo_reset(struct ring_fifo *fifo);



#ifdef __cplusplus
}
#endif

#endif

