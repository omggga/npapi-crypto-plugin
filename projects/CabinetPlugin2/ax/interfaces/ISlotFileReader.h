/*
 COM-интерфейс ISlotFileReader --- Дополнительный интерфейс для потока чтения из файла или URL.

 $Name: work1 $
 $Revision: 1.1.2.3 $
 $Date: 2008/10/31 15:25:53 $
 */

#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

/* ISlotFileReader */

#ifdef AX_ISlotFileReader_IDL
[
	object,
	uuid("9F3659D2-513D-474f-9734-3C33077F0235"),
	oleautomation,	
	helpstring("ISlotFileReader Interface"),
	pointer_default(unique)
]
#else
[
	uuid("9F3659D2-513D-474f-9734-3C33077F0235"),
	helpstring("ISlotFileReader Interface")
]
#endif
__interface ISlotFileReader : public IUnknown 
{
public:
	// ----
	// Чтение из файла - основная функция 

	[propput, helpstring("property Path")] STDMETHOD(Path)([in] BSTR path);
	[propget, helpstring("property Path")] STDMETHOD(Path)([out,retval] BSTR* out_path);

	STDMETHOD(Open)();



	// ----
	// Дополнительные возможности

	// * Файл во временных файлах интернета 

	STDMETHOD(CreateInCache)(); 

	[propput, helpstring("property CacheUrl")] STDMETHOD(CacheUrl)([in] BSTR cacheUrl);
	[propget, helpstring("property CacheUrl")] STDMETHOD(CacheUrl)([in] BSTR* out_cacheUrl);

	STDMETHOD(SetCacheUrlExt)(BSTR url,BSTR ext); 

	// * Запись файла 

	// Скопировать все данные из потока inputStream, если путь уже известен 

	STDMETHOD(WriteStream)([in] IStream* inputStream);

	STDMETHOD(WriteXmlDocument)([in] IUnknown* document); 

	STDMETHOD(WriteSetOpen)();

	STDMETHOD(WriteOpen)();

	STDMETHOD(WriteClose)(); 
}; 
