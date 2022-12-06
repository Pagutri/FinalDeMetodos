#include "libraries.h"



void parse_commandline(int argc, char **argv, int *N, double *dt, int *option)
{
if(argc != 5)
  {
  explain_useage_exit(argv[0]);
  }

if(1 != sscanf(argv[1], "%d", N) )
  {
  explain_useage_exit(argv[0]);
  }

if(*N < 1)
  {
  explain_useage_exit(argv[0]);
  }

if(1 != sscanf(argv[2], "%le", dt) )
  {
  explain_useage_exit(argv[0]);
  }

if(*dt <= 0.0)
  {
  explain_useage_exit(argv[0]);
  }

if(1 != sscanf(argv[3], "%d", option) )
  {
  explain_useage_exit(argv[0]);
  }

if(*option != 0 && *option != 1)
  {
  explain_useage_exit(argv[0]);
  }
}



void explain_useage_exit(char *myname)
{
printf("\n\nUseage:\n\n%s  N  dt  option  output_file\n\n"\
       "will simulate a chaotic double pendulum.\n"\
       "Set option to 0 to solve the equations of motion with the\n"\
       "Euler Forward algorithm and set it to 1 to use Runge-Kutta.\n"\
       "Any algorithm will work with 'N' time steps of 'dt' lenght.\n"\
       "'N' must be a positive integer, 'dt' must be positive.\n\n", myname);
printf("Graphical output uses two methods:\n"\
       "First, the SDL library (libsdlorg) for on-the-fly graphics window output, and\n"\
       "second, ppm picture output, automatically converted to gif by system calls.\n\n\n");
exit(0);
}

