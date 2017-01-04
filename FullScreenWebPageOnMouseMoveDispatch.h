// ---------------------------------------------------------------------------

#ifndef FullScreenWebPageOnMouseMoveDispatchH
#define FullScreenWebPageOnMouseMoveDispatchH

#include "FullScreenWebPageMouseMove.h"

class TOnMouseMoveDispatch : public IDispatch {
	long m_cRef;

	IMouseMove *m_MouseMove;

public:
	TOnMouseMoveDispatch(IMouseMove *MouseMove) : m_cRef(1) {
		m_MouseMove = MouseMove;
	}

	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv) {
		*ppv = NULL;

		if (IsEqualGUID(riid, IID_IUnknown))
			* ppv = reinterpret_cast<void**>(this);
		else if (IsEqualGUID(riid, IID_IDispatch))
			* ppv = reinterpret_cast<void**>(this);

		if (*ppv) {
			((IUnknown*)*ppv)->AddRef();
			return S_OK;
		}
		else
			return E_NOINTERFACE;
	}

	DWORD __stdcall AddRef() {
		InterlockedIncrement(&m_cRef);
		return m_cRef;
	}

	DWORD __stdcall Release() {
		InterlockedDecrement(&m_cRef);
		if (m_cRef == 0) {
			delete this;
		}
		return m_cRef;
	}

	STDMETHOD(GetTypeInfoCount)(unsigned int FAR* pctinfo) {
		return E_NOTIMPL;
	}

	STDMETHOD(GetTypeInfo)(unsigned int iTInfo, LCID lcid,
		ITypeInfo FAR* FAR* ppTInfo) {
		return E_NOTIMPL;
	}

	STDMETHOD(GetIDsOfNames)(REFIID riid, OLECHAR FAR* FAR* rgszNames,
		unsigned int cNames, LCID lcid, DISPID FAR* rgDispId) {
		return S_OK;
	}

	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
		DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO * pExcepInfo,
		UINT * puArgErr) {
		m_MouseMove->MouseMoveEvent();

		return S_OK;
	}
};
#endif
