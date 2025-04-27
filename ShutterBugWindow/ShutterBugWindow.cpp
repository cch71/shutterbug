// ShutterBugWindow.cpp : Implementation of CShutterBugWindowApp and DLL registration.

#include "stdafx.h"
#include "ShutterBugWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CShutterBugWindowApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x6D317765, 0xE37D, 0x498B, { 0x84, 0x65, 0x1E, 0x73, 0xF5, 0x54, 0xCE, 0x8E } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CShutterBugWindowApp::InitInstance - DLL initialization

BOOL CShutterBugWindowApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CShutterBugWindowApp::ExitInstance - DLL termination

int CShutterBugWindowApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
