#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"

class System {
 public:
  Processor& Cpu();                   // DONE_LukPek: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // DONE_LukPek: See src/system.cpp
  std::string UpTime();               // DONE_LukPek: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel();               // DONE_LukPek: See src/system.cpp
  std::string OperatingSystem();      // DONE_LukPek: See src/system.cpp

  // TODO: Define any necessary private members
 private:
  Processor cpu_;
  std::vector<Process> processes_ = {};
  
  
};

#endif