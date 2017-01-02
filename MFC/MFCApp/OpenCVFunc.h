
#include "Singleton.h"

#pragma once

class OpenCVFunc : public Singleton<OpenCVFunc> 
{
public:
	OpenCVFunc();
	virtual ~OpenCVFunc();

	void FuncTest(void);
};

