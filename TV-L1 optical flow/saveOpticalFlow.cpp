#include "saveOpticalFlow.h"
using namespace cv;

void showImage(IplImage *img1, IplImage *img2)
{
	
	if (img1!= NULL && img2!= NULL)
	{
		CvMat *magnitude;
		CvMat *angle;
		CvMat *_hls[4], *hsv;
		float mag_max;

		magnitude = cvCreateMat(img1->height, img1->width, CV_32F);
		angle = cvCreateMat(img1->height, img1->width, CV_32F);
		for (int i=0;i<4;i++)
		{
			_hls[i] = cvCreateMat(img1->height, img1->width, CV_32F);
		}
		hsv = cvCreateMat(img1->height, img1->width, CV_32FC4);

		cvCartToPolar(img1, img2, magnitude, angle, false);
		_hls[0] = cvCloneMat(angle);
		for (int i =0; i<angle->rows;i++)
		{
			for (int j=0; j<angle->cols;j++)
			{
				cvSetReal2D(_hls[1], i, j, 1.0);
				cvSetReal2D(_hls[3], i, j, 0.0);
			}
		}
		_hls[2] = cvCloneMat(magnitude);
		cvMerge( _hls[0], _hls[1], _hls[2], _hls[3], hsv);
		//convert to BGR and show
		//CvMat *bgr = cvCreateMat(hsv->rows, hsv->cols, hsv->type);//CV_32FC3 matrix
		//cvCvtColor(hsv,bgr, COLOR_HLS2RGB_FULL);

		cvNamedWindow("Optical Flow",CV_WINDOW_AUTOSIZE);
		cvShowImage("Optical Flow" ,hsv);
		//cvWaitKey(0);
		//cvReleaseImage(&img1);
		//cvReleaseImage(&img2);
		//cvDestroyWindow("Display Picture");
	}
	
	
	
}
