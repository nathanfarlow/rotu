#pragma once

#define NULL 0
#define u32 unsigned int

#define sinf ((float (*)(float))0x8007d7f0)
#define cosf ((float (*)(float))0x8007d834)
#define gFrameCount ((volatile unsigned int *)0x803ec3c4)
#define gCheats ((volatile unsigned char *)0x803ed090)

#define _strlen ((u32(*)(char *))0x802af4f8)
#define _sprintf ((u32(*)(char *, char *, ...))0x802abcb4)
