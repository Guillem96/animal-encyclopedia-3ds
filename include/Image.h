#pragma once

#include <string>

#include "Vector2.h"
#include "Vector3.h"

class Image
{
private:
    Vector2 m_scale;
    Vector3 m_position;
    std::string m_name;

public:
    Image(const Vector3& position, const Vector2& scale) : m_position(position), m_scale(scale) { }
    ~Image();

    const Vector3&      getPosition()   { return m_position; }
    const Vector2&      getScale()      { return m_scale; }
    const std::string&  getImageName()  { return m_name; }
};
