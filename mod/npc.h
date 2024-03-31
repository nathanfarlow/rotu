#pragma once
#include "common.h"

#define zNPCInstance void
#define zNPCCommon void

bool should_have_data(zNPCInstance *, zNPCCommon *);
void iter_npcs(void (*func)(zNPCInstance *, zNPCCommon *));
