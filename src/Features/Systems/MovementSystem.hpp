#pragma once

#include <Core/Infra/Singleton.hpp>
#include <Core/World/Position.hpp>

#include <unordered_map>
#include <unordered_set>

namespace sw::core
{
	class Unit;
	class World;
}

namespace sw::features
{
	class MovementSystem : public core::Singleton<MovementSystem>
	{
	private:
		std::unordered_map<uint32_t, core::Position> _targets{};
		std::unordered_set<uint32_t> _occupyingUnits{};

	public:
		core::Position nextStep(const core::Position& from, const core::Position& to) const;

		bool advance(core::Unit& unit, core::World& world);
		void move(const core::Unit& unit, const core::Position& target);
		void finishMove(core::Unit& unit);
		bool canMove(const core::Unit& unit, core::World& world);

		void setOccupying(const core::Unit& unit);
		bool isBlocked(const core::Position& pos, core::World& world) const;
	};
}
