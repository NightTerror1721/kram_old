#pragma once

#include "utils.h"

using kbyte   = int8;
using kshort  = int16;
using kint    = int32;
using klong   = int64;

using kubyte  = uint8;
using kushort = uint16;
using kuint   = uint32;
using kulong  = uint64;

using kfloat  = float;
using kdouble = double;

using kchar   = uint16;

using kbool   = uint8;

struct karray
{
	size_t _len;
	uint8* _dat;
};

struct kclass
{

};

struct kobject
{
	size_t _len;
	kclass* _class;
	uint8* _dat;
};

#define KBYTE_SIZE sizeof(kbyte)
#define KSHORT_SIZE sizeof(kshort)
#define KINT_SIZE sizeof(kint)
#define KLONG_SIZE sizeof(klong)

#define KUBYTE_SIZE sizeof(kubyte)
#define KUSHORT_SIZE sizeof(kushort)
#define KUINT_SIZE sizeof(kuint)
#define KULONG_SIZE sizeof(kulong)

#define KFLOAT_SIZE sizeof(kfloat)
#define KDOUBLE_SIZE sizeof(kdouble)

#define KCHAR_SIZE sizeof(kchar)

#define KBOOL_SIZE sizeof(kbool)

#define get_karray_size(_arr) (sizeof(size_t) + ((_arr)._len * sizeof(uint8)))
#define get_kobject_size(_obj) (sizeof(kclass*) + ((_obj)._len * sizeof(uint8)))
