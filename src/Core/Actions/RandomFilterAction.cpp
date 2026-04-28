#include "RandomFilterAction.hpp"

#include "Core/Infra/ServiceLocator.hpp"
#include "Core/Systems/RandomGenerator.hpp"
#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"

namespace sw::core
{
	bool RandomFilterAction::execute(Unit& self, World& world, std::vector<uint32_t>& ctx)
	{
		uint32_t enemyId = ServiceLocator::get<RandomGenerator>().choose(ctx);
		uint32_t targetId = ctx[enemyId];
		ctx = std::vector<uint32_t>{targetId};
		return true;
	}
}
