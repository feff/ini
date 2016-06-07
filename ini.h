/*
 INI File Processor.
 Optimized INI text file processor for the embedded c++ system.
 Written by Huirak Lee (huirak.lee@gmail.com)
 Version 5.5.0, 2016/6/6

 Official Repository.
 https://bitbucket.org/mobileoff/ini

 Copyright (C) Huirak Lee. All rights reserved.
 The copyright of this toolkit is guaranteed in accordance with the international copyright law.

 For the Personal or Educational or Open Source Project Use.
 You may use this whole program, or part of the codes, for the personal purpose or the educational purpose also Open Source Projects under the following restrictions:
 This toolkit may be redistributed while keeping untouched whole codes and program informations, original author name, license agreement and revision history. Modified codes shall not be redistributed.
 Any modified or derived source codes will descend this license policy and the copyright, so it's ownership belongs to the original author.
 If you found bugs or any improvement idea, let the original author know that to enhance the code quality and to fix possible bugs.

 For the Commercial Use.
 Contact the original author if you want to use this toolkit under the commercial purpose.
 Even if you are using this toolkit that belongs to some open source projects used in commercial applications subject to commercial licensing rules.

 Revision History.
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
#pragma once

#include <stdio.h>
#include <string.h>//for gpp - 140103
#include <vector>
#include <string>

inline int StringNoCaseCompare(const char* sz1, const char* sz2, int maxlen) {
#if defined(WIN32)
	//error C4996: 'strnicmp': The POSIX name for this item is deprecated. Instead, use the ISO C and C++ conformant name: _strnicmp. See online help for details.
	//return strnicmp(sz1, sz2, maxlen);
	return _strnicmp(sz1, sz2, maxlen);
#else
	return strncasecmp(sz1, sz2, maxlen);
#endif	
} 

class Ini
{
public:
	//Don't looks good, but seems no better way out.
	static const int maxSectKeyLen = 256;
	static const int maxValLen = 128*1024;
protected:
	struct Item
	{
		const char* key;
		int keyLen;
		const char* val;
		int valLen;
		int valRoom;

		Item() : key(NULL), keyLen(0), val(NULL), valLen(0), valRoom(0) {
		}
		
		static struct CompareItem {
			bool operator() ( const char* key, const Item& item) const {
				return StringNoCaseCompare(key, item.key, maxSectKeyLen) < 0;
			}
			bool operator() ( const char* key, const char* key1) const {
				return StringNoCaseCompare(key, key1, maxSectKeyLen) < 0;
			}
			bool operator() ( const Item& item, const char* key) const {
				return StringNoCaseCompare(item.key, key, maxSectKeyLen) < 0;
			}
			bool operator() ( const Item& item, const Item& item1) const {
				return StringNoCaseCompare(item.key, item1.key, maxSectKeyLen) < 0;
			}
		} Compare;
	};

	typedef std::vector<Item> ItemList;

	struct Section
	{
		const char* key;
		int keyLen;		
		ItemList items;

		Section() : key(NULL), keyLen(0) {
			items.reserve(100);
		}
		
		static struct CompareSection {
			bool operator() ( const char* key, const Section& s) const {
				return StringNoCaseCompare(key, s.key, maxSectKeyLen) < 0;
			}
			bool operator() ( const char* key, const char* key1) const {
				return StringNoCaseCompare(key, key1, maxSectKeyLen) < 0;
			}
			bool operator() ( const Section& s, const char* key) const {
				return StringNoCaseCompare(s.key, key, maxSectKeyLen) < 0;
			}
			bool operator() ( const Section& s, const Section& s1) const {
				return StringNoCaseCompare(s.key, s1.key, maxSectKeyLen) < 0;
			}
		} Compare;
	};

	typedef std::vector<Section> SectionList;	

	friend Item;
	friend Section;

	SectionList sects;
	SectionList::iterator lastParsedSection;
	SectionList::iterator lastFoundSectionFFS;
	SectionList::iterator lastFoundSectionFFK;
	ItemList::iterator lastFoundItemFFK;
	Section emptySection;//for gpp - 140103

	char* strPool;
	size_t sizPool;
	unsigned int posPool;

	char iniFileName[256];	
	static int logLevel;

	void CreateNewItem(Item& newItem, const char* key, const char* val);
	const char* PushString(const char* s);
	SectionList::iterator FindSection(const char* sect);
	ItemList::iterator FindItem(const char* sect, const char*key);
public:
	// Life Cycle
	Ini(const int strPoolSize=64*1024);
	virtual ~Ini(void);
	bool LoadFile(const char* iniFileName, bool checkCRC=true);
	bool SaveFile(const char* iniFileName=NULL, bool writeCRC=true);
	void SetFileName(const char* iniFileName);
	const char* GetFileName();
	bool FromString(const char* buf, size_t buflen, bool sorted=false);
	std::string ToString();	
	void Reset();
	static bool ValidateFile(const char* iniFileName);
	// Property
	inline int GetSectCount() {return sects.size();} //+huirak.lee 150517
	int GetItemCount();	//+huirak.lee 150517
	// Search Functions
	bool IsSection(const char* sect);
	bool IsKey(const char* sect, const char* key);
	int FindFirstKey(const char* sect, const char** key, const char** val);
	int FindNextKey(const char** key, const char** val);
	const char* FindFirstSection();
	const char* FindNextSection();
	// Get Functions
	inline char GetValue(const char* sect, const char* key, char& val, char _default=0) {return(val = (char)GetValueInt(sect,key,_default));}
	inline unsigned char GetValue(const char* sect, const char* key, unsigned char& val, unsigned char _default=0) {return(val = (unsigned char)GetValueInt(sect,key,_default));}
	inline short GetValue(const char* sect, const char* key, short& val, char _default=0) {return(val = (short)GetValueInt(sect,key,_default));}
	inline unsigned short GetValue(const char* sect, const char* key, unsigned short& val, unsigned short _default=0) {return(val = (unsigned short)GetValueInt(sect,key,_default));}
	inline int GetValue(const char* sect, const char* key, int& val, int _default=0) {return(val = GetValueInt(sect,key,_default));}
	inline unsigned int GetValue(const char* sect, const char* key, unsigned int& val, int _default=0) {return(val = GetValueUInt(sect,key,_default));}
	inline long GetValue(const char* sect, const char* key, long& val, long _default=0) {return (val=GetValueLong(sect,key,_default));}
	inline unsigned long GetValue(const char* sect, const char* key, unsigned long& val, unsigned long _default=0) {return (val=GetValueULong(sect, key, _default));}
	inline bool GetValue(const char* sect, const char* key, bool& val, bool _default=0) {return(val = GetValueInt(sect,key,_default) ? true : false) ;}
	inline float GetValue(const char* sect, const char* key, float& val, float _default=0.0) {return(val = GetValueFloat(sect,key,_default));}
	inline double GetValue(const char* sect, const char* key, double& val, float _default=0.0) {return(val = GetValueDouble(sect,key,_default));}
	inline long double GetValue(const char* sect, const char* key, long double& val, long double _default=0.0) {return (val = GetValueLongDouble(sect,key,_default));}
	const char* GetValueStr(const char* sect, const char* key, const char* _default="");
	void GetValueStrBuf(const char* sect, const char* key, char* buf, size_t bufSize, const char* _default="");
	int GetValueInt(const char* sect, const char* key, int _default=0);
	unsigned int GetValueUInt(const char* sect, const char* key, unsigned int _default=0);
	long GetValueLong(const char* sect, const char* key, long _default=0);
	unsigned long GetValueULong(const char* sect, const char* key, unsigned long _default=0);
	float GetValueFloat(const char* sect, const char* key, float _default=0.0);
	double GetValueDouble(const char* sect, const char* key, double _default=0.0);
	inline long double GetValueLongDouble(const char* sect, const char* key, long double _default=0.0) {return GetValueDouble(sect,key,_default);}
	void GetValueRaw(const char* sect, const char* key, void* byteArray, const size_t byteArraySize, unsigned char _default=0x00);
	#define GetValueBuf(sect,key,buf) GetValueRaw(sect,key,&buf,sizeof(buf))
	// Set Functions
	inline void SetValue(const char* sect, const char* key, char val) {SetValueInt(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, unsigned char val) {SetValueInt(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, const char val[]) {SetValueStr(sect, key, val);} //+Fix SetValue("key","value") linked to SetValue(const char*,bool) - 160531
	//inline void SetValue(const char* sect, const char* key, const unsigned char* val,size_t size) {SetValueRaw(sect, key, val, size);}
	inline void SetValue(const char* sect, const char* key, short val) {SetValueInt(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, unsigned short val) {SetValueInt(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, int val) {SetValueInt(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, unsigned int val) {SetValueUInt(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, long val) {SetValueLong(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, unsigned long val) {SetValueULong(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, long long val) {SetValueLongLong(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, unsigned long long val)	{SetValueULongLong(sect, key, val);}	
	inline void SetValue(const char* sect, const char* key, bool val) {SetValueUInt(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, float val) {SetValueFloat(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, double val) {SetValueDouble(sect, key, val);}
	inline void SetValue(const char* sect, const char* key, long double val) {SetValueLongDouble(sect, key, val);}
	void SetValueStr(const char* sect, const char* key, const char* val, bool sortedFile = false);
	void SetValueStrBuf(const char* sect, const char* key, char* buf, size_t bufSize);
	//TBD: void SetValueStrMulti(const char* sect, const char* key, const char* val);
	void SetValueInt(const char* sect, const char* key, int val);
	void SetValueUInt(const char* sect, const char* key, unsigned int val);
	void SetValueLong(const char* sect, const char* key, long val);
	void SetValueULong(const char* sect, const char* key, unsigned long val);
	void SetValueLongLong(const char* sect, const char* key, long long val);
	void SetValueULongLong(const char* sect, const char* key, unsigned long long val);
	void SetValueFloat(const char* sect, const char* key, float val);
	void SetValueDouble(const char* sect, const char* key, double val);
	inline void SetValueLongDouble(const char* sect, const char* key, long double val) {SetValueDouble(sect,key,val);}
	void SetValueRaw(const char* sect, const char* key, const void* buf, const size_t bufLen);
	#define SetValueBuf(sect,key,buf) SetValueRaw(sect,key,&buf,sizeof(buf))	
	//Helper func.
	static char* ByteArrayToHexString(const unsigned char* byteArray, size_t sizeArray);
	static int HexStringToByteArray(const char* hexString, unsigned char* byteArray, size_t sizeByteArray);
	void Dump(void);
	enum LogLevel {
		Debug = 0,
		Verbose = 1,
		Normal = 2,
		Error = 3,
	};
	static void SetLogLevel(int level) {logLevel = level;}
	static int GetLogLevel() {return logLevel;}
	static void Dprintf(int level, const char* fmt, ...);
	static std::string GetTimeStamp();
};

#define LOG_PREFIX "[ini]%s "

#define LOGD(fmt,...) Ini::Dprintf(Ini::Debug, LOG_PREFIX fmt, Ini::GetTimeStamp().c_str(), ##__VA_ARGS__)
#define LOGV(fmt,...) Ini::Dprintf(Ini::Verbose, LOG_PREFIX fmt, Ini::GetTimeStamp().c_str(), ##__VA_ARGS__)
#define LOGN(fmt,...) Ini::Dprintf(Ini::Normal, LOG_PREFIX fmt, Ini::GetTimeStamp().c_str(), ##__VA_ARGS__)
#define LOGE(fmt,...) Ini::Dprintf(Ini::Error, LOG_PREFIX fmt, Ini::GetTimeStamp().c_str(), ##__VA_ARGS__)

#ifdef NDEBUG
	#undef LOGD
	#define LOGD(fmt,...) ((void)0)
#endif