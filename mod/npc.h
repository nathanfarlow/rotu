#pragma once
#include "common.h"

#define zNPCInstance void
#define zNPCCommon void

short get_cur_hp(zNPCCommon *);
short get_max_hp(zNPCCommon *);
bool should_have_data(zNPCInstance *, zNPCCommon *);
void iter_npcs(void (*func)(zNPCInstance *, zNPCCommon *));
