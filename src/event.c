#include "common.h"
#include "event.h"


static bool g_events[__GE_EVENT_COUNT] = {};


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
    }
  }
}


bool GE_event(GE_Event event) {
  return g_events[event];
}
