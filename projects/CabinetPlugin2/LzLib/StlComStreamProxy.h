#pragma once

namespace Lz {

template <class T>
class ATL_NO_VTABLE StlComStreamProxy : public CComObjectRoot, public ISequentialStream
{
protected:
	T* m_pStdStream;

public:

	StlComStreamProxy() : m_pStdStream(NULL) {}

	void Attach(T* pStdStream) { m_pStdStream = pStdStream; };

	BEGIN_COM_MAP(StlComStreamProxy)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY(ISequentialStream)
	END_COM_MAP()

	virtual HRESULT STDMETHODCALLTYPE Write(void const * pv, ULONG cb, ULONG * pcbWritten)
	{
		ATLASSERT(m_pStdStream);

		m_pStdStream->write((T::char_type*)pv, cb);

		if( pcbWritten ) *pcbWritten = cb;

		return S_OK;
		//		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Read(void* pv, ULONG cb, ULONG* pcbRead)
	{
		ATLASSERT(m_pStdStream);

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