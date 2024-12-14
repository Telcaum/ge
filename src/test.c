#include "common.h"
#include "event.h"
#include "file.h"
#include "list.h"
#include "sprite.h"
#include "test.h"


static GE_Sprite *sprite = NULL;
static bool text_input = false;
static list_char_t buf;


void GE_load(void) {
  list_init(&buf);
}


void GE_update(void) {
  if (GE_event(GE_E_LEFT_CLICK)) {
    if (text_input) {
      SDL_StopTextInput();
      if (sprite != NULL) {
        GE_Sprite_free(sprite);
      }
      if (GE_fileExists(buf.data)) {
        sprite = GE_Sprite_new(buf.data);
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
}


void GE_draw(void) {
  if (sprite != NULL) {
    GE_Sprite_draw(sprite);
  }
}


void GE_unload(void) {
  list_free(&buf);
  if (sprite != NULL) GE_Sprite_free(sprite);
}
