#include "mods.h"
#include "text.h"

/* void (*draw_demo)(float) = (void (*)(float))0x800bbc88; */
#define guh_text ((volatile char **)0x803ed55c)

/** Gets called at the start of while loop in void Global::zGameLoop(void)
 */
void game_loop_hook() {
#ifdef HEAD_MOD
  scale_head();
#endif
}

void end_of_render() {
  draw_text("Hello, World!", 19.0f, 22.0f, 2.0f, 0xFFE600FF);
}
