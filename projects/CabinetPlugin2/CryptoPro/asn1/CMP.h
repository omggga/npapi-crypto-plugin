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
 * \version $Revision: 133488 $
 * \date $Date:: 2016-01-28 15:30:20 +0300#$
 * \author $Author: cross $
 *
 * \brief ������ � ��������� ������������ �� PKIXCMP.
 */

#ifndef _ASN1CMP_H_INCLUDED
#define _ASN1CMP_H_INCLUDED

#include <cplib/Blob.h>
#include <cplib/DateTime.h>
#include <asn1/Extension.h>
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

class CPKIFreeText;

/// ��������� ������� ��������� ��������� (RFC 2510, ������ 3.2.3)
enum PKIStatusEnum {
    /// ��������� �������� �� ��� �����������
    PKI_STATUS_GRANTED,
    /// ��������� �������� �� ��� ����������� � �����������
    PKI_STATUS_GRANTEDWITHMODS,
    /// ����� � �������������� ������ (�������� ����� ���� ������� � ������ �����)
    PKI_STATUS_REJECTION,
    /// ������ ��� ��� ��������������
    PKI_STATUS_WAITING,
    /// �������������� � ����������� ������
    PKI_STATUS_REVOCATIONWARNING,
    /// �������������� � ������������ ������
    PKI_STATUS_REVOCATIONNOTIFICATION,
    /// ��� ���� ����������� ����� ����� ��� ����������� ���������� � ������� �� ����� �����
    PKI_STATUS_KEYUPDATEWARNING
};

class CRevAnnContentImpl;
/**
 * \class CRevAnnContent CMP.h <asn1/CMP.h>
 * \brief ASN.1 ��������� RevAnnContent (RFC 2510, ������ 3.3.15).
 *
 * �������� � ���� ����� ������ �����������.
 *
 */
class CPASN1_CLASS CRevAnnContent
{
public:
    /// ������� ������ ������
    CRevAnnContent();
    /**
     * \brief ������� � �������������� ������
     * \param status [in] ���� status
     * \param certId [in] ���� certId
     * \param willBeRevokedAt [in] ���� willBeRevokedAt
     * \param badSinceDate [in] ���� badSinceDate
     */
    CRevAnnContent(
	const PKIStatusEnum& status,
	const CCertId& certId,
	const CDateTime& willBeRevokedAt,
	const CDateTime& badSinceDate);
    /// ���������� ������
    ~CRevAnnContent();
    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CRevAnnContent( const CRevAnnContent& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CRevAnnContent& operator=( const CRevAnnContent& src);
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
    /// ��������� ���� status
    const PKIStatusEnum& get_status() const;
    /// ��������� ���� certId
    const CCertId& get_certId() const;
    /// ��������� ���� willBeRevokedAt
    const CDateTime& get_willBeRevokedAt() const;
    /// ��������� ���� badSinceDate
    const CDateTime& get_badSinceDate() const;
    /// ��������� ������������� ���� crlDetails
    const CExtensions* get_crlDetails() const;
    // set
    /// ��������� ���� status
    void put_status(const PKIStatusEnum& status);
    /// ��������� ���� certId
    void put_certId(const CCertId& certId);
    /// ��������� ���� willBeRevokedAt
    void put_willBeRevokedAt(const CDateTime& willBeRevokedAt);
    /// ��������� ���� badSinceDate
    void put_badSinceDate( const CDateTime& badSinceDate);
    /// ��������� ������������� ���� crlDetails
    void put_crlDetails( const CExtensions* crlDetails);
private:
    CRevAnnContentImpl *pImpl_;
};

/**
 * \class CPKIFailureInfo CMP.h <asn1/CMP.h>
 * \brief ASN.1 ������� ������ (BIT STRING) PKIFailureInfo (RFC 2510, ������ 3.2.2).
 *
 * ������������ ��� �������� �������������� ���������� �
 * ������������ �������.
 * \sa CPKIStatusInfo, PKIStatusEnum
 */
class CPASN1_CLASS CPKIFailureInfo
{
public:
    /// ����������� ��� �������� ������ ���� � ���� failureInfo � ��������� PKIStatusInfo
    enum Bit {
        /// ����������� ��� ���������������� ������������� ���������
	badAlg = 0,
	/// �� ������ �������� ����������� ��������� (�������� �� ����������� �������)
	badMessageCheck = 1,
	/// ���������� ��������� ��� �� ��������������
	badRequest = 2,
	/// ����� (���� messageTime) ������������ ������ � ���������� ������� (������������ ��������� ���������)
	badTime = 3,
	/// �� ������ ���������� ��������������� ��������� ��������������
	badCertId = 4,
	/// ���������� ������ ���� ������������� �������
	badDataFormat = 5,
	/// ��������� � ������ ��� ��������������� ������ ��� ������� �� ��������� � �����������
	wrongAuthority = 6,
        // the requester's data is incorrect (used for notary services)
	/// ������ � ������� ����������� (������������ � ������������ ��������)
	incorrectData = 7,
	/// ����������� ������������ ����� ������� (�������������� ����� ��������� ���������)
	missingTimeStamp = 8,
	/// �� �������� ����� ��������� ������
	badPOP = 9,
        /// �������� ������� ������ ������� ������� ���������� 
	timeNotAvailable = 14,
	/// ������������� �������� ������ ������� ������� �� ��������������
	unacceptedPolicy = 15,
	/// ������������� ���������� �� �������������� ������� ������� �������
	unacceptedExtension = 16,
	/// ������������� �������������� ���������� ��������� ��� ����������
	addInfoNotAvailable = 17,
	/// ������ �� ����� ���� ��������� ��-�� ��������� ������
	systemFailure = 25
    };

    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������� ������� ������
     */
    CPKIFailureInfo( unsigned value = 0);
    
    /// ���������� ������
    ~CPKIFailureInfo();

    /**
    * \brief ������� ����� ��������� �������.
    * \param src [in] ������, ����� �������� ���������
    */
    CPKIFailureInfo( const CPKIFailureInfo& src);
    /**
    * \brief �������� �������� ������ � �������.
    * \param src [in] ������, ������� ���������� � �������
    * \return ������ �� ������� ������.
    */
    CPKIFailureInfo& operator=( const CPKIFailureInfo& src);

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

    /// ���������� �������� ������� ������
    unsigned get_value() const;
    /// ������������� �������� ������� ������
    void put_value( unsigned value);
    /**
     * \brief ���������� �������� ��������� ����
     * \param bitNumber [in] ����� ����
     */
    bool get_bit( unsigned bitNumber ) const;
    /**
     * \brief ������������� �������� ��������� ����
     * \param bitNumber [in] ����� ����
     * \param value [in] ��������������� ��������
     */
    void put_bit( unsigned bitNumber, bool value );
private:
    unsigned value_;
};

/// �������� �� ���������
CPASN1_API bool operator==(
    const CPKIFailureInfo& lhs, const CPKIFailureInfo& rhs);
/// �������� �� �����������
CPASN1_API bool operator!=(
    const CPKIFailureInfo& lhs, const CPKIFailureInfo& rhs);

/**
 * \class CLanguageTag CMP.h <asn1/CMP.h>
 * \brief ���, ������������ ������������ ���� (RFC 1766).
 *
 * ���� ��� ������ ��������� � ������ ������ ��������� PKIFreeText (RFC 2510 ������ 3.1.1)
 * \sa CPKIFreeText, CPKIStatusInfo, PKIStatusEnum
 */
class CPASN1_CLASS CLanguageTag
{
public:
    /// ������� ������ ������
    CLanguageTag();
    /**
     * \brief ������� � �������������� ������
     * \param tag [in] ��������� ������������� ��������� ����
     */
    explicit CLanguageTag( const char *tag );
    /**
     * \brief ������� � �������������� ������
     * \param tag [in] ��������� ������������� ��������� ����
     */
    explicit CLanguageTag( const wchar_t *tag );
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CLanguageTag( const CLanguageTag &src );
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CLanguageTag& operator=( const CLanguageTag &src );

    /// ���������� ��������� �������� ����
    CStringProxy tostring() const;

    /// ��������� ������� �� ���������
    bool operator==( const CLanguageTag &rhs ) const;
    /// ��������� ������� �� �����������
    bool operator!=( const CLanguageTag &rhs ) const;
private:
    CStringProxy tag_;
    static std::string normalize( const char *ptr );
    void assign( const CLanguageTag &right );
};

/**
 * \class CLanguageTagRuRu CMP.h <asn1/CMP.h>
 * \brief ���, ������������ ������� ���� (ru-RU) (RFC 1766).
 *
 * \sa CLanguageTag
 */
class CPASN1_CLASS CLanguageTagRuRu: public CLanguageTag
{
public:
    /// ������� ������.
    CLanguageTagRuRu();
};

/**
 * \class CLanguageTagEnUs CMP.h <asn1/CMP.h>
 * \brief ���, ������������ ���������� ���� (en-US) (RFC 1766).
 *
 * \sa CLanguageTag
 */
class CPASN1_CLASS CLanguageTagEnUs: public CLanguageTag
{
public:
    /// ������� ������.
    CLanguageTagEnUs();
};

/**
 * \class CLanguageTagDefaultRead CMP.h <asn1/CMP.h>
 * \brief ��� �� ��������� ��� ������ (*) (RFC 1766).
 *
 * \sa CLanguageTag
 */
class CPASN1_CLASS CLanguageTagDefaultRead: public CLanguageTag
{
public:
    CLanguageTagDefaultRead();
};

/// ��� �� ��������� ��� ������, ��������� ��� CLanguageTagRuRu
typedef CLanguageTagRuRu CLanguageTagDefaultWrite;

/**
 * \class CPKIFreeTextString CMP.h <asn1/CMP.h>
 * \brief ������ �� ������ ��������� PKIFreeText.
 *
 * \sa CLanguageTag, CPKIFreeText
 */
class CPASN1_CLASS CPKIFreeTextString
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param tag [in] ������������ ����
     */
    CPKIFreeTextString( CLanguageTag tag = CLanguageTagDefaultWrite() );
    /**
     * \brief ������� � �������������� ������
     * \param str [in] �������� ������
     * \param tag [in] ������������ ����
     */
    CPKIFreeTextString( const wchar_t *str, CLanguageTag tag = CLanguageTagDefaultWrite() );
    /**
     * \brief ������� � �������������� ������
     * \param str [in] �������� ������
     * \param tag [in] ������������ ����
     */
    CPKIFreeTextString( const char* str, CLanguageTag tag = CLanguageTagDefaultWrite() );
    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CPKIFreeTextString( const CPKIFreeTextString& src );
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CPKIFreeTextString& operator=( const CPKIFreeTextString& src );

    /// ���������� ���� ������
    const CLanguageTag& get_language() const;
    /// ���������� �������� ������
    const wchar_t * get_value() const;

    /// ������������� �������� ������
    void set_value( const wchar_t * value);

    /// ��������� ������� �� ���������
    bool operator==( const CPKIFreeTextString &right ) const;
    /// ��������� ������� �� �����������
    bool operator!=( const CPKIFreeTextString &right ) const;
private:
    CWStringProxy value_;
    CLanguageTag tag_;
    void assign( const CPKIFreeTextString& right );
};

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CPKIFreeTextString, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CPKIFreeText CMP.h <asn1/CMP.h>
 * \brief ASN.1 ��������� PKIFreeText (RFC 2510, ������ 3.1.1).
 *
 * \sa CPKIStatusInfo, CPKIFreeTextString, CDllList
 */
class CPASN1_CLASS CPKIFreeText: public CDllList<CPKIFreeTextString>
{
public:
    /// ������� ������ ������
    CPKIFreeText();
    /**
     * \brief ������� ������ � �������������� ��� ����� �������
     * \param text [in] ����� ������
     * \param tag [in] ���� ������
     */
    CPKIFreeText( const wchar_t *text, CLanguageTag tag = CLanguageTagDefaultWrite() );
    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CPKIFreeText( const CPKIFreeTextString &src );
    /// ��������� ���������� ������� � ���� CPKIFreeTextString
    operator CPKIFreeTextString();
    /// ��������� ���������� ������� � ���� CPKIFreeTextString
    operator const CPKIFreeTextString&() const;
    /**
     * \brief ������� ������ � �������� �������� �����
     * \param tag [in] �������� ���
     * \return ��������, ����������� �� ��������� ������, ���� ��
     * ������� ������ ��������� �� ��������� ���� ������ �� ������.
     */
    const_iterator find( CLanguageTag tag = CLanguageTagDefaultRead() ) const;
    /**
     * \brief ������� ������ � �������� �������� �����
     * \param tag [in] �������� ���
     * \return ��������, ����������� �� ��������� ������, ���� ��
     * ������� ������ ��������� �� ��������� ���� ������ �� ������.
     */
    iterator find( CLanguageTag tag = CLanguageTagDefaultRead() );
    /**
     * \brief ������� ������ � �������� �������� �����
     * \param tag [in] �������� ���
     */
    void remove( const CLanguageTag& tag );
    /**
     * \brief ��������� ����� ������
     * \param str [in] ����������� ������
     */
    void insert( const CPKIFreeTextString &str );
};

/**
 * \class CPKIStatusInfo CMP.h <asn1/CMP.h>
 * \brief ASN.1 ��������� PKIStatusInfo (RFC 2510, ������ 3.2.3).
 *
 * ������������ ��� �������� ���������� � ������� � ������� ��
 * �������.
 *
 * \sa CPKIStatusEnum, CPKIFailureInfo, CPKIFreeText
 */
class CPASN1_CLASS CPKIStatusInfo
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param pkiStatus [in] ���� pkiStatus
     */
    CPKIStatusInfo( PKIStatusEnum pkiStatus = PKI_STATUS_REJECTION );
    /// ���������� ������
    ~CPKIStatusInfo();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CPKIStatusInfo( const CPKIStatusInfo& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CPKIStatusInfo& operator=( const CPKIStatusInfo& src);

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
    void decode( const CBlob&	d);

    //get
    /// ���������� ���� pkiStatus
    PKIStatusEnum get_pkiStatus() const;
    /// ���������� ���� failureInfo
    const CPKIFailureInfo& get_failureInfo() const;
    /// ���������� ���� statusString
    const CPKIFreeText& get_statusString() const;
    //set
    /// ������������� ���� pkiStatus
    void put_pkiStatus( PKIStatusEnum pkiStatus);
    /// ������������� ���� failureInfo
    void put_failureInfo( const CPKIFailureInfo& failureInfo);
    /// ������������� ���� statusString
    void put_statusString( const CPKIFreeText& statusString);
private:
    PKIStatusEnum pkiStatus_;
    CPKIFailureInfo failureInfo_;
    CPKIFreeText statusString_;
};

/**
 * \class CInfoTypeAndValue CMP.h <asn1/CMP.h>
 * \brief ASN.1 ��������� InfoTypeAndValue (RFC 2510, ������ 3.3.18).
 *
 * ������������ ��� �������� �������������� ����������.
 * \sa CInfoTypeAndValueList
 */
class CPASN1_CLASS CInfoTypeAndValue
{
public:
    /// ������� ������ ������
    CInfoTypeAndValue();
    /// ���������� ������
    ~CInfoTypeAndValue();
    /**
     * \brief ������� � �������������� ������
     * \param type [in] OID ���� ��������
     */
    CInfoTypeAndValue( const char * type );
    /**
     * \brief ������� � �������������� ������
     * \param type [in] OID ���� ��������
     * \param value [in] ������������� ��������
     */
    CInfoTypeAndValue( const char * type, const CBlob& value );
    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CInfoTypeAndValue( const CInfoTypeAndValue &src );
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CInfoTypeAndValue& operator=( const CInfoTypeAndValue &src );
    /// ���������� ���� infoType (OID ���� ��������)
    const char * get_infoType() const;
    /// ���������� �������������� ��������
    const CBlob& get_infoValue() const;
    /// ��������� ������� �� ���������
    bool operator==( const CInfoTypeAndValue &right ) const;
    /// ��������� ������� �� �����������
    bool operator!=( const CInfoTypeAndValue &right ) const;
private:
    CStringProxy type_;
    CBlob value_;
};

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CInfoTypeAndValue, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CInfoTypeAndValueList CMP.h <asn1/CMP.h>
 * \brief ������ �������� �InfoTypeAndValue.
 *
 * \sa CInfoTypeAndValue, CDllList
 */
class CPASN1_CLASS CInfoTypeAndValueList: public CDllList<CInfoTypeAndValue>
{
public:
    /**
     * \brief ������� ������ � ������ � ��������� ����� ��������
     * \param type [in] OID ���� ��������
     * \return ��������, ����������� �� ��������� ������, ���� ��
     * ������� ������ ��������� �� ��������� ���� ������ �� ������.
     */
    iterator find( const char *type );
    /**
     * \brief ������� ������ � ������ � ��������� ����� ��������
     * \param type [in] OID ���� ��������
     * \return ��������, ����������� �� ��������� ������, ���� ��
     * ������� ������ ��������� �� ��������� ���� ������ �� ������.
     */
    const_iterator find( const char *type ) const;
    /**
     * \brief ������� ��� ������� �� ���������� ��������� ���� �� ������
     * \param type [in] OID ���� ��������
     */
    void remove( const char *type );
    /**
     * \brief ��������� ����� ������ � ������
     * \param typeAndValue [in] ����������� ������
     */
    void insert( const CInfoTypeAndValue &typeAndValue );
};

/**
 * \class CReasonFlags CMP.h <asn1/CMP.h>
 * \brief ASN.1 ������� ������ (BIT STRING) ReasonFlags (RFC 3280, ������ 3.2.2).
 *
 * ������������ ��� �������� ������ ������ ������������.
 */
class CPASN1_CLASS CReasonFlags
{
public:
    /// ����� ������ ������
    enum Flag
    {
	/// �� ���������� ������� ������
	unspecified = 0x01, //(0)
	/// ���������������� ����������
	keyCompromise = 0x02, //(1)
	/// ����������������� ����� ������������
	caCompromise = 0x04, //(2)
	/// ���������� ��������� � �����������
	affiliationChanged = 0x08, //(3)
	/// ���������� �������
	superseded = 0x10, //(4)
	/// ���������� ������ �� ����� ��� ��� ����� ��� ������� ����������
	cessationOfOperation = 0x20, //(5)
	/// �������� ����������� ��������������
	certificateHold = 0x40, //(6)
	/// ����������, �������������� ������ ������������ ���� ��������
	privilegeWithdrawn = 0x80, //(7)
	/// ����������������� �����, ����������� ���������� �����������
	aACompromise = 0x100 //(8)
    };
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������� ������� ������
     */
    CReasonFlags( unsigned value = 0);

    /// ���������� �������� ������� ������
    unsigned get_value() const;
    /// ������������� �������� ������� ������
    void put_value( unsigned value);
    /**
     * \brief ���������� �������� ��������� ����
     * \param bitNumber [in] ����� ����
     */
    bool get_bit( unsigned bitNumber ) const;
    /**
     * \brief ������������� �������� ��������� ����
     * \param bitNumber [in] ����� ����
     * \param value [in] ��������������� ��������
     */
    void put_bit( unsigned bitNumber, bool value );
    /**
     * \brief ������������� ����
     * \param flag [in] ��������������� ����
     */
    void add_flag( Flag flag );
    /**
     * \brief ������� ����
     * \param flag [in] ��������� ����
     */
    void remove_flag( Flag flag );
    /**
     * \brief ���������, ���������� ���� ��� ���
     * \param flag [in] ����������� ����
     */
    bool get_flag( Flag flag ) const;
private:
    static unsigned sequence[9];
    unsigned value_;
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==(
    const CReasonFlags& lhs,
    const CReasonFlags& rhs );
/// ��������� ������� �� �����������
CPASN1_API bool operator!=(
    const CReasonFlags& lhs,
    const CReasonFlags& rhs );

} // namespace ASN1

} // namespace CryptoPro

#pragma warning(pop)

#endif // _ASN1CMP_H_INCLUDED
