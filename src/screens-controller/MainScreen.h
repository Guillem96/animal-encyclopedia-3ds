#pragma once

#include <memory>
#include <3ds.h>

class ScreenList;
class IScreen;

class MainScreen
{
  public:
    MainScreen();
    virtual ~MainScreen();

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

  private:
    void update();
    void draw();
};
