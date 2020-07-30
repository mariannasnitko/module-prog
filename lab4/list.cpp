#include "list.h"
#include <iostream>
#include <cassert>

List::List()
{
    this->capacity_ = 10;
    this->size_ = 0;
    this->items_ = static_cast<double *>(malloc(sizeof(this->items_[0]) * this->capacity_));
    if (this->items_ == NULL)
    {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
}

List::~List()
{
    free(this->items_);
}

void List::realloc(size_t newCapacity)
{
    double *newArray = static_cast<double *>(std::realloc(this->items_, sizeof(this->items_[0]) * newCapacity));
    if (newArray == NULL)
    {
        std::cerr << "Reallocation error" << std::endl;
        abort();
    }
    this->items_ = newArray;
    this->capacity_ = newCapacity;
}

size_t List::size()
{
    return this->size_;
}

double &List::operator[](int index)
{
    if (index < 0 || index > this->size())
    {
        abort();
    }
    return this->items_[index];
}

void List::insert(int index, double value)
{
    if (index < 0 || index > this->size())
    {
        abort();
    }

    if (this->size_ == this->capacity_)
    {
        int newCapacity = this->capacity_ * 2;
        realloc(newCapacity);
    }

    for (int i = this->size_ - 1; i >= index; i--)
    {
        this->items_[i + 1] = this->items_[i];
    }
    this->items_[index] = value;
    this->size_ += 1;
}

void List::removeAt(int index)
{
    if (index < 0 || index > this->size())
    {
        abort();
    }
    for (int i = index; i < this->size(); i++)
    {
        this->items_[i] = this->items_[i + 1];
    }
    this->size_ -= 1;
}

void List::add(double value)
{
    this->items_[this->size_] = value;
    this->size_ += 1;
    if (this->size_ == this->capacity_)
    {
        int newCapacity = this->capacity_ * 2;
        realloc(newCapacity);
    }
}

void List::remove(double value)
{
    this->removeAt(this->indexOf(value));
}

int List::indexOf(double value)
{
    for (size_t i = 0; i < this->size(); i++)
    {
        if (this->items_[i] == value)
        {
            return i;
        }
    }
    printf("ERROR: value does not exist\n");
    return -1;
}

bool List::contains(double value)
{
    for (size_t i = 0; i < this->size_; i++)
    {
        if (this->items_[i] == value)
        {
            return 1;
        }
    }
    return 0;
}

bool List::isEmpty()
{
    if (this->size_ == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void List::clear()
{
    this->size_ = 0;
}