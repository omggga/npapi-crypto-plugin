#ifndef _ALGIDEX_H_INCLUDED
#define _ALGIDEX_H_INCLUDED

#if !defined UNIX
#   include <windows.h>
#   include <wincrypt.h>
#endif	/* !UNIX */

#include <asn1/Types.h>

namespace CryptoPro {
namespace ASN1 {

/**
 * \brief ������������� ��������� � ����������� ALG_ID
 * 
 * ������ ����� ��������� � ��������� ������ CAlgorithmIdentifier
 * ������� ��������� ALG_ID. ��� ���������� ALG_ID ������� Crypto API
 * ���������� ������ ���� ���, ����� ���� ���������� �������� ����������
 * ������ ������� �� ��� ���, ���� �� �� ����� �������. 
 *
 * \sa CAlgorithmIdentifier
 */
class CAlgorithmIdentifierEx: public ASN1::CAlgorithmIdentifier
{
public:
    /// ������� ������ ������
    CAlgorithmIdentifierEx();
    /**
     * \brief ������� � �������������� ������
     * \param algorithm [in] OID ���������
     */
    CAlgorithmIdentifierEx( const char *algorithm);
    /**
    * \brief ������� ����� ��������� �������.
    *
    * \param src [in] ������, ����� �������� ���������
    */
    CAlgorithmIdentifierEx( const CAlgorithmIdentifierEx &src );
    /**
    * \brief ������� ����� ��������� �������.
    *
    * \param src [in] ������, ����� �������� ���������
    */
    CAlgorithmIdentifierEx( const CAlgorithmIdentifier &src );
    /**
    * \brief �������� �������� ������ � �������.
    *
    * \param src [in] ������, ������� ���������� � �������
    */
    CAlgorithmIdentifierEx &operator=( const CAlgorithmIdentifierEx& src );
    /**
    * \brief �������� �������� ������ � �������.
    *
    * \param src [in] ������, ������� ���������� � �������
    */
    CAlgorithmIdentifierEx &operator=( const CAlgorithmIdentifier& src );
    /**
    * \brief �������� ������ ��������.
    *
    * \param src [in] ������ ��� ������
    * \remarks ������� �� ���������� ����������.
    */
    void swap( CAlgorithmIdentifierEx &src ) throw();

    /// ���������� ALG_ID, �������������� �������� �������������� ���������
    ALG_ID get_AlgId() const;
    /// ������������� OID ���������
    void put_algorithm( const char * algorithm);

    /// �������� ��������������� ���������� �� ���������
    bool operator==( const CAlgorithmIdentifierEx& right ) const;
    /// �������� ��������������� ���������� �� �����������
    bool operator!= ( const CAlgorithmIdentifierEx& right ) const;
private:
    mutable ALG_ID cachedAlgId_;
};

} // namespace ASN1
} // namespace CryptoPro

#include "algidex.inl"

#endif // _ALGIDEX_H_INCLUDED
