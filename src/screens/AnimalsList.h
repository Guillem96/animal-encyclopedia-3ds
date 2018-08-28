#pragma once

#include <vector>
#include <3ds.h>
#include <citro2d.h>

#include "../screens-controller/IScreen.h"
#include "../models/Animal.h"
#include "AnimalDetail.h"
#include "../font-manager/FontManager.h"

class AnimalsList: public IScreen
{
private:
    std::vector<Animal> m_animals;    
    std::string m_title;
    bool m_hasNext;    

    int m_selectedAnimal = 0;
    int m_nextScreen = 0;

    AnimalDetail* m_ad;

    C3D_RenderTarget* m_target;

    FontManager *m_fontManager;

    void nextAnimalsPage();
    void previousAnimalsPage();
public:
    AnimalsList(std::vector<Animal> animals, int index, bool hasNext, AnimalDetail* ad);
    ~AnimalsList();

    void setTarget(C3D_RenderTarget* target);
    
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;
	virtual void onExit() override;

	virtual void update() override;
    virtual void draw() override;
};