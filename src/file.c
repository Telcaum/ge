#include <stdio.h>
#include <stdlib.h>

#include "file.h"


bool GE_fileExists(char const *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) return false;
  fclose(file);
  return true;
}


char *GE_readFile(char const *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) return NULL;

  fseek(file, 0, SEEK_END);
  size_t length = ftell(file);
  rewind(file);

  char *buf = malloc(sizeof(char) * (length + 1));
  if (buf == NULL) {
    fprintf(stderr, "Not enough memory to read '%s'.\n", path);
    exit(1);
  }

  size_t bytes_read = fread(buf, sizeof(char), length, file);
  if (bytes_read < length) {
    fprintf(stderr, "Failed to read file '%s'.\n", path);
    exit(1);
  }

  fclose(file);
  buf[length] = '\0';
  return buf;
}
