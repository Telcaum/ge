#ifndef TABLE_H
#define TABLE_H


#define TABLE_INITIAL_CAPACITY (8)
#define TABLE_MAX_LOAD (.75)


typedef struct {
  char *key;
  void *value;
} GE_Entry;


typedef struct {
  unsigned long capacity, length;
  GE_Entry *entries;
} GE_Table;


void GE_Table_init(GE_Table *table);
void GE_Table_free(GE_Table *table);

// The key is copied when adding a new entry, the value does not.
void GE_Table_set(GE_Table *table, char const *key, void *value);
GE_Entry *GE_Table_get(GE_Table *table, char const *key);
void GE_Table_remove(GE_Table *table, char const *key);


#endif
