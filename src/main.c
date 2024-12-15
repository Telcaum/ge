#include <stdio.h>
#include <string.h>

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "common.h"
#include "core.h"
#include "event.h"
#include "file.h"
#include "list.h"
#include "sprite.h"
#include "test.h"


int _GE_MAIN_fps = -1;


static Uint64 capFPS(Uint64 start_tick) {
  Uint64 end_tick = SDL_GetTicks64();
  Uint64 dt = end_tick - start_tick;

  if (1000. / _GE_MAIN_fps > dt) {
    SDL_Delay(1000. / _GE_MAIN_fps - dt);
  }

  return SDL_GetTicks64();
}


int main() {
  GE_init("test", 800, 450);
  SDL_StopTextInput();

  list_char_t buf;
  list_init(&buf);

  GE_load();

  double dt = 0;
  Uint64 tick = SDL_GetTicks64();

  for (;;) {
    GE_handleEvents();
    if (GE_event(GE_E_QUIT)) break;

    GE_update(dt);

    if (SDL_SetRenderDrawColor(GE_renderer(), 0, 0, 0, 255) != 0) SDL_ERR();
    if (SDL_RenderClear(GE_renderer()) != 0) SDL_ERR();

    GE_draw();

    SDL_RenderPresent(GE_renderer());

    Uint64 end_tick = capFPS(tick);
    dt = (end_tick - tick) / 1000.;
    tick = end_tick;
  }

  GE_unload();

  GE_quit();
  return 0;
}
