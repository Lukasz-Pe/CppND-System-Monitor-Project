#include "ncurses_display.h"
#include "system.h"
#include "format.h"

int main() {
  System system;
  NCursesDisplay::Display(system);
//  Process proc;
//  proc.GetData(258094);
//  std::cout<<"CPU: "<<100*proc.CpuUtilization()<<
//      "\nUptime: "<<Format::ElapsedTime(proc.UpTime())<<"\n";
}