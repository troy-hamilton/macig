#include <stddef.h>
#include <stdint.h>

enum
{
	GOOD, // a generic good condition
	BAD, // a generic bad condition
	INCMPLMSG, // message was incomplete, and more data should be appended
	BROKENMSG, // message was broken, and the cleanup should be performed
	FAILEDCOND, // a condition failed, and cleanup should be performed
	WRITEFUL, // a write occurred, and it is safe to check for a new message
	GET,
	PUT,
	POST,
	DELETE	
};
