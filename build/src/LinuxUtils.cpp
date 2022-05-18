// LinuxUtils.cpp

#include "LinuxUtils.h"
#include <iostream>

std::string GetStdoutFromCommand(std::string cmd)
{
  std::string data;
  FILE * stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  cmd.append(" 2>&1");

  stream = popen(cmd.c_str(), "r");

  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  std::cout << "GetStdoutFromCommand(" << cmd << ") | DEBUG | Result: " << data << std::endl;
  return data;
}
