
// MFCAppDoc.h : CMFCAppDoc ��Ľӿ�
//


#pragma once


class CMFCAppDoc : public CDocument
{
protected: // �������л�����
	CMFCAppDoc();
	DECLARE_DYNCREATE(CMFCAppDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMFCAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
