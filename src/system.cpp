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

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// DONE_LukPek: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// DONE_LukPek: Return the system's memory utilization
float System::MemoryUtilization() {
  std::string found_key, line;
  float total_memory{0}, free_memory{0}, cache_memory{0};
  long int found_value;
  std::ifstream file(LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename);
  if(file.is_open()){
    while(std::getline(file,line)){
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream linestream(line);
      while(linestream>>found_key>>found_value){
        if(found_key=="MemTotal"){
          total_memory=static_cast<float>(found_value);
        }
        if(found_key=="MemFree"){
          free_memory=static_cast<float>(found_value);
        }
        if(found_key=="Cached"){
          cache_memory=static_cast<float>(found_value);
        }
      }
    }
  }
  return (total_memory-(free_memory+cache_memory))/total_memory;
}

// DONE_LukPek: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return 0; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return 0; }

// DONE_LukPek: Return the number of seconds since the system started running
std::string System::UpTime() {
  std::ifstream file(LinuxParser::kProcDirectory+LinuxParser::kUptimeFilename);
  long int seconds;
  std::stringstream uptime;
  int hours, minutes;
  if(file.is_open()){
    std::string line;
    std::getline(file,line);
    std::istringstream linestream(line);
    linestream>>seconds;
  }
  hours=seconds/3600;
  seconds-=(hours*3600);
  minutes=seconds/60;
  seconds-=(minutes*60);
  if(hours<10){
    uptime<<"0"<<hours<<":"<<minutes<<":"<<seconds;
  }else {
    uptime << hours << ":" << minutes << ":" << seconds;
  }
  return uptime.str();
}