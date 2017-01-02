#pragma once
#include "ImageProcItf.h"

class ImageSmoothProc : public ImageProcItf
{
public:
	ImageSmoothProc();
	virtual ~ImageSmoothProc();

	void imageSmooth(void);
};

