// ShutterBugWindowCtrl.cpp : Implementation of the CShutterBugWindowCtrl ActiveX Control class.

#include "stdafx.h"
#include <afxinet.h>
#include <atlimage.h>
#include "ShutterBugWindow.h"
#include "ShutterBugWindowCtrl.h"
#include "ShutterBugWindowPropPage.h"
#include ".\shutterbugwindowctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CShutterBugWindowApp NEAR theApp;

IMPLEMENT_DYNCREATE(CShutterBugWindowCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CShutterBugWindowCtrl, COleControl)
	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CShutterBugWindowCtrl, COleControl)
	DISP_FUNCTION_ID(CShutterBugWindowCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CShutterBugWindowCtrl, "ImageURL", dispidImageURL, m_ImageURL, OnImageURLChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CShutterBugWindowCtrl, "RefreshDelay", dispidRefreshDelay, m_RefreshDelay, OnRefreshDelayChanged, VT_I4)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CShutterBugWindowCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CShutterBugWindowCtrl, 1)
	PROPPAGEID(CShutterBugWindowPropPage::guid)
END_PROPPAGEIDS(CShutterBugWindowCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CShutterBugWindowCtrl, "SHUTTERBUGWINDOW.ShutterBugWindowCtrl.1",
	0xe296b30, 0x145, 0x498b, 0x9f, 0x5f, 0x32, 0x7, 0x97, 0xa0, 0x10, 0x17)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CShutterBugWindowCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID BASED_CODE IID_DShutterBugWindow =
		{ 0x869F5284, 0x303C, 0x4BCA, { 0xB1, 0xAC, 0xEE, 0xD2, 0x83, 0xFB, 0x9A, 0xE8 } };
const IID BASED_CODE IID_DShutterBugWindowEvents =
		{ 0x8AB21B2A, 0xB199, 0x4138, { 0x89, 0xE5, 0x3D, 0x85, 0x57, 0xC3, 0xB7, 0x6E } };



// Control type information

static const DWORD BASED_CODE _dwShutterBugWindowOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CShutterBugWindowCtrl, IDS_SHUTTERBUGWINDOW, _dwShutterBugWindowOleMisc)



// CShutterBugWindowCtrl::CShutterBugWindowCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CShutterBugWindowCtrl

BOOL CShutterBugWindowCtrl::CShutterBugWindowCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegInsertable | afxRegApartmentThreading to afxRegInsertable.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_SHUTTERBUGWINDOW,
			IDB_SHUTTERBUGWINDOW,
			afxRegInsertable | afxRegApartmentThreading,
			_dwShutterBugWindowOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CShutterBugWindowCtrl::CShutterBugWindowCtrl - Constructor

CShutterBugWindowCtrl::CShutterBugWindowCtrl()
{
	m_TimerID = 0;
	m_imgBMP = NULL;
	m_RefreshDelay = 100000;
	m_isConnected = true;
	InitializeIIDs(&IID_DShutterBugWindow, &IID_DShutterBugWindowEvents);
}



// CShutterBugWindowCtrl::~CShutterBugWindowCtrl - Destructor

CShutterBugWindowCtrl::~CShutterBugWindowCtrl()
{
	if(NULL!=m_imgBMP) {
		delete m_imgBMP;
	}
}



// CShutterBugWindowCtrl::OnDraw - Drawing function

void CShutterBugWindowCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	DoSuperclassPaint(pdc, rcBounds);
	if(!m_TimerID) {
		m_TimerID = SetTimer(1,m_RefreshDelay,NULL);
		UpdateWebImage();
	}

	if(NULL!=m_imgBMP) {
		RECT destRect;
		this->GetClientRect(&destRect);
		m_imgBMP->StretchBlt(pdc->m_hDC,destRect);
	}

	if(!m_isConnected) {
		pdc->DrawIcon(0,0,theApp.LoadIcon(MAKEINTRESOURCE(IDI_NOCONNECTION)));
	}
}



// CShutterBugWindowCtrl::DoPropExchange - Persistence support

void CShutterBugWindowCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_String(pPX, _T("ImageURL"), m_ImageURL, _T(""));
	PX_Long(pPX, _T("RefreshDelay"), m_RefreshDelay, 1000000);


	// TODO: Call PX_ functions for each persistent custom property.
}



// CShutterBugWindowCtrl::OnResetState - Reset control to default state

void CShutterBugWindowCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CShutterBugWindowCtrl::AboutBox - Display an "About" box to the user
void CShutterBugWindowCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_SHUTTERBUGWINDOW);
	dlgAbout.DoModal();
}

// CShutterBugWindowCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CShutterBugWindowCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("STATIC");
	return COleControl::PreCreateWindow(cs);
}



// CShutterBugWindowCtrl::IsSubclassedControl - This is a subclassed control

BOOL CShutterBugWindowCtrl::IsSubclassedControl()
{
	return TRUE;
}



// CShutterBugWindowCtrl::OnOcmCommand - Handle command messages

LRESULT CShutterBugWindowCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}



// CShutterBugWindowCtrl message handlers

void CShutterBugWindowCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	UpdateWebImage();
	COleControl::OnLButtonDblClk(nFlags, point);
}

void CShutterBugWindowCtrl::UpdateWebImage() {
	if( (0==m_ImageURL.GetLength()) || (0==m_RefreshDelay) ) {return;}
	CInternetSession is(0,1,PRE_CONFIG_INTERNET_ACCESS,0,0,INTERNET_FLAG_DONT_CACHE);
	COleStreamFile imgStream;
	if(!imgStream.CreateMemoryStream()) {
		AfxMessageBox("Error Creating Memory Stream");
		return;
	}

	TRY
	{
		CStdioFile* webFile = is.OpenURL(m_ImageURL,1,INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_RELOAD|INTERNET_FLAG_DONT_CACHE);
		if(NULL!=webFile) {
			int bytesRead = 0;
			BYTE szBuff[1024];
			while ( (bytesRead=webFile->Read(szBuff,1024)) > 0)
			{
		      imgStream.Write(szBuff,bytesRead);
			}
			delete webFile;
			m_isConnected = true;
		} else {
			m_isConnected = false;
		}
		is.Close();
	}
	CATCH(CInternetException, pEx)
	{
			m_isConnected = false;
			this->UpdateWindow();
	}
	END_CATCH

	if(0<imgStream.GetLength()) {
		if(NULL!=m_imgBMP) { delete m_imgBMP; }
		m_imgBMP = new CImage();
		HRESULT result = m_imgBMP->Load(imgStream.GetStream());
		if(S_OK==result) {
			RECT destRect;
			this->GetClientRect(&destRect);
			CDC *dc = this->GetDC();
			if (dc) {
				m_imgBMP->StretchBlt(dc->m_hDC,destRect);
				if(!m_isConnected) {
					dc->DrawIcon(0,0,theApp.LoadIcon(MAKEINTRESOURCE(IDI_NOCONNECTION)));
				}
				this->ReleaseDC(dc);
				this->UpdateWindow();
			}
		}
		imgStream.Close();
	}
}

void CShutterBugWindowCtrl::OnTimer(UINT nIDEvent)
{
	UpdateWebImage();
	COleControl::OnTimer(nIDEvent);
}

void CShutterBugWindowCtrl::OnDestroy()
{
	COleControl::OnDestroy();

	if(m_TimerID) {
		KillTimer(m_TimerID);
		m_TimerID = 0;
	}
}

void CShutterBugWindowCtrl::OnImageURLChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}

void CShutterBugWindowCtrl::OnRefreshDelayChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}
