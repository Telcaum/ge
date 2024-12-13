#include <stdlib.h>

#include <SDL_image.h>

#include "common.h"
#include "core.h"
#include "sprite.h"


struct GE_Sprite {
  SDL_Texture *texture;
  SDL_Rect rect;
};


GE_Sprite *GE_Sprite_new(char const *path) {
  SDL_Surface *surface = IMG_Load(path);
  if (surface == NULL) SDL_ERR();
  SDL_Texture *texture = SDL_CreateTextureFromSurface(GE_renderer(), surface);
  if (texture == NULL) SDL_ERR();
  GE_Sprite *sprite = NEW(GE_Sprite);
  if (sprite == NULL) exit(1);
  sprite->texture = texture;
  sprite->rect = surface->clip_rect;
  SDL_FreeSurface(surface);
  return sprite;
}


void GE_Sprite_free(GE_Sprite *sprite) {
  SDL_DestroyTexture(sprite->texture);
  free(sprite);
}


void GE_Sprite_draw(GE_Sprite *sprite) {
  SDL_RenderCopy(GE_renderer(), sprite->texture, NULL, &sprite->rect);
}
