// ShutterBugWindowPropPage.cpp : Implementation of the CShutterBugWindowPropPage property page class.

#include "stdafx.h"
#include "ShutterBugWindow.h"
#include "ShutterBugWindowPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CShutterBugWindowPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CShutterBugWindowPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CShutterBugWindowPropPage, "SHUTTERBUGWIND.ShutterBugWindPropPage.1",
	0x51b8a882, 0x9, 0x4714, 0x9a, 0x35, 0x2a, 0xf4, 0x44, 0x9c, 0x2e, 0x6e)



// CShutterBugWindowPropPage::CShutterBugWindowPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CShutterBugWindowPropPage

BOOL CShutterBugWindowPropPage::CShutterBugWindowPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SHUTTERBUGWINDOW_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CShutterBugWindowPropPage::CShutterBugWindowPropPage - Constructor

CShutterBugWindowPropPage::CShutterBugWindowPropPage() :
	COlePropertyPage(IDD, IDS_SHUTTERBUGWINDOW_PPG_CAPTION)
{
}



// CShutterBugWindowPropPage::DoDataExchange - Moves data between page and properties

void CShutterBugWindowPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CShutterBugWindowPropPage message handlers
