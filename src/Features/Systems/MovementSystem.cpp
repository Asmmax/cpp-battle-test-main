#include "MovementSystem.hpp"

#include <Core/Infra/EventBus.hpp>
#include <Core/World/Unit.hpp>
#include <Core/World/World.hpp>
#include "Features/Events/MarchEnded.hpp"
#include "Features/Events/MarchStarted.hpp"
#include "Features/Events/UnitMoved.hpp"

#include <algorithm>

namespace sw::features
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

	core::Position MovementSystem::nextStep(const core::Position& from, const core::Position& to) const
	{
		return {from.x + stepToward(from.x, to.x), from.y + stepToward(from.y, to.y)};
	}

	bool MovementSystem::advance(core::Unit& unit, core::World& world)
	{
		const auto it = _targets.find(unit.unitId);
		if (it == _targets.end())
		{
			return false;
		}

		const core::Position& target = it->second;

		if (unit.pos == target)
		{
			finishMove(unit);
			return false;
		}

		const core::Position next = nextStep(unit.pos, target);

		const bool canMove = !isBlocked(next, world);
		if (canMove)
		{
			unit.pos = next;
			core::EventBus::publish<UnitMoved>({unit.unitId, next.x, next.y});
		}

		if (unit.pos == target)
		{
			finishMove(unit);
		}
		return canMove;
	}

	void MovementSystem::move(const core::Unit& unit, const core::Position& target)
	{
		_targets[unit.unitId] = target;
		core::EventBus::publish<MarchStarted>({unit.unitId, unit.pos.x, unit.pos.y, target.x, target.y});
	}

	void MovementSystem::finishMove(core::Unit& unit)
	{
		const auto it = _targets.find(unit.unitId);
		if (it == _targets.end())
		{
			return;
		}

		_targets.erase(it);

		core::EventBus::publish<MarchEnded>({unit.unitId, unit.pos.x, unit.pos.y});
	}

	bool MovementSystem::canMove(const core::Unit& unit, core::World& world)
	{
		const auto it = _targets.find(unit.unitId);
		if (it == _targets.end())
		{
			return false;
		}

		const core::Position& target = it->second;

		if (unit.pos == target)
		{
			return true;
		}

		return !isBlocked(nextStep(unit.pos, target), world);
	}

	void MovementSystem::setOccupying(const core::Unit& unit)
	{
		_occupyingUnits.insert(unit.unitId);
	}

	bool MovementSystem::isBlocked(const core::Position& pos, core::World& world) const
	{
		return !world.foreachUnit(
			[pos, this](const core::Unit& unit)
			{
				if (unit.pos != pos)
				{
					return true;
				}
				return !_occupyingUnits.contains(unit.unitId);
			});
	}
}
