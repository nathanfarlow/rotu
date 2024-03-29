#include "text.h"

#define xfont void
#define basic_rect void

#define xtextbox void

void (*xfont_create)(xfont *font, u32 unk, float x, float y, float unk1,
                     u32 *color_, basic_rect *rect, u32 *color2, float unk2,
                     float unk3) = (void (*)(xfont *, u32, float, float, float,
                                             u32 *, basic_rect *, u32 *, float,
                                             float))0x80013604;

void (*xtextbox_create)(xtextbox *textbox, xfont *font, basic_rect *rect, u32 a,
                        float b, float c, float d,
                        float e) = (void (*)(xtextbox *, xfont *, basic_rect *,
                                             u32, float, float, float,
                                             float))0x800134c4;

void (*xtextbox_set_text)(xtextbox *textbox,
                          char *text) = (void (*)(xtextbox *,
                                                  char *))0x80032034;

void (*textbox_render)(xtextbox *textbox,
                       char unk) = (void (*)(xtextbox *, char))0x80013484;

#define screen_bounds ((basic_rect *)0x803efff8)

void (*render_text)(char *text, char unk) = (void (*)(char *, char))0x80075988;

float nscreeny(float y) { return y * 0.0020833334; }
float nscreenx(float x) { return x * 0.0015625; }

void draw_text(char *text, float x, float y, float scale, u32 foreground_color,
               u32 background_color) {
  char font[0x100];
  xfont_create((xfont *)font, 0, nscreenx(x), nscreeny(y), 0.,
               &foreground_color, screen_bounds, &background_color, 2., 2.);

  char textbox[0x100];
  xtextbox_create((xtextbox *)textbox, (xfont *)font, screen_bounds, 2, 0, 0, 0,
                  0);

  xtextbox_set_text((xtextbox *)textbox, text);
  textbox_render((xtextbox *)textbox, 1);
}
