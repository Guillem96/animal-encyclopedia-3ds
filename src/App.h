
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "screens-engine/MainScreen.h"
#include "models/Animal.h"
#include "csv-utils/CsvIterator.h"

class App: MainScreen
{
private:
    void readAnimals(void);

    std::vector<Animal> m_animals;
public:
    App();
    ~App();

    virtual void onInit() override;
    virtual void addScreens() override;
    virtual void onExit() override;
};
