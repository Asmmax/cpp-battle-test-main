#pragma once

#include <cstdint>

namespace sw::core
{
	struct Position
	{
		uint32_t x{0};
		uint32_t y{0};

		bool operator==(const Position& other) const
		{
			return x == other.x && y == other.y;
		}
	};
}
