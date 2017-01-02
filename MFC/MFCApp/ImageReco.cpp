// ImageReco.cpp : implementation file
//

#include <string>
#include <afxdlgs.h>

#include "stdafx.h"
#include "MFCApp.h"
#include "afxdialogex.h"
#include "ImageReader.h"
#include "PicProceed.h"
#include "ImageReco.h"


#define RECO_TIMER 1

volatile BOOLEAN g_isRun = TRUE;
CString ImageReco::m_sFilePath;
CString ImageReco::m_sTargetFile;
UINT ImageReco::m_thresh = 0;

IMPLEMENT_DYNAMIC(ImageReco, CDialogEx)

ImageReco::ImageReco(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PARA_SET, pParent)
{
	m_pUtils = Utils::GetInstance();
	ASSERT(NULL != m_pUtils);
}

ImageReco::~ImageReco()
{
}

static UINT indicators[] =
{
	IDS_INDICATOR_MESSAGE,
	IDS_INDICATOR_TIME,
};

void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	if (idEvent != RECO_TIMER) return;

	ImageReco::GetInstance()->SetShowTime();
}

void ImageReco::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_FOLD, m_sFilePath);
	DDX_Text(pDX, IDC_EDT_TARGET, m_sTargetFile);
	DDX_Text(pDX, IDC_EDT_THRESH, m_thresh);
	DDV_MinMaxUInt(pDX, m_thresh, 0, 100);
	DDX_Text(pDX, IDC_TIME, m_showTime);
	DDX_Text(pDX, IDC_ELAPSE, m_elapse);
}

BEGIN_MESSAGE_MAP(ImageReco, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_FOLD, &ImageReco::OnBnClickedBtnFold)
	ON_BN_CLICKED(IDC_BTN_TARGET, &ImageReco::OnBnClickedBtnTarget)
	ON_EN_CHANGE(IDC_EDT_THRESH, &ImageReco::OnEnChangeEdtThresh)
	ON_BN_CLICKED(IDC_BTN_START, &ImageReco::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &ImageReco::OnBnClickedBtnStop)
END_MESSAGE_MAP()
//  ON_WM_TIMER()

void ImageReco::OnBnClickedBtnFold()
{
	BROWSEINFO bi;
	TCHAR path[MAX_PATH];

	bi.hwndOwner = NULL;  // this->GetSafeHwnd();  
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;// Buffer;//此参数如为NULL则不能显示对话框
	bi.lpszTitle = TEXT("设置待检测图像库路径");
	bi.ulFlags = BIF_EDITBOX;//包括文件 BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT
	bi.lpfn = NULL;
	bi.iImage = IDR_MAINFRAME;

	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);
	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, path);
		ImageReader::SetFilePath(m_pUtils->Tchar2Str(path));
		m_sFilePath.Format(L"%s", path);
		UpdateData(FALSE);
	}
	LPMALLOC lpMalloc;
	if (FAILED(SHGetMalloc(&lpMalloc))) return;
	lpMalloc->Free(pIDList);
	lpMalloc->Release();
}

void GetTchar(char cStr[], TCHAR tcStr[])
{
#ifdef UNICODE
	MultiByteToWideChar(CP_ACP, 0, cStr, -1, tcStr, 100);
#else
	strcpy(tcStr, cStr);
#endif
}

static char BASED_CODE szFilter[] = { "All Files(*.*)|*.*||" };
void ImageReco::OnBnClickedBtnTarget()
{
	BOOLEAN bFileOpen = TRUE;
	TCHAR filter[64] = { 0 };
	CFileDialog *lpszOpenFile;
	GetTchar(szFilter, filter);
	lpszOpenFile = new CFileDialog(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filter, NULL);
	if (lpszOpenFile->DoModal() == IDOK)
	{
		CString szGetName;
		szGetName = lpszOpenFile->GetPathName();
		ImageReader::SetTargetFile(m_pUtils->CStr2Str(szGetName));
		m_sTargetFile = szGetName;
		UpdateData(FALSE);
	}
	delete lpszOpenFile;
}


void ImageReco::OnEnChangeEdtThresh()
{
	UpdateData(TRUE);
}

#include <io.h>
BOOLEAN ImageReco::CheckPara()
{
	if (m_thresh < 0 || m_thresh >100)
	{
		MessageBox(_T("阈值配置错误！"), _T("ERROR"), MB_ICONERROR | MB_OK);
		return FALSE;
	}
	const char* folderPath = m_pUtils->CStr2Char(m_sFilePath);
	if (-1 == _access(folderPath, 0))
	{
		MessageBox(_T("文件夹路径错误！"), _T("ERROR"), MB_ICONERROR | MB_OK);
		return FALSE;
	}
	const char* filePath = m_pUtils->CStr2Char(m_sTargetFile);
	if (-1 == _access(filePath, 06))
	{
		MessageBox(_T("目标文件不存在or读写权限不够！"), _T("ERROR"), MB_ICONERROR | MB_OK);
		return FALSE;
	}
	return TRUE;
}


void ImageReco::OnBnClickedBtnStart()
{
	UpdateData(TRUE);
	if (!CheckPara()) return;
	SetStartTime();
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MoniThread, NULL, 0, 0);

	while (g_isRun)
	{
		SetShowTime();
		MSG   msg;
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(1000); 
	}
	SetStopTime();
	CloseHandle(hThread);
}

void ImageReco::SetStartTime()
{
	m_startTime = time(NULL);
	
	g_isRun = TRUE;

	SetShowTime();
}

void ImageReco::SetStopTime()
{
	time_t now = time(NULL);

	g_isRun = FALSE;
	KillTimer(RECO_TIMER);

	m_elapse = (now - m_startTime);
	UpdateData(FALSE);
}

void ImageReco::SetShowTime()
{
	struct tm st;
	time_t t = time(NULL);
	char time[32] = { 0 };

	localtime_s(&st, &t);
	strftime(time, 12, "%T", &st);
	m_showTime = time;

	UpdateData(FALSE);
}
/*
CTime time;
CString strTime;
time = CTime::GetCurrentTime();
strTime = time.Format("%H:%M:%S");
*/

void ImageReco::OnBnClickedBtnStop()
{
	g_isRun = FALSE;
	KillTimer(RECO_TIMER);
}

void ImageReco::OnTimer(UINT nIDEvent)
{
	SetShowTime();
}

template <typename T>
AlgProceedItf<T>* GetAlgProcess(void)
{
	return &AlgProceedItf<T>::GetProcessor();
}

void ImageReco::Begin(void)
{
	AlgProceedItf<PicProceed> *processor = GetAlgProcess<PicProceed>();

	processor->SetAlgPara(m_sFilePath, m_sTargetFile, m_thresh);
	processor->Start();
}

void ImageReco::End(void)
{
	g_isRun = FALSE;
}

DWORD WINAPI ImageReco::MoniThread(LPVOID lpParam)
{
	Begin();

	End();

	return RESULT_SUCC;
}

/* 重载系统多线程操作下的Debug异常抛出 */
void ImageReco::AssertValid() const
{
	if (m_hWnd == NULL)
		return;     // null (unattached) windows are valid

					// check for special wnd??? values
	ASSERT(HWND_TOP == NULL);       // same as desktop
	if (m_hWnd == HWND_BOTTOM)
		ASSERT(this == &CWnd::wndBottom);
	else if (m_hWnd == HWND_TOPMOST)
		ASSERT(this == &CWnd::wndTopMost);
	else if (m_hWnd == HWND_NOTOPMOST)
		ASSERT(this == &CWnd::wndNoTopMost);
	else
	{
		// should be a normal window
		ASSERT(::IsWindow(m_hWnd));

		// should also be in the permanent or temporary handle map
		// CHandleMap* pMap = afxMapHWND();
		// ASSERT(pMap != NULL);

		//CObject* p = NULL;
		//if (pMap)
		//{
		//	ASSERT((p = pMap->LookupPermanent(m_hWnd)) != NULL ||
		//		(p = pMap->LookupTemporary(m_hWnd)) != NULL);
		//}
		//ASSERT((CWnd*)p == this);   // must be us

		// Note: if either of the above asserts fire and you are
		// writing a multithreaded application, it is likely that
		// you have passed a C++ object from one thread to another
		// and have used that object in a way that was not intended.
		// (only simple inline wrapper functions should be used)
		//
		// In general, CWnd objects should be passed by HWND from
		// one thread to another.  The receiving thread can wrap
		// the HWND with a CWnd object by using CWnd::FromHandle.
		//
		// It is dangerous to pass C++ objects from one thread to
		// another, unless the objects are designed to be used in
		// such a manner.
		/***************
		http://www.cnblogs.com/yan-boy/archive/2012/09/08/2676154.html
		**************************/
	}
}
