/*
 COM-��������� ISlotCrypt --- ����������������� ������� �� ��������� ���� � 34.10-2001.

 $Name: work1 $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/10 15:09:16 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

namespace 
{
	namespace SlotCryptPassiveOperations
	{
		/* PassiveOperation */

		enum PassiveOperation
		{
			PassiveOperation_NoOp   = 0, // ��������� �������� �� ���������� 
			PassiveOperation_Verify = 1, // �������� ������� 
			PassiveOperation_Hash   = 2, // ����������� �������� 
			PassiveOperation_Sign   = 3  // ������� �������� 
		};

		/* State */

		enum PassiveState
		{
			State_Idle     = 0, // ������������ 
			//
			// ����� ��������, ����������� ���������: @a="..."
			State_SearchingTargetByAttribute  = 1, 
			// ����������� �������� 
			PassiveOperationState_HashingTarget = 2, 
			//
			PassiveOperationState_Verify_0 = 10, 
			PassiveOperationState_Verify_1 = 11, 
			//
			State_HashTarget_Begin = 20, 
			State_HashTarget_CollectingNs = 21, 
			State_HashTarget_Hashing = 22, 
		};

		/* Command */

		enum PassiveCommand 
		{
			Command_Idle  = 0, // ��� ����������
			Command_Sync  = 1, // ������� ������� Sync() 
			Command_Begin = 2, // � ������!
			Command_Write = 3, // ����!
			Command_Ready = 4  // ������
		};

		/* SyncAction */

		enum SyncAction 
		{
			SyncAction_Sync = 0, // ��������� ��� ���������: ��� �������������� ���������� / �������
			SyncAction_Completed  = 1, // ��������� ������������������ �������� 
			SyncAction_Ready  = 1 // ������� � ��������� �������, ��� �������������� ������ 
		};

	} // namespace SlotCryptPassiveOperations 
} // namespace  





/* ISlotCrypt */

#ifdef AX_ISlotCrypt_IDL
[
	object,
	uuid("340726C4-C33C-44b8-AEE7-AFADF9B48757"),
	oleautomation,	
	helpstring("ISlotCrypt Interface"),
	pointer_default(unique)
]
#else
[
	uuid("340726C4-C33C-44b8-AEE7-AFADF9B48757"),
	helpstring("ISlotCrypt Interface")
]
#endif
__interface ISlotCrypt : public IUnknown 
{
public:
	// ----
	// ������������

	STDMETHOD(SetKeyTempPath)([in] BSTR keyTempPath);

	STDMETHOD(CreateRootCertificate)([in] BSTR commonName);
 
	// ----
	// XML � �������� ������� ds:Signature 
	// ��������� �����

	STDMETHOD(getDocument)([out] IUnknown** out_pDocument);

	STDMETHOD(getPassiveOperation)([out] int* out_pOp);

	STDMETHOD(getPassiveOperationState)([out] int* out_pOpState);

	STDMETHOD(getPassiveCommand)([out] int* out_pCommand);

	// ������� ��������� ��������� ������ 

	STDMETHOD(Sync)(int syncAction);

	// Hash : Passive mode 

	STDMETHOD(HashPassiveStart)([in] BSTR search);

	STDMETHOD(HashPassiveResult)([out] BSTR* out_hash64);

	// Signature : Verify : Passive mode 

	STDMETHOD(VerifySignaturePassiveStart)([in] BSTR search); // 

	STDMETHOD(VerifySignaturePassiveResult)([out] BSTR* message); 



	// ----
	// XML � �������� ������� ds:Signature 
	// �������� �����

	STDMETHOD(HashUrl)([in] BSTR url,[in] BSTR search,[out] BSTR* out_hash64);

	STDMETHOD(Hash)([in] IStream* stream,[in] BSTR search,[out] BSTR* out_hash64);






	// Signature : Verify : Active mode 

      STDMETHOD(SignElementByXPath)(
            [in] IStream* pKeyInfoStream,
            [in] IStream* pCertInfoStream,
            [in] IStream* pDocumentStream,
            [in] BSTR xPath,
            [in] IStream* pXsltStream,
            [in] IStream* pXsltArgStream,
            [out] IStream** ppSignedDocumentStream,
            [out] IStream** ppOutHashStream); 
 
      STDMETHOD(VerifySignature)(
            [in] IUnknown* pDocumentStream,
            [in] BSTR xPath,
            [out, retval] BSTR* message);
            
      STDMETHOD(HashOfElement)(
            [in] IStream* pDocumentStream,
            [in] BSTR xPath);
      
      STDMETHOD(ExpandCertInfo)(
            [in] IStream* pCertInfoStream,
            [out, retval] IStream** ppFullCertInfoStream);




	  STDMETHOD(Test)(
		  );

	STDMETHOD(Test0)();

	STDMETHOD(Test1)([in] IUnknown* pUnk);

	  STDMETHOD(Test2)(
		  [in] BSTR text
		  );

	  STDMETHOD(Test3)(
		  [in] BSTR text,
		  [out, retval] BSTR* result
		  );

	  STDMETHOD(Test4)(
		  [in] IUnknown* pUnk
		  );

	  STDMETHOD(Test5)(
		  [in] BYTE* p
		  );
}; 

 

 

