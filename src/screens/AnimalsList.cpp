#include "screen/AnimalsList.h"

AnimalsList::AnimalsList(std::vector<Animal> animals,
                         int index,
                         bool hasNext,
                         AnimalDetail *ad) : m_animals(animals), m_ad(ad)
{
    m_screenIndex = index;
    m_title = m_animals[0].getKingdom();
    m_fontManager = new FontManager(m_screen->m_target);
}

AnimalsList::~AnimalsList() {}

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

    m_fontManager->addStaticText(Text(m_title.c_str(),
                                      Color(244.0f / 255.0f, 149.0f / 255.0f, 66.0f / 255.0f, 1.0f),
                                      Vector3(150.0f, 30.0f, 0.5f),
                                      Vector2(.8f, .8f), TEXT_ALIGN::CENTER));

    m_fontManager->addStaticText(Text("Press start to exit. A to see more details.\n    <- or -> to change to next animals.",
                                      Color(104.0f / 255.0f, 162.0f / 255.0f, 1.0f, 1.0f),
                                      Vector3(100.0f, 220.0f, 0.5f),
                                      Vector2(.4f, .4f), TEXT_ALIGN::CENTER));

    m_fontManager->init();
    

    Vector2 nextPos = Vector2(.0f, 65.0f);
    for (Animal &animal : m_animals)
    {
       Text* t = new Text(animal.getCommonName().c_str(),
                        Color(.0f, .0f, .0f, 1.0f),
                        Vector3(30.0f, nextPos.y, 0.5f),
                        Vector2(.6f, .6f), TEXT_ALIGN::CENTER);
        
        m_fontManager->addDynamicText(t);
        m_animalsText.push_back(t);
        
        Vector2 currentDims = Vector2(.0f, .0f);
        m_fontManager->getTextDims(t, currentDims);
        nextPos.y += currentDims.y * 1.5f;
    }
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
    for (Text* t : m_animalsText)
    {
        t->setColor(Color(.0f, .0f, .0f, 1.0f));
    } 
    m_animalsText[m_selectedAnimal]->setColor(Color(244.0f / 255.0f, 149.0f / 255.0f, 66.0f / 255.0f, 1.0f));
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
