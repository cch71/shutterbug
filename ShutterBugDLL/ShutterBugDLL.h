// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SHUTTERBUG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SHUTTERBUG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef SHUTTERBUG_EXPORTS
#define SHUTTERBUG_API __declspec(dllexport)
#else
#define SHUTTERBUG_API __declspec(dllimport)
#endif

// This class is exported from the ShutterBug.dll
/*
class SHUTTERBUG_API CShutterBug {
public:
	CShutterBug(void);
	// TODO: add your methods here.
};
*/

//extern SHUTTERBUG_API int nShutterBug;

#ifdef __cplusplus
extern "C"{
#endif 

SHUTTERBUG_API void CameraStart(HANDLE hWnd, int left, int top, int right, int bottom);
SHUTTERBUG_API void CameraSnapPhotoToFile(TCHAR* szFileName);
SHUTTERBUG_API void CameraSnapPhoto(int** pImage,long* pImageLength);
SHUTTERBUG_API void CameraStop(void);

#ifdef __cplusplus
}
#endif 

