#include <rlib/runtime/system.h>

typedef struct M M;
typedef struct P P;
typedef struct R R;

struct M {
  P* p;
};

struct P {
 void* _;
};

struct R {
  void* _;
};

R_Status R_System_Init(void) {
  return R_Unknown;
}