#pragma once

#include "Core/Infra/Singleton.hpp"
#include "Core/World/Position.hpp"

#include <unordered_map>
#include <unordered_set>

namespace sw::core
{
	class Unit;
	class World;

	class MovementSystem : public Singleton<MovementSystem>
	{
	private:
		std::unordered_map<uint32_t, Position> _targets{};
		std::unordered_set<uint32_t> _occupyingUnits{};

	public:
		Position nextStep(const Position& from, const Position& to) const;

		bool advance(Unit& unit, World& world);
		void move(const Unit& unit, const Position& target);
		void finishMove(Unit& unit);
		bool canMove(const Unit& unit, World& world);

		void setOccupying(const Unit& unit);
		bool isBlocked(const Position& pos, World& world) const;
	};
}
