#pragma once

#include <memory>
#include <3ds.h>
#include <citro2d.h>
#include "Color.h"

class ScreenList;
class IScreen;

class MainScreen
{  
    public:
        MainScreen(const Color &backgroundColor);
        virtual ~MainScreen();
        C3D_RenderTarget *m_target = nullptr;


        // Runs and initializes the game
        void run();
        // Exits the app
        void exit();

        // Called on initialization
        virtual void onInit() = 0;
        // For adding all screens
        virtual void addScreens() = 0;
        // Called when exiting
        virtual void onExit() = 0;

    protected:
        bool init();
        bool initSystems();

        ScreenList *m_screenList = nullptr;
        IScreen *m_currentScreen = nullptr;
        bool m_isRunning = false;

        Color m_backgroundColor;

    private:
        void update();
        void draw();
};
