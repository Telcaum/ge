#pragma once

#include <stdbool.h>

#include <SDL.h>


void GE_init(char const *title, int w, int h);
void GE_quit(void);

SDL_Renderer *GE_renderer(void);

// Caps the amount of FPS
// -1 is no cap
void GE_setFPS(int fps);
