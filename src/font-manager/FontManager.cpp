#include "FontManager.h"

FontManager::FontManager(C3D_RenderTarget *screenTarget)
{
    m_targetScreen = screenTarget;
}

FontManager::~FontManager()
{
}

void FontManager::init()
{
    m_staticBuf = C2D_TextBufNew(MAX_GLYPHS);
    m_dynamicBuf = C2D_TextBufNew(MAX_GLYPHS);

    for (Text &t : m_staticText)
    {
        printf("Generating static text: %s\n", t.getText().c_str());
        generateText(&t, m_staticBuf);
    }
}

void FontManager::render()
{
    C2D_TextBufClear(m_dynamicBuf);

    // Render static text
    for (Text &t : m_staticText)
    {
        Vector2 pos = t.getPosition();
        printf("Render static text at: %f %f\n", pos.x, pos.y);
        Vector2 scale = t.getSize();
        C2D_DrawText(&t.getRenderText(), C2D_AtBaseline | C2D_WithColor, pos.x, pos.y, 0.5f, scale.x, scale.y, t.getColor().getColor());
    }

    // Generate dynamic text
    for (Text *t : m_dynamicText)
    {
        Vector2 pos = t->getPosition();
        Vector2 scale = t->getSize();
        printf("Render dynamic text at: %f %f\n", pos.x, pos.y);
        generateText(t, m_dynamicBuf);
        C2D_DrawText(&t->getRenderText(), C2D_AtBaseline | C2D_WithColor, pos.x , pos.y, 0.5f, scale.x, scale.y, t->getColor().getColor());
    }
}

void FontManager::destroy()
{
    C2D_TextBufDelete(m_dynamicBuf);
    C2D_TextBufDelete(m_staticBuf);
}

void FontManager::generateText(Text *t, C2D_TextBuf &buffer)
{
    C2D_TextParse(&t->getRenderText(), buffer, t->getText().c_str());
    C2D_TextOptimize(&t->getRenderText());
}

void FontManager::addStaticText(Text text)
{
    printf("Adding static text: %s\n", text.getText().c_str());
    m_staticText.push_back(text);
}

void FontManager::addDynamicText(Text *text)
{
    printf("Adding Dynamix text: %s\n", text->getText().c_str());
    m_dynamicText.push_back(text);
}
