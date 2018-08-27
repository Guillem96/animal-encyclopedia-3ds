/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>

#include "font-manager/FontManager.h"

int main(int argc, char *argv[])
{
    gfxInitDefault();
    consoleInit(GFX_BOTTOM, NULL);
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    C3D_RenderTarget *top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    FontManager *fm = new FontManager(top);
    Text *dynText = new Text("Hola em dic guillem", Color(1, 1, 1, .5), Vector2(16.0f, 20.0f), Vector2(1, 1), TEXT_ALIGN::CENTER);
    fm->addDynamicText(dynText);
    fm->addStaticText(Text("Hola em dic guillem\n Hola em dic guillem\n Hola em dic guillem\n Hola em dic guillem\n Hola em dic guillem", Color(1, 0, 0, .5), Vector2(16.0f, 40.0f), Vector2(1, 1), TEXT_ALIGN::CENTER));

    fm->init();

    // Main loop
    while (aptMainLoop())
    {
        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break; // break in order to return to hbmenu

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
        C2D_SceneBegin(top);

        fm->render();

        C3D_FrameEnd(0);

    }

    C2D_Fini();
    C3D_Fini();
    gfxExit();

    fm->destroy();
    delete dynText;
    delete fm;
    return 0;
}
*/
#include "App.h"

int main(int argc, char *argv[])
{
    App app = App();
    app.run();
    return 0;
}
