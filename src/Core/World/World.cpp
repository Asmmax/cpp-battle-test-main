#include "World.hpp"

#include "IO/Events/MapCreated.hpp"
#include "IO/Events/UnitDied.hpp"
#include "IO/Events/UnitSpawned.hpp"
#include "Core/Actions/IActionNode.hpp"
#include "Core/Infra/EventBus.hpp"

#include <algorithm>
#include <assert.h>

namespace sw::core
{
	void World::createMap(uint32_t width, uint32_t height)
	{
		_map.emplace(width, height);
		EventBus::publish<sw::io::MapCreated>({width, height});
	}

	Bound* World::getMap()
	{
		return _map ? &_map.value() : nullptr;
	}

	void World::scheduleCommand(Command command)
	{
		_commandQueue.push_back(std::move(command));
	}

	bool World::canStep()
	{
		if (!_commandQueue.empty())
		{
			return true;
		}
		if (_units.size() <= 1)
		{
			return false;
		}
		return std::any_of(
			_units.begin(), _units.end(), [this](Unit& unit) { return unit.behaviour->check(unit, *this); });
	}

	int World::getStepNum()
	{
		return _stepCounter;
	}

	void World::step()
	{
		_stepCounter++;

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
			unit.behaviour->execute(unit, *this);
		}

		for (auto id : _pendingDeleteUnits)
		{
			std::erase_if(_units, [id](const Unit& unit) { return unit.unitId == id; });
		}
		_pendingDeleteUnits.clear();

		for (auto& command : _commandQueue)
		{
			command(*this);
		}
		_commandQueue.clear();
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
			EventBus::publish<sw::io::UnitSpawned>({unit.unitId, unit.unitType, unit.pos.x, unit.pos.y});
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

	std::vector<uint32_t> World::getUnitsByPos(const Position& pos)
	{
		std::vector<uint32_t> result;
		for (const auto& unit : _units)
		{
			if (unit.pos == pos)
			{
				result.push_back(unit.unitId);
			}
		}
		return result;
	}

	void World::removeUnit(uint32_t id)
	{
		_pendingDeleteUnits.push_back(id);
		EventBus::publish<sw::io::UnitDied>({id});
	}
}
