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
 * \brief ����� ��� ������ �� ��������.
 */

#ifndef _CPLIB_DATETIME_H_INCLUDED
#define _CPLIB_DATETIME_H_INCLUDED

#include <time.h>
#if !defined UNIX
#   include <windows.h>
#endif	/* !UNIX */
#include <cplib/StringProxy.h>

namespace CryptoPro {

class CPLIB_CLASS CDateTime;

/**
 * \class CDateTimeSpan DateTime.h <cplib/DateTime.h>
 * \brief ������ �������.
 *
 * ����� ������ ������ ������� � ��������� �� �������������.
 *
 * \sa CDateTime
 */
class CPLIB_CLASS 
CDateTimeSpan
{
public:
    /// ������� ������ ������
    explicit CDateTimeSpan();
    /**
     * \brief ������� � �������������� ������
     *
     * \param alya_generalizedTime [in] ��������� ������������� ������� �������
     * \remarks ������ ���������� ������������� ���������: "YYYYMMDDhhmmss.ddddddZ"
     * ��� YYYY - ����, MM - ������, DD - ���, hh - ����, mm - ������, ss - �������, 
     * dddddd - ���� ������� (�� 6-�� ������, ����� ������������� ������ � ��������������
     * ������. �������: "00050600114530Z", "00000000000023.123Z", "00000000000003.123456Z"
     */
    explicit CDateTimeSpan( const char* alya_generalizedTime);
    /**
     * \brief ������� � �������������� ������
     *
     * \param seconds [in] - ���������� ������ � ������� �������
     * \param microseconds [in] - ���������� ����������� � ������� �������
     */
    explicit CDateTimeSpan( unsigned seconds, unsigned microseconds = 0);
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CDateTimeSpan( const CDateTimeSpan& src);

    /**
     * \brief ���������� ������ ������� � ��������� ������� (ANSI)
     * \sa getGeneralizedTime(), towstring(), CDateTimeSpan()
     */
    CStringProxy tostring() const;
    /**
     * \brief ���������� ������ ������� � ��������� ������� (Unicode)
     * \sa getGeneralizedTime(), tostring(), CDateTimeSpan()
     */
    CWStringProxy towstring() const;
    /**
     * \brief ���������� ������ ������� � ��������� ������� (ANSI)
     * \sa tostring(), towstring(), CDateTimeSpan()
     */
    CStringProxy getGeneralizedTime() const;

    /**
     * \brief ���������� ������� ����� ���������� ����������
     */
    DWORD getLowPart();

    /**
     * \brief ���������� ������� ����� ���������� ����������
     */
    DWORD getHighPart();

    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CDateTimeSpan& operator=( const CDateTimeSpan& src);
    /**
     * \brief �������� ������ ��������.
     *
     * \param src [in] ������ ��� ������
     * \remarks ������� �� ���������� ����������.
     */
    void swap( CDateTimeSpan &src ) throw();

    CPLIB_API friend bool operator==( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend bool operator!=( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend bool operator<=( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend bool operator>=( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend bool operator<( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend bool operator>( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend CDateTime& operator +=( CDateTime &lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend CDateTime& operator -=( CDateTime &lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend CDateTimeSpan& operator +=( CDateTimeSpan &lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend CDateTimeSpan& operator -=( CDateTimeSpan &lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend CDateTimeSpan operator -( const CDateTime &lhs, const CDateTime &rhs); 

    CPLIB_API friend CDateTimeSpan& operator *=( CDateTimeSpan &lhs, unsigned rhs);
    CPLIB_API friend CDateTimeSpan& operator /=( CDateTimeSpan &lhs, unsigned rhs);
    CPLIB_API friend CDateTimeSpan& operator %=( CDateTimeSpan &lhs, unsigned rhs);

    CPLIB_API friend CDateTimeSpan operator *( const CDateTimeSpan &lhs, unsigned rhs);
    CPLIB_API friend CDateTimeSpan operator /( const CDateTimeSpan &lhs, unsigned rhs);
    CPLIB_API friend CDateTimeSpan operator %( const CDateTimeSpan &lhs, unsigned rhs);

    CPLIB_API friend unsigned operator / (const CDateTimeSpan &lhs, const CDateTimeSpan &rhs);
    CPLIB_API friend CDateTimeSpan operator % ( const CDateTimeSpan &lhs, const CDateTimeSpan &rhs );

    static const CDateTimeSpan& OneYear();
    static const CDateTimeSpan& OneMonth();
    static const CDateTimeSpan& OneDay();
    static const CDateTimeSpan& OneHour();
    static const CDateTimeSpan& OneMinute();
    static const CDateTimeSpan& OneSecond();
    static const CDateTimeSpan& OneMillisecond();

private:
    /// ������ ���� ��� (365 ����)
    static const CDateTimeSpan oneYear;
    /// ������ ���� ����� (30 ����)
    static const CDateTimeSpan oneMonth;
    /// ������ ���� ����
    static const CDateTimeSpan oneDay;
    /// ������ ���� ���
    static const CDateTimeSpan oneHour;
    /// ������ ���� ������
    static const CDateTimeSpan oneMinute;
    /// ������ ���� �������
    static const CDateTimeSpan oneSecond;
    /// ������ ���� ������������
    static const CDateTimeSpan oneMillisecond;

    DWORD high_;
    DWORD low_;
};

/**
 * \class CDateTime DateTime.h <cplib/DateTime.h>
 * \brief �����.
 *
 * ����� ������ �������� ������� � ��������� �� �������������.
 *
 * \sa CDateTimeSpan
 */
class CPLIB_CLASS
CDateTime
{
public:
     /**
     * \brief ������� � �������������� ������
     *
     * \param time [in] - ����� � ������� __time64_t 
     * \param micro [in] - ���������� �����������
     */
    explicit CDateTime( long long time = 0, unsigned int micro = 0);
    /**
     * \brief ������� � �������������� ������
     *
     * \param generalizedTime [in] ��������� ������������� ������� �������
     * \remarks ������ ���������� ������������� ���������: "YYYYMMDDhhmmss.ddddddZ"
     * ��� YYYY - ����, MM - ������, DD - ���, hh - ����, mm - ������, ss - �������, 
     * dddddd - ���� ������� (�� 6-�� ������, ����� ������������� ������ � ��������������
     * ������. �������: "20041105114530Z", "19940821101532.123Z", "19940821101532.123456Z"
     */
    explicit CDateTime( const char* generalizedTime);
        /**
     * \brief ������� � �������������� ������
     *
     * \param time [in] - ����� � ������� __time32_t 
     * \param micro [in] - ���������� �����������
     */
    CDateTime( long time, unsigned int micro);
    /**
     * \brief ������� � �������������� ������
     *
     * \param filetime [in] ����� � ������� FILETIME
     */
    CDateTime( FILETIME filetime);
    /**
     * \brief ������� � �������������� ������
     *
     * \param systemtime [in] ����� � ������� SYSTEMTIME
     */
    CDateTime( SYSTEMTIME systemtime);
    /**
    * \brief ������� � �������������� ������
    *
    * \param year [in] ���
    * \param month [in] �����
    * \param day [in] ����
    * \param hour [in] ���
    * \param minute [in] ������
    * \param second [in] �������
    * \param milli [in] ������������
    * \param micro [in] ������������
    */
    CDateTime(
	unsigned int year,
	unsigned int month,
	unsigned int day,
	unsigned int hour = 0,
	unsigned int minute = 0,
	unsigned int second = 0,
	unsigned int milli = 0,
	unsigned int micro = 0);
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param time [in] ������, ����� �������� ���������
     */
    CDateTime( const CDateTime& time);
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CDateTime& operator=( const CDateTime& src);
    /**
     * \brief �������� ������ ��������.
     *
     * \param src [in] ������ ��� ������
     * \remarks ������� �� ���������� ����������.
     */
    void swap( CDateTime &src ) throw();

    /// ���������� ���
    unsigned int year() const;
    /// ���������� �����
    unsigned int month() const;
    /// ���������� ����
    unsigned int day() const;
    /// ���������� ���
    unsigned int hour() const;
    /// ���������� ������
    unsigned int minute() const;
    /// ���������� �������
    unsigned int second() const;
    /// ���������� ������������
    unsigned int millisecond() const;
    /// ���������� ������������
    unsigned int microsecond() const;

    /**
     * \brief ���������� ����� � ��������� ������� (ANSI)
     * \sa getTime(), getFileTime(), getSystemTime(), tostring(), towstring(), CDateTimeSpan
     */
    CStringProxy getGeneralizedTime() const;
    CStringProxy getGeneralizedTimeTrimMicroseconds() const;
    /**
     * \brief ���������� ����� � ������� time_t
     * \sa getGeneralizedTime(), getFileTime(), getSystemTime(), tostring(), towstring(), CDateTimeSpan
     */
    time_t getTime() const;
    /**
     * \brief ���������� ����� � ������� FILETIME
     * \sa getGeneralizedTime(), getTime(), getSystemTime(), tostring(), towstring(), CDateTimeSpan
     */
    FILETIME getFileTime() const;
    /**
     * \brief ���������� ����� � ������� SYSTEMTIME
     * \sa getGeneralizedTime(), getTime(), getFileTime(), tostring(), towstring(), CDateTimeSpan
     */
    SYSTEMTIME getSystemTime() const;
    /**
     * \brief ���������� ����� � �������������� ��������� ������� (ANSI)
     * \sa getGeneralizedTime(), getTime(), getFileTime(), getSystemTime(), towstring(), CDateTimeSpan
     */
    CStringProxy tostring() const;
    /**
     * \brief ���������� ����� � �������������� ��������� ������� (Unicode)
     * \sa getGeneralizedTime(), getTime(), getFileTime(), getSystemTime(), tostring(), CDateTimeSpan
     */
    CWStringProxy towstring() const;
    /**
     * \brief ���������� �����, ��������������� � ���������� �������������
     * \sa localToUtc()
     */
    CDateTime utcToLocal() const;
    /**
     * \brief ���������� �����, ��������������� � ������������� � ������� �������������� ����������������� ������� (UTC)
     * \sa utcToLocal()
     */
    CDateTime localToUtc() const;

    /// ���������� ������ � ������� �������� ������� � ��������� �� ������������ � ������� �������������� ����������������� ������� (UTC)
    static CDateTime Now();

    /// ���������� ������ � ������� �������� ������� � ��������� �� ������������ � ������� �������������� ����������������� ������� (UTC)
    static CDateTime GetCurrentTime(){return Now();}

    CPLIB_API friend bool operator==( const CDateTime& lhs, const CDateTime& rhs);
    CPLIB_API friend bool operator!=( const CDateTime& lhs, const CDateTime& rhs);
    CPLIB_API friend bool operator<=( const CDateTime& lhs, const CDateTime& rhs);
    CPLIB_API friend bool operator>=( const CDateTime& lhs, const CDateTime& rhs);
    CPLIB_API friend bool operator<( const CDateTime& lhs, const CDateTime& rhs);
    CPLIB_API friend bool operator>( const CDateTime& lhs, const CDateTime& rhs);
    CPLIB_API friend CDateTime& operator +=( CDateTime &lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend CDateTime& operator -=( CDateTime &lhs, const CDateTimeSpan& rhs);
    CPLIB_API friend CDateTimeSpan operator -( const CDateTime &lhs, const CDateTime &rhs); 

#ifdef UNIX
    CDateTime( timeval tval);
    timeval getTimeval() const;
#endif // UNIX
private:
    DWORD high_;
    DWORD low_;
};

/// �������� �������� �� ���������
CPLIB_API bool operator==( const CDateTime& lhs, const CDateTime& rhs);
/// �������� �������� �� �����������
CPLIB_API bool operator!=( const CDateTime& lhs, const CDateTime& rhs);
/// �������� ��������� (������ ��� �����)
CPLIB_API bool operator<=( const CDateTime& lhs, const CDateTime& rhs);
/// �������� ��������� (������ ��� �����)
CPLIB_API bool operator>=( const CDateTime& lhs, const CDateTime& rhs);
/// �������� ��������� (������)
CPLIB_API bool operator<( const CDateTime& lhs, const CDateTime& rhs);
/// �������� ��������� (������)
CPLIB_API bool operator>( const CDateTime& lhs, const CDateTime& rhs);

/// �������� �������� �� ���������
CPLIB_API bool operator==( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
/// �������� �������� �� �����������
CPLIB_API bool operator!=( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
/// �������� ��������� (������ ��� �����)
CPLIB_API bool operator<=( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
/// �������� ��������� (������ ��� �����)
CPLIB_API bool operator>=( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
/// �������� ��������� (������)
CPLIB_API bool operator<( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
/// �������� ��������� (������)
CPLIB_API bool operator>( const CDateTimeSpan& lhs, const CDateTimeSpan& rhs);
/// �������� ����������� ������� �� �������
CPLIB_API CDateTime& operator +=( CDateTime &lhs, const CDateTimeSpan& rhs);
/// �������� ��������� ������� �� �������
CPLIB_API CDateTime& operator -=( CDateTime &lhs, const CDateTimeSpan& rhs);

/// �������� ����������� ������� � �������
CPLIB_API CDateTimeSpan& operator +=( CDateTimeSpan &lhs, const CDateTimeSpan& rhs);
/**
 * \brief �������� ��������� ������� �� �������
 * \remark ������ ������� �� ����� ���� �������������. ���� � ����������
 * ��������� ���������� ������������� ������, ������������ ����������.
 */
CPLIB_API CDateTimeSpan& operator -=( CDateTimeSpan &lhs, const CDateTimeSpan& rhs);

/// �������� ��������� ������� �� �����
CPLIB_API CDateTimeSpan& operator *=( CDateTimeSpan &lhs, unsigned rhs);
/// �������� ������� ������� �� �����
CPLIB_API CDateTimeSpan& operator /=( CDateTimeSpan &lhs, unsigned rhs);
/// �������� ��������� ������� �� ������� ������� �� �����
CPLIB_API CDateTimeSpan& operator %=( CDateTimeSpan &lhs, unsigned rhs);

/// �������� ��������� ������� �� �����
CPLIB_API CDateTimeSpan operator *( const CDateTimeSpan &lhs, unsigned rhs);
/// �������� ������� ������� �� �����
CPLIB_API CDateTimeSpan operator /( const CDateTimeSpan &lhs, unsigned rhs);
/// �������� ��������� ������� �� ������� ������� �� �����
CPLIB_API CDateTimeSpan operator %( const CDateTimeSpan &lhs, unsigned rhs);

/// �������� ������� ������� �� ������
CPLIB_API unsigned operator / ( const CDateTimeSpan &lhs, const CDateTimeSpan &rhs );
/// �������� ��������� ������� �� ������� ������� �� ������
CPLIB_API CDateTimeSpan operator % ( const CDateTimeSpan &lhs, const CDateTimeSpan &rhs );

/**
 * \brief �������� ��������� ������� �� �������
 * \remark ������ ������� �� ����� ���� �������������. ���� � ����������
 * ��������� ���������� ������������� ������, ������������ ����������.
 */
CPLIB_API CDateTimeSpan operator -( const CDateTimeSpan &lhs, const CDateTimeSpan &rhs); 
/**
 * \brief �������� ��������� ������� �� �������
 * \remark ������ ������� �� ����� ���� �������������. ��� ���������
 * ����� �������� ������� ������� �� ����� ������� ������������ ����������
 */
CPLIB_API CDateTimeSpan operator -( const CDateTime &lhs, const CDateTime &rhs); 
/// �������� ��������� ������� �� ����
CPLIB_API CDateTime operator -( const CDateTime &lhs, const CDateTimeSpan &rhs); 

/// �������� ����������� ������� � �������
CPLIB_API CDateTimeSpan operator +( const CDateTimeSpan &lhs, const CDateTimeSpan &rhs); 
/// �������� ����������� ������� �� �������
CPLIB_API CDateTime operator +( const CDateTime &lhs, const CDateTimeSpan &rhs); 

/**
* \brief ������� ����������� � ���� ��������� ������� �������
*
* \param intervalUnit [in] ������� ��������� � ������� ������� ��������, ��������
*        ��������� ����� ���� ������:
*	 - "s" - �������;
*	 - "n" - ������;
*	 - "h" - ����;
*	 - "d" - ���; 
*	 - "w" - ������;
*	 - "m" - ������;
*	 - "y" - ����.
* \param interval [in] ������ ������������� ���������
* \param value [in] ����, � ������� ������������ ��������
*
* \return ����� �������� ����.
*/
CPLIB_API CDateTime DateAddA( const char* intervalUnit,
    int interval, const CDateTime& value);

/**
* \brief ������� ����������� � ���� ��������� ������� �������
*
* \param intervalUnit [in] ������� ��������� � ������� ������� ��������, ��������
*        ��������� ����� ���� ������:
*	 - "s" - �������;
*	 - "n" - ������;
*	 - "h" - ����;
*	 - "d" - ���; 
*	 - "w" - ������;
*	 - "m" - ������;
*	 - "y" - ����.
* \param interval [in] ������ ������������� ���������
* \param value [in] ����, � ������� ������������ ��������
*
* \return ����� �������� ����.
*/
CPLIB_API CDateTime DateAddW( const wchar_t* intervalUnit,
    int interval, const CDateTime& value);

#ifdef UNICODE
#define DateAdd DateAddW
#else
#define DateAdd DateAddA
#endif

} // namespace CryptoPro

#endif //_CPLIB_DATETIME_H_INCLUDED
