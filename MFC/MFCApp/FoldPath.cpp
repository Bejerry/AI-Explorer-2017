// FoldPath.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApp.h"
#include "FoldPath.h"
#include "afxdialogex.h"


// FoldPath dialog

IMPLEMENT_DYNAMIC(FoldPath, CDialogEx)

FoldPath::FoldPath(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PARA_SET, pParent)
{

}

FoldPath::~FoldPath()
{
}

void FoldPath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FoldPath, CDialogEx)
END_MESSAGE_MAP()


// FoldPath message handlers
