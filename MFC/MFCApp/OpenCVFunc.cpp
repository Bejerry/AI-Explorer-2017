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
	Mat A, C;                                 // 只创建信息头部分
	A = imread("E:\\Work\\TestFile\\Pics\\026.jpg", CV_LOAD_IMAGE_COLOR); // 这里为矩阵开辟内存

	Mat B(A);                                 // 使用拷贝构造函数

	C = A;                                    // 赋值运算符
	Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
	Mat D(A, Rect(10, 10, 100, 100)); // using a rectangle
	//Mat E = A(Range:all(), Range(1, 3)); // using row and column boundaries
	//cout << "M = " << endl << " " << M << endl << endl;
}
