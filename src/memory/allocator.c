#include "pch.h"
#include <stdlib.h>
#include <rlib/memory/allocator.h>

void* R_malloc(size_t size) {
  return malloc(size);
}

void R_free(void* ptr) {
  free(ptr);
}