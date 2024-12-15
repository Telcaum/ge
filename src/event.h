#pragma once

#include <stdbool.h>

#include <SDL.h>

#include "vec2.h"


typedef enum {
  GE_E_QUIT,

  GE_E_LEFT_CLICK,
  GE_E_RIGHT_CLICK,

  GE_E_TEXT_INPUT,

  __GE_EVENT_COUNT
} GE_Event;


void GE_initEvents(void);
void GE_handleEvents(void);

bool GE_event(GE_Event event);
void GE_startTextInput(void);
void GE_stopTextInput(void);
char const *GE_textInput(void);
GE_Vec2 GE_getMousePos(void);
bool GE_keyDown(SDL_Keycode k);
