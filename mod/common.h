#pragma once

#define NULL 0
#define u32 unsigned int
#define u8 unsigned char
#define bool u8
#define true 1
#define false 0

#define sinf ((float (*)(float))0x8007d7f0)
#define cosf ((float (*)(float))0x8007d834)
#define sqrtf ((float (*)(float))0x800782a8)
#define gFrameCount ((volatile unsigned int *)0x803ec3c4)
#define gCheats ((volatile unsigned char *)0x803ed090)

#define _strlen ((u32(*)(char *))0x802af4f8)
#define _sprintf ((u32(*)(char *, char *, ...))0x802abcb4)

#define dbgf(a, ...)                                                           \
  {                                                                            \
    char buf[0x100];                                                           \
    _sprintf(buf, a, __VA_ARGS__);                                             \
    draw_text(buf, 0.5, 0.5, 1.0f, 0xFF00FFFF, 0);                             \
  }

typedef struct xVec3 {
  float x;
  float y;
  float z;
} xVec3;

/** offset1: bytes from start of objects
 * offset2: words from start of vtable
 */
void *vtable(void *obj, int offset1, int offset2);
void set_vtable(void *obj, int offset1, int offset2, void *func);
