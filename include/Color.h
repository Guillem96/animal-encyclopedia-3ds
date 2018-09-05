#pragma once
#include <citro2d.h>

class Color
{
  private:
    u32 m_color;

  public:
    Color(float r, float g, float b, float alpha)
    {
        m_color = C2D_Color32f(r, g, b, alpha);
    }
    
    u32 getColor() { return m_color; }
};