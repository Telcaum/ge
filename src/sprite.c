#include <stdlib.h>

#include <SDL_image.h>

#include "common.h"
#include "core.h"
#include "sprite.h"


struct GE_Sprite {
  SDL_Texture *texture;
  SDL_Rect rect;
  bool centered;
  double scale;
};

struct GE_SpriteX {
  GE_Sprite super;
  double angle;
};


GE_Sprite *GE_Sprite_new(char const *path, int x, int y, bool centered, double scale) {
  SDL_Surface *surface = IMG_Load(path);
  if (surface == NULL) SDL_ERR();
  SDL_Texture *texture = SDL_CreateTextureFromSurface(GE_renderer(), surface);
  if (texture == NULL) SDL_ERR();

  GE_Sprite *sprite = NEW(GE_Sprite);
  if (sprite == NULL) exit(1);

  sprite->texture = texture;
  sprite->rect = surface->clip_rect;
  sprite->rect.x = x;
  sprite->rect.y = y;
  sprite->centered = centered;
  sprite->scale = scale;

  SDL_FreeSurface(surface);
  return sprite;
}


void GE_Sprite_free(GE_Sprite *sprite) {
  SDL_DestroyTexture(sprite->texture);
  free(sprite);
}


void GE_Sprite_draw(GE_Sprite *sprite) {
  SDL_Rect rect = sprite->rect;
  rect.w *= sprite->scale;
  rect.h *= sprite->scale;

  if (sprite->centered) {
    rect.x -= rect.w / 2;
    rect.y -= rect.h / 2;
  }

  SDL_RenderCopy(GE_renderer(), sprite->texture, NULL, &rect);
}


void GE_Sprite_setPos(GE_Sprite *sprite, int x, int y) {
  sprite->rect.x = x;
  sprite->rect.y = y;
}


GE_Vec2 GE_Sprite_getPos(GE_Sprite *sprite) {
  return GE_TO_VEC2(sprite->rect.x, sprite->rect.y);
}


void GE_Sprite_setScale(GE_Sprite *sprite, double scale) {
  sprite->scale = scale;
}


double GE_Sprite_getScale(GE_Sprite *sprite) {
  return sprite->scale;
}


GE_SpriteX *GE_SpriteX_new(char const *path, int x, int y, bool centered, double scale, double angle) {
  GE_SpriteX *sprite = (GE_SpriteX *)GE_Sprite_new(path, x, y, centered, scale);
  sprite = realloc(sprite, sizeof(GE_SpriteX));
  if (sprite == NULL) exit(1);

  sprite->angle = angle;

  return sprite;
}


void GE_SpriteX_draw(GE_SpriteX *sprite) {
  SDL_Rect rect = sprite->super.rect;
  rect.w *= sprite->super.scale;
  rect.h *= sprite->super.scale;
  if (sprite->super.centered) {
    rect.x -= rect.w / 2;
    rect.y -= rect.h / 2;
  }

  SDL_RenderCopyEx(GE_renderer(), sprite->super.texture, NULL, &rect, sprite->angle, NULL, SDL_FLIP_NONE);
}


void GE_SpriteX_setAngle(GE_SpriteX *sprite, double angle) {
  sprite->angle = angle;
}


double GE_SpriteX_getAngle(GE_SpriteX *sprite) {
  return sprite->angle;
}
