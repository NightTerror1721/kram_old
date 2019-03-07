#include "memory.h"

#include <iostream>

__memblock create_raw_memblock(const size_t size)
{
	__memblock blk;
	blk._bin = reinterpret_cast<bin_t>(std::malloc(size));
	blk._size = size;
	return blk;
}

void free_memblock(__memblock& blk)
{
	std::free(blk._bin);
	blk._size = 0;
}

void dump_memblock(__memblock& blk)
{
	std::cout << std::hex;
	for (offset_t i = 0; i < blk._size; i++)
		std::cout << static_cast<int>(*mb_offset(blk, i)) << " ";
	std::cout << std::dec << std::endl;
}

void fill_memblock(__memblock& blk, byte val)
{
	std::memset(blk._bin, val, sizeof(byte) * blk._size);
}
