// LevelEngine.cpp

#include "Registry.h"
#include "Level.h"
#include <unistd.h>
#include <cstring>
#include <iostream>

/**
 * @brief Main method for the LevelEngine
 * This handles calling the correct Level files to display to the user
 *
 * @param argv This should include <dir>/Registry.ini
 * @param argv This should include the source directory for level json files
 * @return int
 */
int main(int argc, char** argv)
{
    // Check that there is referenced Registry.ini and Level source directory
    if(argc <= 2)
    {
        std::cout << "Requires 2 arguments, only " << argc - 1 << " provided" << std::endl;
        return -1;
    }
    else
    {
        if(strstr(argv[1], "Registry.ini") == NULL)
        {
            std::cout << "Missing argument: Registry.ini" << std::endl;
            return -1;
        }

        if(strstr(argv[2], "/") == NULL)
        {
            std::cout << "Missing argument: Level source directory" << std::endl;
            return -1;
        }
    }

    // Otherwise, we have all the arguments we need
    std::string registryFile = argv[1];
    std::string levelSourceDirectory = argv[2];

    // Initialize the game registry
    Registry *p_registry = new Registry(registryFile);

    Level *p_level = NULL;

    // Main game loop
    while(1)
    {
        // Read any changes that have been made to the registry
        p_registry->read();

        if(p_level == NULL)
        {
            switch(p_registry->EventManager->GetLevel())
            {
                case 1:
                    p_level = new Level("/" + levelSourceDirectory + "/level1.json");
                    p_registry->level = p_level;
                break;

                default:
                break;
            }
        }
        // Update ingame changes to the registry
        p_registry->update();

        usleep(1E5); // sleep for 100 msec
    }

    delete(p_registry);
    return 0;
}
