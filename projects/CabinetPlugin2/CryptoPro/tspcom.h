

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Oct 02 00:36:07 2012
 */
/* Compiler settings for .\tspcom.idl:
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


#ifndef __tspcom_h__
#define __tspcom_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITSPRequest_FWD_DEFINED__
#define __ITSPRequest_FWD_DEFINED__
typedef interface ITSPRequest ITSPRequest;
#endif 	/* __ITSPRequest_FWD_DEFINED__ */


#ifndef __ITSPStamp_FWD_DEFINED__
#define __ITSPStamp_FWD_DEFINED__
typedef interface ITSPStamp ITSPStamp;
#endif 	/* __ITSPStamp_FWD_DEFINED__ */


#ifndef __ITSPRequest2_FWD_DEFINED__
#define __ITSPRequest2_FWD_DEFINED__
typedef interface ITSPRequest2 ITSPRequest2;
#endif 	/* __ITSPRequest2_FWD_DEFINED__ */


#ifndef __ITSPStamp2_FWD_DEFINED__
#define __ITSPStamp2_FWD_DEFINED__
typedef interface ITSPStamp2 ITSPStamp2;
#endif 	/* __ITSPStamp2_FWD_DEFINED__ */


#ifndef __TSPRequest_FWD_DEFINED__
#define __TSPRequest_FWD_DEFINED__

#ifdef __cplusplus
typedef class TSPRequest TSPRequest;
#else
typedef struct TSPRequest TSPRequest;
#endif /* __cplusplus */

#endif 	/* __TSPRequest_FWD_DEFINED__ */


#ifndef __TSPStamp_FWD_DEFINED__
#define __TSPStamp_FWD_DEFINED__

#ifdef __cplusplus
typedef class TSPStamp TSPStamp;
#else
typedef struct TSPStamp TSPStamp;
#endif /* __cplusplus */

#endif 	/* __TSPStamp_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_tspcom_0000_0000 */
/* [local] */ 

#include "capicom.h"




extern RPC_IF_HANDLE __MIDL_itf_tspcom_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_tspcom_0000_0000_v0_0_s_ifspec;


#ifndef __TSPCOM_LIBRARY_DEFINED__
#define __TSPCOM_LIBRARY_DEFINED__

/* library TSPCOM */
/* [helpstring][version][uuid] */ 

typedef /* [public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_tspcom_0000_0000_0001
    {	TSPCOM_AUTH_TYPE_ANONYMOUS	= 0,
	TSPCOM_AUTH_TYPE_BASIC	= 1,
	TSPCOM_AUTH_TYPE_DIGEST	= 2,
	TSPCOM_AUTH_TYPE_NTLM	= 3,
	TSPCOM_AUTH_TYPE_NEGOTIATE	= 4
    } 	TSPCOM_AUTH_TYPE;


EXTERN_C const IID LIBID_TSPCOM;

#ifndef __ITSPRequest_INTERFACE_DEFINED__
#define __ITSPRequest_INTERFACE_DEFINED__

/* interface ITSPRequest */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITSPRequest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D493E84E-4055-4691-AE63-8B6309AAB3AB")
    ITSPRequest : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Import( 
            /* [in] */ BSTR strRequest) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Export( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Send( 
            /* [defaultvalue][in] */ VARIANT_BOOL Verify,
            /* [retval][out] */ ITSPStamp **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Display( 
            /* [defaultvalue][in] */ LONG hwndParent = 0,
            /* [defaultvalue][in] */ BSTR Title = L"") = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TSAAddress( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TSAAddress( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertReq( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertReq( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UseNonce( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseNonce( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TSAPassword( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TSAPassword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PolicyID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PolicyID( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyAddress( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyAddress( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyPassword( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyPassword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyUserName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyUserName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TSAUserName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TSAUserName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Hash( 
            /* [in] */ /* external definition not present */ IHashedData *Hash) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClientCertificate( 
            /* [retval][out] */ /* external definition not present */ ICertContext **pVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_ClientCertificate( 
            /* [in] */ /* external definition not present */ ICertContext *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TSAAuthType( 
            /* [retval][out] */ TSPCOM_AUTH_TYPE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TSAAuthType( 
            /* [in] */ TSPCOM_AUTH_TYPE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyAuthType( 
            /* [retval][out] */ TSPCOM_AUTH_TYPE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyAuthType( 
            /* [in] */ TSPCOM_AUTH_TYPE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HashValue( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HashAlgorithm( 
            /* [retval][out] */ /* external definition not present */ IOID **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HTTPStatus( 
            /* [retval][out] */ LONG *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITSPRequestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITSPRequest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITSPRequest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITSPRequest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITSPRequest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITSPRequest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITSPRequest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITSPRequest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Import )( 
            ITSPRequest * This,
            /* [in] */ BSTR strRequest);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Export )( 
            ITSPRequest * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Send )( 
            ITSPRequest * This,
            /* [defaultvalue][in] */ VARIANT_BOOL Verify,
            /* [retval][out] */ ITSPStamp **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ITSPRequest * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSAAddress )( 
            ITSPRequest * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TSAAddress )( 
            ITSPRequest * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CertReq )( 
            ITSPRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CertReq )( 
            ITSPRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseNonce )( 
            ITSPRequest * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseNonce )( 
            ITSPRequest * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSAPassword )( 
            ITSPRequest * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TSAPassword )( 
            ITSPRequest * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PolicyID )( 
            ITSPRequest * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PolicyID )( 
            ITSPRequest * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProxyAddress )( 
            ITSPRequest * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProxyAddress )( 
            ITSPRequest * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProxyPassword )( 
            ITSPRequest * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProxyPassword )( 
            ITSPRequest * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProxyUserName )( 
            ITSPRequest * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProxyUserName )( 
            ITSPRequest * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSAUserName )( 
            ITSPRequest * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TSAUserName )( 
            ITSPRequest * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Hash )( 
            ITSPRequest * This,
            /* [in] */ /* external definition not present */ IHashedData *Hash);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientCertificate )( 
            ITSPRequest * This,
            /* [retval][out] */ /* external definition not present */ ICertContext **pVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ClientCertificate )( 
            ITSPRequest * This,
            /* [in] */ /* external definition not present */ ICertContext *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSAAuthType )( 
            ITSPRequest * This,
            /* [retval][out] */ TSPCOM_AUTH_TYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TSAAuthType )( 
            ITSPRequest * This,
            /* [in] */ TSPCOM_AUTH_TYPE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProxyAuthType )( 
            ITSPRequest * This,
            /* [retval][out] */ TSPCOM_AUTH_TYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProxyAuthType )( 
            ITSPRequest * This,
            /* [in] */ TSPCOM_AUTH_TYPE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HashValue )( 
            ITSPRequest * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HashAlgorithm )( 
            ITSPRequest * This,
            /* [retval][out] */ /* external definition not present */ IOID **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HTTPStatus )( 
            ITSPRequest * This,
            /* [retval][out] */ LONG *pVal);
        
        END_INTERFACE
    } ITSPRequestVtbl;

    interface ITSPRequest
    {
        CONST_VTBL struct ITSPRequestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITSPRequest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITSPRequest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITSPRequest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITSPRequest_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITSPRequest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITSPRequest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITSPRequest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITSPRequest_Import(This,strRequest)	\
    ( (This)->lpVtbl -> Import(This,strRequest) ) 

#define ITSPRequest_Export(This,pVal)	\
    ( (This)->lpVtbl -> Export(This,pVal) ) 

#define ITSPRequest_Send(This,Verify,pVal)	\
    ( (This)->lpVtbl -> Send(This,Verify,pVal) ) 

#define ITSPRequest_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 

#define ITSPRequest_get_TSAAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAAddress(This,pVal) ) 

#define ITSPRequest_put_TSAAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAAddress(This,newVal) ) 

#define ITSPRequest_get_CertReq(This,pVal)	\
    ( (This)->lpVtbl -> get_CertReq(This,pVal) ) 

#define ITSPRequest_put_CertReq(This,newVal)	\
    ( (This)->lpVtbl -> put_CertReq(This,newVal) ) 

#define ITSPRequest_get_UseNonce(This,pVal)	\
    ( (This)->lpVtbl -> get_UseNonce(This,pVal) ) 

#define ITSPRequest_put_UseNonce(This,newVal)	\
    ( (This)->lpVtbl -> put_UseNonce(This,newVal) ) 

#define ITSPRequest_get_TSAPassword(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAPassword(This,pVal) ) 

#define ITSPRequest_put_TSAPassword(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAPassword(This,newVal) ) 

#define ITSPRequest_get_PolicyID(This,pVal)	\
    ( (This)->lpVtbl -> get_PolicyID(This,pVal) ) 

#define ITSPRequest_put_PolicyID(This,newVal)	\
    ( (This)->lpVtbl -> put_PolicyID(This,newVal) ) 

#define ITSPRequest_get_ProxyAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_ProxyAddress(This,pVal) ) 

#define ITSPRequest_put_ProxyAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_ProxyAddress(This,newVal) ) 

#define ITSPRequest_get_ProxyPassword(This,pVal)	\
    ( (This)->lpVtbl -> get_ProxyPassword(This,pVal) ) 

#define ITSPRequest_put_ProxyPassword(This,newVal)	\
    ( (This)->lpVtbl -> put_ProxyPassword(This,newVal) ) 

#define ITSPRequest_get_ProxyUserName(This,pVal)	\
    ( (This)->lpVtbl -> get_ProxyUserName(This,pVal) ) 

#define ITSPRequest_put_ProxyUserName(This,newVal)	\
    ( (This)->lpVtbl -> put_ProxyUserName(This,newVal) ) 

#define ITSPRequest_get_TSAUserName(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAUserName(This,pVal) ) 

#define ITSPRequest_put_TSAUserName(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAUserName(This,newVal) ) 

#define ITSPRequest_putref_Hash(This,Hash)	\
    ( (This)->lpVtbl -> putref_Hash(This,Hash) ) 

#define ITSPRequest_get_ClientCertificate(This,pVal)	\
    ( (This)->lpVtbl -> get_ClientCertificate(This,pVal) ) 

#define ITSPRequest_putref_ClientCertificate(This,newVal)	\
    ( (This)->lpVtbl -> putref_ClientCertificate(This,newVal) ) 

#define ITSPRequest_get_TSAAuthType(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAAuthType(This,pVal) ) 

#define ITSPRequest_put_TSAAuthType(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAAuthType(This,newVal) ) 

#define ITSPRequest_get_ProxyAuthType(This,pVal)	\
    ( (This)->lpVtbl -> get_ProxyAuthType(This,pVal) ) 

#define ITSPRequest_put_ProxyAuthType(This,newVal)	\
    ( (This)->lpVtbl -> put_ProxyAuthType(This,newVal) ) 

#define ITSPRequest_get_HashValue(This,pVal)	\
    ( (This)->lpVtbl -> get_HashValue(This,pVal) ) 

#define ITSPRequest_get_HashAlgorithm(This,pVal)	\
    ( (This)->lpVtbl -> get_HashAlgorithm(This,pVal) ) 

#define ITSPRequest_get_HTTPStatus(This,pVal)	\
    ( (This)->lpVtbl -> get_HTTPStatus(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITSPRequest_INTERFACE_DEFINED__ */


#ifndef __ITSPStamp_INTERFACE_DEFINED__
#define __ITSPStamp_INTERFACE_DEFINED__

/* interface ITSPStamp */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITSPStamp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F59A43D1-B906-47E0-8AF7-55C726AEC81D")
    ITSPStamp : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Import( 
            /* [in] */ BSTR strStamp,
            /* [optional][in] */ VARIANT Request) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Export( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Compare( 
            /* [in] */ ITSPStamp *Stamp,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyStamp( 
            /* [in] */ /* external definition not present */ ICertContext *TSACertificate,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyCertificate( 
            /* [in] */ /* external definition not present */ ICertContext *TSACertificate,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TimePart( 
            BSTR Interval,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Display( 
            /* [defaultvalue][in] */ LONG hwndParent = 0,
            /* [defaultvalue][in] */ BSTR Title = L"") = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Certificates( 
            /* [retval][out] */ /* external definition not present */ ICertificates **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TSACertificate( 
            /* [optional][in] */ VARIANT Store,
            /* [retval][out] */ /* external definition not present */ ICertificate **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FailInfo( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatusString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PolicyID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SerialNumber( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ordering( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TSAName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Accuracy( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Time( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HashValue( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HashAlgorithm( 
            /* [retval][out] */ /* external definition not present */ IOID **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasNonce( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultAccuracy( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DefaultAccuracy( 
            /* [in] */ LONG newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITSPStampVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITSPStamp * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITSPStamp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITSPStamp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITSPStamp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITSPStamp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITSPStamp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITSPStamp * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Import )( 
            ITSPStamp * This,
            /* [in] */ BSTR strStamp,
            /* [optional][in] */ VARIANT Request);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Export )( 
            ITSPStamp * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Compare )( 
            ITSPStamp * This,
            /* [in] */ ITSPStamp *Stamp,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyStamp )( 
            ITSPStamp * This,
            /* [in] */ /* external definition not present */ ICertContext *TSACertificate,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyCertificate )( 
            ITSPStamp * This,
            /* [in] */ /* external definition not present */ ICertContext *TSACertificate,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TimePart )( 
            ITSPStamp * This,
            BSTR Interval,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ITSPStamp * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Certificates )( 
            ITSPStamp * This,
            /* [retval][out] */ /* external definition not present */ ICertificates **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSACertificate )( 
            ITSPStamp * This,
            /* [optional][in] */ VARIANT Store,
            /* [retval][out] */ /* external definition not present */ ICertificate **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FailInfo )( 
            ITSPStamp * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StatusString )( 
            ITSPStamp * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Status )( 
            ITSPStamp * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PolicyID )( 
            ITSPStamp * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SerialNumber )( 
            ITSPStamp * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ordering )( 
            ITSPStamp * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSAName )( 
            ITSPStamp * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Accuracy )( 
            ITSPStamp * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Time )( 
            ITSPStamp * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HashValue )( 
            ITSPStamp * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HashAlgorithm )( 
            ITSPStamp * This,
            /* [retval][out] */ /* external definition not present */ IOID **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasNonce )( 
            ITSPStamp * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultAccuracy )( 
            ITSPStamp * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultAccuracy )( 
            ITSPStamp * This,
            /* [in] */ LONG newVal);
        
        END_INTERFACE
    } ITSPStampVtbl;

    interface ITSPStamp
    {
        CONST_VTBL struct ITSPStampVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITSPStamp_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITSPStamp_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITSPStamp_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITSPStamp_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITSPStamp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITSPStamp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITSPStamp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITSPStamp_Import(This,strStamp,Request)	\
    ( (This)->lpVtbl -> Import(This,strStamp,Request) ) 

#define ITSPStamp_Export(This,pVal)	\
    ( (This)->lpVtbl -> Export(This,pVal) ) 

#define ITSPStamp_Compare(This,Stamp,pVal)	\
    ( (This)->lpVtbl -> Compare(This,Stamp,pVal) ) 

#define ITSPStamp_VerifyStamp(This,TSACertificate,pVal)	\
    ( (This)->lpVtbl -> VerifyStamp(This,TSACertificate,pVal) ) 

#define ITSPStamp_VerifyCertificate(This,TSACertificate,pVal)	\
    ( (This)->lpVtbl -> VerifyCertificate(This,TSACertificate,pVal) ) 

#define ITSPStamp_TimePart(This,Interval,pVal)	\
    ( (This)->lpVtbl -> TimePart(This,Interval,pVal) ) 

#define ITSPStamp_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 

#define ITSPStamp_get_Certificates(This,pVal)	\
    ( (This)->lpVtbl -> get_Certificates(This,pVal) ) 

#define ITSPStamp_get_TSACertificate(This,Store,pVal)	\
    ( (This)->lpVtbl -> get_TSACertificate(This,Store,pVal) ) 

#define ITSPStamp_get_FailInfo(This,pVal)	\
    ( (This)->lpVtbl -> get_FailInfo(This,pVal) ) 

#define ITSPStamp_get_StatusString(This,pVal)	\
    ( (This)->lpVtbl -> get_StatusString(This,pVal) ) 

#define ITSPStamp_get_Status(This,pVal)	\
    ( (This)->lpVtbl -> get_Status(This,pVal) ) 

#define ITSPStamp_get_PolicyID(This,pVal)	\
    ( (This)->lpVtbl -> get_PolicyID(This,pVal) ) 

#define ITSPStamp_get_SerialNumber(This,pVal)	\
    ( (This)->lpVtbl -> get_SerialNumber(This,pVal) ) 

#define ITSPStamp_get_Ordering(This,pVal)	\
    ( (This)->lpVtbl -> get_Ordering(This,pVal) ) 

#define ITSPStamp_get_TSAName(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAName(This,pVal) ) 

#define ITSPStamp_get_Accuracy(This,pVal)	\
    ( (This)->lpVtbl -> get_Accuracy(This,pVal) ) 

#define ITSPStamp_get_Time(This,pVal)	\
    ( (This)->lpVtbl -> get_Time(This,pVal) ) 

#define ITSPStamp_get_HashValue(This,pVal)	\
    ( (This)->lpVtbl -> get_HashValue(This,pVal) ) 

#define ITSPStamp_get_HashAlgorithm(This,pVal)	\
    ( (This)->lpVtbl -> get_HashAlgorithm(This,pVal) ) 

#define ITSPStamp_get_HasNonce(This,pVal)	\
    ( (This)->lpVtbl -> get_HasNonce(This,pVal) ) 

#define ITSPStamp_get_DefaultAccuracy(This,pVal)	\
    ( (This)->lpVtbl -> get_DefaultAccuracy(This,pVal) ) 

#define ITSPStamp_put_DefaultAccuracy(This,newVal)	\
    ( (This)->lpVtbl -> put_DefaultAccuracy(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITSPStamp_INTERFACE_DEFINED__ */


#ifndef __ITSPRequest2_INTERFACE_DEFINED__
#define __ITSPRequest2_INTERFACE_DEFINED__

/* interface ITSPRequest2 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITSPRequest2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DB3BE9AB-F041-48e0-9864-B088A471A4EB")
    ITSPRequest2 : public ITSPRequest
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Import2( 
            /* [in] */ SAFEARRAY * Request) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Export2( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddData( 
            /* [in] */ SAFEARRAY * Data) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetData( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClientCertificate2( 
            /* [retval][out] */ /* external definition not present */ ICertificate **pVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_ClientCertificate2( 
            /* [in] */ /* external definition not present */ ICertificate *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HashAlgorithm2( 
            /* [retval][out] */ /* external definition not present */ IOID **pVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_HashAlgorithm2( 
            /* [in] */ /* external definition not present */ IOID *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITSPRequest2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITSPRequest2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITSPRequest2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITSPRequest2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITSPRequest2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITSPRequest2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITSPRequest2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITSPRequest2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Import )( 
            ITSPRequest2 * This,
            /* [in] */ BSTR strRequest);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Export )( 
            ITSPRequest2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Send )( 
            ITSPRequest2 * This,
            /* [defaultvalue][in] */ VARIANT_BOOL Verify,
            /* [retval][out] */ ITSPStamp **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ITSPRequest2 * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSAAddress )( 
            ITSPRequest2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TSAAddress )( 
            ITSPRequest2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CertReq )( 
            ITSPRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CertReq )( 
            ITSPRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseNonce )( 
            ITSPRequest2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseNonce )( 
            ITSPRequest2 * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSAPassword )( 
            ITSPRequest2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TSAPassword )( 
            ITSPRequest2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PolicyID )( 
            ITSPRequest2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PolicyID )( 
            ITSPRequest2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProxyAddress )( 
            ITSPRequest2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProxyAddress )( 
            ITSPRequest2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProxyPassword )( 
            ITSPRequest2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProxyPassword )( 
            ITSPRequest2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProxyUserName )( 
            ITSPRequest2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProxyUserName )( 
            ITSPRequest2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSAUserName )( 
            ITSPRequest2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TSAUserName )( 
            ITSPRequest2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Hash )( 
            ITSPRequest2 * This,
            /* [in] */ /* external definition not present */ IHashedData *Hash);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientCertificate )( 
            ITSPRequest2 * This,
            /* [retval][out] */ /* external definition not present */ ICertContext **pVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ClientCertificate )( 
            ITSPRequest2 * This,
            /* [in] */ /* external definition not present */ ICertContext *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSAAuthType )( 
            ITSPRequest2 * This,
            /* [retval][out] */ TSPCOM_AUTH_TYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TSAAuthType )( 
            ITSPRequest2 * This,
            /* [in] */ TSPCOM_AUTH_TYPE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProxyAuthType )( 
            ITSPRequest2 * This,
            /* [retval][out] */ TSPCOM_AUTH_TYPE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProxyAuthType )( 
            ITSPRequest2 * This,
            /* [in] */ TSPCOM_AUTH_TYPE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HashValue )( 
            ITSPRequest2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HashAlgorithm )( 
            ITSPRequest2 * This,
            /* [retval][out] */ /* external definition not present */ IOID **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HTTPStatus )( 
            ITSPRequest2 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Import2 )( 
            ITSPRequest2 * This,
            /* [in] */ SAFEARRAY * Request);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Export2 )( 
            ITSPRequest2 * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddData )( 
            ITSPRequest2 * This,
            /* [in] */ SAFEARRAY * Data);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetData )( 
            ITSPRequest2 * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClientCertificate2 )( 
            ITSPRequest2 * This,
            /* [retval][out] */ /* external definition not present */ ICertificate **pVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ClientCertificate2 )( 
            ITSPRequest2 * This,
            /* [in] */ /* external definition not present */ ICertificate *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HashAlgorithm2 )( 
            ITSPRequest2 * This,
            /* [retval][out] */ /* external definition not present */ IOID **pVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_HashAlgorithm2 )( 
            ITSPRequest2 * This,
            /* [in] */ /* external definition not present */ IOID *pVal);
        
        END_INTERFACE
    } ITSPRequest2Vtbl;

    interface ITSPRequest2
    {
        CONST_VTBL struct ITSPRequest2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITSPRequest2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITSPRequest2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITSPRequest2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITSPRequest2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITSPRequest2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITSPRequest2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITSPRequest2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITSPRequest2_Import(This,strRequest)	\
    ( (This)->lpVtbl -> Import(This,strRequest) ) 

#define ITSPRequest2_Export(This,pVal)	\
    ( (This)->lpVtbl -> Export(This,pVal) ) 

#define ITSPRequest2_Send(This,Verify,pVal)	\
    ( (This)->lpVtbl -> Send(This,Verify,pVal) ) 

#define ITSPRequest2_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 

#define ITSPRequest2_get_TSAAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAAddress(This,pVal) ) 

#define ITSPRequest2_put_TSAAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAAddress(This,newVal) ) 

#define ITSPRequest2_get_CertReq(This,pVal)	\
    ( (This)->lpVtbl -> get_CertReq(This,pVal) ) 

#define ITSPRequest2_put_CertReq(This,newVal)	\
    ( (This)->lpVtbl -> put_CertReq(This,newVal) ) 

#define ITSPRequest2_get_UseNonce(This,pVal)	\
    ( (This)->lpVtbl -> get_UseNonce(This,pVal) ) 

#define ITSPRequest2_put_UseNonce(This,newVal)	\
    ( (This)->lpVtbl -> put_UseNonce(This,newVal) ) 

#define ITSPRequest2_get_TSAPassword(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAPassword(This,pVal) ) 

#define ITSPRequest2_put_TSAPassword(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAPassword(This,newVal) ) 

#define ITSPRequest2_get_PolicyID(This,pVal)	\
    ( (This)->lpVtbl -> get_PolicyID(This,pVal) ) 

#define ITSPRequest2_put_PolicyID(This,newVal)	\
    ( (This)->lpVtbl -> put_PolicyID(This,newVal) ) 

#define ITSPRequest2_get_ProxyAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_ProxyAddress(This,pVal) ) 

#define ITSPRequest2_put_ProxyAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_ProxyAddress(This,newVal) ) 

#define ITSPRequest2_get_ProxyPassword(This,pVal)	\
    ( (This)->lpVtbl -> get_ProxyPassword(This,pVal) ) 

#define ITSPRequest2_put_ProxyPassword(This,newVal)	\
    ( (This)->lpVtbl -> put_ProxyPassword(This,newVal) ) 

#define ITSPRequest2_get_ProxyUserName(This,pVal)	\
    ( (This)->lpVtbl -> get_ProxyUserName(This,pVal) ) 

#define ITSPRequest2_put_ProxyUserName(This,newVal)	\
    ( (This)->lpVtbl -> put_ProxyUserName(This,newVal) ) 

#define ITSPRequest2_get_TSAUserName(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAUserName(This,pVal) ) 

#define ITSPRequest2_put_TSAUserName(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAUserName(This,newVal) ) 

#define ITSPRequest2_putref_Hash(This,Hash)	\
    ( (This)->lpVtbl -> putref_Hash(This,Hash) ) 

#define ITSPRequest2_get_ClientCertificate(This,pVal)	\
    ( (This)->lpVtbl -> get_ClientCertificate(This,pVal) ) 

#define ITSPRequest2_putref_ClientCertificate(This,newVal)	\
    ( (This)->lpVtbl -> putref_ClientCertificate(This,newVal) ) 

#define ITSPRequest2_get_TSAAuthType(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAAuthType(This,pVal) ) 

#define ITSPRequest2_put_TSAAuthType(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAAuthType(This,newVal) ) 

#define ITSPRequest2_get_ProxyAuthType(This,pVal)	\
    ( (This)->lpVtbl -> get_ProxyAuthType(This,pVal) ) 

#define ITSPRequest2_put_ProxyAuthType(This,newVal)	\
    ( (This)->lpVtbl -> put_ProxyAuthType(This,newVal) ) 

#define ITSPRequest2_get_HashValue(This,pVal)	\
    ( (This)->lpVtbl -> get_HashValue(This,pVal) ) 

#define ITSPRequest2_get_HashAlgorithm(This,pVal)	\
    ( (This)->lpVtbl -> get_HashAlgorithm(This,pVal) ) 

#define ITSPRequest2_get_HTTPStatus(This,pVal)	\
    ( (This)->lpVtbl -> get_HTTPStatus(This,pVal) ) 


#define ITSPRequest2_Import2(This,Request)	\
    ( (This)->lpVtbl -> Import2(This,Request) ) 

#define ITSPRequest2_Export2(This,pVal)	\
    ( (This)->lpVtbl -> Export2(This,pVal) ) 

#define ITSPRequest2_AddData(This,Data)	\
    ( (This)->lpVtbl -> AddData(This,Data) ) 

#define ITSPRequest2_ResetData(This)	\
    ( (This)->lpVtbl -> ResetData(This) ) 

#define ITSPRequest2_get_ClientCertificate2(This,pVal)	\
    ( (This)->lpVtbl -> get_ClientCertificate2(This,pVal) ) 

#define ITSPRequest2_putref_ClientCertificate2(This,newVal)	\
    ( (This)->lpVtbl -> putref_ClientCertificate2(This,newVal) ) 

#define ITSPRequest2_get_HashAlgorithm2(This,pVal)	\
    ( (This)->lpVtbl -> get_HashAlgorithm2(This,pVal) ) 

#define ITSPRequest2_putref_HashAlgorithm2(This,pVal)	\
    ( (This)->lpVtbl -> putref_HashAlgorithm2(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITSPRequest2_INTERFACE_DEFINED__ */


#ifndef __ITSPStamp2_INTERFACE_DEFINED__
#define __ITSPStamp2_INTERFACE_DEFINED__

/* interface ITSPStamp2 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITSPStamp2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9AC30674-D6BC-4fd3-AD10-257B8C09550E")
    ITSPStamp2 : public ITSPStamp
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Import2( 
            /* [in] */ SAFEARRAY * Stamp,
            /* [optional][in] */ VARIANT Request) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Export2( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Verify( 
            /* [optional][in] */ VARIANT TSACertificate,
            /* [defaultvalue][in] */ BSTR AllowedCriticalExtensions,
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyCertificate2( 
            /* [optional][in] */ VARIANT TSACertificate,
            /* [optional][in] */ VARIANT Store,
            /* [retval][out] */ LONG *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITSPStamp2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITSPStamp2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITSPStamp2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITSPStamp2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITSPStamp2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITSPStamp2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITSPStamp2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITSPStamp2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Import )( 
            ITSPStamp2 * This,
            /* [in] */ BSTR strStamp,
            /* [optional][in] */ VARIANT Request);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Export )( 
            ITSPStamp2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Compare )( 
            ITSPStamp2 * This,
            /* [in] */ ITSPStamp *Stamp,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyStamp )( 
            ITSPStamp2 * This,
            /* [in] */ /* external definition not present */ ICertContext *TSACertificate,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyCertificate )( 
            ITSPStamp2 * This,
            /* [in] */ /* external definition not present */ ICertContext *TSACertificate,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TimePart )( 
            ITSPStamp2 * This,
            BSTR Interval,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ITSPStamp2 * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Certificates )( 
            ITSPStamp2 * This,
            /* [retval][out] */ /* external definition not present */ ICertificates **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSACertificate )( 
            ITSPStamp2 * This,
            /* [optional][in] */ VARIANT Store,
            /* [retval][out] */ /* external definition not present */ ICertificate **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FailInfo )( 
            ITSPStamp2 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StatusString )( 
            ITSPStamp2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Status )( 
            ITSPStamp2 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PolicyID )( 
            ITSPStamp2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SerialNumber )( 
            ITSPStamp2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ordering )( 
            ITSPStamp2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TSAName )( 
            ITSPStamp2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Accuracy )( 
            ITSPStamp2 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Time )( 
            ITSPStamp2 * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HashValue )( 
            ITSPStamp2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HashAlgorithm )( 
            ITSPStamp2 * This,
            /* [retval][out] */ /* external definition not present */ IOID **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasNonce )( 
            ITSPStamp2 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultAccuracy )( 
            ITSPStamp2 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultAccuracy )( 
            ITSPStamp2 * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Import2 )( 
            ITSPStamp2 * This,
            /* [in] */ SAFEARRAY * Stamp,
            /* [optional][in] */ VARIANT Request);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Export2 )( 
            ITSPStamp2 * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Verify )( 
            ITSPStamp2 * This,
            /* [optional][in] */ VARIANT TSACertificate,
            /* [defaultvalue][in] */ BSTR AllowedCriticalExtensions,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyCertificate2 )( 
            ITSPStamp2 * This,
            /* [optional][in] */ VARIANT TSACertificate,
            /* [optional][in] */ VARIANT Store,
            /* [retval][out] */ LONG *pVal);
        
        END_INTERFACE
    } ITSPStamp2Vtbl;

    interface ITSPStamp2
    {
        CONST_VTBL struct ITSPStamp2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITSPStamp2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITSPStamp2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITSPStamp2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITSPStamp2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITSPStamp2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITSPStamp2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITSPStamp2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITSPStamp2_Import(This,strStamp,Request)	\
    ( (This)->lpVtbl -> Import(This,strStamp,Request) ) 

#define ITSPStamp2_Export(This,pVal)	\
    ( (This)->lpVtbl -> Export(This,pVal) ) 

#define ITSPStamp2_Compare(This,Stamp,pVal)	\
    ( (This)->lpVtbl -> Compare(This,Stamp,pVal) ) 

#define ITSPStamp2_VerifyStamp(This,TSACertificate,pVal)	\
    ( (This)->lpVtbl -> VerifyStamp(This,TSACertificate,pVal) ) 

#define ITSPStamp2_VerifyCertificate(This,TSACertificate,pVal)	\
    ( (This)->lpVtbl -> VerifyCertificate(This,TSACertificate,pVal) ) 

#define ITSPStamp2_TimePart(This,Interval,pVal)	\
    ( (This)->lpVtbl -> TimePart(This,Interval,pVal) ) 

#define ITSPStamp2_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 

#define ITSPStamp2_get_Certificates(This,pVal)	\
    ( (This)->lpVtbl -> get_Certificates(This,pVal) ) 

#define ITSPStamp2_get_TSACertificate(This,Store,pVal)	\
    ( (This)->lpVtbl -> get_TSACertificate(This,Store,pVal) ) 

#define ITSPStamp2_get_FailInfo(This,pVal)	\
    ( (This)->lpVtbl -> get_FailInfo(This,pVal) ) 

#define ITSPStamp2_get_StatusString(This,pVal)	\
    ( (This)->lpVtbl -> get_StatusString(This,pVal) ) 

#define ITSPStamp2_get_Status(This,pVal)	\
    ( (This)->lpVtbl -> get_Status(This,pVal) ) 

#define ITSPStamp2_get_PolicyID(This,pVal)	\
    ( (This)->lpVtbl -> get_PolicyID(This,pVal) ) 

#define ITSPStamp2_get_SerialNumber(This,pVal)	\
    ( (This)->lpVtbl -> get_SerialNumber(This,pVal) ) 

#define ITSPStamp2_get_Ordering(This,pVal)	\
    ( (This)->lpVtbl -> get_Ordering(This,pVal) ) 

#define ITSPStamp2_get_TSAName(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAName(This,pVal) ) 

#define ITSPStamp2_get_Accuracy(This,pVal)	\
    ( (This)->lpVtbl -> get_Accuracy(This,pVal) ) 

#define ITSPStamp2_get_Time(This,pVal)	\
    ( (This)->lpVtbl -> get_Time(This,pVal) ) 

#define ITSPStamp2_get_HashValue(This,pVal)	\
    ( (This)->lpVtbl -> get_HashValue(This,pVal) ) 

#define ITSPStamp2_get_HashAlgorithm(This,pVal)	\
    ( (This)->lpVtbl -> get_HashAlgorithm(This,pVal) ) 

#define ITSPStamp2_get_HasNonce(This,pVal)	\
    ( (This)->lpVtbl -> get_HasNonce(This,pVal) ) 

#define ITSPStamp2_get_DefaultAccuracy(This,pVal)	\
    ( (This)->lpVtbl -> get_DefaultAccuracy(This,pVal) ) 

#define ITSPStamp2_put_DefaultAccuracy(This,newVal)	\
    ( (This)->lpVtbl -> put_DefaultAccuracy(This,newVal) ) 


#define ITSPStamp2_Import2(This,Stamp,Request)	\
    ( (This)->lpVtbl -> Import2(This,Stamp,Request) ) 

#define ITSPStamp2_Export2(This,pVal)	\
    ( (This)->lpVtbl -> Export2(This,pVal) ) 

#define ITSPStamp2_Verify(This,TSACertificate,AllowedCriticalExtensions,pVal)	\
    ( (This)->lpVtbl -> Verify(This,TSACertificate,AllowedCriticalExtensions,pVal) ) 

#define ITSPStamp2_VerifyCertificate2(This,TSACertificate,Store,pVal)	\
    ( (This)->lpVtbl -> VerifyCertificate2(This,TSACertificate,Store,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITSPStamp2_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TSPRequest;

#ifdef __cplusplus

class DECLSPEC_UUID("9519B122-E646-410C-9D6F-B228F81AEFE8")
TSPRequest;
#endif

EXTERN_C const CLSID CLSID_TSPStamp;

#ifdef __cplusplus

class DECLSPEC_UUID("CC4DA861-67F1-486A-B062-E27A1C36734B")
TSPStamp;
#endif
#endif /* __TSPCOM_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


