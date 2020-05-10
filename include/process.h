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
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // DONE_LukPek: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // DONE_LukPek: See src/process.cpp
  bool operator>(Process const& a) const;  // DONE_LukPek: See src/process.cpp
  void GetData(const int& pid);
  // TODO: Declare any necessary private members
 private:
  void CPUUtilization(int pid);
  long int previous_process_cpu_{0}, previous_total_cpu_{0};
  long int now_process_cpu_{0}, now_total_cpu_{0};
  int pid_{0};
  std::string user_{};
  std::string command_{};
  float cpu_utilization_{0.0};
  std::string ram_{0};
  long int uptime_{0};
};

#endif