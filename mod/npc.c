#include "npc.h"
#include "common.h"

#define zNPCMgr void
#define zNPCBase void
#define zNPCInstance void
#define zNPCCommon void

zNPCBase *(*GetData)(zNPCMgr *this, int npc_type,
                     int index) = (void *)0x800d0ed0;

zNPCInstance *(*GetInstance)(zNPCBase *npc_base, int npc_type,
                             int index) = (void *)0x800d0ea4;

zNPCCommon *(*get_data)(zNPCInstance *npc_instance) = (void *)0x80091b3c;
bool (*should_have_data)(zNPCInstance *npc_instance) = (void *)0x801b94c8;

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

#define npc_mgr_instance ((zNPCMgr **)0x803ed9e8)

void iter_npcs(void (*f)(zNPCInstance *, zNPCCommon *)) {
  for (u32 npc_type = 0; npc_type < NUM_NPC_TYPES; npc_type = npc_type + 1) {
    for (int i = 0; i < *(int *)(*npc_mgr_instance + npc_type * 4 + 0x1d0);
         i++) {
      zNPCInstance *instance = GetInstance(*npc_mgr_instance, npc_type, i);
      zNPCCommon *common = get_data(instance);
      if (!should_have_data(instance) || common == NULL)
        continue;
      f(instance, common);
    }
  }
}
