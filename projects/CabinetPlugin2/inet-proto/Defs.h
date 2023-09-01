
#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

#define SP_INITIAL_CACHE_ENTRY_SIZE 512

#define SP_FILE_BUF_SIZE 4096

// CABINET 

#define _PROTOCOL_CLSID_STR (L"9212F305-5FFF-4FFA-9931-6048592BFAED")
#define _MIME_FILTER_CLSID_STR (L"875DBF3D-D009-414f-ACDF-704F74524F08")

// Gate

#define LOCAL_GATE_PROGID (L"Protocol.LocalGate")

// Web

// #define CABINET_START_PAGE_PATH _T("/protocol/Start.xml")

// XML

#define Protocol_NsUri (L"http://cabinet.example.com/schema/-protocol/rel-1/")

// DocumentHandler

#define HandlerStep_OnRequest		1 
#define HandlerStep_OnSave			2 
#define HandlerStep_OnOpen			3 
