#pragma once

#include <vector>
#include <string>
#include <citro2d.h>

#include "Image.h"

class SpriteRenderer
{
    public:
        SpriteRenderer(C3D_RenderTarget *screenTarget, const std::string& spriteSheetPath);
        ~SpriteRenderer();

        // Initializes and destroys the sprite render variables
        void init();
        void destroy();

        // Render the images
        void render();

        // Push animage to render on the following frames
        void addImage(Image* image);

        // Clears all the images to be rendered
        void clearImages();
    private:
        C3D_RenderTarget *m_targetScreen;

        std::string m_spriteSheetPath;

        std::vector<Image*> m_images;
        std::vector<C2D_Sprite*> m_sprites;

        C2D_Sprite* generateSpriteFromImage(Image* image);
}
