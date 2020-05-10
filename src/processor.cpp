#include "processor.h"

// DONE_LukPek: Return the aggregate CPU utilization
float Processor::Utilization() {
  Make_previous();
  Get_data();
  return (Total_diff()-Idle_diff())/Total_diff();
}
void Processor::Get_data() {
  now=LinuxParser::Jiffies();
  now_idle=LinuxParser::IdleJiffies();
}
