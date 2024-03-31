#include "npc.h"
#include "common.h"

#define zNPCMgr void
#define zNPCInstance void
#define zNPCCommon void

zNPCInstance *(*GetInstance)(zNPCMgr *npc_mgr, int npc_type,
                             int index) = (void *)0x800d0ea4;

bool (*ShouldHaveData)(zNPCInstance *) = (void *)0x801b94c8;
zNPCCommon *(*GetData)(zNPCInstance *) = (void *)0x80091b3c;

void (*SetChase)(zNPCInstance *, char b) = (void *)0x800cf158;
void (*SetAttack)(zNPCInstance *, char b) = (void *)0x800cf150;

#define NUM_NPC_TYPES 12

zNPCMgr **npc_mgr_instance = (void *)0x803ed9e8;

void iter_npcs(void (*f)(zNPCInstance *, zNPCCommon *)) {
  for (u32 npc_type = 0; npc_type < NUM_NPC_TYPES; npc_type++) {
    for (int i = 0; i < *(int *)(*npc_mgr_instance + npc_type * 4 + 0x1d0);
         i++) {
      zNPCInstance *instance = GetInstance(*npc_mgr_instance, npc_type, i);
      zNPCCommon *common = GetData(instance);

      if (common == NULL)
        continue;

      f(instance, common);
    }
  }
}

bool should_have_data(zNPCInstance *a, zNPCCommon *b) {
  return ShouldHaveData(a) && b != NULL;
}

void *(*get_combat)(zNPCCommon *) = (void *)0x80112808;

short get_cur_hp(zNPCCommon *npc) {
  void *combat = get_combat(npc);
  if (combat == NULL)
    return 1;
  return *(short *)(combat + 0x1c);
}

short get_max_hp(zNPCCommon *npc) {
  void *combat = get_combat(npc);
  if (combat == NULL)
    return 1;
  return *(short *)(combat + 0x1e);
}
