/*
 AX_SlotStreamChannel --- ���������� ����������� ������. 

 $Name: work1 $
 $Revision: 1.1.2.5 $
 $Date: 2008/11/01 11:50:28 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <ax/interfaces/ISlotStreamChannel.h>



// =================================================
// ���������� ISlotStreamChannel 

namespace  {

	class ATL_NO_VTABLE CSlotStreamChannel : 
		public CComObjectRootEx<CComSingleThreadModel>, 
		public CComCoClass<CSlotStreamChannel>, 
		public ISlotStreamChannel,
		public IStream 
	{
	public:
		template<class I>
		inline static I* Create() // new reference 
		{
			try
			{
				typedef CComObject<CSlotStreamChannel> _CoClass;
				_CoClass* pClass;
				HRESULT rc = _CoClass::CreateInstance(&pClass);
				if (FAILED(rc)) throw MethodError(rc);
				//
				pClass->AddRef();
				//
				CComPtr<I> i;
				rc = pClass->QueryInterface(__uuidof(I),(void**)&i);
				if (FAILED(rc)) throw MethodError(rc);
				//
				pClass->Release();
				pClass = NULL;
				//
				return i.Detach();
			}
			_Catch()
		}

		template<class I>
		inline static I* ReadStream(IStream* stream) // new reference 
		{
			try
			{
				if (! stream) throw MethodError(E_INVALIDARG); 
				//
				CComPtr<I> i;
				i.Attach( Create<I>() ); 
				if (! i) throw MethodError(E_UNEXPECTED); 
				//
				// ��������� ����� 
				//
				CComQIPtr<ISlotStreamChannel> reader(i);
				if (! reader) throw MethodError(E_UNEXPECTED); 
				//
				HRESULT rc = reader->put_InputStream(stream); 
				if (FAILED(rc)) throw MethodError(rc);
				//
				return i.Detach(); 
			}
			_Catch() 
		}

	protected:

		// ���� 

		CComPtr<IStream> m_InputStream; 
		
		// ����� 

		CComPtr<IStream> m_OutStream; 

		// ������ 

		int m_Position;
		int m_Size; 



		// ----
		// ����� ������ 

		inline void Clear() 
		{
			m_Position = 0;
			m_Size = 0; 
		}

		inline void Free()
		{
			Clear();
		}



	public:
		CSlotStreamChannel()
		{
			Clear(); 
		}

		BEGIN_COM_MAP(CSlotStreamChannel)
			COM_INTERFACE_ENTRY_IID(__uuidof(ISlotStreamChannel),ISlotStreamChannel)
			COM_INTERFACE_ENTRY_IID(__uuidof(IStream),IStream)
			COM_INTERFACE_ENTRY_IID(__uuidof(ISequentialStream),IStream)
		END_COM_MAP()

		DECLARE_PROTECT_FINAL_CONSTRUCT()

		HRESULT FinalConstruct() 
		{
			return S_OK;
		}

		void FinalRelease() 
		{
			Free();
		}

		~CSlotStreamChannel()
		{
			Free(); 
		}



	protected:
		// ... 

	public:
		// ----
		// ISlotStreamChannel 

		// ----
		// ������ 

		// * ������� ����� 

		STDMETHOD(put_InputStream)(IStream* inStream) 
		{
			try
			{
				if (! inStream) throw MethodError(E_INVALIDARG); 
				//
				Free(); 
				//
				CComQIPtr<IStream> q(inStream); 
				m_InputStream.Attach( q.Detach() ); 
				return S_OK; 
			}
			_ComCatch() 
		}

		STDMETHOD(get_InputStream)(IStream** out_inStream) 
		{
			try
			{
				if (! out_inStream) throw MethodError(E_INVALIDARG); 
				//
				if (m_InputStream)
				{
					CComQIPtr<IStream> q(m_InputStream); 
					*out_inStream = q.Detach(); 
				}
				else
				{
					*out_inStream = 0; 
				}
				return S_OK; 
			}
			_ComCatch() 
		}

		// * �������� ����� 

		STDMETHOD(put_OutStream)(IStream* outStream) 
		{
			try
			{
				if (m_OutStream) m_OutStream.Release(); 
				//
				if (outStream) 
				{
					CComQIPtr<IStream> q(outStream); 
					m_OutStream.Attach( q.Detach() ); 
				}
				return S_OK; 
			}
			_ComCatch() 
		}

		STDMETHOD(get_OutStream)(IStream** out_outStream) 
		{
			try
			{
				if (! out_outStream) throw MethodError(E_INVALIDARG); 
				//
				if (m_OutStream)
				{
					CComQIPtr<IStream> q(m_OutStream); 
					*out_outStream = q.Detach(); 
				}
				else
				{
					*out_outStream = 0; 
				}
				return S_OK; 
			}
			_ComCatch() 
		}



		// ----
		// ISequentialStream 

		STDMETHOD(Read)(
			void *pv,
			ULONG cb,
			ULONG *pcbRead)
		{
			try
			{
				if (cb <= 0) return S_OK; // ������ �� ������ 
				//
				// ������ 
				//
				//if (<Open Condition>)
				//{
				//	Open(); 
				//}
				//
				int len = cb;
				//if (m_Position + len > m_Size) len = m_Size - m_Position; 
				if (len == 0)
				{
					if (pcbRead) *pcbRead = len; 
					return S_FALSE; // ������ ��������� 
				}
				//
				ULONG bytesRead = 0;
				Blob data;
				data.Expand(len); 
				HRESULT rc = m_InputStream->Read(data.GetBuffer(), len, &bytesRead); 
				if (FAILED(rc)) throw MethodError(E_UNEXPECTED); 
				if (bytesRead > 0) data.SetSize(bytesRead);
				else data.Free(); 
				//
				//if ((int)bytesRead != len) 
				//{
				//	throw MethodError(E_UNEXPECTED); 
				//}
				if ((int)bytesRead > (int)cb) 
				{
					throw MethodError(E_UNEXPECTED); 
				}
				//
				if (data.Length() > 0)
				{
					int n = bytesRead; 
					int wrong_n = data.Length();
					if (wrong_n != n)
					{
						string errorMsg = FormatStr(
							L"������ ��� ����������� ������� ������: %d --- %d", wrong_n, n );
						throw MethodError(errorMsg); 
					}
					CopyMemory(pv,data.GetBuffer(),n); 
					//
					m_Position += data.Length(); 
					//
					//if (m_Position == m_Size)
					//{
					//	// f.Close(); 
					//}
				}
				//
				if (pcbRead) *pcbRead = (ULONG)data.Length(); 
				if (data.Length() > 0)
				{
					return S_OK;
				}
				else
				{
					return S_FALSE;
				}
			}
			_ComCatch()
		}

		STDMETHOD(Write)(
			const void* pv,
			ULONG cb,
			ULONG* pcbWritten)
		{
			try
			{
				throw MethodError(E_NOTIMPL); 
				//
				// ���������� 
				//
				// MutliWriter:
				//{
				//	m_Writer.Open(); 
				//	//
				//	// ������
				//	//
				//	if (cb <= 0) return S_OK; 
				//	//
				//	m_Writer.AddBinary((const char*)pv,cb); 
				//}
				//if (pcbWritten) *pcbWritten = cb; 
				//return S_OK; 
			}
			_ComCatch()
		}



		// ----
		// IStream

		HRESULT STDMETHODCALLTYPE Seek( 
			/* [in] */ LARGE_INTEGER dlibMove,
			/* [in] */ DWORD dwOrigin,
			/* [out] */ ULARGE_INTEGER *plibNewPosition) 
		{
			try
			{
				if (! m_InputStream) return S_FALSE; 
				//
				HRESULT rc = m_InputStream->Seek(dlibMove, dwOrigin, plibNewPosition); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				return rc; 
			}
			_ComCatch(); 
			//
			//switch (dwOrigin)
			//{
			//case FILE_BEGIN:
			//	{
			//		// TODO: !!! 
			//		m_Position = dlibMove.LowPart;
			//		//
			//		//if (m_Position == 0)
			//		//{
			//		//	f.Close();
			//		//	f.Open(m_Path);
			//		//}
			//	}
			//	break;
			//case FILE_CURRENT:
			//	{
			//		throw MethodError(E_NOTIMPL); 
			//	}
			//	break;
			//case FILE_END:
			//	{
			//		throw MethodError(E_NOTIMPL); 
			//	}
			//	break;
			//default:
			//	{
			//		throw MethodError(E_NOTIMPL); 
			//	}
			//}
			//
			//return S_OK;
		}

		HRESULT STDMETHODCALLTYPE SetSize( 
			/* [in] */ ULARGE_INTEGER libNewSize) 
		{
			return E_NOTIMPL; 
		}

		HRESULT STDMETHODCALLTYPE CopyTo( 
			/* [unique][in] */ IStream *pstm,
			/* [in] */ ULARGE_INTEGER cb,
			/* [out] */ ULARGE_INTEGER *pcbRead,
			/* [out] */ ULARGE_INTEGER *pcbWritten) 
		{
			return E_NOTIMPL; 
		}

		HRESULT STDMETHODCALLTYPE Commit( 
			/* [in] */ DWORD grfCommitFlags) 
		{
			return S_OK; // ������ �� ������ 
		}

		HRESULT STDMETHODCALLTYPE Revert() 
		{
			return E_NOTIMPL; 
		}

		HRESULT STDMETHODCALLTYPE LockRegion( 
			/* [in] */ ULARGE_INTEGER libOffset,
			/* [in] */ ULARGE_INTEGER cb,
			/* [in] */ DWORD dwLockType) 
		{
			return S_OK; // ������ �� ������ 
		}

		HRESULT STDMETHODCALLTYPE UnlockRegion( 
			/* [in] */ ULARGE_INTEGER libOffset,
			/* [in] */ ULARGE_INTEGER cb,
			/* [in] */ DWORD dwLockType) 
		{
			return S_OK; // ������ �� ������ 
		}

		HRESULT STDMETHODCALLTYPE Stat( 
			/* [out] */ STATSTG *pstatstg,
			/* [in] */ DWORD grfStatFlag) 
		{
			try
			{
				ZeroMemory(pstatstg,sizeof(STATSTG));
				//
				return S_FALSE; // no info 
				//
				pstatstg->cbSize.QuadPart = 0;
				pstatstg->cbSize.LowPart = m_Size; 
				//
				return S_OK; 
			}
			_ComCatch()
		}

		HRESULT STDMETHODCALLTYPE Clone( 
			/* [out] */ IStream **ppstm) 
		{
			try
			{
				if (! ppstm) throw MethodError(E_POINTER); 
				//
				CComPtr<IStream> stream;
				stream.Attach(
					CSlotStreamChannel::Create<IStream>()  
					);
				if (! stream) throw MethodError(E_UNEXPECTED); 
				//
				CComQIPtr<ISlotStreamChannel> reader(stream); 
				if (! reader) throw MethodError(E_UNEXPECTED); 
				//
				CComPtr<IStream> s2; 
				if (m_InputStream)
				{
					HRESULT rc = m_InputStream->Clone(&s2); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
				//
				HRESULT rc = reader->put_InputStream(s2); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				rc = reader->put_OutStream(m_OutStream); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				*ppstm = stream.Detach(); 
				return S_OK; 
			}
			_ComCatch() 
		}
	};
	// CSlotStreamChannel  

} // namespace  
