#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

class Deque
{
    double *items_;
    int capacity_;
    int first_;
    int last_;

  public:
    Deque();
    ~Deque();
    void pushBack(double value);
    double popBack();
    void pushFront(double value);
    double popFront();
    size_t size();
    bool isEmpty();
    void print();
};
