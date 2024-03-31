#include "mods.h"
#include "npc.h"
#include "text.h"

void kill_npc(zNPCInstance *a, zNPCCommon *npc) {
  void (*kill)(zNPCCommon *) = vtable(npc, 0xdc, 0x15);
  kill(npc);
}

void freeze_npc(zNPCInstance *a, zNPCCommon *npc) {
  void (*freeze)(zNPCCommon *) = vtable(npc, 0xdc, 0x63);
  freeze(npc);
}

void (*CheatLevelLocksmith)() = (void *)0x80091f5c;

/** Gets called at the start of while loop in void Global::zGameLoop(void)
 */
void game_loop_hook() {
  CheatLevelLocksmith();
  iter_npcs(freeze_npc);
#ifdef HEAD_MOD
  scale_head();
#endif
}

void end_of_render() {}
