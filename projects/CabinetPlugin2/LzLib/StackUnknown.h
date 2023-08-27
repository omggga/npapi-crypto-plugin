#if !defined(INC_STACK_UNKNOWN_h_)
#define INC_STACK_UNKNOWN_h_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace Lz {

template <class Base>
class __declspec(novtable) StackUnknown : public Base
{
public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef() {return 1;}
	virtual ULONG STDMETHODCALLTYPE Release() {return 1;}
};

template <class Base>
HRESULT STDMETHODCALLTYPE
StackUnknown<Base>::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == __uuidof(Base) || riid == __uuidof(IUnknown))
	{
		// No need to AddRef since this class will only be created on the stack
		*ppv = this;
		return S_OK;
	}

	*ppv = NULL;
	return E_NOINTERFACE;
}

}; //namespace Lz

#endif // !defined(INC_STACK_UNKNOWN_h_)
