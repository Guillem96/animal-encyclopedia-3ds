#include "screen/AnimalDetail.h"

AnimalDetail::AnimalDetail(AnimalImageMapper *imageMapper) : m_imageMapper(imageMapper)
{
    m_fontManager = new FontManager(m_screen->m_target);
    m_spriteRenderer = new SpriteRenderer(m_screen->m_target, "romfs:/res/animals-gfx/animals_sprites.t3x");
}

AnimalDetail::~AnimalDetail() {}

int AnimalDetail::getNextScreenIndex() const
{
    return SCREEN_INDEX_NO_SCREEN;
}

int AnimalDetail::getPreviousScreenIndex() const
{
    return 0;
}

void AnimalDetail::build()
{
    m_spriteRenderer->init();
}

void AnimalDetail::destroy()
{
    delete m_fontManager;

    m_spriteRenderer->destroy();
    delete m_spriteRenderer;
}

void AnimalDetail::onEntry()
{
    m_fontManager->init();

    Vector3 titlePos(.0f, 30.0f, 0.5f);
    std::string title = m_animal->getCommonName() + "(" + m_animal->getScientificName() + ")";
    m_fontManager->addStaticText(Text(title.c_str(),
                                      Color(244.0f / 255.0f, 149.0f / 255.0f, 66.0f / 255.0f, 1.0f),
                                      titlePos,
                                      Vector2(.8f, .8f), TEXT_ALIGN::CENTER));

    m_fontManager->addStaticText(Text("Press B to go back.",
                                      Color(104.0f / 255.0f, 162.0f / 255.0f, 1.0f, 1.0f),
                                      Vector3(.0f, 240.0f, 0.5f),
                                      Vector2(.4f, .4f), TEXT_ALIGN::CENTER));

    // Generate animal portrait
    Vector3 nextPos = generateAnimalPortrait(titlePos);

    char buffer[1024];
    // Generate main anaimal facts
    sprintf(buffer, "Kingdom: %s\nDiet: %s\nLife span: %s\nWeight: %s\nIUNC: %s",
            m_animal->getKingdom().c_str(),
            m_animal->getDiet().c_str(),
            m_animal->getLifeSpan().c_str(),
            m_animal->getWeight().c_str(),
            m_animal->getIUNC().c_str());

    m_fontManager->addStaticText(Text(buffer,
                                      Color(.0f, .0f, .0f, 1.0f),
                                      Vector3(nextPos.x + 10.0f, titlePos.y + 20.0f, 0.5f),
                                      Vector2(.6f, .6f), TEXT_ALIGN::FREE));

    generateRelativeSize(nextPos);
}

void AnimalDetail::onExit()
{
    for (size_t i = 0; i < m_imagePool.size(); i++)
        delete m_imagePool[i];

    m_imagePool.clear();

    m_spriteRenderer->clearImages();
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
    m_spriteRenderer->render();
}

Vector3 AnimalDetail::generateAnimalPortrait(const Vector3 &startPosition)
{
    Vector3 imgPosition(10.0f, startPosition.y + 10.0f, startPosition.z);

    std::string imgName = m_animal->getTumbnailImageName();
    Image *animalPortrait = new Image(m_imageMapper->getImageId(imgName), imgName, imgPosition, Vector2(.65f, .65f));
    m_imagePool.push_back(animalPortrait);

    Vector2 dims(.0f, 0.f);
    m_spriteRenderer->getImageSize(animalPortrait, &dims);

    // Re-position image
    animalPortrait->setPosition(Vector3(imgPosition.x + dims.x / (float)2, imgPosition.y + dims.y / (float)2, imgPosition.z));

    m_spriteRenderer->addImage(animalPortrait);

    return Vector3(dims.x / (float)2 + animalPortrait->getPosition().x, animalPortrait->getPosition().y + dims.y / (float)2, startPosition.z);
}

void AnimalDetail::generateRelativeSize(const Vector3 &startPosition)
{
    Vector3 relImgPosition(SCREEN_WIDTH / (float)2, startPosition.y + 20.0f, startPosition.z);

    std::string imgName = m_animal->getRelativeSizeImageName();
    int index = m_imageMapper->getImageId(imgName);
    if (index != 0) // Some animals do not have relative size image
    {
        Image *animalRelativeSize = new Image(index, imgName, relImgPosition, Vector2(.8f, .8f));
        m_imagePool.push_back(animalRelativeSize);

        Vector2 dims(.0f, 0.f);
        m_spriteRenderer->getImageSize(animalRelativeSize, &dims);

        // Re-position image
        animalRelativeSize->setPosition(Vector3(relImgPosition.x, relImgPosition.y + dims.y / (float)2, relImgPosition.z));

        m_spriteRenderer->addImage(animalRelativeSize);
    }
}
