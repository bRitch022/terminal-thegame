// main.cpp

#include <string>
#include <iostream>

#include <EventManager.h>
#include <LevelManager.h>
#include <Registry.h>

Registry g_Reg;
EventManager g_EventMan;

/**
 * @brief Starts the Terminal program
 *
 * @param argc Requires 2(+1) arguments
 * @param argv
 * argv[1] = Registry.ini filepath
 * argv[2] = Level source directory
 *
 * @return int
 */
int main(int argc, char** argv)
{
    int rc = 0;

    std::cout << "TERMINAL main | Game Started" << std::endl;

    if(argc <= 2)
    {
        std::cout << "TERMINAL main | ERROR: Requires 2 arguments, only " << argc - 1 << " provided" << std::endl;
        return -1; // TODO (BAR): Create enum of return codes
    }
    else
    {
        if(strstr(argv[1], "Registry.ini") == NULL)
        {
            std::cout << "TERMINAL main | ERROR: Missing argument: Registry.ini" << std::endl;
            return -1;
        }

        if(strstr(argv[2], "/") == NULL)
        {
            std::cout << "TERMINAL main | ERROR: Missing argument: Level source directory" << std::endl;
            return -1;
        }
    }

    std::string regFile = argv[1];
    std::string levelDir = argv[2];

    if(!g_Reg.init(regFile))
    {
        std::cout << "TERMINAL main | ERROR: Unable to start registry with provided file" << std::endl;
        return -1;
    }

    LevelManager LevelMan;
    LevelMan.init(levelDir);

    while(!g_Reg.GetKillSwitch())
    {
        g_Reg.heartbeat();

        LevelMan.heartbeat();
        g_EventMan.heartbeat();

    }

    return rc;
}
