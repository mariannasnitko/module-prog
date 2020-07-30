#pragma once

#include "strstrmap.h"

typedef struct BinTree BinTree;
struct BinTree
{
   int key;         
   StrStrMap *value;
   BinTree *left;   
   BinTree *right;  
};

void    BinTree_init    (BinTree *self, int key, StrStrMap *value);
void    BinTree_deinit  (BinTree *self);

BinTree *BinTree_alloc  (int key, StrStrMap *value);
void    BinTree_free    (BinTree *self);