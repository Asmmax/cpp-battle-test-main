#include "World.hpp"

#include "Core/Actions/IActionNode.hpp"
#include "Core/Infra/EventBus.hpp"
#include "Core/Events/MapCreated.hpp"
#include "Core/Events/UnitDied.hpp"
#include "Core/Events/UnitSpawned.hpp"

#include <algorithm>
#include <assert.h>

namespace sw::core
{
	void World::createMap(uint32_t width, uint32_t height)
	{
		_map.emplace(width, height);
		EventBus::publish<MapCreated>({width, height});
	}

	Bound* World::getMap()
	{
		return _map ? &_map.value() : nullptr;
	}

	void World::scheduleCommand(Command command)
	{
		_commandQueue.push_back(std::move(command));
	}

	int World::getStepNum()
	{
		return _stepCounter;
	}

	bool World::step()
	{
		_stepCounter++;

		uint32_t executedUnitsCount = 0;
		for (Unit& unit : _units)
		{
			if (std::find(_pendingDeleteUnits.begin(), _pendingDeleteUnits.end(), unit.unitId)
				!= _pendingDeleteUnits.end())
			{
				continue;
			}
			if (!unit.behaviour)
			{
				continue;
			}
			if (unit.behaviour->execute(unit, *this))
			{
				executedUnitsCount++;
			}
		}

		for (auto id : _pendingDeleteUnits)
		{
			std::erase_if(_units, [id](const Unit& unit) { return unit.unitId == id; });
		}
		_pendingDeleteUnits.clear();

		if (_commandQueue.empty() && executedUnitsCount <= 1)
		{
			return false;
		}

		for (auto& command : _commandQueue)
		{
			command(*this);
		}
		_commandQueue.clear();

		return true;
	}

	void World::run()
	{
		while (step())
		{
		}
	}

	void World::addUnit(const Unit& unit)
	{
		assert(tryGetUnit(unit.unitId) == nullptr && "Unit with same unit id already exists");
		if (!_map)
		{
			return;
		}
		if (_map->IsInside(unit.pos))
		{
			_units.push_back(unit);
			EventBus::publish<UnitSpawned>({unit.unitId, unit.unitType, unit.pos.x, unit.pos.y});
		}
	}

	Unit* World::tryGetUnit(uint32_t id)
	{
		const auto foundIt
			= std::find_if(_units.begin(), _units.end(), [id](const Unit& unit) { return unit.unitId == id; });
		if (foundIt == _units.end())
		{
			return nullptr;
		}
		return &(*foundIt);
	}

	Unit& World::getUnit(uint32_t id)
	{
		Unit* unitPtr = tryGetUnit(id);
		assert(unitPtr && "Unit does not exist in world");
		return *unitPtr;
	}

	bool World::foreachUnit(std::function<bool(const Unit&)> visitor) const
	{
		for (const auto& unit : _units)
		{
			if (!visitor(unit))
			{
				return false;
			}
		}
		return true;
	}

	void World::removeUnit(uint32_t id)
	{
		_pendingDeleteUnits.push_back(id);
		EventBus::publish<UnitDied>({id});
	}
}
