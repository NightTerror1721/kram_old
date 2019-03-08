#include "types.h"
#include <iostream>

int main(int argc, char** argv)
{
	kint8 val = 10;

	kint8 other_val = val;
	kint8 last(0);
	last = val;

	std::cout << "val: " << &val << "; other_val: " << &other_val << "; last: " << &last << std::endl;

	std::cout << sizeof(kint8) << std::endl;

	std::system("pause");

	return 0;
}