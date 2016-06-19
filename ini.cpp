/*
 INI File Processor.
 Optimized INI text file processor for the embedded c++ system.
 Written by Huirak Lee (huirak.lee@gmail.com)
 Version 5.9.0, 2016/6/19

 Official Repository.
 https://bitbucket.org/mobileoff/ini

 Introduction.
 This toolkit was designed to achieve the best performance, and provide the convenience for managing standard INI file.
 Not only best for the embedded operating system, but also good for the non embedded system.

 Copyright (C) Huirak Lee. All rights reserved.
 The copyright of this toolkit is guaranteed in accordance with the international copyright law.

 For the Personal or Educational or Open Source Project Use.
 You may use this whole program, or part of the codes, for the personal purpose or the educational purpose also open source projects under the following restrictions:
 This toolkit may be redistributed while keeping untouched whole codes and program informations, original author name, license agreement and revision history. Modified codes shall not be redistributed.
 Any modified or derived source codes will descend this license policy and the copyright, so it's ownership belongs to the original author.
 If you found bugs or any improvement idea, let the original author know that to enhance the code quality and to fix possible bugs.

 For the Commercial Use.
 Contact the original author if you want to use this toolkit under the commercial purpose.
 Even if you are using this toolkit that belongs to some open source projects used in commercial applications, it is subjected to the commercial licensing rules.

 Revision History.
 v5.9.0, 160619, huirak.lee, Unlimit sect, key, and value length. Enhance GetTimeStamp performance. Add ValidateFormat to validate character set and basic INI formatting. Change CRC value format into string. Cygwin ports. FromString stops parsing when the string pool is out of space. Fix fopen read option of the ValidateFile. Fix app crash while saving empty INI file. Fix first timestamp not updated in case of the time element is 0.
 v5.5.0, 160606, huirak.lee, Faster parsing speed for FromString, but source string will be touched. Remove dynamic allocation of sect, key, value in FromString. Process dirty format ini. Add CreateNewItem. Reorder protected member variables and functions. Virtualize destructor ~Ini.
 v5.4.0, 160605, huirak.lee, Port to Visual Studio 2015, WIN32 platform. Ini now have two license type: free and commercial. Separate test codes to the test-ini.cpp. EOL character will be automatically selected to the compiler platform. Embed logging function to the Ini class.
 v5.3.5, 160604, huirak.lee, Fix Stopwatch time miscalculated in the MINGW compiler.
 v5.3.4, 160603, huirak.lee, Fix 'unsigned long' GetValueLong to 'long'. Add NDEBUG option for the release build recipe.
 v5.3.3, 160602, huirak.lee, Fix FromString return value unchecked in the LoadFile.
 v5.3.2, 160601, huirak.lee, ValidateFile() logs 'No CRC checksum' error.
 v5.3.1, 160601, huirak.lee, Add StringNoCaseCompare for easily changing the string compare function.
 v5.3.0, 160601, huirak.lee, Add FromString(), ToString() to serialize from / to string.
 v5.2.0, 160601, huirak.lee, Add [ini] prefix and current time stamp to the logs. Add short log definitions. Rename d_printf with ini_dprintf. Add GetLogLevel fcuntion.
 v5.1.0, 160601, huirak.lee, New GetValue & SetValue functions for the huge integer & floating types: long long, unsigned long long, long double.
 v5.0.0, 160531, huirak.lee, Move CRC header in front of the file. Allow empty section. Remove strict INI header checking. Allow '#' to describe remark. Quit LoadFile when there is no key to avoid crash. Enforce test functions. Refactor variable name, etc.
 v4.3.4, 160517, huirak.lee, TRACE has renamed d_printf. 
 v4.3.3, 160517, huirak.lee, Port to MINGW32.
 v4.3.2, 160421, huirak.lee, Define EOL character for the cross platform.
 v4.3.1, 160418, huirak.lee, Change long to unsigned int of the CRC table, Fix warnings under -Wall compile option.
 v4.3.0, 160301, huirak.lee, Fix CRC checking pass hole. Fix potential eternal parse loop in case of there is no CRC.
 v4.2.2, 151028, jungjun.lee, Fix 'Time of check time of use' issue.
 v4.2.1, 150407, huirak.lee, Remove warning: variable 'footerSize' set but not used [-Wunused-but-set-variable]
 v4.2.0, 141126, huirak.lee, Add CheckFileIntegrity function to verify broken file after writing a file.
 v4.1.0, 130625, huirak.lee, Add length field on each key, value due to SaveFile function crash
 v4.0.0, 130518, huirak.lee, Employ string pool. faster parsing(insertion) speed for the sorted file.
 v3.0.0, 130513, huirak.lee, Change STL map to vector and binary search due to SIGSEGV in QNX platform
 v2.5.0, 130208, huirak.lee, Improve buffer overrun safty with parsing, string compare. add debug function. easy set debug level.
 v2.4.0, 130206, huirak.lee, GetValueBuf, SetValueBuf added for easy buf handling
 v2.3.0, 121126, huirak.lee, Optimize for faster reading & writing
 v2.2.0, 121126, huirak.lee, Add key insurance check logic
 v2.1.0, 121125, huirak.lee, Add footer for crc checking
 v2.1.0, 121114, huirak.lee, Add SetValueStrBuf for buffer overrun safety
 v2.0.0, 121114, huirak.lee, Add polymorphic functions of GetValue, SetValue
 v1.9.0, 121112, huirak.lee, Add ByteArrayToHexString, HexStringToByteArray
 v1.8.1, 120807, huirak.lee, Fix first item omit bug
 v1.8.0, 120807, huirak.lee, Add SetValue
 v1.7.0, 120707, huirak.lee, Add GetValueRaw,SetValueRaw
 v1.6.1, 120707, huirak.lee, Rename GetValueDword as GetValueUInt, SetValue also
 v1.6.0, 120320, huirak.lee, Port to QNX 6.3.0
 v1.5.1, 100310, huirak.lee, Refactor FindFirstKey, FindNextKey
 v1.5.0, 100222, huirak.lee, Support default value
 v1.4.0, 091117, huirak.lee, Optimized
 v1.3.0, 091112, huirak.lee, Optimized
 v1.2.0, 091111, huirak.lee, Port to Visual Studio 2005
 v1.1.0, 071227, huirak.lee, Port to Embedded Visual C++ 4.0, STL
 v1.0.0, 060502, huirak.lee, Created
 
 Known Bugs.
 * N/A

 To Do.
 * Support inline remarks feature. #like this.
 * error C4996: '__sys_errlist': This function or variable may be unsafe. Consider using strerror instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
 * Fix -effc++ option error.

 TBD.
 * Detect contents changes so that not save the unchanged contents again.
 * Realloc strPool when it is out of space.
 * Set debug function of the caller.
 * Employ TDD.
 * Partially read, partially update the value, but concerning lower speed. 
*/
#include <sys/stat.h>
#include <errno.h>
#include <stdarg.h>
#include <io.h>
#include <assert.h>

#if defined WIN32
#include <winsock.h> //for htonl function.
#include <tchar.h>
#define ultoa _ultoa
#elif defined __CYGWIN__ 
#include <tchar.h> 
#include <arpa/inet.h> //for htonl function. 
#else
#include <arpa/inet.h> //for htonl function.
#endif

#include <algorithm>

#include "ini.h"

using namespace std;

#ifdef WIN32
//End Of Line character : Windows, DOS style
#define EOL "\r\n"
#else
//End Of Line character : UNIX, LINUX style
#define EOL "\n"
#endif

#define EOL_LEN (sizeof(EOL)-1)

static const unsigned char crcHeaderSig[4] = {'C','R','C','='};
static const int crc32StrSize = 4*2;//string format like '00ABCDEF'
static const int crcHeaderSize = sizeof(crcHeaderSig) + crc32StrSize + EOL_LEN;

//hexstr output is like 00ABCD..
//hexstr length shall be sizebin * 2
const char* 
BinToHexStr(void* bin, size_t sizebin, char* hexstr, size_t sizehex)
{
	if (bin == NULL || hexstr == NULL) {
		return NULL;
	}
	const unsigned char* p = (unsigned char*) bin;
	char *q = hexstr;
	//LOGD("%s : sizebin=%d", __FUNCTION__, sizebin);
	size_t len = min(sizebin, sizehex/2);
	for (unsigned int i = 0; i<len; i++) {
		//LOGD("%02X ",(unsigned char)*p);
		if (*p >= 16) *q = *p / 16 >= 10 ? ('A' + *p / 16 - 10) : '0' + *p / 16;
		else *q = '0';
		q++;
		if (*p % 16) *q = *p % 16 >= 10 ? ('A' + *p % 16 - 10) : ('0' + *p % 16);
		else *q = '0';
		q++;
		if (i + 1 == len) {
			*q = 0;
			break;
		}
		p++;
	}
	//LOGD("\n");
	return hexstr;
}

int Ini::logLevel = Normal;

void
Ini::Dprintf(int level, const char* fmt, ...)
{
	if (level < Ini::logLevel) {
		return;
	}
	va_list argList;
	va_start(argList,fmt);
	vfprintf(stdout,fmt,argList);
	va_end(argList);
}

#ifdef __MINGW32__
#include <sys/time.h>
#else
#include <time.h>
#endif

const char*
Ini::GetTimeStamp()
{
	static char timeStr[]="[HH:MM:SS.MLS]";
#if defined(WIN32) || defined(__MINGW32__)
	SYSTEMTIME stNow;
	static SYSTEMTIME stLast = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	GetSystemTime(&stNow);
	if (memcmp(&stNow, &stLast, sizeof(SYSTEMTIME))==0) {
		return timeStr;
	}
#if 1
	//fast.
	snprintf(timeStr, sizeof(timeStr), "[%02d:%02d:%02d.%03d]",
		stNow.wHour,
		stNow.wMinute,
		stNow.wSecond,
		stNow.wMilliseconds);
#else
	//slow. why?
	//timeStr[0] = '[';
	if (stNow.wHour != stLast.wHour) {
		timeStr[1] = '0' + stNow.wHour / 10;
		timeStr[2] = '0' + stNow.wHour % 10;
	}
	//timeStr[3] = ':';
	if (stNow.wMinute != stLast.wMinute) {
		timeStr[4] = '0' + stNow.wMinute / 10;
		timeStr[5] = '0' + stNow.wMinute % 10;
	}
	//timeStr[6] = ':';
	if (stNow.wSecond != stLast.wSecond) {
		timeStr[7] = '0' + stNow.wSecond / 10;
		timeStr[8] = '0' + stNow.wSecond % 10;
	}
	//timeStr[9] = '.';
	if (stNow.wMilliseconds != stLast.wMilliseconds) {
		timeStr[10] = '0' + stNow.wMilliseconds / 100;
		timeStr[11] = '0' + stNow.wMilliseconds / 10 % 10;
		timeStr[12] = '0' + stNow.wMilliseconds % 10;
	}
#endif
	//timeStr[13] = ']';
	//timeStr[14] = 0;
	memcpy(&stLast,&stNow,sizeof(SYSTEMTIME));	
#else
	timespec tsNow;	
	static timespec tsLast = { -1, -1 };
	tm tmNow;
	static tm tmLast = { -1,-1,-1,-1,-1,-1,-1,-1,-1 };

    if( clock_gettime(CLOCK_REALTIME, &tsNow) == -1 ) {
    	perror( "clock_gettime" );
    	return NULL;
    }

	if (memcmp(&tsNow, &tsLast, sizeof(timespec))==0) {
		return timeStr;
	}

	gmtime_r(&tsNow.tv_sec, &tmNow);
#if 0
	//slow - cygwin only
	snprintf(timeStr, sizeof(timeStr), "[%02d:%02d:%02d.%03ld]",
		tmNow.tm_hour,
		tmNow.tm_min,
		tmNow.tm_sec,
		tsNow.tv_nsec / 1000000);
#else
	//fast
	if (tmNow.tm_hour != tmLast.tm_hour) {
		timeStr[1] = '0' + tmNow.tm_hour / 10;
		timeStr[2] = '0' + tmNow.tm_hour % 10;
	}
	//timeStr[3] = ':';
	if (tmNow.tm_min != tmLast.tm_min) {
		timeStr[4] = '0' + tmNow.tm_min / 10;
		timeStr[5] = '0' + tmNow.tm_min % 10;
	}
	//timeStr[6] = ':';
	if (tmNow.tm_sec != tmLast.tm_sec) {
		timeStr[7] = '0' + tmNow.tm_sec / 10;
		timeStr[8] = '0' + tmNow.tm_sec % 10;
	}
	//timeStr[9] = '.';
	if (tsNow.tv_nsec != tsLast.tv_nsec) {
		int ms = tsNow.tv_nsec / 1000000;
		timeStr[10] = '0' + ms / 100;
		timeStr[11] = '0' + ms / 10 % 10;
		timeStr[12] = '0' + ms % 10;
	}
#endif
	//timeStr[13] = ']';
	//timeStr[14] = 0;	
	memcpy(&tmLast,&tmNow,sizeof(tm));
	memcpy(&tsLast,&tsNow,sizeof(timespec));	
#endif
	return timeStr;
}

//+For Visual Studio 2015
Ini::Section::CompareSection Ini::Section::Compare;
Ini::Item::CompareItem Ini::Item::Compare;

//------------->8------------->8------------->8------------->8------------->8------------->8
//>>> CRC32 begin

/*
 * Copyright (C) 1986 Gary S. Brown.  You may use this program, or
 * code or tables extracted from it, as desired without restriction.
 */

/* First, the polynomial itself and its table of feedback terms.  The  */
/* polynomial is                                                       */
/* X^32+X^26+X^23+X^22+X^16+X^12+X^11+X^10+X^8+X^7+X^5+X^4+X^2+X^1+X^0 */
/* Note that we take it "backwards" and put the highest-order term in  */
/* the lowest-order bit.  The X^32 term is "implied"; the LSB is the   */
/* X^31 term, etc.  The X^0 term (usually shown as "+1") results in    */
/* the MSB being 1.                                                    */

/* Note that the usual hardware shift register implementation, which   */
/* is what we're using (we're merely optimizing it by doing eight-bit  */
/* chunks at a time) shifts bits into the lowest-order term.  In our   */
/* implementation, that means shifting towards the right.  Why do we   */
/* do it this way?  Because the calculated CRC must be transmitted in  */
/* order from highest-order term to lowest-order term.  UARTs transmit */
/* characters in order from LSB to MSB.  By storing the CRC this way,  */
/* we hand it to the UART in the order low-byte to high-byte; the UART */
/* sends each low-bit to hight-bit; and the result is transmission bit */
/* by bit from highest- to lowest-order term without requiring any bit */
/* shuffling on our part.  Reception works similarly.                  */

/* The feedback terms table consists of 256, 32-bit entries.  Notes:   */
/*                                                                     */
/*     The table can be generated at runtime if desired; code to do so */
/*     is shown later.  It might not be obvious, but the feedback      */
/*     terms simply represent the results of eight shift/xor opera-    */
/*     tions for all combinations of data and CRC register values.     */
/*                                                                     */
/*     The values must be right-shifted by eight bits by the "updcrc"  */
/*     logic; the shift must be unsigned (bring in zeroes).  On some   */
/*     hardware you could probably optimize the shift in assembler by  */
/*     using byte-swap instructions.                                   */

//*Fix warning: narrowing conversion of '3134207493u' from 'unsigned int' to 'const long int' inside { } [-Wnarrowing]
static const unsigned int cr3tab[] = { /* CRC polynomial 0xedb88320 */
0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

#define UPDC32(b, c) (cr3tab[((int)c ^ b) & 0xff] ^ ((c >> 8) & 0x00FFFFFF))

//*Fix warning: narrowing conversion of '3134207493u' from 'unsigned int' to 'const long int' inside { } [-Wnarrowing]
static unsigned int 
GetCRC32(char *buf, int bufLen)
{
	unsigned int crc = 0xFFFFFFFFL; // it must be this
	for(int i=0; i<bufLen; i++) {
		crc = UPDC32(buf[i], crc);
	}
	return crc^0xFFFFFFFFL; // do not forget it!
}

//<<< End of CRC32
//------------->8------------->8------------->8------------->8------------->8------------->8

static bool 
FlushFile(FILE* file)
{
#if defined WIN32 || defined __CYGWIN__ //__MINGW32__
	int flush_res = fflush(file);
	if (flush_res) {
		LOGE("flush : %s\n", strerror(errno));
	}
	return !flush_res;
#else
	int fd = fileno(file);
	if (fd==-1) {
		LOGE("fileno : %s\n", strerror(errno));
		return false;
	}
	int r = fsync(fd);
	if (r) {
		LOGE("fsync : %s\n", strerror(errno));
		return false;
	}
#endif	
	return true;	
}

class FileBuffer
{
protected:	
	FILE *file;
	const char *name;
	char *buf;
	int size;
	char *p;
	char *e;
	int crc32;	
public:
	int err;	

	FileBuffer(FILE *file, size_t bufsize, const char* name = "")
	{
		this->buf	= (char*) malloc(bufsize);
		this->size	= bufsize;
		this->file	= file;
		this->name  = name;
		p = buf;
		e = buf + bufsize - 1;
		crc32 = 0xFFFFFFFFL;
		err = 0;
	}
	~FileBuffer()
	{
		free(buf);
		buf = NULL;
	}
	inline
	void push(char c)
	{
		*p++ = c;
		crc32 = UPDC32(c,crc32);
		if (p>=e) {
			flush();
		}
	}
	inline
	void push(const char *s)
	{
		int length=strlen(s);
		push(s,length);
	}
	inline
	void push(const char *s, int length)
	{
		if (p+length>=e) {
			flush();
		}
		memcpy(p,s,length);
		for(int i=0; i<length; i++) {
			crc32 = UPDC32(s[i], crc32);
		}
		p+=length;
	}
	inline
	void flush()
	{
		if (fwrite(buf,(p-buf)*sizeof(char),1,file)<1) {
			LOGE("fwrite %d bytes : %s (%s)\n", p-buf, name, strerror(errno));
			err++;
		} else {
			FlushFile(file);
			LOGD("%s %d bytes flushed : %s\n",__func__,p-buf, name);
		}
		p = buf;
	}
	inline
	int getCRC32()
	{
		return crc32 ^ 0xFFFFFFFFL;
	}
};

Ini::Ini(const int strpoolsize/*=256*1024*/)
{
	LOGD("%s, poolsize=%d\n", __FUNCTION__, strpoolsize);
	iniFileName[0] = 0;

	sects.reserve(100);
	lastParsedSection = sects.end();

	strPool = (char*)malloc(strpoolsize);
	if (strPool) {
		sizPool = strpoolsize;
		remPool = strpoolsize;
	}
	posPool = 0;
}

Ini::~Ini(void)
{
	LOGD("%s\n",__FUNCTION__);	
	if (strPool) {
		free(strPool);
		strPool = NULL;		
	}
}

void
Ini::Reset()
{
	sects.clear();
	lastParsedSection = sects.end();

	memset(iniFileName,0,sizeof(iniFileName));
	memset(strPool,0,sizPool);
	posPool = 0;
	remPool = sizPool;
}

//TBD: Reallocate strPool when it is out of space.
const char* 
Ini::PushString(const char* s) 
{
	size_t room = strlen(s) + 1;
	if (sizPool < posPool + room) {
		LOGE("Can't push the string to pool : string pool is full\n");
		return NULL;
	}
	memcpy(strPool + posPool, s, room);
	posPool += room;
	remPool -= room;
	return strPool + posPool - room;
}

bool
Ini::LoadFile(const char* theFileName, bool checkCRC)
{
	LOGD("%s: %s, checkCRC=%d\n", __FUNCTION__, theFileName, checkCRC);

	FILE *file = NULL;
	char *buf = NULL;
	bool result = false;

	do {
		long fileSize = 0;
		size_t strSize = 0;

		file = fopen(theFileName, "rb");
		if (file==NULL) {
			LOGE("fopen : %s (%s)\n",theFileName,strerror(errno));
			break;
		}

		if( -1 == fseek(file, 0L, SEEK_END) ) {
			LOGE("fseek SEEK_END : %s (%s)\n",theFileName,strerror(errno));
			break;
		}

		fileSize = ftell(file);
		if(-1L == fileSize) {
			LOGE("ftell : %s (%s)\n",theFileName,strerror(errno));
			break;	
		}
		LOGD("fileSize=%d\n",fileSize);

		if( -1 == fseek(file, 0L, SEEK_SET) ) {
			LOGE("fseek SEEK_SET : %s (%s)\n",theFileName,strerror(errno));
			break;
		}

		strSize = fileSize;

		buf = (char*)malloc(fileSize+1);
		if (!buf) {
			LOGE("malloc(%d) : %s\n",fileSize,theFileName);
			break;
		}

		int fread_res = 0;
		if ((fread_res=fread(buf,1,fileSize,file))!=fileSize) {
			LOGE("fread return %d : %s (%s)\n",fread_res,theFileName,strerror(errno));
			break;
		}

		*(buf + fileSize) = 0;

		bool haveCRC = false;
		if (crcHeaderSize < fileSize && memcmp(buf, crcHeaderSig, sizeof(crcHeaderSig))==0) {
			haveCRC = true;
			if (checkCRC) {
				char crc32str[crc32StrSize + 1] = { 0 };
				unsigned int crc32;
				memcpy(&crc32str,buf+sizeof(crcHeaderSig),crc32StrSize);
				HexStringToByteArray(crc32str, (unsigned char*)&crc32, sizeof(crc32));
				crc32 = ntohl(crc32);
				if (crc32!=GetCRC32(buf+crcHeaderSize,strSize-crcHeaderSize)) {
					LOGE("CRC checksum fail. broken file : %s\n",theFileName);
					break;
				}
			}
		}

		Reset();

		if (haveCRC) {
			if (!FromString(buf + crcHeaderSize, strSize - crcHeaderSize, true)) {
				break;
			}
		} else {
			if (!FromString(buf, strSize, false)) {
				break;
			}
		}

		SetFileName(theFileName);
		result = true;
	} while(0);
	if (buf)  free(buf);
	if (file) fclose(file);
	return result;
}

bool
Ini::ValidateFile(const char* theFileName)
{
	FILE* file = fopen(theFileName, "rb");	
	if (file == NULL) {
		LOGE("fopen : %s (%s)\n", theFileName, strerror(errno));
		return false;
	}
	char* buf = NULL;
	bool result = false;
	do {
		struct stat fileStat = {0,};
		if (stat(theFileName, &fileStat)) {
			LOGE("stat : %s (%s)\n",theFileName,strerror(errno));
			break;
		}
		size_t fileSize = fileStat.st_size;
		size_t strSize = fileStat.st_size;
		buf = (char*)malloc(fileSize);
		if (!buf) {
			LOGE("malloc(%d) : %s\n",fileSize,theFileName);
			break;
		}
		if (fread(buf,fileSize,1,file)!=1) {
			LOGE("fread : %s (%s)\n",theFileName,strerror(errno));
			break;
		}		
		if (fileSize <= crcHeaderSize) {
			LOGE("No CRC checksum : %s\n",theFileName);
			break;
		}
		if (memcmp(buf, crcHeaderSig, sizeof(crcHeaderSig))==0) {
			unsigned int crc32;
			char crc32str[crc32StrSize + 1] = { 0 };
			memcpy(&crc32str, buf + sizeof(crcHeaderSig), crc32StrSize);
			HexStringToByteArray(crc32str, (unsigned char*)&crc32, sizeof(crc32));
			crc32 = ntohl(crc32);
			if (crc32 != GetCRC32(buf + crcHeaderSize, strSize - crcHeaderSize)) {
				LOGE("CRC checksum fail. broken file : %s\n", theFileName);
				break;
			}
		} else {
			LOGE("No CRC checksum : %s\n",theFileName);
			break;			
		}
		result = true;
	} while(0);
	if (file) fclose(file);
	if (buf) free(buf);
	return result;
}

bool 
Ini::ValidateFormat(const char * buf, size_t buflen)
{
	const char *p = buf;
	const char *e = buf + min((size_t)100, buflen);
	int inich = 0;

	while (p < e) {
		if ((*p < 33 || 126 < *p) && *p!='\r' && *p!='\n' && *p!=' ' && *p!='\t' ) {
			LOGD("Invalid character at %d : 0x%X\n", p - buf, (unsigned char)*p);
			return false;
		} else if (*p == '=' || *p == '[' || *p==']') {
			inich++;
		}
		p++;
	}
	return 0 < inich;
}

bool
Ini::SaveFile(const char* theFileName, bool writeCRC)
{
	const char *fileName = theFileName ? theFileName : iniFileName;
	bool result = false;

	LOGD("fopen for write : %s\n", fileName);
	FILE* file = fopen(fileName, "wb");
	if (file==NULL) {
		LOGE("fopen : %s (%s)\n", fileName, strerror(errno));
		return false;
	}

	do {
		FileBuffer fb(file, 128*1024, fileName);
		if (writeCRC) {
			if (fwrite(crcHeaderSig,sizeof(crcHeaderSig),1,file)<1) {
				LOGE("fwrite crcHeaderSig : %s (%s)\n", fileName, strerror(errno));
				break;
			}
			char crcDummy[crc32StrSize] = { 0 };
			if (fwrite(&crcDummy,crc32StrSize,1,file)<1) {
				LOGE("fwrite crcDummy : %s (%s)\n", fileName, strerror(errno));
				break;
			}
			if (fwrite(EOL,EOL_LEN,1,file)<1) {
				LOGE("fwrite EOL : %s (%s)\n", fileName, strerror(errno));
				break;
			}
		}
		SectionList::iterator finalSect = sects.empty() ? sects.end() : --sects.end();
		for (SectionList::iterator sect=sects.begin(); sect!=sects.end(); sect++) {
			if (*sect->key) {
				fb.push('[');
				fb.push(sect->key, sect->keyLen);
				fb.push("]" EOL,1+EOL_LEN);
			}
			ItemList::iterator finalItem = sect->items.empty() ? sect->items.end() : --sect->items.end();
			for (ItemList::iterator item=sect->items.begin(); item!=sect->items.end(); item++) {
				fb.push(item->key,item->keyLen);
				fb.push('=');
				fb.push(item->val,item->valLen);
				if (sect!=finalSect || item!=finalItem) {
					fb.push(EOL,EOL_LEN);
				}
			}
			if (sect!=finalSect) {
				fb.push(EOL,EOL_LEN);
			}
		}
		fb.flush();
		if (fb.err) {
			LOGE("fwrite contents : %s (%s)\n", fileName, strerror(errno));
			break;
		}
		if (!FlushFile(file)) {
			break;
		}
		if (writeCRC) {
			if (fseek(file,sizeof(crcHeaderSig),SEEK_SET)==-1) {
				LOGE("fseek crcHeaderSig : %s (%s)\n", fileName, strerror(errno));
				break;
			}
			int crc32le = fb.getCRC32();
			int crc32be = htonl(crc32le);
			char crc32str[crc32StrSize + 1] = { 0 };
			BinToHexStr(&crc32be, sizeof(crc32be), crc32str, sizeof(crc32str));
			if (fwrite(crc32str,crc32StrSize,1,file)<1) {
				LOGE("fwrite crc : %s (%s)\n", fileName, strerror(errno));
				break;
			}
		}
		if (!FlushFile(file)) {
			break;
		}
		result = true;
	} while(0);

	fclose(file);	

	return result;
}

void
Ini::SetFileName(const char* theFileName)
{
	snprintf(iniFileName, sizeof(iniFileName), "%s", theFileName);
}

const char*
Ini::GetFileName()
{
	return iniFileName;
}

//buf shall be terminated with null character
bool
Ini::FromString(const char* buf, size_t buflen, bool sorted)
{
	bool result = false;

	Reset();

	do {
		const char *p = buf;
		const char *e = buf + buflen;
		const char *sos = NULL; //start of section

		if (!ValidateFormat(buf, buflen)) {
			break;
		}

		while(p<e) {
			while(p<e && (!*p || *p==' ' || *p=='\r' || *p=='\n' || *p=='\t')) {
				p++;
			}
			if (e <= p) {
				break;
			}
			if (*p=='[') {
				p++;
				//get sect
				while(p<e && *p==' ') {
					p++;
				}
				sos = p; //start of section
				const char *eos = NULL; //end of section
				while(p<e && *p!='\r' && *p!='\n') {
					if (*p == ']') {
						eos = p;
					}
					p++;
				}
				if (eos) {					
					while (*(eos-1) == ' ') {
						eos--;//remove trail blank
					}
					*(char*)eos = 0;
					LOGD("sect(%d)='%s'\n", eos - sos, sos);
					if (remPool < (size_t)(eos - sos)) {
						LOGE("Not enough room in the strPool to store the section\n");
						break;
					}
				}
				continue;
			} else if (*p==';' || *p=='#') { //Add '#' for the remarks - 160530
				//remarks
				while(p<e && *p!='\r' && *p!='\n') {
					p++;
				}
				continue;
			}
			//get key
			const char *sok = p; //start of key - 160606
			const char *eok = NULL; //end of key - 160606
			//remove && *p!='[' condition to allow key like 'key[0]' - 160606
			while(p<e && *p!='=' && *p!='\r' && *p!='\n') {
				p++;
			}
			if (*p != '=' || p == sok) {
				LOGE("No key!\n");
				p++;
				continue;
			}
			eok = p; //end of key - 160606
			while (*(eok - 1) == ' ') {
				eok--;//remove trail blank
			}
			*(char*)eok = 0;
			LOGD("key(%d)='%s'\n", eok - sok, sok);
			if (remPool < (size_t)(eok - sok)) {
				LOGE("Not enough room in the strPool to store the key\n");
				break;
			}
			if (p<e) {
				p++;
			}
			while (p<e && *p == ' ') {
				p++;//remove precede blank
			}
			//get value
			const char *sov = p; //start of value - 160606
			while (p<e && *p != '\r' && *p != '\n') {
				p++;
			}
			const char *eov = p; //end of value - 160606
			while (*(eov - 1) == ' ') {
				eov--;//remove trail blank
			}
			*(char*)eov = 0;
			LOGD("val(%d)='%s'\n", eov - sov, sov);
			if (remPool < (size_t)(eov - sov)) {
				LOGE("Not enough room in the strPool to store the value\n");
				break;
			}
			else if (sok && *sok) { //*Allow empty section - 160530
				SetValueStr(sos, sok, sov, sorted ? true : false); //allow empty value
			}
			sok = NULL;
			sov = NULL;
		}
		result = true;
	} while(0);
	return result;
}

string
Ini::ToString()
{
	string str;
	SectionList::iterator finalSect = sects.empty() ? sects.end() : --sects.end();
	for (SectionList::iterator sect=sects.begin(); sect!=sects.end(); sect++) {
		if (*sect->key) {
			str.push_back('[');
			str.append(sect->key,sect->keyLen);
			str.append("]" EOL,1+EOL_LEN);
		}
		ItemList::iterator finalItem = sect->items.empty() ? sect->items.end() : --sect->items.end();
		for (ItemList::iterator item=sect->items.begin(); item!=sect->items.end(); item++) {
			str.append(item->key,item->keyLen);
			str.push_back('=');
			str.append(item->val,item->valLen);
			if (sect!=finalSect || item!=finalItem) {
				str.append(EOL,EOL_LEN);
			}
		}
		if (sect!=finalSect) {
			str.append(EOL,EOL_LEN);
		}
	}	
	return str;
}

int
Ini::GetItemCount() 
{
	int itemCount=0;	
	for (SectionList::iterator sect=sects.begin(); sect!=sects.end(); sect++) {
		itemCount += sect->items.size();
	}	
	return itemCount;
}

Ini::SectionList::iterator
Ini::FindSection(const char* sect)
{
	SectionList::iterator foundSect = lower_bound(sects.begin(), sects.end(), sect, Section::Compare);	
	if (foundSect==sects.end()) {
		LOGD("Section not found : '%s'\n", sect);
		return sects.end();
	} else {
		if (StringNoCaseCompare(foundSect->key, sect, maxSectKeyLen)) {
			LOGD("Section not found : '%s'\n", foundSect->key);
			return sects.end();
		} else {
			LOGD("Section exist : '%s'\n", foundSect->key);
			return foundSect;
		}
	}
}

Ini::ItemList::iterator
Ini::FindItem(const char* sect, const char*key)
{
	SectionList::iterator foundSect = FindSection(sect);
	if (foundSect==sects.end()) {
		//return NULL;
		return emptySection.items.end();//for gpp - 140103
	}
	ItemList::iterator foundItem = lower_bound(foundSect->items.begin(), foundSect->items.end(), key, Item::Compare);
	if (foundItem==foundSect->items.end()) {
		LOGD("Item not found : '%s'\n", key);
		return foundSect->items.end();
	} else {
		if (StringNoCaseCompare(foundItem->key, key, maxSectKeyLen)) {
			LOGD("Item not found : '%s'\n", key);
			return foundSect->items.end();
		} else {
			LOGD("Item exist : '%s'='%s'\n", key, foundItem->val);
			return foundItem;
		}
	}
}

const char*
Ini::FindFirstSection()
{
	lastFoundSectionFFS = sects.end();
	if (!sects.empty()) {
		lastFoundSectionFFS = sects.begin();
		return lastFoundSectionFFS->key;
	}
	return NULL;
}

const char*
Ini::FindNextSection()
{
	if (lastFoundSectionFFS==sects.end()) {
		return NULL;
	}
	lastFoundSectionFFS++;
	if (lastFoundSectionFFS==sects.end()) {
		return NULL;
	}
	return lastFoundSectionFFS->key;
}

int
Ini::FindFirstKey(const char* sect, const char** key, const char** val)
{
	lastFoundSectionFFK = sects.end();
	if (!sect) { //+allow empty section - 160531
		sect = "";
	}		
	if (!key || !val) {
		return 0;
	}	
	if (sects.empty()) {
		return 0;
	}
	SectionList::iterator foundSect = FindSection(sect);
	if (foundSect == sects.end()) {
		return 0;
	}
	if (foundSect->items.empty()) {
		return 0;
	}
	lastFoundSectionFFK = foundSect;
	lastFoundItemFFK = foundSect->items.begin();
	*key = lastFoundItemFFK->key;
	*val = lastFoundItemFFK->val;
	return (int)foundSect->items.size();
}

int
Ini::FindNextKey(const char** key, const char** val)
{
	if (!key || !val) {
		return 0;
	}
	if (lastFoundSectionFFK == sects.end()) {
		return 0;
	}
	if (lastFoundItemFFK == lastFoundSectionFFK->items.end()) {	
		LOGD("%s End of item (1)\n", __FUNCTION__);
		return 0;
	}
	if (++lastFoundItemFFK == lastFoundSectionFFK->items.end()) {
		LOGD("%s End of item (2)\n", __FUNCTION__);
		return 0;
	}
	*key = lastFoundItemFFK->key;
	*val = lastFoundItemFFK->val;
	return 1;
}

bool
Ini::IsSection(const char* sect)
{
//--- allow empty section - 160531
//	if (!sect) {
//		return false;
//	}
//---
	return FindSection(sect) != sects.end();
}

bool
Ini::IsKey(const char* sect, const char* key)
{
	if (!sect) { //+allow empty section - 160531
		sect = "";
	}	
	if (!key) {
		return false;
	}
	SectionList::iterator foundSect = FindSection(sect);
	if (foundSect==sects.end()) {
		return false;
	}
	ItemList::iterator foundItem = FindItem(sect,key);
	//return foundItem!=foundSect->items.end() && foundItem!=NULL;
	return foundItem!=emptySection.items.end() && foundItem!=foundSect->items.end();//for gpp - 140103
}

const char*
Ini::GetValueStr(const char* sect, const char* key, const char* _default)
{
	if (!sect) { //+allow empty section - 160531
		sect = "";
	}	
	if (!key) {
		return _default;
	}
	if (sects.empty()) {
		return _default;
	}
	SectionList::iterator foundSect = FindSection(sect);
	if (foundSect==sects.end()) {
		return _default;
	}
	ItemList::iterator item = FindItem(sect,key);
	if (item==foundSect->items.end()) {
		return _default;
	}
	return item->val;
}

void
Ini::GetValueStrBuf(const char* sect, const char* key, char* strBuf, size_t bufSize, const char* _default)
{
	strBuf[0]=0;
	const char* str=GetValueStr(sect, key);
	if (str==NULL) {
		memset(strBuf, 0, bufSize);
		return;
	}
	snprintf(strBuf, bufSize, "%s", str);
}

int
Ini::GetValueInt(const char* sect, const char* key, int _default)
{
	const char* val = GetValueStr(sect,key);
	if (val == NULL || *val == 0) {
		return _default;
	}
	return atoi(val);
}

unsigned int
Ini::GetValueUInt(const char* sect, const char* key, unsigned int _default)
{
	const char* val = GetValueStr(sect,key);
	if (val == NULL || *val == 0) {
		return _default;
	}
	char *endptr;
	return strtoul(val, &endptr, 10);
}

long
Ini::GetValueLong(const char* sect, const char* key, long _default/*=0*/)
{
	const char* val = GetValueStr(sect,key);
	if (val == NULL || *val == 0) {
		return _default;
	}
	char *endptr;
	return strtol(val, &endptr, 10);
}

unsigned long
Ini::GetValueULong(const char* sect, const char* key, unsigned long _default)
{
	const char* val = GetValueStr(sect,key);
	if (val == NULL || *val == 0) {
		return _default;
	}
	char *endptr;
	return strtoul(val, &endptr, 10);
}

float
Ini::GetValueFloat(const char* sect, const char* key, float _default/*=0.0*/)
{
	const char* val=GetValueStr(sect,key);
	if (val == NULL || *val == 0) {
		return _default;
	}
	char* endptr;
	return strtof(val,&endptr);
}

double
Ini::GetValueDouble(const char* sect, const char* key, double _default/*=0.0*/)
{
	const char* val=GetValueStr(sect,key);
	if (val == NULL || *val == 0) {
		return _default;
	}
	char* endptr;
	return strtod(val,&endptr);
}

char*
Ini::ByteArrayToHexString(const unsigned char* byteArray, size_t sizeByteArray)
{
	//00 AB CD ...
	char* s=(char*)malloc(3*sizeByteArray); //Last blank for the null character.
	if (s==NULL) {
		return NULL;
	}
	const unsigned char* p=byteArray;
	char *q=s;
	//LOGD("ByteArrayToHexString : length=%d, byteArray=", sizeByteArray);
	for(unsigned int i=0; i<sizeByteArray; i++) {
		//LOGD("%02X ",(unsigned char)*p);
		if (*p>=16) *q = *p/16 >= 10 ? ('A' + *p/16 - 10) : '0' + *p/16;
		else *q='0';
		q++;
		if (*p%16) *q = *p%16 >= 10 ? ('A' + *p%16 - 10) : ('0' + *p%16);
		else *q = '0';
		q++;
		if (i+1==sizeByteArray) { 
			*q=0; 
			break; 
		}
		*q++ = ' ';
		p++;
	}
	//LOGD("\n");
	return s;
}

int
Ini::HexStringToByteArray(const char* hexString, unsigned char* byteArray, size_t sizeByteArray)
{
	int hexStrLen = strlen(hexString);
	const char* p = hexString;
	const char* e = p + hexStrLen;
	//LOGD("HexStringToByteArray : strlength=%d, sizeByteArray=%d\n", hexStrLen,sizeByteArray);
	if (!byteArray) {
		return 0;
	}
	unsigned char* bp=byteArray;
	while(p<e && (unsigned int)(bp-byteArray) < sizeByteArray) {
		//LOGD("%02X ",(unsigned char)*p);
		unsigned char h=0;
		/***/if ('0'<=*p && *p<='9') h = *p-'0';
		else if ('A'<=*p && *p<='F') h = *p-'A'+10;
		else if ('a'<=*p && *p<='f') h = *p-'a'+10;
		else break;
		p++;
		unsigned char l=0;
		//LOGD("%02X ",(unsigned char)*p);
		/***/if ('0'<=*p && *p<='9') l = *p-'0';
		else if ('A'<=*p && *p<='F') l = *p-'A'+10;
		else if ('a'<=*p && *p<='f') l = *p-'a'+10;
		else { l=h; h=0; }
		p++;
		*bp++ = 16*h + l;
		while (*p==' ' && p<e) {
			//LOGD("%02X ",(unsigned char)*p);
			p++;
		}
		if (*p==0) {
			break;
		}
	}
	return bp-byteArray;
}

void
Ini::GetValueRaw(const char* sect, const char* key, void* byteArray, const size_t sizeByteArray, unsigned char _default/*=0x00*/)
{
	const char* hexString=GetValueStr(sect, key, NULL);
	if (hexString && *hexString) {
		HexStringToByteArray(hexString, (unsigned char*)byteArray, sizeByteArray);
	} else {
		memset(byteArray,_default,sizeByteArray);
	}
}

void
Ini::SetValueRaw(const char* sect, const char* key, const void* byteArray, const size_t sizeByteArray)
{
	if (sizeByteArray==0) {
		SetValueStr(sect, key, "");
		return;
	}
	char* hexString = ByteArrayToHexString((unsigned char*)byteArray, sizeByteArray);
	if (hexString!=NULL) {
		SetValueStr(sect, key, hexString);
		free(hexString);
	}
}

void
Ini::SetValueStrBuf(const char* sect, const char* key, char* buf, size_t bufSize)
{
	char* dupString = (char*)malloc(bufSize);
	if (!dupString) {
		return;
	}
	snprintf(dupString,bufSize,"%s",buf);
	SetValueStr(sect,key,dupString);
	free(dupString);
}

void
Ini::CreateNewItem(Item& newItem, const char* key, const char* val) 
{
	newItem.key = PushString(key);
	newItem.keyLen = strlen(key);
	newItem.val = PushString(val);
	newItem.valLen = strlen(val);
	newItem.valRoom = newItem.valLen + 1;
}

void
Ini::SetValueStr(const char* sect, const char* key, const char* val, bool sortedFile /*= false*/)
{
	if (!sect) { //+allow empty section - 160531
		sect = "";
	}	
	if (!key||!val) {
		return;
	}

	int valRoom = strlen(val)+1;
	if (sortedFile) {
		if (lastParsedSection==sects.end() || StringNoCaseCompare(lastParsedSection->key, sect, maxSectKeyLen)) {
			LOGD("Create section : '%s'\n", sect);

			Section newSect;
			newSect.key = PushString(sect);
			newSect.keyLen = strlen(sect);

			Item newItem;
			CreateNewItem(newItem,key,val);
			newSect.items.push_back(newItem);
			sects.push_back(newSect);

			lastParsedSection = --sects.end();
			return;
		} else {
			Item newItem;
			CreateNewItem(newItem,key,val);
			lastParsedSection->items.push_back(newItem);
			return;
		}
	}

	SectionList::iterator foundSect = lower_bound(sects.begin(), sects.end(), sect, Section::Compare);

	if (foundSect==sects.end()) {
		LOGD("Create section : '%s'\n", sect);

		Section newSect;
		newSect.key = PushString(sect);
		newSect.keyLen = strlen(sect);
		
		LOGD("Create item : '%s'='%s'\n", key, val);

		Item newItem;
		CreateNewItem(newItem,key,val);
		newSect.items.push_back(newItem);

		sects.push_back(newSect);
	} else {
		if (StringNoCaseCompare(foundSect->key, sect, maxSectKeyLen)) {
			LOGD("Create section : '%s'\n", sect);

			Section newSect;
			newSect.key = PushString(sect);
			newSect.keyLen = strlen(sect);
			
			LOGD("Create item : '%s'='%s'\n", key, val);

			Item newItem;
			CreateNewItem(newItem,key,val);
			newSect.items.push_back(newItem);

			sects.insert(foundSect, newSect);
		} else {
			LOGD("Section exist : '%s'\n",foundSect->key);

			ItemList::iterator foundItem = lower_bound(foundSect->items.begin(), foundSect->items.end(), key, Item::Compare);

			if (foundItem==foundSect->items.end()) {
				LOGD("Create item : '%s'='%s'\n", key, val);

				Item newItem;
				CreateNewItem(newItem,key,val);
				foundSect->items.push_back(newItem);
			} else {
				if (StringNoCaseCompare(foundItem->key, key, maxSectKeyLen)) {
					LOGD("Create item : '%s'='%s'\n", key, val);

					Item newItem;
					CreateNewItem(newItem,key,val);
					foundSect->items.insert(foundItem,newItem);
				} else {
					LOGD("Item exist : '%s'='%s'\n", key, val);

					if ( valRoom <= foundItem->valRoom ) {
						memcpy((void*)foundItem->val,val,valRoom);
					} else {
						foundItem->val = PushString(val);
						foundItem->valLen = strlen(val);
						foundItem->valRoom = valRoom;
					}
				}
			}
		}
	}
}

/*TBD:
void
Ini::SetValueStrMulti(const char* sect, const char* key, const char* val)
{
	if (!sect||!key||!val) return;
	SectionList::iterator sect = lower_bound(sects.begin(), sects.end(),
		sect, Section::Compare);
	if (sect==sects.end()) {
		LOGD("Create section : %s\n", sect);

		Section newSect;
		snprintf(newSect.key,maxSectKeyLen,"%s",sect);

		LOGD("Create item : %s=%s\n", key, val);

		Item newItem;
		snprintf(i.key,maxSectKeyLen,"%s",key);
		i.val = val;

		newSect.items.push_back(i);

		sects.push_back(newSect);
	} else {
		if (StringNoCaseCompare(sect->key,sect,maxSectKeyLen)) {
			LOGD("Create section : %s\n", sect);

			Section newSect;
			snprintf(newSect.key,maxSectKeyLen,"%s",sect);

			LOGD("Create item : %s=%s\n", key, val);

			Item i;
			snprintf(i.key,maxSectKeyLen,"%s",key);
			i.val = val;

			newSect.items.push_back(i);

			sects.insert(sect, newSect);
		} else {
			LOGD("Section exist : %s\n",sect->key);

			ItemList::iterator it = lower_bound(sect->items.begin(), sect->items.end(),
					key, Item::Compare);
			if (it==sect->items.end()) {
				LOGD("Create item : %s=%s\n", key, val);

				Item i;

				snprintf(i.key,maxSectKeyLen,"%s",key);
				i.val = val;

				sect->items.push_back(i);
			} else {
				if (StringNoCaseCompare(it->key, key, maxSectKeyLen)) {
					LOGD("Create item : %s=%s\n", key, val);

					Item i;

					snprintf(i.key,maxSectKeyLen,"%s",key);
					i.val = val;

					sect->items.insert(it,i);
				} else {
					LOGD("Item exist : %s=%s\n", key, val);

					//TBD..
					//it->val = val;

					Item i;

					snprintf(i.key,maxSectKeyLen,"%s",key);
					i.val = val;

					sect->items.insert(it,i);
				}
			}
		}
	}
}
*/

void
Ini::SetValueInt(const char* sect, const char* key, int val)
{
	//32bit machine: -2147483648 ~ 2147483647
	//TBD: fit max int width in the 64bit machine?	
	char buf[100];
#if defined (WIN32) && !defined(__CYGWIN__)
	itoa(val, buf, 10);
#else
	snprintf(buf,sizeof(buf),"%d",val);
#endif
	SetValueStr(sect,key,buf);
}

void
Ini::SetValueUInt(const char* sect, const char* key, unsigned int val)
{
	//TBD: fit max unsigned int width in the 64bit machine?	
	char buf[100];
#ifdef ultoa
	ultoa(val,buf,10);
#else	
	snprintf(buf,sizeof(buf),"%u",val);
#endif
	SetValueStr(sect,key,buf);
}

void
Ini::SetValueLong(const char* sect, const char* key, long val)
{
	//long l = -2147483648;//mingw32-gcc: ../ini.cpp:1581:2: error: this decimal constant is unsigned only in ISO C90 [-Werror]	
	//TBD: fit buffer size to max value width
	char buf[100];
#if defined (WIN32)
	ltoa(val, buf, 10);
#else
	snprintf(buf,sizeof(buf),"%ld",val);
#endif
	SetValueStr(sect,key,buf);
}

void
Ini::SetValueULong(const char* sect, const char* key, unsigned long val)
{
	//32bit machine: 4,294,967,295
	char buf[100];
#ifdef ultoa
	ultoa(val, buf, 10);
#else
	snprintf(buf,sizeof(buf),"%lu",val);
#endif
	SetValueStr(sect,key,buf);
}

void
Ini::SetValueLongLong(const char* sect, const char* key, long long val)
{
	//language spec: –9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
	//but actually...
	//long long ll = -9223372036854775808; //mingw32-gcc: ../ini.cpp:1610:18: error: integer constant is so large that it is unsigned [-Werror]
	//TBD: fit buffer size to max value width
	char buf[sizeof("-9223372036854775808")];
#if (defined (WIN32) && !defined(__MINGW32__)) || defined(__CYGWIN__)
	snprintf(buf, sizeof(buf), "%lld", val);
#else
	lltoa(val, buf, 10);
#endif
	SetValueStr(sect,key,buf);
}

void
Ini::SetValueULongLong(const char* sect, const char* key, unsigned long long val)
{
	//language spec: 0 to 18,446,744,073,709,551,615
	//but actually it is up to 1844674407370955169
	//unsigned long long ull = 18446744073709551615;//mingw32-gcc: ../ini.cpp:1617:27: error: integer constant is so large that it is unsigned [-Werror]	
	//TBD: fit buffer size to max value width
	char buf[sizeof("18446744073709551615")];
#if (defined (WIN32) && !defined(__MINGW32__)) || defined(__CYGWIN__)
	snprintf(buf, sizeof(buf), "%llu", val);
#else
	ulltoa(val, buf, 10);
#endif
	SetValueStr(sect,key,buf);
}

void
Ini::SetValueFloat(const char* sect, const char* key, float val)
{
	char buf[100];
	//TBD: input x to 0.xf
	snprintf(buf,100,"%0.7f",val);
	SetValueStr(sect,key,buf);
}

void
Ini::SetValueDouble(const char* sect, const char* key, double val)
{
	char buf[100];
	//TBD: input x to 0.xf
	snprintf(buf,100,"%0.7f",val);
	SetValueStr(sect,key,buf);
}

void
Ini::Dump(void)
{
	LOGN("%s:\n", __func__);
	for (SectionList::iterator sect=sects.begin(); sect!=sects.end(); sect++) {
		LOGN("[%s]\n",sect->key);
		for (ItemList::iterator item=sect->items.begin(); item!=sect->items.end(); item++) {
			LOGN("%s=%s\n",item->key,item->val);
		}
	}
}

//------------->8------------->8------------->8------------->8------------->8------------->8