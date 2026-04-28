#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstdint>

namespace sw::core
{
	class Position;
	class Unit;
	class World;

	class SpatialSystem
	{
	private:
		std::unordered_map<uint32_t, uint32_t> _distOffset;
		std::unordered_set<uint32_t> _flyingUnits;

	public:
		std::vector<uint32_t> findUnitsInRange(
			World& world, const Position& origin, uint32_t minDist, uint32_t maxDist, bool withFlying = false);

		void setFlying(const Unit& unit);
		void setDistOffset(const Unit& unit, uint32_t offset);
	};
}
