#include "App.h"
#include "AppBottom.h"

#define STACKSIZE (4 * 1024)

void top(void *arg);
void bottom(void *arg);

int main(int argc, char *argv[])
{
    Thread bottomThread, topThread;
    
    s32 mainPriority = 0;
    svcGetThreadPriority(&mainPriority, CUR_THREAD_HANDLE);

    topThread = threadCreate(top, NULL, STACKSIZE, mainPriority + 1, -2, false);
    bottomThread = threadCreate(bottom, NULL, STACKSIZE * 10, mainPriority + 1, -2, false);

    threadJoin(topThread, U64_MAX);
    threadFree(topThread);

    threadJoin(bottomThread, U64_MAX);
    threadFree(bottomThread);

    return 0;
}

void top(void *arg)
{
    App app(Color(245.0f/255.0f, 245.0f/255.0f, 245.0f/255.0f, 1.0f));
    app.run();
}

void bottom(void *arg)
{
    AppBottom app(Color(1.0f, 1.0f, 1.0f, 1.0f));
    app.run();
}