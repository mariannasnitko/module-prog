#include "deque.h"

Deque::Deque()
{
    this->capacity_ = 20;
    this->first_ = 10;
    this->last_ = 10;
    this->items_ = static_cast<double *>(malloc(sizeof(this->items_[0]) * this->capacity_));
}

Deque::~Deque()
{
    free(this->items_);
}

void Deque::pushFront(double value)
{
    if (this->first_ == -1)
    {
        this->first_ = 0;
        this->last_ = 0;
    }
    else if (this->first_ == 0 || this->last_ == this->capacity_ - 1)
    {
        if (this->last_ + 1 < this->capacity_)
        {
            int newCap = this->capacity_ * 2;
            double *newItems = static_cast<double *>(realloc(this->items_, sizeof(this->items_[0]) * newCap));
            if (newItems == NULL)
            {
                free(this->items_);
                fprintf(stderr, "Reallocating memory error\n");
                abort();
            }
            this->items_ = newItems;
            this->capacity_ = newCap;
        }
        for (size_t i = this->last_; i >= this->capacity_; i--)
        {
            this->items_[i + 1] = this->items_[i - 1];
        }
        this->items_[this->last_] = value;
        this->last_++;
    }
    else
    {
        this->first_--;
    }
    this->items_[this->first_] = value;
}

void Deque::pushBack(double value)
{
    this->items_[this->last_] = value;
    this->last_ += 1;
    if (this->last_ == this->capacity_)
    {
        this->last_ = 0;
    }
    if (this->last_ == this->first_)
    {
        fprintf(stderr, "Deque is full");
        int newCap = this->capacity_ * 2;
        double *newItems = static_cast<double *>(realloc(this->items_, sizeof(this->items_[0]) * newCap));
        if (newItems == NULL)
        {
            free(this->items_);
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        this->items_ = newItems;
        this->capacity_ = newCap;
    }
}

double Deque::popFront()
{
    double value = this->items_[this->first_];
    this->items_[this->first_] = -1;
    if (this->first_ == this->last_)
    {
        this->first_ = -1;
        this->last_ = -1;
    }
    else if (this->first_ == this->capacity_ - 1)
    {
        this->first_ = 0;
    }
    else
    {
        this->first_++;
    }
    return value;
}

double Deque::popBack()
{
    double value = this->items_[this->last_];
    this->items_[this->last_] = -1;
    if (this->first_ == this->last_)
    {
        this->first_ = -1;
        this->last_ = -1;
    }
    else if (this->last_ == 0)
    {
        this->last_ = this->capacity_ - 1;
    }
    else
    {
        this->last_--;
    }
    return value;
}

size_t Deque::size()
{
    if (this->last_ >= this->first_)
        return this->last_ - this->first_;
    return this->capacity_ - this->first_ + this->last_;
}

bool Deque::isEmpty()
{
    if (this->first_ == -1)
    {
        return true;
    }
    return false;
}

void Deque::print()
{
    for (int i = this->first_; i < this->last_; i++)
    {
        printf("%d). %3.3lf\n", i, this->items_[i]);
    }
}