#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "load.h"


char const *const GE_parse_err_msgs[] = {
  [GE_PARSE_ERR_MISSING_EQUAL] = "Missing equal sign.",
  [GE_PARSE_ERR_MISSING_VALUE] = "Missing value after equal sign.",
};


static bool loaded = false;
static GE_Table g_values;


typedef struct {
  char const *start;
  unsigned pos;
  GE_LoadParseError error;
} Parser;


#define CUR() (parser->start[parser->pos])
#define ADVANCE() parser->pos++;

static void Parser_skipWhite(Parser *parser) {
  for (;;) {
    switch (CUR()) {
      case ' ':
      case '\t':
      case '\r':
      case '\n':
        ADVANCE();
        break;

      default:
        return;
    }
  }
}


static bool Parser_atEnd(Parser *parser) {
  return CUR() == '\0';
}


static size_t Parser_getNameLen(Parser *parser) {
  unsigned startpos = parser->pos;
  while (CUR() != '=' && CUR() != '\0') ADVANCE();
  size_t length = parser->pos - startpos;
  parser->pos = startpos;
  return length;
}


static void Parser_getName(Parser *parser, char *dest, size_t len) {
  for (size_t i = 0; i < len; i++) {
    dest[i] = CUR();
    ADVANCE();
  }
  if (CUR() != '=') {
    parser->error = GE_PARSE_ERR_MISSING_EQUAL;
  }
  ADVANCE();
}


static double Parser_getValue(Parser *parser) {
  char *endptr;
  double value = strtod(&CUR(), &endptr);
  if (&CUR() == endptr) {
    parser->error = GE_PARSE_ERR_MISSING_VALUE;
    return 0.;
  }
  parser->pos += endptr - parser->start;
  return value;
}


static void Parser_parse(Parser *parser) {
  for (;;) {
    Parser_skipWhite(parser);

    if (Parser_atEnd(parser)) break;

    size_t name_len = Parser_getNameLen(parser);
    char name[name_len + 1];
    Parser_getName(parser, name, name_len);
    if (parser->error) return;
    
    double value = Parser_getValue(parser);
    if (parser->error) return;

    GE_Table_set(&g_values, name, (union { double d; void *p; }){ .d = value, }.p);
  }
}

#undef CUR
#undef ADVANCE


static GE_LoadParseError parse(char const *content) {
  Parser parser;
  parser.start = content;
  parser.pos = 0;
  parser.error = GE_PARSE_ERR_OK;

  Parser_parse(&parser);
  return parser.error;
}


GE_LoadParseError GE_loadLoadFile(char const *path) {
  loaded = true;

  GE_Table_init(&g_values);

  char *content = GE_readFile(path);
  if (content == NULL) {
    fprintf(stderr, "File '%s' does not exist.\n", path);
    exit(1);
  }

  GE_LoadParseError res = parse(content);

  free(content);
  if (res != 0) GE_unloadLoadFile();

  return res;
}


void GE_unloadLoadFile(void) {
  if (!loaded) return;

  GE_Table_free(&g_values);
}


double GE_loadValue(char const *name) {
  return (union { void *p; double d; }){ .p = GE_Table_get(&g_values, name)->value, }.d;
}
