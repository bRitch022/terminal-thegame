// main.cpp

#include "GameRegistryIni.h"

int main(int argc, char** argv)
{
    // Check that there is a file argument
    if(argc <= 1)
    {
        std::cout << "Missing argument: ini file" << std::endl;
        return -1;
    }

    GameRegistry *p_registry = new GameRegistry(std::string(argv[1]));

    return 0;
}
