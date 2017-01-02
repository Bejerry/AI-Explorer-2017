
#include "stdafx.h"

#include "FileTools.h"
#include "TypeDef.h"
#include "PicProceed.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#pragma warning(disable:4267)

PicProceed::PicProceed()
	: m_picType(JPEG)
{
	m_pUtils = Utils::GetInstance();
	ASSERT(NULL != m_pUtils);
	m_picList.clear();
}

PicProceed::~PicProceed()
{
}

void PicProceed::SetPicType(F_Type type)
{
	m_picType = type;
}

void PicProceed::SetAlgPara(CString filePath, CString targetFile, UINT thresh)
{
	m_filePath = filePath;
	m_targetFile = targetFile;
	m_thresh = thresh;
}

/*
	��ʵ��������ʾ��ƥ���Pic�����ڿ���HashMap�ȱ����б�һ������Pic��N�η����ȶԺ���չʾ
*/
void PicProceed::Start(void)
{
	static WORD execNum = 1;
	char title[32] = { 0 };
	sprintf_s(title, "��%d��ִ��Ŀ��ͼ��", execNum++);

	GetFileList();

	DrawPic(GetTargetFile(), title);

	GenThumbnail();

	ProcessPic();
}

void PicProceed::GenThumbnail(void)
{
	size_t num = 0;

	for (; num < m_picList.size(); ++num)
	{
		if (!FileTools::SaveThumbnail(GetFilePath() + m_picList[num], TRUE)) break;
	}
	FileTools::SaveThumbnail(Utils::CStr2Str(m_targetFile), FALSE);
}

void PicProceed::GetFileList(void)
{
	string path = GetFilePath();
	m_picList = FileTools::GetInstance()->GetFileList(path, m_picType);
}

string PicProceed::GetFilePath(void)
{
	return Utils::CStr2Str(m_filePath) + "\\";
}

DWORD PicProceed::GetPicSimilarity(string fileA, string fileB)
{	
	WORD  rstIdx = 0;
	Mat imageA = imread(fileA);
	Mat imageB = imread(fileB);
	WORD  pixRst[MAX_PIX * MAX_PIX] = { 0 };
	Vec3b vecRst[MAX_PIX][MAX_PIX] = { { 0 } };
	size_t row = Utils::Get3Min(imageA.rows, imageB.rows, MAX_PIX);
	size_t col = Utils::Get3Min(imageA.cols, imageB.cols, MAX_PIX);

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
	return GetArrayAcc(pixRst);
}

DWORD PicProceed::GetArrayAcc(WORD arr[])
{
	DWORD total = 0;
	for (DWORD i = 0; i < MAX_PIX * MAX_PIX; i++)
	{
		total += arr[i];
	}
	return total;
}

BOOLEAN PicProceed::IsPicIdentical(string picA, string picB)
{
	DWORD simRate = GetPicSimilarity(picA, picB);

	return CheckThresh(simRate);
}

void PicProceed::ProcessPic(void)
{
	// ��ȡĿ���ļ�
	string target = GetTargetFile();

	// ��ȡthumbList
	// Image *img = FileTools::toThumbnail(target);
	// FileTools::SaveTargetFile(img, GetTargetPath());

	// ��ȡ�㷨
	/* ................ */

	// չʾĿ���ļ�
	// DrawPic(target, "Ŀ��ͼ��");

	// ѭ��ƥ��
	string tarFile = GetTarPathFile();
	string thuFile = GetThumbPath();
	DWORD index = 1;
	static DWORD execNum = 1;
	char title[64] = { 0 };
	for (DWORD idx = 0; idx < m_picList.size(); ++idx)
	{
		if (!IsPicIdentical(tarFile, thuFile + "\\" + m_picList[idx])) continue;

		// չʾ��ѡ�ļ�
		sprintf_s(title, "��%d��ִ�У���%d�ź�ѡͼ��", execNum++, index++);
		DrawPic(GetFilePath() + "\\" + m_picList[idx], title);
	}
	if (1 == index)
		MessageBox(NULL, _T("ͼ��ʶ������㷨��ִ����ɣ�û��ƥ���ϣ�"), _T("SUCCESS"), MB_OK);
	else
		MessageBox(NULL, _T("ͼ��ʶ������㷨��ִ�����...��"), _T("SUCCESS"), MB_OK);
}

string PicProceed::GetTarPathFile()
{
	return FileTools::GetPathFile(Utils::CStr2Str(m_targetFile), FALSE);
}

void PicProceed::DrawPic(string pathFile, string title)
{
	Mat image = imread(pathFile);
	ASSERT(NULL != image.data);

	string fileName = FileTools::GetFileName(pathFile);
	//cvtColor(image, greyImage, CV_BGR2GRAY);
	//imwrite("../../images/Gray_Image.jpg", greyImage);

	namedWindow(title, CV_WINDOW_AUTOSIZE);
	imshow(title, image);

	waitKey(5);
}

void PicProceed::DrawPic(HWND hWnd, string file)
{
	HDC hdc = GetWindowDC(hWnd);
	Graphics gf(hdc);
	Image pic(Utils::Str2WStr(file));
	Status ret = gf.DrawImage(&pic, 1, 1, pic.GetWidth(), pic.GetHeight());
}
