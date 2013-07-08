liigo's bho
===========

A sample IE BHO for getting webbrowser's POST data in BeforeNavigate2 event.

Compiler: VC6

Install: regsvr32 full/path/to/liigobho.dll (need administrator privileges)

Uninstall: regsvr32 full/path/to/liigobho.dll (need administrator privileges)

The core code in file BhoApp.cpp list here:

	STDMETHODIMP CBhoApp::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pvarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
	{
		switch(dispidMember)
		{
		case DISPID_BEFORENAVIGATE2:
			{
				//liigo 2013-6-26:
				//there are 7 args in pDispParams->rgvarg[0] to pDispParams->rgvarg[6]
				assert(pDispParams->cArgs == 7);

				//Arg0: Cancel
				VARIANTARG argCancel = pDispParams->rgvarg[0];
				assert(argCancel.vt == (VT_BYREF|VT_BOOL));
				//we can set VARIANT_TRUE to cancel the navigation
				// *(argCancel.pboolVal) = VARIANT_TRUE;

				//Arg1: Headers
				VARIANTARG argHeaders = pDispParams->rgvarg[1];
				assert(argHeaders.vt == (VT_BYREF|VT_VARIANT));
				assert(argHeaders.pvarVal->vt == VT_BSTR);
				BSTR bstrHeaders = argHeaders.pvarVal->bstrVal;
				MessageBoxW(0, bstrHeaders, L"headers", MB_OK);

				//Arg2: PostData
				VARIANTARG argPostData = pDispParams->rgvarg[2];
				assert(argPostData.vt == (VT_BYREF|VT_VARIANT));
				assert(argPostData.pvarVal->vt == (VT_BYREF|VT_VARIANT));
				if(argPostData.pvarVal->pvarVal->vt != VT_EMPTY)
				{
					assert(argPostData.pvarVal->pvarVal->vt == (VT_ARRAY|VT_UI1));
					SAFEARRAY* pSafeArray = argPostData.pvarVal->pvarVal->parray;
					assert(pSafeArray);
					assert(pSafeArray->cDims == 1 && pSafeArray->cbElements == 1); //array of VT_UI1
					unsigned int nPostDataSize = pSafeArray->rgsabound[0].cElements * pSafeArray->cbElements; //in bytes
					void* pPostData = pSafeArray->pvData;
					ShowDataMessage(pPostData, nPostDataSize, "post data binary");
					MessageBoxA(0, (char*)pPostData, "post data string", MB_OK);
				}

				//Arg3: TargetFrameName
				VARIANTARG argTargetFrameName = pDispParams->rgvarg[3];
				assert(argTargetFrameName.vt == (VT_BYREF|VT_VARIANT));
				assert(argTargetFrameName.pvarVal->vt == VT_BSTR);
				BSTR bstrTargetFrameName = argTargetFrameName.pvarVal->bstrVal;
				MessageBoxW(0, bstrTargetFrameName, L"TargetFrameName", MB_OK);

				//Arg4: Flags
				VARIANTARG argFlags = pDispParams->rgvarg[4];
				assert(argFlags.vt == (VT_BYREF|VT_VARIANT));
				assert(argFlags.pvarVal->vt == VT_I4);
				LONG lFlags = argFlags.pvarVal->lVal;

				//Arg5: Url
				VARIANTARG argUrl = pDispParams->rgvarg[5];
				assert(argUrl.vt == (VT_BYREF|VT_VARIANT));
				assert(argUrl.pvarVal->vt == VT_BSTR);
				BSTR bstrUrl = argUrl.pvarVal->bstrVal;
				MessageBoxW(0, bstrUrl, L"URL", MB_OK);

				//Arg6: WebBrowser
				VARIANTARG argWebBrowser = pDispParams->rgvarg[6];
				assert(argWebBrowser.vt == VT_DISPATCH);
				IDispatch* pDispWebBrowser = argWebBrowser.pdispVal;

				return S_OK;
			}
