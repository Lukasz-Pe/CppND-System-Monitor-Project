#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os>>version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE_LukPek: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  std::string found_key, line;
  float total_memory{0}, free_memory{0}, cache_memory{0};
  long int found_value;
  std::ifstream file(kProcDirectory + kMeminfoFilename);
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

// DONE_LukPek: Read and return the system uptime
long LinuxParser::UpTime() {
  std::ifstream file(kProcDirectory+kUptimeFilename);
  long int seconds;
  if(file.is_open()){
    std::string line;
    std::getline(file,line);
    std::istringstream linestream(line);
    linestream>>seconds;
  }
  return seconds;
}

// DONE_LukPek: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  long int total{0}, data;
  string line,id;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream>>id;
    for(int i=0;i<10;i++){
      linestream>>data;
      total+=data;
      data=0;
    }
  }
  return total;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  long int total{0}, starttime{0};
  string line,id, data;
  std::ifstream stream(kProcDirectory +"/"+ to_string(pid) + kStatFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream>>id;
    for(int i=0;i<23;i++){
      linestream>>data;
      if(i==13||i==14||i==15||i==16||i==17) {
        total += stol(data);
      }
      if(i==22){
        starttime=stol(data);
      }
      data= {};
    }
  }
  return std::abs(total-starttime);
}

// DONE_LukPek: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  long int total{0}, data;
  string line,id;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream>>id;
    for(int i=0;i<10;i++){
      linestream>>data;
      if(i!=3||i!=4) {
        total += data;
      }
      data=0;
    }
  }
  return total; }

// DONE_LukPek: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  long int total{0}, data;
  string line,id;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream>>id;
    for(int i=0;i<10;i++){
      linestream>>data;
      if(i==3||i==4) {
        total += data;
      }
      data=0;
    }
  }
  return total;  }

// DONE_LukPek: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  int processes{0};
  std::ifstream file(kProcDirectory+kStatFilename);
  if(file.is_open()){
    std::string line, key;
    while(std::getline(file,line)){
      std::stringstream sstream(line);
      sstream>>key;
      if(key=="processes"){
        sstream>>processes;
      }
    }
  }
  return processes;
}

// DONE_LukPek: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  int processes{0};
  std::ifstream file(kProcDirectory+kStatFilename);
  if(file.is_open()){
    std::string line, key;
    while(std::getline(file,line)){
      std::stringstream sstream(line);
      sstream>>key;
      if(key=="procs_running"){
        sstream>>processes;
      }
    }
  }
  return processes;
}

// DONE_LukPek: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string cmd;
  std::ifstream file(kProcDirectory+"/"+std::to_string(pid)+kCmdlineFilename);
  if(file.is_open()){
    std::getline(file,cmd);
  }
  return cmd;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) {
  return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
