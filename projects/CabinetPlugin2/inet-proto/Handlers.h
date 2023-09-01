#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <ax/interfaces/ISlotRequestHandler.h>
//
// Handlers 
//
#include <inet-proto/SecurityHandler.h>



namespace  {

	struct CHandlers
	{
	public:
		// ���������� ����������, �������� ProgId 

		template<class I>
		inline static I* Create(const string& progId,IStream* composer) // new reference 
		{
			try
			{
				CComPtr<ISlotRequestHandler> handler;
				if ((progId == _PROTOCOL_PROGID_SecurityHandler) ||
					(progId == _PROTOCOL_PROGID_SecurityHandler_V10)
					)
				{
					handler.Attach(
						CSlotSecurityHandler::Create<ISlotRequestHandler>() // new reference 
						); 
					if (! handler) throw MethodError(E_NOINTERFACE); 
					//
					HRESULT rc = handler->put_Request(composer); 
					if (FAILED(rc)) throw MethodError(rc); 
				}
				else if (progId.GetLength() == 0) 
				{
					return 0; 
				}
				//
				if (! handler) throw MethodError(E_NOTIMPL); 
				//
				CComQIPtr<I> i(handler);
				if (! i) throw MethodError(E_NOTIMPL); 
				//
				return i.Detach(); 
			}
			_Catch()
		}
	};

} // namespace  
