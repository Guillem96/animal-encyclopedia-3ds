#include "App.h"

App::App()
{
}

App::~App()
{
}

void App::onInit()
{
    readAnimals();
}

void App::addScreens()
{
    m_mainMenuScreen = std::make_unique<MainMenuScreen>();
    m_gameplayScreen = std::make_unique<GameplayScreen>();
    m_editorScreen = std::make_unique<EditorScreen>();

    // sure these are in order, where mainmenuscreen is 0 and gameplayscreen is 1
    m_screenList->addScreen(m_mainMenuScreen.get());
    m_screenList->addScreen(m_gameplayScreen.get());
    m_screenList->addScreen(m_editorScreen.get());

    m_screenList->setScreen(m_mainMenuScreen->getScreenIndex());
}

void App::onExit()
{
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
    return animals;
}