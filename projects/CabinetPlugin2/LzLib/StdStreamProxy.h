#pragma once

#include "stackunknown.h"

namespace Lz {

template <class T>
class StdStreamProxy : public Lz::StackUnknown<ISequentialStream>
{
public:

	T* m_pStdStream;

	StdStreamProxy(T* pStdStream) { m_pStdStream = pStdStream; };

	virtual HRESULT STDMETHODCALLTYPE Write(void const * pv, ULONG cb, ULONG * pcbWritten)
	{
		m_pStdStream->write((T::char_type*)pv, cb);

		if( pcbWritten ) *pcbWritten = cb;

		return S_OK;
		//		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Read(void* pv, ULONG cb, ULONG* pcbRead)
	{
		if( m_pStdStream->good() )
		{
			m_pStdStream->read((T::char_type*)pv, cb);

			if( pcbRead )
				*pcbRead = m_pStdStream->gcount();

			return S_OK;
		}

		if( pcbRead )
			*pcbRead = 0;

		return S_FALSE;
	};
};

}; //namespace Lz