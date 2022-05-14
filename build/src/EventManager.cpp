// EventManager.cpp

#include "EventManager.h"
#include "LinuxUtils.h"
#include <fstream>
#include <iostream>

// EventManager::EventManager() : Manager("event") {}

/**
 * @brief
 * @todo @BAR
 *
 * @return true
 * @return false
 */
bool EventManager::heartbeat()
{
    return true;
}
/**
 * @brief Read ~/.bash_history and obtain the last command entered by the user
 *
 */
std::string EventManager::GetLastUserCommand_FromBashHistory()
{
    std::string user = GetStdoutFromCommand("whoami");

    // Remove the '\n' from the result
    if (!user.empty() && user[user.length()-1] == '\n') { user.erase(user.length()-1); }

    std::string historyFile = "/home/" + user + "/.bash_history";
    std::ifstream f_file(historyFile);

    if(!f_file)
    {
        std::cout << "EventManager::GetLastUserCommand_FromBashHistory | ERROR: Unable to open " + historyFile << std::endl;
        return "NULL";
    }

    // We want to read the last line, start just before EOF
    f_file.seekg(-1, std::ios::end);

    // find the last line (we should be at it already)
    while(f_file.peek() != '\n')
    {
        f_file.seekg(-1, std::ios_base::cur);
    }

    // Start searching for the next \n occurrence
    f_file.seekg(-1, std::ios_base::cur);
    for(int i = f_file.tellg(); i > 0; i--)
    {
        if(f_file.peek() == '\n')
        {
            // Found the second to last line
            f_file.get();
            // End here
            break;
        }

        f_file.seekg(i, std::ios_base::beg);
    }

    std::string lastCommand;
    getline(f_file, lastCommand);

    f_file.close();

    return lastCommand;
}

/**
 * @brief Set the m_lastUserCommand data member
 *
 * @param val
 */
void EventManager::SetLastCommand_FromRegistry(std::string val)
{
    m_lastUserCommand = val;
}

// bool EventManager::RegistryPoll()
// {

// }
// bool EventManager::RegistryPush()
// {

// }
