#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "screens-controller/MainScreen.h"
#include "screens-controller/IScreen.h"
#include "screens-controller/ScreenList.h"
#include "models/Animal.h"
#include "csv-utils/CsvIterator.h"
#include "screens/AnimalsList.h"

#define NUM_GROUPS 7

class App: public MainScreen
{
private:
    void readAnimals(void);
    std::vector<Animal> m_animals;
    std::vector<AnimalsList*> m_animalsScreens;
public:
    App();
    ~App();

    virtual void onInit() override;
    virtual void addScreens() override;
    virtual void onExit() override;
};
