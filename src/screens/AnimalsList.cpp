#include "AnimalsList.h"

AnimalsList::AnimalsList(std::vector<Animal> animals,
                         int index,
                         bool hasNext) : m_animals(animals)
{
    m_screenIndex = index;
}

AnimalsList::~AnimalsList() {}

int AnimalsList::getNextScreenIndex() const {
    if(!m_hasNext)
        return SCREEN_INDEX_NO_SCREEN;

    return m_screenIndex + 1;
}

int AnimalsList::getPreviousScreenIndex() const {
    return m_screenIndex - 1;
}

void AnimalsList::build() {
}

void AnimalsList::destroy() {
}

void AnimalsList::onEntry() {   
}

void AnimalsList::update() {
    // TODO: Controls logic   
}

void AnimalsList::draw() {   
    for(int i = 0; i < m_animals.size(); i++) {
        if (i == m_selectedAnimal)
            printf("\x1b[31m-> %s\n\x1b[0m", m_animals[i].toCStr());
        else
            printf("%s\n", m_animals[i].toCStr());
    }
}

void AnimalsList::nextAnimalsPage() {
    m_currentState = ScreenState::CHANGE_NEXT;
}

void AnimalsList::previousAnimalsPage() {
	m_currentState = ScreenState::CHANGE_PREVIOUS;
}

