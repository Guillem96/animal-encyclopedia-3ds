#pragma once

#include <vector>

#include "../screens-controller/IScreen.h"
#include "../models/Animal.h"

class AnimalsList: public IScreen
{
private:
    std::vector<Animal> m_animals;    
    std::string m_title;
    bool m_hasNext;    
    int m_selectedAnimal = 0;

    void nextAnimalsPage();
    void previousAnimalsPage();
public:
    AnimalsList(std::vector<Animal> animals, int index, bool hasNext);
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