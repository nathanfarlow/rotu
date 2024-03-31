#include "mods.h"
#include "text.h"

/* #define mr_i_can_take_damage ((volatile void **)0x802ff93c) */

char no() { return 0; }
char yes() { return 1; }

#define zNPCMgr void
#define zNPCBase void
#define zNPCInstance void
#define zNPCCommon void

typedef char bool;

zNPCBase *(*GetData)(zNPCMgr *this, int npc_type,
                     int index) = (void *)0x800d0ed0;

zNPCInstance *(*GetInstance)(zNPCBase *npc_base, int npc_type,
                             int index) = (void *)0x800d0ea4;

zNPCCommon *(*get_data)(zNPCInstance *npc_instance) = (void *)0x80091b3c;
bool (*should_have_data)(zNPCInstance *npc_instance) = (void *)0x801b94c8;

/* zNPCInstance *(*get_instance)(zNPCBase *npc_base) = (void *)0x800d0410; */

#define dbgf(a, ...)                                                           \
  {                                                                            \
    char buf[100];                                                             \
    _sprintf(buf, a, __VA_ARGS__);                                             \
    draw_text(buf, 0.5, 0.5, 1.0f, 0xFF00FFFF, 0);                             \
  }

typedef struct xVec3 {
  float x;
  float y;
  float z;
} xVec3;

xVec3 *(*get_last_pos)(zNPCInstance *npc_instance) = (void *)0x800bd09c;

typedef unsigned char u8;
void (*SetChase)(zNPCInstance *npc_instance, char b) = (void *)0x800cf158;
void (*SetAttack)(zNPCInstance *npc_instance, char b) = (void *)0x800cf150;
u8 (*get_flags)(zNPCInstance *npc_instance) = (void *)0x800aca0c;

#define NUM_NPC_TYPES 12

void iter_npcs(zNPCMgr *this, void (*func)(zNPCInstance *, zNPCCommon *)) {
  for (u32 npc_type = 1; npc_type < NUM_NPC_TYPES; npc_type = npc_type + 1) {
    for (int i = 0; i < *(int *)(this + npc_type * 4 + 0x1d0); i++) {
      zNPCInstance *instance = GetInstance(this, npc_type, i);
      zNPCCommon *common = get_data(instance);
      if (!should_have_data(instance) || common == NULL)
        continue;
      func(instance, common);
    }
  }
}

#define npc_mgr_instance ((zNPCMgr **)0x803ed9e8)

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

void end_of_render() {

  /* *mr_i_can_take_damage = (void *)no; */

  /* float x = sinf(*gFrameCount * 0.01) * 0.5 + 0.5; */
  /* float y = cosf(*gFrameCount * 0.01) * 0.5 + 0.5; */
  /* int color = sinf(*gFrameCount * 0.1) * 0xFF; */

  /* draw_text("yeet", x, y, 4.0f, (color << 24 | 0x00FFFF), (color << 16 |
   * 0xff)); */
  iter_npcs(*npc_mgr_instance, kill_npc);
}
