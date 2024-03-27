#define head_scale ((volatile float *)0x803e9ab8)
#define other_head_scale ((volatile float *)0x803f108c)

#define sinf ((float (*)(float))0x8007d7f0)
#define gFrameCount ((volatile unsigned int *)0x803ec3c4)
#define gCheats ((volatile unsigned char *)0x803ed090)

#define enable_head_scale_cheat()                                              \
  do {                                                                         \
    *gCheats = (*gCheats & 0xf7) | 8;                                          \
  } while (0)

/** Gets called at the start of while loop in void Global::zGameLoop(void) */
void game_loop_hook() {

  float value = 2 * sinf(*gFrameCount * 0.2f) * 0.5f + 1.0f;

  *head_scale = value;
  *other_head_scale = value;

  enable_head_scale_cheat();
}
