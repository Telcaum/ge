#pragma once

#include <stdlib.h>


#define LIST_INITIAL_CAPACITY 8


#define list_t(T) struct { \
  unsigned length, capacity; \
  T *data; \
}


#define list_init(l) do { \
  (l)->data = malloc(sizeof(*(l)->data) * LIST_INITIAL_CAPACITY); \
  if ((l)->data == NULL) exit(1); \
  (l)->capacity = LIST_INITIAL_CAPACITY; \
  (l)->length = 0; \
} while (0)


#define list_from_array(l, arr, arr_len) do { \
  list_init(l); \
  for (int i = 0; i < (arr_len); i++) { \
    list_push((l), (arr)[i]); \
} while (0)


#define list_free(l) do { \
  free((l)->data); \
  (l)->length = 0; \
  (l)->capacity = 0; \
} while (0)


#define _list_grow(l) do { \
  (l)->data = realloc((l)->data, (l)->capacity *= 2); \
  if ((l)->data == NULL) exit(1); \
} while (0)


#define list_push(l, v) do { \
  if ((l)->length == (l)->capacity) { \
    _list_grow(l); \
  } \
  (l)->data[(l)->length++] = (v); \
} while (0)


#define list_pop(l) ((l)->data[--(l)->length])


#define list_clear(l) do { (l)->length = 0; } while (0)


#define list_append_array(l, arr, len) do { \
  for (int i = 0; i < (len); i++) { \
    list_push((l), (arr)[i]); \
  } \
} while (0)


typedef list_t(int) list_int_t;
typedef list_t(char) list_char_t;
