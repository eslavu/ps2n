#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

#include <stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

class MovingAverage
{
private:
  int size,
    head = 0,
    count = 0;
  float windowSum = 0.0f;
  float *queue;

public:
  MovingAverage(int);

  float next(float);

  ~MovingAverage();
};

#endif