#pragma once

#include <string>

#include "Singleton.h"

class Utils : public Singleton<Utils>
{
public:
	Utils();
	virtual ~Utils();

public:
	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);	
	std::string Tchar2Str(TCHAR *str);
	static std::string CStr2Str(CString CStr);
	const char* CStr2Char(CString CStr);
	static LPWSTR Str2WStr(const std::string& s);
	static int Get3Max(int a, int b, int c);
	static int Get3Min(int a, int b, int c);
};

