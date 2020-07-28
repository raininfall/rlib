#ifndef __RLIB_RING_BUFFER_H__
#define __RLIB_RING_BUFFER_H__

#include <stddef.h>
#include "../status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct R_RingBuffer R_RingBuffer;

R_Status R_RingBuffer_Create(R_RingBuffer** rb, size_t capacity);

R_Status R_RingBuffer_Push(R_RingBuffer* rb, void* data);

R_Status R_RingBuffer_Pop(R_RingBuffer* rb, void** data);

size_t R_RingBuffer_Capacity(R_RingBuffer* rb);

size_t R_RingBuffer_Length(R_RingBuffer* rb);

void R_RingBuffer_Destroy(R_RingBuffer* rb);

#ifdef __cplusplus
}
#endif

#endif  // __RLIB_RING_BUFFER_H__