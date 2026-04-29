#include "Simulation.hpp"

#include "Core/Actions/IActionNode.hpp"
#include "Unit.hpp"
#include "World.hpp"

#include <algorithm>
#include <assert.h>

namespace sw::core
{
	void Simulation::scheduleCommand(Command command)
	{
		_commandQueue.push_back(std::move(command));
	}

	int Simulation::getStepNum()
	{
		return _stepCounter;
	}

	bool Simulation::step(World& world)
	{
		_stepCounter++;

		uint32_t executedUnitsCount = 0;

		world.foreachUnit(
			[&world, &executedUnitsCount](Unit& unit)
			{
				if (!unit.behaviour)
				{
					return true;
				}
				if (unit.behaviour->execute(unit, world))
				{
					executedUnitsCount++;
				}
				return true;
			});

		world.cleanupUnits();

		if (_commandQueue.empty() && executedUnitsCount <= 1)
		{
			return false;
		}

		for (auto& command : _commandQueue)
		{
			command(world);
		}
		_commandQueue.clear();

		return true;
	}

	void Simulation::run(World& world)
	{
		while (step(world))
		{
		}
	}
}
