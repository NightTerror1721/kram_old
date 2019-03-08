#pragma once

#include "utils.h"

#include <string>

enum class ktype : uint8
{
	Undefined		= 0x00,

	Integer_8		= 0x01,
	Integer_16		= 0x02,
	Integer_32		= 0x03,
	Integer_64		= 0x04,
	U_Integer_8		= 0x05,
	U_Integer_16	= 0x06,
	U_Integer_32	= 0x07,
	U_Integer_64	= 0x08,
	Float_32		= 0x09,
	Float_64		= 0x0A,
	Boolean			= 0x0B,
	String			= 0x0C,

	List			= 0x0D,
	Tuple			= 0x0E,
	Set				= 0x0F,
	Map				= 0x10,

	Object			= 0x11,

	Iterable		= 0x12,
	Callable		= 0x13,
	Bytes			= 0x14,
	Userdefined		= 0x15
};

struct kvalue
{
	const ktype __type;

	inline kvalue(const ktype _type) : __type(_type) {}
	inline kvalue(const kvalue& __v) : __type(__v.__type) {}
	inline kvalue(const kvalue&& __v) : __type(__v.__type) {}
};

struct kundef : public kvalue {};

template<typename _Type, ktype _KType>
struct __k_oneattr_type : public kvalue
{
	_Type __value;

	inline __k_oneattr_type(const _Type _value) : kvalue(_KType), __value(_value) {}
	inline __k_oneattr_type(const __k_oneattr_type& __v) : kvalue(_KType), __value(__v.__value) {}
	inline __k_oneattr_type(const __k_oneattr_type&& __v) : kvalue(_KType), __value(__v.__value) {}

	inline __k_oneattr_type<_Type, _KType>& operator= (const __k_oneattr_type<_Type, _KType>& __v)
	{
		__value = __v.__value;
		return *this;
	}
};

using kint8 = __k_oneattr_type<int8, ktype::Integer_8>;
using kint16 = __k_oneattr_type<int16, ktype::Integer_16>;
using kint32 = __k_oneattr_type<int32, ktype::Integer_32>;
using kint64 = __k_oneattr_type<int64, ktype::Integer_64>;
using kuint8 = __k_oneattr_type<uint8, ktype::U_Integer_8>;
using kuint16 = __k_oneattr_type<uint16, ktype::U_Integer_16>;
using kuint32 = __k_oneattr_type<uint32, ktype::U_Integer_32>;
using kuint64 = __k_oneattr_type<uint64, ktype::U_Integer_64>;

using kfloat32 = __k_oneattr_type<float, ktype::Float_32>;
using kfloat64 = __k_oneattr_type<double, ktype::Float_64>;

using kbool = __k_oneattr_type<bool, ktype::Boolean>;


struct kstr : public kvalue
{
	wchar_t* __data;
	size_t __len;

	kstr(wchar_t* _str, size_t _len) : kvalue(ktype::String), __data(_str), __len(_len) {}
	kstr(std::wstring _str) : kstr(_str.c_str(), _str.length()) {}
	kstr(char* _str, size_t _len) : kvalue(ktype::String), __data(nullptr), __len(_len)
	{
		std::wstring _wstr(_len, L'#');
		std::mbstowcs(&_wstr[0], _str, _len);
		__data = &_wstr[0];
	}
};

