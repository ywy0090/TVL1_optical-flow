#include <stdlib.h>
#include <stdio.h>
#include <math.h>



#define BOUNDARY_CONDITION_DIRICHLET 0
#define BOUNDARY_CONDITION_REFLECTING 1
#define BOUNDARY_CONDITION_PERIODIC 2

#define DEFAULT_GAUSSIAN_WINDOW_SIZE 5
#define DEFAULT_BOUNDARY_CONDITION BOUNDARY_CONDITION_REFLECTING
void divergence(
	const float *v1, // x component of the vector field
	const float *v2, // y component of the vector field
	float *div,      // output divergence
	const int nx,    // image width
	const int ny     // image height
	);
void forward_gradient(
	const float *f, //input image
	float *fx,      //computed x derivative
	float *fy,      //computed y derivative
	const int nx,   //image width
	const int ny    //image height
	);
void centered_gradient(
	const float *input,  //input image
	float *dx,           //computed x derivative
	float *dy,           //computed y derivative
	const int nx,        //image width
	const int ny         //image height
	);
void gaussian(
	float  *I,             // input/output image
	const int xdim,       // image width
	const int ydim,       // image height
	const double sigma    // Gaussian sigma
	);