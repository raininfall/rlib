#include <stdbool.h>
#include <rlib/memory/allocator.h>
#include <rlib/container/ring_buffer.h>

struct R_RingBuffer {
  size_t head;
  size_t tail;
  size_t capacity;
  void* buf[1];
};

static size_t roundup_pow_of_two(size_t x) {
  size_t b = 1;

  for (size_t i = 0; i < sizeof(size_t) * 8; ++i) {
    if (x < b) {
      break;
    }
    b = b << 1;
  }

  return b;
}

R_Status R_RingBuffer_Create(R_RingBuffer** rb, size_t capacity) {
  capacity = roundup_pow_of_two(capacity) - 1;

  R_RingBuffer* me = (R_RingBuffer*)R_malloc(capacity * sizeof(void*) + sizeof(R_RingBuffer));
  if (NULL == me) {
    return R_MemoryFull;
  }
  memset(me, 0, capacity + sizeof(R_RingBuffer));

  me->head = me->tail = 0;
  me->capacity = capacity;

  *rb = me;

  return R_OK;
}

void R_RingBuffer_Destroy(R_RingBuffer* rb) {
  R_free(rb);
}

static bool R_RingBuffer_IsFull(R_RingBuffer* rb) {
  return R_RingBuffer_Capacity(rb) == R_RingBuffer_Length(rb);
}

static bool R_RingBuffer_IsEmpty(R_RingBuffer* rb) {
  return 0 == R_RingBuffer_Length(rb);
}

size_t R_RingBuffer_Length(R_RingBuffer* rb) {
  return (rb->tail - rb->head) & rb->capacity;
}

size_t R_RingBuffer_Capacity(R_RingBuffer* rb) {
  return rb->capacity;
}

R_Status R_RingBuffer_Push(R_RingBuffer* rb, void* data) {
  if (R_RingBuffer_IsFull(rb)) {
    return R_Full;
  }

  ++rb->tail;
  rb->buf[rb->tail & rb->capacity] = data;

  return R_OK;
}

R_Status R_RingBuffer_Pop(R_RingBuffer* rb, void** data) {
  if (R_RingBuffer_IsEmpty(rb)) {
    return R_Empty;
  }

  ++rb->head;
  *data = rb->buf[rb->head & rb->capacity];

  return R_OK;
}