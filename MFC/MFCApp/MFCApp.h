
// MFCApp.h : MFCApp Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCAppApp:
// �йش����ʵ�֣������ MFCApp.cpp
//

class CMFCAppApp : public CWinApp
{
public:
	CMFCAppApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnImageTest();
	afx_msg void OnPatternDis();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCAppApp theApp;
