/*
 SmartMap.h : �������.

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/10/10 15:12:24 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// ATL
//
#include <atlcoll.h>

// 
//
#include "SmartHashValue.h"
#include "SmartPtr.h"

namespace  { 



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� DictionaryObject

/*
class DictionaryObject : public Object
{
public:
	inline virtual TypeId GetTypeId() const
	{
		return Type_Dictionary;
	}

	virtual ~DictionaryObject() 
	{
	}

	inline virtual bool SameAs(const Object& //rhs
		,TypeId rhsTypeId) const 
	{
		if (rhsTypeId != this->GetTypeId()) return false;
		return false;
	}

public:
	class DictItem;

	inline DictItem operator [](Any key)
	{
		return DictItem(*this,key);
	}

	class ConstDictItem;

	inline ConstDictItem operator [](Any key) const 
	{
		return ConstDictItem(*this,key);
	}

	virtual Any FindItem(const Any& key,bool* out_found,bool returnValue=true) =0; 

	virtual Any FindConstItem(const Any& key,bool* out_found,bool returnValue=true) const =0; 

	virtual Any GetItem(const Any& key) =0;

	virtual Any GetConstItem(const Any& key) const =0;

	virtual void SetItem(const Any& key,Any& v) =0;

	// virtual void SetConstItem(const Any& key,const Any& v) =0;

	virtual void Remove(const Any& key) =0;

	virtual void RemoveAll() =0;

	virtual int GetSize() const =0;

	//inline bool IsEmpty() const
	//{
	//	return GetSize() == 0;
	//}

	// ������������

	virtual bool GetFirst(Any& out_key,int& out_index) =0;

	virtual bool GetNext(Any& out_key,int& index) =0;

	virtual bool GetFirst(Any& out_key,Any& out_value,int& out_index) =0;

	virtual bool GetNext(Any& out_key,Any& out_value,int& index) =0;

	virtual bool GetConstFirst(Any& out_key,int& out_index) const =0;

	virtual bool GetConstNext(Any& out_key,int& index) const =0;

	virtual bool GetConstFirst(Any& out_key,Any& out_value,int& out_index) const =0;

	virtual bool GetConstNext(Any& out_key,Any& out_value,int& index) const =0;

public:
	// ===========================================================================================
	// ���������� ������ 
	// ----------------------

	// ������ � �������� �������

	class DictItem
	{
		friend DictionaryObject;

		mutable DictionaryObject& m_parent;

		Any m_key;

		inline DictItem(DictionaryObject& parent,const Any& key) : m_parent(parent), m_key(key)
		{
		}

	public:
		inline operator Any() 
		{
			return m_parent.GetItem(m_key);
		}

		//inline void operator =(Any& v)
		//{
		//	m_parent.SetItem(m_key,v);
		//}

		//inline void operator =(const Any& v) const 
		//{
		//	m_parent.SetConstItem(m_key,v);
		//}
	};

	class ConstDictItem
	{
		friend DictionaryObject;

		const DictionaryObject& m_parent;

		Any m_key;

		inline ConstDictItem(const DictionaryObject& parent,const Any& key) : m_parent(parent), m_key(key)
		{
		}

	public:
		inline operator Any() const 
		{
			return m_parent.GetConstItem(m_key);
		}
	};



	// ��������
	class Iterator
	{
		DictionaryObject& m_dict;

		int m_index;

		bool m_found;

		Any m_key;

		Any m_value;

	public:
		Iterator(DictionaryObject& dict) : m_dict(dict)
		{
			m_found = m_dict.GetFirst(m_key,m_value,m_index);
		}

		inline Iterator& operator ++()
		{
			m_found = m_dict.GetNext(m_key,m_value,m_index);
			return *this;
		}

		inline Any Id() const 
		{
			if (! m_found) throw LowLevelError(SLOT_NOT_FOUND);
			return m_key;
		}

		inline operator Any() 
		{
			if (! m_found) throw LowLevelError(SLOT_NOT_FOUND);
			return m_value;
		}
	};
};
*/






// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// ����� Map

// ��������� ���������� �������

template<class _Id,class _Value>
class Map ////: public DictionaryObject 
{
protected:
	// ===========================================================================================
	// ������ 
	// ----------------------

	typedef _Value* Pointer;

	typedef CAtlMap<ULONG,Pointer> MapType;

	mutable SharedPtr<MapType> m_data;

public:
	// ===========================================================================================
	// ��������� DictionaryObject 
	// ----------------------

	/*
	virtual Any FindItem(const Any& key,bool* out_found,bool returnValue=true) 
	{
		if (returnValue)
		{
			_Value* v;
			FindItem(_Id(key),out_found,&v);
			if (out_found) return Any(*v);
			else return Any();
		}
		else
		{
			FindItem(_Id(key),out_found);
			return Any();
		}
	}
	
	virtual Any FindConstItem(const Any& key,bool* out_found,bool returnValue=true) const 
	{
		if (returnValue)
		{
			_Value v;
			FindConstItem(_Id(key),out_found,&v);
			return v;
		}
		else
		{
			FindConstItem(_Id(key),out_found);
			return Any();
		}
	}

	Any GetItem(const Any& key) 
	{
		return GetItem(_Id(key));
	}

	Any GetConstItem(const Any& key) const 
	{
		return GetConstItem(_Id(key));
	}

	void SetItem(const Any& key,Any& v) 
	{
		SetItemValue(_Id(key),(_Value&)v);
	}

	//void SetConstItem(const Any& key,const Any& v) 
	//{
	//	SetConstItemValue(_Id(key),v);
	//}
	//*/

	//void Remove(const Any& key) 
	//{
	//	Remove(_Id(key));
	//}

	void RemoveAll() 
	{
		POSITION pos = m_data->GetStartPosition();
		if (pos != 0)
		{
			ULONG hc;
			Pointer v;
			for (; 
				 pos != 0; 
				 m_data->GetNextAssoc(pos,hc,v))
			{
				m_data->GetAt(pos,hc,v);
				if (v) delete v;
			}
		}
		m_data->RemoveAll();
	}

	int GetSize() const 
	{
		/* const MapType* pMap = (const MapType*)m_data; return pMap->GetCount(); */
		return (int)m_data->GetCount();
	}

	inline bool IsEmpty() const
	{
		return GetSize() == 0;
	}



	// �����������

	Map(const Map& other) : m_data(new MapType())
	{		
		for (Map::ConstIterator i(other); i; ++i)
		{
			(*this)[i.Id()] = other[i.Id()];
		}
	}

	const Map& operator =(const Map& other)
	{		
		for (Map::ConstIterator i(other); i; ++i)
		{
			(*this)[i.Id()] = other[i.Id()];
		}
		//
		return other;
	}



	// ������������

	//bool GetFirst(Any& out_key,int& out_index) 
	//{
	//	_Id key;
	//	bool found = GetFirst(key,out_index);
	//	if (found) out_key = key;
	//	return found;
	//}

	bool GetFirst(_Id& out_key,int& out_index) 
	{
		POSITION pos = m_data->GetStartPosition();
		out_index = (int)(__int64)pos;
		if (! pos)
		{
			return false;
		}
		else
		{
			ULONG hc;
			Pointer v;
			m_data->GetAt(pos,hc,v);
			out_key = IdMap::GetId(hc);
			return true;
		}
	}

	//bool GetFirst(Any& out_key,Any& out_value,int& out_index) 
	//{
	//	_Id key;
	//	_Value* v;
	//	bool found = GetFirst(key,&v,out_index);
	//	if (found)
	//	{
	//		out_key = key;
	//		if (v) out_value = *v;
	//		else out_value = Any();
	//	}
	//	return found;
	//}

	bool GetFirst(_Id& out_key,_Value** out_value,int& out_index) 
	{
		if (! out_value) throw LowLevelError(E_POINTER);
		//
		POSITION pos = m_data->GetStartPosition();
		out_index = (int)(__int64)pos;
		if (! pos)
		{
			return false;
		}
		else
		{
			ULONG hc;
			Pointer v;
			m_data->GetAt(pos,hc,v);
			out_key = IdMap::GetId(hc);
			*out_value = v;
			return true;
		}
	}

	//bool GetNext(Any& out_key,int& index) 
	//{
	//	_Id key;
	//	bool found = GetNext(key,index);
	//	if (found) out_key = key;
	//	return found;
	//}

	bool GetNext(_Id& out_key,int& index) 
	{
		ULONG hc;
		Pointer v;
		POSITION pos = (POSITION)(__int64)index;
		m_data->GetNextAssoc(pos,hc,v);
		if (! pos) 
		{
			return false;
		}
		else
		{
			ULONG hc;
			Pointer v;
			m_data->GetAt(pos,hc,v);
			out_key = IdMap::GetId(hc);
			index = (int)(__int64)pos;
			return true;
		}
	}

	//bool GetNext(Any& out_key,Any& out_value,int& index) 
	//{
	//	_Id key;
	//	_Value* v;
	//	bool found = GetNext(key,&v,index);
	//	if (found)
	//	{
	//		out_key = key;
	//		if (v) out_value = *v;
	//		else out_value = Any();
	//	}
	//	return found;
	//}

	bool GetNext(_Id& out_key,_Value** out_value,int& index) 
	{
		if (! out_value) throw LowLevelError(E_POINTER);
		//
		ULONG hc;
		Pointer v;
		POSITION pos = (POSITION)(__int64)index;
		m_data->GetNextAssoc(pos,hc,v);
		if (! pos) 
		{
			return false;
		}
		else
		{
			ULONG hc;
			Pointer v;
			m_data->GetAt(pos,hc,v);
			out_key = IdMap::GetId(hc);
			index = (int)(__int64)pos;
			*out_value = v;
			return true;
		}
	}

	// ������������ (const)

	//bool GetConstFirst(Any& out_key,int& out_index) const 
	//{
	//	_Id key;
	//	bool found = GetConstFirst(key,out_index);
	//	if (found) out_key = key;
	//	return found;
	//}

	bool GetConstFirst(_Id& out_key,int& out_index) const 
	{
		POSITION pos = m_data->GetStartPosition();
		out_index = (int)(__int64)pos;
		if (! pos)
		{
			return false;
		}
		else
		{
			ULONG hc;
			Pointer v;
			m_data->GetAt(pos,hc,v);
			out_key = IdMap::GetId(hc);
			return true;
		}
	}

	//bool GetConstFirst(Any& out_key,Any& out_value,int& out_index) const 
	//{
	//	_Id key;
	//	_Value* v;
	//	bool found = GetConstFirst(key,&v,out_index);
	//	if (found)
	//	{
	//		out_key = key;
	//		if (v) out_value = *v;
	//		else out_value = Any();
	//	}
	//	return found;
	//}

	bool GetConstFirst(_Id& out_key,_Value** out_value,int& out_index) const 
	{
		if (! out_value) throw LowLevelError(E_POINTER);
		//
		POSITION pos = m_data->GetStartPosition();
		out_index = (int)(__int64)pos;
		if (! pos)
		{
			return false;
		}
		else
		{
			ULONG hc;
			Pointer v;
			m_data->GetAt(pos,hc,v);
			out_key = IdMap::GetId(hc);
			*out_value = v;
			return true;
		}
	}

	//bool GetConstNext(Any& out_key,int& index) const 
	//{
	//	_Id key;
	//	bool found = GetConstNext(key,index);
	//	if (found) out_key = key;
	//	return found;
	//}

	bool GetConstNext(_Id& out_key,int& index) const 
	{
		ULONG hc;
		Pointer v;
		POSITION pos = (POSITION)(__int64)index;
		m_data->GetNextAssoc(pos,hc,v);
		if (! pos) 
		{
			return false;
		}
		else
		{
			ULONG hc;
			Pointer v;
			m_data->GetAt(pos,hc,v);
			out_key = IdMap::GetId(hc);
			index = (int)(__int64)pos;
			return true;
		}
	}

	//bool GetConstNext(Any& out_key,Any& out_value,int& index) const 
	//{
	//	_Id key;
	//	_Value* v;
	//	bool found = GetConstNext(key,&v,index);
	//	if (found)
	//	{
	//		out_key = key;
	//		if (v) out_value = *v;
	//		else out_value = Any();
	//	}
	//	return found;
	//}

	bool GetConstNext(_Id& out_key,_Value** out_value,int& index) const 
	{
		if (! out_value) throw LowLevelError(E_POINTER);
		//
		ULONG hc;
		Pointer v;
		POSITION pos = (POSITION)(__int64)index;
		m_data->GetNextAssoc(pos,hc,v);
		if (! pos) 
		{
			return false;
		}
		else
		{
			ULONG hc;
			Pointer v;
			m_data->GetAt(pos,hc,v);
			out_key = IdMap::GetId(hc);
			index = (int)(__int64)pos;
			*out_value = v;
			return true;
		}
	}



	// ===========================================================================================
	// ����������� ������ ������� 
	// ----------------------

	class Item;

	Item operator [](const _Id& key)
	{
		return Item(*this,key);
	}

	class ConstItem;

	ConstItem operator [](const _Id& key) const
	{
		return ConstItem(*this,key);
	}

	Item operator [](const TCHAR* key)
	{
		return Item(*this,key);
	}

	ConstItem operator [](const TCHAR* key) const
	{
		return ConstItem(*this,key);
	}

	void FindItem(const _Id& key,bool* out_found,_Value** out_value=0) 
	{
		if (! out_found) throw LowLevelError(E_POINTER);
		//
		ULONG hc = HashValue(key);
		Pointer v;
		if (m_data->Lookup(hc,v))
		{ 
			*out_found = true;
			if (out_value)
			{
				if (v) 
				{
					*out_value = v;
				}
				else
				{
					*out_found = false;
				}
			}
			else return;
		}
		else
		{
			*out_found = false;
		}
	}

	void FindConstItem(const _Id& key,bool* out_found,_Value* out_value=0) const 
	{
		if (! out_found) throw LowLevelError(E_POINTER);
		//
		ULONG hc = HashValue(key);
		Pointer v;
		if (m_data->Lookup(hc,v))
		{ 
			*out_found = true;
			if (out_value)
			{
				if (v) 
				{
					*out_value = *v;
				}
				else
				{
					*out_found = false;
				}
			}
			else return;
		}
		else
		{
			*out_found = false;
		}
	}

	bool HasItem(const _Id& key) const 
	{
		bool found;
		FindConstItem(key,&found);
		return found;
	}

	bool ContainsKey(const _Id& key) const 
	{
		return HasItem(key);
	}

	bool ContainsValue(const _Value& value) const 
	{
		for (Map<_Id,_Value>::ConstIterator i(*this); i; ++i)
		{
			if ( ((const _Value&)i) == value) return true;
		}
		return false;
	}

	_Value& GetItem(const _Id& key) 
	{
		bool found;
		_Value* v; 
		FindItem(key,&found,&v);
		if (found) return *v;
		else throw LowLevelError(ERROR_NOT_FOUND);
	}

	_Value GetConstItem(const _Id& key) const 
	{
		// TRACE_LOG("Here! -------------------------------------------------------");
		bool found;
		_Value v;
		FindConstItem(key,&found,&v);
		if (found) return _Value(v);
		else throw LowLevelError(ERROR_NOT_FOUND);
	}

	void SetItemValue(const _Id& key,_Value& value) 
	{
		ULONG hc = HashValue(key);
		Pointer v;
		if (m_data->Lookup(hc,v))
		{
			if (v) delete v;
			v = new _Value(value);
		}
		else
		{
			IdMap::PushId(key,hc);
			v = new _Value(value);
		}
		m_data->operator [](hc) = v;
	}

	void SetConstItemValue(const _Id& key,const _Value& value) const 
	{
		ULONG hc = HashValue(key);
		Pointer v;
		if (m_data->Lookup(hc,v))
		{
			if (v) delete v;
			v = new _Value(value);
		}
		else
		{
			IdMap::PushId(key);
			v = new _Value(value);
		}
		m_data->operator [](hc) = v;
	}

	void Remove(const TCHAR* key)
	{
		Remove(_Id(key));
	}

	void Remove(const _Id& key)
	{
		ULONG hc = HashValue(key);
		Pointer v;
		if (m_data->Lookup(hc,v))
		{
			if (v) delete v;
			m_data->RemoveKey(hc);
			IdMap::PopId(key);
		}
	}

public:
	Map() : m_data(new MapType())
	{
	}

	virtual ~Map()
	{
		RemoveAll();
	}



public:
	// ===========================================================================================
	// ���������� ������ 
	// ----------------------

	// ������ � �������� �������

	class Item
	{
		friend Map;

		//mutable 
			Map& m_parent;

		_Id m_key;

		inline Item(Map& parent,const _Id& key) : m_parent(parent), m_key(key)
		{
		}

	public:
		inline operator _Value() 
		{
			return m_parent.GetItem(m_key);
		}

		inline void operator =(_Value& v)
		{
			m_parent.SetItemValue(m_key,v);
		}

		inline void operator =(const _Value& v) const 
		{
			m_parent.SetConstItemValue(m_key,v);
		}
	};

	class ConstItem
	{
		friend Map;

		const Map& m_parent;

		_Id m_key;

		inline ConstItem(const Map& parent,const _Id& key) : m_parent(parent), m_key(key)
		{
		}

	public:
		inline operator _Value() const 
		{
			return m_parent.GetConstItem(m_key);
		}
	};



	// ��������
	class Iterator
	{
		Map& m_dict;

		int m_index;

		bool m_found;

		_Id m_key;

		_Value* m_value;

	public:
		Iterator(Map& dict) : m_dict(dict)
		{
			m_found = m_dict.GetFirst(m_key,&m_value,m_index);
		}


		inline Iterator& operator ++()
		{
			m_found = m_dict.GetNext(m_key,&m_value,m_index);
			return *this;
		}

		inline operator bool() const 
		{
			return m_found;
		}

		inline bool operator !() const 
		{
			return ! operator bool();
		}

		inline _Id Id() const 
		{
			if (! m_found) throw LowLevelError(TYPE_E_OUTOFBOUNDS);
			return m_key;
		}

		inline operator _Value&() 
		{
			if (! m_found) throw LowLevelError(TYPE_E_OUTOFBOUNDS);
			if (! m_value) throw LowLevelError(E_POINTER);
			return *m_value;
		}

		inline operator const _Value&() const 
		{
			if (! m_found) throw LowLevelError(TYPE_E_OUTOFBOUNDS);
			if (! m_value) throw LowLevelError(E_POINTER);
			return *m_value;
		}

		//inline operator Any() 
		//{
		//	return Any(operator const _Value&());
		//}
	};

	class ConstIterator
	{
		const Map& m_dict;

		int m_index;

		bool m_found;

		_Id m_key;

		_Value* m_value;

	public:
		ConstIterator(const Map& dict) : m_dict(dict)
		{
			m_found = m_dict.GetConstFirst(m_key,&m_value,m_index);
		}


		inline ConstIterator& operator ++()
		{
			m_found = m_dict.GetConstNext(m_key,&m_value,m_index);
			return *this;
		}

		inline operator bool() const 
		{
			return m_found;
		}

		inline bool operator !() const 
		{
			return ! operator bool();
		}

		inline _Id Id() const 
		{
			if (! m_found) throw LowLevelError(TYPE_E_OUTOFBOUNDS);
			return m_key;
		}

		inline operator _Value&() 
		{
			if (! m_found) throw LowLevelError(TYPE_E_OUTOFBOUNDS);
			if (! m_value) throw LowLevelError(E_POINTER);
			return *m_value;
		}

		inline operator const _Value&() const 
		{
			if (! m_found) throw LowLevelError(TYPE_E_OUTOFBOUNDS);
			if (! m_value) throw LowLevelError(E_POINTER);
			return *m_value;
		}

		//inline operator Any() 
		//{
		//	return Any(operator const _Value&());
		//}
	};



protected:
	// ===========================================================================================
	// ������� ��������������� 
	// ----------------------

	class IdMap
	{
	public:
		typedef CAtlMap<ULONG,_Id*> IdMapType;

		mutable SharedPtr<IdMapType> m_idMap;

		typedef CAtlMap<ULONG,ULONG> IdCountMapType;

		SharedPtr<IdCountMapType> m_idCountMap;

		IdMap()
		{
			m_idMap = new IdMapType;
			m_idCountMap = new IdCountMapType;
		}

		static IdMap& Acquire()
		{
			static IdMap s_idMap;
			return s_idMap;
		}

	public:
		~IdMap()
		{
			POSITION pos = m_idMap->GetStartPosition();
			if (pos != 0)
			{
				ULONG hc;
				_Id* v;
				for (; 
					pos != 0; 
					m_idMap->GetNextAssoc(pos,hc,v))
				{
					m_idMap->GetAt(pos,hc,v);
					delete v;
				}
			}
			m_idMap->RemoveAll();
			//
			m_idCountMap->RemoveAll();
		}

		static void PushId(const _Id& id,ULONG in_hc=0)
		{
			IdMap& M = Acquire();
			//
			ULONG hc;
			if (in_hc) hc = in_hc; else hc = HashValue(id);
			_Id* pId;
			if (M.m_idMap->Lookup(hc,pId))
			{
				ULONG N;
				M.m_idCountMap->Lookup(hc,N);
				M.m_idCountMap->operator [](hc) = N+1;
			}
			else
			{
				M.m_idMap->operator [](hc) = new _Id(id);
				M.m_idCountMap->operator [](hc) = 1;
			}
		}

		static void PopId(const _Id& id,ULONG hc=0)
		{
			IdMap& M = Acquire();
			//
			ULONG hc1;
			if (hc) hc1 = hc; else hc1 = HashValue(id);
			_Id* pId;
			if (M.m_idMap->Lookup(hc1,pId))
			{
				ULONG N;
				M.m_idCountMap->Lookup(hc1,N);
				if (N == 1)
				{
					M.m_idMap->RemoveKey(hc1);
					M.m_idCountMap->RemoveKey(hc1);
				}
				else M.m_idCountMap->operator [](hc1) = N-1;
			}
		}

		static _Id GetId(ULONG hc)
		{
			IdMap& M = Acquire();
			//
			_Id* pId = 0;
			if (! M.m_idMap->Lookup(hc,pId)) return _Id();
			return *pId;
		}
	};
};



typedef Map<CString,CString> TextMap;



} // namespace  
