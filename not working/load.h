#pragma once

#include "table.h"


typedef enum {
  GE_PARSE_ERR_OK = 0,
  GE_PARSE_ERR_MISSING_EQUAL,
  GE_PARSE_ERR_MISSING_VALUE,
} GE_LoadParseError;


extern char const *const GE_parse_err_msgs[];


// Change values in your program without recompiling.
// Load file syntax:
// name=value
// Returns GE_PARSE_ERR_OK on success.
GE_LoadParseError GE_loadLoadFile(char const *path);
void GE_unloadLoadFile(void);
double GE_loadValue(char const *name);
