#pragma once

#include "strstrmap.h"
#include "bintree.h"

typedef struct BSTree BSTree;
struct BSTree
{
   BinTree *root; 
   size_t size;   
};

void    BSTree_init     (BSTree *self);
void    BSTree_deinit   (BSTree *self);
BSTree *BSTree_alloc();
void    BSTree_free     (BSTree *self);

size_t  BSTree_size     (BSTree *self);

int     getKey          (StrStrMap *value);

void    BSTree_insert(BSTree *self, StrStrMap *value); 
bool    BSTree_lookup(BSTree *self, int key);          
StrStrMap *BSTree_search(BSTree *self, int key);    
StrStrMap *BSTree_delete(BSTree *self, int key);  
void    BSTree_clear(BSTree *self);                  

static void insertNode(BinTree *node, BinTree *newNode);
static bool lookupKey(BinTree *self, int key);
static StrStrMap* searchValue(BinTree *self, int key);
static void clearBinTree(BinTree *self);
static void modifyTreeOnDelete(BinTree *node, BinTree *parent);
static BinTree *searchMin(BinTree *node);
void traverseInOrder(BinTree * node);