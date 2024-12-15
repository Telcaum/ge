/*
 * spinning sprite
 */

#include <math.h>

#include "common.h"
#include "core.h"
#include "event.h"
#include "file.h"
#include "list.h"
#include "sprite.h"
#include "test.h"


static GE_SpriteX *sprite = NULL;
static bool text_input = false;
static list_char_t buf;
static double time = 0.;


void GE_load(void) {
  list_init(&buf);
  GE_setFPS(-1);
}


void GE_update(double dt) {
  time += dt;

  GE_Vec2 mouse_pos = GE_getMousePos();

  if (GE_event(GE_E_LEFT_CLICK)) {
    if (text_input) {
      SDL_StopTextInput();
      list_push(&buf, '\0');
      printf("%s\n", buf.data);
      if (sprite != NULL) {
        GE_SpriteX_free(sprite);
      }
      if (GE_fileExists(buf.data)) {
        sprite = GE_SpriteX_new(buf.data, 100, 100, true, .1, 0);
      }
      else {
        sprite = NULL;
        fprintf(stderr, "File not found.\n");
      }
      list_clear(&buf);
    }
    else SDL_StartTextInput();
    text_input = !text_input;
  }

  if (GE_event(GE_E_TEXT_INPUT)) {
    size_t len = strlen(GE_textInput());
    list_append_array(&buf, GE_textInput(), len);
  }

  if (sprite != NULL) {
    GE_SpriteX_setPos(sprite, GE_FROM_VEC2(mouse_pos));
    GE_SpriteX_setAngle(sprite, sin(time * 2.) * 30.);
    GE_SpriteX_setScale(sprite, fabs(sin(time * 7.) * .1) + .1);
  }

  printf("%d %d\n", mouse_pos.x, mouse_pos.y);
}


void GE_draw(void) {
  if (sprite != NULL) {
    GE_SpriteX_draw(sprite);
  }
}


void GE_unload(void) {
  list_free(&buf);
  if (sprite != NULL) GE_SpriteX_free(sprite);
}
