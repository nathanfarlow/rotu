#include "gfx.h"

// ------ world to screen
typedef float mat4[4][4];
// position is x + 0x30
mat4 **cam = (void *)0x80398318;
mat4 **cam_screen = (void *)0x8039831c;

#define xCamScreen void
xCamScreen **x_cam_screen_instance = (void *)0x8039831c;
float (*world_to_screen_)(xCamScreen *, xVec3 *, xVec3 *) = (void *)0x8000d570;

float world_to_screen(xVec3 *dst, xVec3 *src) {
  return world_to_screen_(*x_cam_screen_instance, dst, src);
}

// ------ text drawing

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
                        u32 centering) = (void (*)(xtextbox *, xfont *,
                                                   basic_rect *,
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

void draw_text(char *text, float x, float y, float scale, u32 foreground_color,
               u32 shadow_color) {
  char font[0x100];

  float xscale = nscreenx(22.) * scale;
  float yscale = nscreeny(19.) * scale;

  x -= xscale * _strlen(text) / 2;
  y -= yscale / 2;

  basic_rect foo = {x, y, xscale * _strlen(text), yscale};

  xfont_create((xfont *)font, NULL, xscale, yscale, 0, &foreground_color,
               screen_bounds, &shadow_color);

  char textbox[0x100];
  xtextbox_create((xtextbox *)textbox, (xfont *)font, &foo, 10);

  xtextbox_set_text((xtextbox *)textbox, text);
  textbox_render((xtextbox *)textbox, 1);
}
