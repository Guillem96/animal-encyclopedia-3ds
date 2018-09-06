#include "SpriteRenderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <citro3d.h>

SpriteRenderer::SpriteRenderer(C3D_RenderTarget *screenTarget,
                               const std::string &spriteSheetPath,
                               const std::string& spriteSheetSource) :  m_targetScreen(screenTarget),
                                                                        m_spriteSheetPath(spriteSheetPath),
                                                                        m_spriteSheetSource(spriteSheetSource)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::init()
{
    readImageNames();
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
    if(getImageIndex(image->getImageName()) < 0)
        printf("ERROR: Image %s does not exist.\n", image->getImageName().c_str());
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
    int index = getImageIndex(image->getImageName());
    C2D_SpriteFromSheet(&sprite, m_spriteSheet, index);
    C2D_SpriteSetCenter(&sprite, 0.5f, 0.5f);
    C2D_SpriteSetPos(&sprite, image->getPosition().x, image->getPosition().y);
    C2D_SpriteSetScale(&sprite, image->getScale().x, image->getScale().y);
    C2D_SpriteSetDepth(&sprite, image->getPosition().z);
    return sprite;
}

void SpriteRenderer::readImageNames()
{
    FILE *f;
    f = fopen(m_spriteSheetSource.c_str(), "r");

    if (f != NULL)
    {
        printf("Reading: %s\n", m_spriteSheetSource.c_str());
        
        char line[512];
        
        fgets(line, 512, f); // Skip first line

        while (fgets(line, 512, f) != NULL)
        {
            std::string name(line);
            name = name.erase(name.find_last_not_of("\t\n\v\f\r ") + 1);
            m_imageNames.push_back(name);
        }
        fclose(f);
    }
    else
    {
        printf("ERROR: Reading file %s\n", m_spriteSheetSource.c_str());
    }
}

int SpriteRenderer::getImageIndex(const std::string& imageName)
{
    for(size_t i = 0; i < m_imageNames.size(); i++)
        if (m_imageNames[i] == imageName)
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
    
    m_imageNames.clear();
    m_sprites.clear();
    m_images.clear();
}
