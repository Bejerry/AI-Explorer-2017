#include <string>
#include <vector>

using namespace std;

#pragma once

#include "TypeDef.h"

class ImageInterface
{
public:
	ImageInterface();
	virtual ~ImageInterface();

	// 获取文件列表
	virtual vector<string>& GetFile(string path, F_Type type = PNG) = 0;
	// 获取文件数量
	virtual DWORD GetFileNum(F_Type type, string path = "") = 0;
	virtual DWORD FastGetFileNum(F_Type type, string path = "") = 0;
	// 测试函数
	virtual void testPics(HWND hWnd) = 0;
};

