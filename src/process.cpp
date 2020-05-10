#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// DONE_LukPek: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_utilization_; }

// DONE_LukPek: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// DONE_LukPek: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// DONE_LukPek: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// DONE_LukPek: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return this->cpu_utilization_<a.cpu_utilization_;
}
void Process::GetData(const int& pid) {
  pid_=pid;
//  CPUUtilization(pid_);
}
float Process::CPUUtilization(int pid) {
  previous_process_cpu_=now_process_cpu_;
  now_process_cpu_=LinuxParser::ActiveJiffies(pid);
  previous_total_cpu_=now_total_cpu_;
  now_total_cpu_=LinuxParser::Jiffies();
  float diff_total=static_cast<float>((now_total_cpu_-previous_total_cpu_));
  float diff_proc=static_cast<float>((now_process_cpu_-previous_process_cpu_));
  cpu_utilization_=diff_proc/diff_total;
  return cpu_utilization_;
}
