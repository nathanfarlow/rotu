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
  /* iter_npcs(freeze_npc); */
#ifdef HEAD_MOD
  scale_head();
#endif
}

/* #define dbgf(a, ...) \ */
/*   { \ */
/*     char buf[0x100]; \ */
/*     _sprintf(buf, a, __VA_ARGS__); \ */
/*     draw_text(buf, 0.5, 0.5, 1.0f, 0xFF00FFFF, 0); \ */
/*   } */

xVec3 *(*xEntGetPos)(zNPCCommon *) = (void *)0x80025424;

#define xCamScreen void
xCamScreen **x_cam_screen_instance = (void *)0x8039831c;
float (*world_to_screen)(xCamScreen *, xVec3 *, xVec3 *) = (void *)0x8000d570;

typedef float mat4[4][4];

// Global::globals
// has type xCamGroup*
// position is x + 0x30
mat4 **cam = (void *)0x80398318;

/* float dist(xVec3 *a, xVec3 *b) { */
/*   return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y)
 * + */
/*                (a->z - b->z) * (a->z - b->z)); */
/* } */

float (*_sqrtf)(float) = (void *)0x800782a8;

mat4 **cam_screen = (void *)0x8039831c;

float dist(xVec3 *a, xVec3 *b) {
  return _sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y) +
                (a->z - b->z) * (a->z - b->z));
}

void draw_marker(zNPCInstance *a, zNPCCommon *npc) {
  xVec3 *v = xEntGetPos(npc);
  xVec3 screen;
  float f = world_to_screen(*x_cam_screen_instance, &screen, v);
  if (f < 0 || f > 1)
    return;

  draw_text("X", screen.x, screen.y, 0.5f, 0xFF00FFFF, 0);
}

void end_of_render() { iter_npcs(draw_marker); }
