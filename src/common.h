#pragma once

#include <stdio.h>

#include <SDL.h>


#define SDL_ERR() do { \
  fprintf(stderr, "Error: %s\n", SDL_GetError()); \
  exit(1); \
} while (0)


#define NEW(T) ((T *)malloc(sizeof(T)))
