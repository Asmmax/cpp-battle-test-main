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
	static int stepToward(int from, int to)
	{
		if (to > from)
		{
			return 1;
		}
		if (to < from)
		{
			return -1;
		}
		return 0;
	}

	Position MovementSystem::nextStep(const Position& from, const Position& to) const
	{
		return {from.x + stepToward(from.x, to.x), from.y + stepToward(from.y, to.y)};
	}

	void MovementSystem::advance(Unit& unit, World& world)
	{
		const auto it = _targets.find(unit.unitId);
		if (it == _targets.end())
		{
			return;
		}

		const Position& target = it->second;

		if (unit.pos == target)
		{
			finishMove(unit);
			return;
		}

		const Position next = nextStep(unit.pos, target);

		if (!isBlocked(next, world))
		{
			unit.pos = next;
			EventBus::publish<sw::io::UnitMoved>({unit.unitId, next.x, next.y});
		}

		if (unit.pos == target)
		{
			finishMove(unit);
		}
	}

	void MovementSystem::move(const Unit& unit, const Position& target)
	{
		_targets[unit.unitId] = target;
		EventBus::publish<sw::io::MarchStarted>({unit.unitId, unit.pos.x, unit.pos.y, target.x, target.y});
	}

	void MovementSystem::finishMove(Unit& unit)
	{
		const auto it = _targets.find(unit.unitId);
		if (it == _targets.end())
		{
			return;
		}

		_targets.erase(it);

		EventBus::publish<sw::io::MarchEnded>({unit.unitId, unit.pos.x, unit.pos.y});
	}

	bool MovementSystem::isMoving(const Unit& unit, World& world)
	{
		const auto it = _targets.find(unit.unitId);
		if (it == _targets.end())
		{
			return false;
		}

		const Position& target = it->second;

		if (unit.pos == target)
		{
			return true;
		}

		return !isBlocked(nextStep(unit.pos, target), world);
	}

	void MovementSystem::setOccupying(const Unit& unit)
	{
		_occupyingUnits.insert(unit.unitId);
	}

	bool MovementSystem::isBlocked(const Position& pos, World& world) const
	{
		const auto units = world.getUnitsByPos(pos);

		return std::any_of(units.begin(), units.end(), [this](uint32_t id) { return _occupyingUnits.contains(id); });
	}
}
