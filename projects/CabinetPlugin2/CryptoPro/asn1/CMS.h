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
 * \version $Revision: 132852 $
 * \date $Date:: 2016-01-12 15:12:28 +0300#$
 * \author $Author: denisenko $
 *
 * \brief ������ � ��������� ����������� � CMS (Cryptographic Message Syntax).
 */

#ifndef _CMS_H_INCLUDED
#define _CMS_H_INCLUDED

#include <cplib/Blob.h>
#include <asn1/Types.h>

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
 * \class CContentInfo CMS.h <asn1/CMS.h>
 * \brief ASN.1 ��������� ContentInfo ( RFC 3369 ������ 3 )
 * 
 * \remark ������� ���������, ��� ������������ � ContentInfo ����������
 * ������ ��������������� ��������� ����. ��������, � ������ ���� ����������
 * data (szOID_RSA_data), ��������� ������ ���� ������� ������� (OCTET STRING)
 */
class CPASN1_CLASS CContentInfo
{
public:
    /// ������� ������ ������
    CContentInfo();
    /**
     * \brief ������� � �������������� ������
     * \param contentType [in] OID ���� �����������
     * \param content [in] ����������
     */
    CContentInfo( const char * contentType,
	const CBlob& content = CBlob());
    /// ���������� ������
    ~CContentInfo();

    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CContentInfo( const CContentInfo& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CContentInfo& operator=( const CContentInfo& src);

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
    /// ���������� OID ���� �����������
    const char * get_contentType() const;
    /// ���������� �������������� �������� ������������� �����������
    const CBlob& get_content() const;
    //set
    /// ������������� OID ���� �����������
    void put_contentType( const char * contentType);
    /// ������������� �������������� �������� ������������� �����������
    void put_content( const CBlob& content);
private:
    CStringProxy contentType_;
    CBlob content_;
};

/**
 * \class CSignerInfo CMS.h <asn1/CMS.h>
 * \brief ASN.1 �������� SignerInfo (RFC 3369 5.1)
 *
 * ��������� SignerInfo �������� ������ ���������� ������������
 * CMS ���������.
 */
class CPASN1_CLASS CSignerInfo
{
public:
    /// ������� ������ ������
    CSignerInfo();
    /// ���������� ������
    ~CSignerInfo();

    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CSignerInfo( const CSignerInfo& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CSignerInfo& operator=( const CSignerInfo& src);

    // get
    /// ���������� ������ �������
    unsigned get_version() const;
    /// ���������� �������������� ��� (Name) �������� ����������� ����������
    const CBlob& get_issuer() const;
    /// ���������� �������� ����� ����������� ����������
    const CBigInteger& get_serialNumber() const;
    /// ���������� �������� �������
    const CAlgorithmIdentifier& get_signatureAlgorithm() const;
    /// ���������� �������� ����
    const CAlgorithmIdentifier& get_digestAlgorithm() const;
    /// ���������� �������� �������� �������
    const CBlob& get_signature() const;
    // set
    /// ������������� ������ �������
    void put_version( unsigned version);
    /// ������������� �������������� ��� (Name) �������� ����������� ����������
    void put_issuer( const CBlob& issuer);
    /// ������������� �������� ����� ����������� ����������
    void put_serialNumber( const CBigInteger& serialNumber);
    /// ������������� �������� �������
    void put_signatureAlgorithm(
	const CAlgorithmIdentifier& signatureAlgorithm);
    /// ������������� �������� ����
    void put_digestAlgorithm(
	const CAlgorithmIdentifier& digestAlgorithm);
    /// ������������� �������� �������� �������
    void put_signature( const CBlob& signature);
private:
    unsigned version_;
    CBlob issuer_;
    CBigInteger serialNumber_;
    CAlgorithmIdentifier signatureAlgorithm_;
    CAlgorithmIdentifier digestAlgorithm_;
    CBlob signature_;
};

/// ��������� ��������� SignerInfo �� ���������
CPASN1_API bool operator==( const CSignerInfo& lhs, const CSignerInfo& rhs);
/// ��������� ��������� SignerInfo �� �����������
CPASN1_API bool operator!=( const CSignerInfo& lhs, const CSignerInfo& rhs);

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CSignerInfo, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CSignerInfoList CMS.h <asn1/CMS.h>
 * \brief ������ �������� CSignerInfo
 * \sa CSignerInfo, CDllList
 */
class CSignerInfoList: public CDllList<CSignerInfo>
{
};

} // namespace ASN1

} // namespace CryptoPro

#pragma warning(pop)

#endif // _CMS_H_INCLUDED
