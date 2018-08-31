#pragma once
#include <vector>

class MainScreen;
class IScreen;

class ScreenList
{
  public:
    ScreenList(MainScreen *game);
    ~ScreenList();

    IScreen *moveNext();
    IScreen *movePrevious();

    void setScreen(int nextScreen);
    void addScreen(IScreen *newScreen);

    void destroy();

    IScreen *getCurrent();

  protected:
    MainScreen *m_screen = nullptr;
    std::vector<IScreen *> m_screens;
    int m_currentScreenIndex = -1;
};