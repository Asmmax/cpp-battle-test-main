#pragma once

#include "Bound.hpp"
#include "Unit.hpp"

#include <functional>
#include <optional>

namespace sw::core
{
	class World
	{
	private:
		std::vector<Unit> _units{};
		std::vector<uint32_t> _pendingDeleteUnits{};
		std::optional<Bound> _map{};

	public:
		void createMap(uint32_t width, uint32_t height);
		Bound* getMap();

		void addUnit(const Unit& unit);
		Unit* tryGetUnit(uint32_t id);
		Unit& getUnit(uint32_t id);
		bool foreachUnit(std::function<bool(Unit&)> visitor);
		void removeUnit(uint32_t id);
		void cleanupUnits();
	};
}
