#include "stdafx.h"
#include "ImageSmoothProc.h"

#include <string>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;

string testImage = "E:\\Work\\TestFile\\Pics\\lena.jpg";

ImageSmoothProc::ImageSmoothProc()
{
}


ImageSmoothProc::~ImageSmoothProc()
{
}

using namespace cv;

void ImageSmoothProc::imageSmooth(void)
{
	Mat org = imread(testImage, 1);


}

/*
int display_caption( char* caption ) 
{ 
dst = Mat::zeros( src.size(), src.type() ); 
putText( dst, caption, Point( src.cols/4, src.rows/2), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255) );

imshow( window_name, dst ); 
int c = waitKey( DELAY_CAPTION ); 
if( c >= 0 ) 
{ 
return -1; 
} 
return 0;
}

*/