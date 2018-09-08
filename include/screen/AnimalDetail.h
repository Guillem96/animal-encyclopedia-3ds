#pragma once

#include <3ds.h>

#include "IScreen.h"
#include "Animal.h"
#include "FontManager.h"
#include "SpriteRenderer.h"
#include "AnimalImageMapper.h"
#include "Image.h"

class AnimalDetail : public IScreen
{
private:
    Animal* m_animal;

    std::vector<Image*> m_imagePool;
    
    FontManager *m_fontManager;
    SpriteRenderer *m_spriteRenderer;

    AnimalImageMapper* m_imageMapper;

    Vector3 generateAnimalPortrait(const Vector3& startPosition);
    void generateRelativeSize(const Vector3& startPosition);
public:
    AnimalDetail(AnimalImageMapper* imageMapper);
    ~AnimalDetail();

    void setAnimal(Animal* animal) { m_animal = animal; }

    virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;
	virtual void onExit() override;

	virtual void update() override;
    virtual void draw() override;
};