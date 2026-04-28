#include "MovementSystem.hpp"

#include "Core/Infra/EventBus.hpp"
#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"
#include "IO/Events/MarchEnded.hpp"
#include "IO/Events/MarchStarted.hpp"
#include "IO/Events/UnitMoved.hpp"

#include <algorithm>

namespace sw::core
{
	void MovementSystem::advance(Unit& unit, World& world)
	{
		auto it = _targets.find(unit.unitId);
		if (it == _targets.end())
		{
			return;
		}

		const Position target = it->second;

		if (unit.pos == target)
		{
			_targets.erase(it);
			EventBus::publish<sw::io::MarchEnded>({unit.unitId, unit.pos.x, unit.pos.y});
			return;
		}

		Position next = unit.pos;

		if (target.x > unit.pos.x)
		{
			next.x++;
		}
		else if (target.x < unit.pos.x)
		{
			next.x--;
		}

		if (target.y > unit.pos.y)
		{
			next.y++;
		}
		else if (target.y < unit.pos.y)
		{
			next.y--;
		}

		std::vector<uint32_t> units = world.getUnitsByPos(next);
		const bool hasOccupy = std::any_of(
			units.begin(), units.end(), [this](uint32_t unitId) { return _occupyingUnits.contains(unitId); });
		if (!hasOccupy)
		{
			unit.pos = next;
			EventBus::publish<sw::io::UnitMoved>({unit.unitId, next.x, next.y});
		}

		if (unit.pos == target)
		{
			_targets.erase(it);
			EventBus::publish<sw::io::MarchEnded>({unit.unitId, unit.pos.x, unit.pos.y});
		}
	}

	void MovementSystem::move(const Unit& unit, const Position& target)
	{
		_targets[unit.unitId] = target;
		EventBus::publish<sw::io::MarchStarted>({unit.unitId, unit.pos.x, unit.pos.y, target.x, target.y});
	}

	bool MovementSystem::isMoving(const Unit& unit, World& world)
	{
		auto it = _targets.find(unit.unitId);
		if (it == _targets.end())
		{
			return false;
		}

		const Position target = it->second;

		if (unit.pos == target)
		{
			return true;
		}

		Position next = unit.pos;

		if (target.x > unit.pos.x)
		{
			next.x++;
		}
		else if (target.x < unit.pos.x)
		{
			next.x--;
		}

		if (target.y > unit.pos.y)
		{
			next.y++;
		}
		else if (target.y < unit.pos.y)
		{
			next.y--;
		}

		std::vector<uint32_t> units = world.getUnitsByPos(next);
		const bool hasOccupy = std::any_of(
			units.begin(), units.end(), [this](uint32_t unitId) { return _occupyingUnits.contains(unitId); });
		return !hasOccupy;
	}

	void MovementSystem::setOccupying(const Unit& unit)
	{
		_occupyingUnits.insert(unit.unitId);
	}
}
