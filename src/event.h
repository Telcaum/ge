#pragma once

#include <stdbool.h>


typedef enum {
  GE_E_QUIT,

  __GE_EVENT_COUNT
} GE_Event;


void GE_handleEvents(void);
bool GE_event(GE_Event event);
