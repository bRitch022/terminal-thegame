// main.cpp

#include "GameRegistryIni.h"
#include <unistd.h>
#include <cstring>
#include <iostream>


int main(int argc, char** argv)
{
    // Check that there is referenced GameRegistry.ini
    if(argc <= 1 || strstr(argv[1], "GameRegistry.ini") == NULL)
    {
        std::cout << "Missing argument: GameRegistry.ini" << std::endl;
        return -1;
    }

    // Initialize the game registry
    // This includes initializing the Player, and the Engine
    GameRegistry *p_registry = new GameRegistry(std::string(argv[1]));

    // Main game loop
    while(1)
    {
        // Read any changes that have been made to the registry
        p_registry->read();

        // Game stuff happens here
        p_registry->player->SetSkillLevel(p_registry->player->GetSkillLevel() + 1);

        // Update ingame changes to the registry
        p_registry->update();

        usleep(1E5);
    }

    delete(p_registry);
    return 0;
}
