#pragma once

#include <vector>
#include <3ds.h>
#include <citro2d.h>

#include "IScreen.h"
#include "SpriteRenderer.h"

class SplashScreen: public IScreen
{
private:
    SpriteRenderer *m_spriteRenderer;
    Image* m_splash;

public:
    SplashScreen();
    ~SplashScreen();
    
	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;
	virtual void onExit() override;

	virtual void update() override;
    virtual void draw() override;
};