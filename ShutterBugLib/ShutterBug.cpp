#include "StdAfx.h"
#include ".\shutterbug.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

CShutterBug::CShutterBug(void)
{
	m_pGraph = NULL;
	m_pGrabber = NULL;
	CoInitialize(NULL);
}

CShutterBug::~CShutterBug(void)
{
	StopCamera();
	CoUninitialize();
}

void CShutterBug::Error( TCHAR * pText )
{
	TCHAR szBuffer[_MAX_PATH];
	memset(szBuffer,0,sizeof(TCHAR) * _MAX_PATH);
	ExpandEnvironmentStrings(_T("%TEMP%"),szBuffer,sizeof(TCHAR) * _MAX_PATH);
	TCHAR fileName[_MAX_PATH];
	if(_tcslen(szBuffer)) {
		if(_T('\\')==szBuffer[_tcslen(szBuffer)-1]) {
			szBuffer[_tcslen(szBuffer)-1] = _T('\0');
		}
		_stprintf(fileName,_T("%s\\%s"),szBuffer,_T("ShutterBugLog.log\0"));
	} else {
		_stprintf(fileName,_T("C:\\ShutterBugLog.log\0"));
	}
	SYSTEMTIME st;
	GetLocalTime(&st);
	ofstream ofs;
	ofs.open(fileName,ios_base::out|ios_base::app);
#ifdef _UNICODE
	char szOut[_MAX_PATH];
	memset(szOut,0,_MAX_PATH);
	wctomb(szOut,pText);
	ofs << szOut << endl;
#else
	ofs << pText << " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << " " << st.wMonth << "." << st.wDay << "." << st.wYear << endl;
#endif
	ofs.close();
}

void CShutterBug::StartCamera(HWND hWnd,RECT& rect)
{
    HRESULT hr;
	imageCache = NULL;
	imageCacheLength = NULL;
    // create a filter graph
    //
    hr = m_pGraph.CoCreateInstance( CLSID_FilterGraph );
    if( !m_pGraph )
    {
        Error( TEXT("Could not create filter graph") );
        return;
    }
    CComPtr< IBaseFilter > pWebCamera;
    CComPtr< ICreateDevEnum > pCreateDevEnum;
    pCreateDevEnum.CoCreateInstance( CLSID_SystemDeviceEnum );

	CComPtr< IEnumMoniker > pEm;
    pCreateDevEnum->CreateClassEnumerator( CLSID_VideoInputDeviceCategory, &pEm, 0 );
	
	CComPtr< IMoniker > pMoniker = NULL;
	ULONG cFetched = 0;

	if(S_OK==pEm->Next(1,&pMoniker,&cFetched)) {
		hr = pMoniker->BindToObject(0,0,IID_IBaseFilter, (void**)&pWebCamera);
	}

    // add the capture filter to the graph
    //
    hr = m_pGraph->AddFilter( pWebCamera, L"Web Video Camera" );
    if( FAILED( hr ) )
    {
        Error( TEXT("Could not put capture device in graph"));
        return;
    }

    // create a sample grabber
    //
    hr = m_pGrabber.CoCreateInstance( CLSID_SampleGrabber );
    if( !m_pGrabber )
    {
        Error( TEXT("Could not create SampleGrabber (is qedit.dll registered?)"));
        return;
    }
    CComQIPtr< IBaseFilter, &IID_IBaseFilter > pGrabBase( m_pGrabber );

    // force it to connect to video, 24 bit
    //
	AM_MEDIA_TYPE VideoType;
	ZeroMemory(&VideoType, sizeof(AM_MEDIA_TYPE));
	VideoType.majortype = MEDIATYPE_Video;
	VideoType.subtype = MEDIASUBTYPE_RGB32;
    hr = m_pGrabber->SetMediaType( &VideoType ); // shouldn't fail
    if( FAILED( hr ) )
    {
        Error( TEXT("Could not set media type"));
        return;
    }

    // add the grabber to the graph
    //
    hr = m_pGraph->AddFilter( pGrabBase, L"Grabber" );
    if( FAILED( hr ) )
    {
        Error( TEXT("Could not put sample grabber in graph"));
        return;
    }

    // build the graph
    CComPtr<ICaptureGraphBuilder2> pCGB2;
    hr = pCGB2.CoCreateInstance (CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC);
    if (FAILED( hr ))
    {
        Error(TEXT ("Can't get a ICaptureGraphBuilder2 reference"));
        return;
    }

    hr = pCGB2->SetFiltergraph( m_pGraph );
    if (FAILED( hr ))
    {
        Error(TEXT("SetGraph failed"));
        return;
    }


    // If there is a VP pin present on the video device, then put the 
    // renderer on CLSID_NullRenderer
    CComPtr<IPin> pVPPin;
    hr = pCGB2->FindPin(
                        pWebCamera, 
                        PINDIR_OUTPUT, 
                        &PIN_CATEGORY_VIDEOPORT, 
                        NULL, 
                        FALSE, 
                        0, 
                        &pVPPin);


    // If there is a VP pin, put the renderer on NULL Renderer
    CComPtr<IBaseFilter> pRenderer;
    if (S_OK == hr)
    {   
        hr = pRenderer.CoCreateInstance(CLSID_NullRenderer);    
        if (S_OK != hr)
        {
            Error(TEXT("Unable to make a NULL renderer"));
            return;
        }
        hr = m_pGraph->AddFilter(pRenderer, L"NULL renderer");
        if (FAILED (hr))
        {
            Error(TEXT("Can't add the filter to graph"));
            return;
        }
    }

    hr = pCGB2->RenderStream(
                            &PIN_CATEGORY_PREVIEW,
                            &MEDIATYPE_Interleaved, 
                            pWebCamera, 
                            pGrabBase, 
                            pRenderer);
    if (FAILED (hr))
    {
        // try to render preview pin
        hr = pCGB2->RenderStream( 
                                &PIN_CATEGORY_PREVIEW, 
                                &MEDIATYPE_Video,
                                pWebCamera, 
                                pGrabBase, 
                                pRenderer);

        // try to render capture pin
        if( FAILED( hr ) )
        {
            hr = pCGB2->RenderStream( 
                                    &PIN_CATEGORY_CAPTURE, 
                                    &MEDIATYPE_Video,
                                    pWebCamera, 
                                    pGrabBase, 
                                    pRenderer);
        }
    }

    if( FAILED( hr ) )
    {
        Error( TEXT("Can't build the graph") );
        return;
    }

    // don't buffer the samples as they pass through
    //
    hr = m_pGrabber->SetBufferSamples( TRUE );

    // only grab one at a time, stop stream after
    // grabbing one sample
    //
    hr = m_pGrabber->SetOneShot( FALSE );
	
	// find the video window and stuff it in our window
    //
	CComQIPtr< IVideoWindow, &IID_IVideoWindow > pVideoWindow = m_pGraph;
    if( !pVideoWindow )
    {
        Error( TEXT("Could not get video window interface"));
        return;
    }

    // Set the video window to be a child of the main window
	if(0!=hWnd) {
		hr = pVideoWindow->put_Owner((OAHWND)hWnd);
		hr = pVideoWindow->put_Left( 0 );
	    hr = pVideoWindow->put_Top( 0 );
		hr = pVideoWindow->put_Width( rect.right - rect.left );
	    hr = pVideoWindow->put_Height( rect.bottom - rect.top );
		hr = pVideoWindow->put_WindowStyle( WS_CHILD | WS_CLIPSIBLINGS );
		hr = pVideoWindow->put_Visible( OATRUE );
	} else {
		hr = pVideoWindow->put_AutoShow( OAFALSE );
		hr = pVideoWindow->put_Visible( OAFALSE );
	}

    CComQIPtr< IMediaControl, &IID_IMediaControl > pControl = m_pGraph;
    hr = pControl->Run( );
	Error(_T("Camera Started"));
}

void CShutterBug::SnapPhotoToFile(TCHAR* szFileName)
{
	long imageLength=0;
	BYTE* image = SnapPhoto(&imageLength);
	if((NULL==image) || (0==imageLength) ) {
		//MessageBox(NULL,"Error Getting Picture Info","Err",MB_OK);
		return;
	}
	HANDLE hf = CreateFile(
		szFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL,
		CREATE_ALWAYS, NULL, NULL );

    if( hf == INVALID_HANDLE_VALUE )
        return;

	DWORD dwWritten = 0;
    WriteFile( hf, image, imageLength, &dwWritten, NULL );

    CloseHandle( hf );
}


BYTE* CShutterBug::SnapPhoto(long *imageLength)
{
	HRESULT hr;

	// Find the required buffer size.
	long lBufferSize = 0;
	hr = m_pGrabber->GetCurrentBuffer(&lBufferSize, NULL);
	char *pBuffer = new char[lBufferSize];
	if (!pBuffer) 
	{
		Error(_T("Out Of Memory Taking Picture"));
	}
	hr = m_pGrabber->GetCurrentBuffer(&lBufferSize, (long*)pBuffer);

	AM_MEDIA_TYPE mt;
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	hr = m_pGrabber->GetConnectedMediaType(&mt);
	if (FAILED(hr))
	{
		Error(_T("Failed Getting Media Type"));
	}
	// Examine the format block.
	VIDEOINFOHEADER *pVih;
	if ((mt.formattype == FORMAT_VideoInfo) && 
		(mt.cbFormat >= sizeof(VIDEOINFOHEADER)) &&
		(mt.pbFormat != NULL) ) 
	{
		pVih = (VIDEOINFOHEADER*)mt.pbFormat;
	}
	else 
	{
		// Wrong format. Free the format block and return an error.
		Error(_T("Image Format is not correct"));
		return(NULL);
	}


    // write out the file header
    //
    BITMAPFILEHEADER bfh;
    memset( &bfh, 0, sizeof( bfh ) );
    bfh.bfType = 'MB';
    bfh.bfSize = sizeof( bfh ) + lBufferSize + sizeof( BITMAPINFOHEADER );
    bfh.bfOffBits = sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER );

	*imageLength = sizeof(bfh) + sizeof(pVih->bmiHeader) + lBufferSize;
	if( (imageCacheLength != *imageLength) || (NULL==imageCache)) {
		if(NULL!=imageCache) { delete[] imageCache; }
		imageCache = new BYTE[*imageLength];
		if(NULL == imageCache) { return(NULL); }
	}

	BYTE *pImgArray = imageCache;
	memcpy(pImgArray,&bfh,sizeof(bfh));
	pImgArray += sizeof(bfh);

	memcpy(pImgArray,&(pVih->bmiHeader), sizeof(pVih->bmiHeader));
	pImgArray += sizeof(pVih->bmiHeader);

	memcpy(pImgArray, pBuffer, lBufferSize);
	delete[] pBuffer;
	return(imageCache);
}


void CShutterBug::StopCamera(void)
{
	if(m_pGraph) {
	    CComQIPtr< IMediaControl, &IID_IMediaControl > pControl = m_pGraph;
		pControl->Stop();
		Error(_T("Camera Stopped"));
	}
	if(m_pGrabber) m_pGrabber.Release();
	if(m_pGraph) m_pGraph.Release();
	m_pGrabber = NULL;
	m_pGraph = NULL;
	if(NULL!=imageCache) { delete[] imageCache; }
	imageCacheLength = 0;
}

void CShutterBug::StartCamera(HANDLE hWnd, int left, int top, int right, int bottom)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
	StartCamera((HWND)hWnd,rect);
}