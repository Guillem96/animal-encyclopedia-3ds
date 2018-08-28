#pragma once

#include <string>
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"

enum TEXT_ALIGN
{
    RIGHT,
    LEFT,
    CENTER
};

class Text
{
  private:
    std::string m_content;
    Color m_color;
    Vector3 m_position;
    TEXT_ALIGN m_alignment;
    C2D_Text m_renderText;
    Vector2 m_size;

  public:
    Text(const std::string &text,
         const Color &color,
         const Vector3 &pos,
         const Vector2 &size,
         TEXT_ALIGN alignment) : m_content(text),
                                 m_color(color),
                                 m_position(pos),
                                 m_alignment(alignment),
                                 m_size(size)
    {
    }

    std::string     getText()       { return m_content; }
    Color&          getColor()      { return m_color; }
    const Vector2&  getSize()       { return m_size; }
    const Vector3&  getPosition()   { return m_position; }
    C2D_Text&       getRenderText() { return m_renderText; }
};