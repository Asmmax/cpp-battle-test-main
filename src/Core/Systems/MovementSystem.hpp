#pragma once

#include "Core/World/Position.hpp"

#include <unordered_map>
#include <unordered_set>

namespace sw::core
{
	class Unit;
	class World;

	class MovementSystem
	{
	private:
		std::unordered_map<uint32_t, Position> _targets;
		std::unordered_set<uint32_t> _occupyingUnits;

	public:
		void advance(Unit& unit, World& world);
		void move(const Unit& unit, const Position& target);
		bool isMoving(const Unit& unit, World& world);

		void setOccupying(const Unit& unit);
	};
}
