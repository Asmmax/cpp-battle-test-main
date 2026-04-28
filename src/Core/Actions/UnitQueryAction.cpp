#include "UnitQueryAction.hpp"

#include "Core/Infra/ServiceLocator.hpp"
#include "Core/Providers/IStatProvider.hpp"
#include "Core/Systems/SpatialSystem.hpp"
#include "Core/World/Unit.hpp"

namespace sw::core
{
	UnitQueryAction::UnitQueryAction(
		std::unique_ptr<IStatProvider> minRange, std::unique_ptr<IStatProvider> maxRange, bool withFlying) :
			_minRange(std::move(minRange)),
			_maxRange(std::move(maxRange)),
			_withFlying(withFlying)
	{}

	UnitQueryAction::~UnitQueryAction() = default;

	bool UnitQueryAction::execute(Unit& self, World& world, std::vector<uint32_t>& ctx)
	{
		ctx = ServiceLocator::get<SpatialSystem>().findUnitsInRange(
			world, self.pos, _minRange->get(self), _maxRange->get(self), _withFlying);
		return !ctx.empty();
	}
}
