// Manager.h

#ifndef MANAGER_H
#define MANAGER_H

#include "Registry.h"
#include "Manager.h"
#include <unistd.h>
#include <cstring>
#include <iostream>

class Manager
{
public:
    Manager(const std::string type) : m_type(type) {}
    ~Manager() {}

    virtual bool RegistryPoll()=0;
    virtual bool RegistryPush()=0;

private:
    std::string m_type; // TODO (BAR): Make this a template
};

#endif
