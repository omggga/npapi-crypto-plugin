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
 * \version $Revision: 127051 $
 * \date $Date:: 2015-09-09 15:08:20 +0300#$
 * \author $Author: pav $
 *
 * \brief ������-������� ��� �����
 */

#ifndef _STRINGPROXY_H_INCLUDED
#define _STRINGPROXY_H_INCLUDED

#if !defined CPLIB_DLL_DEFINES
#   define CPLIB_DLL_DEFINES
#   if defined _WIN32 && !defined CRYPTCP && !defined CPLIB_STATIC
#	if defined CPLIB_DLL
#	    define CPLIB_CLASS __declspec(dllexport)
#	    define CPLIB_API __declspec(dllexport)
#	    define CPLIB_DATA __declspec(dllexport)
#	    define CPLIB_EXTERN_TEMPLATE
#	else // defined CPLIB_DLL
#	    define CPLIB_CLASS __declspec(dllimport)
#	    define CPLIB_API __declspec(dllimport)
#	    define CPLIB_DATA __declspec(dllimport)
#	    define CPLIB_EXTERN_TEMPLATE extern
#	endif // !defined CPLIB_DLL
#   else // defined _WIN32 && !defined CRYPTCP && !defined CPLIB_STATIC
#	define CPLIB_CLASS
#	define CPLIB_API
#	define CPLIB_DATA
#	define CPLIB_EXTERN_TEMPLATE
#       define NO_EXPIMP_CDLLLIST_ITERATORS
#   endif // !defined _WIN32 || defined CRYPTCP || defined CPLIB_STATIC
#endif // !defined CPLIB_DLL_DEFINES

#include <string>
#ifndef wstring 
namespace std {
    typedef basic_string<wchar_t> wstring;
    }
#endif //wstring

#include <cpstldll.h>

namespace CryptoPro {

/**
 * \class CStringProxy StringProxy.h <cplib/StringProxy.h>
 * \brief ������-��������� ��� �����.
 *
 * � �������� ����� ������ ������� �������� � ������������
 * ���� CryptoPro ���������� ANSI ������. ���� ����� ������ - ����������
 * ��������� ������������ ������, ���������� ��� ������ (������ ��������� ������
 * ������������ ����������, � ������������� ������ ��� ��).
 *
 * ��� ������� ������������� ������� �� ������������ ���� CryptoPro
 * ��� ������������� ��������������� ������������ ���� �����. � ������
 * ������������� ������� \link CryptoPro::CStringProxy::c_str c_str() \endlink, 
 * ������������ ��������� �� c-������ ( �� �������� � std::string ).
 * ������ ����������� ������������� �������, ������������ ������
 * ������ CStringProxy:
 *
 * \code
 * 
 * CStringProxy f();
 *
 * std::string s = f().c_str();
 * CString atls = f().c_str();
 *
 * \endcode
 * 
 * ����������� ������������ ���� ����� ��������� �������:
 *
 * \code
 * const char* s = f().c_str();
 * \endcode
 *
 * ���������� ������ �� ������� ��������� s ����� ������������, ���������
 * f() ���������� ��������� ������, ������� ������������ ����� �������� ��
 * �������. ��������� ��� ���������:
 *
 * \code
 * 
 * // ��������� �����
 * size_t len = strlen(f());
 *
 * // ��������� ������ ��� ������
 * const char* s = (char*)malloc(len+1);
 * if(!s)
 *     error("not enough memory");
 *
 * // ��������� ������ � ����������� � ���������� ������
 * strncpy(s,f(),len+1);
 *
 * \endcode
 *
 * \sa CWStringProxy
 */
class CPLIB_CLASS 
CStringProxy
{
public:
    /**
     * \brief ������� � �������������� ������
     *
     * \param str [in] ��������� �� ������ ��������
     */
    CStringProxy( const char* str = "");
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CStringProxy( const CStringProxy& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CStringProxy& operator=( const CStringProxy& src);
    /// ���������� ������.
    ~CStringProxy();

    /// �������� ������ � ���� const char*
    const char* c_str() const;
private:
#pragma warning(push)
#pragma warning(disable: 4251)
    std::string *m_pValue;
#pragma warning(pop)
};

/**
 * \class CWStringProxy StringProxy.h <cplib/StringProxy.h>
 * \brief ������-��������� ��� �����.
 *
 * � �������� ����� ������ ������� �������� � ������������
 * ���� CryptoPro ���������� UNICODE ������. ���� ����� ������ - ����������
 * ��������� ������������ ������, ���������� ��� ������ (������ ��������� ������
 * ������������ ����������, � ������������� ������ ��� ��).
 *
 * ��� ������� ������������� ������� �� ������������ ���� CryptoPro
 * ��� ������������� ��������������� ������������ ���� �����. � ������
 * ������������� ������� \link CryptoPro::CStringProxy::c_str c_str() \endlink, 
 * ������������ ��������� �� c-������ ( �� �������� � std::wstring ).
 * ������ ����������� ������������� �������, ������������ ������
 * ������ CWStringProxy:
 *
 * \code
 * 
 * CWStringProxy f();
 *
 * std::wstring s = f().c_str();
 * CString atls = f().c_str();
 *
 * \endcode
 * 
 * ����������� ������������ ���� ����� ��������� �������:
 *
 * \code
 * const wchar_t* s = f().c_str();
 * \endcode
 *
 * ���������� ������ �� ������� ��������� s ����� ������������, ���������
 * f() ���������� ��������� ������, ������� ������������ ����� �������� ��
 * �������. ��������� ��� ���������:
 *
 * \code
 * 
 * // ��������� �����
 * size_t len = wcslen(f());
 *
 * // ��������� ������ ��� ������
 * const char* s = (char*)malloc((len+1)*sizeof(wchar_t));
 * if(!s)
 *     error("not enough memory");
 *
 * // ��������� ������ � ����������� � ���������� ������
 * wcsncpy(s,f(),len+1);
 *
 * \endcode
 *
 * \sa CStringProxy
 */
class CPLIB_CLASS 
CWStringProxy
{
public:
    /**
     * \brief ������� � �������������� ������
     *
     * \param str [in] ��������� �� ������ ��������
     */
    CWStringProxy( const wchar_t* str = L"");
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CWStringProxy( const CWStringProxy& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CWStringProxy& operator=( const CWStringProxy& src);
    /// ���������� ������.
    ~CWStringProxy();

    /// �������� ������ � ���� const wchar_t*
    const wchar_t* c_str() const;
private:
#pragma warning(push)
#pragma warning(disable: 4251)
    std::wstring *m_pValue;
#pragma warning(pop)
};

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CStringProxy, CPLIB_EXTERN_TEMPLATE, CPLIB_CLASS);

/// ������ �������� CStringProxy
class CPLIB_CLASS CStringList: public CDllList<CStringProxy> {};

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CWStringProxy, CPLIB_EXTERN_TEMPLATE, CPLIB_CLASS);

/// ������ �������� CWStringProxy
class CPLIB_CLASS CWStringList: public CDllList<CWStringProxy> {};

} // namespace CryptoPro

#endif // _STRINGPROXY_H_INCLUDED
