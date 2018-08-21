#pragma once

#include <string>
#include "Color.h"
#include "Vector2.h"

enum TEXT_ALIGN
{
    RIGHT,
    LEFT,
    CENTER
}

class Text
{
  private:
    std::string m_content;
    Color m_color;
    Vector2 m_position;
    TEXT_ALIGN m_alignment;
    C2D_Text* m_renderText;
    Vector2 m_size;
  public:

    Text(const std::string &text,
         const Color& color,
         const Vector2& pos,
         const Vector2& size,
         TEXT_ALIGN alignment) : m_color(color),
                                 m_position(pos), 
                                 m_content(text), 
                                 m_alignment(alignment),
                                 m_size(size)
    {
        m_renderText = nullptr;
    }

    std::string getText() { return m_content; }
    const Vector2 getSize() { return m_size; }
    const Vector2& getPosition() { return m_pos; }
    std::string getRenderText() { return m_renderText; }

}