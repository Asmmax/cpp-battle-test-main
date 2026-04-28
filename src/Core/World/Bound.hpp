#pragma once

#include "Position.hpp"

namespace sw::core
{
	struct Bound
	{
		uint32_t width{};
		uint32_t height{};

		bool IsInside(const Position& pos)
		{
			return pos.x < width && pos.y < height;
		}
	};
}
