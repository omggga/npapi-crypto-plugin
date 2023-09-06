
#pragma once

#ifdef _DEBUG
#pragma message("Including: " __FILE__)
#endif

// -----------------------------------------------------------------------------------------------
// {{ Debugging



#define _TRACE_CALLS_2



//	_SYS_INFO_DETAILED

//#		ifndef _SYS_INFO_DETAILED
//#		define _SYS_INFO_DETAILED 1
//#		endif
//
// force:
#		ifdef _SYS_INFO_DETAILED
#		undef _SYS_INFO_DETAILED
#		endif
#		define _SYS_INFO_DETAILED 1

// _TRACE_CREATION_EVENTS

#		ifndef _TRACE_CREATION_EVENTS
#		define _TRACE_CREATION_EVENTS 1
#		endif



// ----
// Protocol

#define _PROTOCOL_TRACE_EVENTS



// }} Debugging
// -----------------------------------------------------------------------------------------------
