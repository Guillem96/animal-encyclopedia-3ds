#pragma once

#define IGNORE_VALUE -1.0f

class Vector3
{
  public:
    float x;
    float y;
    float z;

    Vector3(){ }
    Vector3(float x, float y, float z) : x(x), y(y), z(z) { }
};