Salma Gutiérrez, diciembre 2022
Maestría en Computación
Proyecto Final Métodos Numéricos
CIMAT
salma.gutierrez@cimat.mx



DEPENDENCIAS:
libsdl1.2-dev



Programa que resuelve las ecuaciones de movimiento de un
péndulo doble utilizando el método de Runge-Kutta de 4
pasos.
Se establece que las dos longitudes y masas del péndulo
son iguales. Las condiciones iniciales consisten en ambas
velocidades angulares nulas y ángulos aleatorios.
Al terminar, se crea una visualización de la evolución
del sistema.



La visualización se construye en dos pasos:
-------------------------------------------
Primero, se dibujan los estados utilizando la librería
gratuita Simple DirectMedia Layer (SDL)
http://www.libsdl.org/

Segundo, llamando a ppm_to_gif_script.sh, se guardan
en imágenes los estados sucesivos del sistema que
después pueden utilizarse para hacer un gif, por
ejemplo, en Python.




Instrucciones:
==============

1.) Compilar y correr:
----------------------

cd src

make

cd ../bin/

./double_pendulum


2.) Limpiar:
------------

cd src

make clean
