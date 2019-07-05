#pragma once

#include "raws.h"

#include <vector>

#define REGISTER_COUNT 8

class Memory;
class Registers;

namespace
{
	using RegAllocator = qword_t*;
	template<class _Ty>
	class __Reg;
}

using reg8_t = __Reg<byte_t>;
using reg16_t = __Reg<word_t>;
using reg32_t = __Reg<dword_t>;
using reg64_t = __Reg<qword_t>;

namespace
{
	template<class _Ty>
	class __Reg
	{
	private:
		_Ty* _ptr;

		__Reg(_Ty* ptr) : _ptr{ ptr } {}

		inline _Ty& operator* () { return *_ptr; }
		inline const _Ty& operator* () const { return *_ptr; }

	public:
		__Reg(const __Reg& reg) : _ptr{ reg._ptr }  {}

		__Reg& operator= (const __Reg& reg) { _ptr = reg._ptr; return *this; }

		friend class ::Memory;
		friend class ::Registers;
	};
}

enum class R64 : byte_t { RAX, RBX, RCX, RDX, RSX, RHX, RRX, RIX };

enum class R32 : byte_t
{
	EAX = 0, EA0 = EAX, EA1,
	EBX = 2, EB0 = EBX, EB1,
	ECX = 4, EC0 = ECX, EC1,
	EDX = 6, ED0 = EDX, ED1,
	ESX = 8, ES0 = ESX, ES1,
	EHX = 10, EH0 = EHX, EH1,
	ERX = 12, ER0 = ERX, ER1,
	EIX = 14, EI0 = EIX, EI1
};

enum class R16 : byte_t
{
	AX = 0, A0 = AX, A1, A2, A3,
	BX = 4, B0 = BX, B1, B2, B3,
	CX = 8, C0 = CX, C1, C2, C3,
	DX = 12, D0 = DX, D1, D2, D3,
	SX = 16, S0 = SX, S1, S2, S3,
	HX = 20, H0 = HX, H1, H2, H3,
	RX = 24, R0 = RX, R1, R2, R3,
	IX = 28, I0 = IX, I1, I2, I3,
};

enum class R8 : byte_t
{
	A0L, A0H, A1L, A1H, A2L, A2H, A3L, A3H,
	B0L, B0H, B1L, B1H, B2L, B2H, B3L, B3H,
	C0L, C0H, C1L, C1H, C2L, C2H, C3L, C3H,
	D0L, D0H, D1L, D1H, D2L, D2H, D3L, D3H,
	S0L, S0H, S1L, S1H, S2L, S2H, S3L, S3H,
	H0L, H0H, H1L, H1H, H2L, H2H, H3L, H3H,
	R0L, R0H, R1L, R1H, R2L, R2H, R3L, R3H,
	I0L, I0H, I1L, I1H, I2L, I2H, I3L, I3H
};

class Registers
{
private:
	union
	{
		byte_t _reg8[sizeof(qword_t) / sizeof(byte_t) * REGISTER_COUNT];
		word_t _reg16[sizeof(qword_t) / sizeof(word_t) * REGISTER_COUNT];
		dword_t _reg32[sizeof(qword_t) / sizeof(dword_t) * REGISTER_COUNT];
		qword_t _reg64[sizeof(qword_t) / sizeof(qword_t) * REGISTER_COUNT];
	};

public:
	constexpr size_t count() const { return 8; }

	reg8_t operator[] (const R8& reg);
	const reg8_t operator[] (const R8& reg) const;

	reg16_t operator[] (const R16& reg);
	const reg16_t operator[] (const R16& reg) const;

	reg32_t operator[] (const R32& reg);
	const reg32_t operator[] (const R32& reg) const;

	reg64_t operator[] (const R64& reg);
	const reg64_t operator[] (const R64& reg) const;
};
