#pragma once

#include <stdbool.h>


typedef enum {
  GE_E_QUIT,

  GE_E_LEFT_CLICK,

  GE_E_TEXT_INPUT,

  __GE_EVENT_COUNT
} GE_Event;


void GE_handleEvents(void);
bool GE_event(GE_Event event);
char const *GE_textInput(void);
