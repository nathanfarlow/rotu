#ifdef HEAD_MOD

#include "common.h"

#define head_scale ((volatile float *)0x803e9ab8)
#define other_head_scale ((volatile float *)0x803f108c)

#define CHEAT_EGO_PROBLEM 8

/** They really be vibing */
void scale_head() {
  *gCheats |= CHEAT_EGO_PROBLEM;

  float value = sinf(*gFrameCount * 0.2f) + 1.0f;

  *head_scale = value;
  *other_head_scale = value;
}

#endif
