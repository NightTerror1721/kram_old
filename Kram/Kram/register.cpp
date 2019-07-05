#include "register.h"

#define REG8_PARTS sizeof(byte_t) / sizeof(qword_t)
#define REG16_PARTS sizeof(word_t) / sizeof(qword_t)
#define REG32_PARTS sizeof(dword_t) / sizeof(qword_t)
#define REG64_PARTS sizeof(qword_t) / sizeof(qword_t)

#define part(reg) static_cast<byte_t>(reg)
#define get_reg(regs, reg) (regs + part(reg))
#define get_creg(regs, reg, type) const_cast<type*>(get_reg(regs, reg))

reg8_t Registers::operator[] (const R8& reg) { return { get_reg(_reg8, reg) }; }
const reg8_t Registers::operator[] (const R8& reg) const { return { get_creg(_reg8, reg, byte_t) }; }

reg16_t Registers::operator[] (const R16& reg) { return { get_reg(_reg16, reg) }; }
const reg16_t Registers::operator[] (const R16& reg) const { return { get_creg(_reg16, reg, word_t) }; }

reg32_t Registers::operator[] (const R32& reg) { return { get_reg(_reg32, reg) }; }
const reg32_t Registers::operator[] (const R32& reg) const { return { get_creg(_reg32, reg, dword_t) }; }

reg64_t Registers::operator[] (const R64& reg) { return { get_reg(_reg64, reg) }; }
const reg64_t Registers::operator[] (const R64& reg) const { return { get_creg(_reg64, reg, qword_t) }; }
