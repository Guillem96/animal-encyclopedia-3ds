#pragma once

#include <string>
#include <citro2d.h>
#include "Vector2.h"
#include "Vector3.h"

class Image
{
  private:
    std::string m_name;
    Vector3 m_position;
    Vector2 m_scale;

  public:
    Image(const std::string name, const Vector3 &position, const Vector2 &scale) 
        : m_name(name),
          m_position(position),
          m_scale(scale) {}
    ~Image() { }

    const Vector3       &getPosition()  { return m_position; }
    const Vector2       &getScale()     { return m_scale; }
    const std::string   &getImageName() { return m_name; }
};
