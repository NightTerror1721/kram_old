#pragma once

#include <cstdlib>
#include "utils.h"


using byte = uint8;
using word = uint16;
using dword = uint32;
using qword = uint64;

using bin_t = byte*;
using std::size_t;
using offset_t = size_t;

#define __mem_offset_cast(bin, off, type) reinterpret_cast<type>((bin) + (off))
#define __mem_offset(bin, off) ((bin) + (off))

struct __memblock
{
	bin_t _bin;
	size_t _size;
};

__memblock create_raw_memblock(const size_t);
void free_memblock(__memblock&);
void dump_memblock(__memblock&);
void fill_memblock(__memblock&, byte);

#define mb_offset_cast(blk, off, type) __mem_offset_cast((blk)._bin, off, type)
#define mb_offset(blk, off) __mem_offset((blk)._bin, off)



/* CallStack definition */
using CallStack = __memblock;

#define __cs_push(cs, off, type, value) (*mb_offset_cast(cs, off, type) = (value))
#define cs_push_b(cs, off, value) (*mb_offset(cs, off) = (value))
#define cs_push_w(cs, off, value) __cs_push(cs, off, word*, value)
#define cs_push_dw(cs, off, value) __cs_push(cs, off, dword*, value)
#define cs_push_qw(cs, off, value) __cs_push(cs, off, qword*, value)

#define __cs_pop(cs, off, type) (*mb_offset_cast(cs, off, type))
#define cs_pop_b(cs, off) (*mb_offset(cs, off))
#define cs_pop_w(cs, off) __cs_pop(cs, off, word*)
#define cs_pop_dw(cs, off) __cs_pop(cs, off, dword*)
#define cs_pop_qw(cs, off) __cs_pop(cs, off, qword*)



/* directions */
struct dir_t
{
	offset_t _off;
	byte _type;

	enum type : byte
	{
		Stack,
		Heap,
		Global
	};
};
#define DIR_SIZE sizeof(dir_t)

#define cs_push_dir(cs, off, value) __cs_push(cs, off, dir_t*, value)
#define cs_pop_dir(cs, off) __cs_pop(cs, off, dir_t*)
