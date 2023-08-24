/*
 * Copyright(C) 2003 ������ ���
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
 * \version $Revision: 160633 $
 * \date $Date:: 2017-07-19 19:27:05 +0300#$
 * \author $Author: xmv $
 *
 * \brief ������ � ��������� ��� ASN.1 �����.
 */

#ifndef _ASN1TYPES_H
#define _ASN1TYPES_H

#include <string>
#if !defined UNIX
#   include <windows.h>
#endif	/* !UNIX */
#include <cplib/Blob.h>
#include <cplib/DateTime.h>
#include <asn1/Attribute.h>

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

class CReasonFlags;

/**
 * \brief ���������, �������� �� ������ OID'��.
 *
 * \param str [in] ����������� ������
 * \return � ������ ���� ������ �������� OID'�� ������������
 * true, � ��������� ������ - false.
 */
CPASN1_API bool isOID( const char * str);

/**
 * \class CBigInteger Types.h <asn1/Types.h>
 * \brief ������� ����� ����������� �����.
 *
 * ����� ������������ ��� �������� ������� ����� ����������� �����, ���
 * ������, ����� �������� ����������� ����� �� ������� (��������, ���
 * �������� ��������� ������)
 *
 * \sa CBlob
 */
class CPASN1_CLASS CBigInteger : public CBlob
{
public:
    /// ������� ������ ������
    CBigInteger();
    /**
     * \brief ������� � �������������� �����
     *
     * \param ptr [in] ��������� �� ������ ������ ���������� � �����
     * \param length [in] ����� ������ � ������
     * \remarks ��� ������������� ������ ������� ������ ��� ��������
     * ������ � �������� �� ���� �� ���������� � ��������� ptr �����.
     */
    CBigInteger(const unsigned char *ptr, unsigned long length );
    /**
     * \brief ������� ������
     *
     * \param length [in] ����� ����� � ������
     * \remarks ��� ������������� ������ ������� ��������� ���������� ������
     * ��� �����.
     */
    CBigInteger( unsigned long length );
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CBigInteger( const CBigInteger &src );
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CBigInteger& operator=( const CBigInteger& src);
    /// ���������� ������
    ~CBigInteger();

    /**
     * \brief �������� ����� � ASN.1 DER �������������
     *
     * \return ������ CBlob ���������� �������� ������������������.
     */
    CBlob encode() const;
    /**
     * \brief ���������� ����� �� ASN.1 DER �������������
     *
     * \param encoded [in] ������ CBlob ���������� �������� ������������������.
     */
    void decode( const CBlob& encoded);

    /**
     * \brief ����������� �������� ����� �� �������
     *
     * \param start [in] ����� �����, ������� � �������� ���������
     * ��������� (����� � �������� �� 0 �� start-1 ������ ��������
     * �����������)
     */
    void increment( int start = 0);
    /**
    * \brief ��������� � ����� ������ �����
    * 
    * \return ���� �������� ������������, ���������� �������� 
    * ���������������� �������� �����.
    * \remark ����� ������ ���� ���������� �����
    */
    unsigned char add( const CBigInteger& v);
    /// ���������� �������� ���������� 
    CBigInteger& operator++();
    /// ����������� �������� ����������
    CBigInteger operator++(int);
    /// ���������� �������� ����� �� ������
    CBigInteger abs() const;

    CPASN1_API friend bool operator==( const CBigInteger& lhs, const CBigInteger& rhs);
    CPASN1_API friend bool operator!=( const CBigInteger& lhs, const CBigInteger& rhs);
    CPASN1_API friend bool operator<( const CBigInteger& lhs, const CBigInteger& rhs);
    CPASN1_API friend bool operator>( const CBigInteger& lhs, const CBigInteger& rhs);
    CPASN1_API friend bool operator<=( const CBigInteger& lhs, const CBigInteger& rhs);
    CPASN1_API friend bool operator>=( const CBigInteger& lhs, const CBigInteger& rhs);
private:
    int compare( const CBigInteger& rhs) const;
};

/// �������� �� ���������
CPASN1_API bool operator==( const CBigInteger& lhs, const CBigInteger& rhs);
/// �������� �� �����������
CPASN1_API bool operator!=( const CBigInteger& lhs, const CBigInteger& rhs);
/// �������� "������"
CPASN1_API bool operator<( const CBigInteger& lhs, const CBigInteger& rhs);
/// �������� "������"
CPASN1_API bool operator>( const CBigInteger& lhs, const CBigInteger& rhs);
/// �������� "������ ��� �����"
CPASN1_API bool operator<=( const CBigInteger& lhs, const CBigInteger& rhs);
/// �������� "������ ��� �����"
CPASN1_API bool operator>=( const CBigInteger& lhs, const CBigInteger& rhs);

/**
 * \class CAlgorithmIdentifier Types.h <asn1/Types.h>
 * \brief ������������� ��������� (RFC 3280, ������ 4.1.1.2)
 *
 * ������������� ������� �� ���� ����� - OID ��������� �
 * ���������. ����, ���������� ���������, ����������� � ���
 * ���������� ������� �� ���� ���������.
 */
class CPASN1_CLASS CAlgorithmIdentifier
{
public:
    /// ������� ������ ������
    CAlgorithmIdentifier();
    /**
     * \brief ������� � �������������� ������
     * \param algorithm [in] OID ���������
     */
    CAlgorithmIdentifier( const char * algorithm);
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CAlgorithmIdentifier( const CAlgorithmIdentifier &src );
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CAlgorithmIdentifier &operator=( const CAlgorithmIdentifier &src );
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     */
    void assign( const CAlgorithmIdentifier &src );
    /// ���������� ������
    virtual ~CAlgorithmIdentifier();
    /**
    * \brief �������� ������ ��������.
    *
    * \param src [in] ������ ��� ������
    * \remarks ������� �� ���������� ����������.
    */
    void swap( CAlgorithmIdentifier &src ) throw();

    /// ���������� OID ���������
    const char * get_algorithm() const;
    /// ���������� �������������� ��������� ��������� (�������� ������)
    const CBlob& get_parameters() const;
    /// ������������� OID ���������
    virtual void put_algorithm( const char * algorithm);
    /// ������������� ��������� ��������� (�������� ������)
    void put_parameters( const CBlob& parameters);
    /// �������� ��������������� ���������� �� ���������
    bool operator==( const CAlgorithmIdentifier &right ) const;
    /// �������� ��������������� ���������� �� �����������
    bool operator!= ( const CAlgorithmIdentifier &right ) const;
    /**
     * \brief �������� ������������� ��������� � ������� ASN.1 DER � ����������
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
    CStringProxy algorithm_;
    CBlob parameters_;
};

class CGeneralNameImpl;
/**
 * \class CGeneralName Types.h <asn1/Types.h>
 * \brief ��������� ASN.1 GeneralName (RFC 3280, ������ 4.2.1.7)
 *
 * ��������� GeneralName ����� ��������� ���� �� ���������� ����� ��������.
 * ��� ��������� �������� ���� ��������� ��������������� ������� get_() ���, 
 * ������� �� ���� �����, ������������ ���������. ���� ���������, ������������
 * ��������, ����� ����, �� � ��������� ���������� �������� ����, ��������� �� ����,
 * ������� ���������� ������ �������. ������ ��� ��������, ����������� � ���������
 * ����� � ������� ������� get_type()
 */
class CPASN1_CLASS CGeneralName
{
public:
    /// ���� ��������� �������� (RFC 3280, ������ 4.2.1.7)
    enum Type
    {
//	t_otherName = 1,
	t_rfc822Name = 2,
	t_dNSName = 3,
//	t_x400Address = 4,
	t_directoryName = 5,
//	t_ediPartyName = 6,
	t_uniformResourceIdentifier = 7,
	t_iPAddress = 8,
	t_registeredID = 9
    };
public:
    /// ������� ������ ������
    CGeneralName();
    /// ���������� ������
    ~CGeneralName();

    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CGeneralName( const CGeneralName& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CGeneralName& operator=( const CGeneralName& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    // get
    /// ���������� ��� ��������
    Type get_type() const;
    /// ���������� rfc822Name
    const wchar_t *get_rfc822Name() const;
    /// ���������� dNSName
    const wchar_t *get_dNSName() const;
    /// ���������� directoryName
    const CBlob* get_directoryName() const;
    /// ���������� uniformResourceIdentifier
    const wchar_t *get_uniformResourceIdentifier() const;
    /// ���������� iPAddress
    const CBlob* get_iPAddress() const;
    /// ���������� registeredID
    const wchar_t *get_registeredID() const;
    // set
    /// ������������� rfc822Name
    void put_rfc822Name( const wchar_t * rfc822Name);
    /// ������������� dNSName
    void put_dNSName( const wchar_t * dNSName);
    /// ������������� directoryName
    void put_directoryName( const CBlob& directoryName);
    /// ������������� uniformResourceIdentifier
    void put_uniformResourceIdentifier( 
	const wchar_t * uniformResourceIdentifier);
    /// ������������� iPAddress
    void put_iPAddress( const CBlob& iPAddress);
    /// ������������� registeredID
    void put_registeredID( const wchar_t * registeredID);
    /// ���������� ��������� ������������� �������
    CWStringProxy toString() const;
private:
    void clear();
    CGeneralNameImpl* pImpl_;
};

/// �������� �� ��������� �������� GeneralName
CPASN1_API bool operator==( const CGeneralName& lhs, const CGeneralName& rhs);
/// �������� �� ����������� �������� GeneralName
CPASN1_API bool operator!=( const CGeneralName& lhs, const CGeneralName& rhs);

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CGeneralName, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CGeneralNames Types.h <asn1/Types.h>
 * \brief ������ �������� GeneralName
 * \sa CGeneralName, CDllList
 */
class CPASN1_CLASS CGeneralNames: public CDllList<CGeneralName>
{
#ifdef _WIN32
    friend CPASN1_API bool operator==( const CGeneralNames& lhs, const CGeneralNames& rhs);
#endif
};
#ifdef _WIN32
/// �������� �� ��������� ������ �������� GeneralName
CPASN1_API bool operator==( const CGeneralNames& lhs, const CGeneralNames& rhs);
/// �������� �� ����������� ������ �������� GeneralName
CPASN1_API bool operator!=( const CGeneralNames& lhs, const CGeneralNames& rhs);
#endif 

/**
 * \class CPolicyInformation Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� PolicyInformation (RFC 3280)
 *
 * ��������� �������� ���������� � ��������
 * \sa CPolicyInformationList
 */
class CPASN1_CLASS CPolicyInformation
{
public:
     /// ������� ������ ������
    CPolicyInformation();
    /**
     * \brief ������� � �������������� ������
     * \param policyIdentifier [in] ���� policyIdentifier (OID)
     */
    CPolicyInformation( const char * policyIdentifier);
    /// ���������� ������
    ~CPolicyInformation();

    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CPolicyInformation( const CPolicyInformation& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CPolicyInformation& operator=( const CPolicyInformation& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    //get
    /// ���������� ���� policyIdentifier
    const char * get_policyIdentifier() const;
    //set
    /// ������������� ���� policyIdentifier
    void put_policyIdentifier( const char * policyIdentifier);
private:
    CStringProxy policyIdentifier_;
};

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CPolicyInformation, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CPolicyInformationList Types.h <asn1/Types.h>
 * \brief ������ �������� �PolicyInformation.
 *
 * \sa CPolicyInformation, CDllList
 */
class CPASN1_CLASS CPolicyInformationList: public CDllList<CPolicyInformation>
{
};

/**
 * \class CIssuerSerial Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� IssuerSerial (RFC 2634, ������ 5.4.1).
 *
 * ��������� �������� � ���� ��� �������� (���� issuer) � ��������
 * ����� (���� serialNumber).
 * \sa CESSCertID, COtherCertID
 */
class CPASN1_CLASS CIssuerSerial
{
public:
    /// ������� ������ ������
    CIssuerSerial();
    /**
     * \brief ������� � �������������� ������
     * \param issuer [in] ���� issuer
     * \param serialNumber [in] ���� serialNumber
     */
    CIssuerSerial(
	const CGeneralNames& issuer,
	const CBigInteger& serialNumber);
    /// ���������� ������
    ~CIssuerSerial();

    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CIssuerSerial( const CIssuerSerial& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CIssuerSerial& operator=( const CIssuerSerial& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    //get
    /// ���������� ���� issuer
    const CGeneralNames& get_issuer() const;
    /// ���������� ���� serialNumber
    const CBigInteger& get_serialNumber() const;
    //set
    /// ������������� ���� issuer
    void put_issuer( const CGeneralNames& issuer);
    /// ������������� ���� serialNumber
    void put_serialNumber( const CBigInteger& serialNumber);
private:
    CGeneralNames issuer_;
    CBigInteger serialNumber_;
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==( const CIssuerSerial& lhs, const CIssuerSerial& rhs);
/// ��������� ������� �� �����������
CPASN1_API bool operator!=( const CIssuerSerial& lhs, const CIssuerSerial& rhs);

class CESSCertIDImpl;
/**
 * \class CESSCertID Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� ESSCertID (RFC 2634, ������ 5.4.1).
 *
 * ��������� ������ ��������������� �����������. Ÿ ������������
 * ���� (certHash) �������� SHA1 ��� ����� ��������������� �����������.
 * ������������ ���� issuerSerial ����� �������� ����� ��� ��������
 * � �������� ����� �����������.
 * \sa CIssuerSerial, COtherCertID, CESSCertIDList
 */
class CPASN1_CLASS CESSCertID
{
public:
    /// ������� ������ ������
    CESSCertID();
    /**
     * \brief ������� � �������������� ������
     * \param certHash [in] ���� certHash
     */
    CESSCertID( const CBlob& certHash);
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CESSCertID( const CESSCertID& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CESSCertID& operator=( const CESSCertID& src);

    /// ���������� ������
    ~CESSCertID();

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    // get
    /// ���������� ���� certHash
    const CBlob& get_certHash() const;
    /// ���������� ������������ ���� issuerSerial
    const CIssuerSerial* get_issuerSerial() const;
    // set
    /// ������������� ���� certHash
    void put_certHash( const CBlob& certHash);
    /// ������������� ������������ ���� issuerSerial
    void put_issuerSerial( const CIssuerSerial* issuerSerial);
private:
    CESSCertIDImpl *pImpl_;
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==( const CESSCertID& lhs, const CESSCertID& rhs);
/// ��������� ������� �� �����������
CPASN1_API bool operator!=( const CESSCertID& lhs, const CESSCertID& rhs);

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CESSCertID, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \brief ������ �������� CESSCertID.
 *
 * \sa CESSCertID, CDllList
 */
class CPASN1_CLASS CESSCertIDList: public CDllList<CESSCertID>
{
};

class CESSCertIDv2Impl;
/**
 * \class CESSCertIDv2 Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� ESSCertID (RFC 5035, ������ 4).
 *
 * ��������� ������ ��������������� �����������. Ÿ ������������
 * ���� (certHash) �������� ��� ����� ��������������� �����������.
 * ���� hashAlgorithm �������� �������� �����������. ����
 * ��� ���� �� ��������, ��������������� �������� ���� SHA 256.
 * ������������ ���� issuerSerial ����� �������� ����� ��� ��������
 * � �������� ����� �����������.
 * \sa CIssuerSerial, COtherCertID, CCertID, CESSCertIDv2List
 */
class CPASN1_CLASS CESSCertIDv2
{
public:
    /// ������� ������ ������
    CESSCertIDv2();
    /**
     * \brief ������� � �������������� ������ (�������� ���� �� ��������� SHA 256)
     * \param certHash [in] ���� certHash
     */
    CESSCertIDv2( const CBlob& certHash);
    /**
     * \brief ������� � �������������� ������
     * \param certHash [in] ���� certHash
     * \param hashAlgorithm [in] ���� hashAlgorithm
     */
    CESSCertIDv2( const CBlob& certHash, const CAlgorithmIdentifier& hashAlgorithm );
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CESSCertIDv2( const CESSCertIDv2& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CESSCertIDv2& operator=( const CESSCertIDv2& src);

    /// ���������� ������
    ~CESSCertIDv2();

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    // get
    /// ���������� ���� hashAlgorithm
    const CAlgorithmIdentifier& get_hashAlgorithm() const;
    /// ���������� ���� certHash
    const CBlob& get_certHash() const;
    /// ���������� ������������ ���� issuerSerial
    const CIssuerSerial* get_issuerSerial() const;
    // set
    /// ������������� ���� hashAlgorithm
    void put_hashAlgorithm( const CAlgorithmIdentifier& hashAlgorithm);
    /// ������������� ���� certHash
    void put_certHash( const CBlob& certHash);
    /// ������������� ������������ ���� issuerSerial
    void put_issuerSerial( const CIssuerSerial* issuerSerial);
private:
    CESSCertIDv2Impl *pImpl_;
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==( const CESSCertIDv2& lhs, const CESSCertIDv2& rhs);
/// ��������� ������� �� �����������
CPASN1_API bool operator!=( const CESSCertIDv2& lhs, const CESSCertIDv2& rhs);

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CESSCertIDv2, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \brief ������ �������� CESSCertIDv2.
 *
 * \sa CESSCertIDv2, CDllList
 */
class CPASN1_CLASS CESSCertIDv2List: public CDllList<CESSCertIDv2>
{
};

/**
 * \class COtherHashAlgAndValue Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� OtherHashAlgAndValue (RFC 3126, ������ 3.8.2).
 *
 * �������� ���� (���� hashAlgorithm) � ��� �������� (���� hashValue)
 * \sa COtherCertID, COtherHash
 */
class CPASN1_CLASS COtherHashAlgAndValue
{
public:
    /// ������� ������ ������
    COtherHashAlgAndValue();
    /**
     * \brief ������� � �������������� ������
     * \param hashValue [in] ���� hashValue
     * \param hashAlgorithm [in] ���� hashAlgorithm
     */
    COtherHashAlgAndValue(
	const CBlob& hashValue,
	const CAlgorithmIdentifier& hashAlgorithm);	
    /// ���������� ������
    ~COtherHashAlgAndValue();

    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    COtherHashAlgAndValue(
	const COtherHashAlgAndValue& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    COtherHashAlgAndValue& operator=( 
	const COtherHashAlgAndValue& src);

    /**
    * \brief ���������� �������� ������ � ������� �� ���� hashValue
    *
    * \param value [in] ������, ������� ������������ � �������
    * \return ��������� ���������.
    */
    bool compare_hashValue(
        const COtherHashAlgAndValue& value) const;

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    //get
    /// ���������� ���� hashAlgorithm
    const CAlgorithmIdentifier& get_hashAlgorithm() const;
    /// ���������� ���� hashValue
    const CBlob& get_hashValue() const;
    //set
    /// ������������� ���� hashAlgorithm
    void put_hashAlgorithm( 
	const CAlgorithmIdentifier& hashAlgorithm);
    /// ������������� ���� hashValue
    void put_hashValue( const CBlob& hashValue);
private:
    CAlgorithmIdentifier hashAlgorithm_;
    CBlob hashValue_;
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==( 
    const COtherHashAlgAndValue& lhs, const COtherHashAlgAndValue& rhs);
/// ��������� ������� �� �����������
CPASN1_API bool operator!=(
    const COtherHashAlgAndValue& lhs, const COtherHashAlgAndValue& rhs);

class COtherHashImpl;

/**
 * \class COtherHash Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� OtherHash (RFC 3126, ������ 3.8.2).
 *
 * ����� ��������� ���� SHA1 ��� (��� sha1Hash), ����
 * ������������ ��� (��� otherHash).
 * \sa COtherCertID, COtherHashAlgAndValue
 */
class CPASN1_CLASS COtherHash
{
public:
    /// ��� �����������
    enum Type
    {
	/// SHA1 ���
	t_sha1Hash = 1,
	/// ������������ ���
	t_otherHash = 2
    };
public:
    /// ������� ������ ������
    COtherHash();
    /**
     * \brief ������� � �������������� ������
     * \param sha1Hash [in] SHA1 ���
     */
    explicit COtherHash( const CBlob& sha1Hash);
    /**
     * \brief ������� � �������������� ������
     * \param otherHash [in] ������������ ���
     */
    explicit COtherHash( const COtherHashAlgAndValue& otherHash);
    /// ���������� ������
    virtual ~COtherHash();
    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    COtherHash( const COtherHash& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    COtherHash& operator=( const COtherHash& src);
    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    /**
    * \brief ���������� �������� ������ � ������� �� ����� sha1Hash � otherHash
    * ��� ����� ���������� ��������� �����������.
    * \param value [in] ������, ������� ������������ � �������
    * \return ��������� ���������.
    */
    bool compare_hashValue(const COtherHash& value) const;

    // get
    /// ���������� ��� �����������
    Type get_type() const;
    /// ���������� sha1Hash, ���� �� ���������� � ���������, ����� 0
    const CBlob* get_sha1Hash() const;
    /// ���������� otherHash, ���� �� ���������� � ���������, ����� 0
    const COtherHashAlgAndValue* get_otherHash() const;
    // set
    /// ������������� ��� � �������� ����������� sha1Hash
    void put_sha1Hash( const CBlob& sha1Hash);
    /// ������������� ��� � �������� ����������� otherHash
    void put_otherHash( const COtherHashAlgAndValue& otherHash);
private:
    void clear();
    COtherHashImpl* pImpl_;
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==( const COtherHash& lhs, const COtherHash& rhs);
/// ��������� ������� �� �����������
CPASN1_API bool operator!=( const COtherHash& lhs, const COtherHash& rhs);

class COtherCertIDImpl;
/**
 * \class COtherCertID Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� OtherCertID (RFC 3126, ������ 3.8.2).
 *
 * ��������� ������ ��������������� �����������. Ÿ ������������
 * ���� (otherCertHash) �������� SHA1 ��� ������������ ��� 
 * ����� ��������������� �����������.
 * ������������ ���� issuerSerial ����� �������� ����� ��� ��������
 * � �������� ����� �����������.
 * \sa CESSCertID, COtherHash, CIssuerSerial
 */
class CPASN1_CLASS COtherCertID
{
public:
    /// ������� ������ ������
    COtherCertID();
    /**
     * \brief ������� � �������������� ������ SHA1 �����
     * \param sha1Hash [in] SHA1 ���
     */
    COtherCertID( const CBlob& sha1Hash);
    /**
     * \brief ������� � �������������� ������ ������������ �����
     * \param hashValue [in] �������� ����
     * \param hashAlgorithm [in] �������� ����
     */
    COtherCertID( 
	const CBlob& hashValue,
	const CAlgorithmIdentifier& hashAlgorithm);

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    COtherCertID( const COtherCertID& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    COtherCertID& operator=( const COtherCertID& src);

    /// ���������� ������
    ~COtherCertID();

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    /**
    * \brief ���������� �������� ������ � ������� ��� ����� ���������� ��������� �����������
    *
    * \param value [in] ������, ������� ������������ � �������
    * \return ��������� ���������.
    */
    bool compare_noHashParam(const COtherCertID& value) const;

    // get
    /// ���������� ���� otherCertHash
    const COtherHash& get_otherCertHash() const;
    /// ���������� ���� issuerSerial
    const CIssuerSerial* get_issuerSerial() const;
    // set
    /// ������������� ���� otherCertHash
    void put_otherCertHash( const COtherHash& otherCertHash);
    /// ������������� ���� issuerSerial
    void put_issuerSerial( const CIssuerSerial* issuerSerial);
private:
    COtherCertIDImpl *pImpl_;
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==( const COtherCertID& lhs, const COtherCertID& rhs);
/// ��������� ������� �� �����������
CPASN1_API bool operator!=( const COtherCertID& lhs, const COtherCertID& rhs);

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(COtherCertID, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class COtherCertIDList Types.h <asn1/Types.h>
 * \brief ������ �������� CESSCertID.
 *
 * \sa COtherCertID, CDllList
 */
class CPASN1_CLASS COtherCertIDList: public CDllList<COtherCertID>
{
};

class CDistributionPointNameImpl;

/**
 * \class CDistributionPointName Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� DistributionPointName (RFC 3280, ������ 4.2.1.14).
 *
 * ��� ����� ��������������� CRL. ����� ������ ���� ���
 * �����������, �� � ���������� �������� ���������� ������ �����.
 * \sa CDistributionPoint
 */
class CPASN1_CLASS CDistributionPointName
{
public:
    /// ���� �����������
    enum Type
    {
	/// ������ ���
	t_fullName = 1
    };
public:
    /// ������� ������ ������
    CDistributionPointName();
    /**
     * \brief ������� � �������������� ������ ����� fullName
     * \param fullName [in] ������ ���
     */
    CDistributionPointName( const CGeneralNames& fullName);
    /// ���������� ������
    ~CDistributionPointName();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CDistributionPointName( const CDistributionPointName& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CDistributionPointName& operator=( const CDistributionPointName& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    // get
    /// ���������� ��� ��������� ��������
    Type get_type() const;
    /// ���������� fullName, ���� �� ���������� � ���������, ����� 0
    const CGeneralNames* get_fullName() const;
    // set
    /// ������������� ��� � �������� ����������� fullName
    void put_fullName( const CGeneralNames& fullName);
private:
    void clear();
    CDistributionPointNameImpl* pImpl_;
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==(
    const CDistributionPointName& lhs,
    const CDistributionPointName& rhs );
/// ��������� ������� �� �����������
CPASN1_API bool operator!=(
    const CDistributionPointName& lhs,
    const CDistributionPointName& rhs );

class CDistributionPointImpl;

/**
 * \class CDistributionPoint Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� DistributionPoint (RFC 3280, ������ 4.2.1.14).
 *
 * ����� ��������������� CRL.
 * \sa CDistributionPointList, CCRLDistPointsSyntax
 */
class CPASN1_CLASS CDistributionPoint
{
public:
    /// ������� ������ ������
    CDistributionPoint();
    /// ���������� ������
    ~CDistributionPoint();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CDistributionPoint( const CDistributionPoint& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CDistributionPoint& operator=( const CDistributionPoint& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    // get
    /// ���������� ������������ ���� distributionPoint
    const CDistributionPointName* get_distributionPoint() const;
    /// ���������� ������������ ���� reasons
    const CReasonFlags* get_reasons() const;
    /// ���������� ������������ ���� cRLIssuer
    const CGeneralNames* get_cRLIssuer() const;
    // set
    /// ������������� ������������ ���� distributionPoint
    void put_distributionPoint( 
	const CDistributionPointName* distributionPoint);
    /// ������������� ������������ ���� reasons
    void put_reasons( const CReasonFlags* reasons);
    /// ������������� ������������ ���� cRLIssuer
    void put_cRLIssuer( const CGeneralNames* cRLIssuer);
private:
    void clear();
    CDistributionPointImpl* pImpl_;
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==(
    const CDistributionPoint& lhs,
    const CDistributionPoint& rhs );
/// ��������� ������� �� �����������
CPASN1_API bool operator!=(
    const CDistributionPoint& lhs,
    const CDistributionPoint& rhs );

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CDistributionPoint, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CCRLDistPointsSyntax Types.h <asn1/Types.h>
 * \brief ������ ����� ��������������� CRL.
 *
 * \sa CDistributionPoint, CDllList
 */
class CPASN1_CLASS CCRLDistPointsSyntax: public CDllList<CDistributionPoint>
{
#ifdef _WIN32
    friend CPASN1_API bool operator==(
	const CCRLDistPointsSyntax& lhs,
	const CCRLDistPointsSyntax& rhs );
#endif
};
#ifdef  _WIN32
/// ��������� ������� �� ���������
CPASN1_API bool operator==(
    const CCRLDistPointsSyntax& lhs,
    const CCRLDistPointsSyntax& rhs );
/// ��������� ������� �� �����������
CPASN1_API bool operator!=(
    const CCRLDistPointsSyntax& lhs,
    const CCRLDistPointsSyntax& rhs );
#endif

/**
 * \struct CCertId Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� CertId (RFC 2511, ������ 6.5)
 * 
 * ������������� �����������.
 * \sa CRevAnnContent
 */
struct CPASN1_CLASS CCertId
{
    /// �������� �����������
    CGeneralName issuer;
    /// �������� ����� �����������
    CBigInteger serialNumber;
};

/**
 * \brief ����������� �������� ������������������ � ������ ������� (OCTET STRING)
 * \param blob [in] �������� ������������������
 * \return �������������� � ASN.1 DER ������ �������
 */
CPASN1_API CBlob toOctetString( const CBlob& blob);
/**
 * \brief ������������� �������� ������������������ �� ������ ������� (OCTET STRING)
 * \param blob [in] �������������� � ASN.1 DER ������ �������
 * \return �������� ������������������ ����������� �� �������������� ������ �������
 */
CPASN1_API CBlob fromOctetString( const CBlob& blob);

/**
 * \class CAccessDescription Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� AccessDescription (RFC 3280, ������ 4.2.2.1).
 *
 * ������ ������� � ���������� � ������ ������������
 * \sa CAuthorityInfoAccessSyntax
 */
class CPASN1_CLASS CAccessDescription
{
public:
    /// ������� ������ ������
    CAccessDescription();
    /**
     * \brief ������� � �������������� ������
     * \param accessMethod [in] ���� accessMethod
     * \param accessLocation [in] ���� accessLocation
     */
    CAccessDescription(
	const char * accessMethod,
	const CGeneralName& accessLocation);
    /// ���������� ������
    ~CAccessDescription();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CAccessDescription( const CAccessDescription& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CAccessDescription& operator=( const CAccessDescription& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    //get
    /// ���������� ���� accessMethod
    const char * get_accessMethod() const;
    /// ���������� ���� accessLocation
    const CGeneralName& get_accessLocation() const;
    //set
    /// ������������� ���� accessMethod
    void put_accessMethod( const char * accessMethod);
    /// ������������� ���� accessLocation
    void put_accessLocation( const CGeneralName& accessLocation); 
private:
    CStringProxy accessMethod_;
    CGeneralName accessLocation_;
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==( const CAccessDescription& lhs, const CAccessDescription& rhs);
/// ��������� ������� �� �����������
CPASN1_API bool operator!=( const CAccessDescription& lhs, const CAccessDescription& rhs);

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CAccessDescription, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CAuthorityInfoAccessSyntax Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� AuthorityInfoAccessSyntax (RFC 3280, ������ 4.2.2.1).
 *
 * ������ �������� CAccessDescription.
 * \sa CAccessDescription
 */
class CPASN1_CLASS CAuthorityInfoAccessSyntax: public CDllList<CAccessDescription>
{
public:
    /**
    * \brief �������� ������ � ������� ASN.1 DER � ����������
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

class CTimeChoiceImpl;
/**
 * \class CTimeChoice Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� Time (RFC 3280, ������ 4.1).
 *
 * ����� ����� ���� ������������ ����� ������ - utcTime �
 * generalizedTime. ������� �� 2049 ���� ������������ ��������������
 * � ���� utcTime, ����� 2049 ���� - � ���� generalizedTime.
 * \sa CDateTime
 */
class CPASN1_CLASS CTimeChoice
{
public:
    /// ��� �����������
    enum Type
    {
	/// ��� utcTime
	t_utcTime = 1,
	/// ��� generalizedTime
	t_generalTime = 2
    };
public:
    /// ������� ������ ������
    CTimeChoice();
    /**
     * \brief ������� � �������������� ������
     * \param time [in] �����
     */
    CTimeChoice( const CDateTime& time);
    /// ���������� ������
    ~CTimeChoice();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CTimeChoice( const CTimeChoice& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CTimeChoice& operator=( const CTimeChoice& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    // get
    /// ���������� ��� �������
    Type get_type() const;
    /// ���������� �����
    const CDateTime& get_time() const;
    // set
    /// ������������� �����
    void put_time( const CDateTime& time);
private:
    void clear();
    CTimeChoiceImpl* pImpl_;
};

/**
 * \class CRelativeDistinguishedName Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� RelativeDistinguishedName (RFC 3280, ������ 4.1.2.4).
 *
 * \sa CAttributeTypeAndValueSet, CName, CRDNSequence
 */
class CPASN1_CLASS CRelativeDistinguishedName: public CAttributeTypeAndValueSet
{
public:
    /// ������� ������ ������
    CRelativeDistinguishedName();
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� RDN (�������� "CN=Ivan Ivanov+E=ivan@empty.com")
     */
    CRelativeDistinguishedName( const wchar_t * str);

    /// ���������� ��������� ������������� RDN
    CWStringProxy toString() const;
    /// �������������� ������ �� ���������� ������������� RDN
    void fromString( const wchar_t * str);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    friend CPASN1_API bool operator==(
	const CRelativeDistinguishedName& lhs,
	const CRelativeDistinguishedName& rhs );
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==(
    const CRelativeDistinguishedName& lhs,
    const CRelativeDistinguishedName& rhs );
/// ��������� ������� �� �����������
CPASN1_API bool operator!=(
    const CRelativeDistinguishedName& lhs,
    const CRelativeDistinguishedName& rhs );

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CRelativeDistinguishedName, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CRDNSequence Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� RDNSequence (RFC 3280, ������ 4.1.2.4).
 *
 * \sa CAttributeTypeAndValueSet, CName, �RelativeDistinguishedName, CDllList
 */
class CPASN1_CLASS CRDNSequence: public CDllList<CRelativeDistinguishedName>
{
};

/**
 * \class CName Types.h <asn1/Types.h>
 * \brief ASN.1 ��������� Name (RFC 3280, ������ 4.1.2.4).
 *
 * ��� ��������.
 * \sa CAttributeTypeAndValueSet, CRDNSequence, �RelativeDistinguishedName, CDllList
 */
class CPASN1_CLASS CName: public CRDNSequence
{
public:
    /// ������� ������ ������
    CName();
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ����� ("CN=Ivan Ivanov,E=ivan@empty.com,O=Org,C=RU")
     */
    CName( const wchar_t * str);

    /// ���������� ��������� ������������� �����
    CWStringProxy toString() const;
    /// �������������� ������ �� ���������� ������������� �����
    void fromString( const wchar_t * str);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
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

} // namespace ASN1

} // namespace CryptoPro

#pragma warning(pop)

#endif // _ASN1TYPES_H
