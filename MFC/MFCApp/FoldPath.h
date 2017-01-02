#pragma once


// FoldPath dialog

class FoldPath : public CDialogEx
{
	DECLARE_DYNAMIC(FoldPath)

public:
	FoldPath(CWnd* pParent = NULL);   // standard constructor
	virtual ~FoldPath();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARA_SET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
