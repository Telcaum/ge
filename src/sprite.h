#pragma once


typedef struct GE_Sprite GE_Sprite;


GE_Sprite *GE_Sprite_new(char const *path);
void GE_Sprite_free(GE_Sprite *sprite);
void GE_Sprite_draw(GE_Sprite *sprite);
