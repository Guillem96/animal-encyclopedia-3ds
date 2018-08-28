#include "App.h"
#include "screen/AnimalDetail.h"

App::App()
{
}

App::~App()
{
}

void App::onInit()
{
    readAnimals();
    m_target = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
}

void App::addScreens()
{
    int groupLength = (int) m_animals.size()/NUM_GROUPS;

    AnimalDetail* detailScreen = new AnimalDetail();

    for(unsigned int  i = 0; i < m_animals.size(); i += groupLength) {
        std::vector<Animal> group;
        for(int j = 0; j < groupLength; j++) {
            group.push_back(m_animals[j + i]);
        }
        
        AnimalsList* al = new AnimalsList(group, (int)i/groupLength, !((i + groupLength) < m_animals.size()), detailScreen);
        al->setTarget(m_target);
        m_animalsScreens.push_back(al);
        m_screenList->addScreen(al);
    }
    
    m_screenList->addScreen(detailScreen);
    m_screenList->setScreen(m_animalsScreens[0]->getScreenIndex());
}

void App::onExit()
{
    for(unsigned int i = 0; i < m_animalsScreens.size(); i++) {
        free(m_animalsScreens[i]);
    }
}


void App::readAnimals()
{   
    Result rc = romfsInit();
    if (rc)
    {
        printf("romfsInit: %08lX\n", rc);
    }
    else
    {
        CsvIterator it("romfs:/animals", ",", true);
                
        while (it.hasNext())
        {
            std::vector<std::string> next = it.next();
            Animal a = Animal();
            a.fromCsv(next);
            m_animals.push_back(a);
        }
    }
}