#include "stdafx.h"
#include "OpenCVFunc.h"

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

OpenCVFunc::OpenCVFunc()
{
}


OpenCVFunc::~OpenCVFunc()
{
}

void OpenCVFunc::FuncTest(void)
{
	Mat A, C;                                 // ֻ������Ϣͷ����
	A = imread("E:\\Work\\TestFile\\Pics\\026.jpg", CV_LOAD_IMAGE_COLOR); // ����Ϊ���󿪱��ڴ�

	Mat B(A);                                 // ʹ�ÿ������캯��

	C = A;                                    // ��ֵ�����
	Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
	Mat D(A, Rect(10, 10, 100, 100)); // using a rectangle
	//Mat E = A(Range:all(), Range(1, 3)); // using row and column boundaries
	//cout << "M = " << endl << " " << M << endl << endl;
}
