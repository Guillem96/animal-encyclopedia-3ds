#pragma once

#include "IScreen.h"
#include "Animal.h"
#include <3ds.h>

class AnimalDetail : public IScreen
{
private:
    Animal* m_animal;
    int m_refScreen = 0;

public:
    AnimalDetail();
    ~AnimalDetail();

    void setRefScreen(int index) { m_refScreen = index; }
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