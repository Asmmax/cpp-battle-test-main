#include "UnitStatProvider.hpp"

#include "Core/World/Unit.hpp"

namespace sw::core
{
	UnitStatProvider::UnitStatProvider(std::string statName) :
			_statName(statName)
	{}

	uint32_t UnitStatProvider::get(Unit& unit) const
	{
		const auto foundIt = unit.stats.find(_statName);
		if (foundIt != unit.stats.end())
		{
			return foundIt->second;
		}
		return 0;
	}

	void UnitStatProvider::set(Unit& unit, uint32_t value)
	{
		const auto foundIt = unit.stats.find(_statName);
		if (foundIt != unit.stats.end())
		{
			foundIt->second = value;
		}
	}
}
