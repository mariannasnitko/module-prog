#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"
#include "strstrmap.h"

void BSTree_init(BSTree *self)
{
    self->root = NULL;
    self->size = 0;
}
void BSTree_deinit(BSTree *self)
{
}

BSTree *BSTree_alloc()
{
    BSTree *newTree = malloc(sizeof(BSTree));
    BSTree_init(newTree);
    return newTree;
}

void BSTree_free(BSTree *self)
{
    BSTree_deinit(self);
    free(self);
}

size_t BSTree_size(BSTree *self)
{
    return self->size;
}

int getKey(StrStrMap *value)
{
    return atoi(StrStrMap_get(value, "id"));
}

void BSTree_insert(BSTree *self, StrStrMap *value)
{
    int key = getKey(value);
    BinTree *newValue = BinTree_alloc(key, value);
    self->size += 1;
    if (self->root == NULL)
    {
        self->root = newValue;
    }
    else
    {
        insertNode(self->root, newValue);
    }
}

static void insertNode(BinTree *node, BinTree *newNode)
{
    if (newNode->key == node->key)
    {
        fprintf(stderr, "Key %i already exists in BST\n", newNode->key);
        abort();
    }
    else if (newNode->key < node->key)
    {
        if (node->left == NULL)
        {
            node->left = newNode;
        }
        else
        {
            insertNode(node->left, newNode);
        }
    }
    else if (newNode->key > node->key)
    {
        if (node->right == NULL)
        {
            node->right = newNode;
        }
        else
        {
            insertNode(node->right, newNode);
        }
    }
}

bool BSTree_lookup(BSTree *self, int key)
{
    return lookupKey(self->root, key);
}

static bool lookupKey(BinTree *self, int key)
{
    if (self == NULL)
    {
        return false;
    }
    if (key < self->key)
    {
        return lookupKey(self->left, key);
    }
    else if (key > self->key)
    {
        return lookupKey(self->right, key);
    }
    return true;
}

StrStrMap *BSTree_search(BSTree *self, int key)
{
    return searchValue(self->root, key);
}

static StrStrMap *searchValue(BinTree *self, int key)
{
    if (self == NULL)
    {
        return NULL;
    }
    if (self->key == key)
    {
        return self->value;
    }
    else if (key < self->key)
    {
        return searchValue(self->left, key);
    }
    else if (key > self->key)
    {
        return searchValue(self->right, key);
    }
    return NULL;
}

void BSTree_clear(BSTree *self)
{
    clearBinTree(self->root);
}

static void clearBinTree(BinTree *self)
{
    if (self == NULL)
    {
        return;
    }
    clearBinTree(self->left);
    clearBinTree(self->right);
    BinTree_free(self);
}

StrStrMap *delete (BinTree *node, int key, BinTree *parent)
{
    if (node == NULL)
    {
        fprintf(stderr, "Key `%i` not found on deletion\n", key);
        abort();
    }
    if (key < node->key)
    {
        return delete (node->left, key, node);
    }
    else if (key > node->key)
    {
        return delete (node->right, key, node);
    }
    else
    {
        modifyTreeOnDelete(node, parent);
        StrStrMap *deletedValue = node->value;
        BinTree_free(node);
        return deletedValue;
    }
}

static void modifyTreeOnDelete(BinTree *node, BinTree *parent)
{
    BinTree *replacementNode = NULL;
    if (node->left == NULL && node->right == NULL)
    {
        replacementNode = NULL;
    }
    else if (node->left == NULL || node->right == NULL)
    {
        BinTree *child = (node->left != NULL) ? node->left : node->right;
        replacementNode = child;
    }
    else
    {
        BinTree *minNode = searchMin(node->right);
        StrStrMap *deletedValue = delete (node->right, minNode->key, node);
        BinTree *newMin = BinTree_alloc(getKey(deletedValue), deletedValue);
        newMin->left = node->left;
        newMin->right = node->right;
        replacementNode = newMin;
    }
    if (parent->left == node)
    {
        parent->left = replacementNode;
    }
    else
    {
        parent->right = replacementNode;
    }
}

static BinTree *searchMin(BinTree *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->left == NULL)
    {
        return node;
    }
    return searchMin(node->left);
}

StrStrMap *BSTree_delete(BSTree *self, int key)
{
    BinTree fakeParent;
    fakeParent.left = self->root;
    StrStrMap *old = delete (self->root, key, &fakeParent);
    self->root = fakeParent.left;
    return old;
}

void traverseInOrder(BinTree *node)
{
    if (node == NULL)
    {
        return;
    }
    traverseInOrder(node->left);
    List values;
    List_init(&values);
    StrStrMap_values(node->value, &values);
    for (size_t i = 0; i < List_size(&values); i++)
    {
        if (i == 0)
        {
            printf("key: %s ", (char *)List_get(&values, i));
        }
        else
        {
            printf("%s ", (char *)List_get(&values, i));
        }
    }
    List_deinit(&values);
    printf("\n");
    traverseInOrder(node->right);
}