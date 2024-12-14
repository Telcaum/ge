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


int main() {
  GE_init("test", 800, 450);
  SDL_StopTextInput();

  list_char_t buf;
  list_init(&buf);

  GE_load();

  for (;;) {
    GE_handleEvents();
    if (GE_event(GE_E_QUIT)) break;

    GE_update();

    if (SDL_SetRenderDrawColor(GE_renderer(), 0, 0, 0, 255) != 0) SDL_ERR();
    if (SDL_RenderClear(GE_renderer()) != 0) SDL_ERR();

    GE_draw();

    SDL_RenderPresent(GE_renderer());
  }

  GE_unload();

  GE_quit();
  return 0;
}
