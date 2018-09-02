#include "SpriteRenderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <citro3d.h>

SpriteRenderer::SpriteRenderer(C3D_RenderTarget *screenTarget,
                               const std::string &spriteSheetPath,
                               const std::string& spriteSheetSource) : m_targetScreen(screenTarget),
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

                printf("%d\n", C2D_SpriteSheetCount(m_spriteSheet));

}

void SpriteRenderer::destroy()
{
    C2D_SpriteSheetFree(m_spriteSheet);
}

// Render the images
void SpriteRenderer::render()
{
    for (size_t i = 0; i < m_sprites.size(); i++)
    {   
        C2D_DrawSprite(&(m_sprites[i]));
    }
}

// Push animage to render on the following frames
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
    C2D_SpriteSetCenter(&sprite, 0.0f, 0.0f);
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
            std::string name = std::string(line);
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
    int index = 0;
    for(std::string& n: m_imageNames)
    {
        if(n == imageName)
        {
            return index;
        }
        index++;
    }

    return -1;
}
