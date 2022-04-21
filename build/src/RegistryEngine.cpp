// main.cpp

#include "Registry.h"
#include <unistd.h>
#include <cstring>
#include <iostream>

/**
 * @brief Main method for the RegistryEngine
 * For now, this manages the Player and the BASHEngine
 *
 * @param argv This should include <dir>/GameRegistry.ini
 * @return int
 */
int main(int argc, char** argv)
{
    // Check that there is referenced GameRegistry.ini
    if(argc <= 1 || strstr(argv[1], "GameRegistry.ini") == NULL)
    {
        std::cout << "Missing argument: GameRegistry.ini" << std::endl;
        return -1;
    }

    // Initialize the game registry
    // This includes initializing the Player, and the BASHEngine
    GameRegistry *p_registry = new GameRegistry(std::string(argv[1]));

    // Main game loop
    while(1)
    {
        // Read any changes that have been made to the registry
        p_registry->read();

        // Update ingame changes to the registry
        p_registry->update();

        usleep(1E5); // sleep for 100 msec
    }

    delete(p_registry);
    return 0;
}
