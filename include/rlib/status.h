#ifndef __RLIB_STATUS_H__
#define __RLIB_STATUS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  R_OK,
  R_MemoryFull,
  R_Full,
  R_Empty,
  R_Unknown,
  R_System,
} R_Status;

#ifdef __cplusplus
}
#endif

#endif // __RLIB_STATUS_H__
