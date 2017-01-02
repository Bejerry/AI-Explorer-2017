
#include "Utils.h"
#include "ImageInterface.h"

#if _MSC_VER > 1000
#pragma once
#endif

#define SYS_ERR -1

class ImageReader : public Singleton<ImageReader>, public ImageInterface
{
public:
	ImageReader();
	virtual ~ImageReader();
	
	virtual void testPics(HWND hWnd);
	virtual vector<string>& GetFile(string path, F_Type type = PNG);
	virtual DWORD GetFileNum(F_Type type, string path);
	virtual DWORD FastGetFileNum(F_Type type, string path);

	virtual bool IsIdentical(string fold, string targetFile);
	void GenTargetFile(string sFold, string dFold, F_Type sType = PNG, F_Type dType = PNG);
private:
	bool GetFileListFromPath(string path, vector<string>& fileList);
	string GetTypeName(F_Type type);
	
	vector<string> m_fileList;
	static string  m_filePath;
	static string  m_targetFile;
	ULONG_PTR m_gdiToken;
	bool m_gdiReady;
	Utils *m_pUtils;
public:
	static void SetFilePath(string filePath);
	static void SetTargetFile(string file);
};

