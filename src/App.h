
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "screens-controller/MainScreen.h"
#include "screens-controller/IScreen.h"
#include "models/Animal.h"
#include "csv-utils/CsvIterator.h"

#define NUM_GROUPS 6

class App: MainScreen
{
private:
    void readAnimals(void);

    std::vector<Animal> m_animals;
    std::vector<IScreen> m_animalsScreens;
public:
    App();
    ~App();

    virtual void onInit() override;
    virtual void addScreens() override;
    virtual void onExit() override;
};
