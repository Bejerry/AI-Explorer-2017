#pragma once

#include "Singleton.h"

class Utils;
class ImageReco : public CDialogEx, public Singleton<ImageReco>
{
	DECLARE_DYNAMIC(ImageReco)

public:
	ImageReco(CWnd* pParent = NULL);
	virtual ~ImageReco();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARA_SET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void AssertValid() const;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnFold();
	afx_msg void OnBnClickedBtnTarget();

private:
	static CString m_sFilePath;
	static CString m_sTargetFile;
	Utils *m_pUtils;
	BOOLEAN CheckPara(void);
	time_t m_startTime;
	CStatusBar m_statusBar;
	CString m_showTime;
	time_t m_elapse;
	HANDLE m_hThread;

public:
	static UINT m_thresh;
	afx_msg void OnEnChangeEdtThresh();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedBtnStop();
private:
	void SetStartTime();
	void SetStopTime();
	static void Begin(void);
	static void End(void);
	//static void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
public:
	void SetShowTime();
	static DWORD WINAPI MoniThread(LPVOID lpParam);
};