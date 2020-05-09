#ifndef PROCESSOR_H
#define PROCESSOR_H


class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members
 private:
  //The order of arrays elements is the same as in /proc/stat cpu line(s)
  //That is: [0]user [1]nice [2]system [3]idle [4]iowait [5]irq [6]softirq [7]steal [8]guest [9]guest_nice
  long long int previous[10]={0,0,0,0,0,0,0,0,0,0};
  long long int now[10]={10,10,10,10,10,10,10,10,10,10};
  void Get_data();
  void Make_previous(){for(int i=0;i<10;i++){previous[i]=now[i];}}
  [[nodiscard]] long long int Total_previous_idle() const{return previous[3]+previous[4];};
  [[nodiscard]] long long int Total_idle() const{return now[3]+now[4];};
  [[nodiscard]] long long int Total_previous_non_idle() const{return previous[0]+previous[1]+previous[3]+previous[5]+previous[6]+previous[7];};
  [[nodiscard]] long long int Total_non_idle() const{return now[0]+now[1]+now[3]+now[5]+now[6]+now[7];};
  [[nodiscard]] long long int Previous_total() const{return Total_previous_idle()+Total_previous_non_idle();};
  [[nodiscard]] long long int Total() const{return Total_idle()+Total_non_idle();};
  [[nodiscard]] long long int Total_diff() const{return Total()-Previous_total();};
  [[nodiscard]] long long int Idle_diff() const{return Total_idle()-Total_previous_idle();};
};

#endif