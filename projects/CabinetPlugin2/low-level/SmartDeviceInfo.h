/*
 SmartDeviceInfo.h : �������� ����������. 

 $Name:  $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/10 15:38:07 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// 
//
#include "../_cpp/SlotUtil.h"
#include "../_cpp/SlotAsn.h"
#include "SmartXml.h"

#ifndef _DI_UNK_DEVICE_TYPE
#define _DI_UNK_DEVICE_TYPE (L"unknown")
#endif

#ifndef _DI_UNK_DEVICE_T_RDRIVE
#define _DI_UNK_DEVICE_T_RDRIVE (L"RemovableDrive")
#endif

#ifndef _DI_UNK_DEVICE_T_ETOKEN
#define _DI_UNK_DEVICE_T_ETOKEN (L"eToken")
#endif

#ifndef _DI_UNK_DEVICE_ID_DELIM
#define _DI_UNK_DEVICE_ID_DELIM (L":")
#endif

namespace  {

	class DeviceInfo
	{
	public:
		string DeviceType; 

		string ID; 

	private:
		inline void Clear()
		{
			DeviceType = L""; 
			ID = L""; 
		}

	public:
		DeviceInfo() 
		{
		}

		const DeviceInfo& operator =(const DeviceInfo& other) 
		{
			DeviceType = other.DeviceType; 
			ID = other.ID; 
			//
			return other; 
		}

		DeviceInfo(const DeviceInfo& other) 
		{
			*this = other; 
		}

		inline void ParseID(const string& ID_) 
		{
			try
			{
				DeviceType = _DI_UNK_DEVICE_TYPE; 
				//
				int p1 = ID_.Find(_DI_UNK_DEVICE_ID_DELIM); 
				if (p1 == -1)
				{
					ID = ID_; 
				}
				else
				{
					ID = ID_.Right(ID_.GetLength()-p1-_W(_DI_UNK_DEVICE_ID_DELIM).GetLength()); 
					DeviceType = ID_.Left(p1); 
				}
			}
			_Catch()
		}

		inline void Analyze() 
		{
			try
			{
			}
			_Catch() 
		}

		inline void SetID(const string& ID_) 
		{
			try
			{
				ParseID(ID_); 
				Analyze(); 
			}
			_Catch()
		}

		inline void SetIDAndType(const string& ID_, const string& DeviceType_) 
		{
			try
			{
				ID = ID_; 
				DeviceType = DeviceType_; 
				Analyze(); 
			}
			_Catch()
		}

		inline bool Unknown() 
		{
			try
			{
				bool f = false; 
				if (DeviceType.GetLength() == 0) f = true;
				else if (DeviceType == _DI_UNK_DEVICE_TYPE) f = true;
				return f; 
			}
			_Catch() 
		}
	};

} // namespace  
