#include <gtest/gtest.h>
#include <rlib/container/ring_buffer.h>
#include "../defer.hpp"

TEST(ring_buffer, create_and_destroy) {
  R_RingBuffer* rb = nullptr;

  ASSERT_EQ(R_OK, R_RingBuffer_Create(&rb, 32));
  ASSERT_NE(nullptr, rb);

  R_RingBuffer_Destroy(rb);
}

TEST(ring_buffer, capacity) {
  R_RingBuffer* rb = nullptr;

  ASSERT_EQ(R_OK, R_RingBuffer_Create(&rb, 31));
  ASSERT_NE(nullptr, rb);

  ASSERT_EQ(31, R_RingBuffer_Capacity(rb));

  R_RingBuffer_Destroy(rb);
}

TEST(ring_buffer, capacity_round) {
  R_RingBuffer* rb = nullptr;

  ASSERT_EQ(R_OK, R_RingBuffer_Create(&rb, 30));
  ASSERT_NE(nullptr, rb);

  ASSERT_EQ(31, R_RingBuffer_Capacity(rb));

  R_RingBuffer_Destroy(rb);
}

TEST(ring_buffer, push) {
  R_RingBuffer* rb = nullptr;

  ASSERT_EQ(R_OK, R_RingBuffer_Create(&rb, 4));
  ASSERT_NE(nullptr, rb);
  defer(R_RingBuffer_Destroy(rb));

  for (size_t i = 0; i < R_RingBuffer_Capacity(rb); ++i) {
    ASSERT_EQ(R_OK, R_RingBuffer_Push(rb, (void*)i)) << i;
  }
  ASSERT_EQ(R_Full, R_RingBuffer_Push(rb, NULL));
}

TEST(ring_buffer, pop) {
  R_RingBuffer* rb = nullptr;

  ASSERT_EQ(R_OK, R_RingBuffer_Create(&rb, 4));
  ASSERT_NE(nullptr, rb);
  defer(R_RingBuffer_Destroy(rb));

  void* data = nullptr;

  ASSERT_EQ(R_Empty, R_RingBuffer_Pop(rb, &data));

  for (size_t i = 0; i < R_RingBuffer_Capacity(rb); ++i) {
    ASSERT_EQ(R_OK, R_RingBuffer_Push(rb, (void*)i)) << i;
  }
  for (size_t i = 0; i < R_RingBuffer_Capacity(rb); ++i) {
    ASSERT_EQ(R_OK, R_RingBuffer_Pop(rb, &data)) << i;
    ASSERT_EQ((void*)i, data);
  }

  ASSERT_EQ(R_Empty, R_RingBuffer_Pop(rb, &data));
}

TEST(ring_buffer, push_and_pop) {
  R_RingBuffer* rb = nullptr;

  ASSERT_EQ(R_OK, R_RingBuffer_Create(&rb, 4));
  ASSERT_NE(nullptr, rb);
  defer(R_RingBuffer_Destroy(rb));

  void* data = nullptr;

  for (size_t n = 1; n <= R_RingBuffer_Capacity(rb); ++n) {
    ASSERT_EQ(R_Empty, R_RingBuffer_Pop(rb, &data));

    for (size_t i = 0; i < n; ++i) {
      ASSERT_EQ(R_OK, R_RingBuffer_Push(rb, (void*)i)) << i;
    }
    for (size_t i = 0; i < n; ++i) {
      ASSERT_EQ(R_OK, R_RingBuffer_Pop(rb, &data)) << i;
      ASSERT_EQ((void*)i, data);
    }

    ASSERT_EQ(R_Empty, R_RingBuffer_Pop(rb, &data));
  }
}