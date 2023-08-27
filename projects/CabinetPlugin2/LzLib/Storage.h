#pragma once


namespace Lz {

typedef CAtlMap<CString, CComQIPtr<IStorage>, CStringElementTraitsI<CString>, CComQIPtrElementTraits<IStorage> > StorageMap;

template<class T = IStorage>
class StorageFile
{
public:

	HRESULT Create(const WCHAR* pwcsFileName, T** ppObject, DWORD grfMode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT)
	{
		return StgCreateStorageEx(
				pwcsFileName,
				grfMode | STGM_CREATE,
				STGFMT_STORAGE,
				0,
				NULL,
				0,
				__uuidof(T),
				(void**)ppObject
			);
	};

	HRESULT Open(const WCHAR* pwcsFileName, T** ppObject, DWORD grfMode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT)
	{
		return StgOpenStorageEx(
				pwcsFileName,
				grfMode,
				STGFMT_STORAGE,
				0,
				NULL,
				0,
				__uuidof(T),
				(void**)ppObject
			);
	};
};

template<class T, const WCHAR* _StorageName>
class StgXmlStream : public T
{
public:
	StgXmlStream() : T() {};
	const WCHAR* GetStorageName() { return _StorageName; };

	template<class _DestObjClass>
	void Load(IStorage* pStorage, _DestObjClass& pObj) throw( _com_error )
	{
		CComPtr<IStream> pStream;
		_com_util::CheckError( pStorage->OpenStream(GetStorageName(), NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pStream) );

		pObj.Load(CComVariant(pStream));
	};
};

namespace StorageHelper {

#define STG_CTIME 0x1
#define STG_ATIME 0x2
#define STG_MTIME 0x4

inline HRESULT SetElementTimes(IStorage* pStorage, const WCHAR* pwcsName, const COleDateTime& dt, WORD wTimeMask)
{
	FILETIME ft;
	FILETIME* pctime = ( wTimeMask & STG_CTIME ? &ft : NULL );
	FILETIME* patime = ( wTimeMask & STG_ATIME ? &ft : NULL );
	FILETIME* pmtime = ( wTimeMask & STG_MTIME ? &ft : NULL );

	{
		SYSTEMTIME st;
		dt.GetAsSystemTime(st);
		::SystemTimeToFileTime(&st, &ft);
	}

	return pStorage->SetElementTimes(pwcsName, pctime, patime, pmtime);
}

inline HRESULT Stream2File(IStream* pIStream, LPCWSTR szFileName, DWORD cbBufSize = 2048)
{
	HRESULT hr;
	CHeapPtr<BYTE> _buf;
	CAtlFile file;
	DWORD _buf_read = 0;
	
	hr = file.Create(CString(szFileName), GENERIC_WRITE, FILE_SHARE_READ, CREATE_ALWAYS);
	if( FAILED(hr) ) return hr;

	_buf.AllocateBytes(cbBufSize);

	while( SUCCEEDED(pIStream->Read(_buf, cbBufSize, &_buf_read)) && _buf_read > 0 )
	{
		if( FAILED(file.Write(_buf, _buf_read)) || _buf_read < cbBufSize )
			break;
	}

	return S_OK;
}

inline HRESULT File2Stream(LPCWSTR szFileName, IStream* pIStream, DWORD cbBufSize = 2048)
{
	HRESULT hr;
	CHeapPtr<BYTE> _buf;
	CAtlFile file;
	DWORD _buf_read = 0;
	
	hr = file.Create(CString(szFileName), GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING);
	ATLASSERT(SUCCEEDED(hr));

	_buf.AllocateBytes(cbBufSize);

	while( SUCCEEDED(file.Read(_buf, cbBufSize, _buf_read)) && _buf_read > 0 )
	{
		if( FAILED(pIStream->Write(_buf, _buf_read, NULL)) || _buf_read < cbBufSize )
			break;
	}

	return S_OK;
}

inline HRESULT StreamSeek0(IStream* pIStream)
{
	LARGE_INTEGER _offset;
	memset(&_offset, 0x0, sizeof(LARGE_INTEGER));
	return pIStream->Seek(_offset, STREAM_SEEK_SET, NULL);
}

} // namespace IStorageHelper


class StorageStream
{
protected:
	WORD m_wTmeMask;
	CComPtr<IStorage> m_spRoot;
	CComPtr<IStorage> m_spIStorage;
	CComPtr<IStream> m_spIStream;
	CStringW m_Name;

public:
	StorageStream() 
	{
		m_wTmeMask = 0;
	}

	StorageStream(IStorage* pRoot, LPCWSTR szName)
	{
		Init(pRoot, szName);
	}

	void Init(IStorage* pRoot, LPCWSTR szName)
	{
		ATLASSERT(pRoot);
		ATLASSERT(szName);

		m_wTmeMask = 0;
		m_spRoot = pRoot;
		m_Name = szName;
	}

	HRESULT Create()
	{
		HRESULT hr = m_spRoot->CreateStorage(m_Name, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, 0, &m_spIStorage);
		if( FAILED(hr) ) return hr;
		hr = m_spIStorage->CreateStream(m_Name, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, 0, &m_spIStream);
		m_wTmeMask |= STG_CTIME | STG_MTIME;
		return hr;
	}

	HRESULT Open()
	{
		HRESULT hr = m_spRoot->OpenStorage(m_Name, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, 0, &m_spIStorage);
		if( FAILED(hr) ) return hr;
		return m_spIStorage->OpenStream(m_Name, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &m_spIStream);
	}

	void Release()
	{
		m_spIStream.Release();
		m_spIStorage.Release();
		m_spRoot.Release();
	}

	~StorageStream()
	{
		Release();
		
		if( m_wTmeMask )
			HRESULT hr = Lz::StorageHelper::SetElementTimes(m_spRoot, m_Name, COleDateTime::GetCurrentTime(), m_wTmeMask);
	}

	DATE GetModifyTime()
	{
		COleDateTime dt;
		STATSTG stat;
		if( m_spIStorage->Stat(&stat, STATFLAG_NONAME) == S_OK )
			dt = stat.mtime;
		return dt;
	}

	DWORD GetSize()
	{
		STATSTG stat;
		if( m_spIStream->Stat(&stat, STATFLAG_NONAME) == S_OK )
			return stat.cbSize.LowPart;
		return 0;
	}

	operator IStream*() { return m_spIStream; }
	operator IStorage*() { return m_spIStorage; }
};


} // namespace Lz