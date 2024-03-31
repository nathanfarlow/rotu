#include "mods.h"
#include "npc.h"
#include "text.h"

/** Gets called at the start of while loop in void Global::zGameLoop(void)
 */
void game_loop_hook() {
#ifdef HEAD_MOD
  scale_head();
#endif
}

void kill_npc(zNPCInstance *a, zNPCCommon *npc) {
  void (*kill)(zNPCCommon *) = (void *)*(int *)(*(int *)(npc + 0xdc) + 0x54);
  kill(npc);
}

void end_of_render() { iter_npcs(kill_npc); }
