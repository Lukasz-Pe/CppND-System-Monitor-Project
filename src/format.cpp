#include <string>
#include <sstream>

#include "format.h"

using std::string;

// DONE_LukPek: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int hours, minutes;
  std::stringstream uptime;
  hours=seconds/3600;
  seconds-=(hours*3600);
  minutes=seconds/60;
  seconds-=(minutes*60);
  if(hours<10){
    uptime<<"0"<<hours<<":"<<minutes<<":"<<seconds;
  }else {
    uptime << hours << ":" << minutes << ":" << seconds;
  }
  return uptime.str(); }