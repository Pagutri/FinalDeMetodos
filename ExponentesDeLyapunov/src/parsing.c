#include "libraries.h"



void parse_commandline(int argc, char **argv, int *N)
{
if(argc != 3)
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
}



void explain_useage_exit(char *myname)
{
printf("\n\nUso:\n\n%s  N  trayectoria1_file  trayectoria2_file\n\n"\
       "calcula los exponentes promedio de Lyapunov de un sistema dinámico\n"\
       "de dos dimensiones.\n"\
       "'trayectoria1_file' y 'trayectoria2_file' deberán tener tres columnas\n"\
       "y la misma cantidad 'N' de intervalos temporales de la misma longitud.\n\n", myname);
exit(0);
}

