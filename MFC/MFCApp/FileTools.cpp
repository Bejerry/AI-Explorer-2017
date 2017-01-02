#include "stdafx.h"

#include "ImageReader.h"
#include "FileTools.h"

#include <gdiplusheaders.h>

using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
#pragma warning(disable : 4267)

FileTools::FileTools()
{
	m_pImageReader = ImageReader::GetInstance();
}

FileTools::~FileTools()
{
}

vector<string>& FileTools::GetFileList(string path, F_Type type)  
{
	return m_pImageReader->GetFile(path, type);
}

#include <io.h>
#include <direct.h> 
Image* FileTools::toThumbnail(string img)
{
	Image pic(Utils::Str2WStr(img));

	Image *ptThm = pic.GetThumbnailImage(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, NULL, NULL);

	return ptThm;
}

BOOLEAN FileTools::SaveThumbnail(string img, BOOLEAN isThumb, Image* pThumb)
{
	CLSID pngClsid;
	size_t pos = img.rfind("\\", img.length());
	ASSERT(pos != img.length());

	string thumbPath = GetPath(img, isThumb, pos);

	Utils::GetEncoderClsid(L"image/png", &pngClsid);
	string thumbImg = GetPathFile(img, isThumb, pos);

	if (RETURN_ERROR == _access(thumbPath.c_str(), 06)) _mkdir(thumbPath.c_str());
	if (NULL == pThumb) pThumb = toThumbnail(img);
	ASSERT(NULL != pThumb);
	pThumb->Save(Utils::Str2WStr(thumbImg), &pngClsid, NULL);

	return TRUE;
}

string FileTools::GetPath(string path, BOOLEAN isThumb, int site)
{
	size_t pos = site;

	if (POS_INVALID == site)
	{
		pos = path.rfind("\\", path.length());
		ASSERT(pos != path.length());
	}
	string typePath = isThumb ? ThumbnailFolder : TargetFolder;
	return (path.substr(0, pos) + "\\" + typePath);
}

string FileTools::GetPathFile(string path, BOOLEAN isThumb, int site)
{
	size_t pos = site;

	if (POS_INVALID == site)
	{
		pos = path.rfind("\\", path.length());
		ASSERT(pos != path.length());
	}
	return (GetPath(path, isThumb, pos) + path.substr(pos, path.length()));
}

BOOLEAN FileTools::SaveTargetFile(Image* pFile, string path)
{
	ASSERT(NULL != pFile);

	CLSID pngClsid;
	Utils::GetEncoderClsid(L"image/png", &pngClsid);
	if (RETURN_ERROR == _access(path.c_str(), 06)) _mkdir(path.c_str());
	
	pFile->Save(Utils::Str2WStr(path), &pngClsid, NULL); // should be path-file!!
	return TRUE;
}

string FileTools::GetFileName(string path, int site)
{
	size_t pos = site;

	if (POS_INVALID == site)
	{
		pos = path.rfind("\\", path.length());
		ASSERT(pos != path.length());
	}
	return path.substr(pos + 1, path.length());
}