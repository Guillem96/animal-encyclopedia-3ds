#pragma once

#include <vector>
#include <3ds.h>
#include <citro2d.h>
#include <algorithm>

#include "IScreen.h"
#include "Animal.h"
#include "screen/AnimalDetail.h"
#include "FontManager.h"
#include "SpriteRenderer.h"
#include "AnimalImageMapper.h"

class AnimalsList: public IScreen
{
private:
    std::vector<Animal> m_animals;
    
    std::vector<Text*> m_animalsText;
    std::vector<Image*> m_animalsImages;

    std::string m_title;
    Text* m_titleRenderText = nullptr;
    
    size_t m_selectedAnimal = 0;

    size_t m_interval;
    size_t m_start = 0;
    size_t m_end;

    AnimalDetail* m_ad;

    FontManager *m_fontManager;
    SpriteRenderer *m_spriteRenderer;
    AnimalImageMapper* m_imageMapper;
    
    void nextAnimalsPage();
    void previousAnimalsPage();

    void initFontManager();
    void initSpriteRenderer();

    void generateAnimal(Animal* a, Vector2& nextPos);

    void updateScreenContent();
public:
    AnimalsList(std::vector<Animal> animals, size_t interval, AnimalDetail* ad, AnimalImageMapper* imageMapper);
    ~AnimalsList();
    
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;
	virtual void onExit() override;

	virtual void update() override;
    virtual void draw() override;
};