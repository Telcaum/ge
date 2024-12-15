/*
 * sprite selection & placement thing
 */

#include <string.h>

#include "core.h"
#include "event.h"
#include "file.h"
#include "list.h"
#include "sprite.h"
#include "test.h"


typedef list_t(GE_SpriteX *) list_SpriteX_t;


static list_SpriteX_t g_sprites;
static GE_Vec2 g_mouse;
static list_char_t g_input_buffer;
static void (*g_update_callback)(double) = NULL;


static void updateDefault(double dt);


void GE_load(void) {
  list_init(&g_sprites);
  list_init(&g_input_buffer);
  g_update_callback = updateDefault;

  GE_setFPS(30);
}


static void placeNewSprite(void) {
  list_push(&g_input_buffer, '\0');

  if (!GE_fileExists(g_input_buffer.data)) {
    fprintf(stderr, "File '%s' does not exist.\n", g_input_buffer.data);
    list_clear(&g_input_buffer);
    g_update_callback = updateDefault;
    return;
  }

  GE_SpriteX *sprite = GE_SpriteX_new(g_input_buffer.data, GE_FROM_VEC2(g_mouse), true, .5, 0.);
  list_push(&g_sprites, sprite);
  list_clear(&g_input_buffer);

  g_update_callback = updateDefault;
}


static void listenForSpritePath(double dt) {
  if (GE_event(GE_E_TEXT_INPUT)) {
    char const *input = GE_textInput();
    size_t len = strlen(input);
    list_append_array(&g_input_buffer, input, len);
    printf("%s", input);
    fflush(stdout);
  }

  if (GE_keyDown(SDLK_KP_ENTER)) {
    puts("");
    placeNewSprite();
    return;
  }
}


static void startPlacingNewSprite(void) {
  printf("Listening\n");
  GE_startTextInput();
  g_update_callback = listenForSpritePath;
}


static void updateDefault(double dt) {
  if (GE_event(GE_E_RIGHT_CLICK)) {
    startPlacingNewSprite();
    return;
  }
}


void GE_update(double dt) {
  g_mouse = GE_getMousePos();

  g_update_callback(dt);
}


void GE_draw(void) {
  int i; GE_SpriteX *sprite;
  list_foreach(&g_sprites, i, sprite) {
    GE_SpriteX_draw(sprite);
  }
}


void GE_unload(void) {
  int i; GE_SpriteX *sprite;
  list_foreach(&g_sprites, i, sprite) {
    GE_SpriteX_free(sprite);
  }
  list_free(&g_sprites);
}