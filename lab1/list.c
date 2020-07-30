#include "list.h"

void List_init(List *self)
{
    self->capacity = 10;
    self->size = 0;
    self->items = malloc(sizeof(double) * self->capacity);
    if (self->items == NULL)
    {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
}

void List_deinit(List *self)
{
    free(self->items);
}

List *List_alloc(void)
{
    List *self = malloc(sizeof(List));
    List_init(self);
    return self;
}

void List_free(List *self)
{
    List_deinit(self);
    free(self);
}

size_t List_size(List *self)
{
    return self->size;
}

double List_get(List *self, int index)
{
    return self->items[index];
}

void List_set(List *self, int index, double value)
{
    self->items[index] = value;
}

void List_insert(List *self, int index, double value)
{
    if (index > self->size || index < 0)
    {
        fprintf(stderr, "ERROR: item cannot be inserted\n");
        abort();
    }
    else if (index == self->size)
    {
        List_add(self, value);
    }
    else if (index < self->size)
    {
        if (self->size + 1 < self->capacity)
        {
            int newCap = self->capacity + 1;
            void *newItems = realloc(self->items, sizeof(double) * newCap);
            if (newItems == NULL)
            {
                free(self->items);
                fprintf(stderr, "Reallocating memory error\n");
                abort();
            }
            self->items = newItems;
            self->capacity = newCap;
        }
        for (size_t i = self->size; i >= index; i--)
        {
            self->items[i + 1] = self->items[i - 1];
        }
        self->items[index] = value;
        self->size++;
    }
}

void List_removeAt(List *self, int index)
{
    if (index < 0 || index > self->size)
    {
        abort();
    }
    else
    {
        for (int i = index - 1; i < self->size - 1; i++)
        {
            self->items[i] = self->items[i + 1];
        }
        self->size--;
    }
}

void List_add(List *self, double value)
{
    self->items[self->size] = value;
    self->size += 1;
    if (self->size == self->capacity)
    {
        int newCap = self->capacity * 2;
        void *newItems = realloc(self->items, sizeof(double) * newCap);
        if (newItems == NULL)
        {
            free(self->items);
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        self->items = newItems;
        self->capacity = newCap;
    }
}

void List_remove(List *self, double value)
{
    for (size_t i = 0; i < self->size; i++)
    {
        if (self->items[i] == value)
        {
            free(&self->items[i]);
            for (size_t j = i; j < self->size; j++)
            {
                if (j != self->size - 1)
                {
                    self->items[j] = self->items[j + 1];
                }
            }
            self->size--;
            return;
        }
    }
    printf("ERROR: value does not exist\n");
}

int List_indexOf(List *self, double value)
{
    for (size_t i = 0; i < self->size; i++)
    {
        if (self->items[i] == value)
        {
            return i;
        }
    }
    printf("ERROR: value does not exist\n");
    return -1;
}

bool List_contains(List *self, double value)
{
    for (size_t i = 0; i < self->size; i++)
    {
        if (self->items[i] == value)
        {
            return 1;
        }
    }
    return 0;
}

bool List_isEmpty(List *self)
{
    if (self->size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void List_clear(List *self)
{
    self->size = 0;
}
