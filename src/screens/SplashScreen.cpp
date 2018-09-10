#include "screen/SplashScreen.h"

SplashScreen::SplashScreen()
{
    m_spriteRenderer = new SpriteRenderer(m_screen->m_target, "romfs:/res/animals-gfx/splash.t3x");
}

SplashScreen::~SplashScreen() {}

int SplashScreen::getNextScreenIndex() const
{
    return SCREEN_INDEX_NO_SCREEN;
}

int SplashScreen::getPreviousScreenIndex() const
{
    return SCREEN_INDEX_NO_SCREEN;
}

void SplashScreen::build()
{
    m_spriteRenderer->init();
    m_splash = new Image(0, "splash", Vector3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.5f), Vector2(.5f, .5f));
    m_spriteRenderer->addImage(m_splash);
}

void SplashScreen::destroy()
{
    m_spriteRenderer->destroy();
    delete m_splash;
    delete m_spriteRenderer;
}

void SplashScreen::onEntry()
{
}

void SplashScreen::onExit()
{
}

void SplashScreen::update()
{
}

void SplashScreen::draw()
{
    m_spriteRenderer->render();
}