#include "StatConsistFilterAction.hpp"

#include "Core/Infra/ServiceLocator.hpp"
#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"

namespace sw::core
{
	StatConsistFilterAction::StatConsistFilterAction(std::string statName) :
			_statName(std::move(statName))
	{}

	bool StatConsistFilterAction::execute(Unit& self, World& world, std::vector<uint32_t>& ctx)
	{
		std::vector<uint32_t> result;

		for (auto unitId : ctx)
		{
			Unit* unit = world.tryGetUnit(unitId);
			if (!unit)
			{
				continue;
			}

			if (unit->stats.contains(_statName))
			{
				result.push_back(unitId);
			}
		}
		ctx = std::move(result);

		return !ctx.empty();
	}
}
