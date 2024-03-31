#include "gfx.h"
#include "mods.h"
#include "npc.h"

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
  /* iter_npcs(freeze_npc); */
#ifdef HEAD_MOD
  scale_head();
#endif
}

xVec3 *(*xEntGetPos)(zNPCCommon *) = (void *)0x80025424;

void draw_marker(zNPCInstance *a, zNPCCommon *npc) {
  xVec3 *v = xEntGetPos(npc);
  xVec3 screen;
  float f = world_to_screen(&screen, v);
  if (f <= 0 || f >= 1 || !should_have_data(a, npc))
    return;

  float scale = f * 10;

  draw_text("X", screen.x, screen.y, scale, 0xFF00FFFF, 0);
}

void end_of_render() { iter_npcs(draw_marker); }
