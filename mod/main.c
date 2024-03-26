#define head_scale ((volatile float *)0x803e9ab8)


/** Gets called at the start of while loop in void Global::zGameLoop(void) */
int game_loop_hook() {
  // TODO: float constants are broken for PIC.
  *head_scale += (*head_scale / *head_scale) / (*head_scale);
  /* *head_scale += *(float *)&tiny_float; */
  return 0;
}
