// busyboxtest.cpp

#include <iostream>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "ERROR:Please provide an image to deploy [busybox, debian, etc.]" << std::endl;
        std::cout << "Exiting." << std::endl;
        return -1;
    }

    char cmd[128];
    sprintf(cmd, "docker run --hostname testGame -it --rm -u testuser %s", argv[1]);
    std::cout << cmd << std::endl;
    system(cmd);

    return 0;
}