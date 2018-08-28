#include "screen/AnimalsList.h"

AnimalsList::AnimalsList(std::vector<Animal> animals,
                         int index,
                         bool hasNext,
                         AnimalDetail *ad) : m_animals(animals), m_ad(ad)
{
    m_screenIndex = index;
    m_title = m_animals[0].getKingdom();
    m_fontManager = new FontManager(m_target);
}

AnimalsList::~AnimalsList() {}

void AnimalsList::setTarget(C3D_RenderTarget* target)
{
    m_target = target;
}

int AnimalsList::getNextScreenIndex() const
{
    return m_nextScreen;
}

int AnimalsList::getPreviousScreenIndex() const
{
    return m_screenIndex - 1;
}

void AnimalsList::build()
{
    m_fontManager->addStaticText(Text("Hola em dic guillem\n Hola em dic guillem\n Hola em dic guillem\n Hola em dic guillem\n Hola em dic guillem", Color(1, 0, 0, .5), Vector3(16.0f, 40.0f, 0.5f), Vector2(1, 1), TEXT_ALIGN::CENTER));
    m_fontManager->init();
}

void AnimalsList::destroy()
{
    m_fontManager->destroy();
    delete m_fontManager;
}

void AnimalsList::onEntry()
{
    if (!m_hasNext)
        m_nextScreen = SCREEN_INDEX_NO_SCREEN;
    else
        m_nextScreen = m_screenIndex + 1;
}

void AnimalsList::onExit()
{
}

void AnimalsList::update()
{
    u32 kDown = hidKeysDown();
    if (kDown & KEY_A)
    {
        m_nextScreen = m_ad->getScreenIndex();
        m_ad->setRefScreen(m_screenIndex);
        m_ad->setAnimal(&m_animals[m_selectedAnimal]);
        m_currentState = ScreenState::CHANGE_NEXT;
    }

    if ((kDown & KEY_DOWN) && m_selectedAnimal < (int)m_animals.size() - 1)
    {
        m_selectedAnimal++;
    }

    if ((kDown & KEY_UP) && m_selectedAnimal > 0)
    {
        m_selectedAnimal--;
    }

    if (kDown & KEY_RIGHT)
    {
        m_currentState = ScreenState::CHANGE_NEXT;
    }

    if (kDown & KEY_LEFT)
    {
        m_currentState = ScreenState::CHANGE_PREVIOUS;
    }
}

void AnimalsList::draw()
{
    //The top screen has 30 rows and 50 columns
    //The bottom screen has 30 rows and 40 columns
    // printf("\x1b[10;25H%s\n", m_title.c_str());

    // int index = 0;
    // for (Animal &animal : m_animals)
    // {
    //     if (index == m_selectedAnimal)
    //     {
    //         printf("\x1b[31m-> %s\n\x1b[0m", animal.toCStr());
    //     }
    //     else
    //     {
    //         printf("   %s\n", animal.toCStr());
    //     }
    //     index++;
    // }
    m_fontManager->render();
}

void AnimalsList::nextAnimalsPage()
{
    m_currentState = ScreenState::CHANGE_NEXT;
}

void AnimalsList::previousAnimalsPage()
{
    m_currentState = ScreenState::CHANGE_PREVIOUS;
}
