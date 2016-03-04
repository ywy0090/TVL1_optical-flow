


#define BOUNDARY_CONDITION 0
//0 Neumann
//1 Periodic
//2 Symmetric
static int neumann_bc(int x, int nx, bool *out);
static int periodic_bc(int x, int nx, bool *out);
static int symmetric_bc(int x, int nx, bool *out);
static double cubic_interpolation_cell (
	double v[4],  //interpolation points
	double x      //point to be interpolated
	);
static double bicubic_interpolation_cell (
	double p[4][4], //array containing the interpolation points
	double x,       //x position to be interpolated
	double y        //y position to be interpolated
	);
float bicubic_interpolation_at(
	const float *input, //image to be interpolated
	const float  uu,    //x component of the vector field
	const float  vv,    //y component of the vector field
	const int    nx,    //image width
	const int    ny,    //image height
	bool         border_out //if true, return zero outside the region
	);
void bicubic_interpolation_warp(
	const float *input,     // image to be warped
	const float *u,         // x component of the vector field
	const float *v,         // y component of the vector field
	float       *output,    // image warped with bicubic interpolation
	const int    nx,        // image width
	const int    ny,        // image height
	bool         border_out // if true, put zeros outside the region
	);
