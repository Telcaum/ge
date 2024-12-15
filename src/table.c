#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


void GE_Table_init(GE_Table *table) {
  table->capacity = TABLE_INITIAL_CAPACITY;
  table->length = 0;
  table->entries = (GE_Entry *)calloc(table->capacity, sizeof(GE_Entry));
  if (table->entries == NULL) {
    fprintf(stderr, "Out of memory: failed to initialize table.\n");
    exit(1);
  }
}


static void freeEntry(GE_Entry *entry) {
  free(entry->key);
}


static void freeEntries(GE_Entry *entries, size_t capacity) {
  for (int i = 0; i < capacity; i++) {
    if (entries[i].key != NULL && *entries[i].key != '\0') freeEntry(&entries[i]);
  }
  free(entries);
}


void GE_Table_free(GE_Table *table) {
  freeEntries(table->entries, table->capacity);
}


static uint64_t hashKey(char const *key, size_t key_length) {
  uint64_t hash = 14695981039346656037UL;

  for (size_t i = 0; i < key_length; i++) {
    hash ^= key[i];
    hash *= 1099511628211;
  }

  return hash;
}


GE_Entry *GE_Table_get(GE_Table *table, char const *key) {
  uint64_t hash = hashKey(key, strlen(key));

  size_t i = hash & (table->capacity - 1);
  for (;;) {
    GE_Entry *entry = &table->entries[i];
    if (entry->key == NULL) {
      return NULL;
    }
    if (strcmp(entry->key, key) == 0) {
      return entry;
    }
    i = (i + 1) & (table->capacity - 1);
  }
}


static int _setEntry(GE_Entry *entries, size_t capacity, char const *key, void *value) {
  uint64_t hash = hashKey(key, strlen(key));

  GE_Entry *first_empty = NULL;

  size_t i = hash & (capacity - 1);
  for (;;) {
    GE_Entry *entry = &entries[i];
    if (entry->key == NULL || *entry->key == '\0') {
      first_empty = entry;
      break;
    }
    if (strcmp(entry->key, key) == 0) {
      entry->value = value;
      return 0;
    }
    i = (i + 1) & (capacity - 1);
  }

  char *owned_key = (char *)malloc((strlen(key) + 1) * sizeof(char));
  if (owned_key == NULL) {
    fprintf(stderr, "Out of memory: could not clone the key of a table entry.\n");
    exit(1);
  }
  memcpy(owned_key, key, (strlen(key) + 1) * sizeof(char));
  first_empty->key = owned_key;
  first_empty->value = value;
  return 1;
}


static void growTable(GE_Table *table) {
  GE_Entry *new_entries = (GE_Entry *)calloc(table->capacity << 1, sizeof(GE_Entry));
  if (new_entries == NULL) {
    fprintf(stderr, "Out of memory: failed to grow table's capacity.\n");
    exit(1);
  }

  table->length = 0;
  for (size_t i = 0; i < table->capacity; i++) {
    GE_Entry *entry = &table->entries[i];
    if (entry->key != NULL && *entry->key != '\0') {
      table->length += _setEntry(new_entries, table->capacity << 1, entry->key, entry->value);
    }
  }

  freeEntries(table->entries, table->capacity);
  table->entries = new_entries;
  table->capacity <<= 1;
}


void GE_Table_set(GE_Table *table, char const *key, void *value) {
  if (table->length / (double)table->capacity > TABLE_MAX_LOAD) {
    growTable(table);
  }

  table->length += _setEntry(table->entries, table->capacity, key, value);
}


void GE_Table_remove(GE_Table *table, char const *key) {
  GE_Entry *entry = GE_Table_get(table, key);
  if (entry == NULL) return;
  freeEntry(entry);
  entry->key = "";
  entry->value = NULL;
}

