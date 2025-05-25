#include "MovingAverage.hpp"

MovingAverage::MovingAverage(int size)
{
    this->size = size;
    this->queue = new float[size];
    for (size_t i = 0; i < size; i++)
        this->queue[i] = 0.0f;
}

float MovingAverage::next(float val)
{
    int tail = (this->head + 1) % this->size;
    
    this->count++;
    this->windowSum = this->windowSum - this->queue[tail] + val;
    this->head = (this->head + 1) % this->size;
    this->queue[this->head] = val;
    
    return ((float)this->windowSum) / ((float)MIN(this->size, this->count));
}

MovingAverage::~MovingAverage()
{ delete this->queue; }