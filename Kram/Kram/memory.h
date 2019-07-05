#pragma once

#include <cinttypes>

#include "error.h"
#include "register.h"

DECLARE_ERROR_TYPE(bad_mem_offset)
{
private:
	size_t _offset;

public:
	bad_mem_offset(const size_t offset);

	size_t offset() const;
};

class Memory
{
private:
	void* const _mem;
	const size_t _size;

public:
	Memory(size_t size);
	~Memory();

	size_t size() const;
	
	void move_to_register(size_t offset, reg8_t& reg);
	void move_to_register(size_t offset, reg16_t& reg);
	void move_to_register(size_t offset, reg32_t& reg);
	void move_to_register(size_t offset, reg64_t& reg);

	void move_from_register(reg8_t& reg, size_t offset);
	void move_from_register(reg16_t& reg, size_t offset);
	void move_from_register(reg32_t& reg, size_t offset);
	void move_from_register(reg64_t& reg, size_t offset);

	void move(size_t dest, size_t source, size_t length);
};
