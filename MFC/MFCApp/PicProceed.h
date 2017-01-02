#pragma once
#include "AlgProceedItf.h"
#include "Utils.h"

class PicProceed : public AlgProceedItf<PicProceed>
{
public:
	PicProceed();
	PicProceed(CString filePath, CString targetFile, UINT thresh)
	{
		m_filePath = filePath;
		m_targetFile = targetFile;
		m_thresh = thresh;
	}
	virtual ~PicProceed();

public:
	void SetPicType(F_Type type);

protected:
	virtual void SetAlgPara(CString filePath, CString targetFile, UINT thresh);
	virtual void Start(void);

private:
	CString m_filePath;
	CString m_targetFile;
	UINT m_thresh;
	Utils *m_pUtils;
	F_Type m_picType;
	vector<string> m_picList;

	void GenThumbnail(void);
	void GetFileList(void);
	string GetFilePath(void);
	void DrawPic(HWND hwnd, string file);
	DWORD GetPicSimilarity(string fileA, string fileB);
	DWORD GetArrayAcc(WORD array[]);
	BOOLEAN IsPicIdentical(string picA, string picB);
	BOOLEAN CheckThresh(DWORD thresh)
	{
		return thresh < IMAGE_DVALUE_THRESHOLD;
	}
	void ProcessPic(void);

	string GetTargetFile()
	{
		return Utils::CStr2Str(m_targetFile);
	}
	string GetThumbPath()
	{
		return GetFilePath() + ThumbnailFolder;
	}
	string GetTargetPath()
	{
		return GetFilePath() + TargetFolder;
	}
	string GetTarPathFile(void);
	void DrawPic(string pathFile, string title = "UnNamed");
};

