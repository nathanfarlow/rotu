#pragma once

#define zNPCInstance void
#define zNPCCommon void

void iter_npcs(void (*func)(zNPCInstance *, zNPCCommon *));
