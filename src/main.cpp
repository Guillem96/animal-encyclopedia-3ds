#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include "models/animal.h"
#include "csv-utils/CsvIterator.h"

std::vector<Animal> readAnimals(void);

int main(int argc, char *argv[])
{
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    std::vector<Animal> animals = readAnimals();
    printf("%d\n", (int)animals.size());
    
    
    // Main loop
    while (aptMainLoop())
    {
        gspWaitForVBlank();
        gfxSwapBuffers();
        hidScanInput();

        // Your code goes here
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
            break; // break in order to return to hbmenu
    }

    gfxExit();
    return 0;
}

std::vector<Animal> readAnimals()
{   
    std::vector<Animal> animals;

    Result rc = romfsInit();
    if (rc)
    {
        printf("romfsInit: %08lX\n", rc);
    }
    else
    {
        CsvIterator it("romfs:/animals", ",");
        it.next(); //> Skip header
        
        while (it.hasNext())
        {
            std::vector<std::string> next = it.next();
            Animal a = Animal();
            a.fromCsv(next);
            animals.push_back(a);
        }
    }
    return animals;
}