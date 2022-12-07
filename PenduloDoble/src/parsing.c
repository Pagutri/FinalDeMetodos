#include "libraries.h"



void parse_commandline(int argc, char **argv, int *N, double *dt)
{
if(argc != 4)
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
}



void explain_useage_exit(char *myname)
{
printf("\n\nUso:\n\n%s  N  dt  output_file\n\n"\
       "simula el movimiento de un péndulo doble utilizando el\n"\
       "método de Runge-Kutta con 'N' pasos temporales de longitud 'dt'.\n"\
       "'N' debe ser un entero positivo, 'dt' debe ser positivo y pequeño.\n"\
       "'output_file' guardará los valores de los ángulos en el tiempo.\n\n", myname);
exit(0);
}

