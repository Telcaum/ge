#include "common.h"
#include "event.h"


static bool g_events[__GE_EVENT_COUNT] = {};
static char g_text_input[32];


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
        }
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


char const *GE_textInput(void) {
  return g_text_input;
}
