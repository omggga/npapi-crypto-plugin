#pragma once

#include "lzexception.h"

namespace Lz {

template<class T = IXMLDOMDocument2> class XmlDoc : public CComPtr<T> //IXMLDOMDocument
{
public:
	XmlDoc() throw(_com_error)
	{
		ChkComErr(CoCreateInstance(__uuidof(FreeThreadedDOMDocument40), NULL, CLSCTX_SERVER));

		p->put_async(VARIANT_FALSE);
		p->put_preserveWhiteSpace(VARIANT_FALSE);

		p->put_validateOnParse(VARIANT_FALSE);
		p->put_resolveExternals(VARIANT_FALSE);

		p->setProperty(_bstr_t(_T("SelectionLanguage")), _variant_t("XPath"));
		SetServerHTTPRequest(false);
	};

	virtual ~XmlDoc() {};

	void SetValidationSchema(VARIANT pSchemaCollection, BOOL bValidate = FALSE)
	{
		if( (pSchemaCollection.vt & VT_DISPATCH) == VT_DISPATCH
			&& pSchemaCollection.pdispVal != NULL )
		{
			ChkComErr(p->putref_schemas(pSchemaCollection));

			if( bValidate )
			{
				p->put_validateOnParse(VARIANT_TRUE); //FALSE
				p->put_resolveExternals(VARIANT_TRUE); //resolve xmlns
			}
		}
	}

	void SetSelectionNamespaces(LPCTSTR szSelectionNamespaces)
	{
		p->setProperty(_bstr_t(_T("SelectionNamespaces")), _variant_t(szSelectionNamespaces));
	}

	void SetServerHTTPRequest(bool bUse)
	{
		p->setProperty(_bstr_t(_T("ServerHTTPRequest")), CComVariant(bUse));
	}

	void Load(VARIANT varSource) throw(_com_error)
	{
		VARIANT_BOOL fSuccess(VARIANT_TRUE);

		ChkComErr(p->load(varSource, &fSuccess));

		if( fSuccess == VARIANT_FALSE )
			CheckParseError();
	};

	void LoadXml(BSTR bstrSource) throw(_com_error)
	{
		VARIANT_BOOL fSuccess(VARIANT_TRUE);

		ChkComErr(p->loadXML(bstrSource, &fSuccess));

		if( fSuccess == VARIANT_FALSE )
			CheckParseError();
	};

	void CreateProcessor(IXSLProcessor** ppProcessor)
	{
		CComPtr<IXSLTemplate> pTemplate;

		ChkComErr(pTemplate.CoCreateInstance(__uuidof(XSLTemplate40), NULL, CLSCTX_SERVER));
		ChkComErr(pTemplate->putref_stylesheet(p));
		ChkComErr(pTemplate->createProcessor(ppProcessor));
	};

	void Transform(IXSLProcessor* pProcessor, IUnknown* pUnkOut)
	{
		VARIANT vOut, vInput;
		VARIANT_BOOL fDone;

		V_VT(&vInput) = VT_UNKNOWN;
		V_UNKNOWN(&vInput) = (IUnknown*)p;

		ChkComErr(pProcessor->put_input(vInput));

		V_VT(&vOut) = VT_UNKNOWN;
		V_UNKNOWN(&vOut) = pUnkOut;

		ChkComErr(pProcessor->put_output(vOut));
		ChkComErr(pProcessor->transform(&fDone));
	};

	void GetParseErrorInfo(IErrorInfo** ppErrorInfo)
	{
		CComBSTR url, reason, err_msg;
		long line, column, code;

		CComPtr<IXMLDOMParseError> pParseError;
		p->get_parseError(&pParseError);
		
		if( !pParseError ) return;

		pParseError->get_errorCode(&code);

		if( code == 0 ) return;

		pParseError->get_url(&url);
		pParseError->get_reason(&reason);
		pParseError->get_line(&line);
		pParseError->get_linepos(&column);

		err_msg = _T("Parse error:");

		if( reason )
		{
			err_msg.Append(_T(" "));
			err_msg.AppendBSTR(reason);
		}

		if( url )
		{
			err_msg.Append(_T(" url="));
			err_msg.AppendBSTR(url);
		}

		if( line != 0 )
		{
			char buf[100];
			sprintf(buf, " line=%u col=%u", line, column);
			err_msg.Append(buf);
		}

		CComPtr<ICreateErrorInfo> pCreatErrInfo;
//		CComQIPtr<IErrorInfo> pErrInfo;

		CreateErrorInfo(&pCreatErrInfo);

		pCreatErrInfo->SetDescription(err_msg);
		pCreatErrInfo.QueryInterface(ppErrorInfo);

//		pErrInfo = pCreatErrInfo;
	};


	void CheckParseError() throw(_com_error)
	{
		CComPtr<IErrorInfo> pErrInfo;

		GetParseErrorInfo(&pErrInfo);

		if( !pErrInfo )
			return;

		throw _com_error(E_FAIL, pErrInfo, TRUE);
	};
};


//typedef SmartPtr<XmlDoc> XmlDocPtr;

}; // namespace Lz
