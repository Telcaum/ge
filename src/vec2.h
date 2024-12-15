#pragma once


typedef struct {
  int x, y;
} GE_Vec2;

typedef struct {
  double x, y;
} GE_Vec2f;


#define GE_TO_VEC2(_x, _y) ((GE_Vec2){ .x = (_x), .y = (_y), })
#define GE_FROM_VEC2(v) (v).x, (v).y

#define GE_FROM_VEC2F(v) GE_FROM_VEC2(v)


GE_Vec2 GE_Vec2_add(GE_Vec2 v1, GE_Vec2 v2);
GE_Vec2 GE_Vec2_sub(GE_Vec2 v1, GE_Vec2 v2);
