#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_utilization_; }

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const {
  return this->cpu_utilization_<a.cpu_utilization_;
}
bool Process::operator>(Process const& a[[maybe_unused]]) const {
  return this->cpu_utilization_>a.cpu_utilization_;
}
void Process::GetData(const int& pid) {
  pid_=pid;
  command_=LinuxParser::Command(pid_);
  CPUUtilization(pid_);
  ram_=LinuxParser::Ram(pid_);
  user_=LinuxParser::User(pid_);
  uptime_=LinuxParser::UpTime(pid_);
  
}
void Process::CPUUtilization(int pid) {
  previous_process_cpu_=now_process_cpu_;
  now_process_cpu_=LinuxParser::ActiveJiffies(pid);
  previous_total_cpu_=now_total_cpu_;
  now_total_cpu_=LinuxParser::Jiffies();
  float diff_total=static_cast<float>((now_total_cpu_-previous_total_cpu_));
  float diff_proc=static_cast<float>((now_process_cpu_-previous_process_cpu_));
  cpu_utilization_=diff_proc/diff_total;
}
