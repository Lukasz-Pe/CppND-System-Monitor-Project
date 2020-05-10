#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // DONE_LukPek: See src/processor.cpp
  // DONE_LukPek: Declare any necessary private members
 private:
  //The order of arrays elements is the same as in /proc/stat cpu line(s)
  //That is: [0]user [1]nice [2]system [3]idle [4]iowait [5]irq [6]softirq [7]steal [8]guest [9]guest_nice
  long int previous{0}, previous_idle{0};
  long int now {0}, now_idle{0};
  void Get_data();
  void Make_previous(){previous=now;previous_idle=now_idle;}
  [[nodiscard]] float Total_diff() const{return static_cast<float>(now-previous);};
  [[nodiscard]] float Idle_diff() const{return static_cast<float>(now_idle-previous_idle);};
};

#endif