#pragma once

#include "Unit.hpp"
#include "Bound.hpp"

#include <optional>
#include <functional>

namespace sw::core
{
	class World
	{
	public:
		using Command = std::function<void(World&)>;

	private:
		int _stepCounter = 0;
		std::vector<Command> _commandQueue;
		std::vector<Unit> _units;
		std::vector<uint32_t> _pendingDeleteUnits;
		std::optional<Bound> _map;

	public:
		void createMap(uint32_t width, uint32_t height);
		Bound* getMap();

		void scheduleCommand(Command command);
		bool canStep();
		int getStepNum();
		void step();

		void addUnit(const Unit& unit);
		Unit* tryGetUnit(uint32_t id);
		Unit& getUnit(uint32_t id);
		std::vector<uint32_t> getUnitsByPos(const Position& pos);
		void removeUnit(uint32_t id);
	};
}
