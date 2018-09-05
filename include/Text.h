#pragma once

#include <string>
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"

enum TEXT_ALIGN
{
    RIGHT,  // Will ignore x component of position vector
    LEFT,   // Will ignore x component of position vector
    CENTER, // Will ignore x component of position vector
    FREE
};

class Text
{
  private:
    std::string m_content;
    Color m_color;
    Vector3 m_position;
    TEXT_ALIGN m_alignment;
    C2D_Text m_renderText;
    Vector2 m_scale;

  public:
    Text(const std::string &text,
         const Color &color,
         const Vector3 &pos,
         const Vector2 &size,
         TEXT_ALIGN alignment = TEXT_ALIGN::FREE)
        : m_content(text),
          m_color(color),
          m_position(pos),
          m_alignment(alignment),
          m_scale(size)
    {
    }

    std::string     getText()       { return m_content;     }
    Color&          getColor()      { return m_color;       }
    Vector2&        getSize()       { return m_scale;       }
    Vector3&        getPosition()   { return m_position;    }
    C2D_Text&       getRenderText() { return m_renderText;  }
    TEXT_ALIGN      getAlignment()  { return m_alignment;   }

    void setColor(const Color &c)           { m_color = c;      }
    void setText(const std::string &s)      { m_content = s;    }
    void setPosition(const Vector3 &pos)    { m_position = pos; }
    void setScale(const Vector2 &s)         { m_scale = s;      }
};