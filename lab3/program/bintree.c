#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"
#include "strstrmap.h"

void BinTree_init(BinTree *self, int key, StrStrMap *value)
{
    self->key = key;
    self->value = value;
    self->left = NULL;
    self->right = NULL;
}

void BinTree_deinit(BinTree *self)
{
}

BinTree *BinTree_alloc(int key, StrStrMap *value)
{
    BinTree *newNode = malloc(sizeof(BinTree));
    BinTree_init(newNode, key, value);
    return newNode;
}

void BinTree_free(BinTree *self)
{
    BinTree_deinit(self);
    free(self);
}