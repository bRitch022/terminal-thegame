// main.cpp

#include "GameRegistryIni.h"
#include <unistd.h>

int main(int argc, char** argv)
{
    // Check that there is referenced GameRegistry.ini 
    if(argc <= 1 || strstr(argv[1], "GameRegistry.ini") == NULL)
    {
        std::cout << "Missing argument: GameRegistry.ini" << std::endl;
        return -1;
    }

    // Initialize the registry
    GameRegistry *p_registry = new GameRegistry(std::string(argv[1]));

    // Main game loop
    while(1)
    {
        char cmd[128] = "clear";
        system(cmd);
        p_registry->read();

#if DEBUG
        p_registry->printINI();
#endif
        p_registry->update();

        sleep(1);
    }

    delete(p_registry);
    return 0;
}
