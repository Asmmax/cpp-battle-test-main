#pragma once

#include <cstdint>

namespace sw::core
{
	struct Position
	{
		uint32_t x{};
		uint32_t y{};

		bool operator==(const Position& other) const
		{
			return x == other.x && y == other.y;
		}
	};
}
