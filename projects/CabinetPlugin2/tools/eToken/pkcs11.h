/* pkcs11.h include file for PKCS #11.  1997 December 22 */

#ifndef _PKCS11_H_
#define _PKCS11_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

/* Win 32 specific */
#ifdef _WIN32
#pragma pack(push, cryptoki, 1)

  #define CK_PTR *

  #define CK_DEFINE_FUNCTION(returnType, name) \
    returnType name
 
  #define CK_DECLARE_FUNCTION(returnType, name) \
    returnType name
 
  #define CK_DECLARE_FUNCTION_POINTER(returnType, name) \
    returnType (* name)

  #define CK_CALLBACK_FUNCTION(returnType, name) \
    returnType (* name)
#endif /* _WIN32 */

#ifndef NULL_PTR
#define NULL_PTR 0
#endif

/* All the various Cryptoki types and #define'd values are in the
 * file pkcs11t.h. */
#include "pkcs11t.h"

#define __PASTE(x,y)      x##y


/* ==============================================================
 * Define the "extern" form of all the entry points.
 * ==============================================================
 */

#define CK_NEED_ARG_LIST  1
#define CK_PKCS11_FUNCTION_INFO(name) \
  extern CK_DECLARE_FUNCTION(CK_RV, name)

/* pkcs11f.h has all the information about the Cryptoki
 * function prototypes. */
#include "pkcs11f.h"

#undef CK_NEED_ARG_LIST
#undef CK_PKCS11_FUNCTION_INFO


/* ==============================================================
 * Define the typedef form of all the entry points.  That is, for
 * each Cryptoki function C_XXX, define a type CK_C_XXX which is
 * a pointer to that kind of function.
 * ==============================================================
 */

#define CK_NEED_ARG_LIST  1
#define CK_PKCS11_FUNCTION_INFO(name) \
  typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, __PASTE(CK_,name))

/* pkcs11f.h has all the information about the Cryptoki
 * function prototypes. */
#include "pkcs11f.h"

#undef CK_NEED_ARG_LIST
#undef CK_PKCS11_FUNCTION_INFO


/* ==============================================================
 * Define structed vector of entry points.  A CK_FUNCTION_LIST
 * contains a CK_VERSION indicating a library's Cryptoki version
 * and then a whole slew of function pointers to the routines in
 * the library.  This type was declared, but not defined, in
 * pkcs11t.h.
 * ==============================================================
 */

#define CK_PKCS11_FUNCTION_INFO(name) \
  __PASTE(CK_,name) name;
  
struct CK_FUNCTION_LIST {

  CK_VERSION    version;  /* Cryptoki version */

/* Pile all the function pointers into the CK_FUNCTION_LIST. */
/* pkcs11f.h has all the information about the Cryptoki
 * function prototypes. */
#include "pkcs11f.h"

};

#undef CK_PKCS11_FUNCTION_INFO


#undef __PASTE

#ifdef __cplusplus
}
#endif

/* Win32 stuff */
#ifdef _WIN32
  #pragma pack(pop, cryptoki)
#endif /* _WIN32 */

#endif
