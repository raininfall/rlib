#ifndef __RLIB_ALLOCATOR_H__
#define __RLIB_ALLOCATOR_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* R_malloc(size_t size);

void R_free(void* ptr);

#ifdef __cplusplus
}
#endif

#endif // __RLIB_ALLOCATOR_H__