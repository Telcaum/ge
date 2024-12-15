#include <SDL_image.h>
#include <SDL_ttf.h>

#include "common.h"
#include "core.h"
#include "event.h"


extern int _GE_MAIN_fps;


static SDL_Window *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;


void GE_init(char const *title, int w, int h) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    SDL_ERR();
  }
  if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) == 0) {
    SDL_ERR();
  }
  if (TTF_Init() != 0) {
    SDL_ERR();
  }

  GE_initEvents();

  g_window = SDL_CreateWindow(
    title,
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    w, h,
    SDL_WINDOW_RESIZABLE
  );
  if (g_window == NULL) {
    SDL_ERR();
  }

  g_renderer = SDL_CreateRenderer(g_window, -1, 0);
  if (g_renderer == NULL) SDL_ERR();
}


void GE_quit(void) {
  SDL_DestroyRenderer(g_renderer);
  g_renderer = NULL;
  SDL_DestroyWindow(g_window);
  g_window = NULL;
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}


SDL_Renderer *GE_renderer(void) {
  return g_renderer;
}


void GE_setFPS(int fps) {
  _GE_MAIN_fps = fps;
}
