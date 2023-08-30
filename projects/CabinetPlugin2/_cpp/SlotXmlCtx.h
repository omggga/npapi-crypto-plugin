/*
 SlotXmlCtx.h : XML-��������, ���������� ������ �������  

 $Name: work1 $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/24 07:48:40 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include "../low-level/SmartXml.h"

namespace  {

	class XmlContext
	{
	protected:
		XmlDocument m_ContextXml;

		XmlElement m_ContextRoot;

		inline void Clear()
		{
			m_ContextExternal = false; 
		}

	public:
		XmlContext()
		{
			Clear();
		}

		virtual ~XmlContext() 
		{
			try
			{
				if (m_ContextExternal)
				{
					//if (m_ContextXml)
					//{
					//	HRESULT rc = (m_ContextXml.GetXmlObjectInterface())->putref_documentElement(NULL); 
					//	if (FAILED(rc)) throw MethodError(rc); 
					//}
				}
			}
			_Catch()
		}

		inline void ContextLoad(const CString& path)
		{
			try
			{
				if (m_ContextXml) m_ContextXml.Dispose();
				//
				m_ContextXml.Load(_W(path));
				//
				// TODO: if (! m_ContextXml) throw MethodError(E_UNEXPECTED);
				//
				OpenRoot();
			}
			_Catch()
		}

		inline void ContextLoadXmlStr(const string& xml)
		{
			try
			{
				m_ContextXml.Dispose();
				//
				m_ContextXml.LoadXml(xml);
				//
				// TODO: if (! m_ContextXml) throw MethodError(E_UNEXPECTED);
				//
				OpenRoot(); 
			}
			_Catch()
		}

		inline void ContextLoadEmpty()
		{
			try
			{
				m_ContextRoot.Dispose();
				m_ContextXml.Dispose();
				//
				ContextLoadXmlStr(_W(COMMON_XML_START) + L"<root />"); 
			}
			_Catch()
		}

		bool m_ContextExternal;

		void SetContext(IXMLDOMElement* context)
		{
			try
			{
				// ���������� ����� �������� 
				//
				if (! context) throw MethodError(E_INVALIDARG); 
				//
				//if (true) // (! m_ContextXml)
				//{
				//	ContextLoadEmpty(); 
				//}
				////
				//HRESULT rc = m_ContextXml->putref_documentElement(context); 
				//if (FAILED(rc)) throw MethodError(rc);
				////
				//////context->AddRef(); 
				////
				//if (m_ContextRoot) m_ContextRoot.Release();
				////
				//rc = m_ContextXml->get_documentElement(&m_ContextRoot); 
				//if (FAILED(rc)) throw MethodError(rc);
				//if (! m_ContextRoot) throw MethodError(E_UNEXPECTED);
				//
				m_ContextXml.Dispose(); 
				//
				m_ContextRoot = context; 
			}
			_Catch()
		}

		IXMLDOMElement* ReleaseContext2() // borrowed 
		{
			try
			{
				if (m_ContextRoot.IsEmpty()) throw MethodError(E_POINTER); 
				//
				return m_ContextRoot.GetXmlObjectInterface(); 
			}
			_Catch()
		}

		inline IXMLDOMDocument* ContextXml() // borrowed 
		{
			try
			{
				if (m_ContextXml.IsEmpty())
				{
					throw MethodError(E_INVALIDARG); 
				}
				return m_ContextXml.GetXmlObjectInterface();
			}
			_Catch()
		}

	protected:
		inline void OpenRoot()
		{
			try
			{
				if (! m_ContextRoot.IsEmpty()) return;
				//
				if (m_ContextXml.IsEmpty())
				{
					throw MethodError(E_INVALIDARG); 
				}
				//
				m_ContextRoot = m_ContextXml.DocumentElement();
			}
			_Catch()
		}

	public:
		inline IXMLDOMElement* ContextRoot() // borrowed reference 
		{
			try
			{
				OpenRoot();
				//
				return m_ContextRoot.GetXmlObjectInterface();
			}
			_Catch()
		}

		string GetAttribute(const string& name,const string& elementXPath=L"/*")
		{
			try
			{
				const string empty = L"";
				//
				if (m_ContextRoot.IsEmpty()) return L""; // throw MethodError(E_UNEXPECTED); 
				//
				CComPtr<IXMLDOMNode> node;
				HRESULT rc = m_ContextRoot.GetXmlObjectInterface()->selectSingleNode(
					CComBSTR(elementXPath),&node);
				if (FAILED(rc)) throw MethodError(rc);
				if ((rc == S_OK) && (node))
				{
					DOMNodeType t;
					rc = node->get_nodeType(&t);
					if (FAILED(rc)) throw MethodError(rc);
					//
					if (t != NODE_ELEMENT) throw MethodError(E_INVALIDARG);
					//
					CComQIPtr<IXMLDOMElement> E(node);
					if (! E) throw MethodError(E_UNEXPECTED);
					//
					CComVariant v;
					rc = E->getAttribute(CComBSTR(name),&v);
					if (rc == S_OK)
					{
						if (v.vt == VT_BSTR)
						{
							string value(v.bstrVal);
							return value; 
						}
					}
				}
				return empty; 
			}
			_Catch()
		}

		bool GetFlag(const string& name,const string& elementXPath=L"/*")
		{
			try
			{
				string v = GetAttribute(name,elementXPath);
				v.Trim();
				v.MakeLower();
				//
				bool x = false;
				if ((v == L"true") || (v == L"1") || (v == L"-1") || (v == "yes") || (v == "��") || (v == "on"))
				{
					x = true;
				}
				return x;
			}
			_Catch()
		}

		void SetAttribute(const string& name,const string& value,const string& elementXPath=L"/*")
		{
			try
			{
				if (m_ContextRoot.IsEmpty()) throw MethodError(E_UNEXPECTED); 
				//
				CComPtr<IXMLDOMNode> node;
				HRESULT rc = m_ContextRoot.GetXmlObjectInterface()->selectSingleNode(
					CComBSTR(elementXPath),&node);
				if (FAILED(rc)) throw MethodError(rc);
				if ((rc == S_OK) && (node))
				{
					DOMNodeType t;
					rc = node->get_nodeType(&t);
					if (FAILED(rc)) throw MethodError(rc);
					//
					if (t != NODE_ELEMENT) throw MethodError(E_INVALIDARG);
					//
					CComQIPtr<IXMLDOMElement> E(node);
					if (! E) throw MethodError(E_UNEXPECTED);
					//
					rc = E->setAttribute(CComBSTR(name),CComVariant(CComBSTR(value)));
					if (FAILED(rc)) throw MethodError(rc); 
				}
				else
				{
					throw MethodError(E_INVALIDARG);
				}
			}
			_Catch()
		}

		void AddContext(IXMLDOMElement* C) 
		{
			try
			{
				if (! C) return; // ��� ��������� 
				//
				if (m_ContextRoot.IsEmpty()) throw MethodError(E_UNEXPECTED); 
				//
				CComPtr<IXMLDOMNode> C_node;
				HRESULT rc = C->cloneNode(VARIANT_TRUE,&C_node);
				if (FAILED(rc)) throw MethodError(rc);
				if (! C_node) throw MethodError(E_UNEXPECTED);
				//
				CComPtr<IXMLDOMNode> newChild;
				rc = m_ContextRoot.GetXmlObjectInterface()->appendChild(C_node,&newChild);
				if (FAILED(rc)) throw MethodError(rc);
			}
			_Catch()
		}
	};

} // namespace  
