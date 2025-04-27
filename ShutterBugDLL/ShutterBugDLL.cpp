// ShutterBug.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ShutterBugDLL.h"
#include "..\ShutterBugLib\ShutterBug.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

CShutterBug* g_ShutterBug=NULL;
// This is an example of an exported variable
//SHUTTERBUG_API int nShutterBug=0;

SHUTTERBUG_API void CameraStart(HANDLE hWnd, int left, int top, int right, int bottom) {
	if(NULL!=g_ShutterBug) { return; }
	g_ShutterBug = new CShutterBug();
	g_ShutterBug->StartCamera(hWnd,left,top,right,bottom);
}

SHUTTERBUG_API void CameraSnapPhotoToFile(TCHAR* szFileName) {
	if(NULL==g_ShutterBug) { return; }
	g_ShutterBug->SnapPhotoToFile(szFileName);
}

SHUTTERBUG_API void CameraSnapPhoto(int** pImage, long* pImageLength) {
	if(NULL==g_ShutterBug) { return; }
	*pImage = (int*) g_ShutterBug->SnapPhoto(pImageLength);
	return;
}

SHUTTERBUG_API void CameraStop(void) {
	if(NULL==g_ShutterBug) { return; }
	g_ShutterBug->StopCamera();
	delete g_ShutterBug;
	g_ShutterBug = NULL;
}


// This is the constructor of a class that has been exported.
// see ShutterBug.h for the class definition
//CShutterBug::CShutterBug()
//{ 
//	return; 
//}



