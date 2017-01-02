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

	// ��ȡ�ļ��б�
	virtual vector<string>& GetFile(string path, F_Type type = PNG) = 0;
	// ��ȡ�ļ�����
	virtual DWORD GetFileNum(F_Type type, string path = "") = 0;
	virtual DWORD FastGetFileNum(F_Type type, string path = "") = 0;
	// ���Ժ���
	virtual void testPics(HWND hWnd) = 0;
};

