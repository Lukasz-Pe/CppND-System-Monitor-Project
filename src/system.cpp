#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE_LukPek: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// DONE_LukPek: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<int> pids=LinuxParser::Pids();
  if(processes_.empty()){
    for(int pid:pids){
      AddProcess(pid);
    }
  }else{
    for(int pid:pids){
      bool exist=false;
      for(auto process:processes_){
        if(pid==process.Pid()) {
          exist = true;
        }
      }
      if(!exist){
        AddProcess(pid);
      }
    }
    for(auto process:processes_){
      bool exists=true;
      for(auto pid:pids){
        if(process.Pid()!=pid){
          exists=false;
        }else{
          break;
        }
      }
      if(!exists){
        processes_.erase(std::find(processes_.begin(),processes_.end(),process));
      }
    }
  }
  std::sort(processes_.begin(),processes_.end(),compare);
  return processes_; }

// DONE_LukPek: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// DONE_LukPek: Return the system's memory utilization
float System::MemoryUtilization() {
  return LinuxParser::MemoryUtilization();
}

// DONE_LukPek: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// DONE_LukPek: Return the number of processes actively running on the system
int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();
}

// DONE_LukPek: Return the total number of processes on the system
int System::TotalProcesses() {
  return LinuxParser::TotalProcesses();
}

// DONE_LukPek: Return the number of seconds since the system started running
long System::UpTime() {
  return LinuxParser::UpTime();
}
bool System::compare(const Process& a, const Process& b){
  return a>b;
}
void System::AddProcess(int pid) {
  Process process;
  process.GetData(pid);
  processes_.push_back(process);
}
