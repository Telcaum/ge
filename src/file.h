#pragma once

#include <stdbool.h>


bool GE_fileExists(char const *path);
// You must free the pointer yourself.
char *GE_readFile(char const *path);
