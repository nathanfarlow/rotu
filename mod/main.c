#include "mods.h"
#include "text.h"

/** Gets called at the start of while loop in void Global::zGameLoop(void)
 */
void game_loop_hook() {
#ifdef HEAD_MOD
  scale_head();
#endif
}

void end_of_render() { draw_text("yuh", 19.0f, 22.0f, 2.0f, 0xFFE600FF, 0x0); }
