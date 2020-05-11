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
  std::vector<Process>& Processes();  // DONE_LukPek: See src/system.cpp
  float MemoryUtilization();          // DONE_LukPek: See src/system.cpp
  long UpTime();                      // DONE_LukPek: See src/system.cpp
  int TotalProcesses();               // DONE_LukPek: See src/system.cpp
  int RunningProcesses();             // DONE_LukPek: See src/system.cpp
  std::string Kernel();               // DONE_LukPek: See src/system.cpp
  std::string OperatingSystem();      // DONE_LukPek: See src/system.cpp
  std::vector<Process> processes_;
  // DONE_LukPek: Define any necessary private members
 private:
  Processor cpu_;
  void AddProcess(int pid);
  static bool compare(const Process& a, const Process& b);
  
};

#endif