#ifndef __FIFO_H__
#define __FIFO_H__

/************************************************************************/
/*                                                                      */
/************************************************************************/
#ifndef min
#define min(x,y) ({ \
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	(void) (&_x == &_y);	\
	_x < _y ? _x : _y; })
#endif

#ifndef max
#define max(x,y) ({ \
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	(void) (&_x == &_y);	\
	_x > _y ? _x : _y; })
#endif
/************************************************************************/
/*                                                                      */
/************************************************************************/
struct fifo
{
    unsigned char *buffer;	/* the buffer holding the data */
    unsigned int size;	/* the size of the allocated buffer */
    unsigned int in;	/* data is added at offset (in % size) */
    unsigned int out;	/* data is extracted from off. (out % size) */
};

/************************************************************************/
/*                                                                      */
/************************************************************************/
int fifo_init(struct fifo *fifo, unsigned char *buffer, unsigned int size);
unsigned int fifo_put(struct fifo *fifo, unsigned char *buffer, unsigned int len);
unsigned int fifo_get(struct fifo *fifo, unsigned char *buffer, unsigned int len);
unsigned int fifo_cnt(struct fifo *fifo);
void fifo_reset(struct fifo *fifo);

#endif
