#include "screen/AnimalsList.h"

AnimalsList::AnimalsList(std::vector<Animal> animals, 
                            int interval, 
                            AnimalDetail* ad,
                            AnimalImageMapper* imageMapper) : m_animals(animals), 
                                                                m_interval(interval), 
                                                                m_ad(ad),
                                                                m_imageMapper(imageMapper)
{
    m_end = interval;
    m_title = m_animals[0].getKingdom();
    m_fontManager = new FontManager(m_screen->m_target);
    m_spriteRenderer = new SpriteRenderer(m_screen->m_target, "romfs:/res/animals-gfx/animals_sprites.t3x");
}

AnimalsList::~AnimalsList() {}

int AnimalsList::getNextScreenIndex() const
{
    return m_ad->getScreenIndex();
}

int AnimalsList::getPreviousScreenIndex() const
{
    return SCREEN_INDEX_NO_SCREEN;
}

void AnimalsList::build()
{
    initFontManager();
    initSpriteRenderer();
    
    int index = 0;
    Vector2 nextPos(.0f, ((SCREEN_HEIGHT - 60.0f) / ((float)m_animals.size() * 2)) + 30.0f);
    for (Animal &animal : m_animals)
    {
        generateAnimal(&animal, nextPos);
        index++;
        if (m_interval % index == 0)
            nextPos.y = 65.0f; // Reset y position
    }
}

void AnimalsList::destroy()
{
    m_fontManager->destroy();
    delete m_fontManager;
}

void AnimalsList::onEntry()
{
}

void AnimalsList::onExit()
{
}

void AnimalsList::update()
{
    u32 kDown = hidKeysDown();
    if (kDown & KEY_A)
    {
        m_ad->setRefScreen(m_screenIndex);
        m_ad->setAnimal(&m_animals[m_selectedAnimal]);
        m_currentState = ScreenState::CHANGE_NEXT;
    }

    if ((kDown & KEY_DOWN) && m_selectedAnimal < m_end - 1)
    {
        m_selectedAnimal++;
    }

    if ((kDown & KEY_UP) && m_selectedAnimal > m_start)
    {
        m_selectedAnimal--;
    }

    if ((kDown & KEY_RIGHT) && m_end < (int)m_animals.size())
    {
        nextAnimalsPage();
    }

    if ((kDown & KEY_LEFT) && m_start > 0)
    {
        previousAnimalsPage();
    }
}

void AnimalsList::draw()
{
    for (Text *t : m_animalsText)
        t->setColor(Color(.0f, .0f, .0f, 1.0f));
    
    m_animalsText[m_selectedAnimal + m_start]->setColor(Color(244.0f / 255.0f, 149.0f / 255.0f, 66.0f / 255.0f, 1.0f));
    m_fontManager->render();
    m_spriteRenderer->render();
}

void AnimalsList::nextAnimalsPage()
{       
    m_selectedAnimal = 0;
    m_start += m_interval;
    m_end += m_interval;

    // m_fontManager->clearText();
    for(size_t i = m_start; i < m_end && i < (int)m_animals.size(); i++)
        m_fontManager->addDynamicText(m_animalsText[i]);
}

void AnimalsList::previousAnimalsPage()
{
    m_selectedAnimal = 0;
    m_start -= m_interval;
    m_end -= m_interval;

    if (m_start < 0)
    {
        m_start = 0;
        m_end = m_interval;
    }

    // m_fontManager->clearText();
    for(size_t i = m_start; i < m_end && i < (int)m_animals.size(); i++)
        m_fontManager->addDynamicText(m_animalsText[i]);
}

void AnimalsList::initFontManager()
{
    m_fontManager->init();

    m_titleRenderText = new Text(m_title.c_str(),
                                      Color(244.0f / 255.0f, 149.0f / 255.0f, 66.0f / 255.0f, 1.0f),
                                      Vector3(0.0f, 30.0f, 0.5f),
                                      Vector2(.8f, .8f), TEXT_ALIGN::CENTER);
    m_fontManager->addDynamicText(m_titleRenderText);
                                  
    m_fontManager->addStaticText(Text("Press start to exit. A to see more details.\n    <- or -> to change to next animals.",
                                      Color(104.0f / 255.0f, 162.0f / 255.0f, 1.0f, 1.0f),
                                      Vector3(0.0f, 220.0f, 0.5f),
                                      Vector2(.4f, .4f), TEXT_ALIGN::CENTER));
}

void AnimalsList::initSpriteRenderer()
{
    m_spriteRenderer->init();
}

void AnimalsList::generateAnimal(Animal *a, Vector2& nextPos)
{  
    // Generate image name 
    std::string animalName = a->getCommonName();
    std::replace(animalName.begin(), animalName.end(), ' ', '_');
    std::string imgName = "thumbnails/" + animalName + ".jpg";

    Image *img = new Image(imgName, Vector3(50.0f, nextPos.y, 0.5f), Vector2(0.35f, 0.35f));
    m_spriteRenderer->addImage(img);

    Text *t = new Text(a->getCommonName().c_str(),
                       Color(.0f, .0f, .0f, 1.0f),
                       Vector3(0.0f, nextPos.y, 0.5f),
                       Vector2(.7f, .7f), TEXT_ALIGN::CENTER);
    m_fontManager->addDynamicText(t);
    
    m_animalsText.push_back(t);

    Vector2 currentDims(.0f, .0f);
    m_fontManager->getTextDims(t, currentDims);
    nextPos.y += (SCREEN_HEIGHT - 60.0f) / (float)m_animals.size();
}