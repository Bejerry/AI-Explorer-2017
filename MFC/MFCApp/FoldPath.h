#pragma once

class FoldPath : public CDialogEx
{
	DECLARE_DYNAMIC(FoldPath)

public:
	FoldPath(CWnd* pParent = NULL);
	virtual ~FoldPath();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARA_SET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
};
