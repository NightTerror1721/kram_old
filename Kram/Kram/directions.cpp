#include "directions.h"

#include <algorithm>

DirectionPart::DirectionPart(const direction_t min_dir, const direction_t max_dir) :
	_min_dir{ std::min(min_dir, max_dir) },
	_max_dir{ std::max(min_dir, max_dir) }
{}

DirectionPart::~DirectionPart() {}

direction_t DirectionPart::min_dir() const { return _min_dir; }
direction_t DirectionPart::max_dir() const { return _max_dir; }

bool DirectionPart::is_valid_direction(const direction_t dir) const { return dir >= _min_dir && dir <= _max_dir; }

direction_t DirectionPart::adapt_dir(const direction_t dir) const { return dir - _min_dir; }



DirectionHub::DirectionHub() :
	_parts{}
{}
DirectionHub::~DirectionHub()
{
	auto it = _parts.begin();
	while (it != _parts.end())
	{
		delete *it;
		it = _parts.erase(it);
	}
}

void DirectionHub::move_to_register(const direction_t dir, reg8_t& reg) const
{
	DirectionPart* part = _Find_part(dir);
	if (part)
		part->move_to_register(part->adapt_dir(dir), reg);
}
void DirectionHub::move_to_register(const direction_t dir, reg16_t& reg) const
{
	DirectionPart* part = _Find_part(dir);
	if (part)
		part->move_to_register(part->adapt_dir(dir), reg);
}
void DirectionHub::move_to_register(const direction_t dir, reg32_t& reg) const
{
	DirectionPart* part = _Find_part(dir);
	if (part)
		part->move_to_register(part->adapt_dir(dir), reg);
}
void DirectionHub::move_to_register(const direction_t dir, reg64_t& reg) const
{
	DirectionPart* part = _Find_part(dir);
	if (part)
		part->move_to_register(part->adapt_dir(dir), reg);
}

void DirectionHub::move_from_register(const reg8_t& reg, const direction_t dir)
{
	DirectionPart* part = _Find_part(dir);
	if (part)
		part->move_from_register(reg, part->adapt_dir(dir));
}
void DirectionHub::move_from_register(const reg16_t& reg, const direction_t dir)
{
	DirectionPart* part = _Find_part(dir);
	if (part)
		part->move_from_register(reg, part->adapt_dir(dir));
}
void DirectionHub::move_from_register(const reg32_t& reg, const direction_t dir)
{
	DirectionPart* part = _Find_part(dir);
	if (part)
		part->move_from_register(reg, part->adapt_dir(dir));
}
void DirectionHub::move_from_register(const reg64_t& reg, const direction_t dir)
{
	DirectionPart* part = _Find_part(dir);
	if (part)
		part->move_from_register(reg, part->adapt_dir(dir));
}

DirectionPart* DirectionHub::_Find_part(const direction_t dir) const
{
	for (DirectionPart* part : _parts)
	{
		if (part->is_valid_direction(dir))
			return part;
	}
	return nullptr;
}
