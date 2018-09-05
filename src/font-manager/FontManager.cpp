#include "FontManager.h"

FontManager::FontManager(C3D_RenderTarget *screenTarget) : m_targetScreen(screenTarget)
{
}

FontManager::FontManager(C3D_RenderTarget *screenTarget,
                         float leftMargin,
                         float rightMargin)
                            : m_targetScreen(screenTarget),
                            m_leftMargin(leftMargin),
                            m_rightMargin(rightMargin)
{
}

FontManager::~FontManager()
{
}

void FontManager::init()
{
    m_staticBuf = C2D_TextBufNew(MAX_GLYPHS);
    m_dynamicBuf = C2D_TextBufNew(MAX_GLYPHS);
    m_tmpBuf = C2D_TextBufNew(MAX_GLYPHS);
}

void FontManager::render()
{
    C2D_TextBufClear(m_dynamicBuf);

    // Render static text
    for (Text &t : m_staticText)
    {
        Vector3 pos = t.getPosition();
        Vector2 scale = t.getSize();
        C2D_DrawText(&t.getRenderText(), C2D_WithColor | C2D_AtBaseline, pos.x, pos.y, pos.z, scale.x, scale.y, t.getColor().getColor());
    }

    // Generate & render dynamic text
    for (Text *t : m_dynamicText)
    {
        Vector3 pos = t->getPosition();
        Vector2 scale = t->getSize();
        generateText(t, m_dynamicBuf);
        C2D_DrawText(&t->getRenderText(), C2D_WithColor | C2D_AtBaseline, pos.x, pos.y, pos.z, scale.x, scale.y, t->getColor().getColor());
    }
}

void FontManager::destroy()
{
    m_staticText.clear();
    m_dynamicText.clear();

    C2D_TextBufClear(m_dynamicBuf);
    C2D_TextBufClear(m_staticBuf);
    C2D_TextBufClear(m_tmpBuf);

    C2D_TextBufDelete(m_dynamicBuf);
    C2D_TextBufDelete(m_staticBuf);
    C2D_TextBufDelete(m_tmpBuf);
}

void FontManager::generateText(Text *t, C2D_TextBuf &buffer)
{
    C2D_TextParse(&t->getRenderText(), buffer, t->getText().c_str());
    C2D_TextOptimize(&t->getRenderText());
}

void FontManager::addStaticText(Text text)
{
    generateText(&text, m_staticBuf);
    m_staticText.push_back(text);
}

void FontManager::addDynamicText(Text *text)
{
    m_dynamicText.push_back(text);
}

void FontManager::getTextDims(Text *t, Vector2 &dims)
{
    generateText(t, m_tmpBuf);
    C2D_TextGetDimensions(&t->getRenderText(), t->getSize().x, t->getSize().y, &dims.x, &dims.y);
}

void FontManager::generateTextPosition(Text *text)
{

    switch (text->getAlignment())
    {
        case FREE:
            break;
        
        case LEFT:
            text->getPosition().x = m_leftMargin;
            break;

        case RIGHT:
        {
            Vector2 dims(0.0f, 0.0f);
            getTextDims(text, dims);
            text->getPosition().x = SCREEN_WIDTH - dims.x - m_rightMargin;
            break;
        }
        case CENTER:
        {
            Vector2 dims(0.0f, 0.0f);
            getTextDims(text, dims);
            text->getPosition().x = SCREEN_WIDTH / (float)2 - dims.x / (float)2;
            break;
        }
    }
}
