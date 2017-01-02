#pragma once

#include "Singleton.h"
#include "TypeDef.h"

#include <gdiplus.h>
#include <gdiplusheaders.h>

using namespace Gdiplus;

class ImageReader;
class FileTools : public Singleton<FileTools>
{
public:
	FileTools();
	FileTools(const FileTools& self) 
	{
		m_pImageReader = self.m_pImageReader;
	}
	virtual ~FileTools();

public:
	vector<string>& GetFileList(string path, F_Type type);
	static Image* toThumbnail(string pImage);
	static BOOLEAN SaveThumbnail(string img, BOOLEAN isThumb, Image* pThumb = NULL);
	static BOOLEAN SaveTargetFile(Image* pFile, string path);
	static string GetPathFile(string path, BOOLEAN isThumb, int pos = POS_INVALID);
	static string GetFileName(string path, int site = POS_INVALID);

private:
	ImageReader *m_pImageReader;

	static string GetPath(string path, BOOLEAN isThumb, int pos);
};

