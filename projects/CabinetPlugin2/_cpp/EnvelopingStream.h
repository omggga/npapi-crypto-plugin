/*
 SlotEToken.h : Функции для работы с eToken при помощи библиотеки CryptoCOM.

 $Name:  $
 $Revision: 1.1.2.2 $
 $Date: 2008/10/10 15:38:07 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#include <SlotUtil.h>
#include <SlotAsn.h>

namespace 
{
    class EnvelopingStream // : Stream
    {
	public:
        Blob _mData;

        long _position;

        EnvelopingStream(Blob data)
        {
            _mData = data;
        }

        long Length()
        {
            return _mData.Length(); 
        }

        void Flush()
        {
            //throw new System.NotImplementedException();
        }

       long Position()
       {
                return _position;
       }

		void set_Position(long value)
        {
                if (value < 0 || value > _mData.Length())
                    MethodError(L"Wrong position: {0}");
                //
                _position = value;
        }

		enum SeekOrigin
		{
			Begin,
			Current,
			End 
		};

        long Seek(long offset, SeekOrigin origin)
        {
            switch (origin)
            {
                case SeekOrigin.Begin:
                    _position = offset;
                    break;
                    //
                case SeekOrigin.Current:
                    _position += offset;
                    break;
                    //
                case SeekOrigin.End:
                    _position = _mData.Length() + offset;
                    break;
            }
            return Position();
        }

        void SetLength(long value)
        {
            MethodError(L"NotSupportedException");
        }

        int Read(Blob buffer, int offset, int count)
        {
            if (offset < 0 || offset >= buffer.Length())
                MethodError(L"Wrong offset {0} in a buffer of size {1}");
            //
            if (count <= 0) return 0;
            //
            if (_position >= _mData.Length()) return 0;
            //
            int len = count;
            if (len > _mData.Length() - _position) len = _mData.Length() - (int)_position;
            //
			memcpy(buffer.GetBuffer(), _mData.GetBuffer()+(int)_position, len);
            //
            _position += len;
            //
            return len;
        }

        void Write(Blob buffer, int offset, int count)
        {
            MethodError(L"NotSupportedException");
        }

        bool CanRead()
        {
            return true; 
        }

        bool CanWrite()
        {
            return false; 
        }

        bool CanSeek()
        {
            return true; 
        }
    }
}
