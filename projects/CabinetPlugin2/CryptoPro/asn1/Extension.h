/*
 * Copyright(C) 2004 ������ ���
 *
 * ���� ���� �������� ����������, ����������
 * �������������� �������� ������ ���.
 *
 * ����� ����� ����� ����� �� ����� ���� �����������,
 * ����������, ���������� �� ������ �����,
 * ������������ ��� �������������� ����� ��������,
 * ���������������, �������� �� ���� � ��� ��
 * ����� ������������ ������� ��� ����������������
 * ���������� ���������� � ��������� ������ ���.
 */

/*!
 * \file $RCSfile$
 * \version $Revision: 137732 $
 * \date $Date:: 2016-04-25 14:38:45 +0300#$
 * \author $Author: dim $
 *
 * \brief ������ ����������.
 */

#ifndef _EXTENSION_H_INCLUDED
#define _EXTENSION_H_INCLUDED

#include <cplib/Blob.h>
#include <cplib/DateTime.h>
#include <asn1/Types.h>
#include <memory>		/* Linux/autoptr */

#define sz_id_ad_caIssuers "1.3.6.1.5.5.7.48.2"
#define sz_id_ad_caRepository "1.3.6.1.5.5.7.48.5"
#define sz_id_ce_keyUsage "2.5.29.15"
#define sz_id_ce_privateKeyUsagePeriod "2.5.29.16"
#define sz_id_pe_subjectInfoAccess "1.3.6.1.5.5.7.1.11"
#define sz_id_pkix_ocsp_nocheck "1.3.6.1.5.5.7.48.1.5"
#define sz_id_ce_authorityKeyIdentifier "2.5.29.35"
#define sz_id_ce_issuerAltName "2.5.29.18"
#define sz_id_ce_subjectAltName "2.5.29.17"
#define sz_id_ce_subjectKeyIdentifier "2.5.29.14"
#define sz_id_pe_authorityInfoAccess "1.3.6.1.5.5.7.1.1"
#define sz_id_ce_cRLDistributionPoints "2.5.29.31"
#define sz_id_ce_basicConstraints "2.5.29.19"
#define sz_id_ce_invalidityDate "2.5.29.24"
#define sz_id_ce_certificateIssuer "2.5.29.29"
#define sz_id_ce_reasonCode "2.5.29.21"
#define sz_id_ce_instructionCode "2.5.29.23"

#if !defined CPASN1_DLL_DEFINES
#   define CPASN1_DLL_DEFINES
#   if defined _WIN32 && !defined CRYPTCP && !defined CPASN1_STATIC
#	ifdef CPASN1_DLL
#	    define CPASN1_CLASS __declspec(dllexport)
#	    define CPASN1_API __declspec(dllexport)
#	    define CPASN1_DATA __declspec(dllexport)
#	    define CPASN1_EXTERN_TEMPLATE
#	else // defined CPASN1_DLL
#	    define CPASN1_CLASS __declspec(dllimport)
#	    define CPASN1_API __declspec(dllimport)
#	    define CPASN1_DATA __declspec(dllimport)
#	    define CPASN1_EXTERN_TEMPLATE extern
#	endif // !defined CPASN1_DLL
#   else // defined _WIN32 && !defined CRYPTCP && !defined CPASN1_STATIC
#	define CPASN1_CLASS
#	define CPASN1_API
#	define CPASN1_DATA
#	define CPASN1_EXTERN_TEMPLATE
#       define NO_EXPIMP_CDLLLIST_ITERATORS
#   endif // !defined _WIN32 || defined CRYPTCP || defined CPASN1_STATIC
#endif // !defined CPASN1_DLL_DEFINES

#pragma warning(push)
#pragma warning(disable: 4251)

namespace CryptoPro
{

namespace ASN1
{

/**
 * \class CExtValue Extension.h <asn1/Extension.h>
 * \brief �������� ����������.
 *
 * �������� ��������������� � ASN.1 DER �������� ���������� � ���� 
 * �������� ������������������� � ���� ���������� � ���� OID.
 * \sa CExtension, CExtensions
 */
class CPASN1_CLASS CExtValue
{    
public:
    /// ������� ������ ������
    CExtValue();
    /// ���������� ������
    ~CExtValue();
    /**
     * \brief ������� � �������������� ������
     * \param oid [in] OID, ������������ ��� ����������
     */
    CExtValue (const char * oid);
    /**
     * \brief ������� � �������������� ������
     * \param oid [in] OID, ������������ ��� ����������
     * \param value [in] �������������� ����������
     */
    CExtValue (const char * oid, const CBlob& value);
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CExtValue (const CExtValue& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CExtValue& operator=( const CExtValue& src);
    /// ���������� OID ���������� (ANSI).
    const char * get_oid() const;
    /// ���������� �������������� �������� ����������.
    const CBlob& get_value() const;
protected:
    CBlob& value();
private:
    CStringProxy oid_;
    CBlob value_;
};

/**
 * \class CExtension Extension.h <asn1/Extension.h>
 * \brief ���������� (RFC 3280, ������ 4.1).
 *
 * ��� ���������� ������������ OID'�� (extnID). ��� ���������� ����������
 * ��� �������� ����������. ���������� ����� ���� ��������� ��� �����������.
 * \sa CExtValue, CExtensions
 */
class CPASN1_CLASS CExtension
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������� ����������
     * \param critical [in] ���� ����������� ����������
     */
    CExtension(
	const CExtValue& value, 
	bool critical = false);
    /// ������� ������ ������
    CExtension();
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CExtension(const CExtension& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CExtension& operator=( const CExtension& src);
    /// ���������� ��� ���������� � ���� OID
    const char * get_extnID() const;
    /// ���������� �������������� �������� ����������
    const CBlob& get_extnValue() const;
    /// ���������� ���������� ����������
    bool get_critical() const;
    /**
     * \brief �������� ���������� � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);
private:
    CExtValue value_;
    bool critical_;
};

/// �������� �������� ���������� �� ���������
CPASN1_API extern bool operator==( const CExtension& lhs, const CExtension& rhs);
/// �������� �������� ���������� �� �����������
CPASN1_API extern bool operator!=( const CExtension& lhs, const CExtension& rhs);

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CExtension, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CExtensions Extension.h <asn1/Extension.h>
 * \brief ������ ���������� (RFC 3280, ������ 4.1).
 *
 * \sa CExtValue, CExtension, CDllList
 */
class CPASN1_CLASS CExtensions: public CDllList<CExtension>
{
public:
    /**
     * \brief ������� ���������� ��������� ���� �� ������
     * \param oid [in] OID ���� ����������
     */
    void erase(const char * oid);
    /**
     * \brief ��������� ���������� � ������
     * \param extension [in] ����������� ����������
     */
    void insert(const CExtension& extension);
    /**
     * \brief ������� ���������� � �������� ����� � ������
     * \param oid [in] OID ���� ����������
     * \return ��������, ����������� �� ��������� ������, ���� ��
     * ������� ������ ��������� �� ��������� ���� ������ �� ������.
     */
    iterator find( const char * oid );
    /**
     * \brief ������� ���������� � �������� ����� � ������
     * \param oid [in] OID ���� ����������
     * \return ��������, ����������� �� ��������� ������, ���� ��
     * ������� ������ ��������� �� ��������� ���� ������ �� ������.
     */
    const_iterator find( const char * oid ) const;

    /**
     * \brief �������� ������ ���������� � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);
};

/// �������� �������� �������� �� ���������
CPASN1_API extern bool operator==( const CExtensions& lhs, const CExtensions& rhs);
/// �������� �������� �������� �� �����������
CPASN1_API extern bool operator!=( const CExtensions& lhs, const CExtensions& rhs);

/**
 * \class CExtInvalidityDate Extension.h <asn1/Extension.h>
 * \brief �������� ���������� InvalidityDate (RFC 3280, ������ 5.3.3)
 *
 */
class CPASN1_CLASS CExtInvalidityDate: public CExtValue
{
public:
    /// ������� ������ ������
    CExtInvalidityDate();
    /**
     * \brief ������� � �������������� ������
     * \param invalidityDate [in] �����
     */
    CExtInvalidityDate( 
	const CDateTime& invalidityDate);
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� �������� ����������
     */
    CExtInvalidityDate( const CBlob& value);

    /// ���������� ������
    ~CExtInvalidityDate();

    //get
    /// ���������� ����� ��������� � ��������
    const CDateTime& get_invalidityDate() const;
    /// ������������� �����
    void put_invalidityDate( 
	const CDateTime& invalidityDate);
private:
    CDateTime invalidityDate_;
    void encode();
    void decode();
};

/**
 * \class CExtCertificateIssuer Extension.h <asn1/Extension.h>
 * \brief �������� ���������� CertificateIssuer (RFC 3280, ������ 5.3.4)
 *
 */
class CPASN1_CLASS CExtCertificateIssuer: public CExtValue
{
public:
    /// ������� ������ ������
    CExtCertificateIssuer();
    /**
     * \brief ������� � �������������� ������
     * \param issuer [in] ��� �������� �����������
     */
    CExtCertificateIssuer( 
	const CGeneralNames& issuer);
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� �������� ����������
     */
    CExtCertificateIssuer( const CBlob& value);

    /// ���������� ������
    ~CExtCertificateIssuer();

    //get
    /// ���������� ��� �������� �����������
    const CGeneralNames& get_issuer() const;
    //set
    /// ������������� ��� �������� �����������
    void put_issuer( 
	const CGeneralNames& issuer);
private:
    CGeneralNames issuer_;
    void encode();
    void decode();
};

/// ������� ������ ����������� (RFC 3280, ������ 5.3.1)
enum CrlReason {
	/// �� ���������� ������� ������
    CRLREASON_UNSPECIFIED = 0,
	/// ���������������� ����������
    CRLREASON_KEYCOMPROMISE = 1, 
	/// ����������������� ����� ������������
    CRLREASON_CACOMPROMISE = 2, 
	/// ���������� ��������� � �����������
    CRLREASON_AFFILIATIONCHANGED = 3,
	/// ���������� �������
    CRLREASON_SUPERSEDED = 4, 
	/// ���������� ������ �� ����� ��� ��� ����� ��� ������� ����������
    CRLREASON_CESSATIONOFOPERATION = 5, 
	/// �������� ����������� ��������������
    CRLREASON_CERTIFICATEHOLD = 6, 
	/// ������ ��������� �� CRL (������������ ������ � ���������� CRL)
    CRLREASON_REMOVEFROMCRL = 8,
	/// ����������, �������������� ������ ������������ ���� ��������
    CRLREASON_PRIVILEDGEWITHDRAWN = 9,
	/// ����������������� �����, ����������� ���������� �����������
    CRLREASON_AACOMPROMISE = 10
};

/**
 * \class CExtCRLReason Extension.h <asn1/Extension.h>
 * \brief �������� ���������� CRLReason (RFC 3280, ������ 5.3.1)
 *
 */
class CPASN1_CLASS CExtCRLReason: public CExtValue
{
public:
    /// ������� ������ ������
    CExtCRLReason();
    /**
     * \brief ������� � �������������� ������
     * \param reason [in] ������� ������
     */
    CExtCRLReason(CrlReason reason);
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� �������� ����������
     */
    CExtCRLReason( const CBlob& value);

    /// ���������� ������
    ~CExtCRLReason();

    //get
    /// ���������� ������� ������
    CrlReason get_reason() const;
    //set
    /// ������������� ������� ������
    void put_reason(CrlReason reason);
private:
    CrlReason reason_;
    void encode();
    void decode();
};

// possible code oids
#define sz_id_holdinstruction_none "1.2.840.10040.2.1"
#define sz_id_holdinstruction_callissuer "1.2.840.10040.2.2"
#define sz_id_holdinstruction_reject "1.2.840.10040.2.3"

/**
 * \class CExtHoldInstructionCode Extension.h <asn1/Extension.h>
 * \brief �������� ���������� HoldInstructionCode (RFC 3280, ������ 5.3.2)
 *
 */
class CPASN1_CLASS CExtHoldInstructionCode: public CExtValue
{
public:
    /// ������� ������ ������
    CExtHoldInstructionCode();
    /**
     * \brief ������� � �������������� ������
     * \param code [in] OID ����
     */
    CExtHoldInstructionCode( 
	const char * code);
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� �������� ����������
     */
    CExtHoldInstructionCode( const CBlob& value);

    /// ���������� ������
    ~CExtHoldInstructionCode();

    /// ���������� OID ����
    const char * get_code() const;
    /// ������������� OID ����
    void put_code( 
	const char * code);
private:
    CStringProxy code_;
    void encode();
    void decode();
};

/**
 * \class CExtPrivateKeyUsagePeriod Extension.h <asn1/Extension.h>
 * \brief �������� ���������� PrivateKeyUsagePeriod (RFC 3280, ������ 4.2.1.4)
 *
 */
class CPASN1_CLASS CExtPrivateKeyUsagePeriod: public CExtValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param notBefore [in] ����� ������ �������� ��������� �����
     * \param notAfter [in] ����� ��������� �������� ��������� �����
     */
    CExtPrivateKeyUsagePeriod( 
	const CDateTime *notBefore = 0, const CDateTime *notAfter = 0);
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� �������� ����������
     */
    CExtPrivateKeyUsagePeriod( const CBlob& value);

    /// ���������� ������
    ~CExtPrivateKeyUsagePeriod();

    /// ���������� ���� notBefore
    const CDateTime *get_notBefore() const;
    /// ���������� ���� notAfter
    const CDateTime *get_notAfter() const;
    /// ������������� ���� notBefore
    void put_notBefore( const CDateTime* notBefore);
    /// ������������� ���� notAfter
    void put_notAfter( const CDateTime* notAfter);
private:
    CExtPrivateKeyUsagePeriod( const CExtPrivateKeyUsagePeriod& );
    CExtPrivateKeyUsagePeriod& operator=( const CExtPrivateKeyUsagePeriod&);
    
    std::auto_ptr<CDateTime> notBefore_;
    std::auto_ptr<CDateTime> notAfter_;
    void encode();
    void decode();
};

} // namespace ASN1
} // namespace CryptoPro

#pragma warning(pop)

#endif // _EXTENSION_H_INCLUDED
