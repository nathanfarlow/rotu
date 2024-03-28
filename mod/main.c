#include "mods.h"
#include "symbols.h"

/* 0x800bbc88 */
// declare a void function at this address
void (*draw_demo)(float) = (void (*)(float))0x800bbc88;
#define text ((volatile char **)0x803ed55c)

/** Gets called at the start of while loop in void Global::zGameLoop(void)
 */
void game_loop_hook() {
#ifdef HEAD_MOD
  scale_head();
#endif
}

void end_of_render() {
  int N = 120;
  float value = (float)((*gFrameCount) % N) / N;
  *text = "Hello, World!";
  draw_demo(value);
}
