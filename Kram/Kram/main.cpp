#include "memory.h"
#include <iostream>

int main(int argc, char** argv)
{
	CallStack cs = create_raw_memblock(16);
	fill_memblock(cs, 0);
	dump_memblock(cs);

	cs_push_dw(cs, 0, 255);
	dump_memblock(cs);

	std::cout << cs_pop_dw(cs, 0) << std::endl;

	free_memblock(cs);

	std::system("pause");

	return 0;
}