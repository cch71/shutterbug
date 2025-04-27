#pragma once
//#using <mscorlib.dll>
#include <atlbase.h>
#include <dshow.h>
#include <qedit.h>
#include <windows.h>

class CShutterBug
{
private:
	void Error(TCHAR * pText);
	BYTE *imageCache;
	int imageCacheLength;
protected:
    // either the capture live graph, or the capture still graph
    CComPtr< IGraphBuilder > m_pGraph;
    // the sample grabber for grabbing stills
    CComPtr< ISampleGrabber > m_pGrabber;
public:
	CShutterBug(void);
	~CShutterBug(void);
	void StartCamera(HWND hWnd,RECT& rect);
	void StartCamera(HANDLE hWnd, int left, int top, int right, int bottom);
	void SnapPhotoToFile(TCHAR* szFileName);
	BYTE* SnapPhoto(long* imageLength);
	void StopCamera(void);
};
