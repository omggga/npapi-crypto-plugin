/*
 LocalGate.h : ������ IGate :
	�������� ����, �� ��� ��������� ������ ��������� [].
	��������� ������� ���� ������ �� ���������� ����, ���� ����������� � �������
	���� �������� ����������� �����.

 $Name: work1 $
 $Revision: 1.1.2.4 $
 $Date: 2008/10/10 15:09:16 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <alg/Alg_1_8_1.h>
#include <low-level/SmartWeb.h>
#include <SlotAsn.h>
#include <SlotCSP_CCOM.h>
//
#include <ax/interfaces/ISlotCrypt.h>
#include <ax/interfaces/ISAXPassiveReader.h>

using namespace ::::Algorithms;
using namespace ::::SlotCryptPassiveOperations;
using namespace ::::Web;



class ISlotCryptDocumentConnector
{
public:
	// ISequentialStream

	STDMETHOD(Read)(
		void* pv,
		ULONG cb,
		ULONG* pcbRead) =0;

	STDMETHOD(Write)(
		void const* pv,
		ULONG cb,
		ULONG* pcbWritten) =0;
};






// CSlotCrypt 
[
	coclass,
	threading("apartment"),
	vi_progid(".SlotCryptDocumentStream"),
	progid(".SlotCryptDocumentStream.1"),
	version(1.0),
	uuid("9CB30871-2D14-45b5-BEC1-644D2868F846"),
	default(ISequentialStream),
	helpstring(".SlotCryptDocumentStream Class")
]
class ATL_NO_VTABLE CSlotCryptDocumentStream : public ISequentialStream
{
	// ISlotCryptDocumentConnector

	ISlotCryptDocumentConnector* Connector;

public:
	STDMETHOD(SetConnector)(ISlotCryptDocumentConnector* C)
	{
		try
		{
			Connector = C;
			return S_OK;
		}
		_ComCatch()
	}

	CSlotCryptDocumentStream()
	{
		Connector = 0;
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease() 
	{
	}



	// ISequentialStream

	STDMETHOD(Read)(
		void* pv,
		ULONG cb,
		ULONG* pcbRead
		)
	{
		//TRACE_LOG(_T("Connector..."));
		try
		{
			//TRACE_LOG(_T("RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"));
			//BYTE* pv1 = *((BYTE**)pv);
			BYTE* pv1 = (BYTE*)pv;
			pv1[0] = 7;
			pv1[1] = 8;
			pv1[2] = 9;
			*pcbRead = 3;
			return S_OK;
			return Connector->Read(pv,cb,pcbRead);
		}
		_ComCatch()
	}

	STDMETHOD(Write)(
		void const* pv,
		ULONG cb,
		ULONG* pcbWritten
		)
	{
		//TRACE_LOG(_T("Connector..."));
		try
		{
			if (! Connector)
			{
				CopyMemory(&Connector,pv,sizeof(ISlotCryptDocumentConnector*));
				return S_OK;
			}
			else
			{
				return Connector->Write(pv,cb,pcbWritten);
			}
		}
		_ComCatch()
	}
};













// CSlotCrypt 
[
	coclass,
	threading("apartment"),
	vi_progid(".SlotCrypt"),
	progid(".SlotCrypt.1"),
	version(1.0),
	uuid("008B6DBA-247C-4af9-A107-D73741A8EE51"),
	default(ISlotCrypt),
	helpstring(".SlotCrypt Class")
]
class ATL_NO_VTABLE CSlotCrypt : public ISlotCrypt, ISlotCryptDocumentConnector 
{
public:
	CSlotCrypt()
	{
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease() 
	{
		////if (iSaxPassiveReader) iSaxPassiveReader.Detach();
	}

protected:

public:
	// ----
	// ����� ���������� ������ ���������
	// ������� �������� ������ ���������� ������ � ���� �����

	STDMETHOD(getDocument)(IUnknown** out_pDocument)
	{
		try
		{
			//TRACE_LOG(_T("0"));
			if (! out_pDocument) return E_POINTER;
			//TRACE_LINE1(_T("out_pDocument: 0x%x"), (int)out_pDocument );
			//
			//TRACE_LOG(_T("1"));
			CComPtr<ISequentialStream> stream;
			HRESULT rc = stream.CoCreateInstance(L".SlotCryptDocumentStream");
			if (FAILED(rc)) throw MethodError(rc);
			//
			ISlotCryptDocumentConnector* C = static_cast<ISlotCryptDocumentConnector*>(this);
			rc = stream->Write(&C,sizeof(ISlotCryptDocumentConnector*),0);
			if (FAILED(rc)) throw MethodError(rc);
			//
			//TRACE_LOG(_T("2"));
			IUnknown* u = static_cast<IUnknown*>(stream.Detach());
			if (! u) throw MethodError(E_POINTER);
			//
			//TRACE_LOG(_T("3"));
			*out_pDocument = u;
			return S_OK;
		}
		_ComCatch()
	}

	//inline void HashBlock(Blob data)
	//{
	//	try
	//	{
	//		throw MethodError(E_NOTIMPL);
	//	}
	//	_Catch()
	//}







	// ----
	// ���������� ���������� ���������� 

	PassiveOperation Operation;

	PassiveState State;

	PassiveCommand Command;

	STDMETHOD(getPassiveOperation)(int* out_pOp)
	{
		try
		{
			//TRACE_LOG(_T("0"));
			if (! out_pOp) return E_POINTER;
			//
			//TRACE_LINE1(_T("Operation: %d"), (int)Operation );
			*out_pOp = Operation;
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(getPassiveOperationState)(int* out_pOpState)
	{
		try
		{
			if (! out_pOpState) return E_POINTER;
			//
			//TRACE_LINE1(_T("State: %d"), (int)State );
			*out_pOpState = State; 
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(getPassiveCommand)(int* out_pCommand)
	{
		try
		{
			//TRACE_LOG(_T("0"));
			if (! out_pCommand) return E_POINTER;
			//
			*out_pCommand = Command; 
			return S_OK;
		}
		_ComCatch()
	}

	inline void SetIdleState()
	{
		Operation = PassiveOperation_NoOp;
		State = State_Idle;
	}

	inline void AssertIdleOperation()
	{
		if (Operation == PassiveOperation_NoOp)
		{
			throw MethodError(_S("������� �������� %d") % (int)Operation );
		}
	}






	// ----
	// ����� ��������� ��������� �������� ��������� XML

	SharedPtr<SaxPassiveReader> PassiveReader;

	string TargetSearch;

	string TargetXPath;

	string TargetAttribute;

	string TargetAttributeValue;

	inline void ParseTargetSearch()
	{
		string msgBadFormat = L"���������������� ������ ��������� XPath: " + TargetXPath;
		//
		try
		{
			string xpp_start = L"#xpointer(//*[@";
			//
			string s(TargetSearch);
			s.Trim();
			//
			if (! (s.Left(xpp_start.GetLength()) == xpp_start)) 
			{
				TargetXPath = TargetSearch;
				return; // TODO: ���������� ���������?
			}
			//
			s = s.Right(s.GetLength() - xpp_start.GetLength());
			//
			if (s.GetLength() <= 2) throw MethodError(msgBadFormat + L" (2)");
			//
			if (s.Right(2) != L")]") throw MethodError(msgBadFormat + L" (3)");
			//
			s = s.Left(s.GetLength() - 2);
			//
			SharedArray<string> parts = s / L"=";
			//
			// .......................................
			throw MethodError(E_NOTIMPL);
		}
		_Catch()		
	}



	SharedPtr<Alg_1_8_1> A1;

	CComPtr<ISAXPassiveReader> iSaxPassiveReader;

	//void StartHashing()
	//{
	//	try
	//	{
	//		A1 = new Alg_1_8_1();
	//		//
	//		//////CComQIPtr<ISAXPassiveReader> reader(
	//		//////	A1->PassiveReader.NormalizePassiveStart()
	//		//////	);
	//		////////
	//		//////iSaxPassiveReader.Attach(reader.Detach());
	//	}
	//	_Catch()
	//}






	// ----
	// ������� ��������� ��������� ������ 



	// ----
	// ISequentialStream

	STDMETHOD(Read)(
		void* pv,
		ULONG cb,
		ULONG* pcbRead
		)
	{
		//TRACE_LOG(_T("0"));
		try
		{
			return E_NOTIMPL;
		}
		_ComCatch()
	}

	STDMETHOD(Write)(
		void const* pv,
		ULONG cb,
		ULONG* pcbWritten
		)
	{
		try
		{
			if (cb <= 0) return S_OK;
			//
			if (
				(State == State_HashTarget_CollectingNs) || 
				(State == State_HashTarget_Hashing) 
				)
			{
				HRESULT rW = iSaxPassiveReader->PassiveWrite((const BYTE*)pv,cb,pcbWritten);		
				//
				// ����������� 
				//
				return S_OK;
			}
			else
			{
				string msg = FormatStr(L"��������� ���������: %d", (int)State );
				throw MethodError(msg);
			}
			//
			//
			//
			//static int S = 0;
			//static int Sd = 0;
			////
			//if (S == 0)
			//{
			//	CStringW a((const wchar_t*)pv,(int)cb/2);
			//	TRACE_LOG1(_T("������: %s"), _S(a).GetString() );
			//}
			////
			//S += cb;
			//if (S > Sd + 10000000)
			//{
			//	TRACE_LINE1(_T("S: %d"), (int)S );
			//	Sd = S;
			//	//
			//	//////CStringW a((const wchar_t*)pv,(int)cb/2);
			//	//////TRACE_LOG1(_T("������: %s"), _S(a).GetString() );
			//}
			////
			//if (pcbWritten) *pcbWritten = cb;
			//return S_OK;
		}
		_ComCatch()
	}



	STDMETHOD(Sync)(int syncAction)
	{
		try
		{
			if (State == State_HashTarget_Begin)
			{
				if (syncAction == SyncAction_Sync)
				{
					////State = State_HashTarget_Hashing;
					State = State_HashTarget_CollectingNs;
					Command = Command_Write;
				}
				else
				{
					return S_FALSE;
				}
			}
			else if ((State == State_HashTarget_Hashing) || (State == State_HashTarget_CollectingNs)) 
			{
				if (syncAction == SyncAction_Sync)
				{
					//State == (State_HashTarget_Hashing || State_HashTarget_CollectingNs);
					Command = Command_Write;
				}
				else if (syncAction == SyncAction_Completed) // ������ �� ����������, ��� ��� written == 0 
				{
					if (State == State_HashTarget_Hashing)
					{
						// ������! 
						State == State_Idle; // ����! 
						Command = Command_Ready;
					}
					else // State == State_HashTarget_CollectingNs 
					{
						State = State_HashTarget_Hashing;
						Command = Command_Begin;
					}
				}
				else
				{
					return S_FALSE;
				}
			}
			else
			{
				//TRACE_LOG2(_T("Unknown State:%d (Action %d)"), (int)State, (int)syncAction );
				return S_FALSE;
			}
			//
			return S_OK;
		}
		_ComCatch()
	}






	// ----
	// Hash : Passive mode 

	STDMETHOD(HashPassiveStart)(BSTR search)
	{
		try
		{
			AssertIdleOperation();
			//
			//TRACE_LOG(_T("1"));
			TargetSearch = string(search);
			ParseTargetSearch();
			//
			// ������������ 
			//
			A1 = new Alg_1_8_1();
			ISAXXMLReader* iSaxReader = A1->NormalizePassiveStart(); // borrowed 
			if (! iSaxReader ) throw MethodError(L"����������� ��������� ISAXXMLReader");
			if (iSaxPassiveReader) iSaxPassiveReader.Release();
			iSaxPassiveReader.Attach(
				CComQIPtr<ISAXPassiveReader>(iSaxReader).Detach()
				); 
			//
			// ��������� 
			//
			State = State_HashTarget_Begin;
			Command = Command_Begin;
			//
			Operation = PassiveOperation_Hash;
			//
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(HashPassiveResult)(BSTR* out_hash64)
	{
		try
		{
			if (! out_hash64) throw MethodError(E_POINTER);
			//
			string hash64 = L"123";
			CComBSTR bstrHash64(hash64);
			*out_hash64 = bstrHash64.Detach();
			return S_OK;
		}
		_ComCatch()
	}



	// ----
	// Signature : Verify : Passive mode

	STDMETHOD(VerifySignaturePassiveStart)(BSTR search) // 
	{
		try
		{
			//CComBSTR xPath = L"/*";
			//TRACE_LOG(_T("XPath: ") + _S(search));
			//
			AssertIdleOperation();
			//
			//TRACE_LOG(_T("1"));
			TargetSearch = string(search);
			ParseTargetSearch();
			//
			//TRACE_LOG(_T("2"));
			State = State_HashTarget_Begin;
			Command = Command_Begin;
			//
			Operation = PassiveOperation_Verify;
			//
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(VerifySignaturePassiveResult)(
		BSTR* message) 
	{
		try
		{
			return S_OK;
		}
		_ComCatch()
	}



	// ----
	// XML � �������� ������� ds:Signature 
	// �������� �����

	static Agent& GetAgent()
	{
		static bool ready = false;
		static SharedPtr<Agent> pAgent;
		//
		if (! ready)
		{
			pAgent = new Agent(L"SlotCryptAx");
			ready = true;
		}
		return *pAgent;
	}

	SharedPtr<Connection> pConnection;

	inline Connection& WebConnection()
	{
		if (pConnection.IsEmpty())
		{
			pConnection = new Connection(GetAgent());
		}
		return *pConnection;
	}

	STDMETHOD(HashUrl)(BSTR url,BSTR search,BSTR* out_hash64) // COM-style 
	{
		try
		{
			// ----
			// �������� ��������
			//
			Request r(WebConnection(),_W(url));
			//
			CComQIPtr<IStream> inputStream(r.GetResponseStream());
			if (! inputStream) throw MethodError(L"�� ������ �������� ��������� IStream");
			//
			return HashStream(inputStream,search,out_hash64); 
		}
		_ComCatch()
	}

	STDMETHOD(HashStream)(IStream* inputStream,BSTR search,BSTR* out_hash64) // COM-style 
	{
		const int dS = 1024;
		//
		try
		{
			if (! inputStream) throw MethodError(E_POINTER);
			//
			// ----
			// Document: ����� ��� ������ ������ �� ���������
			//
			CComPtr<IUnknown> doc_u;
			HRESULT rc = getDocument(&doc_u);
			if (FAILED(rc)) throw MethodError(rc);
			//
			CComQIPtr<ISequentialStream> workerStream(doc_u); 
			if (! workerStream) throw MethodError(L"�� ������ �������� ��������� ISequentialStream");
			//
			// ----
			// �������� 
			//
			string search_s(search);
			rc = HashPassiveStart(CComBSTR(search_s)); 
			if (FAILED(rc)) throw MethodError(rc);
			//
			int pos = 0;
			//
			bool done = false;
			while (!done)
			{
				SyncAction syncAction = SyncAction_Sync;
				//
				int command;
				HRESULT r2 = getPassiveCommand(&command);
				if (FAILED(r2)) throw MethodError(r2); 
				//
				if (command == (int)Command_Begin)
				{
					///pos = 0;
					//
					LARGE_INTEGER zeroPos; 
					ZeroMemory(&zeroPos,sizeof(zeroPos));
					HRESULT r3 = inputStream->Seek(zeroPos,FILE_BEGIN,0); 
					if (r3 != S_OK) throw MethodError(r3); 
				}
				else if (command == (int)Command_Write)
				{
					int n = dS;
					//if (pos + n > data.Length()) n = data.Length() - pos;
					//if (n > 0)
					//{
					//	ULONG bytesWritten = 0;
					//	HRESULT rc1 = workerStream->Write(data.GetBuffer() + pos,n,&bytesWritten);
					//	if (FAILED(rc1)) throw MethodError(rc1);
					//}
					////
					//if ((n == 0) || (pos + n == data.Length())) n = 0;
					//
					Blob data;
					data.Allocate(dS);
					ULONG bytesRead = 0;
					//
					HRESULT rc0 = inputStream->Read(data.GetBuffer(),dS,&bytesRead);
					if (FAILED(rc0)) throw MethodError(rc0);
					//
					n = bytesRead;
					//
					ULONG bytesWritten = 0;
					HRESULT rc1 = workerStream->Write(data.GetBuffer(),n,&bytesWritten);
					if (FAILED(rc1)) throw MethodError(rc1);
					//
					if (n > 0)
					{
						// syncAction = SyncAction.SyncAction_Sync;
					}
					else
					{
						syncAction = SyncAction_Completed;
					}
				}
				else if (command == (int)Command_Ready)
				{
					done = true;
					syncAction = SyncAction_Ready;
				}
				//
				if (command != (int)Command_Idle)
				{
					int r2 = Sync((int)syncAction);
					if (FAILED(r2)) throw MethodError(r2);
				}
			}










			//const int dS = 1024;
			//for (int pos = 0; pos != -1; )
			//{
			//	int n = dS;
			//	if (pos + n > data.Length()) n = data.Length() - pos;
			//	if (n > 0)
			//	{
			//		ULONG bytesWritten = 0;
			//		HRESULT rc1 = workerStream->Write(data.GetBuffer() + pos,n,&bytesWritten);
			//		if (FAILED(rc1)) throw MethodError(rc1);
			//	}
			//	//
			//	if ((n == 0) || (pos + n == data.Length())) pos = -1;
			//}
			//
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(Hash)(IStream* stream,BSTR search,BSTR* out_hash64) 
	{
		try
		{
			return S_OK;
		}
		_ComCatch()
	}



















	STDMETHOD(SignElementByXPath)(
		IStream* pKeyInfoStream,
		IStream* pCertInfoStream,
		IStream* pDocumentStream,
		BSTR xPath,
		IStream* pXsltStream,
		IStream* pXsltArgStream,
		IStream** ppSignedDocumentStream,
		IStream** ppOutHashStream) 
	{
		try
		{
			return E_NOTIMPL;
		}
		_ComCatch()
	}

	  STDMETHOD(VerifySignature)(
			IUnknown* pDocumentStream,
			BSTR xPath,
			BSTR* message) 
	  {
		  try
		  {
			  //TRACE_LOG(_T("***\n!\nCOM-��������� ISlotCrypt\n"));
			  //
			  CComQIPtr<IStream> stream(pDocumentStream);
			  if (! stream)
			  {
				  TRACE_LOG(_T("stream == 0"));
				  return S_OK;
			  }
			  BYTE buf[1024];
			  ULONG read;
			  HRESULT rc = stream->Read(buf,1024,&read);
			  return S_OK;
			  //
			  LARGE_INTEGER m;
			  ZeroMemory(&m,sizeof(LARGE_INTEGER));
			  ULARGE_INTEGER newPos;
			  rc = stream->Seek(m,STREAM_SEEK_SET,&newPos);
			  //
			  // ----
			  // ��������� ������� ��� xPath
			  //
			  string report;
			  bool signatureOk = true;///Alg_1_8_5().VerifySignature(pDocumentStream,string(xPath),&report);
			  return signatureOk ? S_OK : S_FALSE;
		  }
		  _ComCatch()
	  }
	        
	STDMETHOD(HashOfElement)(
		IStream* pDocumentStream,
		BSTR xPath) 
	{
		try
		{
			XmlDocument d1;
			Alg_1_8_1 alg1;
			alg1.NormalizeUrl(L"http://cabinet.example.com/schema/ufml3/rel-1/ufml3.xsd");
			//
			///alg1.Transform(root_E);
			///string hash64 = Slot::Util::ToBase64String(alg1.Hasher.GetHash());
			//
			return S_OK;
		}
		_ComCatch()
	}
	  
	  STDMETHOD(ExpandCertInfo)(
			IStream* pCertInfoStream,
			IStream** ppFullCertInfoStream) 
	  {
		  try
		  {
			  return E_NOTIMPL;
		  }
		  _ComCatch()
	  }



















	// ----
	// ����� 

	STDMETHOD(Test)()
	{
		try
		{
			TRACE_LOG(_T("0"));
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(Test2)(BSTR text)
	{
		try
		{
			TRACE_LOG(_T("0\n") + _S(text));
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(Test3)(BSTR text,BSTR* result)
	{
		try
		{
			TRACE_LOG(_T("0\n") + _S(text));
			*result = CComBSTR(string(L"result: ") + string(text)).Detach();
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(Test4)(IUnknown* pUnk)
	{
		try
		{
			TRACE_LOG(_T("0"));
			TRACE_LOG1(_T("IUnknown*: 0x%x"), (int)pUnk );
			//
			ULONG n = pUnk->AddRef();
			TRACE_LOG1(_T("AddRef: %d"), (int)n );
			//
			IStream* streamU = 0;
			HRESULT rc = pUnk->QueryInterface<IStream>(&streamU);
			if (FAILED(rc))
			{
				TRACE_LOG1(_T("rc=0x%x"), (int)rc );
			}
			//
			//CComQIPtr<IStream> q(pUnk);
			//TRACE_LOG1(_T("2:\n0x%x"), (int)q.operator IStream*());
			//
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(Test5)(BYTE* p)
	{
		try
		{
			IUnknown* pUnk = static_cast<IUnknown*>((void*)p);
			TRACE_LOG(_T("0"));
			TRACE_LOG1(_T("IUnknown*: 0x%x"), (int)pUnk );
			//
			// ULONG n = pUnk->AddRef();
			// TRACE_LOG1(_T("AddRef: %d"), (int)n );
			// //
			// IStream* streamU = 0;
			// HRESULT rc = pUnk->QueryInterface<IStream>(&streamU);
			// if (FAILED(rc))
			// {
			//TRACE_LOG1(_T("rc=0x%x"), (int)rc );
			// }
			//
			//CComQIPtr<IStream> q(pUnk);
			//TRACE_LOG1(_T("2:\n0x%x"), (int)q.operator IStream*());
			//
			return S_OK;
		}
		_ComCatch()
	}






	STDMETHOD(Test0)()
	{
		try
		{
			TRACE_LOG(_T("TEST 0 ~~~~~~~~~~~~~~~~~~~~~~~~"));
			return S_OK;
		}
		_Catch()
	}



	STDMETHOD(Test1)(IUnknown* pUnk)
	{
		try
		{
			TRACE_LOG(_T("TEST 1"));
			TRACE_LINE1(_T("AddRef --> %d"), (int)pUnk->AddRef() );
			return S_OK;
		}
		_Catch()
	}



	// ----
	// ������������

	STDMETHOD(SetKeyTempPath)(
		BSTR keyTempPath)
	{               
		try
		{
			//TRACE_LOG(_T("0"));
			//TRACE_LINE1(_T("Path: %s"), _S(keyTempPath).GetString() );
			return S_OK;
		}
		_ComCatch()
	}

	STDMETHOD(CreateRootCertificate)(
		BSTR commonName)
	{
		try
		{
			// ----
			// ����
			//
			// ... 
			//
			// ----
			// ����������
			//
			Blob ct = AsnObject::CertificateTemplate();
			AsnObject cert_O(ct);
			return S_OK;
		}
		_ComCatch()
	}
};
// CSlotCrypt 
