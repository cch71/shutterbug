#pragma once

// ShutterBugWindowPropPage.h : Declaration of the CShutterBugWindowPropPage property page class.


// CShutterBugWindowPropPage : See ShutterBugWindowPropPage.cpp for implementation.

class CShutterBugWindowPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CShutterBugWindowPropPage)
	DECLARE_OLECREATE_EX(CShutterBugWindowPropPage)

// Constructor
public:
	CShutterBugWindowPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_SHUTTERBUGWINDOW };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

