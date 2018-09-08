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

    Vector3 nextPos = generateTitle();
    generateFacts(nextPos);
    nextPos = generateAnimalPortrait(nextPos);
    generateRelativeSize(nextPos);
    centerPortraitFacts(m_facts, m_portrait);
}

void AnimalDetail::onExit()
{
    delete m_portrait;
    delete m_relativeSize;

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

Vector3 AnimalDetail::generateTitle()
{
    Vector3 titlePos(IGNORE_VALUE, 30.0f, 0.5f);
    Text commonNameText(m_animal->getCommonName().c_str(),
                            Color(101.0f / 255.0f, 206.0f / 255.0f, 115.0f / 255.0f, 1.0f),
                            titlePos,
                            Vector2(.8f, .8f), TEXT_ALIGN::CENTER);
    Vector2 dims(.0f, .0f);
    m_fontManager->getTextDims(&commonNameText, dims);
    
    titlePos.y += dims.y + 1.0f;

    std::string scName = "(" + m_animal->getScientificName() + ")";
    Text scientificNameText(scName.c_str(),
                                Color(101.0f / 255.0f, 206.0f / 255.0f, 115.0f / 255.0f, 1.0f),
                                titlePos,
                                Vector2(.8f, .8f), TEXT_ALIGN::CENTER);

    m_fontManager->addStaticText(commonNameText);
    m_fontManager->addStaticText(scientificNameText);


    m_fontManager->addStaticText(Text("Press B to go back.",
                                      Color(104.0f / 255.0f, 162.0f / 255.0f, 1.0f, 1.0f),
                                      Vector3(IGNORE_VALUE, 240.0f, 0.5f),
                                      Vector2(.4f, .4f), TEXT_ALIGN::CENTER));
    return titlePos;
}

Vector3 AnimalDetail::generateAnimalPortrait(const Vector3 &startPosition)
{
    Vector3 imgPosition(IGNORE_VALUE, startPosition.y + 10.0f, startPosition.z);

    std::string imgName = m_animal->getTumbnailImageName();
    m_portrait = new Image(m_imageMapper->getImageId(imgName), imgName, imgPosition, Vector2(.65f, .65f));

    Vector2 dims(.0f, 0.f);
    m_spriteRenderer->getImageSize(m_portrait, &dims);

    // Re-position image
    m_portrait->setPosition(Vector3(IGNORE_VALUE, imgPosition.y + dims.y / (float)2, imgPosition.z));

    m_spriteRenderer->addImage(m_portrait);

    return Vector3(dims.x / (float)2 + m_portrait->getPosition().x, m_portrait->getPosition().y + dims.y / (float)2, startPosition.z);
}

void AnimalDetail::generateFacts(const Vector3 &startPosition)
{
    char buffer[1024];
    sprintf(buffer, "Kingdom: %s\nDiet: %s\nLife span: %s\nWeight: %s\nIUNC: %s",
            m_animal->getKingdom().c_str(),
            m_animal->getDiet().c_str(),
            m_animal->getLifeSpan().c_str(),
            m_animal->getWeight().c_str(),
            m_animal->getIUNC().c_str());

    m_facts = new Text(buffer, 
                    Color(.0f, .0f, .0f, 1.0f),
                    Vector3(startPosition.x + 10.0f, startPosition.y +25.0f, 0.5f), 
                    Vector2(.6f, .6f), TEXT_ALIGN::FREE);
}


void AnimalDetail::generateRelativeSize(const Vector3 &startPosition)
{
    Vector3 relImgPosition(SCREEN_WIDTH / (float)2, startPosition.y + 10.0f, startPosition.z);

    std::string imgName = m_animal->getRelativeSizeImageName();
    int index = m_imageMapper->getImageId(imgName);
    if (index != 0) // Some animals do not have relative size image
    {
        m_relativeSize = new Image(index, imgName, relImgPosition, Vector2(.75f, .75f));

        Vector2 dims(.0f, 0.f);
        m_spriteRenderer->getImageSize(m_relativeSize, &dims);

        // Re-position image
        m_relativeSize->setPosition(Vector3(relImgPosition.x, relImgPosition.y + dims.y / (float)2, relImgPosition.z));

        m_spriteRenderer->addImage(m_relativeSize);
    }
}

void AnimalDetail::centerPortraitFacts(Text* facts, Image* portrait)
{
    Vector2 portraitDims(.0f, .0f);
    m_spriteRenderer->getImageSize(portrait, &portraitDims);

    Vector2 factsDims(.0f, .0f);
    m_fontManager->getTextDims(facts, factsDims);

    float width = portraitDims.x + factsDims.x;
    float screenCenter = SCREEN_WIDTH/(float)2;

    float xOffset = width /(float)2 - portraitDims.x;
    
    float textX = screenCenter - xOffset;
    facts->setPosition(Vector3(textX, facts->getPosition().y, 0.5f));
    m_fontManager->addStaticText(*facts);

    Vector3 portraitPos = portrait->getPosition();
    float portraitX = textX - portraitDims.x /(float)2 - 10.0f;
    portrait->setPosition(Vector3(portraitX, portraitPos.y, portraitPos.z));
}
