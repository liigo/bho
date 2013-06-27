// BhoApp.h : Declaration of the CBhoApp

#ifndef __BHOAPP_H_
#define __BHOAPP_H_

#include "resource.h"       // main symbols
#include<atlcom.h>
#include<atlbase.h>
#include "Exdisp.h"
/////////////////////////////////////////////////////////////////////////////
// CBhoApp
class ATL_NO_VTABLE CBhoApp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBhoApp, &CLSID_BhoApp>,
	public IObjectWithSiteImpl<CBhoApp>,
	public IConnectionPointContainerImpl<CBhoApp>,
	public IDispatchImpl<IBhoApp, &IID_IBhoApp, &LIBID_LiigoBhoLib>
{
public:
	CBhoApp()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BHOAPP)
DECLARE_NOT_AGGREGATABLE(CBhoApp)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBhoApp)
	COM_INTERFACE_ENTRY(IBhoApp)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CBhoApp)
END_CONNECTION_POINT_MAP()


// IBhoApp
public:
	STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid,LCID lcid, WORD wFlags, DISPPARAMS* pDispParams,VARIANT* pvarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr);
	STDMETHOD(SetSite)(IUnknown *pUnkSite);
	CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> m_spWebBrowser2;  
private:
	HRESULT Connect(void);
	DWORD m_dwCookie;
	CComQIPtr<IConnectionPointContainer,&IID_IConnectionPointContainer> m_spCPC;
};

#endif //__BHOAPP_H_
