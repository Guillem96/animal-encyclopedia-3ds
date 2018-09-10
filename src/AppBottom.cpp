#include "AppBottom.h"

AppBottom::AppBottom(const Color &backgroundColor) : MainScreen(backgroundColor)
{
}

AppBottom::~AppBottom()
{
}

void AppBottom::onInit()
{
    m_target = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
}

void AppBottom::addScreens()
{   
    SplashScreen *ss = new SplashScreen();
    m_screenList->addScreen(ss);
    m_screenList->setScreen(ss->getScreenIndex());
}

void AppBottom::onExit()
{
}
