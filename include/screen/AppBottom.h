#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "MainScreen.h"
#include "IScreen.h"
#include "ScreenList.h"
#include "SplashScreen.h"

#define NUM_GROUPS 12

class AppBottom: public MainScreen
{
public:
    AppBottom(const Color& backgroundColor);
    ~AppBottom();

    virtual void onInit() override;
    virtual void addScreens() override;
    virtual void onExit() override;
};
