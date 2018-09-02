#pragma once

#include <vector>
#include <string>
#include <citro2d.h>

#include "Image.h"

class SpriteRenderer
{
    public:
        SpriteRenderer(C3D_RenderTarget *screenTarget, const std::string& spriteSheetPath, const std::string& spriteSheetSource);
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
        C2D_SpriteSheet m_spriteSheet; 
        
        std::string m_spriteSheetPath;
        std::string m_spriteSheetSource;

        std::vector<Image*> m_images;       //> Contains the information to generate and render the sprite
        std::vector<C2D_Sprite> m_sprites;

        std::vector<std::string> m_imageNames;

        void readImageNames();
        C2D_Sprite generateSpriteFromImage(Image* image);

        int getImageIndex(const std::string& imageName);
};
