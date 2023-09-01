

//#define TRACE_1_8_1_A

//#define TEST_SHOW_RECEIPT
//#define TEST_SHOW_RECEIPT_SERVER_REPLY

// ----
// ���� []

#define TRACE__PROTOCOL_OPERATION(O,echo) {}
//#define TRACE__PROTOCOL_OPERATION(O,echo) { TRACE_LINE2(_T("[:f:%s] %s"), CString(O).GetString(), CString(echo) ) }

#define TRACE__PROTOCOL_ACTIVITY
