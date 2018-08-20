#include "AnimalsList.h"

AnimalsList::AnimalsList(std::vector<Animal> animals,
                         int index,
                         bool hasNext) : m_animals(animals)
{
    m_screenIndex = index;
    m_title = m_animals[0].getKingdom();
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

void AnimalsList::onExit() {   
}


void AnimalsList::update() {
    // TODO: Controls logic   
}

void AnimalsList::draw() {
    //The top screen has 30 rows and 50 columns
	//The bottom screen has 30 rows and 40 columns
    printf("\x1b[10;25H%s\n", m_title.c_str());
    
    int index = 0;
    for(Animal& animal: m_animals) {
        if (index == m_selectedAnimal) {
            printf("\x1b[31m-> %s\n\x1b[0m", animal.toCStr());
        } else {
            printf("   %s\n", animal.toCStr());
        }
        index++;
    }
}

void AnimalsList::nextAnimalsPage() {
    m_currentState = ScreenState::CHANGE_NEXT;
}

void AnimalsList::previousAnimalsPage() {
	m_currentState = ScreenState::CHANGE_PREVIOUS;
}

