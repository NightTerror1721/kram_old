#pragma once

#include <vector>

#include "raws.h"
#include "register.h"

typedef uint32_t direction_t;

class DirectionHub;

class DirectionPart
{
private:
	const direction_t _min_dir;
	const direction_t _max_dir;

public:
	DirectionPart(const direction_t min_dir, const direction_t max_dir);
	virtual ~DirectionPart();

	direction_t min_dir() const;
	direction_t max_dir() const;

	bool is_valid_direction(const direction_t dir) const;

	virtual void move_to_register(const direction_t dir, reg8_t& reg) const = 0;
	virtual void move_to_register(const direction_t dir, reg16_t& reg) const = 0;
	virtual void move_to_register(const direction_t dir, reg32_t& reg) const = 0;
	virtual void move_to_register(const direction_t dir, reg64_t& reg) const = 0;

	virtual void move_from_register(const reg8_t& reg, const direction_t dir) = 0;
	virtual void move_from_register(const reg16_t& reg, const direction_t dir) = 0;
	virtual void move_from_register(const reg32_t& reg, const direction_t dir) = 0;
	virtual void move_from_register(const reg64_t& reg, const direction_t dir) = 0;

	friend class DirectionHub;

private:
	direction_t adapt_dir(const direction_t dir) const;
};

class DirectionHub
{
private:
	std::vector<DirectionPart*> _parts;

public:
	DirectionHub();
	~DirectionHub();

	void move_to_register(const direction_t dir, reg8_t& reg) const;
	void move_to_register(const direction_t dir, reg16_t& reg) const;
	void move_to_register(const direction_t dir, reg32_t& reg) const;
	void move_to_register(const direction_t dir, reg64_t& reg) const;

	void move_from_register(const reg8_t& reg, const direction_t dir);
	void move_from_register(const reg16_t& reg, const direction_t dir);
	void move_from_register(const reg32_t& reg, const direction_t dir);
	void move_from_register(const reg64_t& reg, const direction_t dir);

	template<class _Ty, class... _Args>
	void create_new_part(_Args&&... args)
	{
		_parts.push_back(new _Ty{ args... });
	}

private:
	DirectionPart* _Find_part(const direction_t dir) const;
};
