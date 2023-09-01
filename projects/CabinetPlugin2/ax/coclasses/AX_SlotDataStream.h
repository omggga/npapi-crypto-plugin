/*
 AX_SlotDataStream --- ����� ���������� ������, ���������� ����������� � ������, ������������ �������. 

 $Name: work1 $
 $Revision: 1.1.2.1 $
 $Date: 2008/10/10 15:09:16 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "../../low-level/SmartMap.h"

#include "../interfaces/ISlotDataStreamInfo.h"


#ifndef SLOT_DATA_STREAM_OUTPUT_FILTER_PARAM
#define SLOT_DATA_STREAM_OUTPUT_FILTER_PARAM (L"output-filter")
#endif

#ifndef SLOT_XML_FILTER_IN_STREAM_PARAM
#define SLOT_XML_FILTER_IN_STREAM_PARAM (L"input-stream")
#endif


namespace  {

	// =================================================
	// ���������� ISlotDataStreamInfo, ������� ������ �������� IStream 
	// ������� ��������� ���������� + ���.����. 

	template<
		class _StreamInterface=IStream
	>
	class ATL_NO_VTABLE CSlotDataStreamT : 
		public CComObjectRootEx<CComSingleThreadModel>, 
		public CComCoClass<CSlotDataStreamT<_StreamInterface> >, 
		public ISlotDataStreamInfo, 
		public IStream 
	{
	public:
		typedef _StreamInterface StreamInterface;

		template<class I>
		inline static I* Create() // new reference 
		{
			try
			{
				typedef CComObject<CSlotDataStream> _CoClass;
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
		inline static I* CreateDataStream(
			const string& contentType 
			) // new reference 
		{
			try
			{
				CComPtr<ISlotDataStreamInfo> S;
				S.Attach(
					Create<ISlotDataStreamInfo>() // new reference 
					); 
				if (! S) throw MethodError(E_UNEXPECTED); 
				//
				HRESULT rc = S->SetDataStreamParameter(
					CComBSTR(L"content-type"),
					CComVariant(CComBSTR(contentType)) 
					); 
				if (FAILED(rc)) throw MethodError(rc); 
				//
				CComQIPtr<I> i(S); 
				if (! i) throw MethodError(E_NOINTERFACE); 
				//
				return i.Detach(); 
			}
			_Catch()
		}

	protected:
		// ----
		// ������ 

		Map<string,string> m_Parameters; 

		CComPtr<StreamInterface> m_Stream; 

		CComPtr<ISlotDataStreamInfo> m_OutputFilter; 

		// ----
		// ������������ 

		inline void Clear() 
		{
		}

		inline void Free()
		{
			// ...
			//
			Clear();
		}



	public:
		CSlotDataStreamT()
		{
			Clear(); 
		}

		BEGIN_COM_MAP(CSlotDataStreamT)
			COM_INTERFACE_ENTRY_IID(__uuidof(ISlotDataStreamInfo),ISlotDataStreamInfo)
			COM_INTERFACE_ENTRY_IID(__uuidof(IStream),IStream)
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



	public:
		// ----
		// ISlotDataStream 

		STDMETHOD(put_DataStream)(IStream* dataStream) 
		{
			try
			{
				if (m_Stream)
				{
					m_Stream.Release(); 
				}
				//
				if (dataStream)
				{
					CComQIPtr<StreamInterface> q(dataStream);
					if (! q) throw MethodError(E_NOINTERFACE).AddIfNewSource_(L"StreamInterface"); 
					m_Stream.Attach(q.Detach()); 
				}
				//
				return S_OK; 
			}
			_ComCatch()
		}

		STDMETHOD(get_DataStream)(IStream** out_dataStream) 
		{
			try
			{
				if (! out_dataStream) throw MethodError(E_POINTER); 
				//
				if (m_Stream)
				{
					CComQIPtr<IStream> q(m_Stream); 
					if (! q) throw MethodError(E_NOINTERFACE).AddIfNewSource_(L"IStream"); 
					*out_dataStream = q.Detach(); 
				}
				else
				{
					*out_dataStream = NULL; 
				}
				return S_OK; 
			}
			_ComCatch() 
		}



		// ��������� 

		STDMETHOD(GetDataStreamParameter)(BSTR name,VARIANT* out_value)
		{
			try
			{
				if (! out_value) throw MethodError(E_POINTER); 
				//
				string n(name); 
				//
				if (m_Parameters.ContainsKey(n))
				{
					string s = m_Parameters[n]; 
					//
					CComBSTR bstrValue(s); 
					CComVariant v(bstrValue);
					//
					HRESULT rc = v.Detach(out_value); 
					if (FAILED(rc)) throw MethodError(rc); 
					//
					return S_OK; // found 
				}
				else
				{
					CComBSTR bstrValue(L"");
					CComVariant v(bstrValue);
					//
					HRESULT rc = v.Detach(out_value); 
					if (FAILED(rc)) throw MethodError(rc);
					//
					return S_FALSE; // not found 
				}
			}
			_ComCatch() 
		}

		STDMETHOD(SetDataStreamParameter)(BSTR name,VARIANT value) 
		{
			string shortName = L""; 
			UINT nameSize = SysStringLen(name); 
			if (nameSize >= 256)
			{
				shortName = CStringW((const wchar_t*)name,256); 
			}
			else if (nameSize > 0)
			{
				shortName = _W(name); 
			}
			//
			try
			{
				try
				{
					string s;
					//
					if (value.vt == VT_BSTR)
					{
						s = string(value.bstrVal); 
					}
					else if ( (value.vt == VT_NULL) || (value.vt == VT_EMPTY) ) 
					{
						s = L""; 
					}
					else if (value.vt == VT_BOOL) 
					{
						BOOL v = value.boolVal; 
						s = v ? L"true" : L"false"; 
					}
					else if (value.vt == VT_INT)
					{
						s = FormatStr(L"%d", (int)value.intVal ); 
					}
					else if (value.vt == VT_UI4)
					{
						s = FormatStr(L"%d", (int)value.ulVal ); 
					}
					else if (value.vt == VT_R4)
					{
						s = FormatStr(L"%f", (double)value.fltVal ); 
					}
					else if (value.vt == VT_R8)
					{
						s = FormatStr(L"%f", (double)value.dblVal ); 
					}
					else if (value.vt == VT_UNKNOWN) 
					{
						IUnknown* objectUnk = value.punkVal; 
						if (objectUnk != NULL)
						{
							if (shortName == SLOT_DATA_STREAM_OUTPUT_FILTER_PARAM) 
							{
								// �� ���� ������ ��������� ������ AX_SlotXmlFilter, 
								// ����������� ISlotDataStream 
								//
								CComQIPtr<ISlotDataStreamInfo> S(objectUnk); 
								if (! S) throw MethodError(E_NOINTERFACE).AddIfNewSource_(L"ISlotDataStream"); 
								//
								if (m_OutputFilter) m_OutputFilter.Release(); 
								//
								m_OutputFilter.Attach(S.Detach()); 
								//
								// ������� ������� m_OutputFilter ����� m_Stream � �������� �������� ������ 
								//
								HRESULT rc = m_OutputFilter->SetDataStreamParameter(
									CComBSTR(SLOT_XML_FILTER_IN_STREAM_PARAM),
									CComVariant((IUnknown*)(StreamInterface*)m_Stream) 
									);		// ���������� ������������ ��������������� ��������� 
								if (FAILED(rc)) throw MethodError(rc); 
								//
								// �������� m_Stream �� ����� m_OutputFilter.DataStream 
								//
								if (m_Stream) m_Stream.Release(); 
								//
								// m_OutputFilter->get_DataStream �������� m_OutputFilter->Open() 
								//
								rc = m_OutputFilter->get_DataStream(&m_Stream); 
								if (FAILED(rc)) throw MethodError(rc); 
								return rc; // ������������� 
							}
							else
							{
								throw MethodError(E_INVALIDARG)
									.AddIfNewSource_(L"��������� ��� IUnknown ��� ��������� '" + shortName + L"'"); 
							}
						}
					}
					else
					{
						string msg = FormatStr(L"��������� ��� ��������� (VARIANT): vt == %d", (int)value.vt ); 
						throw MethodError(E_INVALIDARG).AddIfNewSource_(msg); 
					}
					//
					string n(name); 
					//
					m_Parameters[n] = s; 
					return S_OK; 
				}
				_AddMessage(L"������ ��������� ��������� '" + shortName + L"'"); 
			}
			_ComCatch() 
		}

		// Content-Type 

		STDMETHOD(get_ContentType)(BSTR* out_contentType) 
		{
			try
			{
				if (! out_contentType) throw MethodError(E_POINTER); 
				//
				string contentType;
				if (m_Parameters.ContainsKey(aContentType)) 
				{
					contentType = m_Parameters[aContentType]; 
				}
				CComBSTR bstrCT(contentType); 
				*out_contentType = bstrCT.Detach(); 
				return S_OK; 
			}
			_ComCatch() 
		}

		STDMETHOD(put_ContentType)(BSTR contentType)
		{
			try
			{
				CComVariant v(contentType); 
				SetDataStreamParameter(CComBSTR(aContentType),v); 
				return S_OK; 
			}
			_ComCatch() 
		}








		// ----
		// IStream

		STDMETHOD(Read)(
			void *pv,
			ULONG cb,
			ULONG *pcbRead)
		{
			try
			{
				if (! m_Stream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_Stream->Read(pv,cb,pcbRead); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		STDMETHOD(Write)(
			const void* pv,
			ULONG cb,
			ULONG* pcbWritte)
		{
			try
			{
				if (! m_Stream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_Stream->Write(pv,cb,pcbWritte); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE Seek( 
			/* [in] */ LARGE_INTEGER dlibMove,
			/* [in] */ DWORD dwOrigin,
			/* [out] */ ULARGE_INTEGER *plibNewPosition) 
		{
			try
			{
				if (! m_Stream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_Stream->Seek(dlibMove,dwOrigin,plibNewPosition); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE SetSize( 
			/* [in] */ ULARGE_INTEGER libNewSize) 
		{
			try
			{
				if (! m_Stream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_Stream->SetSize(libNewSize); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE CopyTo( 
			/* [unique][in] */ IStream *pstm,
			/* [in] */ ULARGE_INTEGER cb,
			/* [out] */ ULARGE_INTEGER *pcbRead,
			/* [out] */ ULARGE_INTEGER *pcbWritten) 
		{
			try
			{
				if (! m_Stream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_Stream->CopyTo(pstm,cb,pcbRead,pcbWritten); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE Commit( 
			/* [in] */ DWORD grfCommitFlags) 
		{
			try
			{
				if (! m_Stream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_Stream->Commit(grfCommitFlags); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE Revert() 
		{
			try
			{
				if (! m_Stream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_Stream->Revert(); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE LockRegion( 
			/* [in] */ ULARGE_INTEGER libOffset,
			/* [in] */ ULARGE_INTEGER cb,
			/* [in] */ DWORD dwLockType) 
		{
			try
			{
				if (! m_Stream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_Stream->LockRegion(libOffset,cb,dwLockType); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE UnlockRegion( 
			/* [in] */ ULARGE_INTEGER libOffset,
			/* [in] */ ULARGE_INTEGER cb,
			/* [in] */ DWORD dwLockType) 
		{
			try
			{
				if (! m_Stream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_Stream->UnlockRegion(libOffset,cb,dwLockType); 
				if (FAILED(rc)) throw MethodError(rc); 
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE Stat( 
			/* [out] */ STATSTG *pstatstg,
			/* [in] */ DWORD grfStatFlag) 
		{
			try
			{
				if (! m_Stream) throw MethodError(E_NOINTERFACE); 
				//
				HRESULT rc = m_Stream->Stat(pstatstg,grfStatFlag); 
				//if (FAILED(rc)) throw MethodError(rc); 
#				ifdef _DEBUG
				if (FAILED(rc))
				{
					TRACE_LOG(_T("������: ") + _S(MethodError(rc).ToString())); 
				}
#				endif
				return rc; 
			}
			_ComCatch() 
		}

		HRESULT STDMETHODCALLTYPE Clone( 
			/* [out] */ IStream **ppstm) 
		{
			try
			{
				try
				{
					if (! ppstm) throw MethodError(E_POINTER); 
					//
					if (! m_Stream) throw MethodError(E_NOINTERFACE); 
					//
					CComPtr<IStream> S;
					S.Attach( Create<IStream>() ); 
					//
					CSlotDataStream* pInfo = static_cast<CSlotDataStream*>((IStream*)S); 
					//
					CComPtr<IStream> cloned; 
					HRESULT rc = m_Stream->Clone(&cloned); 
					if (FAILED(rc)) throw MethodError(rc); 
					if (! cloned) throw MethodError(E_UNEXPECTED); 
					//
					pInfo->m_Stream.Attach( cloned.Detach() ); 
					//
					// ��������� 
					//
					for (Map<string,string>::Iterator i(m_Parameters); i; ++i)
					{
						string name = i.Id();
						string value = i;
						//
						pInfo->m_Parameters[name] = value; 
					}
					//
					*ppstm = S.Detach(); 
					return S_OK; 
				}
				_ComCatch() 
			}
			_ComCatch() 
		}
	};
	// CSlotDataStream 



	typedef CSlotDataStreamT<> CSlotDataStream;

	typedef CSlotDataStreamT<ISequentialStream> CSlotDataSequentialStream; 

} // namespace  
