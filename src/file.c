#include <stdio.h>

#include "file.h"


bool GE_fileExists(char const *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) return false;
  fclose(file);
  return true;
}
