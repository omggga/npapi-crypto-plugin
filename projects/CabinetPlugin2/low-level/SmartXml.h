/*
 SmartXml.h : ������ ��� ������� ������ � DOM � SAX XML.

 $Name: work1 $
 $Revision: 1.1.2.10 $
 $Date: 2008/10/24 07:51:17 $

 */

#pragma once

#include <Msxml2.h>

#include "AtlX.h"
#include "SmartConvert_A.h"
#include "SmartWrapper.h"
#include "SmartMachine.h"

#ifndef MSXML2_DOM_VersionP
#define MSXML2_DOM_VersionP (L".6.0")
#endif

#ifndef MSXML2_DOMDOCUMENT_ProgId
#define MSXML2_DOMDOCUMENT_ProgId (_W(L"Msxml2.DOMDocument") + MSXML2_DOM_VersionP)
#endif

#ifndef MSXML2_FreeThreaded_DOMDOCUMENT_ProgId
#define MSXML2_FreeThreaded_DOMDOCUMENT_ProgId (_W(L"Msxml2.FreeThreadedDOMDocument") + MSXML2_DOM_VersionP)
#endif

#ifndef MSXML2_SAXREADER_ProgId
#define MSXML2_SAXREADER_ProgId (_W(L"Msxml2.SAXXMLReader") + MSXML2_DOM_VersionP)
#endif

#ifndef MSXML2_SAXWRITER_ProgId
#define MSXML2_SAXWRITER_ProgId (_W(L"Msxml2.SAXXMLReader") + MSXML2_DOM_VersionP)
#endif

#ifndef _SAXPASSIVEREADER_ProgId
#define _SAXPASSIVEREADER_ProgId (L".SAXPassiveReader")
#endif

#define INTERFACE_IDOMDocument IXMLDOMDocument

namespace 
{
	// ===================================================================================
	// XML

	typedef DOMNodeType XmlNodeType; 



	class XmlNodeList;
	class XmlAttributeCollection;
	class XmlElement;
	class XmlDocumentWrapper;



	// ----
	// XmlNode

	class XmlNode : public ComWrapper<IXMLDOMNode>
	{
	public:
		virtual ~XmlNode()
		{
		}

		XmlNode()
		{
		}

		XmlNode(const XmlNode& other) : Wrapper(other)
		{
		}

		XmlNode(IXMLDOMNode* other) : Wrapper(other)
		{
		}

		inline const XmlNode& operator =(const XmlNode& other)
		{
			try
			{
				AssignTo(other);
			}
			_Catch()
		}

		XmlNodeType NodeType()
		{
			try
			{
				AssertObjectNotEmpty();
				//
				DOMNodeType t = (DOMNodeType)0;
				HRESULT rc = m_p->get_nodeType(&t);
				if (FAILED(rc)) throw MethodError(rc);
				return t;
			}
			_Catch()
		}

		XmlNode Clone()
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComPtr<IXMLDOMNode> n1;
				HRESULT rc = m_p->cloneNode(VARIANT_TRUE,&n1);
				if (FAILED(rc)) throw MethodError(rc);
				return XmlNode(n1);
			}
			_Catch()
		}

		string Name()
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComBSTR b_name;
				HRESULT rc = m_p->get_nodeName(&b_name);
				if (FAILED(rc)) throw MethodError(rc);
				return string(b_name);
			}
			_Catch()
		}

		string LocalName()
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComBSTR b_localName;
				HRESULT rc = m_p->get_baseName(&b_localName);
				if (FAILED(rc)) throw MethodError(rc);
				return string(b_localName);
			}
			_Catch()
		}

		string NamespaceURI()
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComBSTR b_namespaceURI;
				HRESULT rc = m_p->get_namespaceURI(&b_namespaceURI);
				if (FAILED(rc)) throw MethodError(rc);
				return string(b_namespaceURI);
			}
			_Catch()
		}

		CComVariant VariantValue()
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComVariant v;
				HRESULT rc = m_p->get_nodeValue(&v);
				if (FAILED(rc)) throw MethodError(rc);
				return v;
			}
			_Catch()
		}

		string Value()
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComVariant v;
				HRESULT rc = m_p->get_nodeValue(&v);
				if (FAILED(rc)) throw MethodError(rc);
				return Convert_A::ToString(v);
			}
			_Catch()
		}

		CComBSTR OuterXmlAsBSTR()
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComBSTR xml1;
				HRESULT rc = m_p->get_xml(&xml1);
				if (FAILED(rc)) throw MethodError(rc);
				return xml1;
			}
			_Catch()
		}

		inline string OuterXml()
		{
			try
			{
				return string(OuterXmlAsBSTR());
			}
			_Catch()
		}

		XmlNode RemoveChild(XmlNode node)
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComPtr<IXMLDOMNode> oldChild;
				HRESULT rc = m_p->removeChild(node.m_p,&oldChild);
				if (FAILED(rc)) throw MethodError(rc);
				return XmlNode(oldChild);
			}
			_Catch()
		}

		void Remove(const string& search)
		{
			string errorMsg = L"������ �������� �����: " + search;
			//
			try
			{
				AssertObjectNotEmpty();
				//
				CComPtr<IXMLDOMNodeList> L;
				HRESULT rc = m_p->selectNodes(CComBSTR(search),&L);
				if (rc != S_OK) 
				{
					string msg_2 = L"������ � selectNodes: " + search;
					if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(msg_2);
					else throw MethodError(msg_2);
				}
				//
				long n = 0;
				rc = L->get_length(&n);
				if (FAILED(rc)) throw MethodError(rc);
				//
				for (int k = 0; k < n; ++k)
				{
					IXMLDOMNode* n1 = 0;
					rc = L->get_item(long(k),&n1);
					if (FAILED(rc)) throw MethodError(rc);
					//
					if (n1)
					{
						CComPtr<IXMLDOMNode> oldChild;
						rc = m_p->removeChild(n1,&oldChild);
						if (FAILED(rc)) throw MethodError(rc);
					}
				}
			}
			_Catch()
		}

		void RemoveAllNodes()
		{
			try
			{
				Remove(L"node()");
			}
			_Catch()
		}

		XmlNode AppendChild(XmlNode child)
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComPtr<IXMLDOMNode> newChild;
				CComQIPtr<IXMLDOMNode> childPtr(child.m_p);
				HRESULT rc = m_p->appendChild(childPtr,&newChild); 
				if (rc != S_OK) throw MethodError(rc);
				return XmlNode(newChild);
			}
			_Catch()
		}

		XmlNode ReplaceChild(XmlNode newChild, XmlNode oldChild)
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComPtr<IXMLDOMNode> pOutOldChild;
				CComQIPtr<IXMLDOMNode> newChildPtr(newChild.m_p);
				CComQIPtr<IXMLDOMNode> oldChildPtr(oldChild.m_p);
				HRESULT rc = m_p->replaceChild(newChildPtr, oldChildPtr, &pOutOldChild); 
				if (rc != S_OK) throw MethodError(rc);
				return XmlNode(newChild);
			}
			_Catch()
		}

		XmlNodeList SelectNodes(const string& search);

		XmlNode SelectSingleNode(const string& search)
		{
			string errorMsg = L"������ ��� ������ ����: " + search;
			//
			try
			{
				try
				{
					AssertObjectNotEmpty();
					//
					CComPtr<IXMLDOMNode> node;
					HRESULT rc = m_p->selectSingleNode(CComBSTR(search),&node);
					if (rc != S_OK) 
					{
						if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(errorMsg);
						else throw MethodError(errorMsg);
					}
					return XmlNode(node);
				}
				_Catch()
			}
			_AddMessage(errorMsg)
		}



		// InnerTextObject

		class InnerTextObject
		{
			XmlNode& m_parent;

		public:
			virtual ~InnerTextObject()
			{
			}

			InnerTextObject(XmlNode& parent) : m_parent(parent)
			{
			}

			const CComBSTR& operator =(const CComBSTR& rhs)
			{
				try
				{
					m_parent.RemoveAllNodes();
					//
					CComPtr<IXMLDOMDocument> doc;
					HRESULT rc = m_parent.m_p->get_ownerDocument(&doc);
					if (FAILED(rc)) throw MethodError(rc);
					//
					if (! doc) throw MethodError(L"������ ��� ��������� � ���������");
					//
					CComPtr<IXMLDOMText> textNode;
					rc = doc->createTextNode(CComBSTR(rhs),&textNode);
					if (FAILED(rc)) throw MethodError(rc);
					//
					CComPtr<IXMLDOMNode> newChild;
					rc = m_parent.m_p->appendChild(textNode,&newChild);
					if (FAILED(rc)) throw MethodError(rc);
					//
					return rhs;
				}
				_Catch()
			}

			const string& operator =(const string& rhs)
			{
				operator =(CComBSTR(rhs));
				return rhs;
			}

			operator string()
			{
				try
				{
					m_parent.AssertObjectNotEmpty();
					//
					CComPtr<IXMLDOMNodeList> L;
					HRESULT rc = m_parent.m_p->selectNodes(CComBSTR(L"text()"),&L);
					if (FAILED(rc)) throw MethodError(rc);
					//
					if (! L) throw MethodError(L"������ ��� ���������� ������ �����");
					//
					long len = 0;
					rc = L->get_length(&len);
					if (FAILED(rc)) throw MethodError(rc);
					//
					if (len == 0)
					{
						CComPtr<IXMLDOMNodeList> L;
						//
						HRESULT rc = m_parent.m_p->selectNodes(CComBSTR(L"*"),&L);
						if (FAILED(rc)) throw MethodError(rc);
						//
						rc = L->get_length(&len);
						if (FAILED(rc)) throw MethodError(rc);
						//
						if (len > 0) 
						{
							IXMLDOMNode* n1 = 0;
							rc = L->get_item(0,&n1);
							if (FAILED(rc)) throw MethodError(rc);
							if (! n1) throw MethodError(L"������ ��� ��������� � �������� ������");
							//
							CComBSTR xml1;
							HRESULT rc = n1->get_xml(&xml1); 
							if (FAILED(rc)) throw MethodError(rc);
							//
							string result(xml1);
							//
							return result; 
						}
					}
					//
					if (len == 0) return L"";
					//
					string result = L"";
					//
					for (int j = 0; j < len; ++j)
					{
						IXMLDOMNode* n1 = 0;
						rc = L->get_item(j,&n1);
						if (FAILED(rc)) throw MethodError(rc);
						if (! n1) throw MethodError(L"������ ��� ��������� � �������� ������");
						//
						CComBSTR text;
						rc = n1->get_text(&text);
						if (FAILED(rc)) throw MethodError(rc);
						//
						string t1(text);
						//
						result = result + t1; 
					}
					//
					return result; 
				}
				_Catch()
			}				
		};

		InnerTextObject InnerText()
		{
			return InnerTextObject(*this);
		}

		XmlDocumentWrapper OwnerDocument();

		

		// ----
		// XSL

		XmlDocumentWrapper TransformToXml(XmlNode xsl);
	};






	// ----
	// XmlNodeList

	class XmlNodeList : public ComWrapper<IXMLDOMNodeList> 
	{
	public:
		virtual ~XmlNodeList()
		{
		}

		XmlNodeList()
		{
		}

		XmlNodeList(const XmlNodeList& other) : Wrapper(other)
		{
		}

		XmlNodeList(IXMLDOMNodeList* other) : Wrapper(other)
		{
		}

		inline const XmlNodeList& operator =(const XmlNodeList& other)
		{
			try
			{
				AssignTo(other);
				return other; 
			}
			_Catch()
		}

		// �������� � ������ XmlNodeList

		int Count()
		{
			try
			{
				AssertObjectNotEmpty();
				//
				long size;
				HRESULT rc = m_p->get_length(&size);
				if (FAILED(rc)) throw MethodError(rc);
				return (int)size;
			}
			_Catch()
		}

		XmlNode operator [](int i)
		{
			string errorMsg = FormatStr(L"������ ��� ��������� � �������� %d ������ �����", (int)i );
			//
			try
			{
				try
				{
					AssertObjectNotEmpty();
					//
					IXMLDOMNode* n1 = 0;
					HRESULT rc = m_p->get_item(i,&n1);
					if (rc != S_OK)				
					{
						if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(errorMsg);
						else throw MethodError(errorMsg);
					}
					return XmlNode(n1);
				}
				_Catch()
			}
			_AddMessage(errorMsg)
		}

		inline XmlNode Item(int i)
		{
			return operator [](i);
		}
	};






	// ----
	// XmlAttributeCollection

	class XmlAttributeCollection : public ComWrapper<IXMLDOMNamedNodeMap> 
	{
	public:
		virtual ~XmlAttributeCollection()
		{
		}

		XmlAttributeCollection()
		{
		}

		XmlAttributeCollection(const XmlAttributeCollection& other) : Wrapper(other)
		{
		}

		XmlAttributeCollection(IXMLDOMNamedNodeMap* other) : Wrapper(other)
		{
		}

		inline const XmlAttributeCollection& operator =(const XmlAttributeCollection& other)
		{
			try
			{
				AssignTo(other);
			}
			_Catch()
		}

		// �������� � ������ XmlAttributeCollection 

		int Count()
		{
			try
			{
				if (! m_p) return 0;
				//
				long size;
				HRESULT rc = m_p->get_length(&size);
				if (FAILED(rc)) throw MethodError(rc);
				return (int)size;
			}
			_Catch()
		}

		XmlNode operator [](int i)
		{
			string errorMsg = FormatStr(L"������ ��� ��������� � �������� %d ������ �����", (int)i );
			//
			try
			{
				try
				{
					AssertObjectNotEmpty();
					//
					IXMLDOMNode* n1 = 0;
					HRESULT rc = m_p->get_item(i,&n1);
					if (rc != S_OK)				
					{
						if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(errorMsg);
						else throw MethodError(errorMsg);
					}
					return XmlNode(n1);
				}
				_Catch()
			}
			_AddMessage(errorMsg)
		}

		inline XmlNode Item(int i)
		{
			return operator [](i);
		}
	};






	// ----
	// XmlNodeObject

	template<
		class _XmlObjectInterface
	>
	class XmlNodeObject : public XmlNode 
	{
	public:
		typedef _XmlObjectInterface XmlObjectInterface;

		typedef XmlNodeObject<XmlObjectInterface> XmlObject;

	protected:
		CComPtr<XmlObjectInterface> m_XmlObject;

		inline void QueryXmlObject() 
		{
			if (m_XmlObject) return; // ������ 
			//
			if (m_p)
			{
				////CComBSTR xml1; 
				////m_p->get_xml(&xml1);
				////TRACE_LOG(_S(xml1)); 
				//
				CComQIPtr<XmlObjectInterface> q(m_p); 
				if (! q)
				{
					string msg = L"�� ������� ��������� ��������� (XmlObjectInterface) // " + _W(__FUNCTION__); 
					throw MethodError(msg); 
				}
				//throw MethodError(E_NOINTERFACE).AddIfNewSource_(msg); 
				m_XmlObject.Attach(q.Detach());
			}
		}

	public:
		void Dispose() // override
		{
			if (m_XmlObject) m_XmlObject.Release();
			//
			XmlNode::Dispose();
		}

		virtual ~XmlNodeObject()
		{
		}

		XmlNodeObject()
		{
		}

		XmlNodeObject(const XmlNodeObject& other) : XmlNode(other)
		{
			QueryXmlObject(); 
		}

		XmlNodeObject(const XmlNode& other) : XmlNode(other)
		{
			QueryXmlObject(); 
		}

		XmlNodeObject(XmlObjectInterface* other)
		{
			try
			{
				if (other)
				{
					CComQIPtr<IXMLDOMNode> q(other);
					InitialAssignTo(q);
				}
				else
				{
					InitialAssignTo(NULL);
				}
				QueryXmlObject(); 
			}
			_Catch()
		}

		const XmlNodeObject& operator =(const XmlNodeObject& other)
		{
			try
			{
				AssignTo((const XmlNode&)other);
				QueryXmlObject(); 
				return other;
			}
			_Catch()
		}

		XmlObjectInterface* operator =(XmlObjectInterface* other)
		{
			try
			{
				if (other)
				{
					CComQIPtr<IXMLDOMNode> q(other);
					AssignTo(q);
				}
				else
				{
					AssignTo(NULL);
				}
				QueryXmlObject(); 
			}
			_Catch()
		}

	public:
		inline XmlObjectInterface* GetXmlObjectInterface() 
		{
			QueryXmlObject(); 
			//
			if (m_XmlObject)
			{
				return m_XmlObject;
			}
			else
			{
				throw MethodError(L"m_XmlObject == NULL // " + _W(__FUNCTION__)); 
				////return NULL;
			}
		}
	};






	// ----
	// XmlElement

	class XmlElement : public XmlNodeObject<IXMLDOMElement>
	{
	public:
		XmlElement()
		{
		}

		XmlElement(const XmlElement& other) : XmlObject(other)
		{
		}

		XmlElement(const XmlNode& other) : XmlObject(other)
		{
		}

		XmlElement(IXMLDOMElement* other) : XmlObject(other)
		{
		}

		XmlElement(IXMLDOMNode* other) : XmlObject(other)
		{
		}

		const XmlElement& operator =(const XmlElement& other)
		{
			try
			{
				AssignTo(other);
				return other;
			}
			_Catch()
		}

		// ----
		// ������ � �������� XmlElement 

		XmlAttributeCollection Attributes()
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComPtr<IXMLDOMNamedNodeMap> m;
				HRESULT rc = m_p->get_attributes(&m);
				if (rc != S_OK)
				{
					string msg = L"�� ������� ��������� ������ ���������";
					if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(msg);
					else throw MethodError(msg);
				}
				return XmlAttributeCollection(m);
			}
			_Catch()
		}

		void SetAttribute(const string& attribute,const CComVariant& value) 
		{
#			ifdef _DEBUG
			string errorMsg = L"������ ��� ������ ��������: " + attribute;
#			else
			const string errorMsg = L"������ ��� ������ ��������";
#			endif
			//
			try
			{
				try
				{
					AssertObjectNotEmpty();
					//
					CComQIPtr<IXMLDOMElement> E(m_p);
					HRESULT rc = E->setAttribute(CComBSTR(attribute),value);
					if (rc != S_OK)
					{
						if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(errorMsg);
						else throw MethodError(errorMsg);
					}
				}
				_Catch()
			}
			_AddMessage(errorMsg)
		}

		inline void SetAttribute(const string& attribute,const string& value) 
		{
			try
			{
				SetAttribute(attribute,CComVariant(CComBSTR(value)));
			}
			_Catch()
		}

		bool HasAttribute(const string& attribute)
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComQIPtr<IXMLDOMElement> E(m_p);
				CComVariant v;
				HRESULT rc = E->getAttribute(CComBSTR(attribute),&v);
				return (rc == S_OK);
			}
			_Catch()
		}

		CComVariant GetAttributeAsVariant(const string& attribute)
		{
			string errorMsg = L"������ ���������� ��������: " + attribute;
			//
			try
			{
				try
				{
					AssertObjectNotEmpty();
					//
					CComQIPtr<IXMLDOMElement> E(m_p);
					CComVariant v;
					HRESULT rc = E->getAttribute(CComBSTR(attribute),&v);
					if (rc != S_OK)
					{
						if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(errorMsg);
						else throw MethodError(errorMsg);
					}
					return v;
				}
				_Catch()
			}
			_AddMessage(errorMsg)
		}

		string GetAttribute(const string& attribute)
		{
			try
			{
				return Convert_A::ToString(
					(const VARIANT&)
					GetAttributeAsVariant(attribute)
					);
			}
			_Catch()
		}
	};






	// ----
	// XmlText

	class XmlText : public XmlNodeObject<IXMLDOMText>
	{
	public:
		XmlText()
		{
		}

		XmlText(const XmlText& other) : XmlObject(other)
		{
		}

		XmlText(const XmlNode& other) : XmlObject(other)
		{
		}

		XmlText(IXMLDOMText* other) : XmlObject(other)
		{
		}

		XmlText(IXMLDOMNode* other) : XmlObject(other)
		{
		}

		const XmlText& operator =(const XmlText& other)
		{
			try
			{
				AssignTo(other);
			}
			_Catch()
		}
	};






	// ----
	// XmlDocument
	// XmlDocumentWrapper, XmlDocumentT
	// XmlDocCreatorT, XmlDocCreator, XmlDocCreatorWithSchema
	// MsManager

	class XmlDocumentWrapper : public XmlNodeObject<INTERFACE_IDOMDocument> 
	{
	public:
		typedef INTERFACE_IDOMDocument IDOMDocument;

	public:
		// ----
		// ������������ � �����������

		XmlDocumentWrapper()
		{
		}

		XmlDocumentWrapper(const XmlDocumentWrapper& other) : XmlObject(other)
		{
		}

		XmlDocumentWrapper(const XmlNode& other) : XmlObject(other)
		{
		}

		XmlDocumentWrapper(IXMLDOMNode* xmlDocNode) : XmlObject(xmlDocNode)
		{
		}

		XmlDocumentWrapper(INTERFACE_IDOMDocument* xmlDoc) 
		{
			try
			{
				if (xmlDoc)
				{
					CComQIPtr<IXMLDOMNode> q(xmlDoc);
					InitialAssignTo(q);
				}
				else
				{
					InitialAssignTo(NULL);
				}
			}
			_Catch()
		}

		//XmlDocumentWrapper(INTERFACE_IDOMDocument* xmlDoc) : XmlObject(xmlDoc)
		//{
		//}

	public:
		// ----
		// ������ � ��������

		void Save(const string& path)
		{
			string errorMsg = L"�� ������� ��������� XML-����, ���� ��� ������ : " + path;
			//
			try
			{
				try
				{
					AssertObjectNotEmpty();
					//
					HRESULT rc = m_XmlObject->save(CComVariant(CComBSTR(path)));
					if (rc != S_OK) 
					{
						if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(errorMsg);
						else throw MethodError(errorMsg);
					}
				}
				_Catch()
			}
			_AddMessage(errorMsg)
		}

		void SetSelectionNamespaces(const string& selNS)
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComQIPtr<IXMLDOMDocument2> d2(m_XmlObject); 
				if (! d2) throw MethodError(L"�� ������ �������� ��������� IXMLDOMDocument2"); 
				//
				HRESULT rc = d2->setProperty(L"SelectionNamespaces",CComVariant(
					CComBSTR(selNS.GetString())));
				if (FAILED(rc)) throw MethodError(rc);
			}
			_Catch()
		}

		XmlElement DocumentElement()
		{
			try
			{
				AssertObjectNotEmpty();
				//
				CComPtr<IXMLDOMElement> root;
				HRESULT rc = m_XmlObject->get_documentElement(&root);	
				if (FAILED(rc)) throw MethodError(rc);
				//
				return XmlElement(root);
			}
			_Catch()
		}

		//inline operator INTERFACE_IDOMDocument* ()
		//{
		//	INTERFACE_IDOMDocument* p(m_XmlObject);  
		//	return p; 
		//}

		// ----
		// �������� �����

		XmlElement CreateElement(
			const string& prefix,
			const string& localName,
			const string& namespaceURI)
		{
			string errorMsg = L"������� " + prefix + L":" + localName;
			//
			try
			{
				try
				{
					AssertObjectNotEmpty();
					//
					string tagName = localName;
					if (prefix.GetLength() > 0) tagName = prefix + L":" + tagName;
					//
					CComPtr<IXMLDOMNode> newNode;
					CComVariant t = NODE_ELEMENT;
					HRESULT rc = m_XmlObject->createNode(
						t,
						CComBSTR(tagName),
						CComBSTR(namespaceURI),
						&newNode);
					//
					if (rc != S_OK) throw MethodError(rc);
					//
					CComQIPtr<IXMLDOMElement> element(newNode);
					return XmlElement(element);
				}
				_Catch()
			}
			_AddMessage(errorMsg)
		}

		static const int CreateTextNode_ErrorMaxText = 64;

		XmlText CreateTextNode(const string& text)
		{
			return CreateTextNode(CComBSTR(text));
		}

		XmlText CreateTextNode(const CComBSTR& text)
		{
			string errorMsg(L"������ ��� �������� ���������� ���� (�����: ");
			if (text.Length() <= CreateTextNode_ErrorMaxText) errorMsg += string(text) + L")";
			else 
			{
				string t = FormatStr(L"... (������: %d)", (int)text.Length() );
				errorMsg += t;
					/// text.Left(CreateTextNode_ErrorMaxText-3) + 
			}
			//
			try
			{
				try
				{
					AssertObjectNotEmpty();
					//
					CComPtr<IXMLDOMText> textNode;
					HRESULT rc = m_XmlObject->createTextNode(text,&textNode);
					if (FAILED(rc)) throw MethodError(rc);
					//
					return XmlText(textNode);
				}
				_Catch()
			}
			_AddMessage(errorMsg)
		}



		// ----
		// ���������

		string GetSchemaUrl(string& targetNamespace,bool* found=0)
		{
			try
			{
				if (DocumentElement().HasAttribute(L"xsi:schemaLocation"))
				{
					string sL = DocumentElement().GetAttribute(L"xsi:schemaLocation");
					int p1 = sL.Find(L" ");
					if (p1 == -1) p1 = sL.Find(L"\n");
					string schemaUrl;
					if (p1 == -1) 
					{
						targetNamespace = L"";
						schemaUrl = sL;
					}
					else
					{
						targetNamespace = sL.Left(p1);
						schemaUrl = sL.Right(sL.GetLength()-p1-1);
					}
					schemaUrl.Trim();
					targetNamespace.Trim();
					//
					if (found) *found = true;
					return schemaUrl;
				}
				else
				{
					if (found) 
					{
						*found = false;
						return L"";
					}
					else throw MethodError(string(L"����������� ������� SchemaLocation"));
				}
			}
			_Catch()
		}

		//bool Validate(XmlDocument& schemaDoc,Exception** pExc)
		//{
		//	try
		//	{
		//		AssertObjectNotEmpty();
		//		//
		//		if (! pExc) throw MethodError(E_POINTER);
		//		//
		//		try
		//		{
		//			CComQIPtr<IXMLDOMDocument2> pXSchema(schemaDoc.GetXMLDOMDocument());
		//			//// TRACE_LOG(schemaDoc.DocumentElement().OuterXml());
		//			//
		//			CComQIPtr<IXMLDOMSchemaCollection> cSchemas;
		//			cSchemas.CoCreateInstance(L"Msxml2.XMLSchemaCache.6.0");
		//			//
		//			string targetNamespace = 
		//				schemaDoc.DocumentElement().GetAttribute(L"targetNamespace");
		//			//
		//			HRESULT hr = cSchemas->add(
		//				CComBSTR(targetNamespace),CComVariant((IXMLDOMDocument*)pXSchema)); 
		//			if (hr != S_OK) throw MethodError(hr);
		//			//
		//			return Validate(cSchemas,pExc);
		//		}
		//		catch(Exception& e1)
		//		{
		//			*pExc = new Exception(e1);
		//			return false;
		//		}
		//		catch(...)
		//		{
		//			*pExc = new MethodError(string(L"����������� ������"));
		//			return false;
		//		}
		//	}
		//	_Catch()
		//}

		//bool Validate(const string& schemaLocation,Exception** pExc)
		//{
		//	try
		//	{
		//		bool found;
		//		string targetNamespace;
		//		string schemaUrl = GetSchemaUrl(targetNamespace,&found);
		//		if (found)
		//		{
		//			return Validate(targetNamespace,schemaUrl,pExc);
		//		}
		//		else
		//		{
		//			throw MethodError(_T("������ ������� schemaLocation: ") + _S(schemaLocation));
		//		}
		//	}
		//	catch(Exception& e1)
		//	{
		//		*pExc = new Exception(e1);
		//		return false;
		//	}
		//	catch(...)
		//	{
		//		*pExc = new MethodError(string(L"����������� ������"));
		//		return false;
		//	}
		//}

		//bool Validate(const string& targetNamespace,const string& schemaUrl,
		//	Exception** pExc)
		//{
		//	AssertObjectNotEmpty();
		//	if (! pExc) throw MethodError(E_POINTER);
		//	//
		//	try
		//	{
		//		CComQIPtr<IXMLDOMSchemaCollection> cSchemas;
		//		cSchemas.CoCreateInstance(L"Msxml2.XMLSchemaCache.6.0");
		//		//
		//		HRESULT hr = cSchemas->add(
		//			CComBSTR(targetNamespace),CComVariant(CComBSTR(schemaUrl)));
		//		if (hr != S_OK) throw MethodError(hr);
		//		//
		//		return Validate(cSchemas,pExc);
		//	}
		//	catch(Exception& e1)
		//	{
		//		*pExc = new Exception(e1); 
		//		return false;
		//	}
		//	catch(...)
		//	{
		//		*pExc = new MethodError(string(L"����������� ������"));
		//		return false;
		//	}
		//}

		//bool Validate(IXMLDOMSchemaCollection* cSchemas,Exception** pExc)
		//{
		//	AssertObjectNotEmpty();
		//	if (! pExc) throw MethodError(E_POINTER);
		//	//
		//	try
		//	{
		//		CComQIPtr<IXMLDOMDocument2> pXDoc(GetXMLDOMDocument());
		//		//
		//		HRESULT hr = pXDoc->putref_schemas(CComVariant(cSchemas));
		//		if (hr != S_OK) throw MethodError(hr);
		//		//
		//		IXMLDOMParseError * pErrObj = NULL;
		//		hr = pXDoc->validate(&pErrObj);
		//		if (FAILED(hr)) throw MethodError(hr);
		//		if (hr == S_OK) 
		//		{
		//			*pExc = 0;
		//			return true;
		//		}
		//		//
		//		long errCode = 0;
		//		hr = pErrObj->get_errorCode(&errCode);
		//		if (FAILED(hr))
		//		{
		//			if (pErrObj) pErrObj->Release();
		//			throw MethodError(hr);
		//		}
		//		//
		//		CComBSTR bstrReason;
		//		hr = pErrObj->get_reason(&bstrReason);
		//		if (FAILED(hr))
		//		{
		//			if (pErrObj) pErrObj->Release();
		//			throw MethodError(hr);
		//		}
		//		//
		//		*pExc = new MethodError(_S(bstrReason));
		//		//
		//		return false;
		//	}
		//	catch(Exception& e1)
		//	{
		//		*pExc = new Exception(e1);
		//		return false;
		//	}
		//	catch(...)
		//	{
		//		*pExc = new MethodError(string(L"����������� ������"));
		//		return false;
		//	}
		//}
	};






	template<
		bool _Async,
		bool _PreserveWhiteSpace,
		bool _ValidateOnParse,
		bool _ProhibitDTD,
		bool _ResolveExternals
		/// , char* _ProgId
	>
	class XmlDocCreatorT
	{
		static CComBSTR sProgId()
		{
			static CComBSTR s_ProgId(MSXML2_FreeThreaded_DOMDOCUMENT_ProgId);
			return s_ProgId;
		}

	public:
		inline bool Async() { return _Async; }
		inline bool PreserveWhiteSpace() { return _PreserveWhiteSpace; }
		inline bool ValidateOnParse() { return _ValidateOnParse; }
		inline bool ProhibitDTD() { return _ProhibitDTD; }
		inline bool ResolveExternals() { return _ResolveExternals; }
		inline CComBSTR ProgId() { return sProgId(); }
	};

	typedef XmlDocCreatorT<false,false,false,true,true> XmlDocCreator;






	template<class _Creator,class _NsManager>
	class XmlDocumentT : public XmlDocumentWrapper
	{
	protected:
		typedef _Creator Creator;

		typedef _NsManager NsManager;

	protected:
		Exception ParseError()
		{
			Exception e = MethodError(L"�� ������� ��������� ��������");
			//
			try
			{
				const string noParseErrorMsg = L"������ ParseError �� �������";
				//
				CComPtr<IXMLDOMParseError> parseErrorObj;
				HRESULT rc = GetXmlObjectInterface()->get_parseError(&parseErrorObj);
				if (rc != S_OK)
				{
					if (FAILED(rc))
					{
						e.Join(MethodError(rc));
						return e;
					}
					else
					{
						return e.AddIfNewSource_(noParseErrorMsg);
					}
				}
				if (! parseErrorObj) return e.AddIfNewSource_(noParseErrorMsg);
				//
				long errorCode;
				rc = parseErrorObj->get_errorCode(&errorCode);
				if (FAILED(rc)) return e.Join(MethodError(rc));
				//
				long filepos;
				rc = parseErrorObj->get_filepos(&filepos);
				if (FAILED(rc)) return e.Join(MethodError(rc));
				//
				long line;
				rc = parseErrorObj->get_line(&line);
				if (FAILED(rc)) return e.Join(MethodError(rc));
				//
				long linepos;
				rc = parseErrorObj->get_linepos(&linepos);
				if (FAILED(rc)) return e.Join(MethodError(rc));
				//
				CComBSTR reason;
				rc = parseErrorObj->get_reason(&reason);
				if (FAILED(rc)) return e.Join(MethodError(rc));
				//
				CComBSTR srcText;
				rc = parseErrorObj->get_srcText(&srcText);
				if (FAILED(rc)) return e.Join(MethodError(rc));
				//
				CComBSTR url;
				rc = parseErrorObj->get_url(&url);
				if (FAILED(rc)) return e.Join(MethodError(rc));
				//
				// ----
				// ��������� �����:
				//
				string msg_1 = FormatStr(
					L"errorCode: 0x%x\n"
					L"filepos: %d\n"
					L"line: %d\n"
					L"linepos: %d\n"
					,(int)errorCode
					,(int)filepos
					,(int)line
					,(int)linepos
					);
				//
				string msg_2 = FormatStr(
					L"url: %s\n"
					L"%s\n"
					L"-\n"
					L"%s"
					,string(url).GetString()
					,string(reason).GetString()
					,string(srcText).GetString()
					);
				//
				string msg = msg_1 + msg_2;
				//
				return e.AddIfNewSource_(msg);
			}
			catch(...)
			{
				return e.AddIfNewSource_(L"�� ������� ������� ParseError (2)");
			}
		}

	protected:
		void Prepare()
		{
			try
			{
				try
				{
					// return; 
					//
					//
					Dispose();
					//
					// ----
					// ������������ ������ ��������� 
					//
					/*
					NsManager nsMgr;
					//
					string selNS = nsMgr.SelectionNamespaces();
					*/
					//
					Creator creator;
					HRESULT rc = m_XmlObject.CoCreateInstance(creator.ProgId());
					if (rc != S_OK) 
					{
						string msg = L"������ ��� �������� ������ " + string(creator.ProgId());
						if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(msg);
						else throw MethodError(msg);
					}
					//
					// ----
					// ����������� ��������� IXMLDOMNode 
					//
					m_p.Attach(
						CComQIPtr<IXMLDOMNode>(m_XmlObject).Detach()
						);
					//
					// ----
					// ����������� ��������� ��������� 
					//
					rc = m_XmlObject->put_async(creator.Async() ? 
						VARIANT_TRUE : VARIANT_FALSE);
					if (FAILED(rc)) throw MethodError(rc);
					//
					rc = m_XmlObject->put_preserveWhiteSpace(creator.PreserveWhiteSpace() ? 
						VARIANT_TRUE : VARIANT_FALSE);
					if (FAILED(rc)) throw MethodError(rc);
					//
					rc = m_XmlObject->put_validateOnParse(creator.ValidateOnParse() ? 
						VARIANT_TRUE : VARIANT_FALSE);
					if (FAILED(rc)) throw MethodError(rc);
					//
					rc = m_XmlObject->put_resolveExternals(creator.ResolveExternals() ? 
						VARIANT_TRUE : VARIANT_FALSE);
					if (FAILED(rc)) throw MethodError(rc);
					//
					CComQIPtr<IXMLDOMDocument2> d2(m_XmlObject); 
					if (! d2) throw MethodError(L"�� ������ �������� ��������� IXMLDOMDocument2"); 
					//
					rc = d2->setProperty(CComBSTR(L"ProhibitDTD"),
						CComVariant(creator.ProhibitDTD() ? TRUE : FALSE)
						);
					if (FAILED(rc)) throw MethodError(rc);
					//
					//rc = d2->setProperty(CComBSTR(L"SelectionNamespaces"),
					//	CComVariant(CComBSTR(selNS.GetString()))
					//	);
					//if (FAILED(rc)) throw MethodError(rc);
				}
				_Catch()
			}
			catch(...)
			{
				Dispose();
				//
				throw;
			}
		}

	public:
		XmlDocumentT()
		{
		}

		// ----
		// ����������� ������������

		XmlDocumentT(INTERFACE_IDOMDocument* document) : XmlDocumentWrapper(document) 
		{
		}

		XmlDocumentT(const XmlDocumentWrapper& other) : XmlDocumentWrapper(other) 
		{
		}

		// ----
		// ����������� ������������

		XmlDocumentT(const XmlDocumentT& other) : XmlDocumentWrapper(other) 
		{
		}

	public:
		string Descriptor;

		inline string Description()
		{
			return L"�������� XML: " + Descriptor;
		}

		// ----
		// �������� / ��������

		void Load(const string& path)
		{
			try
			{
				try
				{
					Descriptor = path;
					//
					Prepare();
					//
					VARIANT_BOOL isSuccessful;
					HRESULT rc = GetXmlObjectInterface()->load(CComVariant(CComBSTR(path)),&isSuccessful);
					if (rc != S_OK || (! isSuccessful)) 
					{
						throw ParseError();
					}
				}
				_Catch()
			}
			_AddMessage(Description())
		}

		void LoadStream(IStream* stream)
		{
			try
			{
				try
				{
					Descriptor = FormatStr(L"Stream at 0x%x", (int)(__int64)stream ); 
					//
					if (! stream) throw MethodError(E_POINTER); 
					//
					Prepare();
					//
					VARIANT_BOOL isSuccessful;
					HRESULT rc = GetXmlObjectInterface()->load(CComVariant(stream),&isSuccessful);
					if (rc != S_OK || (! isSuccessful)) 
					{
						throw ParseError();
					}
				}
				_Catch()
			}
			_AddMessage(Description())
		}

		void LoadXml(const string& data)
		{
			CComBSTR bstrData(data);
			LoadXml(bstrData);
		}

		void LoadXml(CComBSTR& data)
		{
			try
			{
				try
				{
					Prepare();
					//
					VARIANT_BOOL isSuccessful;
					HRESULT rc = m_XmlObject->loadXML(data,&isSuccessful);
					if (rc != S_OK || (! isSuccessful)) 
					{
						throw MethodError(L"�� ������� ��������� ��������");
					}
				}
				_Catch()
			}
			_AddMessage(Description())
		}
	};



	class NsManager
	{
	public:
		string SelectionNamespaces()
		{
			return 
				L"xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' "
				L"xmlns:xsl='http://www.w3.org/1999/XSL/Transform' "
				L"xmlns:sql='urn:schemas-microsoft-com:mapping-schema' "
				L"xmlns:ds='http://www.w3.org/2000/09/xmldsig#' "
				L"xmlns:dsig='http://www.w3.org/2000/09/xmldsig#' "
				L"xmlns:dse='http://cabinet.example.com/schema/xmldsigext-/rel-1/' "
				L"xmlns:protocol='http://cabinet.example.com/schema/-protocol/rel-1/' "
				L"xmlns:slot='urn::slot' "
				L"xmlns:asn='urn::asn' "
				L"xmlns:sm='urn::sysmsg' "
				L"xmlns:slotrequest='urn::slot-request' "
				L"xmlns:ufml='http://cabinet.example.com/schema/ufml3/rel-1/' "
				//
#				ifdef _PUBLIC_CABINET_REQUEST_NSURI
				L"xmlns:cabrequest='" + _W(_PUBLIC_CABINET_REQUEST_NSURI) + L"'"
#				endif
				;
		}
	};



	// ----
	// �����������: XmlDocument, XmlDocumentWithSchema

	typedef XmlDocumentT<XmlDocCreator,NsManager> XmlDocument;

	/// typedef XmlDocumentT<XmlDocCreatorWithSchema,NsManager> XmlDocumentWithSchema;



	// ----
	// ���������� �� ������ / ���������� ���������� 

	inline static XmlDocument GetExceptionXml(Exception e)
	{
		throw MethodError(E_NOTIMPL); 
	}

	inline static XmlDocument GetStatusXml(int statusCode)
	{
		const string SysMsgNsUri = L"urn::sysmsg"; 
		//
		string statusCodeStr = FormatStr(L"%d", (int)statusCode ); 
		//
		XmlDocument statusDoc;
		statusDoc.LoadXml(_W(COMMON_XML_START) + 
			L"<sm:msg xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:sm=\"" 
			+ SysMsgNsUri + L"\" num=\""+ statusCodeStr
			+ L"\" xsi:type=\"error\"></sm:msg>"
			);
		//
		return statusDoc;
	}

} // namespace  









inline ::XmlDocumentWrapper 
::XmlNode::OwnerDocument()
{
	try
	{
		CComPtr<IXMLDOMDocument> doc;
		m_p->get_ownerDocument(&doc);
		CComQIPtr<INTERFACE_IDOMDocument> doc2(doc);
		return XmlDocument(doc);
	}
	_Catch()
}

inline ::XmlDocumentWrapper 
::XmlNode::TransformToXml(XmlNode xsl)
{
	try
	{
		CComBSTR result_s;
		HRESULT rc = m_p->transformNode(xsl.m_p,&result_s);
		if (rc != S_OK) throw MethodError(rc);
		XmlDocument result;
		result.LoadXml(result_s);
		return result;
	}
	_Catch()
}

inline ::XmlNodeList 
::XmlNode::SelectNodes(const string& search)
{
	string errorMsg = L"������ ��� ������������ ������ �����: " + search;
	//
	try
	{
		try
		{
			AssertObjectNotEmpty();
			//
			CComPtr<IXMLDOMNodeList> L;
			HRESULT rc = m_p->selectNodes(CComBSTR(search),&L);
			if (rc != S_OK) 
			{
				if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(errorMsg);
				else throw MethodError(errorMsg);
			}
			return XmlNodeList(L);
		}
		_Catch()
	}
	_AddMessage(errorMsg)
}
























// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// SAX

namespace 
{
	// ===============================
	// Handlers 
	// ===============================

	template<class _Handler>
	class SaxMultiHandler : public ISAXContentHandler 
	{
	public:
		typedef _Handler HandlerType;

		HandlerType Handler;

		SaxMultiHandler() 
		{
		}

		virtual ~SaxMultiHandler() 
		{
		}

		STDMETHOD(QueryInterface)(const struct _GUID &riid, void ** ppObj)
		{ 
			if (riid == IID_IUnknown)
			{
				*ppObj = static_cast<IUnknown*>(this);
			}
			if (riid == __uuidof(ISAXContentHandler))
			{
				*ppObj = static_cast<ISAXContentHandler*>(this);
			}
			else
			{
				*ppObj = NULL ;
				return E_NOINTERFACE ;
			}

			AddRef() ;
			return S_OK;
		}

		ULONG STDMETHODCALLTYPE AddRef(void)
		{ 
			return 0; 
		}

		ULONG STDMETHODCALLTYPE Release(void)
		{ 
			return 0; 
		}

		virtual HRESULT STDMETHODCALLTYPE putDocumentLocator(
			ISAXLocator __RPC_FAR *pLocator)
		{
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE startDocument()
		{
			return S_OK;
		}
        
		virtual HRESULT STDMETHODCALLTYPE endDocument()
		{
			return S_OK;
		}
        
		virtual HRESULT STDMETHODCALLTYPE startPrefixMapping( 
			const wchar_t __RPC_FAR *pwchPrefix,
			int cchPrefix,
			const wchar_t __RPC_FAR *pwchUri,
			int cchUri)
		{
			return S_OK;
		}
        
		virtual HRESULT STDMETHODCALLTYPE endPrefixMapping( 
			const wchar_t __RPC_FAR *pwchPrefix,
			int cchPrefix)
		{
			return S_OK;
		}
        
		virtual HRESULT STDMETHODCALLTYPE startElement( 
			const wchar_t __RPC_FAR *pwchNamespaceUri,
			int cchNamespaceUri,
			const wchar_t __RPC_FAR *pwchLocalName,
			int cchLocalName,
			const wchar_t __RPC_FAR *pwchRawName,
			int cchRawName,
			ISAXAttributes __RPC_FAR *pAttributes)
		{
			return Handler.StartElement(
				string(pwchNamespaceUri,cchNamespaceUri),
				string(pwchLocalName,cchLocalName),
				string(pwchRawName,cchRawName),
				pAttributes);
		}
        
		virtual HRESULT STDMETHODCALLTYPE endElement( 
			const wchar_t __RPC_FAR *pwchNamespaceUri,
			int cchNamespaceUri,
			const wchar_t __RPC_FAR *pwchLocalName,
			int cchLocalName,
			const wchar_t __RPC_FAR *pwchRawName,
			int cchRawName)
		{
			return Handler.EndElement(
				string(pwchNamespaceUri,cchNamespaceUri),
				string(pwchLocalName,cchLocalName),
				string(pwchRawName,cchRawName)
				);
		}
        
		virtual HRESULT STDMETHODCALLTYPE characters( 
			const wchar_t __RPC_FAR *pwchChars,
			int cchChars)
		{
			return Handler.Characters(string(pwchChars,cchChars));
		}
        
		virtual HRESULT STDMETHODCALLTYPE ignorableWhitespace( 
			const wchar_t __RPC_FAR *pwchChars,
			int cchChars)
		{
			return S_OK;
		}
        
		virtual HRESULT STDMETHODCALLTYPE processingInstruction( 
			const wchar_t __RPC_FAR *pwchTarget,
			int cchTarget,
			const wchar_t __RPC_FAR *pwchData,
			int cchData)
		{
			return S_OK;
		}
        
		virtual HRESULT STDMETHODCALLTYPE skippedEntity( 
			const wchar_t __RPC_FAR *pwchName,
			int cchName)
		{
			return S_OK;
		}
	};



	// ===============================
	// Reader Creators 
	// ===============================

	class SaxReaderCreatorT
	{
		static CComBSTR sProgId()
		{
			static CComBSTR s_ProgId(MSXML2_SAXREADER_ProgId);
			return s_ProgId;
		}

	public:
		inline CComBSTR ProgId() { return sProgId(); }

		ISAXXMLReader* QueryISAXXMLReader()
		{
			try
			{
				CComPtr<ISAXXMLReader> p;
				HRESULT rc = p.CoCreateInstance(ProgId());
				if (rc != S_OK) 
				{
					string msg = L"������ ��� �������� ������ " + string(ProgId());
					if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(msg);
					else throw MethodError(msg);
				}
				return p.Detach();
			}
			_Catch()
		}
	};



	class SaxPassiveReaderCreatorT
	{
		static CComBSTR sProgId()
		{
			static CComBSTR s_ProgId(_SAXPASSIVEREADER_ProgId);
			return s_ProgId;
		}

	public:
		inline CComBSTR ProgId() { return sProgId(); }

		ISAXXMLReader* QueryISAXXMLReader()
		{
			try
			{
				CComPtr<ISAXXMLReader> p;
				HRESULT rc = p.CoCreateInstance(ProgId());
				if (rc != S_OK) 
				{
					string msg = L"������ ��� �������� ������ " + string(ProgId());
					if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(msg);
					else throw MethodError(msg);
				}
				return p.Detach();
			}
			_Catch()
		}
	};



	// ============================================
	// SaxReaderT --- ������ ��� ISAXXMLReader
	// ============================================

	template<class _Creator>
	class SaxReaderT : public ComWrapper<ISAXXMLReader>
	{
	protected:
		typedef _Creator Creator;

		void Prepare()
		{
			try
			{
				try
				{
					Dispose();
					//
					// ----
					// ������������ ������ ��������� 
					//
					Creator creator;
					//
					m_p.Attach(creator.QueryISAXXMLReader());
					//
					// ----
					// ����������� ��������� reader'� 
					//
					// ...
				}
				_Catch()
			}
			catch(...)
			{
				Dispose();
				//
				throw;
			}
		}

	public:
		SaxReaderT()
		{
			Prepare();
		}

		void SetMultiHandlerRef(ISAXContentHandler* p) // borrowed reference 
		{
			try
			{
					AssertObjectNotEmpty();
					//
					HRESULT rc = m_p->putContentHandler(p);
					if (FAILED(rc)) throw MethodError(rc);
			}
			_Catch()
		}

		void Parse(IStream* stream)
		{
			string errorMsg = FormatStr(L"������ ������� ������ (����� 0x%x)", (int)stream ); 
			//
			try
			{
				try
				{
					AssertObjectNotEmpty();
					//
					HRESULT rc = m_p->parse(stream);
					if (rc != S_OK) 
					{
						if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(errorMsg);
						else throw MethodError(errorMsg);
					}
				}
				_Catch()
			}
			_AddMessage(errorMsg)
		}

		void ParseUrl(const string& url)
		{
			string errorMsg = L"������ ������� �����: " + url;
			//
			try
			{
				try
				{
					AssertObjectNotEmpty();
					//
					HRESULT rc = m_p->parseURL(url);
					if (rc != S_OK) 
					{
						if (FAILED(rc)) throw MethodError(rc).AddIfNewSource_(errorMsg);
						else throw MethodError(errorMsg);
					}
				}
				_Catch()
			}
			_AddMessage(errorMsg)
		}

		ISAXXMLReader* GetSAXXMLReader() // borrowed 
		{
			try
			{
				if (! m_p) throw MethodError(E_POINTER);
				//
				return (ISAXXMLReader*)m_p;
			}
			_Catch()
		}
	};

	typedef SaxReaderT<SaxReaderCreatorT> SaxReader;

	typedef SaxReaderT<SaxPassiveReaderCreatorT> SaxPassiveReader;






	class IDocumentReader
	{
	public:
		/// ...
	};

} // namespace 






