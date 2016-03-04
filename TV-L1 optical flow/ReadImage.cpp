#include "ReadImage.h"

void *read_image(IplImage * img)
{
	
	if (img->nChannels != 1)
	{
		 printf("non-scalarizable image");
		return NULL;
	}
	//debug
	cvNamedWindow("DebugUncolor",CV_WINDOW_AUTOSIZE);
	cvShowImage("DebugUncolor" ,img);
	cvWaitKey(0);
}

