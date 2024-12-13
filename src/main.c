#include <stdio.h>
#include <string.h>

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "common.h"
#include "core.h"
#include "file.h"
#include "list.h"
#include "sprite.h"


int main() {
  GE_init("test", 800, 450);
  SDL_StopTextInput();

  list_char_t buf;
  list_init(&buf);
  GE_Sprite *sprite = NULL;

  SDL_Event event;
  bool done = false;
  for (;;) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          done = true;
          break;

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_e:
              SDL_StartTextInput();
              break;

            case SDLK_RETURN:
              SDL_StopTextInput();
              list_push(&buf, '\0');
              printf("\n%s\n", buf.data);
              if (sprite != NULL) GE_Sprite_free(sprite);
              sprite = NULL;
              if (!GE_fileExists(buf.data)) {
                fprintf(stderr, "File does not exist.\n");
              }
              else {
                sprite = GE_Sprite_new(buf.data);
              }
              list_clear(&buf);
              break;
          }
          break;

        case SDL_TEXTINPUT:
          for (int _ = 0; _ < strlen(event.text.text); _++) {
            list_push(&buf, '\0');
            printf("%c", event.text.text[_]);
            fflush(stdout);
          }
          strcat(buf.data, event.text.text);
          break;
      }
    }

    if (done) break;

    if (SDL_SetRenderDrawColor(GE_renderer(), 0, 0, 0, 255) != 0) SDL_ERR();
    if (SDL_RenderClear(GE_renderer()) != 0) SDL_ERR();

    if (sprite != NULL) GE_Sprite_draw(sprite);

    SDL_RenderPresent(GE_renderer());
  }

  if (sprite != NULL) GE_Sprite_free(sprite);

  GE_quit();
  return 0;
}
