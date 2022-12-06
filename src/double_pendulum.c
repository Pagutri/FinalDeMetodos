/*
Programa que resuelve las ecuaciones de movimiento de un
péndulo doble utilizando el método de Runge-Kutta de 4
pasos. También calcula los exponentes de Lyapunov de este
sistema caótico.
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



Salma Gutiérrez, diciembre 2022
salma.gutierrez@cimat.mx
 */ 

#include "libraries.h"


int main(int argc, char **argv)
{
int n, N;
double t, dt;
double k1_theta, k2_theta, k1_thetadot, k2_thetadot;
double theta, thetadot, thetadotdot;
double k1_phi, k2_phi, k1_phidot, k2_phidot;
double phi, phidot, phidotdot;
char ppm_file[MAX_LINELENGTH];
struct SDL_graphics *SDL_graphics; 
SDL_Event event;
FILE *output, *shscript;

parse_commandline(argc, argv, &N, &dt);

output = fopen(argv[3], "w");
initialize_rand();

theta = fRand(0.0, PI);
phi = fRand(0.0, PI);
thetadot = 0.0;
phidot = 0.0;
t = 0.0;

printf("Initial angles: theta = %.8f   phi = %.8f\n", theta, phi);
fprintf(output, "%.8f  %.8f  %.8f\n", t, theta, phi);

/* Inicialización del entorno gráfico: ................................ */
SDL_graphics=(struct SDL_graphics*)malloc(sizeof(struct SDL_graphics));
if(NULL == SDL_graphics)
  {
  printf("\n\nError in allocating struct SDL_graphics *SDL_graphics\n\n");
  exit(0);
  }
SDL_graphics->width = GRAPHICS_WIDTH;
SDL_graphics->height= GRAPHICS_HEIGHT;
allocate_SDL_pixelarray(SDL_graphics);
initialize_SDL_graphics(SDL_graphics);
initialize_pixel_array(SDL_graphics);
/* Terminar la inicialización del entorno gráfico ..................... */

shscript = fopen("ppm_to_gif_script.sh", "w");
if(NULL == shscript)
  {
  printf("\n\nCould not open file 'ppm_to_gif_script.sh' for writing.\n\n");
  exit(0);
  }
if(-1 == system("chmod +x ppm_to_gif_script.sh"))
  {
  printf("\n\nCould not make 'ppm_to_gif_script.sh' executable.\n\n");
  exit(0);
  }

/* Runge-Kutta */
for(n = 0; n < N; n++)
  {
  /* Ecuación de movimiento del ángulo theta */
  thetadotdot = (GRAVITY * (0.5 * sin(phi) * cos(theta - phi) -\
    sin(theta)) / LENGHT - 0.5 * sin(theta - phi) * (pow(phidot, 2) +\
    pow(thetadot, 2) * cos(theta - phi))) / (1.0 - 0.5 * pow(cos(theta - phi), 2));

  /* Ecuación de movimiento del ángulo phi */
  phidotdot = ((pow(thetadot, 2) + 0.5 * pow(phidot, 2) *\
    cos(theta - phi)) * sin(theta - phi) + GRAVITY * (sin(theta) *\
    cos(theta - phi) - sin(phi)) / LENGHT) / (1.0 - 0.5 *\
    pow(cos(theta - phi), 2));


  k1_theta = dt * thetadot;
  k1_thetadot = dt * thetadotdot;
  k1_phi = dt * phidot;
  k1_phidot = dt * phidotdot;

  k2_theta = dt * (thetadot + k1_thetadot);
  k2_thetadot = dt * (GRAVITY * (0.5 * sin(phi + k1_phi) * cos(theta +\
    k1_theta - phi - k1_phi) - sin(theta + k1_theta)) / LENGHT - 0.5 *\
    sin(theta + k1_theta - phi - k1_phi) * (pow(phidot + k1_phidot, 2) +\
    pow(thetadot + k1_thetadot, 2) * cos(theta + k1_theta - phi -\
    k1_phi))) / (1.0 - 0.5 * pow(cos(theta + k1_theta - phi - k1_phi), 2)); 
  k2_phi = dt * (phidot + k1_phidot);
  k2_phidot = dt * ((pow(thetadot + k1_thetadot, 2) + 0.5 * pow(phidot + k1_phidot, 2) *\
    cos(theta + k1_theta - phi - k1_phi)) * sin(theta + k1_theta - phi - k1_phi) + GRAVITY *\
    (sin(theta + k1_theta) * cos(theta + k1_theta - phi - k1_phi) - sin(phi + k1_phi)) /\
    LENGHT) / (1.0 - 0.5 * pow(cos(theta + k1_theta - phi - k1_phi), 2));    

  theta += 0.5 * (k1_theta + k2_theta);
  theta = boundary_conditions(theta);
  thetadot += 0.5 * (k1_thetadot + k2_thetadot);  

  phi += 0.5 * (k1_phi + k2_phi);
  phi = boundary_conditions(phi);
  phidot += 0.5 * (k1_phidot + k2_phidot);

  t += dt;

  fprintf(output, "%.8f  %.8f  %.8f\n", t, theta, phi); 

  /* Visualización: */
  draw_origin(SDL_graphics, BLOBSIZE);
  visualize_mass(SDL_graphics, theta, phi, 0, BLOBSIZE);
  visualize_mass(SDL_graphics, theta, phi, 1, BLOBSIZE);

  drawbox(SDL_graphics, GRAPHICS_MARGIN, GRAPHICS_WIDTH-GRAPHICS_MARGIN,
      GRAPHICS_MARGIN, GRAPHICS_HEIGHT-GRAPHICS_MARGIN, GRAPHICS_MARGIN/2, 0);
  sdl_update(SDL_graphics);
  fade_pixel_array(SDL_graphics, FADER);

  if(0 == n%GIF_STEP)
    {
    /* Escribir entrada del script que crea las imágenes .gif: */
    sprintf(ppm_file, "Snapshot_%08d.ppm", n+1);
    write_ppm(SDL_graphics, ppm_file);
    fprintf(shscript, "(convert %s Snapshot_%08d.gif; rm %s)\n", ppm_file, n+1, ppm_file);
    }

  /* Matar la visualización al presionar ctrl+C: */
  signal(SIGINT, exit);
  while( SDL_PollEvent(&event) )
    {
    if(event.type == SDL_KEYDOWN &&
      (event.key.keysym.sym == SDLK_c && event.key.keysym.mod & KMOD_CTRL))
      {
      printf("\n\nGOT KILLED.\n\nRun './ppm_to_gif_script.sh' to convert ppm output to gif.\n\n");
      fclose(shscript);
      exit(0);
      }
    }
  }

printf("\n\nFINISHED.\n\nRun './ppm_to_gif_script.sh' to convert ppm output to gif.\n\n");
fclose(shscript);
fclose(output);

return(1);
}



double boundary_conditions(double angle)
{
/* Los ángulos pueden ir de cero a 2 * PI radianes. */
while(angle > 2.0 * PI)
  {
  angle -= 2.0 * PI;
  }
while(angle < 0.0)
  {
  angle += 2.0 * PI;
  }

return(angle);
}
