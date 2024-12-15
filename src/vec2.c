#include "vec2.h"


GE_Vec2 GE_Vec2_add(GE_Vec2 v1, GE_Vec2 v2) {
  return (GE_Vec2){
    .x = v1.x + v2.x,
    .y = v1.y + v2.y,
  };
}


GE_Vec2 GE_Vec2_sub(GE_Vec2 v1, GE_Vec2 v2) {
  return (GE_Vec2){
    .x = v1.x - v2.x,
    .y = v1.y - v2.y,
  };
}
