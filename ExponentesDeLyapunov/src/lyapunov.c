/*
Programa que calcula los exponentes promedio de Lyapunov
de un sistema dinámico de dos dimensiones.


Salma Gutiérrez, diciembre 2022
salma.gutierrez@cimat.mx
 */ 

#include "libraries.h"


int main(int argc, char **argv)
{
int n, N;
double t, dt;
FILE *output;

parse_commandline(argc, argv, &N);

output = fopen(argv[3], "w");
t = 0.0;

printf("\n\nPROCESO COMPLETO.\n\nCorrer './ppm_to_gif_script.sh' para crear los .gif.\n\n");

return(1);
}
