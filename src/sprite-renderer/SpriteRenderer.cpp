#include "SpriteRenderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <citro3d.h>

SpriteRenderer::SpriteRenderer(C3D_RenderTarget *screenTarget,
                               const std::string &spriteSheetPath) :  m_targetScreen(screenTarget),
                                                                        m_spriteSheetPath(spriteSheetPath)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::init()
{
    m_spriteSheet = C2D_SpriteSheetLoad(m_spriteSheetPath.c_str());
    if (!m_spriteSheet)
    {
        printf("ERROR: Loading spritesheet from %s", m_spriteSheetPath.c_str());
    }
}

void SpriteRenderer::destroy()
{
    C2D_SpriteSheetFree(m_spriteSheet);
    clearImages();
}

void SpriteRenderer::render()
{
    for (size_t i = 0; i < m_sprites.size(); i++)
        C2D_DrawSprite(&(m_sprites[i]));
}

void SpriteRenderer::addImage(Image *image)
{
    if(image->getImageId() < 0)
        printf("ERROR: Image %s does not have id.\n", image->getImageName().c_str());
    else
    {
        m_images.push_back(image);
        C2D_Sprite sprite = generateSpriteFromImage(image);
        m_sprites.push_back(sprite);
    }
}

C2D_Sprite SpriteRenderer::generateSpriteFromImage(Image *image)
{
    C2D_Sprite sprite;
    C2D_SpriteFromSheet(&sprite, m_spriteSheet, image->getImageId());
    C2D_SpriteSetCenter(&sprite, .5f, .5f);
    C2D_SpriteSetPos(&sprite, image->getPosition().x, image->getPosition().y);
    C2D_SpriteSetScale(&sprite, image->getScale().x, image->getScale().y);
    C2D_SpriteSetDepth(&sprite, image->getPosition().z);
    return sprite;
}

int SpriteRenderer::getImageIndex(const std::string& imageName)
{
    for(size_t i = 0; i < m_images.size(); i++)
        if (m_images[i]->getImageName() == imageName)
            return i;
    
    return -1;
}

void SpriteRenderer::getImageSize(Image* image, Vector2* out)
{
    int index = getImageIndex(image->getImageName());
    out->x = m_sprites[index].params.pos.w;
    out->y = m_sprites[index].params.pos.h;
}

void SpriteRenderer::clearImages()
{
    for(size_t i = 0; i < m_images.size(); i++)
        delete m_images[i];
    
    m_sprites.clear();
    m_images.clear();
}
