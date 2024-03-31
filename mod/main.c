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

/** offset1: bytes from start of objects
 * offset2: words from start of vtable
 */
void *vtable(zNPCCommon *obj, int offset1, int offset2) {
  return (*(void ***)(obj + offset1))[offset2];
}

void kill_npc(zNPCInstance *a, zNPCCommon *npc) {
  void (*kill)(zNPCCommon *) = vtable(npc, 0xdc, 0x15);
  kill(npc);
}

void end_of_render() { iter_npcs(*kill_npc); }
