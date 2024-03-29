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

  float x = sinf(*gFrameCount * 0.01) * 0.5 + 0.5;
  float y = cosf(*gFrameCount * 0.01) * 0.5 + 0.5;
  int color = sinf(*gFrameCount * 0.1) * 0xFF;

  draw_text("yeet", x, y, 4.0f, (color << 24 | 0x00FFFF), 0x0);
}
