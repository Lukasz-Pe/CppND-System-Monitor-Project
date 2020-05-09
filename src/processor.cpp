#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  Make_previous();
  Get_data();
  return (1.0*((Total_diff()-Idle_diff())/Total_diff()));
}
void Processor::Get_data() {
  for(int i=0;i<10;i++){
    now[i]+=10;
  }
}
