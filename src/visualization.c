#include "libraries.h"




int allocate_SDL_pixelarray(struct SDL_graphics *graph)
{
graph->pixel=(unsigned char*)malloc(3*graph->width*graph->height*sizeof(unsigned char));
if(NULL == graph->pixel)
  {
  printf("\n\nMemory allocation error in function 'allocate_SDL_pixelarray()'.\n\n");
  exit(0);
  }
return(1);
}




int initialize_SDL_graphics(struct SDL_graphics *graph)
{
SDL_Init(SDL_INIT_VIDEO);
graph->screen = SDL_SetVideoMode(graph->width, graph->height, 24, SDL_HWSURFACE);
atexit(SDL_Quit);
return(1);
}





int initialize_pixel_array(struct SDL_graphics *graph)
{
int i;
for(i = 0; i < 3*graph->width*graph->height; i++)
  {
  graph->pixel[i]=255;
  }
return(1);
}





int fade_pixel_array(struct SDL_graphics *graph, int fader)
{
int i;
for(i = 0; i < 3*graph->width*graph->height; i++)
  {
  if(graph->pixel[i] + fader < 256)
    {
    graph->pixel[i] += fader;
    }
  else
    {
    graph->pixel[i] = 255;
    }
  }
return(1);
}




int sdl_update(struct SDL_graphics *graph)
{
graph->memfield = SDL_CreateRGBSurfaceFrom(graph->pixel, graph->width,graph->height, 24, \
                                           3*graph->width, 0xff0000, 0xff0000, 0xff0000, 0);
SDL_BlitSurface (graph->memfield, NULL, graph->screen, NULL);
SDL_UpdateRect(graph->screen, 0, 0, 0, 0);
return(1);
}
	 


int draw_origin(struct SDL_graphics *graph, int radius)
{
/*
 * Draws the point from where mass 1 is pending.
 *
 */   
int row, col;
float x, y;
float r, beta, dbeta;

x = (int)(X_ORIGIN * graph->width);
y = (int)(Y_ORIGIN * graph->height);

for(r = 0.0; r < radius; r += 0.5)
  {
  dbeta = 1.0 / (2.0 * PI * r);
  for(beta = 0.0; beta < 2.0*PI; beta += dbeta)
    {
    col = (int)(x + r*cos(beta)); 
    row = (int)(y + r*sin(beta)); 
 
    if((row >= 0) && (row < graph->height) && (col >= 0) && (col < graph->width))
      {
      graph->pixel[3*row*graph->width + 3*col    ] = 225;
      graph->pixel[3*row*graph->width + 3*col + 1] = 225;
      graph->pixel[3*row*graph->width + 3*col + 2] = 0;
      }
    }
  }

return(1);
}



int visualize_mass(struct SDL_graphics *graph, double theta, double phi, int m, int radius)
{
/*
 * Draws a filled circular disk with 'radius' in units of pixels around
 * the (x, y) position of mass m.
 * m = 0 corresponds to mass 2.
 * m = 1 corresponds to mass 1.
 *
 */   
int row, col;
float xo, yo, x, y;
float x1, x2, y1, y2;
float r, beta, dbeta;

xo = (int)(X_ORIGIN * graph->width);
yo = (int)(Y_ORIGIN * graph->height);
x1 = (int)(LENGHT * M_TO_PIXEL * sin(theta));
y1 = (int)(LENGHT * M_TO_PIXEL * cos(theta));
x2 = (int)(LENGHT * M_TO_PIXEL * sin(phi));
y2 = (int)(LENGHT * M_TO_PIXEL * cos(phi));

/* Coordinates x2 and y2 are added just for mass 2 */
x = xo + x1 + (1 - m) * x2;
y = yo + y1 + (1 - m) * y2;

/* Draw line */
for(r = 0.0; r < LENGHT; r += 0.01)
  {
  if(m)
    {
    col = xo + (int)(r * M_TO_PIXEL * sin(theta));
    row = yo + (int)(r * M_TO_PIXEL * cos(theta));
    }
  else
    {
    col = xo + x1 + (int)(r * M_TO_PIXEL * sin(phi));
    row = yo + y1 + (int)(r * M_TO_PIXEL * cos(phi));
    }

  if((row >= 0) && (row < graph->height) && (col >= 0) && (col < graph->width))
    {
    /* The color is black for mass 1 and red for mass 2 */
    graph->pixel[3*row*graph->width + 3*col    ] = (1 - m) * 225;
    graph->pixel[3*row*graph->width + 3*col + 1] = 0;
    graph->pixel[3*row*graph->width + 3*col + 2] = 0;
    }
  }

/* Draw mass */
for(r = 0.0; r < radius; r += 0.5)
  {
  dbeta = 1.0 / (2.0 * PI * r);
  for(beta = 0.0; beta < 2.0*PI; beta += dbeta)
    {
    col = (int)(x + r*cos(beta)); 
    row = (int)(y + r*sin(beta)); 
 
    if((row >= 0) && (row < graph->height) && (col >= 0) && (col < graph->width))
      {
      graph->pixel[3*row*graph->width + 3*col    ] = (1 - m) * 225;
      graph->pixel[3*row*graph->width + 3*col + 1] = 0;
      graph->pixel[3*row*graph->width + 3*col + 2] = 0;
      }
    }
  }

return(1);
}
		





int drawbox (struct SDL_graphics *graph, int left, int right, int top, int bottom, int width, int brightness)
{
int x, z, line;

line = 3*graph->width;

if(left>right || top>bottom || width<=0 || brightness<0 || brightness>255)
  {
  printf("\n\nFunction 'drawbox()' was called with nonsense arguments.\n\n");
  exit(0);
  }

for(x=left-width+1; x!=right+width; x++)
  {
  for(z=top-width+1; z!=top+1; z++)
    {
    graph->pixel[z*line+3*x  ]=brightness;
    graph->pixel[z*line+3*x+1]=brightness;
    graph->pixel[z*line+3*x+2]=brightness;
    }
  for(z=bottom; z!=bottom+width; z++)
    {
    graph->pixel[z*line+3*x  ]=brightness;
    graph->pixel[z*line+3*x+1]=brightness;
    graph->pixel[z*line+3*x+2]=brightness;
    }
  }

for(z=top-width+1; z!=bottom+width; z++)
  {
  for(x=left-width+1; x!=left+1; x++)
    {
    graph->pixel[z*line+3*x  ]=brightness;
    graph->pixel[z*line+3*x+1]=brightness;
    graph->pixel[z*line+3*x+2]=brightness;
    }
  for(x=right; x!=right+width; x++)
    {
    graph->pixel[z*line+3*x  ]=brightness;
    graph->pixel[z*line+3*x+1]=brightness;
    graph->pixel[z*line+3*x+2]=brightness;
    }
  }

return(1);
}





int write_ppm(struct SDL_graphics *graph, char *filename)
{
FILE *file;

if((file=fopen(filename,"w"))==NULL)
  {
  printf("\n\nError:\n\nCould not open the file %s for writing\n\n",filename);
  exit(0);
  }

fprintf(file,"P6\n%d %d\n%d\n", graph->width, graph->height, 255);

fwrite (graph->pixel, 1, 3*graph->width*graph->height, file);

fclose(file);
return(1);
}
