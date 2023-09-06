

/* this ALWAYS GENERATED file contains the definitions for the interfaces */



/* Compiler settings for ProtocolApp.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ProtocolApp_h__
#define __ProtocolApp_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IProtocol_FWD_DEFINED__
#define __IProtocol_FWD_DEFINED__
typedef interface IProtocol IProtocol;
#endif 	/* __IProtocol_FWD_DEFINED__ */


#ifndef __IProtocolInfo_FWD_DEFINED__
#define __IProtocolInfo_FWD_DEFINED__
typedef interface IProtocolInfo IProtocolInfo;
#endif 	/* __IProtocolInfo_FWD_DEFINED__ */


#ifndef __IProtocolInfoDi_FWD_DEFINED__
#define __IProtocolInfoDi_FWD_DEFINED__
typedef interface IProtocolInfoDi IProtocolInfoDi;
#endif 	/* __IProtocolInfoDi_FWD_DEFINED__ */


#ifndef __Protocol_FWD_DEFINED__
#define __Protocol_FWD_DEFINED__

#ifdef __cplusplus
typedef class Protocol Protocol;
#else
typedef struct Protocol Protocol;
#endif /* __cplusplus */

#endif 	/* __Protocol_FWD_DEFINED__ */


#ifndef __ProtocolInfo_FWD_DEFINED__
#define __ProtocolInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProtocolInfo ProtocolInfo;
#else
typedef struct ProtocolInfo ProtocolInfo;
#endif /* __cplusplus */

#endif 	/* __ProtocolInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IProtocol_INTERFACE_DEFINED__
#define __IProtocol_INTERFACE_DEFINED__

/* interface IProtocol */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IProtocol;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("30F8E23A-B1D2-49c5-9AD6-90BB0A8E7066")
    IProtocol : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IProtocolVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProtocol * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProtocol * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProtocol * This);
        
        END_INTERFACE
    } IProtocolVtbl;

    interface IProtocol
    {
        CONST_VTBL struct IProtocolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProtocol_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProtocol_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProtocol_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProtocol_INTERFACE_DEFINED__ */


#ifndef __IProtocolInfo_INTERFACE_DEFINED__
#define __IProtocolInfo_INTERFACE_DEFINED__

/* interface IProtocolInfo */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IProtocolInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1F7D0311-358E-4150-90FC-4AEF7A3782B5")
    IProtocolInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVersion( 
            /* [in] */ BSTR inputMsg,
            /* [retval][out] */ BSTR *out_version) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ToBase64( 
            /* [in] */ unsigned char *data,
            /* [in] */ int len,
            /* [retval][out] */ BSTR *out_data64) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FileToBase64( 
            /* [in] */ BSTR path,
            /* [retval][out] */ BSTR *out_data64) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EncodeAndBase64( 
            /* [in] */ BSTR encName,
            /* [in] */ BSTR text,
            /* [retval][out] */ BSTR *out_data64) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Base64ToFile( 
            /* [in] */ BSTR path,
            /* [in] */ BSTR data64) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFileStream( 
            /* [in] */ BSTR path,
            /* [retval][out] */ IStream **out_stream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProtocolInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProtocolInfo * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProtocolInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProtocolInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IProtocolInfo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IProtocolInfo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IProtocolInfo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IProtocolInfo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVersion )( 
            IProtocolInfo * This,
            /* [in] */ BSTR inputMsg,
            /* [retval][out] */ BSTR *out_version);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToBase64 )( 
            IProtocolInfo * This,
            /* [in] */ unsigned char *data,
            /* [in] */ int len,
            /* [retval][out] */ BSTR *out_data64);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FileToBase64 )( 
            IProtocolInfo * This,
            /* [in] */ BSTR path,
            /* [retval][out] */ BSTR *out_data64);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EncodeAndBase64 )( 
            IProtocolInfo * This,
            /* [in] */ BSTR encName,
            /* [in] */ BSTR text,
            /* [retval][out] */ BSTR *out_data64);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Base64ToFile )( 
            IProtocolInfo * This,
            /* [in] */ BSTR path,
            /* [in] */ BSTR data64);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFileStream )( 
            IProtocolInfo * This,
            /* [in] */ BSTR path,
            /* [retval][out] */ IStream **out_stream);
        
        END_INTERFACE
    } IProtocolInfoVtbl;

    interface IProtocolInfo
    {
        CONST_VTBL struct IProtocolInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProtocolInfo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProtocolInfo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProtocolInfo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProtocolInfo_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IProtocolInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IProtocolInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IProtocolInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IProtocolInfo_GetVersion(This,inputMsg,out_version)	\
    ( (This)->lpVtbl -> GetVersion(This,inputMsg,out_version) ) 

#define IProtocolInfo_ToBase64(This,data,len,out_data64)	\
    ( (This)->lpVtbl -> ToBase64(This,data,len,out_data64) ) 

#define IProtocolInfo_FileToBase64(This,path,out_data64)	\
    ( (This)->lpVtbl -> FileToBase64(This,path,out_data64) ) 

#define IProtocolInfo_EncodeAndBase64(This,encName,text,out_data64)	\
    ( (This)->lpVtbl -> EncodeAndBase64(This,encName,text,out_data64) ) 

#define IProtocolInfo_Base64ToFile(This,path,data64)	\
    ( (This)->lpVtbl -> Base64ToFile(This,path,data64) ) 

#define IProtocolInfo_GetFileStream(This,path,out_stream)	\
    ( (This)->lpVtbl -> GetFileStream(This,path,out_stream) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProtocolInfo_INTERFACE_DEFINED__ */



#ifndef __ProtocolAppLib_LIBRARY_DEFINED__
#define __ProtocolAppLib_LIBRARY_DEFINED__

/* library ProtocolAppLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ProtocolAppLib;

EXTERN_C const CLSID CLSID_Protocol;

#ifdef __cplusplus

class DECLSPEC_UUID("44EE3937-4D91-4de0-B4DA-338BD8E333AA")
Protocol;
#endif

EXTERN_C const CLSID CLSID_ProtocolInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("9232CC92-CE6F-4e37-9CF7-703380D2B235")
ProtocolInfo;
#endif
#endif /* __ProtocolAppLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


