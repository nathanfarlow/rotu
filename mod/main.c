#include "symbols.h"

#define head_scale ((volatile float *)0x803e9ab8)
#define other_head_scale ((volatile float *)0x803f108c)

void do_head_thing() {
  // Enable the big head cheat
  *gCheats |= 8;

  float value = sinf(*gFrameCount * 0.2f) + 1.0f;

  *head_scale = value;
  *other_head_scale = value;
}

/** Gets called at the start of while loop in void Global::zGameLoop(void) */
void game_loop_hook() { do_head_thing(); }
