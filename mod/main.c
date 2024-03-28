#include "mods.h"

/** Gets called at the start of while loop in void Global::zGameLoop(void) */
void game_loop_hook() {
#ifdef HEAD_MOD
  scale_head();
#endif
}
