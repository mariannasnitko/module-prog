#pragma once

#include <stdlib.h>
#include "list.h"

typedef struct
{
    const char *key;
    const char *value;
} KeyValue;

struct StrStrMap
{
    KeyValue * items;
    int size;
    int capacity;
};
typedef struct StrStrMap StrStrMap;

StrStrMap *StrStrMap_alloc();
void StrStrMap_init(StrStrMap *self);
void StrStrMap_deinit(StrStrMap *self);
void StrStrMap_free(StrStrMap *self);

size_t StrStrMap_size(StrStrMap *self);

void StrStrMap_add(StrStrMap *self, const char *key, const char *value);
bool StrStrMap_contains(StrStrMap *self, const char *key);
const char *StrStrMap_get(StrStrMap *self, const char *key);
const char *StrStrMap_set(StrStrMap *self, const char *key, const char *value);
const char *StrStrMap_remove(StrStrMap *self, const char *key);
void StrStrMap_clear(StrStrMap *self);
 
void StrStrMap_keys(StrStrMap *self, List *keys);
void StrStrMap_values(StrStrMap *self, List *values);