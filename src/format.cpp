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
    uptime<<"0"<<hours<<":";
  }else {
    uptime << hours <<":";
  }
  if(minutes<10){
    uptime<<"0"<<minutes<<":";
  }else {
    uptime << minutes << ":";
  }
  if(seconds<10){
    uptime<<"0"<<seconds;
  }else {
    uptime << seconds;
  }
  return uptime.str(); }
std::string Format::Nums(long count) {
  if(count<10){
    return ("00"+std::to_string(count));
  }
  if(count<100){
    return ("0"+std::to_string(count));
  }
  return std::to_string(count);
}
