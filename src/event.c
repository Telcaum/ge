#include "common.h"
#include "event.h"


// #define _AN_8TH_OF_THE_SDLK_EVENT_COUNT ((1UL << (sizeof(SDLK_0) * 8)) / 8)
#define HANDLED_KEY_COUNT 8


typedef struct {
  SDL_Keycode sym;
  SDL_Scancode scancode;
} GE_Key;


static bool g_events[__GE_EVENT_COUNT] = {};
static char g_text_input[32];
static int g_keys_down_stack_length = 0, g_keys_up_stack_length = 0;
static GE_Key g_keys_down[HANDLED_KEY_COUNT], g_keys_up[HANDLED_KEY_COUNT];


void GE_initEvents(void) {
  /* for (int i = 0; i < _AN_8TH_OF_THE_SDLK_EVENT_COUNT; i++) {
    g_keys_down[i] = false;
  }
   */
}


void GE_handleEvents(void) {
  for (int i = 0; i < __GE_EVENT_COUNT; i++) {
    g_events[i] = false;
  }
  g_keys_down_stack_length = 0;
  g_keys_up_stack_length = 0;

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        g_events[GE_E_QUIT] = true;
        break;

      case SDL_MOUSEBUTTONDOWN:
        switch (event.button.button) {
          case SDL_BUTTON_LEFT:
            g_events[GE_E_LEFT_CLICK] = true;
            break;

          case SDL_BUTTON_RIGHT:
            g_events[GE_E_RIGHT_CLICK] = true;
            break;
        }
        break;

      case SDL_KEYDOWN:
        if (g_keys_down_stack_length >= HANDLED_KEY_COUNT) break;
        g_keys_down[g_keys_down_stack_length++] = (GE_Key){
          .scancode = event.key.keysym.scancode,
          .sym = event.key.keysym.sym,
        };
        break;

      case SDL_KEYUP:
        if (g_keys_up_stack_length >= HANDLED_KEY_COUNT) break;
        g_keys_up[g_keys_up_stack_length++] = (GE_Key){
          .scancode = event.key.keysym.scancode,
          .sym = event.key.keysym.sym,
        };
        break;

      case SDL_TEXTINPUT:
        g_events[GE_E_TEXT_INPUT] = true;
        memcpy(g_text_input, event.text.text, 32 * sizeof(char));
        break;
    }
  }
}


bool GE_event(GE_Event event) {
  return g_events[event];
}


void GE_startTextInput(void) {
  SDL_StartTextInput();
}


void GE_stopTextInput(void) {
  SDL_StopTextInput();
}


char const *GE_textInput(void) {
  return g_text_input;
}


GE_Vec2 GE_getMousePos(void) {
  GE_Vec2 v;
  SDL_GetMouseState(&v.x, &v.y);
  return v;
}


#define GE_key(fn_name, attr, up_or_down, T) \
  bool GE_ ## fn_name(SDL_ ## T k) { \
    for (int i = 0; i < g_keys_ ## up_or_down ## _stack_length; i++) { \
      if (g_keys_ ## up_or_down[i].attr == k) return true; \
    } \
    return false; \
  }

GE_key(keyDown, sym, down, Keycode)
GE_key(keyUp, sym, up, Keycode)
GE_key(physicalKeyDown, scancode, down, Scancode)
GE_key(physicalKeyUp, scancode, up, Scancode)

#undef GE_key
