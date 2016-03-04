#define ZOOM_SIGMA_ZERO 0.6
void zoom_size(
	int nx,      // width of the orignal image
	int ny,      // height of the orignal image
	int *nxx,    // width of the zoomed image
	int *nyy,    // height of the zoomed image
	float factor // zoom factor between 0 and 1
	);
void zoom_out(
	const float *I,    // input image
	float *Iout,       // output image
	const int nx,      // image width
	const int ny,      // image height
	const float factor // zoom factor between 0 and 1
	);
void zoom_in(
	const float *I, // input image
	float *Iout,    // output image
	int nx,         // width of the original image
	int ny,         // height of the original image
	int nxx,        // width of the zoomed image
	int nyy         // height of the zoomed image
	);