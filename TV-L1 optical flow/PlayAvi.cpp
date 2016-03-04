#include "ReadImage.h"
#include "tvl1flow_lib.h"
#include "saveOpticalFlow.h"
#ifndef DISABLE_OMP
#include <omp.h>

#include "opencv2/highgui/highgui.hpp"
#endif//DISABLE_OMP


#define DISABLE_OMP

#define PAR_DEFAULT_OUTFLOW "flow.flo"
#define PAR_DEFAULT_NPROC   0
#define PAR_DEFAULT_TAU     0.25
#define PAR_DEFAULT_LAMBDA  0.15
#define PAR_DEFAULT_THETA   0.3
#define PAR_DEFAULT_NSCALES 100
#define PAR_DEFAULT_ZFACTOR 0.5
#define PAR_DEFAULT_NWARPS  5
#define PAR_DEFAULT_EPSILON 0.01
#define PAR_DEFAULT_VERBOSE 0




int main(int argc, char *argv[])
{
	int i = 1;
	char* outfile = (argc>i)? argv[i]: PAR_DEFAULT_OUTFLOW;       i++;
	int   nproc   = (argc>i)? atoi(argv[i]): PAR_DEFAULT_NPROC;   i++;
	float tau     = (argc>i)? atof(argv[i]): PAR_DEFAULT_TAU;     i++;
	float lambda  = (argc>i)? atof(argv[i]): PAR_DEFAULT_LAMBDA;  i++;
	float theta   = (argc>i)? atof(argv[i]): PAR_DEFAULT_THETA;   i++;
	int   nscales = (argc>i)? atoi(argv[i]): PAR_DEFAULT_NSCALES; i++;
	float zfactor = (argc>i)? atof(argv[i]): PAR_DEFAULT_ZFACTOR; i++;
	int   nwarps  = (argc>i)? atoi(argv[i]): PAR_DEFAULT_NWARPS;  i++;
	float epsilon = (argc>i)? atof(argv[i]): PAR_DEFAULT_EPSILON; i++;
	int   verbose = (argc>i)? atoi(argv[i]): PAR_DEFAULT_VERBOSE; i++;
	if (nproc < 0) {
		nproc = PAR_DEFAULT_NPROC;
		if (verbose) fprintf(stderr, "warning: "
			"nproc changed to %d\n", nproc);
	}
	if (tau <= 0 || tau > 0.25) {
		tau = PAR_DEFAULT_TAU;
		if (verbose) fprintf(stderr, "warning: "
			"tau changed to %g\n", tau);
	}
	if (lambda <= 0) {
		lambda = PAR_DEFAULT_LAMBDA;
		if (verbose) fprintf(stderr, "warning: "
			"lambda changed to %g\n", lambda);
	}
	if (theta <= 0) {
		theta = PAR_DEFAULT_THETA;
		if (verbose) fprintf(stderr, "warning: "
			"theta changed to %g\n", theta);
	}
	if (nscales <= 0) {
		nscales = PAR_DEFAULT_NSCALES;
		if (verbose) fprintf(stderr, "warning: "
			"nscales changed to %d\n", nscales);
	}
	if (zfactor <= 0 || zfactor >= 1) {
		zfactor = PAR_DEFAULT_ZFACTOR;
		if (verbose) fprintf(stderr, "warning: "
			"zfactor changed to %g\n", zfactor);
	}
	if (nwarps <= 0) {
		nwarps = PAR_DEFAULT_NWARPS;
		if (verbose) fprintf(stderr, "warning: "
			"nwarps changed to %d\n", nwarps);
	}
	if (epsilon <= 0) {
		epsilon = PAR_DEFAULT_EPSILON;
		if (verbose) fprintf(stderr, "warning: "
			"epsilon changed to %f\n", epsilon);
	}

#ifndef DISABLE_OMP
	if (nproc > 0)
		omp_set_num_threads(nproc);
#endif

	int    nx, ny, nx2, ny2;
	IplImage *I0,*I1;
	IplImage *optical_flow1, *optical_flow2;

	CvCapture* capture = cvCreateFileCapture("video.avi");
	if (capture != NULL)
	{
		cvNamedWindow( "Original Video", CV_WINDOW_AUTOSIZE );
		IplImage *frame1;
		IplImage *frame2;
		while(1) 
		{
			frame1 = cvQueryFrame( capture );
			if(!frame1) break;
			cvShowImage("Original Video", frame1 );
			optical_flow1 = cvCreateImage(cvSize(frame1->width, frame1->height), frame1->depth, 1);
			cvCvtColor(frame1, optical_flow1, CV_RGB2GRAY);
			for (int i=0;i<2;i++)
			{
				cvQueryFrame(capture);
			}
			frame2 = cvQueryFrame( capture );
			cvShowImage("Original Video", frame2 );
			optical_flow2 = cvCreateImage(cvSize(frame2->width, frame2->height), frame2->depth, 1);
			cvCvtColor(frame2, optical_flow2, CV_RGB2GRAY);
			//debug
			//read_image(optical_flow1);
			//read_image(optical_flow2);
			//
			char c = cvWaitKey(33);
			if( c == 27 ) break;
			
			//cal the optical flow
			nx = frame1->width;
			ny = frame1->height;
			nx2 = frame2->width;
			ny2 = frame2->height;
			if (nx == nx2 && ny == ny2)
			{
				
				
				
				
				//debug
				//
				I0 = cvCreateImage(cvSize(frame1->width,frame1->height), IPL_DEPTH_32F, 1);
				cvScale(optical_flow1, I0, 1/255., 0.0 );
				I1 = cvCreateImage(cvSize(frame2->width, frame2->height), IPL_DEPTH_32F, 1);
				cvScale(optical_flow2, I1, 1/255., 0.0 );
				//read_image(I0);
				//read_image(I1);
				
				const float N = 1 + log(hypot(nx, ny)/16.0) / log(1/zfactor);
				if (N < nscales)
					nscales = N;
				if (verbose)
					fprintf(stderr,
					"nproc=%d tau=%f lambda=%f theta=%f nscales=%d "
					"zfactor=%f nwarps=%d epsilon=%g\n",
					nproc, tau, lambda, theta, nscales,
					zfactor, nwarps, epsilon);
				IplImage *u = cvCreateImage(cvSize(nx,ny), IPL_DEPTH_32F, 1);
				IplImage *v = cvCreateImage(cvSize(nx2,ny2), IPL_DEPTH_32F, 1);
				Dual_TVL1_optic_flow_multiscale(
					(float *)I0->imageData, (float *)I1->imageData, (float *)u->imageData, (float *)v->imageData, nx, ny, tau, lambda, theta,
					nscales, zfactor, nwarps, epsilon, verbose
					);
				showImage(u, v);
				
			}
		}
		cvReleaseCapture( &capture );
		cvDestroyWindow("Original Video");
		cvDestroyWindow("TVL1Optical Flow");
	}
}
