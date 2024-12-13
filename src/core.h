#pragma once

#include <stdbool.h>

#include <SDL.h>


void GE_init(char const *title, int w, int h);
void GE_quit(void);

SDL_Renderer *GE_renderer(void);
