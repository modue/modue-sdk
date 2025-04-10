#include "FileLogger.h"
#include <fstream>
#include <iostream>
#include <ctime>

void logToFile(const std::string &message)
{
  std::ofstream logFile("plugin_log.txt", std::ios_base::app);
  if (!logFile.is_open())
  {
    std::cerr << "Unable to open log file for writing" << std::endl;
    return;
  }

  std::time_t currentTime = std::time(nullptr);
  char timeBuffer[100];
  if (std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime)))
  {
    logFile << "[" << timeBuffer << "] " << message << std::endl;
  }
  else
  {
    logFile << "[Unknown time] " << message << std::endl;
  }

  logFile.close();
}
