#pragma once
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>

class List
{
    double *items_;
    size_t capacity_;
    size_t size_;

    void realloc(size_t newCapacity);

  public:
    List();
    ~List();

    size_t size();
    double &operator[](int index);
    void insert(int index, double value);
    void removeAt(int index);
    void add(double value);
    void remove(double value);
    int indexOf(double value);
    bool contains(double value);
    bool isEmpty();
    void clear();
};