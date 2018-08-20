#include "MainScreen.h"
#include "ScreenList.h"

MainScreen::IScreen()
{
    m_screenList = std::make_unique<ScreenList>(this);
}

MainScreen::~IScreen()
{
    // Empty
}

void MainScreen::run()
{

    if (!init())
        return;

	// Main loop
	while (aptMainLoop() && m_isRunning)
	{
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

        update();
        draw();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			exit();
	}
}

void MainScreen::exit()
{
    m_isRunning = false;
    m_currentScreen->onExit();
    if (m_screenList)
    {
        m_screenList->destroy();
        m_screenList.reset();
    }
    gfxExit();
    onExit();
}

bool MainScreen::init()
{
    if (!initSystems())
        return false;
    
    m_isRunning = true;

    onInit();
    addScreens();

    m_currentScreen = m_screenList->getCurrent();
    m_currentScreen->onEntry();
    m_currentScreen->setRunning();

    return true;
}

bool MainScreen::initSystems()
{
    gfxInitDefault();

    // TODO: SCREEN TOP OR SCREEN BOTTOM
    consoleInit(GFX_TOP, NULL);

    return true;
}

void MainScreen::update()
{
    if (m_currentScreen)
    {
        switch (m_currentScreen->getState())
        {
        case ScreenState::RUNNING:
            m_currentScreen->update();
            break;
        case ScreenState::CHANGE_NEXT:
            m_currentScreen->onExit();
            m_currentScreen = m_screenList->moveNext();
            m_currentScreen->m_currentState = ScreenState::NONE;
            if (m_currentScreen)
            {
                m_currentScreen->setRunning();
                m_currentScreen->onEntry();
            }
            break;
        case ScreenState::CHANGE_PREVIOUS:
            m_currentScreen->onExit();
            m_currentScreen = m_screenList->movePrevious();
            m_currentScreen->m_currentState = ScreenState::NONE;
            if (m_currentScreen)
            {
                m_currentScreen->setRunning();
                m_currentScreen->onEntry();
            }
            break;
        case ScreenState::EXIT_APPLICATION:
            exit();
            break;
        default:
            break;
        }
    }
    else
    {
        exit();
    }
}

void MainScreen::draw()
{
    if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING)
    {
        m_currentScreen->draw();
    }
}
