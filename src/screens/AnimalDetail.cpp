#include "screen/AnimalDetail.h"

AnimalDetail::AnimalDetail()
{
    m_fontManager = new FontManager(m_screen->m_target);
}

AnimalDetail::~AnimalDetail() {}

int AnimalDetail::getNextScreenIndex() const
{
    return SCREEN_INDEX_NO_SCREEN;
}

int AnimalDetail::getPreviousScreenIndex() const
{
    return m_refScreen;
}

void AnimalDetail::build()
{
}

void AnimalDetail::destroy()
{
    delete m_fontManager;
}

void AnimalDetail::onEntry()
{
    std::string title = m_animal->getCommonName() + "(" + m_animal->getScientificName() + ")";
    m_fontManager->addStaticText(Text(title.c_str(),
                                      Color(244.0f / 255.0f, 149.0f / 255.0f, 66.0f / 255.0f, 1.0f),
                                      Vector3(150.0f, 30.0f, 0.5f),
                                      Vector2(.8f, .8f), TEXT_ALIGN::CENTER));

    m_fontManager->addStaticText(Text("Press B to go back.",
                                      Color(104.0f / 255.0f, 162.0f / 255.0f, 1.0f, 1.0f),
                                      Vector3(100.0f, 220.0f, 0.5f),
                                      Vector2(.4f, .4f), TEXT_ALIGN::CENTER));

    char buffer[1024];
    sprintf(buffer, "Common Name: %s\nScientific Name: %s\nKingdom: %s\nDiet: %s\nLife Span: %s\nWeight: %s\nIUNC: %s (%s)",
                    m_animal->getCommonName().c_str(),
                    m_animal->getScientificName().c_str(),
                    m_animal->getKingdom().c_str(),
                    m_animal->getDiet().c_str(),
                    m_animal->getLifeSpan().c_str(),
                    m_animal->getWeight().c_str(),
                    m_animal->getIUNC().c_str(), m_animal->getIUNCDescription().c_str());
    
    m_fontManager->addStaticText(Text(buffer,
                                    Color(.0f, .0f, .0f, 1.0f),
                                    Vector3(30.0f, 65.0f, 0.5f),
                                    Vector2(.6f, .6f), TEXT_ALIGN::CENTER));

    m_fontManager->init();
}

void AnimalDetail::onExit()
{
    m_fontManager->destroy();
}

void AnimalDetail::update()
{
    u32 kDown = hidKeysDown();
    if (kDown & KEY_B)
    {
        m_currentState = ScreenState::CHANGE_PREVIOUS;
    }
}

void AnimalDetail::draw()
{
    m_fontManager->render();

    // printf("\x1b[10;1H%s - %s\n", m_animal->getCommonName().c_str(), m_animal->getScientificName().c_str());
    // printf("\x1b[15;1H- Common Name: %s\n", m_animal->getCommonName().c_str());
    // printf("- Scientific Name: %s\n", m_animal->getScientificName().c_str());
    // printf("- Kingdom: %s\n", m_animal->getKingdom().c_str());
    // printf("- Diet: %s\n", m_animal->getDiet().c_str());
    // printf("- Life Span: %s\n", m_animal->getLifeSpan().c_str());
    // printf("- Weight: %s\n", m_animal->getWeight().c_str());
    // printf("- IUNC: %s (%s)\n", m_animal->getIUNC().c_str(), m_animal->getIUNCDescription().c_str());
}
