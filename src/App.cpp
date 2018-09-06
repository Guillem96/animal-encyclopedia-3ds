#include "App.h"
#include "screen/AnimalDetail.h"

App::App(const Color &backgroundColor) : MainScreen(backgroundColor)
{
}

App::~App()
{
}

void App::onInit()
{
    readAnimals();
    m_target = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    m_imageMapper = new AnimalImageMapper("romfs:/res/animals-gfx/animals_sprites.t3s");
}

void App::addScreens()
{   
    int groupLength = (int)m_animals.size() / NUM_GROUPS;

    AnimalDetail *detailScreen = new AnimalDetail(m_imageMapper);
    AnimalsList *al = new AnimalsList(m_animals, groupLength, detailScreen, m_imageMapper);

    m_screenList->addScreen(al);
    m_screenList->addScreen(detailScreen);

    m_screenList->setScreen(al->getScreenIndex());
}

void App::onExit()
{
}

void App::readAnimals()
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