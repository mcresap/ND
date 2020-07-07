/*
 * fractal.c - Sample Mandelbrot Fractal Display
 * Starting code for CSE 30341 Project 3.
 * */

#include "gfx.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <complex.h>
#include <pthread.h>

/*
 * Compute the number of iterations at point x, y
 * in the complex space, up to a maximum of maxiter.
 * Return the number of iterations at that point.
 *
 * This example computes the Mandelbrot fractal:
 * z = z^2 + alpha
 *
 * Where z is initially zero, and alpha is the location x + iy
 * in the complex plane.  Note that we are using the "complex"
 * numeric type in C, which has the special functions cabs()
 * and cpow() to compute the absolute values and powers of
 * complex values.
 * */

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
int *tasks=0;
struct options{
	double xmin;
	double xmax;
	double ymin;
	double ymax; 
	int maxiter;
	int chunkmin;
	int chunkmax;
};


static int compute_point( double x, double y, int max)
{
	double complex z = 0;
	double complex alpha = x + I*y;

	int iter = 0;

	while( cabs(z)<4 && iter < max ) {
		z = cpow(z,2) + alpha;
		iter++;
	}

	return iter;
}

/*
 * Compute an entire image, writing each point to the given bitmap.
 * Scale the image to the range (xmin-xmax,ymin-ymax).
 * */

void *compute_image(void *args)
{
	int i,j;

	int width = gfx_xsize();
	int height = gfx_ysize();

	struct options *args2 = args;
	double xmin = args2->xmin;
	double xmax = args2->xmax;
	double ymin=args2->ymin;
	double ymax=args2->ymax; 
	int maxiter=args2->maxiter;
	int chunkmin=args2->chunkmin;
	int chunkmax=args2->chunkmax;

	// For every pixel i,j, in the image...

	for(j=chunkmin; j <= chunkmax; j++) {
		int status =0;
		pthread_mutex_lock(&mutex2);
		if (tasks[j]==0){
			status=1;
			tasks[j]=1;
		}
		pthread_mutex_unlock(&mutex2);
		if (status ==1){
			for(i=0;i<width;i++) {
			
				// Scale from pixels i,j to coordinates x,y
				double x = xmin + i*(xmax-xmin)/width;
				double y = ymin + j*(ymax-ymin)/height;
				// Compute the iterations at x,y
				int iter = compute_point(x,y,maxiter);

				pthread_mutex_lock(&mutex);
				// Convert a iteration number to an RGB color.
				// (Change this bit to get more interesting colors.)
				int gray = 255 * iter / maxiter;
				gfx_color(gray,gray,gray);
	
				// Plot the point on the screen.
				gfx_point(i,j);
				pthread_mutex_unlock(&mutex);
			}
		}
	}
	return 0;
}

void threads(int x, double xmin, double xmax, double ymin, double ymax, int maxiter){
	int numthreads = x;
	int ysize = gfx_ysize();
	int chunks = ysize/numthreads;
	int chunkmin, chunkmax;
	int currline=0;
	pthread_t arr[numthreads];
	
	tasks = malloc(sizeof(int) *gfx_ysize());
	
	for (int i=0; i<=numthreads; i++){
		tasks[i]=0;
		chunkmin=currline;
		chunkmax=currline+chunks;
		currline=chunkmax+1;
		struct options *args = malloc(sizeof(*args));
		args->xmin = xmin;
		args->xmax = xmax;
		args->ymin = ymin;
		args->ymax = ymax;
		args->maxiter = maxiter;
		args->chunkmin = chunkmin;
		args->chunkmax = chunkmax;

		pthread_create(&arr[i], NULL, compute_image, args);
	}

	for (int i=0; i<=numthreads; i++){
		pthread_join(arr[i], NULL);

	}
	free(tasks);
}

int main( int argc, char *argv[] )
{
	// The initial boundaries of the fractal image in x,y space.
	double xmin=-1.5;
	double xmax= 0.5;
	double ymin=-1.0;
	double ymax= 1.0;

	// Maximum number of iterations to compute.
	// Higher values take longer but have more detail. 
	int maxiter=100;

	// Open a new window.
	gfx_open(640,480,"Mandelbrot Fractal");

	// Show the configuration, just in case you want to recreate it.
	printf("coordinates: %lf %lf %lf %lf\n",xmin,xmax,ymin,ymax);

	// Fill it with a dark blue initially.
	gfx_clear_color(0,0,255);
	gfx_clear();
	int x=1;
	// Display the fractal image

	threads(x, xmin, xmax, ymin, ymax, maxiter);
	while(1) {
		// Wait for a key or mouse click.
		int c = gfx_wait();
		
		// Quit if q is pressed.
		if(c=='q') exit(0);
		if (c=='i') { //zoom in
			xmin+=.2;
			xmax-=.2;
			ymin+=.2;
			ymax-=.2;
		}
		if (c=='o') { //zoom out
			xmin-=.2;
			xmax+=.2;
			ymin-=.2;
			ymax+=.2;
		}
		if (c=='l') { //move left
			xmin-=.1;
			xmax-=.1;
		}
		if (c=='r') { //move right
			xmin+=.1;
			xmax+=.1;
		}
		if (c=='1'){ //1 thread
			x=1;
		}	
		if (c=='2'){ //2threads
			x=2;
		}
		if (c=='3'){
			x=3;
		}
		if (c=='4'){
			x=4;
		}
		if (c=='5'){
			x=5;
		}
		if (c=='6'){
			x=6;
		}
		if (c=='7'){
			x=7;
		}	
		if (c=='8'){
			x=8;
		}
		gfx_clear();
		threads(x, xmin, xmax, ymin, ymax, maxiter);
	}
	
	return 0;
}
