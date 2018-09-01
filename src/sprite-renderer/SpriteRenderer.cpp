#include "SpriteRenderer.h"
#include <stdio.h>
#include <stdlib.h>

SpriteRenderer::SpriteRenderer(C3D_RenderTarget *screenTarget,
                               const std::string &spriteSheetPath) : m_targetScreen(screenTarget),
                                                                     m_spriteSheetPath(spriteSheetPath)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::init()
{
    readImageNames();
    m_spriteSheet = C2D_SpriteSheetLoad (m_spriteSheetPath.c_str());
}

void SpriteRenderer::destroy()
{
    C2D_SpriteSheetFree(m_spriteSheet);
}

// Render the images
void SpriteRenderer::render()
{   
    for(size_t i = 0; i < m_images.size(); i++)
    {
        C2D_SpriteSetPos(m_sprites[i], m_images[i]->getPosition().x, m_images[i]->getPosition().y);
        C2D_SpriteSetScale(m_sprites[i], m_images[i]->getScale().x, m_images[i]->getScale().y);
        C2D_SpriteSetDepth(m_sprites[i], m_images[i]->getPosition().z);
        C2D_DrawSprite(m_sprites[i]);
    }
}

// Push animage to render on the following frames
void SpriteRenderer::addImage(Image *image)
{
    m_images.push_back(image);
    m_sprites.push_back(generateSpriteFromImage(image));
}

// Clears all the images to be rendered
void SpriteRenderer::clearImages()
{
    m_sprites.clear();
}

C2D_Sprite *generateSpriteFromImage(Image *image)
{
    C2D_Sprite* sprite;
    // TODO: Generate the index based on image.name
    C2D_SpriteFromSheet(sprite, m_spriteSheet, 1);
    return sprite;
}

void SpriteRenderer::readImageNames()
{
    FILE* f;
    f = fopen("romfs:/res/animals-gfx/animals_sprites.t3s", "r");

    char* kk;
    fscanf(f,"%[^\n]", kk); // Skip first line

    while(!feof(f))
    {
        char* imageName;
        fscanf(f,"%[^\n]", imageName); 
        m_imageNames.push_back(std::string(imageName));
    }

    fclose(f);
}