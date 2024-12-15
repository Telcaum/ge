#pragma once

#include <stdbool.h>

#include "vec2.h"


typedef struct GE_Sprite GE_Sprite;
typedef struct GE_SpriteX GE_SpriteX;


GE_Sprite *GE_Sprite_new(char const *path, int x, int y, bool centered, double scale);
void GE_Sprite_free(GE_Sprite *sprite);
void GE_Sprite_draw(GE_Sprite *sprite);

void GE_Sprite_setPos(GE_Sprite *sprite, int x, int y);
GE_Vec2 GE_Sprite_getPos(GE_Sprite *sprite);
void GE_Sprite_setScale(GE_Sprite *sprite, double scale);
double GE_Sprite_getScale(GE_Sprite *sprite);


GE_SpriteX *GE_SpriteX_new(char const *path, int x, int y, bool centered, double scale, double angle);
#define GE_SpriteX_free(sprite) GE_Sprite_free((GE_Sprite *)(sprite))
void GE_SpriteX_draw(GE_SpriteX *sprite);

#define GE_SpriteX_setPos(sprite, ...) GE_Sprite_setPos((GE_Sprite *)(sprite), __VA_ARGS__)
#define GE_SpriteX_getPos(sprite) GE_Sprite_getPos((GE_Sprite *)(sprite))
#define GE_SpriteX_setScale(sprite, scale) GE_Sprite_setScale((GE_Sprite *)(sprite), (scale))
#define GE_SpriteX_getScale(sprite, scale) GE_Sprite_getScale((GE_Sprite *)(sprite))
void GE_SpriteX_setAngle(GE_SpriteX *sprite, double angle);
double GE_SpriteX_getAngle(GE_SpriteX *sprite);
