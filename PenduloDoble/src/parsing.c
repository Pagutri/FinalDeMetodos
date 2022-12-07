#include "libraries.h"



void parse_commandline(int argc, char **argv, int *N, double *theta, double *phi)
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

if(1 != sscanf(argv[2], "%le", theta) )
  {
  explain_useage_exit(argv[0]);
  }

if(*theta < 0.0 || *theta > 2 * PI)
  {
  explain_useage_exit(argv[0]);
  }

if(1 != sscanf(argv[3], "%le", phi) )
  {
  explain_useage_exit(argv[0]);
  }

if(*phi < 0.0 || *phi > 2 * PI)
  {
  explain_useage_exit(argv[0]);
  }
}



void explain_useage_exit(char *myname)
{
printf("\n\nUso:\n\n%s  N  theta  phi  output_file\n\n"\
       "simula el movimiento de un péndulo doble utilizando el\n"\
       "método de Runge-Kutta con 'N' pasos temporales de longitud 0.01.\n"\
       "'N' debe ser un entero positivo.\n"\
       "'theta' y 'phi' deben estar en el intervalo (0,2PI).\n"\
       "'output_file' guardará los valores de los ángulos en el tiempo.\n\n", myname);
exit(0);
}

