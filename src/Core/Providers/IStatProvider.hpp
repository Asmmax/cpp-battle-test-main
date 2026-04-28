#pragma once

#include <cstdint>

namespace sw::core
{
	class Unit;
	class World;

	class IStatProvider
	{
	public:
		virtual ~IStatProvider() = default;
		virtual uint32_t get(Unit& unit) const = 0;
		virtual void set(Unit& unit, uint32_t value) = 0;
	};
}
