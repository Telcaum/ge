#include "common.h"
#include "event.h"


#define _AN_8TH_OF_THE_SDLK_EVENT_COUNT ((1UL << (sizeof(SDLK_0) * 8)) / 8)


static bool g_events[__GE_EVENT_COUNT] = {};
static char g_text_input[32];
static bool g_keys_down[_AN_8TH_OF_THE_SDLK_EVENT_COUNT] = {};


void GE_initEvents(void) {
  for (int i = 0; i < _AN_8TH_OF_THE_SDLK_EVENT_COUNT; i++) {
    g_keys_down[i] = false;
  }
}


void GE_handleEvents(void) {
  for (int i = 0; i < __GE_EVENT_COUNT; i++) {
    g_events[i] = false;
  }

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
        g_keys_down[event.key.keysym.sym / 8] |= 1 << event.key.keysym.sym % 8;
        break;

      case SDL_KEYUP:
        g_keys_down[event.key.keysym.sym / 8] &= ~(1 << event.key.keysym.sym % 8);
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


bool GE_keyDown(SDL_Keycode k) {
  return g_keys_down[k / 8] &= 1 << k % 8;
}
