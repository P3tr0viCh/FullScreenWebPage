// ---------------------------------------------------------------------------

#ifndef FullScreenWebPageDocHandlerH
#define FullScreenWebPageDocHandlerH

#include "mshtmhst.h"
#include "SHDocVw_OCX.h"

// ---------------------------------------------------------------------------
class TDocHandler : public IDocHostUIHandler {
	long m_cRef;

private:

	TPopupMenu *m_PopupMenu;

public:

	TDocHandler(TPopupMenu *PopupMenu) : m_cRef(1) {
		m_PopupMenu = PopupMenu;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv) {
		if (riid == IID_IUnknown) {
			*ppv = (IUnknown*)this;
		}
		else {
			if (riid == IID_IDocHostUIHandler) {
				*ppv = (IDocHostUIHandler*)this;
			}
			else {
				return E_NOINTERFACE;
			}
		}

		return S_OK;
	}

	virtual ULONG STDMETHODCALLTYPE AddRef() {
		InterlockedIncrement(&m_cRef);
		return m_cRef;
	}

	virtual ULONG STDMETHODCALLTYPE Release() {
		InterlockedDecrement(&m_cRef);
		if (m_cRef == 0) {
			delete this;
		}
		return m_cRef;
	}

	virtual HRESULT STDMETHODCALLTYPE ShowContextMenu(
		/* [in] */ DWORD dwID,
		/* [in] */ POINT __RPC_FAR *ppt,
		/* [in] */ IUnknown __RPC_FAR *pcmdtReserved,
		/* [in] */ IDispatch __RPC_FAR *pdispReserved) {

		if (m_PopupMenu != NULL) {
			m_PopupMenu->Popup(ppt->x, ppt->y);
			return S_OK;
		}

		return S_FALSE;
	}

	virtual HRESULT STDMETHODCALLTYPE GetHostInfo(
		/* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE ShowUI(
		/* [in] */ DWORD dwID,
		/* [in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
		/* [in] */ IOleCommandTarget __RPC_FAR *pCommandTarget,
		/* [in] */ IOleInPlaceFrame __RPC_FAR *pFrame,
		/* [in] */ IOleInPlaceUIWindow __RPC_FAR *pDoc) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE HideUI(void) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE UpdateUI(void) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE EnableModeless(
		/* [in] */ BOOL fEnable) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate(
		/* [in] */ BOOL fActivate) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(
		/* [in] */ BOOL fActivate) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE ResizeBorder(
		/* [in] */ LPCRECT prcBorder,
		/* [in] */ IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
		/* [in] */ BOOL fRameWindow) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(
		/* [in] */ LPMSG lpMsg,
		/* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
		/* [in] */ DWORD nCmdID) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath(
		/* [out] */ LPOLESTR __RPC_FAR *pchKey,
		/* [in] */ DWORD dw) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDropTarget(
		/* [in] */ IDropTarget __RPC_FAR *pDropTarget,
		/* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetExternal(
		/* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE TranslateUrl(
		/* [in] */ DWORD dwTranslate,
		/* [in] */ OLECHAR __RPC_FAR *pchURLIn,
		/* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut) {
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE FilterDataObject(
		/* [in] */ IDataObject __RPC_FAR *pDO,
		/* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet) {
		return E_NOTIMPL;
	}
};
#endif
