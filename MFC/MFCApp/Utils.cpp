
#include "stdafx.h"
#include "TypeDef.h"
#include "Utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
}

using namespace std;

LPWSTR Utils::Str2WStr(const std::string& s)
{
	int Len = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, s.c_str(), -1, NULL, NULL);
	LPWSTR lpszW = new WCHAR[Len];

	MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, lpszW, Len);

	return lpszW;
}

string Utils::Tchar2Str(TCHAR *str)
{
	int iLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	char* chRtn = new char[iLen * sizeof(char)];

	WideCharToMultiByte(CP_ACP, 0, str, -1, chRtn, iLen, NULL, NULL);

	string stdStr(chRtn);

	return stdStr;
}

string Utils::CStr2Str(CString CStr)
{
#ifdef UNICODE
	return CStringA(CStr).GetBuffer(0);
#else
	return CStr.GetBuffer(0);
#endif
}

const char* Utils::CStr2Char(CString CStr)
{
	size_t sz = 0;
	const size_t strSZ = (CStr.GetLength() + 1) * 2;
	char *pStr = new char[strSZ];

	setlocale(LC_ALL, "chs"); // 支持中文
	wcstombs_s(&sz, pStr, strSZ, CStr, _TRUNCATE);

	return pStr;
	//return CStr2Str(CStr).data(); //.c_str()
}

#include <gdiplus.h>
using namespace Gdiplus;
/**
@name    GetEncoderClsid
@brief   取图片类型GLSID
@param[in]        const WCHAR * format
@param[in]        CLSID * pClsid
@return           int
*/
int Utils::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;
	UINT  size = 0;
	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	free(pImageCodecInfo);
	return -1;
}

int Utils::Get3Max(int a, int b, int c)
{
	return a > b ? a > c ? a : c : b > c ? b : c;
}

int Utils::Get3Min(int a, int b, int c)
{
	return a > b ? b > c ? c : b : a > c ? c : a;
}

#if 0
// GDI库使用
#include <gdiplus.h>
using namespace Gdiplus;
#pragma  comment(lib, "gdiplus.lib")

ULONG_PTR m_gdiplusToken;
Gdiplus::GdiplusStartupInput StartupInput;

GdiplusStartup(&m_gdiplusToken, &StartupInput, NULL); // GDI+初始化

Gdiplus::GdiplusShutdown(m_gdiplusToken); // GDI+卸载
#endif

#ifdef FindMainWindow
struct handle_data {
	unsigned long process_id;
	HWND best_handle;
};
HWND find_main_window(unsigned long process_id)
{
	handle_data data;
	data.process_id = process_id;
	data.best_handle = 0;
	EnumWindows(enum_windows_callback, (LPARAM)&data);
	return data.best_handle;
}
BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.process_id != process_id || !is_main_window(handle)) {
		return TRUE;
	}
	data.best_handle = handle;
	return FALSE;
}
BOOL is_main_window(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}
#endif // FindMainWindow

