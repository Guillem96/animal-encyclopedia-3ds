#pragma once

#include "../screens-controller/IScreen.h"
#include "../models/Animal.h"
#include <3ds.h>

class AnimalDetail : public IScreen
{
private:
    Animal* m_animal;
public:
    AnimalDetail();
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