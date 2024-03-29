#pragma once
#include "common.h"

/** x and y are from 0 to 1. draws centered at x y */
void draw_text(char *text, float x, float y, float scale, u32 foreground_color,
               u32 shadow_color);
