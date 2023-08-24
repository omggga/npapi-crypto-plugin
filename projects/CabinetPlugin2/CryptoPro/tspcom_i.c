

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_TSPCOM,0xAE4D769A,0xAFC6,0x4480,0x9C,0x4B,0x43,0x6A,0xF3,0x69,0x38,0xF4);


MIDL_DEFINE_GUID(IID, IID_ITSPRequest,0xD493E84E,0x4055,0x4691,0xAE,0x63,0x8B,0x63,0x09,0xAA,0xB3,0xAB);


MIDL_DEFINE_GUID(IID, IID_ITSPStamp,0xF59A43D1,0xB906,0x47E0,0x8A,0xF7,0x55,0xC7,0x26,0xAE,0xC8,0x1D);


MIDL_DEFINE_GUID(IID, IID_ITSPRequest2,0xDB3BE9AB,0xF041,0x48e0,0x98,0x64,0xB0,0x88,0xA4,0x71,0xA4,0xEB);


MIDL_DEFINE_GUID(IID, IID_ITSPStamp2,0x9AC30674,0xD6BC,0x4fd3,0xAD,0x10,0x25,0x7B,0x8C,0x09,0x55,0x0E);


MIDL_DEFINE_GUID(CLSID, CLSID_TSPRequest,0x9519B122,0xE646,0x410C,0x9D,0x6F,0xB2,0x28,0xF8,0x1A,0xEF,0xE8);


MIDL_DEFINE_GUID(CLSID, CLSID_TSPStamp,0xCC4DA861,0x67F1,0x486A,0xB0,0x62,0xE2,0x7A,0x1C,0x36,0x73,0x4B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



