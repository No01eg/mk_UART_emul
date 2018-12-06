#ifndef __TYPES__
#define __TYPES__

	typedef signed char        s8;
	typedef short              s16;
	typedef int                s32;
	typedef long long          s64;
	typedef unsigned char      u8;
	typedef unsigned short     u16;
	typedef unsigned int       u32;
	typedef unsigned long long u64;

#define PACK_SIZE 256


#ifdef WINDOWS
#define stm_memcpy(dest,source,count) memcpy(dest,source,count);
#define get_sys_time(st_time) \
SYSTEMTIME st; \
GetSystemTime(&st); \
st_time->days = st.wDay; \
st_time->hours = st.wHour; \
st_time->minuts = st.wMinute; \
st_time->months = st.wMonth; \
st_time->seconds = st.wSecond; \
st_time->years = st.wYear;
#endif
#include "header.h"
	void protocol_get_time(time* t);

#endif //!__TYPES__
