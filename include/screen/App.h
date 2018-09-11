#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "MainScreen.h"
#include "IScreen.h"
#include "ScreenList.h"
#include "Animal.h"
#include "CsvIterator.h"
#include "screen/AnimalsList.h"
#include "AnimalImageMapper.h"

#define NUM_GROUPS 12

class App: public MainScreen
{
private:
    void readAnimals(void);
    std::vector<Animal> m_animals;

    AnimalImageMapper* m_imageMapper = nullptr;
public:
    App(const Color& backgroundColor);
    ~App();

    virtual void onInit() override;
    virtual void addScreens() override;
    virtual void onExit() override;
};
