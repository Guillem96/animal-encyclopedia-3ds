#include "MainScreen.h"
#include "ScreenList.h"
#include "IScreen.h"

MainScreen::MainScreen()
{
    m_screenList = new ScreenList(this);
}

MainScreen::~MainScreen()
{
    // Empty
}

void MainScreen::run()
{
    if (init())
    {
        // Main loop
        while (aptMainLoop())
        {
            hidScanInput();

            u32 kDown = hidKeysDown();
            if (kDown & KEY_START)
            {
                exit();
            }

            C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
            C2D_TargetClear(m_target, C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
            C2D_SceneBegin(m_target);

            update();
            draw();

            C3D_FrameEnd(0);
        }
    }
}

void MainScreen::exit()
{
    m_isRunning = false;
    m_currentScreen->onExit();
    if (m_screenList)
    {
        m_screenList->destroy();
    }

    C2D_Fini();
    C3D_Fini();
    gfxExit();

    onExit();
    free(m_screenList);
    delete m_target;
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
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

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
