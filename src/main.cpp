#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  NCursesDisplay::Display(system);
//  std::cout<<LinuxParser::ProcessCpuUtilization(1644)<<"\n";
}