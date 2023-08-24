

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Sep 10 05:43:54 2017
 */
/* Compiler settings for cadescom.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
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


#ifndef __cadescom_h__
#define __cadescom_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICPCertificate_FWD_DEFINED__
#define __ICPCertificate_FWD_DEFINED__
typedef interface ICPCertificate ICPCertificate;

#endif 	/* __ICPCertificate_FWD_DEFINED__ */


#ifndef __ISymmetricAlgorithm_FWD_DEFINED__
#define __ISymmetricAlgorithm_FWD_DEFINED__
typedef interface ISymmetricAlgorithm ISymmetricAlgorithm;

#endif 	/* __ISymmetricAlgorithm_FWD_DEFINED__ */


#ifndef __ICPPrivateKey_FWD_DEFINED__
#define __ICPPrivateKey_FWD_DEFINED__
typedef interface ICPPrivateKey ICPPrivateKey;

#endif 	/* __ICPPrivateKey_FWD_DEFINED__ */


#ifndef __ICPSignedData_FWD_DEFINED__
#define __ICPSignedData_FWD_DEFINED__
typedef interface ICPSignedData ICPSignedData;

#endif 	/* __ICPSignedData_FWD_DEFINED__ */


#ifndef __ICPSignedData2_FWD_DEFINED__
#define __ICPSignedData2_FWD_DEFINED__
typedef interface ICPSignedData2 ICPSignedData2;

#endif 	/* __ICPSignedData2_FWD_DEFINED__ */


#ifndef __ICPSignedData3_FWD_DEFINED__
#define __ICPSignedData3_FWD_DEFINED__
typedef interface ICPSignedData3 ICPSignedData3;

#endif 	/* __ICPSignedData3_FWD_DEFINED__ */


#ifndef __ICPSignedData4_FWD_DEFINED__
#define __ICPSignedData4_FWD_DEFINED__
typedef interface ICPSignedData4 ICPSignedData4;

#endif 	/* __ICPSignedData4_FWD_DEFINED__ */


#ifndef __ICPSignedData5_FWD_DEFINED__
#define __ICPSignedData5_FWD_DEFINED__
typedef interface ICPSignedData5 ICPSignedData5;

#endif 	/* __ICPSignedData5_FWD_DEFINED__ */


#ifndef __ICPSigner_FWD_DEFINED__
#define __ICPSigner_FWD_DEFINED__
typedef interface ICPSigner ICPSigner;

#endif 	/* __ICPSigner_FWD_DEFINED__ */


#ifndef __ICPSigner2_FWD_DEFINED__
#define __ICPSigner2_FWD_DEFINED__
typedef interface ICPSigner2 ICPSigner2;

#endif 	/* __ICPSigner2_FWD_DEFINED__ */


#ifndef __ICPSigner3_FWD_DEFINED__
#define __ICPSigner3_FWD_DEFINED__
typedef interface ICPSigner3 ICPSigner3;

#endif 	/* __ICPSigner3_FWD_DEFINED__ */


#ifndef __ICPSigner4_FWD_DEFINED__
#define __ICPSigner4_FWD_DEFINED__
typedef interface ICPSigner4 ICPSigner4;

#endif 	/* __ICPSigner4_FWD_DEFINED__ */


#ifndef __ISignatureStatus_FWD_DEFINED__
#define __ISignatureStatus_FWD_DEFINED__
typedef interface ISignatureStatus ISignatureStatus;

#endif 	/* __ISignatureStatus_FWD_DEFINED__ */


#ifndef __ICPSigner5_FWD_DEFINED__
#define __ICPSigner5_FWD_DEFINED__
typedef interface ICPSigner5 ICPSigner5;

#endif 	/* __ICPSigner5_FWD_DEFINED__ */


#ifndef __ICPSigner6_FWD_DEFINED__
#define __ICPSigner6_FWD_DEFINED__
typedef interface ICPSigner6 ICPSigner6;

#endif 	/* __ICPSigner6_FWD_DEFINED__ */


#ifndef __ICPBlobs_FWD_DEFINED__
#define __ICPBlobs_FWD_DEFINED__
typedef interface ICPBlobs ICPBlobs;

#endif 	/* __ICPBlobs_FWD_DEFINED__ */


#ifndef __ICPAttribute_FWD_DEFINED__
#define __ICPAttribute_FWD_DEFINED__
typedef interface ICPAttribute ICPAttribute;

#endif 	/* __ICPAttribute_FWD_DEFINED__ */


#ifndef __ICPAttribute2_FWD_DEFINED__
#define __ICPAttribute2_FWD_DEFINED__
typedef interface ICPAttribute2 ICPAttribute2;

#endif 	/* __ICPAttribute2_FWD_DEFINED__ */


#ifndef __ICPAttributes_FWD_DEFINED__
#define __ICPAttributes_FWD_DEFINED__
typedef interface ICPAttributes ICPAttributes;

#endif 	/* __ICPAttributes_FWD_DEFINED__ */


#ifndef __ICPEnvelopedData_FWD_DEFINED__
#define __ICPEnvelopedData_FWD_DEFINED__
typedef interface ICPEnvelopedData ICPEnvelopedData;

#endif 	/* __ICPEnvelopedData_FWD_DEFINED__ */


#ifndef __ICPEnvelopedData2_FWD_DEFINED__
#define __ICPEnvelopedData2_FWD_DEFINED__
typedef interface ICPEnvelopedData2 ICPEnvelopedData2;

#endif 	/* __ICPEnvelopedData2_FWD_DEFINED__ */


#ifndef __ICPHashedData_FWD_DEFINED__
#define __ICPHashedData_FWD_DEFINED__
typedef interface ICPHashedData ICPHashedData;

#endif 	/* __ICPHashedData_FWD_DEFINED__ */


#ifndef __ISignedXML_FWD_DEFINED__
#define __ISignedXML_FWD_DEFINED__
typedef interface ISignedXML ISignedXML;

#endif 	/* __ISignedXML_FWD_DEFINED__ */


#ifndef __ICardholderData_FWD_DEFINED__
#define __ICardholderData_FWD_DEFINED__
typedef interface ICardholderData ICardholderData;

#endif 	/* __ICardholderData_FWD_DEFINED__ */


#ifndef __IIdentityCard_FWD_DEFINED__
#define __IIdentityCard_FWD_DEFINED__
typedef interface IIdentityCard IIdentityCard;

#endif 	/* __IIdentityCard_FWD_DEFINED__ */


#ifndef __IPersonalCardholderData_FWD_DEFINED__
#define __IPersonalCardholderData_FWD_DEFINED__
typedef interface IPersonalCardholderData IPersonalCardholderData;

#endif 	/* __IPersonalCardholderData_FWD_DEFINED__ */


#ifndef __IOMSData_FWD_DEFINED__
#define __IOMSData_FWD_DEFINED__
typedef interface IOMSData IOMSData;

#endif 	/* __IOMSData_FWD_DEFINED__ */


#ifndef __IUECard_FWD_DEFINED__
#define __IUECard_FWD_DEFINED__
typedef interface IUECard IUECard;

#endif 	/* __IUECard_FWD_DEFINED__ */


#ifndef __IUECard2_FWD_DEFINED__
#define __IUECard2_FWD_DEFINED__
typedef interface IUECard2 IUECard2;

#endif 	/* __IUECard2_FWD_DEFINED__ */


#ifndef __IUECard3_FWD_DEFINED__
#define __IUECard3_FWD_DEFINED__
typedef interface IUECard3 IUECard3;

#endif 	/* __IUECard3_FWD_DEFINED__ */


#ifndef __IEventSource_FWD_DEFINED__
#define __IEventSource_FWD_DEFINED__
typedef interface IEventSource IEventSource;

#endif 	/* __IEventSource_FWD_DEFINED__ */


#ifndef __ITrustedSites_FWD_DEFINED__
#define __ITrustedSites_FWD_DEFINED__
typedef interface ITrustedSites ITrustedSites;

#endif 	/* __ITrustedSites_FWD_DEFINED__ */


#ifndef __IPluginConfiguration_FWD_DEFINED__
#define __IPluginConfiguration_FWD_DEFINED__
typedef interface IPluginConfiguration IPluginConfiguration;

#endif 	/* __IPluginConfiguration_FWD_DEFINED__ */


#ifndef __TrustedSites_FWD_DEFINED__
#define __TrustedSites_FWD_DEFINED__

#ifdef __cplusplus
typedef class TrustedSites TrustedSites;
#else
typedef struct TrustedSites TrustedSites;
#endif /* __cplusplus */

#endif 	/* __TrustedSites_FWD_DEFINED__ */


#ifndef __PluginConfiguration_FWD_DEFINED__
#define __PluginConfiguration_FWD_DEFINED__

#ifdef __cplusplus
typedef class PluginConfiguration PluginConfiguration;
#else
typedef struct PluginConfiguration PluginConfiguration;
#endif /* __cplusplus */

#endif 	/* __PluginConfiguration_FWD_DEFINED__ */


#ifndef __IRawSignature_FWD_DEFINED__
#define __IRawSignature_FWD_DEFINED__
typedef interface IRawSignature IRawSignature;

#endif 	/* __IRawSignature_FWD_DEFINED__ */


#ifndef __IAbout_FWD_DEFINED__
#define __IAbout_FWD_DEFINED__
typedef interface IAbout IAbout;

#endif 	/* __IAbout_FWD_DEFINED__ */


#ifndef __IVersion_FWD_DEFINED__
#define __IVersion_FWD_DEFINED__
typedef interface IVersion IVersion;

#endif 	/* __IVersion_FWD_DEFINED__ */


#ifndef __IAbout2_FWD_DEFINED__
#define __IAbout2_FWD_DEFINED__
typedef interface IAbout2 IAbout2;

#endif 	/* __IAbout2_FWD_DEFINED__ */


#ifndef __IAbout3_FWD_DEFINED__
#define __IAbout3_FWD_DEFINED__
typedef interface IAbout3 IAbout3;

#endif 	/* __IAbout3_FWD_DEFINED__ */


#ifndef __IAbout4_FWD_DEFINED__
#define __IAbout4_FWD_DEFINED__
typedef interface IAbout4 IAbout4;

#endif 	/* __IAbout4_FWD_DEFINED__ */


#ifndef __IWebClassFactory_FWD_DEFINED__
#define __IWebClassFactory_FWD_DEFINED__
typedef interface IWebClassFactory IWebClassFactory;

#endif 	/* __IWebClassFactory_FWD_DEFINED__ */


#ifndef __IPrivateKeyUsageValidator_FWD_DEFINED__
#define __IPrivateKeyUsageValidator_FWD_DEFINED__
typedef interface IPrivateKeyUsageValidator IPrivateKeyUsageValidator;

#endif 	/* __IPrivateKeyUsageValidator_FWD_DEFINED__ */


#ifndef __CPAttribute_FWD_DEFINED__
#define __CPAttribute_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPAttribute CPAttribute;
#else
typedef struct CPAttribute CPAttribute;
#endif /* __cplusplus */

#endif 	/* __CPAttribute_FWD_DEFINED__ */


#ifndef __CPAttributes_FWD_DEFINED__
#define __CPAttributes_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPAttributes CPAttributes;
#else
typedef struct CPAttributes CPAttributes;
#endif /* __cplusplus */

#endif 	/* __CPAttributes_FWD_DEFINED__ */


#ifndef __CPSigner_FWD_DEFINED__
#define __CPSigner_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPSigner CPSigner;
#else
typedef struct CPSigner CPSigner;
#endif /* __cplusplus */

#endif 	/* __CPSigner_FWD_DEFINED__ */


#ifndef __CPSigners_FWD_DEFINED__
#define __CPSigners_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPSigners CPSigners;
#else
typedef struct CPSigners CPSigners;
#endif /* __cplusplus */

#endif 	/* __CPSigners_FWD_DEFINED__ */


#ifndef __CPBlobs_FWD_DEFINED__
#define __CPBlobs_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPBlobs CPBlobs;
#else
typedef struct CPBlobs CPBlobs;
#endif /* __cplusplus */

#endif 	/* __CPBlobs_FWD_DEFINED__ */


#ifndef __SignatureStatus_FWD_DEFINED__
#define __SignatureStatus_FWD_DEFINED__

#ifdef __cplusplus
typedef class SignatureStatus SignatureStatus;
#else
typedef struct SignatureStatus SignatureStatus;
#endif /* __cplusplus */

#endif 	/* __SignatureStatus_FWD_DEFINED__ */


#ifndef __About_FWD_DEFINED__
#define __About_FWD_DEFINED__

#ifdef __cplusplus
typedef class About About;
#else
typedef struct About About;
#endif /* __cplusplus */

#endif 	/* __About_FWD_DEFINED__ */


#ifndef __Version_FWD_DEFINED__
#define __Version_FWD_DEFINED__

#ifdef __cplusplus
typedef class Version Version;
#else
typedef struct Version Version;
#endif /* __cplusplus */

#endif 	/* __Version_FWD_DEFINED__ */


#ifndef __CadesSignedData_FWD_DEFINED__
#define __CadesSignedData_FWD_DEFINED__

#ifdef __cplusplus
typedef class CadesSignedData CadesSignedData;
#else
typedef struct CadesSignedData CadesSignedData;
#endif /* __cplusplus */

#endif 	/* __CadesSignedData_FWD_DEFINED__ */


#ifndef __SignedXML_FWD_DEFINED__
#define __SignedXML_FWD_DEFINED__

#ifdef __cplusplus
typedef class SignedXML SignedXML;
#else
typedef struct SignedXML SignedXML;
#endif /* __cplusplus */

#endif 	/* __SignedXML_FWD_DEFINED__ */


#ifndef __CPEnvelopedData_FWD_DEFINED__
#define __CPEnvelopedData_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPEnvelopedData CPEnvelopedData;
#else
typedef struct CPEnvelopedData CPEnvelopedData;
#endif /* __cplusplus */

#endif 	/* __CPEnvelopedData_FWD_DEFINED__ */


#ifndef __CPHashedData_FWD_DEFINED__
#define __CPHashedData_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPHashedData CPHashedData;
#else
typedef struct CPHashedData CPHashedData;
#endif /* __cplusplus */

#endif 	/* __CPHashedData_FWD_DEFINED__ */


#ifndef __RawSignature_FWD_DEFINED__
#define __RawSignature_FWD_DEFINED__

#ifdef __cplusplus
typedef class RawSignature RawSignature;
#else
typedef struct RawSignature RawSignature;
#endif /* __cplusplus */

#endif 	/* __RawSignature_FWD_DEFINED__ */


#ifndef __CPCertificate_FWD_DEFINED__
#define __CPCertificate_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPCertificate CPCertificate;
#else
typedef struct CPCertificate CPCertificate;
#endif /* __cplusplus */

#endif 	/* __CPCertificate_FWD_DEFINED__ */


#ifndef __SymmetricAlgorithm_FWD_DEFINED__
#define __SymmetricAlgorithm_FWD_DEFINED__

#ifdef __cplusplus
typedef class SymmetricAlgorithm SymmetricAlgorithm;
#else
typedef struct SymmetricAlgorithm SymmetricAlgorithm;
#endif /* __cplusplus */

#endif 	/* __SymmetricAlgorithm_FWD_DEFINED__ */


#ifndef __WebClassFactory_FWD_DEFINED__
#define __WebClassFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebClassFactory WebClassFactory;
#else
typedef struct WebClassFactory WebClassFactory;
#endif /* __cplusplus */

#endif 	/* __WebClassFactory_FWD_DEFINED__ */


#ifndef __PrivateKeyUsageValidator_FWD_DEFINED__
#define __PrivateKeyUsageValidator_FWD_DEFINED__

#ifdef __cplusplus
typedef class PrivateKeyUsageValidator PrivateKeyUsageValidator;
#else
typedef struct PrivateKeyUsageValidator PrivateKeyUsageValidator;
#endif /* __cplusplus */

#endif 	/* __PrivateKeyUsageValidator_FWD_DEFINED__ */


#ifndef __EnrollPolicyQualifier_FWD_DEFINED__
#define __EnrollPolicyQualifier_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollPolicyQualifier EnrollPolicyQualifier;
#else
typedef struct EnrollPolicyQualifier EnrollPolicyQualifier;
#endif /* __cplusplus */

#endif 	/* __EnrollPolicyQualifier_FWD_DEFINED__ */


#ifndef __EnrollPolicyQualifiers_FWD_DEFINED__
#define __EnrollPolicyQualifiers_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollPolicyQualifiers EnrollPolicyQualifiers;
#else
typedef struct EnrollPolicyQualifiers EnrollPolicyQualifiers;
#endif /* __cplusplus */

#endif 	/* __EnrollPolicyQualifiers_FWD_DEFINED__ */


#ifndef __EnrollCertificatePolicy_FWD_DEFINED__
#define __EnrollCertificatePolicy_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollCertificatePolicy EnrollCertificatePolicy;
#else
typedef struct EnrollCertificatePolicy EnrollCertificatePolicy;
#endif /* __cplusplus */

#endif 	/* __EnrollCertificatePolicy_FWD_DEFINED__ */


#ifndef __EnrollCertificatePolicies_FWD_DEFINED__
#define __EnrollCertificatePolicies_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollCertificatePolicies EnrollCertificatePolicies;
#else
typedef struct EnrollCertificatePolicies EnrollCertificatePolicies;
#endif /* __cplusplus */

#endif 	/* __EnrollCertificatePolicies_FWD_DEFINED__ */


#ifndef __EnrollX509ExtensionCertificatePolicies_FWD_DEFINED__
#define __EnrollX509ExtensionCertificatePolicies_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollX509ExtensionCertificatePolicies EnrollX509ExtensionCertificatePolicies;
#else
typedef struct EnrollX509ExtensionCertificatePolicies EnrollX509ExtensionCertificatePolicies;
#endif /* __cplusplus */

#endif 	/* __EnrollX509ExtensionCertificatePolicies_FWD_DEFINED__ */


#ifndef __CPPrivateKey_FWD_DEFINED__
#define __CPPrivateKey_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPPrivateKey CPPrivateKey;
#else
typedef struct CPPrivateKey CPPrivateKey;
#endif /* __cplusplus */

#endif 	/* __CPPrivateKey_FWD_DEFINED__ */


#ifndef __CPStore_FWD_DEFINED__
#define __CPStore_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPStore CPStore;
#else
typedef struct CPStore CPStore;
#endif /* __cplusplus */

#endif 	/* __CPStore_FWD_DEFINED__ */


#ifndef __EnrollObjectId_FWD_DEFINED__
#define __EnrollObjectId_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollObjectId EnrollObjectId;
#else
typedef struct EnrollObjectId EnrollObjectId;
#endif /* __cplusplus */

#endif 	/* __EnrollObjectId_FWD_DEFINED__ */


#ifndef __EnrollObjectIds_FWD_DEFINED__
#define __EnrollObjectIds_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollObjectIds EnrollObjectIds;
#else
typedef struct EnrollObjectIds EnrollObjectIds;
#endif /* __cplusplus */

#endif 	/* __EnrollObjectIds_FWD_DEFINED__ */


#ifndef __EnrollX500DistinguishedName_FWD_DEFINED__
#define __EnrollX500DistinguishedName_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollX500DistinguishedName EnrollX500DistinguishedName;
#else
typedef struct EnrollX500DistinguishedName EnrollX500DistinguishedName;
#endif /* __cplusplus */

#endif 	/* __EnrollX500DistinguishedName_FWD_DEFINED__ */


#ifndef __EnrollX509PrivateKey_FWD_DEFINED__
#define __EnrollX509PrivateKey_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollX509PrivateKey EnrollX509PrivateKey;
#else
typedef struct EnrollX509PrivateKey EnrollX509PrivateKey;
#endif /* __cplusplus */

#endif 	/* __EnrollX509PrivateKey_FWD_DEFINED__ */


#ifndef __EnrollX509Extension_FWD_DEFINED__
#define __EnrollX509Extension_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollX509Extension EnrollX509Extension;
#else
typedef struct EnrollX509Extension EnrollX509Extension;
#endif /* __cplusplus */

#endif 	/* __EnrollX509Extension_FWD_DEFINED__ */


#ifndef __EnrollX509Extensions_FWD_DEFINED__
#define __EnrollX509Extensions_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollX509Extensions EnrollX509Extensions;
#else
typedef struct EnrollX509Extensions EnrollX509Extensions;
#endif /* __cplusplus */

#endif 	/* __EnrollX509Extensions_FWD_DEFINED__ */


#ifndef __EnrollCspAlgorithm_FWD_DEFINED__
#define __EnrollCspAlgorithm_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollCspAlgorithm EnrollCspAlgorithm;
#else
typedef struct EnrollCspAlgorithm EnrollCspAlgorithm;
#endif /* __cplusplus */

#endif 	/* __EnrollCspAlgorithm_FWD_DEFINED__ */


#ifndef __EnrollCspAlgorithms_FWD_DEFINED__
#define __EnrollCspAlgorithms_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollCspAlgorithms EnrollCspAlgorithms;
#else
typedef struct EnrollCspAlgorithms EnrollCspAlgorithms;
#endif /* __cplusplus */

#endif 	/* __EnrollCspAlgorithms_FWD_DEFINED__ */


#ifndef __EnrollCspInformation_FWD_DEFINED__
#define __EnrollCspInformation_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollCspInformation EnrollCspInformation;
#else
typedef struct EnrollCspInformation EnrollCspInformation;
#endif /* __cplusplus */

#endif 	/* __EnrollCspInformation_FWD_DEFINED__ */


#ifndef __EnrollCspInformations_FWD_DEFINED__
#define __EnrollCspInformations_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollCspInformations EnrollCspInformations;
#else
typedef struct EnrollCspInformations EnrollCspInformations;
#endif /* __cplusplus */

#endif 	/* __EnrollCspInformations_FWD_DEFINED__ */


#ifndef __EnrollCspStatus_FWD_DEFINED__
#define __EnrollCspStatus_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollCspStatus EnrollCspStatus;
#else
typedef struct EnrollCspStatus EnrollCspStatus;
#endif /* __cplusplus */

#endif 	/* __EnrollCspStatus_FWD_DEFINED__ */


#ifndef __EnrollCspStatuses_FWD_DEFINED__
#define __EnrollCspStatuses_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollCspStatuses EnrollCspStatuses;
#else
typedef struct EnrollCspStatuses EnrollCspStatuses;
#endif /* __cplusplus */

#endif 	/* __EnrollCspStatuses_FWD_DEFINED__ */


#ifndef __EnrollX509CertificateRequestPkcs10_FWD_DEFINED__
#define __EnrollX509CertificateRequestPkcs10_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollX509CertificateRequestPkcs10 EnrollX509CertificateRequestPkcs10;
#else
typedef struct EnrollX509CertificateRequestPkcs10 EnrollX509CertificateRequestPkcs10;
#endif /* __cplusplus */

#endif 	/* __EnrollX509CertificateRequestPkcs10_FWD_DEFINED__ */


#ifndef __EnrollX509Enrollment_FWD_DEFINED__
#define __EnrollX509Enrollment_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollX509Enrollment EnrollX509Enrollment;
#else
typedef struct EnrollX509Enrollment EnrollX509Enrollment;
#endif /* __cplusplus */

#endif 	/* __EnrollX509Enrollment_FWD_DEFINED__ */


#ifndef __EnrollX509ExtensionKeyUsage_FWD_DEFINED__
#define __EnrollX509ExtensionKeyUsage_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollX509ExtensionKeyUsage EnrollX509ExtensionKeyUsage;
#else
typedef struct EnrollX509ExtensionKeyUsage EnrollX509ExtensionKeyUsage;
#endif /* __cplusplus */

#endif 	/* __EnrollX509ExtensionKeyUsage_FWD_DEFINED__ */


#ifndef __EnrollX509ExtensionEnhancedKeyUsage_FWD_DEFINED__
#define __EnrollX509ExtensionEnhancedKeyUsage_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollX509ExtensionEnhancedKeyUsage EnrollX509ExtensionEnhancedKeyUsage;
#else
typedef struct EnrollX509ExtensionEnhancedKeyUsage EnrollX509ExtensionEnhancedKeyUsage;
#endif /* __cplusplus */

#endif 	/* __EnrollX509ExtensionEnhancedKeyUsage_FWD_DEFINED__ */


#ifndef __EnrollX509ExtensionTemplate_FWD_DEFINED__
#define __EnrollX509ExtensionTemplate_FWD_DEFINED__

#ifdef __cplusplus
typedef class EnrollX509ExtensionTemplate EnrollX509ExtensionTemplate;
#else
typedef struct EnrollX509ExtensionTemplate EnrollX509ExtensionTemplate;
#endif /* __cplusplus */

#endif 	/* __EnrollX509ExtensionTemplate_FWD_DEFINED__ */


#ifndef __UECard_FWD_DEFINED__
#define __UECard_FWD_DEFINED__

#ifdef __cplusplus
typedef class UECard UECard;
#else
typedef struct UECard UECard;
#endif /* __cplusplus */

#endif 	/* __UECard_FWD_DEFINED__ */


#ifndef __CardholderData_FWD_DEFINED__
#define __CardholderData_FWD_DEFINED__

#ifdef __cplusplus
typedef class CardholderData CardholderData;
#else
typedef struct CardholderData CardholderData;
#endif /* __cplusplus */

#endif 	/* __CardholderData_FWD_DEFINED__ */


#ifndef __PersonalCardholderData_FWD_DEFINED__
#define __PersonalCardholderData_FWD_DEFINED__

#ifdef __cplusplus
typedef class PersonalCardholderData PersonalCardholderData;
#else
typedef struct PersonalCardholderData PersonalCardholderData;
#endif /* __cplusplus */

#endif 	/* __PersonalCardholderData_FWD_DEFINED__ */


#ifndef __IdentityCard_FWD_DEFINED__
#define __IdentityCard_FWD_DEFINED__

#ifdef __cplusplus
typedef class IdentityCard IdentityCard;
#else
typedef struct IdentityCard IdentityCard;
#endif /* __cplusplus */

#endif 	/* __IdentityCard_FWD_DEFINED__ */


#ifndef __OMSData_FWD_DEFINED__
#define __OMSData_FWD_DEFINED__

#ifdef __cplusplus
typedef class OMSData OMSData;
#else
typedef struct OMSData OMSData;
#endif /* __cplusplus */

#endif 	/* __OMSData_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_cadescom_0000_0000 */
/* [local] */ 

#include "capicom.h"
#include "certenroll.h"

















// √лупый MIDL не умеет генерить ссылки на enum'ы,
// определЄнные в другой библиотеке типов без алиаса,
// поэтому в cadescom.idl повторено определение используемых
// enum'ов CAPICOM. ¬ cadescom.h эти определени€
// не нужны, да к тому же ещЄ привод€т к ошибкам компил€ции,
// поэтому здесь они безусловно выкинуты из компил€ции.
#if 0
typedef /* [public][public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_cadescom_0000_0000_0001
    {
        CAPICOM_ENCODE_BASE64	= 0,
        CAPICOM_ENCODE_BINARY	= 1,
        CAPICOM_ENCODE_ANY	= 0xffffffff
    } 	CAPICOM_ENCODING_TYPE;

#endif //0


extern RPC_IF_HANDLE __MIDL_itf_cadescom_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_cadescom_0000_0000_v0_0_s_ifspec;


#ifndef __CAdESCOM_LIBRARY_DEFINED__
#define __CAdESCOM_LIBRARY_DEFINED__

/* library CAdESCOM */
/* [helpstring][version][uuid] */ 

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_cadescom_0000_0000_0002
    {
        CADESCOM_DISPLAY_DATA_NONE	= 0,
        CADESCOM_DISPLAY_DATA_CONTENT	= 0x1,
        CADESCOM_DISPLAY_DATA_ATTRIBUTE	= 0x2
    } 	CADESCOM_DISPLAY_DATA;

typedef /* [public][public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_cadescom_0000_0000_0003
    {
        CADESCOM_CADES_DEFAULT	= 0,
        CADESCOM_CADES_BES	= 0x1,
        CADESCOM_CADES_T	= 0x5,
        CADESCOM_CADES_X_LONG_TYPE_1	= 0x5d
    } 	CADESCOM_CADES_TYPE;

typedef /* [public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_cadescom_0000_0000_0004
    {
        CADESCOM_STRING_TO_UCS2LE	= 0,
        CADESCOM_BASE64_TO_BINARY	= 0x1
    } 	CADESCOM_CONTENT_ENCODING_TYPE;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_cadescom_0000_0000_0005
    {
        CADESCOM_XML_SIGNATURE_TYPE_ENVELOPED	= 0,
        CADESCOM_XML_SIGNATURE_TYPE_ENVELOPING	= 1,
        CADESCOM_XML_SIGNATURE_TYPE_TEMPLATE	= 2
    } 	CADESCOM_XML_SIGNATURE_TYPE;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_cadescom_0000_0000_0006
    {
        CADESCOM_AUTHENTICATED_ATTRIBUTE_SIGNING_TIME	= 0,
        CADESCOM_AUTHENTICATED_ATTRIBUTE_DOCUMENT_NAME	= 1,
        CADESCOM_AUTHENTICATED_ATTRIBUTE_DOCUMENT_DESCRIPTION	= 2,
        CADESCOM_ATTRIBUTE_OTHER	= 0xffffffff
    } 	CADESCOM_ATTRIBUTE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_cadescom_0000_0000_0007
    {
        CADESCOM_HASH_ALGORITHM_SHA1	= 0,
        CADESCOM_HASH_ALGORITHM_MD2	= 1,
        CADESCOM_HASH_ALGORITHM_MD4	= 2,
        CADESCOM_HASH_ALGORITHM_MD5	= 3,
        CADESCOM_HASH_ALGORITHM_SHA_256	= 4,
        CADESCOM_HASH_ALGORITHM_SHA_384	= 5,
        CADESCOM_HASH_ALGORITHM_SHA_512	= 6,
        CADESCOM_HASH_ALGORITHM_CP_GOST_3411	= 100,
        CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_256	= 101,
        CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_512	= 102
    } 	CADESCOM_HASH_ALGORITHM;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_cadescom_0000_0000_0008
    {
        CADESCOM_ENCRYPTION_ALGORITHM_RC2	= 0,
        CADESCOM_ENCRYPTION_ALGORITHM_RC4	= 1,
        CADESCOM_ENCRYPTION_ALGORITHM_DES	= 2,
        CADESCOM_ENCRYPTION_ALGORITHM_3DES	= 3,
        CADESCOM_ENCRYPTION_ALGORITHM_AES	= 4,
        CADESCOM_ENCRYPTION_ALGORITHM_GOST_28147_89	= 25
    } 	CADESCOM_ENCRYPTION_ALGORITHM;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_cadescom_0000_0000_0009
    {
        CADESCOM_MEMORY_STORE	= 0,
        CADESCOM_LOCAL_MACHINE_STORE	= 1,
        CADESCOM_CURRENT_USER_STORE	= 2,
        CADESCOM_ACTIVE_DIRECTORY_USER_STORE	= 3,
        CADESCOM_SMART_CARD_USER_STORE	= 4,
        CADESCOM_CONTAINER_STORE	= 100
    } 	CADESCOM_STORE_LOCATION;

typedef 
enum _CADESCOM_HUMAN_SEXES
    {
        CADESCOM_SEX_NOT_KNOWN	= 0,
        CADESCOM_SEX_MALE	= 1,
        CADESCOM_SEX_FEMALE	= 2,
        CADESCOM_SEX_NOT_APPLICABLE	= 9
    } 	CADESCOM_HUMAN_SEXES;


EXTERN_C const IID LIBID_CAdESCOM;

#ifndef __ICPCertificate_INTERFACE_DEFINED__
#define __ICPCertificate_INTERFACE_DEFINED__

/* interface ICPCertificate */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPCertificate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4552F41D-0C10-4C60-90FA-0D33709575CD")
    ICPCertificate : public ICertificate2
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindPrivateKey( 
            /* [optional][in] */ VARIANT varCriteria) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPCertificateVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPCertificate * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPCertificate * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPCertificate * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPCertificate * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPCertificate * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPCertificate * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPCertificate * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            ICPCertificate * This,
            /* [retval][out] */ signed long *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_SerialNumber )( 
            ICPCertificate * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_SubjectName )( 
            ICPCertificate * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_IssuerName )( 
            ICPCertificate * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_ValidFromDate )( 
            ICPCertificate * This,
            /* [retval][out] */ DATE *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_ValidToDate )( 
            ICPCertificate * This,
            /* [retval][out] */ DATE *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Thumbprint )( 
            ICPCertificate * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *HasPrivateKey )( 
            ICPCertificate * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetInfo )( 
            ICPCertificate * This,
            /* [in][idldescattr] */ CAPICOM_CERT_INFO_TYPE InfoType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *IsValid )( 
            ICPCertificate * This,
            /* [retval][out] */ ICertificateStatus **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *KeyUsage )( 
            ICPCertificate * This,
            /* [retval][out] */ IKeyUsage **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *ExtendedKeyUsage )( 
            ICPCertificate * This,
            /* [retval][out] */ IExtendedKeyUsage **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *BasicConstraints )( 
            ICPCertificate * This,
            /* [retval][out] */ IBasicConstraints **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Export )( 
            ICPCertificate * This,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Import )( 
            ICPCertificate * This,
            /* [in][idldescattr] */ BSTR EncodedCertificate,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ICPCertificate * This,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Archived )( 
            ICPCertificate * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Archived )( 
            ICPCertificate * This,
            /* [in][idldescattr] */ BOOLEAN noname,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Template )( 
            ICPCertificate * This,
            /* [retval][out] */ ITemplate **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *PublicKey )( 
            ICPCertificate * This,
            /* [retval][out] */ IPublicKey **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_PrivateKey )( 
            ICPCertificate * This,
            /* [retval][out] */ IPrivateKey **retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_PrivateKey )( 
            ICPCertificate * This,
            /* [in][idldescattr] */ IPrivateKey *noname,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Extensions )( 
            ICPCertificate * This,
            /* [retval][out] */ IExtensions **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *ExtendedProperties )( 
            ICPCertificate * This,
            /* [retval][out] */ IExtendedProperties **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            ICPCertificate * This,
            /* [in][idldescattr] */ BSTR FileName,
            /* [in][idldescattr] */ BSTR Password,
            /* [in][idldescattr] */ CAPICOM_KEY_STORAGE_FLAG KeyStorageFlag,
            /* [in][idldescattr] */ CAPICOM_KEY_LOCATION KeyLocation,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            ICPCertificate * This,
            /* [in][idldescattr] */ BSTR FileName,
            /* [in][idldescattr] */ BSTR Password,
            /* [in][idldescattr] */ CAPICOM_CERTIFICATE_SAVE_AS_TYPE SaveAs,
            /* [in][idldescattr] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION IncludeOption,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindPrivateKey )( 
            ICPCertificate * This,
            /* [optional][in] */ VARIANT varCriteria);
        
        END_INTERFACE
    } ICPCertificateVtbl;

    interface ICPCertificate
    {
        CONST_VTBL struct ICPCertificateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPCertificate_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPCertificate_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPCertificate_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPCertificate_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPCertificate_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPCertificate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPCertificate_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPCertificate_get_Version(This,retval)	\
    ( (This)->lpVtbl -> get_Version(This,retval) ) 

#define ICPCertificate_get_SerialNumber(This,retval)	\
    ( (This)->lpVtbl -> get_SerialNumber(This,retval) ) 

#define ICPCertificate_get_SubjectName(This,retval)	\
    ( (This)->lpVtbl -> get_SubjectName(This,retval) ) 

#define ICPCertificate_get_IssuerName(This,retval)	\
    ( (This)->lpVtbl -> get_IssuerName(This,retval) ) 

#define ICPCertificate_get_ValidFromDate(This,retval)	\
    ( (This)->lpVtbl -> get_ValidFromDate(This,retval) ) 

#define ICPCertificate_get_ValidToDate(This,retval)	\
    ( (This)->lpVtbl -> get_ValidToDate(This,retval) ) 

#define ICPCertificate_get_Thumbprint(This,retval)	\
    ( (This)->lpVtbl -> get_Thumbprint(This,retval) ) 

#define ICPCertificate_HasPrivateKey(This,retval)	\
    ( (This)->lpVtbl -> HasPrivateKey(This,retval) ) 

#define ICPCertificate_GetInfo(This,InfoType,retval)	\
    ( (This)->lpVtbl -> GetInfo(This,InfoType,retval) ) 

#define ICPCertificate_IsValid(This,retval)	\
    ( (This)->lpVtbl -> IsValid(This,retval) ) 

#define ICPCertificate_KeyUsage(This,retval)	\
    ( (This)->lpVtbl -> KeyUsage(This,retval) ) 

#define ICPCertificate_ExtendedKeyUsage(This,retval)	\
    ( (This)->lpVtbl -> ExtendedKeyUsage(This,retval) ) 

#define ICPCertificate_BasicConstraints(This,retval)	\
    ( (This)->lpVtbl -> BasicConstraints(This,retval) ) 

#define ICPCertificate_Export(This,EncodingType,retval)	\
    ( (This)->lpVtbl -> Export(This,EncodingType,retval) ) 

#define ICPCertificate_Import(This,EncodedCertificate,retval)	\
    ( (This)->lpVtbl -> Import(This,EncodedCertificate,retval) ) 

#define ICPCertificate_Display(This,retval)	\
    ( (This)->lpVtbl -> Display(This,retval) ) 

#define ICPCertificate_get_Archived(This,retval)	\
    ( (This)->lpVtbl -> get_Archived(This,retval) ) 

#define ICPCertificate_put_Archived(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Archived(This,noname,retval) ) 

#define ICPCertificate_Template(This,retval)	\
    ( (This)->lpVtbl -> Template(This,retval) ) 

#define ICPCertificate_PublicKey(This,retval)	\
    ( (This)->lpVtbl -> PublicKey(This,retval) ) 

#define ICPCertificate_get_PrivateKey(This,retval)	\
    ( (This)->lpVtbl -> get_PrivateKey(This,retval) ) 

#define ICPCertificate_put_PrivateKey(This,noname,retval)	\
    ( (This)->lpVtbl -> put_PrivateKey(This,noname,retval) ) 

#define ICPCertificate_Extensions(This,retval)	\
    ( (This)->lpVtbl -> Extensions(This,retval) ) 

#define ICPCertificate_ExtendedProperties(This,retval)	\
    ( (This)->lpVtbl -> ExtendedProperties(This,retval) ) 

#define ICPCertificate_Load(This,FileName,Password,KeyStorageFlag,KeyLocation,retval)	\
    ( (This)->lpVtbl -> Load(This,FileName,Password,KeyStorageFlag,KeyLocation,retval) ) 

#define ICPCertificate_Save(This,FileName,Password,SaveAs,IncludeOption,retval)	\
    ( (This)->lpVtbl -> Save(This,FileName,Password,SaveAs,IncludeOption,retval) ) 


#define ICPCertificate_FindPrivateKey(This,varCriteria)	\
    ( (This)->lpVtbl -> FindPrivateKey(This,varCriteria) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPCertificate_INTERFACE_DEFINED__ */


#ifndef __ISymmetricAlgorithm_INTERFACE_DEFINED__
#define __ISymmetricAlgorithm_INTERFACE_DEFINED__

/* interface ISymmetricAlgorithm */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISymmetricAlgorithm;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F3233D77-4286-4E9C-AE90-464CDECB551E")
    ISymmetricAlgorithm : public IDispatch
    {
    public:
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_IV( 
            /* [in] */ BSTR pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IV( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DiversData( 
            /* [in] */ BSTR pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DiversData( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateKey( 
            /* [defaultvalue][in] */ CADESCOM_ENCRYPTION_ALGORITHM algorithm = CADESCOM_ENCRYPTION_ALGORITHM_GOST_28147_89) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DiversifyKey( 
            /* [retval][out] */ ISymmetricAlgorithm **ppVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Encrypt( 
            /* [in] */ BSTR pbData,
            /* [in] */ VARIANT_BOOL isFinal,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Decrypt( 
            /* [in] */ BSTR pbData,
            /* [in] */ VARIANT_BOOL isFinal,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ImportKey( 
            /* [in] */ BSTR pbData,
            /* [in] */ /* external definition not present */ ICertificate *pVal,
            /* [defaultvalue][in] */ BSTR Password = L"") = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportKey( 
            /* [in] */ /* external definition not present */ ICertificate *pVal,
            /* [retval][out] */ BSTR *pbData) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISymmetricAlgorithmVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISymmetricAlgorithm * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISymmetricAlgorithm * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISymmetricAlgorithm * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISymmetricAlgorithm * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISymmetricAlgorithm * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISymmetricAlgorithm * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISymmetricAlgorithm * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_IV )( 
            ISymmetricAlgorithm * This,
            /* [in] */ BSTR pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IV )( 
            ISymmetricAlgorithm * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_DiversData )( 
            ISymmetricAlgorithm * This,
            /* [in] */ BSTR pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DiversData )( 
            ISymmetricAlgorithm * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GenerateKey )( 
            ISymmetricAlgorithm * This,
            /* [defaultvalue][in] */ CADESCOM_ENCRYPTION_ALGORITHM algorithm);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DiversifyKey )( 
            ISymmetricAlgorithm * This,
            /* [retval][out] */ ISymmetricAlgorithm **ppVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Encrypt )( 
            ISymmetricAlgorithm * This,
            /* [in] */ BSTR pbData,
            /* [in] */ VARIANT_BOOL isFinal,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Decrypt )( 
            ISymmetricAlgorithm * This,
            /* [in] */ BSTR pbData,
            /* [in] */ VARIANT_BOOL isFinal,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ImportKey )( 
            ISymmetricAlgorithm * This,
            /* [in] */ BSTR pbData,
            /* [in] */ /* external definition not present */ ICertificate *pVal,
            /* [defaultvalue][in] */ BSTR Password);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExportKey )( 
            ISymmetricAlgorithm * This,
            /* [in] */ /* external definition not present */ ICertificate *pVal,
            /* [retval][out] */ BSTR *pbData);
        
        END_INTERFACE
    } ISymmetricAlgorithmVtbl;

    interface ISymmetricAlgorithm
    {
        CONST_VTBL struct ISymmetricAlgorithmVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISymmetricAlgorithm_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISymmetricAlgorithm_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISymmetricAlgorithm_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISymmetricAlgorithm_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISymmetricAlgorithm_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISymmetricAlgorithm_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISymmetricAlgorithm_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISymmetricAlgorithm_put_IV(This,pVal)	\
    ( (This)->lpVtbl -> put_IV(This,pVal) ) 

#define ISymmetricAlgorithm_get_IV(This,pVal)	\
    ( (This)->lpVtbl -> get_IV(This,pVal) ) 

#define ISymmetricAlgorithm_put_DiversData(This,pVal)	\
    ( (This)->lpVtbl -> put_DiversData(This,pVal) ) 

#define ISymmetricAlgorithm_get_DiversData(This,pVal)	\
    ( (This)->lpVtbl -> get_DiversData(This,pVal) ) 

#define ISymmetricAlgorithm_GenerateKey(This,algorithm)	\
    ( (This)->lpVtbl -> GenerateKey(This,algorithm) ) 

#define ISymmetricAlgorithm_DiversifyKey(This,ppVal)	\
    ( (This)->lpVtbl -> DiversifyKey(This,ppVal) ) 

#define ISymmetricAlgorithm_Encrypt(This,pbData,isFinal,pVal)	\
    ( (This)->lpVtbl -> Encrypt(This,pbData,isFinal,pVal) ) 

#define ISymmetricAlgorithm_Decrypt(This,pbData,isFinal,pVal)	\
    ( (This)->lpVtbl -> Decrypt(This,pbData,isFinal,pVal) ) 

#define ISymmetricAlgorithm_ImportKey(This,pbData,pVal,Password)	\
    ( (This)->lpVtbl -> ImportKey(This,pbData,pVal,Password) ) 

#define ISymmetricAlgorithm_ExportKey(This,pVal,pbData)	\
    ( (This)->lpVtbl -> ExportKey(This,pVal,pbData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISymmetricAlgorithm_INTERFACE_DEFINED__ */


#ifndef __ICPPrivateKey_INTERFACE_DEFINED__
#define __ICPPrivateKey_INTERFACE_DEFINED__

/* interface ICPPrivateKey */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_ICPPrivateKey;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C12F1551-C631-4AFE-9BDE-4D0982B34E8C")
    ICPPrivateKey : public IPrivateKey
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_KeyPin( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_KeyPin( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CachePin( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_CachePin( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangePin( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPPrivateKeyVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPPrivateKey * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPPrivateKey * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPPrivateKey * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPPrivateKey * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPPrivateKey * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPPrivateKey * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPPrivateKey * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_ContainerName )( 
            ICPPrivateKey * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_UniqueContainerName )( 
            ICPPrivateKey * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_ProviderName )( 
            ICPPrivateKey * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_ProviderType )( 
            ICPPrivateKey * This,
            /* [retval][out] */ CAPICOM_PROV_TYPE *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_KeySpec )( 
            ICPPrivateKey * This,
            /* [retval][out] */ CAPICOM_KEY_SPEC *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *IsAccessible )( 
            ICPPrivateKey * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *IsProtected )( 
            ICPPrivateKey * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *IsExportable )( 
            ICPPrivateKey * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *IsRemovable )( 
            ICPPrivateKey * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *IsMachineKeyset )( 
            ICPPrivateKey * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *IsHardwareDevice )( 
            ICPPrivateKey * This,
            /* [retval][out] */ BOOLEAN *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            ICPPrivateKey * This,
            /* [in][idldescattr] */ BSTR ContainerName,
            /* [in][idldescattr] */ BSTR ProviderName,
            /* [in][idldescattr] */ CAPICOM_PROV_TYPE ProviderType,
            /* [in][idldescattr] */ CAPICOM_KEY_SPEC KeySpec,
            /* [in][idldescattr] */ CAPICOM_STORE_LOCATION StoreLocation,
            /* [in][idldescattr] */ BOOLEAN bCheckExistence,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Delete )( 
            ICPPrivateKey * This,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_KeyPin )( 
            ICPPrivateKey * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_KeyPin )( 
            ICPPrivateKey * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CachePin )( 
            ICPPrivateKey * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_CachePin )( 
            ICPPrivateKey * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangePin )( 
            ICPPrivateKey * This);
        
        END_INTERFACE
    } ICPPrivateKeyVtbl;

    interface ICPPrivateKey
    {
        CONST_VTBL struct ICPPrivateKeyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPPrivateKey_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPPrivateKey_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPPrivateKey_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPPrivateKey_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPPrivateKey_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPPrivateKey_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPPrivateKey_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPPrivateKey_get_ContainerName(This,retval)	\
    ( (This)->lpVtbl -> get_ContainerName(This,retval) ) 

#define ICPPrivateKey_get_UniqueContainerName(This,retval)	\
    ( (This)->lpVtbl -> get_UniqueContainerName(This,retval) ) 

#define ICPPrivateKey_get_ProviderName(This,retval)	\
    ( (This)->lpVtbl -> get_ProviderName(This,retval) ) 

#define ICPPrivateKey_get_ProviderType(This,retval)	\
    ( (This)->lpVtbl -> get_ProviderType(This,retval) ) 

#define ICPPrivateKey_get_KeySpec(This,retval)	\
    ( (This)->lpVtbl -> get_KeySpec(This,retval) ) 

#define ICPPrivateKey_IsAccessible(This,retval)	\
    ( (This)->lpVtbl -> IsAccessible(This,retval) ) 

#define ICPPrivateKey_IsProtected(This,retval)	\
    ( (This)->lpVtbl -> IsProtected(This,retval) ) 

#define ICPPrivateKey_IsExportable(This,retval)	\
    ( (This)->lpVtbl -> IsExportable(This,retval) ) 

#define ICPPrivateKey_IsRemovable(This,retval)	\
    ( (This)->lpVtbl -> IsRemovable(This,retval) ) 

#define ICPPrivateKey_IsMachineKeyset(This,retval)	\
    ( (This)->lpVtbl -> IsMachineKeyset(This,retval) ) 

#define ICPPrivateKey_IsHardwareDevice(This,retval)	\
    ( (This)->lpVtbl -> IsHardwareDevice(This,retval) ) 

#define ICPPrivateKey_Open(This,ContainerName,ProviderName,ProviderType,KeySpec,StoreLocation,bCheckExistence,retval)	\
    ( (This)->lpVtbl -> Open(This,ContainerName,ProviderName,ProviderType,KeySpec,StoreLocation,bCheckExistence,retval) ) 

#define ICPPrivateKey_Delete(This,retval)	\
    ( (This)->lpVtbl -> Delete(This,retval) ) 


#define ICPPrivateKey_get_KeyPin(This,pVal)	\
    ( (This)->lpVtbl -> get_KeyPin(This,pVal) ) 

#define ICPPrivateKey_put_KeyPin(This,newVal)	\
    ( (This)->lpVtbl -> put_KeyPin(This,newVal) ) 

#define ICPPrivateKey_get_CachePin(This,pVal)	\
    ( (This)->lpVtbl -> get_CachePin(This,pVal) ) 

#define ICPPrivateKey_put_CachePin(This,newVal)	\
    ( (This)->lpVtbl -> put_CachePin(This,newVal) ) 

#define ICPPrivateKey_ChangePin(This)	\
    ( (This)->lpVtbl -> ChangePin(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPPrivateKey_INTERFACE_DEFINED__ */


#ifndef __ICPSignedData_INTERFACE_DEFINED__
#define __ICPSignedData_INTERFACE_DEFINED__

/* interface ICPSignedData */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPSignedData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3CE3D3E5-0815-4CCE-BAA6-F058A0EFF643")
    ICPSignedData : public ISignedData
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Display( 
            /* [defaultvalue][in] */ LONG hwndParent = 0,
            /* [defaultvalue][in] */ BSTR Title = L"÷ифровые подписи") = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPSignedDataVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPSignedData * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPSignedData * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPSignedData * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPSignedData * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPSignedData * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPSignedData * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPSignedData * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Content )( 
            ICPSignedData * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Content )( 
            ICPSignedData * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Signers )( 
            ICPSignedData * This,
            /* [retval][out] */ ISigners **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Certificates )( 
            ICPSignedData * This,
            /* [retval][out] */ ICertificates **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Sign )( 
            ICPSignedData * This,
            /* [in][idldescattr] */ ISigner *pSigner,
            /* [in][idldescattr] */ BOOLEAN bDetached,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *CoSign )( 
            ICPSignedData * This,
            /* [in][idldescattr] */ ISigner *pSigner,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Verify )( 
            ICPSignedData * This,
            /* [in][idldescattr] */ BSTR SignedMessage,
            /* [in][idldescattr] */ BOOLEAN bDetached,
            /* [in][idldescattr] */ CAPICOM_SIGNED_DATA_VERIFY_FLAG VerifyFlag,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ICPSignedData * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        END_INTERFACE
    } ICPSignedDataVtbl;

    interface ICPSignedData
    {
        CONST_VTBL struct ICPSignedDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPSignedData_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPSignedData_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPSignedData_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPSignedData_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPSignedData_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPSignedData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPSignedData_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPSignedData_put_Content(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Content(This,noname,retval) ) 

#define ICPSignedData_get_Content(This,retval)	\
    ( (This)->lpVtbl -> get_Content(This,retval) ) 

#define ICPSignedData_get_Signers(This,retval)	\
    ( (This)->lpVtbl -> get_Signers(This,retval) ) 

#define ICPSignedData_get_Certificates(This,retval)	\
    ( (This)->lpVtbl -> get_Certificates(This,retval) ) 

#define ICPSignedData_Sign(This,pSigner,bDetached,EncodingType,retval)	\
    ( (This)->lpVtbl -> Sign(This,pSigner,bDetached,EncodingType,retval) ) 

#define ICPSignedData_CoSign(This,pSigner,EncodingType,retval)	\
    ( (This)->lpVtbl -> CoSign(This,pSigner,EncodingType,retval) ) 

#define ICPSignedData_Verify(This,SignedMessage,bDetached,VerifyFlag,retval)	\
    ( (This)->lpVtbl -> Verify(This,SignedMessage,bDetached,VerifyFlag,retval) ) 


#define ICPSignedData_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPSignedData_INTERFACE_DEFINED__ */


#ifndef __ICPSignedData2_INTERFACE_DEFINED__
#define __ICPSignedData2_INTERFACE_DEFINED__

/* interface ICPSignedData2 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPSignedData2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7CEE3429-9E4F-44F4-B640-BB902786C811")
    ICPSignedData2 : public ICPSignedData
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignCades( 
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ VARIANT_BOOL bDetached,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CoSignCades( 
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyCades( 
            /* [in] */ BSTR SignedMessage,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType = CADESCOM_CADES_DEFAULT,
            /* [defaultvalue][in] */ VARIANT_BOOL bDetached = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnhanceCades( 
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ BSTR TSAAddress,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPSignedData2Vtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPSignedData2 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPSignedData2 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPSignedData2 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPSignedData2 * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPSignedData2 * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPSignedData2 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPSignedData2 * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Content )( 
            ICPSignedData2 * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Content )( 
            ICPSignedData2 * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Signers )( 
            ICPSignedData2 * This,
            /* [retval][out] */ ISigners **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Certificates )( 
            ICPSignedData2 * This,
            /* [retval][out] */ ICertificates **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Sign )( 
            ICPSignedData2 * This,
            /* [in][idldescattr] */ ISigner *pSigner,
            /* [in][idldescattr] */ BOOLEAN bDetached,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *CoSign )( 
            ICPSignedData2 * This,
            /* [in][idldescattr] */ ISigner *pSigner,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Verify )( 
            ICPSignedData2 * This,
            /* [in][idldescattr] */ BSTR SignedMessage,
            /* [in][idldescattr] */ BOOLEAN bDetached,
            /* [in][idldescattr] */ CAPICOM_SIGNED_DATA_VERIFY_FLAG VerifyFlag,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ICPSignedData2 * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignCades )( 
            ICPSignedData2 * This,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ VARIANT_BOOL bDetached,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CoSignCades )( 
            ICPSignedData2 * This,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyCades )( 
            ICPSignedData2 * This,
            /* [in] */ BSTR SignedMessage,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ VARIANT_BOOL bDetached);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnhanceCades )( 
            ICPSignedData2 * This,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ BSTR TSAAddress,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } ICPSignedData2Vtbl;

    interface ICPSignedData2
    {
        CONST_VTBL struct ICPSignedData2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPSignedData2_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPSignedData2_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPSignedData2_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPSignedData2_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPSignedData2_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPSignedData2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPSignedData2_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPSignedData2_put_Content(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Content(This,noname,retval) ) 

#define ICPSignedData2_get_Content(This,retval)	\
    ( (This)->lpVtbl -> get_Content(This,retval) ) 

#define ICPSignedData2_get_Signers(This,retval)	\
    ( (This)->lpVtbl -> get_Signers(This,retval) ) 

#define ICPSignedData2_get_Certificates(This,retval)	\
    ( (This)->lpVtbl -> get_Certificates(This,retval) ) 

#define ICPSignedData2_Sign(This,pSigner,bDetached,EncodingType,retval)	\
    ( (This)->lpVtbl -> Sign(This,pSigner,bDetached,EncodingType,retval) ) 

#define ICPSignedData2_CoSign(This,pSigner,EncodingType,retval)	\
    ( (This)->lpVtbl -> CoSign(This,pSigner,EncodingType,retval) ) 

#define ICPSignedData2_Verify(This,SignedMessage,bDetached,VerifyFlag,retval)	\
    ( (This)->lpVtbl -> Verify(This,SignedMessage,bDetached,VerifyFlag,retval) ) 


#define ICPSignedData2_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 


#define ICPSignedData2_SignCades(This,Signer,CadesType,bDetached,EncodingType,pVal)	\
    ( (This)->lpVtbl -> SignCades(This,Signer,CadesType,bDetached,EncodingType,pVal) ) 

#define ICPSignedData2_CoSignCades(This,Signer,CadesType,EncodingType,pVal)	\
    ( (This)->lpVtbl -> CoSignCades(This,Signer,CadesType,EncodingType,pVal) ) 

#define ICPSignedData2_VerifyCades(This,SignedMessage,CadesType,bDetached)	\
    ( (This)->lpVtbl -> VerifyCades(This,SignedMessage,CadesType,bDetached) ) 

#define ICPSignedData2_EnhanceCades(This,CadesType,TSAAddress,EncodingType,pVal)	\
    ( (This)->lpVtbl -> EnhanceCades(This,CadesType,TSAAddress,EncodingType,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPSignedData2_INTERFACE_DEFINED__ */


#ifndef __ICPSignedData3_INTERFACE_DEFINED__
#define __ICPSignedData3_INTERFACE_DEFINED__

/* interface ICPSignedData3 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPSignedData3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("782964D8-94BF-4c1d-A6CF-FA9360E5C54F")
    ICPSignedData3 : public ICPSignedData2
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ContentEncoding( 
            /* [retval][out] */ CADESCOM_CONTENT_ENCODING_TYPE *pEncodingType) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ContentEncoding( 
            /* [in] */ CADESCOM_CONTENT_ENCODING_TYPE EncodingType) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPSignedData3Vtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPSignedData3 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPSignedData3 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPSignedData3 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPSignedData3 * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPSignedData3 * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPSignedData3 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPSignedData3 * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Content )( 
            ICPSignedData3 * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Content )( 
            ICPSignedData3 * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Signers )( 
            ICPSignedData3 * This,
            /* [retval][out] */ ISigners **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Certificates )( 
            ICPSignedData3 * This,
            /* [retval][out] */ ICertificates **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Sign )( 
            ICPSignedData3 * This,
            /* [in][idldescattr] */ ISigner *pSigner,
            /* [in][idldescattr] */ BOOLEAN bDetached,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *CoSign )( 
            ICPSignedData3 * This,
            /* [in][idldescattr] */ ISigner *pSigner,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Verify )( 
            ICPSignedData3 * This,
            /* [in][idldescattr] */ BSTR SignedMessage,
            /* [in][idldescattr] */ BOOLEAN bDetached,
            /* [in][idldescattr] */ CAPICOM_SIGNED_DATA_VERIFY_FLAG VerifyFlag,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ICPSignedData3 * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignCades )( 
            ICPSignedData3 * This,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ VARIANT_BOOL bDetached,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CoSignCades )( 
            ICPSignedData3 * This,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyCades )( 
            ICPSignedData3 * This,
            /* [in] */ BSTR SignedMessage,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ VARIANT_BOOL bDetached);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnhanceCades )( 
            ICPSignedData3 * This,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ BSTR TSAAddress,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ContentEncoding )( 
            ICPSignedData3 * This,
            /* [retval][out] */ CADESCOM_CONTENT_ENCODING_TYPE *pEncodingType);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ContentEncoding )( 
            ICPSignedData3 * This,
            /* [in] */ CADESCOM_CONTENT_ENCODING_TYPE EncodingType);
        
        END_INTERFACE
    } ICPSignedData3Vtbl;

    interface ICPSignedData3
    {
        CONST_VTBL struct ICPSignedData3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPSignedData3_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPSignedData3_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPSignedData3_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPSignedData3_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPSignedData3_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPSignedData3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPSignedData3_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPSignedData3_put_Content(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Content(This,noname,retval) ) 

#define ICPSignedData3_get_Content(This,retval)	\
    ( (This)->lpVtbl -> get_Content(This,retval) ) 

#define ICPSignedData3_get_Signers(This,retval)	\
    ( (This)->lpVtbl -> get_Signers(This,retval) ) 

#define ICPSignedData3_get_Certificates(This,retval)	\
    ( (This)->lpVtbl -> get_Certificates(This,retval) ) 

#define ICPSignedData3_Sign(This,pSigner,bDetached,EncodingType,retval)	\
    ( (This)->lpVtbl -> Sign(This,pSigner,bDetached,EncodingType,retval) ) 

#define ICPSignedData3_CoSign(This,pSigner,EncodingType,retval)	\
    ( (This)->lpVtbl -> CoSign(This,pSigner,EncodingType,retval) ) 

#define ICPSignedData3_Verify(This,SignedMessage,bDetached,VerifyFlag,retval)	\
    ( (This)->lpVtbl -> Verify(This,SignedMessage,bDetached,VerifyFlag,retval) ) 


#define ICPSignedData3_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 


#define ICPSignedData3_SignCades(This,Signer,CadesType,bDetached,EncodingType,pVal)	\
    ( (This)->lpVtbl -> SignCades(This,Signer,CadesType,bDetached,EncodingType,pVal) ) 

#define ICPSignedData3_CoSignCades(This,Signer,CadesType,EncodingType,pVal)	\
    ( (This)->lpVtbl -> CoSignCades(This,Signer,CadesType,EncodingType,pVal) ) 

#define ICPSignedData3_VerifyCades(This,SignedMessage,CadesType,bDetached)	\
    ( (This)->lpVtbl -> VerifyCades(This,SignedMessage,CadesType,bDetached) ) 

#define ICPSignedData3_EnhanceCades(This,CadesType,TSAAddress,EncodingType,pVal)	\
    ( (This)->lpVtbl -> EnhanceCades(This,CadesType,TSAAddress,EncodingType,pVal) ) 


#define ICPSignedData3_get_ContentEncoding(This,pEncodingType)	\
    ( (This)->lpVtbl -> get_ContentEncoding(This,pEncodingType) ) 

#define ICPSignedData3_put_ContentEncoding(This,EncodingType)	\
    ( (This)->lpVtbl -> put_ContentEncoding(This,EncodingType) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPSignedData3_INTERFACE_DEFINED__ */


#ifndef __ICPSignedData4_INTERFACE_DEFINED__
#define __ICPSignedData4_INTERFACE_DEFINED__

/* interface ICPSignedData4 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPSignedData4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("42A8CA34-7BF4-48eb-958A-20A6BD26BC42")
    ICPSignedData4 : public ICPSignedData3
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignHash( 
            /* [in] */ /* external definition not present */ IHashedData *Hash,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CoSignHash( 
            /* [in] */ /* external definition not present */ IHashedData *Hash,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyHash( 
            /* [in] */ VARIANT Hash,
            /* [in] */ BSTR SignedMessage,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType = CADESCOM_CADES_DEFAULT) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPSignedData4Vtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPSignedData4 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPSignedData4 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPSignedData4 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPSignedData4 * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPSignedData4 * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPSignedData4 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPSignedData4 * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Content )( 
            ICPSignedData4 * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Content )( 
            ICPSignedData4 * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Signers )( 
            ICPSignedData4 * This,
            /* [retval][out] */ ISigners **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Certificates )( 
            ICPSignedData4 * This,
            /* [retval][out] */ ICertificates **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Sign )( 
            ICPSignedData4 * This,
            /* [in][idldescattr] */ ISigner *pSigner,
            /* [in][idldescattr] */ BOOLEAN bDetached,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *CoSign )( 
            ICPSignedData4 * This,
            /* [in][idldescattr] */ ISigner *pSigner,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Verify )( 
            ICPSignedData4 * This,
            /* [in][idldescattr] */ BSTR SignedMessage,
            /* [in][idldescattr] */ BOOLEAN bDetached,
            /* [in][idldescattr] */ CAPICOM_SIGNED_DATA_VERIFY_FLAG VerifyFlag,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ICPSignedData4 * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignCades )( 
            ICPSignedData4 * This,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ VARIANT_BOOL bDetached,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CoSignCades )( 
            ICPSignedData4 * This,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyCades )( 
            ICPSignedData4 * This,
            /* [in] */ BSTR SignedMessage,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ VARIANT_BOOL bDetached);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnhanceCades )( 
            ICPSignedData4 * This,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ BSTR TSAAddress,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ContentEncoding )( 
            ICPSignedData4 * This,
            /* [retval][out] */ CADESCOM_CONTENT_ENCODING_TYPE *pEncodingType);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ContentEncoding )( 
            ICPSignedData4 * This,
            /* [in] */ CADESCOM_CONTENT_ENCODING_TYPE EncodingType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignHash )( 
            ICPSignedData4 * This,
            /* [in] */ /* external definition not present */ IHashedData *Hash,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CoSignHash )( 
            ICPSignedData4 * This,
            /* [in] */ /* external definition not present */ IHashedData *Hash,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyHash )( 
            ICPSignedData4 * This,
            /* [in] */ VARIANT Hash,
            /* [in] */ BSTR SignedMessage,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType);
        
        END_INTERFACE
    } ICPSignedData4Vtbl;

    interface ICPSignedData4
    {
        CONST_VTBL struct ICPSignedData4Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPSignedData4_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPSignedData4_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPSignedData4_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPSignedData4_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPSignedData4_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPSignedData4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPSignedData4_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPSignedData4_put_Content(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Content(This,noname,retval) ) 

#define ICPSignedData4_get_Content(This,retval)	\
    ( (This)->lpVtbl -> get_Content(This,retval) ) 

#define ICPSignedData4_get_Signers(This,retval)	\
    ( (This)->lpVtbl -> get_Signers(This,retval) ) 

#define ICPSignedData4_get_Certificates(This,retval)	\
    ( (This)->lpVtbl -> get_Certificates(This,retval) ) 

#define ICPSignedData4_Sign(This,pSigner,bDetached,EncodingType,retval)	\
    ( (This)->lpVtbl -> Sign(This,pSigner,bDetached,EncodingType,retval) ) 

#define ICPSignedData4_CoSign(This,pSigner,EncodingType,retval)	\
    ( (This)->lpVtbl -> CoSign(This,pSigner,EncodingType,retval) ) 

#define ICPSignedData4_Verify(This,SignedMessage,bDetached,VerifyFlag,retval)	\
    ( (This)->lpVtbl -> Verify(This,SignedMessage,bDetached,VerifyFlag,retval) ) 


#define ICPSignedData4_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 


#define ICPSignedData4_SignCades(This,Signer,CadesType,bDetached,EncodingType,pVal)	\
    ( (This)->lpVtbl -> SignCades(This,Signer,CadesType,bDetached,EncodingType,pVal) ) 

#define ICPSignedData4_CoSignCades(This,Signer,CadesType,EncodingType,pVal)	\
    ( (This)->lpVtbl -> CoSignCades(This,Signer,CadesType,EncodingType,pVal) ) 

#define ICPSignedData4_VerifyCades(This,SignedMessage,CadesType,bDetached)	\
    ( (This)->lpVtbl -> VerifyCades(This,SignedMessage,CadesType,bDetached) ) 

#define ICPSignedData4_EnhanceCades(This,CadesType,TSAAddress,EncodingType,pVal)	\
    ( (This)->lpVtbl -> EnhanceCades(This,CadesType,TSAAddress,EncodingType,pVal) ) 


#define ICPSignedData4_get_ContentEncoding(This,pEncodingType)	\
    ( (This)->lpVtbl -> get_ContentEncoding(This,pEncodingType) ) 

#define ICPSignedData4_put_ContentEncoding(This,EncodingType)	\
    ( (This)->lpVtbl -> put_ContentEncoding(This,EncodingType) ) 


#define ICPSignedData4_SignHash(This,Hash,Signer,CadesType,EncodingType,pVal)	\
    ( (This)->lpVtbl -> SignHash(This,Hash,Signer,CadesType,EncodingType,pVal) ) 

#define ICPSignedData4_CoSignHash(This,Hash,Signer,CadesType,EncodingType,pVal)	\
    ( (This)->lpVtbl -> CoSignHash(This,Hash,Signer,CadesType,EncodingType,pVal) ) 

#define ICPSignedData4_VerifyHash(This,Hash,SignedMessage,CadesType)	\
    ( (This)->lpVtbl -> VerifyHash(This,Hash,SignedMessage,CadesType) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPSignedData4_INTERFACE_DEFINED__ */


#ifndef __ICPSignedData5_INTERFACE_DEFINED__
#define __ICPSignedData5_INTERFACE_DEFINED__

/* interface ICPSignedData5 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPSignedData5;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("16801082-cb55-455b-8be1-8f25303edac9")
    ICPSignedData5 : public ICPSignedData4
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DisplayData( 
            /* [retval][out] */ CADESCOM_DISPLAY_DATA *pDisplayData) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DisplayData( 
            /* [in] */ CADESCOM_DISPLAY_DATA DisplayData) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPSignedData5Vtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPSignedData5 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPSignedData5 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPSignedData5 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPSignedData5 * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPSignedData5 * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPSignedData5 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPSignedData5 * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Content )( 
            ICPSignedData5 * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Content )( 
            ICPSignedData5 * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Signers )( 
            ICPSignedData5 * This,
            /* [retval][out] */ ISigners **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Certificates )( 
            ICPSignedData5 * This,
            /* [retval][out] */ ICertificates **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Sign )( 
            ICPSignedData5 * This,
            /* [in][idldescattr] */ ISigner *pSigner,
            /* [in][idldescattr] */ BOOLEAN bDetached,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *CoSign )( 
            ICPSignedData5 * This,
            /* [in][idldescattr] */ ISigner *pSigner,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Verify )( 
            ICPSignedData5 * This,
            /* [in][idldescattr] */ BSTR SignedMessage,
            /* [in][idldescattr] */ BOOLEAN bDetached,
            /* [in][idldescattr] */ CAPICOM_SIGNED_DATA_VERIFY_FLAG VerifyFlag,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ICPSignedData5 * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignCades )( 
            ICPSignedData5 * This,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ VARIANT_BOOL bDetached,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CoSignCades )( 
            ICPSignedData5 * This,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyCades )( 
            ICPSignedData5 * This,
            /* [in] */ BSTR SignedMessage,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ VARIANT_BOOL bDetached);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnhanceCades )( 
            ICPSignedData5 * This,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ BSTR TSAAddress,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ContentEncoding )( 
            ICPSignedData5 * This,
            /* [retval][out] */ CADESCOM_CONTENT_ENCODING_TYPE *pEncodingType);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ContentEncoding )( 
            ICPSignedData5 * This,
            /* [in] */ CADESCOM_CONTENT_ENCODING_TYPE EncodingType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignHash )( 
            ICPSignedData5 * This,
            /* [in] */ /* external definition not present */ IHashedData *Hash,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CoSignHash )( 
            ICPSignedData5 * This,
            /* [in] */ /* external definition not present */ IHashedData *Hash,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType,
            /* [defaultvalue][in] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyHash )( 
            ICPSignedData5 * This,
            /* [in] */ VARIANT Hash,
            /* [in] */ BSTR SignedMessage,
            /* [defaultvalue][in] */ CADESCOM_CADES_TYPE CadesType);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayData )( 
            ICPSignedData5 * This,
            /* [retval][out] */ CADESCOM_DISPLAY_DATA *pDisplayData);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_DisplayData )( 
            ICPSignedData5 * This,
            /* [in] */ CADESCOM_DISPLAY_DATA DisplayData);
        
        END_INTERFACE
    } ICPSignedData5Vtbl;

    interface ICPSignedData5
    {
        CONST_VTBL struct ICPSignedData5Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPSignedData5_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPSignedData5_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPSignedData5_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPSignedData5_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPSignedData5_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPSignedData5_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPSignedData5_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPSignedData5_put_Content(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Content(This,noname,retval) ) 

#define ICPSignedData5_get_Content(This,retval)	\
    ( (This)->lpVtbl -> get_Content(This,retval) ) 

#define ICPSignedData5_get_Signers(This,retval)	\
    ( (This)->lpVtbl -> get_Signers(This,retval) ) 

#define ICPSignedData5_get_Certificates(This,retval)	\
    ( (This)->lpVtbl -> get_Certificates(This,retval) ) 

#define ICPSignedData5_Sign(This,pSigner,bDetached,EncodingType,retval)	\
    ( (This)->lpVtbl -> Sign(This,pSigner,bDetached,EncodingType,retval) ) 

#define ICPSignedData5_CoSign(This,pSigner,EncodingType,retval)	\
    ( (This)->lpVtbl -> CoSign(This,pSigner,EncodingType,retval) ) 

#define ICPSignedData5_Verify(This,SignedMessage,bDetached,VerifyFlag,retval)	\
    ( (This)->lpVtbl -> Verify(This,SignedMessage,bDetached,VerifyFlag,retval) ) 


#define ICPSignedData5_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 


#define ICPSignedData5_SignCades(This,Signer,CadesType,bDetached,EncodingType,pVal)	\
    ( (This)->lpVtbl -> SignCades(This,Signer,CadesType,bDetached,EncodingType,pVal) ) 

#define ICPSignedData5_CoSignCades(This,Signer,CadesType,EncodingType,pVal)	\
    ( (This)->lpVtbl -> CoSignCades(This,Signer,CadesType,EncodingType,pVal) ) 

#define ICPSignedData5_VerifyCades(This,SignedMessage,CadesType,bDetached)	\
    ( (This)->lpVtbl -> VerifyCades(This,SignedMessage,CadesType,bDetached) ) 

#define ICPSignedData5_EnhanceCades(This,CadesType,TSAAddress,EncodingType,pVal)	\
    ( (This)->lpVtbl -> EnhanceCades(This,CadesType,TSAAddress,EncodingType,pVal) ) 


#define ICPSignedData5_get_ContentEncoding(This,pEncodingType)	\
    ( (This)->lpVtbl -> get_ContentEncoding(This,pEncodingType) ) 

#define ICPSignedData5_put_ContentEncoding(This,EncodingType)	\
    ( (This)->lpVtbl -> put_ContentEncoding(This,EncodingType) ) 


#define ICPSignedData5_SignHash(This,Hash,Signer,CadesType,EncodingType,pVal)	\
    ( (This)->lpVtbl -> SignHash(This,Hash,Signer,CadesType,EncodingType,pVal) ) 

#define ICPSignedData5_CoSignHash(This,Hash,Signer,CadesType,EncodingType,pVal)	\
    ( (This)->lpVtbl -> CoSignHash(This,Hash,Signer,CadesType,EncodingType,pVal) ) 

#define ICPSignedData5_VerifyHash(This,Hash,SignedMessage,CadesType)	\
    ( (This)->lpVtbl -> VerifyHash(This,Hash,SignedMessage,CadesType) ) 


#define ICPSignedData5_get_DisplayData(This,pDisplayData)	\
    ( (This)->lpVtbl -> get_DisplayData(This,pDisplayData) ) 

#define ICPSignedData5_put_DisplayData(This,DisplayData)	\
    ( (This)->lpVtbl -> put_DisplayData(This,DisplayData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPSignedData5_INTERFACE_DEFINED__ */


#ifndef __ICPSigner_INTERFACE_DEFINED__
#define __ICPSigner_INTERFACE_DEFINED__

/* interface ICPSigner */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPSigner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("771BEF1E-3857-4769-9B4B-0F04903230F4")
    ICPSigner : public ISigner2
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_UnauthenticatedAttributes( 
            /* [retval][out] */ ICPAttributes **ppVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_AuthenticatedAttributes2( 
            /* [retval][out] */ ICPAttributes **ppVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CRLs( 
            /* [retval][out] */ ICPBlobs **ppVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_OCSPResponses( 
            /* [retval][out] */ ICPBlobs **ppVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TSAAddress( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_TSAAddress( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPSignerVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPSigner * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPSigner * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPSigner * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPSigner * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPSigner * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPSigner * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPSigner * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Certificate )( 
            ICPSigner * This,
            /* [retval][out] */ ICertificate **retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Certificate )( 
            ICPSigner * This,
            /* [in][idldescattr] */ ICertificate *noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes )( 
            ICPSigner * This,
            /* [retval][out] */ IAttributes **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Chain )( 
            ICPSigner * This,
            /* [retval][out] */ IChain **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Options )( 
            ICPSigner * This,
            /* [retval][out] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Options )( 
            ICPSigner * This,
            /* [in][idldescattr] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION noname,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            ICPSigner * This,
            /* [in][idldescattr] */ BSTR FileName,
            /* [in][idldescattr] */ BSTR Password,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UnauthenticatedAttributes )( 
            ICPSigner * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes2 )( 
            ICPSigner * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CRLs )( 
            ICPSigner * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OCSPResponses )( 
            ICPSigner * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_TSAAddress )( 
            ICPSigner * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TSAAddress )( 
            ICPSigner * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ICPSignerVtbl;

    interface ICPSigner
    {
        CONST_VTBL struct ICPSignerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPSigner_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPSigner_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPSigner_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPSigner_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPSigner_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPSigner_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPSigner_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPSigner_get_Certificate(This,retval)	\
    ( (This)->lpVtbl -> get_Certificate(This,retval) ) 

#define ICPSigner_put_Certificate(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Certificate(This,noname,retval) ) 

#define ICPSigner_get_AuthenticatedAttributes(This,retval)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes(This,retval) ) 

#define ICPSigner_get_Chain(This,retval)	\
    ( (This)->lpVtbl -> get_Chain(This,retval) ) 

#define ICPSigner_get_Options(This,retval)	\
    ( (This)->lpVtbl -> get_Options(This,retval) ) 

#define ICPSigner_put_Options(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Options(This,noname,retval) ) 

#define ICPSigner_Load(This,FileName,Password,retval)	\
    ( (This)->lpVtbl -> Load(This,FileName,Password,retval) ) 


#define ICPSigner_get_UnauthenticatedAttributes(This,ppVal)	\
    ( (This)->lpVtbl -> get_UnauthenticatedAttributes(This,ppVal) ) 

#define ICPSigner_get_AuthenticatedAttributes2(This,ppVal)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes2(This,ppVal) ) 

#define ICPSigner_get_CRLs(This,ppVal)	\
    ( (This)->lpVtbl -> get_CRLs(This,ppVal) ) 

#define ICPSigner_get_OCSPResponses(This,ppVal)	\
    ( (This)->lpVtbl -> get_OCSPResponses(This,ppVal) ) 

#define ICPSigner_get_TSAAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAAddress(This,pVal) ) 

#define ICPSigner_put_TSAAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAAddress(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPSigner_INTERFACE_DEFINED__ */


#ifndef __ICPSigner2_INTERFACE_DEFINED__
#define __ICPSigner2_INTERFACE_DEFINED__

/* interface ICPSigner2 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPSigner2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF1E9D40-68D6-4b25-800D-6F8CBDF13392")
    ICPSigner2 : public ICPSigner
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Display( 
            /* [defaultvalue][in] */ LONG hwndParent = 0,
            /* [defaultvalue][in] */ BSTR Title = L"—остав цифровой подписи") = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPSigner2Vtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPSigner2 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPSigner2 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPSigner2 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPSigner2 * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPSigner2 * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPSigner2 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPSigner2 * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Certificate )( 
            ICPSigner2 * This,
            /* [retval][out] */ ICertificate **retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Certificate )( 
            ICPSigner2 * This,
            /* [in][idldescattr] */ ICertificate *noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes )( 
            ICPSigner2 * This,
            /* [retval][out] */ IAttributes **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Chain )( 
            ICPSigner2 * This,
            /* [retval][out] */ IChain **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Options )( 
            ICPSigner2 * This,
            /* [retval][out] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Options )( 
            ICPSigner2 * This,
            /* [in][idldescattr] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION noname,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            ICPSigner2 * This,
            /* [in][idldescattr] */ BSTR FileName,
            /* [in][idldescattr] */ BSTR Password,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UnauthenticatedAttributes )( 
            ICPSigner2 * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes2 )( 
            ICPSigner2 * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CRLs )( 
            ICPSigner2 * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OCSPResponses )( 
            ICPSigner2 * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_TSAAddress )( 
            ICPSigner2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TSAAddress )( 
            ICPSigner2 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ICPSigner2 * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        END_INTERFACE
    } ICPSigner2Vtbl;

    interface ICPSigner2
    {
        CONST_VTBL struct ICPSigner2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPSigner2_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPSigner2_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPSigner2_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPSigner2_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPSigner2_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPSigner2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPSigner2_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPSigner2_get_Certificate(This,retval)	\
    ( (This)->lpVtbl -> get_Certificate(This,retval) ) 

#define ICPSigner2_put_Certificate(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Certificate(This,noname,retval) ) 

#define ICPSigner2_get_AuthenticatedAttributes(This,retval)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes(This,retval) ) 

#define ICPSigner2_get_Chain(This,retval)	\
    ( (This)->lpVtbl -> get_Chain(This,retval) ) 

#define ICPSigner2_get_Options(This,retval)	\
    ( (This)->lpVtbl -> get_Options(This,retval) ) 

#define ICPSigner2_put_Options(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Options(This,noname,retval) ) 

#define ICPSigner2_Load(This,FileName,Password,retval)	\
    ( (This)->lpVtbl -> Load(This,FileName,Password,retval) ) 


#define ICPSigner2_get_UnauthenticatedAttributes(This,ppVal)	\
    ( (This)->lpVtbl -> get_UnauthenticatedAttributes(This,ppVal) ) 

#define ICPSigner2_get_AuthenticatedAttributes2(This,ppVal)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes2(This,ppVal) ) 

#define ICPSigner2_get_CRLs(This,ppVal)	\
    ( (This)->lpVtbl -> get_CRLs(This,ppVal) ) 

#define ICPSigner2_get_OCSPResponses(This,ppVal)	\
    ( (This)->lpVtbl -> get_OCSPResponses(This,ppVal) ) 

#define ICPSigner2_get_TSAAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAAddress(This,pVal) ) 

#define ICPSigner2_put_TSAAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAAddress(This,newVal) ) 


#define ICPSigner2_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPSigner2_INTERFACE_DEFINED__ */


#ifndef __ICPSigner3_INTERFACE_DEFINED__
#define __ICPSigner3_INTERFACE_DEFINED__

/* interface ICPSigner3 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPSigner3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0696D6A9-013A-4a64-8BA5-71727D0D1C4F")
    ICPSigner3 : public ICPSigner2
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SignatureTimeStampTime( 
            /* [retval][out] */ DATE *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SigningTime( 
            /* [retval][out] */ DATE *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPSigner3Vtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPSigner3 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPSigner3 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPSigner3 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPSigner3 * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPSigner3 * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPSigner3 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPSigner3 * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Certificate )( 
            ICPSigner3 * This,
            /* [retval][out] */ ICertificate **retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Certificate )( 
            ICPSigner3 * This,
            /* [in][idldescattr] */ ICertificate *noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes )( 
            ICPSigner3 * This,
            /* [retval][out] */ IAttributes **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Chain )( 
            ICPSigner3 * This,
            /* [retval][out] */ IChain **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Options )( 
            ICPSigner3 * This,
            /* [retval][out] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Options )( 
            ICPSigner3 * This,
            /* [in][idldescattr] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION noname,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            ICPSigner3 * This,
            /* [in][idldescattr] */ BSTR FileName,
            /* [in][idldescattr] */ BSTR Password,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UnauthenticatedAttributes )( 
            ICPSigner3 * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes2 )( 
            ICPSigner3 * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CRLs )( 
            ICPSigner3 * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OCSPResponses )( 
            ICPSigner3 * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_TSAAddress )( 
            ICPSigner3 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TSAAddress )( 
            ICPSigner3 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ICPSigner3 * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureTimeStampTime )( 
            ICPSigner3 * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SigningTime )( 
            ICPSigner3 * This,
            /* [retval][out] */ DATE *pVal);
        
        END_INTERFACE
    } ICPSigner3Vtbl;

    interface ICPSigner3
    {
        CONST_VTBL struct ICPSigner3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPSigner3_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPSigner3_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPSigner3_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPSigner3_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPSigner3_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPSigner3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPSigner3_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPSigner3_get_Certificate(This,retval)	\
    ( (This)->lpVtbl -> get_Certificate(This,retval) ) 

#define ICPSigner3_put_Certificate(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Certificate(This,noname,retval) ) 

#define ICPSigner3_get_AuthenticatedAttributes(This,retval)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes(This,retval) ) 

#define ICPSigner3_get_Chain(This,retval)	\
    ( (This)->lpVtbl -> get_Chain(This,retval) ) 

#define ICPSigner3_get_Options(This,retval)	\
    ( (This)->lpVtbl -> get_Options(This,retval) ) 

#define ICPSigner3_put_Options(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Options(This,noname,retval) ) 

#define ICPSigner3_Load(This,FileName,Password,retval)	\
    ( (This)->lpVtbl -> Load(This,FileName,Password,retval) ) 


#define ICPSigner3_get_UnauthenticatedAttributes(This,ppVal)	\
    ( (This)->lpVtbl -> get_UnauthenticatedAttributes(This,ppVal) ) 

#define ICPSigner3_get_AuthenticatedAttributes2(This,ppVal)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes2(This,ppVal) ) 

#define ICPSigner3_get_CRLs(This,ppVal)	\
    ( (This)->lpVtbl -> get_CRLs(This,ppVal) ) 

#define ICPSigner3_get_OCSPResponses(This,ppVal)	\
    ( (This)->lpVtbl -> get_OCSPResponses(This,ppVal) ) 

#define ICPSigner3_get_TSAAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAAddress(This,pVal) ) 

#define ICPSigner3_put_TSAAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAAddress(This,newVal) ) 


#define ICPSigner3_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 


#define ICPSigner3_get_SignatureTimeStampTime(This,pVal)	\
    ( (This)->lpVtbl -> get_SignatureTimeStampTime(This,pVal) ) 

#define ICPSigner3_get_SigningTime(This,pVal)	\
    ( (This)->lpVtbl -> get_SigningTime(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPSigner3_INTERFACE_DEFINED__ */


#ifndef __ICPSigner4_INTERFACE_DEFINED__
#define __ICPSigner4_INTERFACE_DEFINED__

/* interface ICPSigner4 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPSigner4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("893B73A2-FC0D-4781-87E5-CD93BF02AC19")
    ICPSigner4 : public ICPSigner3
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_KeyPin( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_KeyPin( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPSigner4Vtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPSigner4 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPSigner4 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPSigner4 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPSigner4 * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPSigner4 * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPSigner4 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPSigner4 * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Certificate )( 
            ICPSigner4 * This,
            /* [retval][out] */ ICertificate **retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Certificate )( 
            ICPSigner4 * This,
            /* [in][idldescattr] */ ICertificate *noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes )( 
            ICPSigner4 * This,
            /* [retval][out] */ IAttributes **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Chain )( 
            ICPSigner4 * This,
            /* [retval][out] */ IChain **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Options )( 
            ICPSigner4 * This,
            /* [retval][out] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Options )( 
            ICPSigner4 * This,
            /* [in][idldescattr] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION noname,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            ICPSigner4 * This,
            /* [in][idldescattr] */ BSTR FileName,
            /* [in][idldescattr] */ BSTR Password,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UnauthenticatedAttributes )( 
            ICPSigner4 * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes2 )( 
            ICPSigner4 * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CRLs )( 
            ICPSigner4 * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OCSPResponses )( 
            ICPSigner4 * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_TSAAddress )( 
            ICPSigner4 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TSAAddress )( 
            ICPSigner4 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ICPSigner4 * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureTimeStampTime )( 
            ICPSigner4 * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SigningTime )( 
            ICPSigner4 * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_KeyPin )( 
            ICPSigner4 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_KeyPin )( 
            ICPSigner4 * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ICPSigner4Vtbl;

    interface ICPSigner4
    {
        CONST_VTBL struct ICPSigner4Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPSigner4_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPSigner4_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPSigner4_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPSigner4_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPSigner4_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPSigner4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPSigner4_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPSigner4_get_Certificate(This,retval)	\
    ( (This)->lpVtbl -> get_Certificate(This,retval) ) 

#define ICPSigner4_put_Certificate(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Certificate(This,noname,retval) ) 

#define ICPSigner4_get_AuthenticatedAttributes(This,retval)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes(This,retval) ) 

#define ICPSigner4_get_Chain(This,retval)	\
    ( (This)->lpVtbl -> get_Chain(This,retval) ) 

#define ICPSigner4_get_Options(This,retval)	\
    ( (This)->lpVtbl -> get_Options(This,retval) ) 

#define ICPSigner4_put_Options(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Options(This,noname,retval) ) 

#define ICPSigner4_Load(This,FileName,Password,retval)	\
    ( (This)->lpVtbl -> Load(This,FileName,Password,retval) ) 


#define ICPSigner4_get_UnauthenticatedAttributes(This,ppVal)	\
    ( (This)->lpVtbl -> get_UnauthenticatedAttributes(This,ppVal) ) 

#define ICPSigner4_get_AuthenticatedAttributes2(This,ppVal)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes2(This,ppVal) ) 

#define ICPSigner4_get_CRLs(This,ppVal)	\
    ( (This)->lpVtbl -> get_CRLs(This,ppVal) ) 

#define ICPSigner4_get_OCSPResponses(This,ppVal)	\
    ( (This)->lpVtbl -> get_OCSPResponses(This,ppVal) ) 

#define ICPSigner4_get_TSAAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAAddress(This,pVal) ) 

#define ICPSigner4_put_TSAAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAAddress(This,newVal) ) 


#define ICPSigner4_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 


#define ICPSigner4_get_SignatureTimeStampTime(This,pVal)	\
    ( (This)->lpVtbl -> get_SignatureTimeStampTime(This,pVal) ) 

#define ICPSigner4_get_SigningTime(This,pVal)	\
    ( (This)->lpVtbl -> get_SigningTime(This,pVal) ) 


#define ICPSigner4_get_KeyPin(This,pVal)	\
    ( (This)->lpVtbl -> get_KeyPin(This,pVal) ) 

#define ICPSigner4_put_KeyPin(This,newVal)	\
    ( (This)->lpVtbl -> put_KeyPin(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPSigner4_INTERFACE_DEFINED__ */


#ifndef __ISignatureStatus_INTERFACE_DEFINED__
#define __ISignatureStatus_INTERFACE_DEFINED__

/* interface ISignatureStatus */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISignatureStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A0BB7DFF-8614-4196-B974-2DA895B4E0FE")
    ISignatureStatus : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsValid( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISignatureStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISignatureStatus * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISignatureStatus * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISignatureStatus * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISignatureStatus * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISignatureStatus * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISignatureStatus * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISignatureStatus * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IsValid )( 
            ISignatureStatus * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } ISignatureStatusVtbl;

    interface ISignatureStatus
    {
        CONST_VTBL struct ISignatureStatusVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISignatureStatus_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISignatureStatus_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISignatureStatus_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISignatureStatus_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISignatureStatus_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISignatureStatus_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISignatureStatus_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISignatureStatus_get_IsValid(This,pVal)	\
    ( (This)->lpVtbl -> get_IsValid(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISignatureStatus_INTERFACE_DEFINED__ */


#ifndef __ICPSigner5_INTERFACE_DEFINED__
#define __ICPSigner5_INTERFACE_DEFINED__

/* interface ICPSigner5 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPSigner5;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A23B42C3-2D57-4811-9968-674BEA1408F1")
    ICPSigner5 : public ICPSigner4
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SignatureStatus( 
            /* [retval][out] */ ISignatureStatus **ppVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPSigner5Vtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPSigner5 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPSigner5 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPSigner5 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPSigner5 * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPSigner5 * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPSigner5 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPSigner5 * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Certificate )( 
            ICPSigner5 * This,
            /* [retval][out] */ ICertificate **retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Certificate )( 
            ICPSigner5 * This,
            /* [in][idldescattr] */ ICertificate *noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes )( 
            ICPSigner5 * This,
            /* [retval][out] */ IAttributes **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Chain )( 
            ICPSigner5 * This,
            /* [retval][out] */ IChain **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Options )( 
            ICPSigner5 * This,
            /* [retval][out] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Options )( 
            ICPSigner5 * This,
            /* [in][idldescattr] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION noname,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            ICPSigner5 * This,
            /* [in][idldescattr] */ BSTR FileName,
            /* [in][idldescattr] */ BSTR Password,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UnauthenticatedAttributes )( 
            ICPSigner5 * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes2 )( 
            ICPSigner5 * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CRLs )( 
            ICPSigner5 * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OCSPResponses )( 
            ICPSigner5 * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_TSAAddress )( 
            ICPSigner5 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TSAAddress )( 
            ICPSigner5 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ICPSigner5 * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureTimeStampTime )( 
            ICPSigner5 * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SigningTime )( 
            ICPSigner5 * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_KeyPin )( 
            ICPSigner5 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_KeyPin )( 
            ICPSigner5 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureStatus )( 
            ICPSigner5 * This,
            /* [retval][out] */ ISignatureStatus **ppVal);
        
        END_INTERFACE
    } ICPSigner5Vtbl;

    interface ICPSigner5
    {
        CONST_VTBL struct ICPSigner5Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPSigner5_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPSigner5_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPSigner5_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPSigner5_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPSigner5_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPSigner5_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPSigner5_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPSigner5_get_Certificate(This,retval)	\
    ( (This)->lpVtbl -> get_Certificate(This,retval) ) 

#define ICPSigner5_put_Certificate(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Certificate(This,noname,retval) ) 

#define ICPSigner5_get_AuthenticatedAttributes(This,retval)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes(This,retval) ) 

#define ICPSigner5_get_Chain(This,retval)	\
    ( (This)->lpVtbl -> get_Chain(This,retval) ) 

#define ICPSigner5_get_Options(This,retval)	\
    ( (This)->lpVtbl -> get_Options(This,retval) ) 

#define ICPSigner5_put_Options(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Options(This,noname,retval) ) 

#define ICPSigner5_Load(This,FileName,Password,retval)	\
    ( (This)->lpVtbl -> Load(This,FileName,Password,retval) ) 


#define ICPSigner5_get_UnauthenticatedAttributes(This,ppVal)	\
    ( (This)->lpVtbl -> get_UnauthenticatedAttributes(This,ppVal) ) 

#define ICPSigner5_get_AuthenticatedAttributes2(This,ppVal)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes2(This,ppVal) ) 

#define ICPSigner5_get_CRLs(This,ppVal)	\
    ( (This)->lpVtbl -> get_CRLs(This,ppVal) ) 

#define ICPSigner5_get_OCSPResponses(This,ppVal)	\
    ( (This)->lpVtbl -> get_OCSPResponses(This,ppVal) ) 

#define ICPSigner5_get_TSAAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAAddress(This,pVal) ) 

#define ICPSigner5_put_TSAAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAAddress(This,newVal) ) 


#define ICPSigner5_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 


#define ICPSigner5_get_SignatureTimeStampTime(This,pVal)	\
    ( (This)->lpVtbl -> get_SignatureTimeStampTime(This,pVal) ) 

#define ICPSigner5_get_SigningTime(This,pVal)	\
    ( (This)->lpVtbl -> get_SigningTime(This,pVal) ) 


#define ICPSigner5_get_KeyPin(This,pVal)	\
    ( (This)->lpVtbl -> get_KeyPin(This,pVal) ) 

#define ICPSigner5_put_KeyPin(This,newVal)	\
    ( (This)->lpVtbl -> put_KeyPin(This,newVal) ) 


#define ICPSigner5_get_SignatureStatus(This,ppVal)	\
    ( (This)->lpVtbl -> get_SignatureStatus(This,ppVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPSigner5_INTERFACE_DEFINED__ */


#ifndef __ICPSigner6_INTERFACE_DEFINED__
#define __ICPSigner6_INTERFACE_DEFINED__

/* interface ICPSigner6 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPSigner6;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0FD68D28-1AAB-4AFE-B2C3-DC9CEF7B6BB4")
    ICPSigner6 : public ICPSigner5
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CheckCertificate( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_CheckCertificate( 
            /* [in] */ VARIANT_BOOL Val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPSigner6Vtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPSigner6 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPSigner6 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPSigner6 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPSigner6 * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPSigner6 * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPSigner6 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPSigner6 * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Certificate )( 
            ICPSigner6 * This,
            /* [retval][out] */ ICertificate **retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Certificate )( 
            ICPSigner6 * This,
            /* [in][idldescattr] */ ICertificate *noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes )( 
            ICPSigner6 * This,
            /* [retval][out] */ IAttributes **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Chain )( 
            ICPSigner6 * This,
            /* [retval][out] */ IChain **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Options )( 
            ICPSigner6 * This,
            /* [retval][out] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Options )( 
            ICPSigner6 * This,
            /* [in][idldescattr] */ CAPICOM_CERTIFICATE_INCLUDE_OPTION noname,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            ICPSigner6 * This,
            /* [in][idldescattr] */ BSTR FileName,
            /* [in][idldescattr] */ BSTR Password,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UnauthenticatedAttributes )( 
            ICPSigner6 * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AuthenticatedAttributes2 )( 
            ICPSigner6 * This,
            /* [retval][out] */ ICPAttributes **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CRLs )( 
            ICPSigner6 * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OCSPResponses )( 
            ICPSigner6 * This,
            /* [retval][out] */ ICPBlobs **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_TSAAddress )( 
            ICPSigner6 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TSAAddress )( 
            ICPSigner6 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Display )( 
            ICPSigner6 * This,
            /* [defaultvalue][in] */ LONG hwndParent,
            /* [defaultvalue][in] */ BSTR Title);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureTimeStampTime )( 
            ICPSigner6 * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SigningTime )( 
            ICPSigner6 * This,
            /* [retval][out] */ DATE *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_KeyPin )( 
            ICPSigner6 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_KeyPin )( 
            ICPSigner6 * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureStatus )( 
            ICPSigner6 * This,
            /* [retval][out] */ ISignatureStatus **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CheckCertificate )( 
            ICPSigner6 * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_CheckCertificate )( 
            ICPSigner6 * This,
            /* [in] */ VARIANT_BOOL Val);
        
        END_INTERFACE
    } ICPSigner6Vtbl;

    interface ICPSigner6
    {
        CONST_VTBL struct ICPSigner6Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPSigner6_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPSigner6_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPSigner6_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPSigner6_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPSigner6_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPSigner6_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPSigner6_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPSigner6_get_Certificate(This,retval)	\
    ( (This)->lpVtbl -> get_Certificate(This,retval) ) 

#define ICPSigner6_put_Certificate(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Certificate(This,noname,retval) ) 

#define ICPSigner6_get_AuthenticatedAttributes(This,retval)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes(This,retval) ) 

#define ICPSigner6_get_Chain(This,retval)	\
    ( (This)->lpVtbl -> get_Chain(This,retval) ) 

#define ICPSigner6_get_Options(This,retval)	\
    ( (This)->lpVtbl -> get_Options(This,retval) ) 

#define ICPSigner6_put_Options(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Options(This,noname,retval) ) 

#define ICPSigner6_Load(This,FileName,Password,retval)	\
    ( (This)->lpVtbl -> Load(This,FileName,Password,retval) ) 


#define ICPSigner6_get_UnauthenticatedAttributes(This,ppVal)	\
    ( (This)->lpVtbl -> get_UnauthenticatedAttributes(This,ppVal) ) 

#define ICPSigner6_get_AuthenticatedAttributes2(This,ppVal)	\
    ( (This)->lpVtbl -> get_AuthenticatedAttributes2(This,ppVal) ) 

#define ICPSigner6_get_CRLs(This,ppVal)	\
    ( (This)->lpVtbl -> get_CRLs(This,ppVal) ) 

#define ICPSigner6_get_OCSPResponses(This,ppVal)	\
    ( (This)->lpVtbl -> get_OCSPResponses(This,ppVal) ) 

#define ICPSigner6_get_TSAAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_TSAAddress(This,pVal) ) 

#define ICPSigner6_put_TSAAddress(This,newVal)	\
    ( (This)->lpVtbl -> put_TSAAddress(This,newVal) ) 


#define ICPSigner6_Display(This,hwndParent,Title)	\
    ( (This)->lpVtbl -> Display(This,hwndParent,Title) ) 


#define ICPSigner6_get_SignatureTimeStampTime(This,pVal)	\
    ( (This)->lpVtbl -> get_SignatureTimeStampTime(This,pVal) ) 

#define ICPSigner6_get_SigningTime(This,pVal)	\
    ( (This)->lpVtbl -> get_SigningTime(This,pVal) ) 


#define ICPSigner6_get_KeyPin(This,pVal)	\
    ( (This)->lpVtbl -> get_KeyPin(This,pVal) ) 

#define ICPSigner6_put_KeyPin(This,newVal)	\
    ( (This)->lpVtbl -> put_KeyPin(This,newVal) ) 


#define ICPSigner6_get_SignatureStatus(This,ppVal)	\
    ( (This)->lpVtbl -> get_SignatureStatus(This,ppVal) ) 


#define ICPSigner6_get_CheckCertificate(This,pVal)	\
    ( (This)->lpVtbl -> get_CheckCertificate(This,pVal) ) 

#define ICPSigner6_put_CheckCertificate(This,Val)	\
    ( (This)->lpVtbl -> put_CheckCertificate(This,Val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPSigner6_INTERFACE_DEFINED__ */


#ifndef __ICPBlobs_INTERFACE_DEFINED__
#define __ICPBlobs_INTERFACE_DEFINED__

/* interface ICPBlobs */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPBlobs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("546A657C-6133-459D-8C38-764189EC5A4B")
    ICPBlobs : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ VARIANT Blob) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            LONG Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG Index,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPBlobsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPBlobs * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICPBlobs * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICPBlobs * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPBlobs * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPBlobs * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPBlobs * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPBlobs * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ICPBlobs * This,
            /* [in] */ VARIANT Blob);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ICPBlobs * This,
            LONG Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ICPBlobs * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ICPBlobs * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ICPBlobs * This,
            /* [retval][out] */ IUnknown **ppVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ICPBlobs * This,
            /* [retval][out] */ LONG *pVal);
        
        END_INTERFACE
    } ICPBlobsVtbl;

    interface ICPBlobs
    {
        CONST_VTBL struct ICPBlobsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPBlobs_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICPBlobs_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICPBlobs_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICPBlobs_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICPBlobs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICPBlobs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICPBlobs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICPBlobs_Add(This,Blob)	\
    ( (This)->lpVtbl -> Add(This,Blob) ) 

#define ICPBlobs_Remove(This,Index)	\
    ( (This)->lpVtbl -> Remove(This,Index) ) 

#define ICPBlobs_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ICPBlobs_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define ICPBlobs_get__NewEnum(This,ppVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppVal) ) 

#define ICPBlobs_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPBlobs_INTERFACE_DEFINED__ */


#ifndef __ICPAttribute_INTERFACE_DEFINED__
#define __ICPAttribute_INTERFACE_DEFINED__

/* interface ICPAttribute */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPAttribute;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("23AAEFAE-DD8A-440F-9FCC-14160DDA700E")
    ICPAttribute : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_OID( 
            /* [retval][out] */ /* external definition not present */ IOID **ppVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPAttributeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPAttribute * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICPAttribute * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICPAttribute * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPAttribute * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPAttribute * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPAttribute * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPAttribute * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OID )( 
            ICPAttribute * This,
            /* [retval][out] */ /* external definition not present */ IOID **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            ICPAttribute * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            ICPAttribute * This,
            /* [in] */ VARIANT val);
        
        END_INTERFACE
    } ICPAttributeVtbl;

    interface ICPAttribute
    {
        CONST_VTBL struct ICPAttributeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPAttribute_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICPAttribute_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICPAttribute_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICPAttribute_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICPAttribute_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICPAttribute_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICPAttribute_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICPAttribute_get_OID(This,ppVal)	\
    ( (This)->lpVtbl -> get_OID(This,ppVal) ) 

#define ICPAttribute_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define ICPAttribute_put_Value(This,val)	\
    ( (This)->lpVtbl -> put_Value(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPAttribute_INTERFACE_DEFINED__ */


#ifndef __ICPAttribute2_INTERFACE_DEFINED__
#define __ICPAttribute2_INTERFACE_DEFINED__

/* interface ICPAttribute2 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPAttribute2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("597C704F-AA98-4e57-83AF-C22410F1D11E")
    ICPAttribute2 : public ICPAttribute
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ValueEncoding( 
            /* [retval][out] */ CAPICOM_ENCODING_TYPE *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ValueEncoding( 
            /* [in] */ CAPICOM_ENCODING_TYPE val) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ CADESCOM_ATTRIBUTE *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ CADESCOM_ATTRIBUTE val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPAttribute2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPAttribute2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICPAttribute2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICPAttribute2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPAttribute2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPAttribute2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPAttribute2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPAttribute2 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OID )( 
            ICPAttribute2 * This,
            /* [retval][out] */ /* external definition not present */ IOID **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            ICPAttribute2 * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Value )( 
            ICPAttribute2 * This,
            /* [in] */ VARIANT val);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ValueEncoding )( 
            ICPAttribute2 * This,
            /* [retval][out] */ CAPICOM_ENCODING_TYPE *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ValueEncoding )( 
            ICPAttribute2 * This,
            /* [in] */ CAPICOM_ENCODING_TYPE val);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ICPAttribute2 * This,
            /* [retval][out] */ CADESCOM_ATTRIBUTE *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ICPAttribute2 * This,
            /* [in] */ CADESCOM_ATTRIBUTE val);
        
        END_INTERFACE
    } ICPAttribute2Vtbl;

    interface ICPAttribute2
    {
        CONST_VTBL struct ICPAttribute2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPAttribute2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICPAttribute2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICPAttribute2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICPAttribute2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICPAttribute2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICPAttribute2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICPAttribute2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICPAttribute2_get_OID(This,ppVal)	\
    ( (This)->lpVtbl -> get_OID(This,ppVal) ) 

#define ICPAttribute2_get_Value(This,pVal)	\
    ( (This)->lpVtbl -> get_Value(This,pVal) ) 

#define ICPAttribute2_put_Value(This,val)	\
    ( (This)->lpVtbl -> put_Value(This,val) ) 


#define ICPAttribute2_get_ValueEncoding(This,pVal)	\
    ( (This)->lpVtbl -> get_ValueEncoding(This,pVal) ) 

#define ICPAttribute2_put_ValueEncoding(This,val)	\
    ( (This)->lpVtbl -> put_ValueEncoding(This,val) ) 

#define ICPAttribute2_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ICPAttribute2_put_Name(This,val)	\
    ( (This)->lpVtbl -> put_Name(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPAttribute2_INTERFACE_DEFINED__ */


#ifndef __ICPAttributes_INTERFACE_DEFINED__
#define __ICPAttributes_INTERFACE_DEFINED__

/* interface ICPAttributes */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPAttributes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6F624CCE-FEDD-49F8-BB1E-99100127E055")
    ICPAttributes : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ VARIANT Attribute) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            LONG Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG Index,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPAttributesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPAttributes * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICPAttributes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICPAttributes * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPAttributes * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPAttributes * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPAttributes * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPAttributes * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ICPAttributes * This,
            /* [in] */ VARIANT Attribute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ICPAttributes * This,
            LONG Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ICPAttributes * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ICPAttributes * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ICPAttributes * This,
            /* [retval][out] */ IUnknown **ppVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ICPAttributes * This,
            /* [retval][out] */ LONG *pVal);
        
        END_INTERFACE
    } ICPAttributesVtbl;

    interface ICPAttributes
    {
        CONST_VTBL struct ICPAttributesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPAttributes_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICPAttributes_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICPAttributes_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICPAttributes_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICPAttributes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICPAttributes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICPAttributes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICPAttributes_Add(This,Attribute)	\
    ( (This)->lpVtbl -> Add(This,Attribute) ) 

#define ICPAttributes_Remove(This,Index)	\
    ( (This)->lpVtbl -> Remove(This,Index) ) 

#define ICPAttributes_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ICPAttributes_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define ICPAttributes_get__NewEnum(This,ppVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppVal) ) 

#define ICPAttributes_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPAttributes_INTERFACE_DEFINED__ */


#ifndef __ICPEnvelopedData_INTERFACE_DEFINED__
#define __ICPEnvelopedData_INTERFACE_DEFINED__

/* interface ICPEnvelopedData */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_ICPEnvelopedData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6192C026-08C2-4ff1-ABAD-3B6072D7E9F0")
    ICPEnvelopedData : public IEnvelopedData
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ContentEncoding( 
            /* [retval][out] */ CADESCOM_CONTENT_ENCODING_TYPE *pEncodingType) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ContentEncoding( 
            /* [in] */ CADESCOM_CONTENT_ENCODING_TYPE EncodingType) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPEnvelopedDataVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPEnvelopedData * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPEnvelopedData * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPEnvelopedData * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPEnvelopedData * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPEnvelopedData * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPEnvelopedData * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPEnvelopedData * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Content )( 
            ICPEnvelopedData * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Content )( 
            ICPEnvelopedData * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Algorithm )( 
            ICPEnvelopedData * This,
            /* [retval][out] */ IAlgorithm **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Recipients )( 
            ICPEnvelopedData * This,
            /* [retval][out] */ IRecipients **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Encrypt )( 
            ICPEnvelopedData * This,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Decrypt )( 
            ICPEnvelopedData * This,
            /* [in][idldescattr] */ BSTR EnvelopedMessage,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ContentEncoding )( 
            ICPEnvelopedData * This,
            /* [retval][out] */ CADESCOM_CONTENT_ENCODING_TYPE *pEncodingType);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ContentEncoding )( 
            ICPEnvelopedData * This,
            /* [in] */ CADESCOM_CONTENT_ENCODING_TYPE EncodingType);
        
        END_INTERFACE
    } ICPEnvelopedDataVtbl;

    interface ICPEnvelopedData
    {
        CONST_VTBL struct ICPEnvelopedDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPEnvelopedData_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPEnvelopedData_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPEnvelopedData_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPEnvelopedData_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPEnvelopedData_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPEnvelopedData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPEnvelopedData_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPEnvelopedData_put_Content(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Content(This,noname,retval) ) 

#define ICPEnvelopedData_get_Content(This,retval)	\
    ( (This)->lpVtbl -> get_Content(This,retval) ) 

#define ICPEnvelopedData_get_Algorithm(This,retval)	\
    ( (This)->lpVtbl -> get_Algorithm(This,retval) ) 

#define ICPEnvelopedData_get_Recipients(This,retval)	\
    ( (This)->lpVtbl -> get_Recipients(This,retval) ) 

#define ICPEnvelopedData_Encrypt(This,EncodingType,retval)	\
    ( (This)->lpVtbl -> Encrypt(This,EncodingType,retval) ) 

#define ICPEnvelopedData_Decrypt(This,EnvelopedMessage,retval)	\
    ( (This)->lpVtbl -> Decrypt(This,EnvelopedMessage,retval) ) 


#define ICPEnvelopedData_get_ContentEncoding(This,pEncodingType)	\
    ( (This)->lpVtbl -> get_ContentEncoding(This,pEncodingType) ) 

#define ICPEnvelopedData_put_ContentEncoding(This,EncodingType)	\
    ( (This)->lpVtbl -> put_ContentEncoding(This,EncodingType) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPEnvelopedData_INTERFACE_DEFINED__ */


#ifndef __ICPEnvelopedData2_INTERFACE_DEFINED__
#define __ICPEnvelopedData2_INTERFACE_DEFINED__

/* interface ICPEnvelopedData2 */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_ICPEnvelopedData2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CD30EF83-0201-44C5-BB93-A4C2A6660D65")
    ICPEnvelopedData2 : public ICPEnvelopedData
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StreamEncrypt( 
            /* [in] */ BSTR pbData,
            /* [in] */ VARIANT_BOOL isFinal,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StreamDecrypt( 
            /* [in] */ BSTR pbData,
            /* [in] */ VARIANT_BOOL isFinal,
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPEnvelopedData2Vtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPEnvelopedData2 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPEnvelopedData2 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPEnvelopedData2 * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPEnvelopedData2 * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPEnvelopedData2 * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPEnvelopedData2 * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPEnvelopedData2 * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Content )( 
            ICPEnvelopedData2 * This,
            /* [in][idldescattr] */ BSTR noname,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Content )( 
            ICPEnvelopedData2 * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Algorithm )( 
            ICPEnvelopedData2 * This,
            /* [retval][out] */ IAlgorithm **retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Recipients )( 
            ICPEnvelopedData2 * This,
            /* [retval][out] */ IRecipients **retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Encrypt )( 
            ICPEnvelopedData2 * This,
            /* [in][idldescattr] */ CAPICOM_ENCODING_TYPE EncodingType,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Decrypt )( 
            ICPEnvelopedData2 * This,
            /* [in][idldescattr] */ BSTR EnvelopedMessage,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ContentEncoding )( 
            ICPEnvelopedData2 * This,
            /* [retval][out] */ CADESCOM_CONTENT_ENCODING_TYPE *pEncodingType);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ContentEncoding )( 
            ICPEnvelopedData2 * This,
            /* [in] */ CADESCOM_CONTENT_ENCODING_TYPE EncodingType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StreamEncrypt )( 
            ICPEnvelopedData2 * This,
            /* [in] */ BSTR pbData,
            /* [in] */ VARIANT_BOOL isFinal,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StreamDecrypt )( 
            ICPEnvelopedData2 * This,
            /* [in] */ BSTR pbData,
            /* [in] */ VARIANT_BOOL isFinal,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } ICPEnvelopedData2Vtbl;

    interface ICPEnvelopedData2
    {
        CONST_VTBL struct ICPEnvelopedData2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPEnvelopedData2_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPEnvelopedData2_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPEnvelopedData2_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPEnvelopedData2_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPEnvelopedData2_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPEnvelopedData2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPEnvelopedData2_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPEnvelopedData2_put_Content(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Content(This,noname,retval) ) 

#define ICPEnvelopedData2_get_Content(This,retval)	\
    ( (This)->lpVtbl -> get_Content(This,retval) ) 

#define ICPEnvelopedData2_get_Algorithm(This,retval)	\
    ( (This)->lpVtbl -> get_Algorithm(This,retval) ) 

#define ICPEnvelopedData2_get_Recipients(This,retval)	\
    ( (This)->lpVtbl -> get_Recipients(This,retval) ) 

#define ICPEnvelopedData2_Encrypt(This,EncodingType,retval)	\
    ( (This)->lpVtbl -> Encrypt(This,EncodingType,retval) ) 

#define ICPEnvelopedData2_Decrypt(This,EnvelopedMessage,retval)	\
    ( (This)->lpVtbl -> Decrypt(This,EnvelopedMessage,retval) ) 


#define ICPEnvelopedData2_get_ContentEncoding(This,pEncodingType)	\
    ( (This)->lpVtbl -> get_ContentEncoding(This,pEncodingType) ) 

#define ICPEnvelopedData2_put_ContentEncoding(This,EncodingType)	\
    ( (This)->lpVtbl -> put_ContentEncoding(This,EncodingType) ) 


#define ICPEnvelopedData2_StreamEncrypt(This,pbData,isFinal,pVal)	\
    ( (This)->lpVtbl -> StreamEncrypt(This,pbData,isFinal,pVal) ) 

#define ICPEnvelopedData2_StreamDecrypt(This,pbData,isFinal,pVal)	\
    ( (This)->lpVtbl -> StreamDecrypt(This,pbData,isFinal,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPEnvelopedData2_INTERFACE_DEFINED__ */


#ifndef __ICPHashedData_INTERFACE_DEFINED__
#define __ICPHashedData_INTERFACE_DEFINED__

/* interface ICPHashedData */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_ICPHashedData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5A64116E-B059-4554-9709-B3D08CE80226")
    ICPHashedData : public IHashedData
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DataEncoding( 
            /* [retval][out] */ CADESCOM_CONTENT_ENCODING_TYPE *pEncodingType) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DataEncoding( 
            /* [in] */ CADESCOM_CONTENT_ENCODING_TYPE EncodingType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetHashValue( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPHashedDataVtbl
    {
        BEGIN_INTERFACE
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPHashedData * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [out][idldescattr] */ void **ppvObj,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *AddRef )( 
            ICPHashedData * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Release )( 
            ICPHashedData * This,
            /* [retval][out] */ unsigned long *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPHashedData * This,
            /* [out][idldescattr] */ unsigned UINT *pctinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPHashedData * This,
            /* [in][idldescattr] */ unsigned UINT itinfo,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ void **pptinfo,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPHashedData * This,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ signed char **rgszNames,
            /* [in][idldescattr] */ unsigned UINT cNames,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [out][idldescattr] */ signed long *rgdispid,
            /* [retval][out] */ void *retval);
        
        /* [id][restricted][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPHashedData * This,
            /* [in][idldescattr] */ signed long dispidMember,
            /* [in][idldescattr] */ struct GUID *riid,
            /* [in][idldescattr] */ unsigned long lcid,
            /* [in][idldescattr] */ unsigned short wFlags,
            /* [in][idldescattr] */ struct DISPPARAMS *pdispparams,
            /* [out][idldescattr] */ VARIANT *pvarResult,
            /* [out][idldescattr] */ struct EXCEPINFO *pexcepinfo,
            /* [out][idldescattr] */ unsigned UINT *puArgErr,
            /* [retval][out] */ void *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Value )( 
            ICPHashedData * This,
            /* [retval][out] */ BSTR *retval);
        
        /* [id][propget][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *get_Algorithm )( 
            ICPHashedData * This,
            /* [retval][out] */ CAPICOM_HASH_ALGORITHM *retval);
        
        /* [id][propput][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *put_Algorithm )( 
            ICPHashedData * This,
            /* [in][idldescattr] */ CAPICOM_HASH_ALGORITHM noname,
            /* [retval][out] */ void *retval);
        
        /* [id][funcdescattr] */ HRESULT ( STDMETHODCALLTYPE *Hash )( 
            ICPHashedData * This,
            /* [in][idldescattr] */ BSTR newVal,
            /* [retval][out] */ void *retval);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DataEncoding )( 
            ICPHashedData * This,
            /* [retval][out] */ CADESCOM_CONTENT_ENCODING_TYPE *pEncodingType);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_DataEncoding )( 
            ICPHashedData * This,
            /* [in] */ CADESCOM_CONTENT_ENCODING_TYPE EncodingType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetHashValue )( 
            ICPHashedData * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } ICPHashedDataVtbl;

    interface ICPHashedData
    {
        CONST_VTBL struct ICPHashedDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPHashedData_QueryInterface(This,riid,ppvObj,retval)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObj,retval) ) 

#define ICPHashedData_AddRef(This,retval)	\
    ( (This)->lpVtbl -> AddRef(This,retval) ) 

#define ICPHashedData_Release(This,retval)	\
    ( (This)->lpVtbl -> Release(This,retval) ) 

#define ICPHashedData_GetTypeInfoCount(This,pctinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo,retval) ) 

#define ICPHashedData_GetTypeInfo(This,itinfo,lcid,pptinfo,retval)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,itinfo,lcid,pptinfo,retval) ) 

#define ICPHashedData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgdispid,retval) ) 

#define ICPHashedData_Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval)	\
    ( (This)->lpVtbl -> Invoke(This,dispidMember,riid,lcid,wFlags,pdispparams,pvarResult,pexcepinfo,puArgErr,retval) ) 

#define ICPHashedData_get_Value(This,retval)	\
    ( (This)->lpVtbl -> get_Value(This,retval) ) 

#define ICPHashedData_get_Algorithm(This,retval)	\
    ( (This)->lpVtbl -> get_Algorithm(This,retval) ) 

#define ICPHashedData_put_Algorithm(This,noname,retval)	\
    ( (This)->lpVtbl -> put_Algorithm(This,noname,retval) ) 

#define ICPHashedData_Hash(This,newVal,retval)	\
    ( (This)->lpVtbl -> Hash(This,newVal,retval) ) 


#define ICPHashedData_get_DataEncoding(This,pEncodingType)	\
    ( (This)->lpVtbl -> get_DataEncoding(This,pEncodingType) ) 

#define ICPHashedData_put_DataEncoding(This,EncodingType)	\
    ( (This)->lpVtbl -> put_DataEncoding(This,EncodingType) ) 

#define ICPHashedData_SetHashValue(This,newVal)	\
    ( (This)->lpVtbl -> SetHashValue(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPHashedData_INTERFACE_DEFINED__ */


#ifndef __ISignedXML_INTERFACE_DEFINED__
#define __ISignedXML_INTERFACE_DEFINED__

/* interface ISignedXML */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISignedXML;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4B7AB972-0660-4556-A1B1-58B08E912203")
    ISignedXML : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Content( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Content( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Signers( 
            /* [retval][out] */ /* external definition not present */ ISigners **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sign( 
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ BSTR XPath,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Verify( 
            /* [in] */ BSTR SignedMessage,
            /* [defaultvalue][in] */ BSTR XPath = L"") = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SignatureType( 
            /* [retval][out] */ CADESCOM_XML_SIGNATURE_TYPE *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SignatureType( 
            /* [in] */ CADESCOM_XML_SIGNATURE_TYPE SignatureType) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SignatureMethod( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SignatureMethod( 
            /* [in] */ BSTR pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DigestMethod( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DigestMethod( 
            /* [in] */ BSTR pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISignedXMLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISignedXML * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISignedXML * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISignedXML * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISignedXML * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISignedXML * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISignedXML * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISignedXML * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Content )( 
            ISignedXML * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Content )( 
            ISignedXML * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Signers )( 
            ISignedXML * This,
            /* [retval][out] */ /* external definition not present */ ISigners **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Sign )( 
            ISignedXML * This,
            /* [optional][in] */ VARIANT Signer,
            /* [defaultvalue][in] */ BSTR XPath,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Verify )( 
            ISignedXML * This,
            /* [in] */ BSTR SignedMessage,
            /* [defaultvalue][in] */ BSTR XPath);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureType )( 
            ISignedXML * This,
            /* [retval][out] */ CADESCOM_XML_SIGNATURE_TYPE *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SignatureType )( 
            ISignedXML * This,
            /* [in] */ CADESCOM_XML_SIGNATURE_TYPE SignatureType);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureMethod )( 
            ISignedXML * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SignatureMethod )( 
            ISignedXML * This,
            /* [in] */ BSTR pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DigestMethod )( 
            ISignedXML * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_DigestMethod )( 
            ISignedXML * This,
            /* [in] */ BSTR pVal);
        
        END_INTERFACE
    } ISignedXMLVtbl;

    interface ISignedXML
    {
        CONST_VTBL struct ISignedXMLVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISignedXML_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISignedXML_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISignedXML_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISignedXML_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISignedXML_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISignedXML_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISignedXML_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISignedXML_get_Content(This,pVal)	\
    ( (This)->lpVtbl -> get_Content(This,pVal) ) 

#define ISignedXML_put_Content(This,newVal)	\
    ( (This)->lpVtbl -> put_Content(This,newVal) ) 

#define ISignedXML_get_Signers(This,pVal)	\
    ( (This)->lpVtbl -> get_Signers(This,pVal) ) 

#define ISignedXML_Sign(This,Signer,XPath,pVal)	\
    ( (This)->lpVtbl -> Sign(This,Signer,XPath,pVal) ) 

#define ISignedXML_Verify(This,SignedMessage,XPath)	\
    ( (This)->lpVtbl -> Verify(This,SignedMessage,XPath) ) 

#define ISignedXML_get_SignatureType(This,pVal)	\
    ( (This)->lpVtbl -> get_SignatureType(This,pVal) ) 

#define ISignedXML_put_SignatureType(This,SignatureType)	\
    ( (This)->lpVtbl -> put_SignatureType(This,SignatureType) ) 

#define ISignedXML_get_SignatureMethod(This,pVal)	\
    ( (This)->lpVtbl -> get_SignatureMethod(This,pVal) ) 

#define ISignedXML_put_SignatureMethod(This,pVal)	\
    ( (This)->lpVtbl -> put_SignatureMethod(This,pVal) ) 

#define ISignedXML_get_DigestMethod(This,pVal)	\
    ( (This)->lpVtbl -> get_DigestMethod(This,pVal) ) 

#define ISignedXML_put_DigestMethod(This,pVal)	\
    ( (This)->lpVtbl -> put_DigestMethod(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISignedXML_INTERFACE_DEFINED__ */


#ifndef __ICardholderData_INTERFACE_DEFINED__
#define __ICardholderData_INTERFACE_DEFINED__

/* interface ICardholderData */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_ICardholderData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5F7F6186-88DB-4453-BB05-3DDB31674B75")
    ICardholderData : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SocialAccountNumber( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_OMSNumber( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CardholderName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CardholderFirstName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CardholderLastName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CardholderSecondName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CardIssuerAddress( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DateOfBirth( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_PlaceOfBirth( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SexString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Sex( 
            /* [retval][out] */ CADESCOM_HUMAN_SEXES *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICardholderDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICardholderData * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICardholderData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICardholderData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICardholderData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICardholderData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICardholderData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICardholderData * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SocialAccountNumber )( 
            ICardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OMSNumber )( 
            ICardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CardholderName )( 
            ICardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CardholderFirstName )( 
            ICardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CardholderLastName )( 
            ICardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CardholderSecondName )( 
            ICardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CardIssuerAddress )( 
            ICardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DateOfBirth )( 
            ICardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_PlaceOfBirth )( 
            ICardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SexString )( 
            ICardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Sex )( 
            ICardholderData * This,
            /* [retval][out] */ CADESCOM_HUMAN_SEXES *pVal);
        
        END_INTERFACE
    } ICardholderDataVtbl;

    interface ICardholderData
    {
        CONST_VTBL struct ICardholderDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICardholderData_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICardholderData_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICardholderData_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICardholderData_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICardholderData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICardholderData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICardholderData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICardholderData_get_SocialAccountNumber(This,pVal)	\
    ( (This)->lpVtbl -> get_SocialAccountNumber(This,pVal) ) 

#define ICardholderData_get_OMSNumber(This,pVal)	\
    ( (This)->lpVtbl -> get_OMSNumber(This,pVal) ) 

#define ICardholderData_get_CardholderName(This,pVal)	\
    ( (This)->lpVtbl -> get_CardholderName(This,pVal) ) 

#define ICardholderData_get_CardholderFirstName(This,pVal)	\
    ( (This)->lpVtbl -> get_CardholderFirstName(This,pVal) ) 

#define ICardholderData_get_CardholderLastName(This,pVal)	\
    ( (This)->lpVtbl -> get_CardholderLastName(This,pVal) ) 

#define ICardholderData_get_CardholderSecondName(This,pVal)	\
    ( (This)->lpVtbl -> get_CardholderSecondName(This,pVal) ) 

#define ICardholderData_get_CardIssuerAddress(This,pVal)	\
    ( (This)->lpVtbl -> get_CardIssuerAddress(This,pVal) ) 

#define ICardholderData_get_DateOfBirth(This,pVal)	\
    ( (This)->lpVtbl -> get_DateOfBirth(This,pVal) ) 

#define ICardholderData_get_PlaceOfBirth(This,pVal)	\
    ( (This)->lpVtbl -> get_PlaceOfBirth(This,pVal) ) 

#define ICardholderData_get_SexString(This,pVal)	\
    ( (This)->lpVtbl -> get_SexString(This,pVal) ) 

#define ICardholderData_get_Sex(This,pVal)	\
    ( (This)->lpVtbl -> get_Sex(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICardholderData_INTERFACE_DEFINED__ */


#ifndef __IIdentityCard_INTERFACE_DEFINED__
#define __IIdentityCard_INTERFACE_DEFINED__

/* interface IIdentityCard */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_IIdentityCard;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A26E9DDC-FC1C-4042-82C0-F0753F0B5015")
    IIdentityCard : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ContainerType( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ContainerType( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DivisionCode( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DivisionCode( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DivisionName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DivisionName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_EffectiveDate( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_EffectiveDate( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ExpirationDate( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IdExtension( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_IdExtension( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IdNumber( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_IdNumber( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IdSeries( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_IdSeries( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIdentityCardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIdentityCard * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIdentityCard * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIdentityCard * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIdentityCard * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIdentityCard * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIdentityCard * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIdentityCard * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ContainerType )( 
            IIdentityCard * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ContainerType )( 
            IIdentityCard * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DivisionCode )( 
            IIdentityCard * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_DivisionCode )( 
            IIdentityCard * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DivisionName )( 
            IIdentityCard * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_DivisionName )( 
            IIdentityCard * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_EffectiveDate )( 
            IIdentityCard * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_EffectiveDate )( 
            IIdentityCard * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ExpirationDate )( 
            IIdentityCard * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ExpirationDate )( 
            IIdentityCard * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IdExtension )( 
            IIdentityCard * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_IdExtension )( 
            IIdentityCard * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IdNumber )( 
            IIdentityCard * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_IdNumber )( 
            IIdentityCard * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IdSeries )( 
            IIdentityCard * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_IdSeries )( 
            IIdentityCard * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IIdentityCardVtbl;

    interface IIdentityCard
    {
        CONST_VTBL struct IIdentityCardVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIdentityCard_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIdentityCard_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIdentityCard_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIdentityCard_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIdentityCard_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIdentityCard_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIdentityCard_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IIdentityCard_get_ContainerType(This,pVal)	\
    ( (This)->lpVtbl -> get_ContainerType(This,pVal) ) 

#define IIdentityCard_put_ContainerType(This,newVal)	\
    ( (This)->lpVtbl -> put_ContainerType(This,newVal) ) 

#define IIdentityCard_get_DivisionCode(This,pVal)	\
    ( (This)->lpVtbl -> get_DivisionCode(This,pVal) ) 

#define IIdentityCard_put_DivisionCode(This,newVal)	\
    ( (This)->lpVtbl -> put_DivisionCode(This,newVal) ) 

#define IIdentityCard_get_DivisionName(This,pVal)	\
    ( (This)->lpVtbl -> get_DivisionName(This,pVal) ) 

#define IIdentityCard_put_DivisionName(This,newVal)	\
    ( (This)->lpVtbl -> put_DivisionName(This,newVal) ) 

#define IIdentityCard_get_EffectiveDate(This,pVal)	\
    ( (This)->lpVtbl -> get_EffectiveDate(This,pVal) ) 

#define IIdentityCard_put_EffectiveDate(This,newVal)	\
    ( (This)->lpVtbl -> put_EffectiveDate(This,newVal) ) 

#define IIdentityCard_get_ExpirationDate(This,pVal)	\
    ( (This)->lpVtbl -> get_ExpirationDate(This,pVal) ) 

#define IIdentityCard_put_ExpirationDate(This,newVal)	\
    ( (This)->lpVtbl -> put_ExpirationDate(This,newVal) ) 

#define IIdentityCard_get_IdExtension(This,pVal)	\
    ( (This)->lpVtbl -> get_IdExtension(This,pVal) ) 

#define IIdentityCard_put_IdExtension(This,newVal)	\
    ( (This)->lpVtbl -> put_IdExtension(This,newVal) ) 

#define IIdentityCard_get_IdNumber(This,pVal)	\
    ( (This)->lpVtbl -> get_IdNumber(This,pVal) ) 

#define IIdentityCard_put_IdNumber(This,newVal)	\
    ( (This)->lpVtbl -> put_IdNumber(This,newVal) ) 

#define IIdentityCard_get_IdSeries(This,pVal)	\
    ( (This)->lpVtbl -> get_IdSeries(This,pVal) ) 

#define IIdentityCard_put_IdSeries(This,newVal)	\
    ( (This)->lpVtbl -> put_IdSeries(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIdentityCard_INTERFACE_DEFINED__ */


#ifndef __IPersonalCardholderData_INTERFACE_DEFINED__
#define __IPersonalCardholderData_INTERFACE_DEFINED__

/* interface IPersonalCardholderData */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_IPersonalCardholderData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BC97AD5D-77AC-4c70-8391-1DCAC2989F15")
    IPersonalCardholderData : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Address( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Address( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_PhoneNumber( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_PhoneNumber( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Email( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Email( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IndividualTaxpayerNumber( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_IndividualTaxpayerNumber( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VehicleLicenseNumber( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_VehicleLicenseNumber( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VehicleRegistrationCertificate( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_VehicleRegistrationCertificate( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IdentityCard( 
            /* [retval][out] */ IIdentityCard **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Submit( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetAllData( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPersonalCardholderDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPersonalCardholderData * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPersonalCardholderData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPersonalCardholderData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPersonalCardholderData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPersonalCardholderData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPersonalCardholderData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPersonalCardholderData * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Address )( 
            IPersonalCardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Address )( 
            IPersonalCardholderData * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_PhoneNumber )( 
            IPersonalCardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_PhoneNumber )( 
            IPersonalCardholderData * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Email )( 
            IPersonalCardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Email )( 
            IPersonalCardholderData * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IndividualTaxpayerNumber )( 
            IPersonalCardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_IndividualTaxpayerNumber )( 
            IPersonalCardholderData * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_VehicleLicenseNumber )( 
            IPersonalCardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_VehicleLicenseNumber )( 
            IPersonalCardholderData * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_VehicleRegistrationCertificate )( 
            IPersonalCardholderData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_VehicleRegistrationCertificate )( 
            IPersonalCardholderData * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IdentityCard )( 
            IPersonalCardholderData * This,
            /* [retval][out] */ IIdentityCard **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Submit )( 
            IPersonalCardholderData * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResetAllData )( 
            IPersonalCardholderData * This);
        
        END_INTERFACE
    } IPersonalCardholderDataVtbl;

    interface IPersonalCardholderData
    {
        CONST_VTBL struct IPersonalCardholderDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPersonalCardholderData_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPersonalCardholderData_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPersonalCardholderData_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPersonalCardholderData_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPersonalCardholderData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPersonalCardholderData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPersonalCardholderData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPersonalCardholderData_get_Address(This,pVal)	\
    ( (This)->lpVtbl -> get_Address(This,pVal) ) 

#define IPersonalCardholderData_put_Address(This,newVal)	\
    ( (This)->lpVtbl -> put_Address(This,newVal) ) 

#define IPersonalCardholderData_get_PhoneNumber(This,pVal)	\
    ( (This)->lpVtbl -> get_PhoneNumber(This,pVal) ) 

#define IPersonalCardholderData_put_PhoneNumber(This,newVal)	\
    ( (This)->lpVtbl -> put_PhoneNumber(This,newVal) ) 

#define IPersonalCardholderData_get_Email(This,pVal)	\
    ( (This)->lpVtbl -> get_Email(This,pVal) ) 

#define IPersonalCardholderData_put_Email(This,newVal)	\
    ( (This)->lpVtbl -> put_Email(This,newVal) ) 

#define IPersonalCardholderData_get_IndividualTaxpayerNumber(This,pVal)	\
    ( (This)->lpVtbl -> get_IndividualTaxpayerNumber(This,pVal) ) 

#define IPersonalCardholderData_put_IndividualTaxpayerNumber(This,newVal)	\
    ( (This)->lpVtbl -> put_IndividualTaxpayerNumber(This,newVal) ) 

#define IPersonalCardholderData_get_VehicleLicenseNumber(This,pVal)	\
    ( (This)->lpVtbl -> get_VehicleLicenseNumber(This,pVal) ) 

#define IPersonalCardholderData_put_VehicleLicenseNumber(This,newVal)	\
    ( (This)->lpVtbl -> put_VehicleLicenseNumber(This,newVal) ) 

#define IPersonalCardholderData_get_VehicleRegistrationCertificate(This,pVal)	\
    ( (This)->lpVtbl -> get_VehicleRegistrationCertificate(This,pVal) ) 

#define IPersonalCardholderData_put_VehicleRegistrationCertificate(This,newVal)	\
    ( (This)->lpVtbl -> put_VehicleRegistrationCertificate(This,newVal) ) 

#define IPersonalCardholderData_get_IdentityCard(This,pVal)	\
    ( (This)->lpVtbl -> get_IdentityCard(This,pVal) ) 

#define IPersonalCardholderData_Submit(This)	\
    ( (This)->lpVtbl -> Submit(This) ) 

#define IPersonalCardholderData_ResetAllData(This)	\
    ( (This)->lpVtbl -> ResetAllData(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPersonalCardholderData_INTERFACE_DEFINED__ */


#ifndef __IOMSData_INTERFACE_DEFINED__
#define __IOMSData_INTERFACE_DEFINED__

/* interface IOMSData */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_IOMSData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07DA1F55-BD56-4006-82DA-69360874E128")
    IOMSData : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_OGRN( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_OKATO( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_EffectiveDate( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IOMSDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOMSData * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOMSData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOMSData * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IOMSData * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IOMSData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IOMSData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IOMSData * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OGRN )( 
            IOMSData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OKATO )( 
            IOMSData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_EffectiveDate )( 
            IOMSData * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ExpirationDate )( 
            IOMSData * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IOMSDataVtbl;

    interface IOMSData
    {
        CONST_VTBL struct IOMSDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOMSData_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOMSData_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOMSData_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOMSData_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IOMSData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IOMSData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IOMSData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IOMSData_get_OGRN(This,pVal)	\
    ( (This)->lpVtbl -> get_OGRN(This,pVal) ) 

#define IOMSData_get_OKATO(This,pVal)	\
    ( (This)->lpVtbl -> get_OKATO(This,pVal) ) 

#define IOMSData_get_EffectiveDate(This,pVal)	\
    ( (This)->lpVtbl -> get_EffectiveDate(This,pVal) ) 

#define IOMSData_get_ExpirationDate(This,pVal)	\
    ( (This)->lpVtbl -> get_ExpirationDate(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IOMSData_INTERFACE_DEFINED__ */


#ifndef __IUECard_INTERFACE_DEFINED__
#define __IUECard_INTERFACE_DEFINED__

/* interface IUECard */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_IUECard;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("98473852-2B72-4ebe-A985-6B72B9E93193")
    IUECard : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CardholderData( 
            /* [retval][out] */ ICardholderData **pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_PersonalCardholderData( 
            /* [in] */ VARIANT_BOOL bTrustedData,
            /* [retval][out] */ IPersonalCardholderData **pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_UECardWelcomeText( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ProviderVersion( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPin1( 
            /* [in] */ BSTR Pin1) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUECardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUECard * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUECard * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUECard * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUECard * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUECard * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUECard * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUECard * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CardholderData )( 
            IUECard * This,
            /* [retval][out] */ ICardholderData **pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_PersonalCardholderData )( 
            IUECard * This,
            /* [in] */ VARIANT_BOOL bTrustedData,
            /* [retval][out] */ IPersonalCardholderData **pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UECardWelcomeText )( 
            IUECard * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ProviderVersion )( 
            IUECard * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPin1 )( 
            IUECard * This,
            /* [in] */ BSTR Pin1);
        
        END_INTERFACE
    } IUECardVtbl;

    interface IUECard
    {
        CONST_VTBL struct IUECardVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUECard_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUECard_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUECard_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUECard_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IUECard_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IUECard_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IUECard_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IUECard_get_CardholderData(This,pVal)	\
    ( (This)->lpVtbl -> get_CardholderData(This,pVal) ) 

#define IUECard_get_PersonalCardholderData(This,bTrustedData,pVal)	\
    ( (This)->lpVtbl -> get_PersonalCardholderData(This,bTrustedData,pVal) ) 

#define IUECard_get_UECardWelcomeText(This,pVal)	\
    ( (This)->lpVtbl -> get_UECardWelcomeText(This,pVal) ) 

#define IUECard_get_ProviderVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_ProviderVersion(This,pVal) ) 

#define IUECard_SetPin1(This,Pin1)	\
    ( (This)->lpVtbl -> SetPin1(This,Pin1) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUECard_INTERFACE_DEFINED__ */


#ifndef __IUECard2_INTERFACE_DEFINED__
#define __IUECard2_INTERFACE_DEFINED__

/* interface IUECard2 */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_IUECard2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("42916DD9-7DF7-463c-B7EF-05EF955721E5")
    IUECard2 : public IUECard
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Certificate( 
            /* [retval][out] */ /* external definition not present */ ICertificate **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUECard2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUECard2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUECard2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUECard2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUECard2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUECard2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUECard2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUECard2 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CardholderData )( 
            IUECard2 * This,
            /* [retval][out] */ ICardholderData **pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_PersonalCardholderData )( 
            IUECard2 * This,
            /* [in] */ VARIANT_BOOL bTrustedData,
            /* [retval][out] */ IPersonalCardholderData **pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UECardWelcomeText )( 
            IUECard2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ProviderVersion )( 
            IUECard2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPin1 )( 
            IUECard2 * This,
            /* [in] */ BSTR Pin1);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Certificate )( 
            IUECard2 * This,
            /* [retval][out] */ /* external definition not present */ ICertificate **pVal);
        
        END_INTERFACE
    } IUECard2Vtbl;

    interface IUECard2
    {
        CONST_VTBL struct IUECard2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUECard2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUECard2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUECard2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUECard2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IUECard2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IUECard2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IUECard2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IUECard2_get_CardholderData(This,pVal)	\
    ( (This)->lpVtbl -> get_CardholderData(This,pVal) ) 

#define IUECard2_get_PersonalCardholderData(This,bTrustedData,pVal)	\
    ( (This)->lpVtbl -> get_PersonalCardholderData(This,bTrustedData,pVal) ) 

#define IUECard2_get_UECardWelcomeText(This,pVal)	\
    ( (This)->lpVtbl -> get_UECardWelcomeText(This,pVal) ) 

#define IUECard2_get_ProviderVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_ProviderVersion(This,pVal) ) 

#define IUECard2_SetPin1(This,Pin1)	\
    ( (This)->lpVtbl -> SetPin1(This,Pin1) ) 


#define IUECard2_get_Certificate(This,pVal)	\
    ( (This)->lpVtbl -> get_Certificate(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUECard2_INTERFACE_DEFINED__ */


#ifndef __IUECard3_INTERFACE_DEFINED__
#define __IUECard3_INTERFACE_DEFINED__

/* interface IUECard3 */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_IUECard3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("13DEA1C3-9B33-483D-90C8-5D3BD541E54B")
    IUECard3 : public IUECard2
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_OMSData( 
            /* [retval][out] */ IOMSData **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUECard3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUECard3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUECard3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUECard3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUECard3 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUECard3 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUECard3 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUECard3 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CardholderData )( 
            IUECard3 * This,
            /* [retval][out] */ ICardholderData **pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_PersonalCardholderData )( 
            IUECard3 * This,
            /* [in] */ VARIANT_BOOL bTrustedData,
            /* [retval][out] */ IPersonalCardholderData **pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UECardWelcomeText )( 
            IUECard3 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ProviderVersion )( 
            IUECard3 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPin1 )( 
            IUECard3 * This,
            /* [in] */ BSTR Pin1);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Certificate )( 
            IUECard3 * This,
            /* [retval][out] */ /* external definition not present */ ICertificate **pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_OMSData )( 
            IUECard3 * This,
            /* [retval][out] */ IOMSData **pVal);
        
        END_INTERFACE
    } IUECard3Vtbl;

    interface IUECard3
    {
        CONST_VTBL struct IUECard3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUECard3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUECard3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUECard3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUECard3_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IUECard3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IUECard3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IUECard3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IUECard3_get_CardholderData(This,pVal)	\
    ( (This)->lpVtbl -> get_CardholderData(This,pVal) ) 

#define IUECard3_get_PersonalCardholderData(This,bTrustedData,pVal)	\
    ( (This)->lpVtbl -> get_PersonalCardholderData(This,bTrustedData,pVal) ) 

#define IUECard3_get_UECardWelcomeText(This,pVal)	\
    ( (This)->lpVtbl -> get_UECardWelcomeText(This,pVal) ) 

#define IUECard3_get_ProviderVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_ProviderVersion(This,pVal) ) 

#define IUECard3_SetPin1(This,Pin1)	\
    ( (This)->lpVtbl -> SetPin1(This,Pin1) ) 


#define IUECard3_get_Certificate(This,pVal)	\
    ( (This)->lpVtbl -> get_Certificate(This,pVal) ) 


#define IUECard3_get_OMSData(This,pVal)	\
    ( (This)->lpVtbl -> get_OMSData(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUECard3_INTERFACE_DEFINED__ */


#ifndef __IEventSource_INTERFACE_DEFINED__
#define __IEventSource_INTERFACE_DEFINED__

/* interface IEventSource */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID_IEventSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DD2C0155-6308-4ab4-9A1A-BE9A3462D0BE")
    IEventSource : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addEventListener( 
            /* [in] */ BSTR Event,
            /* [in] */ VARIANT Listener,
            /* [defaultvalue][in] */ VARIANT_BOOL bUseCapture = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeEventListener( 
            /* [in] */ BSTR Event,
            /* [in] */ VARIANT Listener,
            /* [defaultvalue][in] */ VARIANT_BOOL bUseCapture = 0) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEventSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEventSource * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEventSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEventSource * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IEventSource * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IEventSource * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IEventSource * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IEventSource * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addEventListener )( 
            IEventSource * This,
            /* [in] */ BSTR Event,
            /* [in] */ VARIANT Listener,
            /* [defaultvalue][in] */ VARIANT_BOOL bUseCapture);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeEventListener )( 
            IEventSource * This,
            /* [in] */ BSTR Event,
            /* [in] */ VARIANT Listener,
            /* [defaultvalue][in] */ VARIANT_BOOL bUseCapture);
        
        END_INTERFACE
    } IEventSourceVtbl;

    interface IEventSource
    {
        CONST_VTBL struct IEventSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEventSource_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEventSource_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEventSource_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEventSource_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IEventSource_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IEventSource_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IEventSource_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IEventSource_addEventListener(This,Event,Listener,bUseCapture)	\
    ( (This)->lpVtbl -> addEventListener(This,Event,Listener,bUseCapture) ) 

#define IEventSource_removeEventListener(This,Event,Listener,bUseCapture)	\
    ( (This)->lpVtbl -> removeEventListener(This,Event,Listener,bUseCapture) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEventSource_INTERFACE_DEFINED__ */


#ifndef __ITrustedSites_INTERFACE_DEFINED__
#define __ITrustedSites_INTERFACE_DEFINED__

/* interface ITrustedSites */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITrustedSites;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8A83BED0-5D07-4f49-9DF4-9C0090592705")
    ITrustedSites : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Site,
            /* [retval][out] */ BSTR *SimpleSite) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            LONG Index) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG Index,
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITrustedSitesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITrustedSites * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITrustedSites * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITrustedSites * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITrustedSites * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITrustedSites * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITrustedSites * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITrustedSites * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITrustedSites * This,
            /* [in] */ BSTR Site,
            /* [retval][out] */ BSTR *SimpleSite);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITrustedSites * This,
            LONG Index);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITrustedSites * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITrustedSites * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            ITrustedSites * This);
        
        END_INTERFACE
    } ITrustedSitesVtbl;

    interface ITrustedSites
    {
        CONST_VTBL struct ITrustedSitesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrustedSites_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITrustedSites_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITrustedSites_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITrustedSites_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITrustedSites_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITrustedSites_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITrustedSites_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITrustedSites_Add(This,Site,SimpleSite)	\
    ( (This)->lpVtbl -> Add(This,Site,SimpleSite) ) 

#define ITrustedSites_Remove(This,Index)	\
    ( (This)->lpVtbl -> Remove(This,Index) ) 

#define ITrustedSites_get_Item(This,Index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,Index,pVal) ) 

#define ITrustedSites_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ITrustedSites_Save(This)	\
    ( (This)->lpVtbl -> Save(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITrustedSites_INTERFACE_DEFINED__ */


#ifndef __IPluginConfiguration_INTERFACE_DEFINED__
#define __IPluginConfiguration_INTERFACE_DEFINED__

/* interface IPluginConfiguration */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPluginConfiguration;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E5741F41-4A28-45ec-AE60-ADCD7FAD02C4")
    IPluginConfiguration : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TrustedSites( 
            /* [retval][out] */ ITrustedSites **ppVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TrustedSitesGroupPolicy( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsUntrustedSitesDisabled( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPluginConfigurationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPluginConfiguration * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPluginConfiguration * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPluginConfiguration * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPluginConfiguration * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPluginConfiguration * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPluginConfiguration * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPluginConfiguration * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_TrustedSites )( 
            IPluginConfiguration * This,
            /* [retval][out] */ ITrustedSites **ppVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_TrustedSitesGroupPolicy )( 
            IPluginConfiguration * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IsUntrustedSitesDisabled )( 
            IPluginConfiguration * This,
            /* [retval][out] */ BOOL *pVal);
        
        END_INTERFACE
    } IPluginConfigurationVtbl;

    interface IPluginConfiguration
    {
        CONST_VTBL struct IPluginConfigurationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPluginConfiguration_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPluginConfiguration_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPluginConfiguration_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPluginConfiguration_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPluginConfiguration_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPluginConfiguration_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPluginConfiguration_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPluginConfiguration_get_TrustedSites(This,ppVal)	\
    ( (This)->lpVtbl -> get_TrustedSites(This,ppVal) ) 

#define IPluginConfiguration_get_TrustedSitesGroupPolicy(This,pVal)	\
    ( (This)->lpVtbl -> get_TrustedSitesGroupPolicy(This,pVal) ) 

#define IPluginConfiguration_get_IsUntrustedSitesDisabled(This,pVal)	\
    ( (This)->lpVtbl -> get_IsUntrustedSitesDisabled(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPluginConfiguration_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TrustedSites;

#ifdef __cplusplus

class DECLSPEC_UUID("E853748A-9CB8-424a-BEDD-4E0B1033CEF3")
TrustedSites;
#endif

EXTERN_C const CLSID CLSID_PluginConfiguration;

#ifdef __cplusplus

class DECLSPEC_UUID("89743089-7EE0-4817-91CC-A5E80AD1C0A2")
PluginConfiguration;
#endif

#ifndef __IRawSignature_INTERFACE_DEFINED__
#define __IRawSignature_INTERFACE_DEFINED__

/* interface IRawSignature */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IRawSignature;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51E0331F-1A41-47B0-80FA-574A6B2DF0C1")
    IRawSignature : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignHash( 
            /* [in] */ /* external definition not present */ IHashedData *Hash,
            /* [optional][in] */ VARIANT Certificate,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerifyHash( 
            /* [in] */ /* external definition not present */ IHashedData *Hash,
            /* [in] */ /* external definition not present */ ICertificate *Certificate,
            /* [in] */ BSTR Signature) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IRawSignatureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRawSignature * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRawSignature * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRawSignature * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRawSignature * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRawSignature * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRawSignature * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRawSignature * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SignHash )( 
            IRawSignature * This,
            /* [in] */ /* external definition not present */ IHashedData *Hash,
            /* [optional][in] */ VARIANT Certificate,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *VerifyHash )( 
            IRawSignature * This,
            /* [in] */ /* external definition not present */ IHashedData *Hash,
            /* [in] */ /* external definition not present */ ICertificate *Certificate,
            /* [in] */ BSTR Signature);
        
        END_INTERFACE
    } IRawSignatureVtbl;

    interface IRawSignature
    {
        CONST_VTBL struct IRawSignatureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRawSignature_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRawSignature_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRawSignature_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRawSignature_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRawSignature_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRawSignature_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRawSignature_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRawSignature_SignHash(This,Hash,Certificate,pVal)	\
    ( (This)->lpVtbl -> SignHash(This,Hash,Certificate,pVal) ) 

#define IRawSignature_VerifyHash(This,Hash,Certificate,Signature)	\
    ( (This)->lpVtbl -> VerifyHash(This,Hash,Certificate,Signature) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IRawSignature_INTERFACE_DEFINED__ */


#ifndef __IAbout_INTERFACE_DEFINED__
#define __IAbout_INTERFACE_DEFINED__

/* interface IAbout */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAbout;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EABAEE0A-CF10-4a80-91BB-DF44E4475F1B")
    IAbout : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MajorVersion( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinorVersion( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BuildVersion( 
            /* [retval][out] */ LONG *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAboutVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAbout * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAbout * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAbout * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAbout * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAbout * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAbout * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAbout * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IAbout * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MajorVersion )( 
            IAbout * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinorVersion )( 
            IAbout * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BuildVersion )( 
            IAbout * This,
            /* [retval][out] */ LONG *pVal);
        
        END_INTERFACE
    } IAboutVtbl;

    interface IAbout
    {
        CONST_VTBL struct IAboutVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAbout_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAbout_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAbout_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAbout_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAbout_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAbout_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAbout_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAbout_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IAbout_get_MajorVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_MajorVersion(This,pVal) ) 

#define IAbout_get_MinorVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_MinorVersion(This,pVal) ) 

#define IAbout_get_BuildVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_BuildVersion(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAbout_INTERFACE_DEFINED__ */


#ifndef __IVersion_INTERFACE_DEFINED__
#define __IVersion_INTERFACE_DEFINED__

/* interface IVersion */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IVersion;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("103D60B6-700F-469d-907A-97D3402648E3")
    IVersion : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_toStringDefault( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE toString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MajorVersion( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinorVersion( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BuildVersion( 
            /* [retval][out] */ LONG *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IVersionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVersion * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVersion * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVersion * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVersion * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVersion * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVersion * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVersion * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_toStringDefault )( 
            IVersion * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *toString )( 
            IVersion * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MajorVersion )( 
            IVersion * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinorVersion )( 
            IVersion * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BuildVersion )( 
            IVersion * This,
            /* [retval][out] */ LONG *pVal);
        
        END_INTERFACE
    } IVersionVtbl;

    interface IVersion
    {
        CONST_VTBL struct IVersionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVersion_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVersion_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVersion_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IVersion_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IVersion_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IVersion_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IVersion_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IVersion_get_toStringDefault(This,pVal)	\
    ( (This)->lpVtbl -> get_toStringDefault(This,pVal) ) 

#define IVersion_toString(This,pVal)	\
    ( (This)->lpVtbl -> toString(This,pVal) ) 

#define IVersion_get_MajorVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_MajorVersion(This,pVal) ) 

#define IVersion_get_MinorVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_MinorVersion(This,pVal) ) 

#define IVersion_get_BuildVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_BuildVersion(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IVersion_INTERFACE_DEFINED__ */


#ifndef __IAbout2_INTERFACE_DEFINED__
#define __IAbout2_INTERFACE_DEFINED__

/* interface IAbout2 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAbout2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BA57172B-6445-4e5c-A63B-5DF16CA23650")
    IAbout2 : public IAbout
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ProviderVersion( 
            /* [defaultvalue][in] */ BSTR ProviderName,
            /* [defaultvalue][in] */ LONG ProviderType,
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAbout2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAbout2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAbout2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAbout2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAbout2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAbout2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAbout2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAbout2 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IAbout2 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MajorVersion )( 
            IAbout2 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinorVersion )( 
            IAbout2 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BuildVersion )( 
            IAbout2 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ProviderVersion )( 
            IAbout2 * This,
            /* [defaultvalue][in] */ BSTR ProviderName,
            /* [defaultvalue][in] */ LONG ProviderType,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IAbout2Vtbl;

    interface IAbout2
    {
        CONST_VTBL struct IAbout2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAbout2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAbout2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAbout2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAbout2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAbout2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAbout2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAbout2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAbout2_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IAbout2_get_MajorVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_MajorVersion(This,pVal) ) 

#define IAbout2_get_MinorVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_MinorVersion(This,pVal) ) 

#define IAbout2_get_BuildVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_BuildVersion(This,pVal) ) 


#define IAbout2_ProviderVersion(This,ProviderName,ProviderType,pVal)	\
    ( (This)->lpVtbl -> ProviderVersion(This,ProviderName,ProviderType,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAbout2_INTERFACE_DEFINED__ */


#ifndef __IAbout3_INTERFACE_DEFINED__
#define __IAbout3_INTERFACE_DEFINED__

/* interface IAbout3 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAbout3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("279D1A07-BF79-496E-9B72-9FD1164498BB")
    IAbout3 : public IAbout2
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CSPVersion( 
            /* [defaultvalue][in] */ BSTR ProviderName,
            /* [defaultvalue][in] */ LONG ProviderType,
            /* [retval][out] */ IVersion **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PluginVersion( 
            /* [retval][out] */ IVersion **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAbout3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAbout3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAbout3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAbout3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAbout3 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAbout3 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAbout3 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAbout3 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IAbout3 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MajorVersion )( 
            IAbout3 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinorVersion )( 
            IAbout3 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BuildVersion )( 
            IAbout3 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ProviderVersion )( 
            IAbout3 * This,
            /* [defaultvalue][in] */ BSTR ProviderName,
            /* [defaultvalue][in] */ LONG ProviderType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CSPVersion )( 
            IAbout3 * This,
            /* [defaultvalue][in] */ BSTR ProviderName,
            /* [defaultvalue][in] */ LONG ProviderType,
            /* [retval][out] */ IVersion **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PluginVersion )( 
            IAbout3 * This,
            /* [retval][out] */ IVersion **pVal);
        
        END_INTERFACE
    } IAbout3Vtbl;

    interface IAbout3
    {
        CONST_VTBL struct IAbout3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAbout3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAbout3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAbout3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAbout3_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAbout3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAbout3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAbout3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAbout3_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IAbout3_get_MajorVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_MajorVersion(This,pVal) ) 

#define IAbout3_get_MinorVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_MinorVersion(This,pVal) ) 

#define IAbout3_get_BuildVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_BuildVersion(This,pVal) ) 


#define IAbout3_ProviderVersion(This,ProviderName,ProviderType,pVal)	\
    ( (This)->lpVtbl -> ProviderVersion(This,ProviderName,ProviderType,pVal) ) 


#define IAbout3_CSPVersion(This,ProviderName,ProviderType,pVal)	\
    ( (This)->lpVtbl -> CSPVersion(This,ProviderName,ProviderType,pVal) ) 

#define IAbout3_get_PluginVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_PluginVersion(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAbout3_INTERFACE_DEFINED__ */


#ifndef __IAbout4_INTERFACE_DEFINED__
#define __IAbout4_INTERFACE_DEFINED__

/* interface IAbout4 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAbout4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2FCAA7DB-8C97-4F2E-9BF4-DD586BAF6DE1")
    IAbout4 : public IAbout3
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CSPName( 
            /* [defaultvalue][in] */ LONG ProviderType,
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAbout4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAbout4 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAbout4 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAbout4 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAbout4 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAbout4 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAbout4 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAbout4 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IAbout4 * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MajorVersion )( 
            IAbout4 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MinorVersion )( 
            IAbout4 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BuildVersion )( 
            IAbout4 * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ProviderVersion )( 
            IAbout4 * This,
            /* [defaultvalue][in] */ BSTR ProviderName,
            /* [defaultvalue][in] */ LONG ProviderType,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CSPVersion )( 
            IAbout4 * This,
            /* [defaultvalue][in] */ BSTR ProviderName,
            /* [defaultvalue][in] */ LONG ProviderType,
            /* [retval][out] */ IVersion **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PluginVersion )( 
            IAbout4 * This,
            /* [retval][out] */ IVersion **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CSPName )( 
            IAbout4 * This,
            /* [defaultvalue][in] */ LONG ProviderType,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IAbout4Vtbl;

    interface IAbout4
    {
        CONST_VTBL struct IAbout4Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAbout4_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAbout4_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAbout4_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAbout4_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAbout4_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAbout4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAbout4_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAbout4_get_Version(This,pVal)	\
    ( (This)->lpVtbl -> get_Version(This,pVal) ) 

#define IAbout4_get_MajorVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_MajorVersion(This,pVal) ) 

#define IAbout4_get_MinorVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_MinorVersion(This,pVal) ) 

#define IAbout4_get_BuildVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_BuildVersion(This,pVal) ) 


#define IAbout4_ProviderVersion(This,ProviderName,ProviderType,pVal)	\
    ( (This)->lpVtbl -> ProviderVersion(This,ProviderName,ProviderType,pVal) ) 


#define IAbout4_CSPVersion(This,ProviderName,ProviderType,pVal)	\
    ( (This)->lpVtbl -> CSPVersion(This,ProviderName,ProviderType,pVal) ) 

#define IAbout4_get_PluginVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_PluginVersion(This,pVal) ) 


#define IAbout4_CSPName(This,ProviderType,pVal)	\
    ( (This)->lpVtbl -> CSPName(This,ProviderType,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAbout4_INTERFACE_DEFINED__ */


#ifndef __IWebClassFactory_INTERFACE_DEFINED__
#define __IWebClassFactory_INTERFACE_DEFINED__

/* interface IWebClassFactory */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWebClassFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B37AAD93-8E42-4995-8812-B316ABB8B832")
    IWebClassFactory : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateObject( 
            /* [in] */ BSTR strProgID,
            /* [retval][out] */ IUnknown **ppIUnknown) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWebClassFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWebClassFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWebClassFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWebClassFactory * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWebClassFactory * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWebClassFactory * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWebClassFactory * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWebClassFactory * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateObject )( 
            IWebClassFactory * This,
            /* [in] */ BSTR strProgID,
            /* [retval][out] */ IUnknown **ppIUnknown);
        
        END_INTERFACE
    } IWebClassFactoryVtbl;

    interface IWebClassFactory
    {
        CONST_VTBL struct IWebClassFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebClassFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWebClassFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWebClassFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWebClassFactory_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWebClassFactory_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWebClassFactory_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWebClassFactory_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWebClassFactory_CreateObject(This,strProgID,ppIUnknown)	\
    ( (This)->lpVtbl -> CreateObject(This,strProgID,ppIUnknown) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWebClassFactory_INTERFACE_DEFINED__ */


#ifndef __IPrivateKeyUsageValidator_INTERFACE_DEFINED__
#define __IPrivateKeyUsageValidator_INTERFACE_DEFINED__

/* interface IPrivateKeyUsageValidator */
/* [nonextensible][dual][object][helpstring][uuid] */ 


EXTERN_C const IID IID_IPrivateKeyUsageValidator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("59EDB358-096F-4E09-82E7-4D3C873EF575")
    IPrivateKeyUsageValidator : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsCertValidOnTime( 
            /* [in] */ VARIANT Certificate,
            /* [in] */ DATE DateTime,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsCertValidNow( 
            /* [in] */ VARIANT Certificate,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsChainValid( 
            /* [in] */ VARIANT Chain,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPrivateKeyUsageValidatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPrivateKeyUsageValidator * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPrivateKeyUsageValidator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPrivateKeyUsageValidator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPrivateKeyUsageValidator * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPrivateKeyUsageValidator * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPrivateKeyUsageValidator * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPrivateKeyUsageValidator * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsCertValidOnTime )( 
            IPrivateKeyUsageValidator * This,
            /* [in] */ VARIANT Certificate,
            /* [in] */ DATE DateTime,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsCertValidNow )( 
            IPrivateKeyUsageValidator * This,
            /* [in] */ VARIANT Certificate,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsChainValid )( 
            IPrivateKeyUsageValidator * This,
            /* [in] */ VARIANT Chain,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IPrivateKeyUsageValidatorVtbl;

    interface IPrivateKeyUsageValidator
    {
        CONST_VTBL struct IPrivateKeyUsageValidatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrivateKeyUsageValidator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPrivateKeyUsageValidator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPrivateKeyUsageValidator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPrivateKeyUsageValidator_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPrivateKeyUsageValidator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPrivateKeyUsageValidator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPrivateKeyUsageValidator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPrivateKeyUsageValidator_IsCertValidOnTime(This,Certificate,DateTime,pVal)	\
    ( (This)->lpVtbl -> IsCertValidOnTime(This,Certificate,DateTime,pVal) ) 

#define IPrivateKeyUsageValidator_IsCertValidNow(This,Certificate,pVal)	\
    ( (This)->lpVtbl -> IsCertValidNow(This,Certificate,pVal) ) 

#define IPrivateKeyUsageValidator_IsChainValid(This,Chain,pVal)	\
    ( (This)->lpVtbl -> IsChainValid(This,Chain,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPrivateKeyUsageValidator_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CPAttribute;

#ifdef __cplusplus

class DECLSPEC_UUID("FE98A77F-7D50-4210-AED4-5B2AE2EDAEF1")
CPAttribute;
#endif

EXTERN_C const CLSID CLSID_CPAttributes;

#ifdef __cplusplus

class DECLSPEC_UUID("A3C2F1D9-28B8-4E44-ABF0-2301981195FC")
CPAttributes;
#endif

EXTERN_C const CLSID CLSID_CPSigner;

#ifdef __cplusplus

class DECLSPEC_UUID("94EBF679-1DED-48B9-9FD2-00A3949E0905")
CPSigner;
#endif

EXTERN_C const CLSID CLSID_CPSigners;

#ifdef __cplusplus

class DECLSPEC_UUID("5881EDE0-0497-4E69-AAD2-4FA2AF6401BB")
CPSigners;
#endif

EXTERN_C const CLSID CLSID_CPBlobs;

#ifdef __cplusplus

class DECLSPEC_UUID("A9FAA9E1-4788-4707-8F35-456061F1B0E1")
CPBlobs;
#endif

EXTERN_C const CLSID CLSID_SignatureStatus;

#ifdef __cplusplus

class DECLSPEC_UUID("68219E48-F0C4-424a-91C3-E773C5EC6CAE")
SignatureStatus;
#endif

EXTERN_C const CLSID CLSID_About;

#ifdef __cplusplus

class DECLSPEC_UUID("37B8E018-B072-42df-8B24-CF5C4500BC26")
About;
#endif

EXTERN_C const CLSID CLSID_Version;

#ifdef __cplusplus

class DECLSPEC_UUID("DE50048F-3B39-4237-B783-CAD4D641993E")
Version;
#endif

EXTERN_C const CLSID CLSID_CadesSignedData;

#ifdef __cplusplus

class DECLSPEC_UUID("1264A46A-FDB8-43a3-AEE3-00E1684C98E9")
CadesSignedData;
#endif

EXTERN_C const CLSID CLSID_SignedXML;

#ifdef __cplusplus

class DECLSPEC_UUID("040FFA18-B7D8-4209-92E5-98064AA2CD6B")
SignedXML;
#endif

EXTERN_C const CLSID CLSID_CPEnvelopedData;

#ifdef __cplusplus

class DECLSPEC_UUID("DD8AB7EF-0420-4157-A2BD-31AECE1248AE")
CPEnvelopedData;
#endif

EXTERN_C const CLSID CLSID_CPHashedData;

#ifdef __cplusplus

class DECLSPEC_UUID("84C6A357-A6B3-48E3-BB1A-4DD841825374")
CPHashedData;
#endif

EXTERN_C const CLSID CLSID_RawSignature;

#ifdef __cplusplus

class DECLSPEC_UUID("35A95BE2-952D-4205-8168-417A4FE41724")
RawSignature;
#endif

EXTERN_C const CLSID CLSID_CPCertificate;

#ifdef __cplusplus

class DECLSPEC_UUID("BD9906FE-BDB0-4200-849F-F50A99FBD9D0")
CPCertificate;
#endif

EXTERN_C const CLSID CLSID_SymmetricAlgorithm;

#ifdef __cplusplus

class DECLSPEC_UUID("3C1166D7-6A8A-4D67-9C95-5F1AFCB4099F")
SymmetricAlgorithm;
#endif

EXTERN_C const CLSID CLSID_WebClassFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("B04C8637-10BD-484E-B0DA-B8A039F60024")
WebClassFactory;
#endif

EXTERN_C const CLSID CLSID_PrivateKeyUsageValidator;

#ifdef __cplusplus

class DECLSPEC_UUID("1FDD1FC3-6347-49DF-BDAB-E465BF32AD92")
PrivateKeyUsageValidator;
#endif

EXTERN_C const CLSID CLSID_EnrollPolicyQualifier;

#ifdef __cplusplus

class DECLSPEC_UUID("8C739CED-7D89-4F05-8927-23CF3974DDE6")
EnrollPolicyQualifier;
#endif

EXTERN_C const CLSID CLSID_EnrollPolicyQualifiers;

#ifdef __cplusplus

class DECLSPEC_UUID("26F3BC25-74BF-46CE-A01B-7FD4B8B09A2A")
EnrollPolicyQualifiers;
#endif

EXTERN_C const CLSID CLSID_EnrollCertificatePolicy;

#ifdef __cplusplus

class DECLSPEC_UUID("36A03528-236B-4C4B-86DB-0ACB41224CD8")
EnrollCertificatePolicy;
#endif

EXTERN_C const CLSID CLSID_EnrollCertificatePolicies;

#ifdef __cplusplus

class DECLSPEC_UUID("CD74AB99-24ED-44BF-90AD-23441484006F")
EnrollCertificatePolicies;
#endif

EXTERN_C const CLSID CLSID_EnrollX509ExtensionCertificatePolicies;

#ifdef __cplusplus

class DECLSPEC_UUID("A75C7E87-2340-4993-9E74-4412F72776AE")
EnrollX509ExtensionCertificatePolicies;
#endif

EXTERN_C const CLSID CLSID_CPPrivateKey;

#ifdef __cplusplus

class DECLSPEC_UUID("3C397532-2022-42e7-AF3B-18E0F98A1665")
CPPrivateKey;
#endif

EXTERN_C const CLSID CLSID_CPStore;

#ifdef __cplusplus

class DECLSPEC_UUID("7CBD72D9-76A3-4939-930C-52C4D6CA206B")
CPStore;
#endif

EXTERN_C const CLSID CLSID_EnrollObjectId;

#ifdef __cplusplus

class DECLSPEC_UUID("6C35C17F-F42E-4CB5-BE6B-3B41165464AD")
EnrollObjectId;
#endif

EXTERN_C const CLSID CLSID_EnrollObjectIds;

#ifdef __cplusplus

class DECLSPEC_UUID("76F48E6D-B6C9-41A1-9399-AC635D7E1AC9")
EnrollObjectIds;
#endif

EXTERN_C const CLSID CLSID_EnrollX500DistinguishedName;

#ifdef __cplusplus

class DECLSPEC_UUID("6AE95067-A75D-4283-8E0F-41D799D6CFA2")
EnrollX500DistinguishedName;
#endif

EXTERN_C const CLSID CLSID_EnrollX509PrivateKey;

#ifdef __cplusplus

class DECLSPEC_UUID("5BAC9FA4-D35E-48AA-A82C-34A5EAA55C5E")
EnrollX509PrivateKey;
#endif

EXTERN_C const CLSID CLSID_EnrollX509Extension;

#ifdef __cplusplus

class DECLSPEC_UUID("34AB3DE5-8953-4DF1-AA6B-0A6223BB43CF")
EnrollX509Extension;
#endif

EXTERN_C const CLSID CLSID_EnrollX509Extensions;

#ifdef __cplusplus

class DECLSPEC_UUID("E6AE4BB6-36F8-4512-945C-5508E0DB7EE4")
EnrollX509Extensions;
#endif

EXTERN_C const CLSID CLSID_EnrollCspAlgorithm;

#ifdef __cplusplus

class DECLSPEC_UUID("07D55D4D-37A4-45EB-BA6E-C86DBEF4EBF4")
EnrollCspAlgorithm;
#endif

EXTERN_C const CLSID CLSID_EnrollCspAlgorithms;

#ifdef __cplusplus

class DECLSPEC_UUID("33AFA2F4-D9F8-47A7-B817-DEA12223815E")
EnrollCspAlgorithms;
#endif

EXTERN_C const CLSID CLSID_EnrollCspInformation;

#ifdef __cplusplus

class DECLSPEC_UUID("FA3B709D-3BF9-4158-8E23-B50E802C6E27")
EnrollCspInformation;
#endif

EXTERN_C const CLSID CLSID_EnrollCspInformations;

#ifdef __cplusplus

class DECLSPEC_UUID("2AFDDBB2-4011-432A-BB74-5D4E2CCEF0C0")
EnrollCspInformations;
#endif

EXTERN_C const CLSID CLSID_EnrollCspStatus;

#ifdef __cplusplus

class DECLSPEC_UUID("F9951303-92F2-4010-8429-F598F03F735E")
EnrollCspStatus;
#endif

EXTERN_C const CLSID CLSID_EnrollCspStatuses;

#ifdef __cplusplus

class DECLSPEC_UUID("A27C315B-FB3E-48EB-9572-6929ED9A5D95")
EnrollCspStatuses;
#endif

EXTERN_C const CLSID CLSID_EnrollX509CertificateRequestPkcs10;

#ifdef __cplusplus

class DECLSPEC_UUID("03297942-1BED-486D-A8FC-D264C84107D5")
EnrollX509CertificateRequestPkcs10;
#endif

EXTERN_C const CLSID CLSID_EnrollX509Enrollment;

#ifdef __cplusplus

class DECLSPEC_UUID("D8F0218D-F889-4F93-8482-C3A40C98D67F")
EnrollX509Enrollment;
#endif

EXTERN_C const CLSID CLSID_EnrollX509ExtensionKeyUsage;

#ifdef __cplusplus

class DECLSPEC_UUID("CC9AFA30-3938-49EC-8097-10B65C7EA995")
EnrollX509ExtensionKeyUsage;
#endif

EXTERN_C const CLSID CLSID_EnrollX509ExtensionEnhancedKeyUsage;

#ifdef __cplusplus

class DECLSPEC_UUID("E51DBC75-DC3D-48D2-9E3C-A5B2C6A0DE01")
EnrollX509ExtensionEnhancedKeyUsage;
#endif

EXTERN_C const CLSID CLSID_EnrollX509ExtensionTemplate;

#ifdef __cplusplus

class DECLSPEC_UUID("0C39EE7A-E02D-4CDC-B096-817A5F90B219")
EnrollX509ExtensionTemplate;
#endif

EXTERN_C const CLSID CLSID_UECard;

#ifdef __cplusplus

class DECLSPEC_UUID("62AA1E69-FC04-44e4-B2DD-2F0246F26B79")
UECard;
#endif

EXTERN_C const CLSID CLSID_CardholderData;

#ifdef __cplusplus

class DECLSPEC_UUID("ED793308-C4E5-4b24-8367-22D3DD1E8855")
CardholderData;
#endif

EXTERN_C const CLSID CLSID_PersonalCardholderData;

#ifdef __cplusplus

class DECLSPEC_UUID("71B62DA9-5457-482f-BB02-39E0B53504AE")
PersonalCardholderData;
#endif

EXTERN_C const CLSID CLSID_IdentityCard;

#ifdef __cplusplus

class DECLSPEC_UUID("00C8B4F7-C45C-419b-A3FD-C698DBA3F935")
IdentityCard;
#endif

EXTERN_C const CLSID CLSID_OMSData;

#ifdef __cplusplus

class DECLSPEC_UUID("33C66838-83FC-4CDE-BE5F-326F3E90A99F")
OMSData;
#endif
#endif /* __CAdESCOM_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


