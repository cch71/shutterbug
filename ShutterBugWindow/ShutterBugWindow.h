#pragma once

// ShutterBugWindow.h : main header file for ShutterBugWindow.DLL

#if !defined( __AFXCTL_H__ )
#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols


// CShutterBugWindowApp : See ShutterBugWindow.cpp for implementation.

class CShutterBugWindowApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

