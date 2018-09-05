#pragma once

#include <string>
#include <vector>
#include <3ds.h>
#include <citro2d.h>

#include "Color.h"
#include "Text.h"
#include "Vector2.h"
#include "Vector3.h"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240
#define MAX_GLYPHS 4096

class FontManager
{
  private:
    C2D_TextBuf m_staticBuf, m_dynamicBuf, m_tmpBuf;
    
    std::vector<Text*> m_dynamicText;
    std::vector<Text> m_staticText;

    C3D_RenderTarget *m_targetScreen;

    float m_leftMargin = 10.0f;
    float m_rightMargin = 10.0f;

    void generateText(Text* t, C2D_TextBuf& buffer);
    void generateTextPosition(Text* text);


  public:
    FontManager(C3D_RenderTarget *screenTarget);
    FontManager(C3D_RenderTarget *screenTarget, float leftMargin, float rightMargin);

    ~FontManager();

    // Inits both buffers, dynamic and static
    void init();
    void destroy();

    // Draw the text to target screen
    void render();

    // Add static text to render
    // Static text won't change during the following renders
    void addStaticText(Text text);
    // Dynamic change can be changed because it is a reference to original created Text
    void addDynamicText(Text *text);

    void getTextDims(Text* t, Vector2& dims);
};