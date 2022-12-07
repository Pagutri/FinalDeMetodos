/*
Programa que calcula los exponentes promedio de Lyapunov
de un sistema dinámico de dos dimensiones.


Salma Gutiérrez, diciembre 2022
salma.gutierrez@cimat.mx
 */ 

#include "libraries.h"


int main(int argc, char **argv)
{
int t, N, leidos;
double dt, d0, lambda;
double *tiempo, *x1, *x2, *y1, *y2;
FILE *trajectory1, *trajectory2;

parse_commandline(argc, argv, &N);

/* leer los archivos y guardar datos en los vectores */
tiempo = (double *)malloc(N * sizeof(double));
x1 = (double *)malloc(N * sizeof(double));
x2 = (double *)malloc(N * sizeof(double));
y1 = (double *)malloc(N * sizeof(double));
y2 = (double *)malloc(N * sizeof(double));

trajectory1 = fopen(argv[2], "r");
for(t = 0; t < 10; t++)
{
  leidos = fscanf(trajectory1, "%lf %lf %lf", &tiempo[t], &x1[t], &y1[t]);
  if(leidos != 3)
  {
    printf("Error al leer el archivo %s\n", argv[2]);
    return(1);
  }
}
fclose(trajectory1);

trajectory2 = fopen(argv[3], "r");
for(t = 0; t < 10; t++)
{
  leidos = fscanf(trajectory2, "%lf %lf %lf", &dt, &x2[t], &y2[t]);
  if(leidos != 3)
  {
    printf("Error al leer el archivo %s\n", argv[3]);
    return(1);
  }
}
fclose(trajectory2);

/* ciclo que suma las diferencias */


free(tiempo);
free(x1);
free(x2);
free(y1);
free(y2);

/* dividir entre el tiempo total de simulacion */

return(1);
}
