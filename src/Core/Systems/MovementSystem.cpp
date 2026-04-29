#include "MovementSystem.hpp"

#include "Core/Infra/EventBus.hpp"
#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"
#include "Core/Events/MarchEnded.hpp"
#include "Core/Events/MarchStarted.hpp"
#include "Core/Events/UnitMoved.hpp"

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

	bool MovementSystem::advance(Unit& unit, World& world)
	{
		const auto it = _targets.find(unit.unitId);
		if (it == _targets.end())
		{
			return false;
		}

		const Position& target = it->second;

		if (unit.pos == target)
		{
			finishMove(unit);
			return false;
		}

		const Position next = nextStep(unit.pos, target);

		const bool canMove = !isBlocked(next, world);
		if (canMove)
		{
			unit.pos = next;
			EventBus::publish<UnitMoved>({unit.unitId, next.x, next.y});
		}

		if (unit.pos == target)
		{
			finishMove(unit);
		}
		return canMove;
	}

	void MovementSystem::move(const Unit& unit, const Position& target)
	{
		_targets[unit.unitId] = target;
		EventBus::publish<MarchStarted>({unit.unitId, unit.pos.x, unit.pos.y, target.x, target.y});
	}

	void MovementSystem::finishMove(Unit& unit)
	{
		const auto it = _targets.find(unit.unitId);
		if (it == _targets.end())
		{
			return;
		}

		_targets.erase(it);

		EventBus::publish<MarchEnded>({unit.unitId, unit.pos.x, unit.pos.y});
	}

	bool MovementSystem::canMove(const Unit& unit, World& world)
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
		return !world.foreachUnit(
			[pos, this](const Unit& unit)
			{
				if (unit.pos != pos)
				{
					return true;
				}
				return !_occupyingUnits.contains(unit.unitId);
			});
	}
}
