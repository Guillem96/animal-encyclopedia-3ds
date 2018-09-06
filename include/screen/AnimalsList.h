#pragma once

#include <vector>
#include <3ds.h>
#include <citro2d.h>

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
        
    std::string m_title;
    Text* m_titleRenderText = nullptr;
    
    int m_selectedAnimal = 0;

    int m_interval;
    int m_start = 0;
    int m_end;

    AnimalDetail* m_ad;

    FontManager *m_fontManager;
    SpriteRenderer *m_spriteRenderer;
    AnimalImageMapper* m_imageMapper;
    
    void nextAnimalsPage();
    void previousAnimalsPage();

    void initFontManager();
    void initSpriteRenderer();
public:
    AnimalsList(std::vector<Animal> animals, int interval, AnimalDetail* ad, AnimalImageMapper* imageMapper);
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