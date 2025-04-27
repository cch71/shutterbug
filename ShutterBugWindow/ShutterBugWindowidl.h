

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Thu Aug 21 00:33:33 2003
 */
/* Compiler settings for .\ShutterBugWindow.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __ShutterBugWindowidl_h__
#define __ShutterBugWindowidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DShutterBugWindow_FWD_DEFINED__
#define ___DShutterBugWindow_FWD_DEFINED__
typedef interface _DShutterBugWindow _DShutterBugWindow;
#endif 	/* ___DShutterBugWindow_FWD_DEFINED__ */


#ifndef ___DShutterBugWindowEvents_FWD_DEFINED__
#define ___DShutterBugWindowEvents_FWD_DEFINED__
typedef interface _DShutterBugWindowEvents _DShutterBugWindowEvents;
#endif 	/* ___DShutterBugWindowEvents_FWD_DEFINED__ */


#ifndef __ShutterBugWindow_FWD_DEFINED__
#define __ShutterBugWindow_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShutterBugWindow ShutterBugWindow;
#else
typedef struct ShutterBugWindow ShutterBugWindow;
#endif /* __cplusplus */

#endif 	/* __ShutterBugWindow_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __ShutterBugWindowLib_LIBRARY_DEFINED__
#define __ShutterBugWindowLib_LIBRARY_DEFINED__

/* library ShutterBugWindowLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_ShutterBugWindowLib;

#ifndef ___DShutterBugWindow_DISPINTERFACE_DEFINED__
#define ___DShutterBugWindow_DISPINTERFACE_DEFINED__

/* dispinterface _DShutterBugWindow */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DShutterBugWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("869F5284-303C-4BCA-B1AC-EED283FB9AE8")
    _DShutterBugWindow : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DShutterBugWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DShutterBugWindow * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DShutterBugWindow * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DShutterBugWindow * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DShutterBugWindow * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DShutterBugWindow * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DShutterBugWindow * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DShutterBugWindow * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DShutterBugWindowVtbl;

    interface _DShutterBugWindow
    {
        CONST_VTBL struct _DShutterBugWindowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DShutterBugWindow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DShutterBugWindow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DShutterBugWindow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DShutterBugWindow_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DShutterBugWindow_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DShutterBugWindow_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DShutterBugWindow_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DShutterBugWindow_DISPINTERFACE_DEFINED__ */


#ifndef ___DShutterBugWindowEvents_DISPINTERFACE_DEFINED__
#define ___DShutterBugWindowEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DShutterBugWindowEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DShutterBugWindowEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8AB21B2A-B199-4138-89E5-3D8557C3B76E")
    _DShutterBugWindowEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DShutterBugWindowEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DShutterBugWindowEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DShutterBugWindowEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DShutterBugWindowEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DShutterBugWindowEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DShutterBugWindowEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DShutterBugWindowEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DShutterBugWindowEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DShutterBugWindowEventsVtbl;

    interface _DShutterBugWindowEvents
    {
        CONST_VTBL struct _DShutterBugWindowEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DShutterBugWindowEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DShutterBugWindowEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DShutterBugWindowEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DShutterBugWindowEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DShutterBugWindowEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DShutterBugWindowEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DShutterBugWindowEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DShutterBugWindowEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ShutterBugWindow;

#ifdef __cplusplus

class DECLSPEC_UUID("0E296B30-0145-498B-9F5F-320797A01017")
ShutterBugWindow;
#endif
#endif /* __ShutterBugWindowLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


