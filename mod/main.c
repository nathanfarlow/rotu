#include "mods.h"
#include "text.h"

/** Gets called at the start of while loop in void Global::zGameLoop(void)
 */
void game_loop_hook() {
#ifdef HEAD_MOD
  scale_head();
#endif
}

void end_of_render() {

  float x = sinf(*gFrameCount * 0.1) * 0.5 + 0.5;
  float y = cosf(*gFrameCount * 0.1) * 0.5 + 0.5;

  draw_text("yuh", x, y, 1.0f, 0xFFE600FF, 0x0);
}
