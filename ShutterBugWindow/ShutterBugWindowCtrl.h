#pragma once

// ShutterBugWindowCtrl.h : Declaration of the CShutterBugWindowCtrl ActiveX Control class.


// CShutterBugWindowCtrl : See ShutterBugWindowCtrl.cpp for implementation.

class CShutterBugWindowCtrl : public COleControl
{
	DECLARE_DYNCREATE(CShutterBugWindowCtrl)

// Constructor
public:
	CShutterBugWindowCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

private:
	void UpdateWebImage();
// Implementation
protected:
	~CShutterBugWindowCtrl();

	DECLARE_OLECREATE_EX(CShutterBugWindowCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CShutterBugWindowCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CShutterBugWindowCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CShutterBugWindowCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();
// Event maps
	DECLARE_EVENT_MAP()

private:
	UINT_PTR m_TimerID;
	CImage *m_imgBMP;
	bool m_isConnected;
// Dispatch and event IDs
public:
	enum {
		dispidRefreshDelay = 2,		dispidImageURL = 1
	};
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
protected:
	void OnImageURLChanged(void);
	CString m_ImageURL;
	void OnRefreshDelayChanged(void);
	LONG m_RefreshDelay;
};

