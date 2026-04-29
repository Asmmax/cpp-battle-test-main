#include "UnitQueryAction.hpp"

#include "Features/Systems/SpatialSystem.hpp"

#include <Core/Providers/IStatProvider.hpp>
#include <Core/World/Unit.hpp>

namespace sw::features
{
	UnitQueryAction::UnitQueryAction(
		std::unique_ptr<core::IStatProvider> minRange, std::unique_ptr<core::IStatProvider> maxRange, bool withFlying) :
			_minRange(std::move(minRange)),
			_maxRange(std::move(maxRange)),
			_withFlying(withFlying)
	{}

	UnitQueryAction::~UnitQueryAction() = default;

	bool UnitQueryAction::execute(core::Unit& self, core::World& world, std::vector<uint32_t>& ctx)
	{
		ctx = SpatialSystem::getInstance().findUnitsInRange(
			world, self.pos, _minRange->get(self), _maxRange->get(self), _withFlying);
		return !ctx.empty();
	}
}
