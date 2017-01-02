#include "stdafx.h"
#include "ImageReader.h"

#include <io.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <gdiplus.h>
#include <gdiplusheaders.h>

using namespace Gdiplus;
using namespace std;
#pragma comment( lib, "gdiplus.lib")
#pragma warning(disable:4996)
#pragma warning(disable:4267)

static F_Map nameMap[] =
{
	{ BMP, "*.bmp" },
	{ GIF, "*.gif" },
	{ PNG, "*.png" },
	{ TIF, "*.tif" },
	{ JPG, "*.jpg" },
	{ JPEG, "*.JPEG"}
};
string ImageReader::m_filePath = "E:\\Work\\TestFile\\Pics\\";
string ImageReader::m_targetFile = "E:\\Work\\TestFile\\Pics\\026.jpg";

ImageReader::ImageReader()
{
	m_fileList.clear();
	m_pUtils = Utils::GetInstance();

	GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::Status ret = GdiplusStartup(&m_gdiToken, &gdiplusStartupInput, NULL);
	m_gdiReady = Gdiplus::Ok == ret ? true : false;

	ASSERT(NULL != m_pUtils);
	//if (NULL == m_pUtils)
	//MessageBox(NULL, (LPCWSTR)"Util Failed!", (LPCWSTR)"Error", MB_ICONWARNING);
}


ImageReader::~ImageReader()
{
	if (m_gdiReady) GdiplusShutdown(m_gdiToken);
}

string ImageReader::GetTypeName(F_Type type)
{
	for (BYTE i = 0; i < MAX_TYPE; ++i)
	{
		if (type == nameMap[i].type) return nameMap[i].name;
	}
	return "";
}

bool ImageReader::GetFileListFromPath(string path, vector<string>& fileList)
{	
	bool bResult = false;
#ifdef _USE_32BIT_TIME_T
	long hFile = 0;
	struct _finddata_t fileInfo;
#else
	intptr_t hFile = 0;
	struct _finddata64i32_t fileInfo;
#endif
	

	memset(&fileInfo, 0, sizeof(_finddata64i32_t));
	fileList.clear();
	try {
		if (SYS_ERR != (hFile = _findfirst(path.c_str(), &fileInfo)))
		{
			do
			{
				if (!(fileInfo.attrib & _A_SUBDIR))
				{
					fileList.push_back(fileInfo.name);
				}
			} while (0 == _findnext(hFile, &fileInfo));
			_findclose(hFile);
			bResult = true;
		}
	}
	catch (...) {
		printf("Err Ocurred!!\n");
	}
	
	return bResult;
}

vector<string>& ImageReader::GetFile(string path, F_Type type)
{
	unsigned int fileNum = 0;
	string iPath = path;
	string sPath = path + GetTypeName(type);

	if (!GetFileListFromPath(sPath, m_fileList))
	{
		printf("\nIn FileReader::GetFile(),Failed!!\n");
	}

	return m_fileList;
}

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

// sFold & dFold should be existed!
void ImageReader::GenTargetFile(string sFold, string dFold, F_Type sType, F_Type dType)
{
	CLSID pngClsid;
	DWORD fileIdx = 0;
	LPWSTR iFile = NULL;
	vector<string> fileList = GetFile(sFold, sType);

	for (; fileIdx < fileList.size(); ++fileIdx)
	{
		iFile = m_pUtils->Str2WStr(sFold + fileList[fileIdx]);
		Image pic(iFile);
		Image *ptTarget = pic.GetThumbnailImage(30, 30, NULL, NULL);

		m_pUtils->GetEncoderClsid(L"image/png", &pngClsid);
		ptTarget->Save(m_pUtils->Str2WStr(dFold + fileList[fileIdx]), &pngClsid, NULL);
	}
}

void ImageReader::testPics(HWND hWnd)
{
	Mat image;
	Mat greyImage;
	string iPath = "";
	LPWSTR file = NULL;
	unsigned int fileNum = 0;
	vector<string> fileList;

	GenTargetFile(m_filePath, m_filePath + "NewPng\\", JPG);
	fileList = GetFile(m_filePath);
	for (; fileNum < m_fileList.size(); ++fileNum)
	{
		iPath = m_filePath + m_fileList[fileNum];

		file = m_pUtils->Str2WStr(iPath);
		Image pic(file);
		Image *ptThm = pic.GetThumbnailImage(30, 30, NULL, NULL);

		CLSID pngClsid;
		m_pUtils->GetEncoderClsid(L"image/png", &pngClsid);
		string newFile = "MyNew\\" + m_fileList[fileNum];
		ptThm->Save(m_pUtils->Str2WStr(newFile)/*L"MyNew\\my.png"*/, &pngClsid, NULL);
#if 1
		HDC hdc = GetWindowDC(hWnd);
		Graphics gf(hdc);
		Image thumbPic(m_pUtils->Str2WStr("MyNew\\" + m_fileList[fileNum]));
		gf.DrawImage(&thumbPic, 1, 1, thumbPic.GetWidth(), thumbPic.GetHeight());
		Status ret =
			gf.DrawImage(
				ptThm,
				1,
				1,
				ptThm->GetWidth(),
				ptThm->GetHeight());

		delete[] file;
		delete ptThm;
#endif
#if 0
		image = imread(iPath);
		if (NULL == image.data) continue;

		//cvtColor(image, greyImage, CV_BGR2GRAY);
		//imwrite("../../images/Gray_Image.jpg", greyImage);

		namedWindow(m_fileList[fileNum], CV_WINDOW_AUTOSIZE);
		//namedWindow("Gray image", CV_WINDOW_AUTOSIZE);

		imshow(m_fileList[fileNum], image);
		//imshow("Gray image", greyImage);
#endif
		waitKey(0);
	}

	//Test Math pic:
	IsIdentical("MyNew\\", "MyNew\\pattern.png");
}

DWORD32 GetMulti(WORD arrayA[])
{
	DWORD32 total = 0;
	for (DWORD32 i = 0; i < MAX_PIX * MAX_PIX; i++)
	{
		total += arrayA[i];
	}
	return total;
}

DWORD GetSimilarity(string fileA, string fileB)
{
	Mat imageA = imread(fileA);
	Mat imageB = imread(fileB);
	size_t row = Utils::Get3Min(imageA.rows, imageB.rows, MAX_PIX);
	size_t col = Utils::Get3Min(imageA.cols, imageB.cols, MAX_PIX);
	Vec3b vecRst[MAX_PIX][MAX_PIX] = { { 0 } };
	WORD  pixRst[MAX_PIX * MAX_PIX] = { 0 };
	WORD  rstIdx = 0;

	if (NULL == imageA.data || NULL == imageB.data) return (MAX_PIX * MAX_PIX * 255 * 3);
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			Vec3b vecA = imageA.at<Vec3b>(i, j);
			Vec3b vecB = imageB.at<Vec3b>(i, j);
			vecRst[i][j] = vecA - vecB;
			pixRst[rstIdx++] = abs(vecRst[i][j][0]) + abs(vecRst[i][j][1]) + abs(vecRst[i][j][2]);
		}
	}
	return GetMulti(pixRst);
}

bool CheckThresh(DWORD32 thresh)
{
	return thresh < IMAGE_DVALUE_THRESHOLD;
}

bool ImageReader::IsIdentical(string fold, string targetFile)
{
	string fullPath = "";
	DWORD32 simRate = 0;
	vector<string> fileList = GetFile(fold);

	for (DWORD i = 0; i < fileList.size(); i++)
	{
		fullPath = fold + fileList[i];
		simRate = GetSimilarity(fullPath, targetFile);
		if (CheckThresh(simRate))
		{
			//OutputDebugString(Str2WStr(fullPath));
			return true;
		}
	}
	return false;
}

DWORD ImageReader::GetFileNum(F_Type type, string path)
{
	DWORD dwNum = 0;
	long  hFile = 0;
	string fullPath = "";
	struct _finddata_t fileInfo;

	if (path.empty()) path = m_filePath;
	fullPath = path + GetTypeName(type);
	if (SYS_ERR == (hFile = (long)_findfirst(fullPath.c_str(), &fileInfo)))
	{
		_findclose(hFile);
		return 0;
	}
	do
	{
		if (!(fileInfo.attrib & _A_SUBDIR)) dwNum++;
	} while (0 == _findnext(hFile, &fileInfo));
	_findclose(hFile);

	return dwNum;
}

DWORD ImageReader::FastGetFileNum(F_Type type, string path)
{
	DWORD dwNum = 0;
	long  hFile = 0;
	string fullPath = "";
	char cmd[128] = { 0 };

	if (path.empty()) path = m_filePath;
	fullPath = path + GetTypeName(type);
	sprintf(cmd, "cmd /c dir /b /a-d %s >FileNum.txt", fullPath.c_str());
	WinExec(cmd, SW_HIDE);
	fstream fs("FileNum.txt");
	string str;
	if (fs)
	{
		while (getline(fs, str)) ++dwNum;
		fs.close();
	}
	return dwNum;
}

// TODO: Pic Rotation; Pic Move; Sample Get; Sample Compare; ; ; ;
/*
std::string getCmdRes(const std::string sc)
{
FILE* crs = popen(sc.c_str(), "r");	// execute the shell command
char result[1024] = "0";
fread(result, sizeof(char), sizeof(result), crs);

if (NULL != crs)
{
fclose(crs);
crs = NULL;
}

std::string res = result;
return res;
}
*/

void ImageReader::SetFilePath(string filePath)
{
	m_filePath = filePath;
}

void ImageReader::SetTargetFile(string file)
{
	m_targetFile = file;
}
