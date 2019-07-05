#include "memory.h"

#include <cstdlib>
#include <sstream>
#include <cstring>

#define rcast(type, value) reinterpret_cast<type>(value)
#define redirect(type, offset) rcast(type *, (rcast(byte_t*, this->_mem) + (offset)))
#define check_bounds(offset, size) if ( (offset) + (size) >= this->_size ) { throw bad_mem_offset{ (offset) }; }

bad_mem_offset::bad_mem_offset(const size_t offset) :
	kram_error{ "invalid memory direction access" },
	_offset{ offset }
{}

size_t bad_mem_offset::offset() const { return _offset; }

Memory::Memory(size_t size) :
	_size{ size },
	_mem{ std::malloc(size) }
{}

Memory::~Memory()
{
	std::free(_mem);
}

size_t Memory::size() const { return _size; }

void Memory::move_to_register(size_t offset, reg8_t& reg) { check_bounds(offset, sizeof(byte_t)) *reg = *redirect(byte_t, offset); }
void Memory::move_to_register(size_t offset, reg16_t& reg) { check_bounds(offset, sizeof(word_t)) *reg = *redirect(word_t, offset); }
void Memory::move_to_register(size_t offset, reg32_t& reg) { check_bounds(offset, sizeof(dword_t)) *reg = *redirect(dword_t, offset); }
void Memory::move_to_register(size_t offset, reg64_t& reg) { check_bounds(offset, sizeof(qword_t)) *reg = *redirect(qword_t, offset); }

void Memory::move_from_register(reg8_t& reg, size_t offset) { check_bounds(offset, sizeof(byte_t)) *redirect(byte_t, offset) = *reg; }
void Memory::move_from_register(reg16_t& reg, size_t offset) { check_bounds(offset, sizeof(word_t)) *redirect(word_t, offset) = *reg; }
void Memory::move_from_register(reg32_t& reg, size_t offset) { check_bounds(offset, sizeof(dword_t)) *redirect(dword_t, offset) = *reg; }
void Memory::move_from_register(reg64_t& reg, size_t offset) { check_bounds(offset, sizeof(qword_t)) *redirect(qword_t, offset) = *reg; }

void Memory::move(size_t dest, size_t source, size_t length)
{
	check_bounds(dest, length);
	check_bounds(source, length);
	std::memcpy(rcast(byte_t*, this->_mem) + dest, rcast(byte_t*, this->_mem) + source, length);
}
