#include "text.h"

#define xfont void

#define xtextbox void

typedef struct basic_rect {
  float x;
  float y;
  float width;
  float height;
} basic_rect;

void (*xfont_create)(xfont *font, u32 unk, float xscale, float yscale,
                     float distance_between_characters, u32 *foreground_color,
                     basic_rect *rect,
                     u32 *shadow_color) = (void (*)(xfont *, u32, float, float,
                                                    float, u32 *, basic_rect *,
                                                    u32 *))0x80013604;

void (*xtextbox_create)(xtextbox *textbox, xfont *font, basic_rect *rect,
                        u32 a) = (void (*)(xtextbox *, xfont *, basic_rect *,
                                           u32))0x800134c4;

void (*xtextbox_set_text)(xtextbox *textbox,
                          char *text) = (void (*)(xtextbox *,
                                                  char *))0x80032034;

void (*textbox_render)(xtextbox *textbox,
                       char unk) = (void (*)(xtextbox *, char))0x80013484;

#define screen_bounds ((basic_rect *)0x803efff8)

void (*render_text)(char *text, char unk) = (void (*)(char *, char))0x80075988;

float nscreeny(float y) { return y * 0.0020833334; }
float nscreenx(float x) { return x * 0.0015625; }

int strlen(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    i++;
  }
  return i;
}

void draw_text(char *text, float x, float y, float scale, u32 foreground_color,
               u32 shadow_color) {
  char font[0x100];

  float xscale = nscreenx(22.) * scale;
  float yscale = nscreeny(19.) * scale;

  basic_rect foo = {x, y, xscale * strlen(text), yscale};

  xfont_create((xfont *)font, NULL, xscale, yscale, 0, &foreground_color,
               screen_bounds, &shadow_color);

  char textbox[0x100];
  xtextbox_create((xtextbox *)textbox, (xfont *)font, &foo, 0);

  xtextbox_set_text((xtextbox *)textbox, text);
  textbox_render((xtextbox *)textbox, 1);
}
