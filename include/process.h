#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // DONE_LukPek: See src/process.cpp
  std::string User();                      // DONE_LukPek: See src/process.cpp
  std::string Command();                   // DONE_LukPek: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // DONE_LukPek: See src/process.cpp
  long int UpTime();                       // DONE_LukPek: See src/process.cpp
  bool operator<(Process const& a) const;  // DONE_LukPek: See src/process.cpp
  bool operator>(Process const& a) const;
  bool operator==(Process const& a) const;
  void GetData(const int& pid);
  // DONE_LukPek: Declare any necessary private members
 private:
  float CPUUtilization();
  long int previous_process_cpu_{0}, previous_total_cpu_{0};
  long int now_process_cpu_{0}, now_total_cpu_{0};
  int pid_{0};
  float cpu_utilization_{0.0};
};

#endif