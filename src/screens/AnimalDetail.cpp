#include "screen/AnimalDetail.h"

AnimalDetail::AnimalDetail() {}
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
}

void AnimalDetail::onEntry()
{
}

void AnimalDetail::onExit()
{
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
    printf("\x1b[10;1H%s - %s\n", m_animal->getCommonName().c_str(), m_animal->getScientificName().c_str());
    printf("\x1b[15;1H- Common Name: %s\n", m_animal->getCommonName().c_str());
    printf("- Scientific Name: %s\n", m_animal->getScientificName().c_str());
    printf("- Kingdom: %s\n", m_animal->getKingdom().c_str());
    printf("- Diet: %s\n", m_animal->getDiet().c_str());
    printf("- Life Span: %s\n", m_animal->getLifeSpan().c_str());
    printf("- Weight: %s\n", m_animal->getWeight().c_str());
    printf("- IUNC: %s (%s)\n", m_animal->getIUNC().c_str(), m_animal->getIUNCDescription().c_str());
}
