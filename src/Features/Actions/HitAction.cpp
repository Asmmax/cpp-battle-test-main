#include "HitAction.hpp"

#include "Features/Events/UnitAttacked.hpp"

#include <Core/Infra/EventBus.hpp>
#include <Core/Providers/IStatProvider.hpp>
#include <Core/World/Unit.hpp>
#include <Core/World/World.hpp>

namespace sw::features
{
	HitAction::HitAction(
		std::string id, std::unique_ptr<core::IStatProvider> health, std::unique_ptr<core::IStatProvider> damage) :
			_id(std::move(id)),
			_health(std::move(health)),
			_damage(std::move(damage))
	{}

	HitAction::~HitAction() = default;

	bool HitAction::execute(core::Unit& self, core::World& world, std::vector<uint32_t>& ctx)
	{
		if (ctx.empty())
		{
			return false;
		}
		for (auto unitId : ctx)
		{
			hit(world, self, world.getUnit(unitId), _damage->get(self));
		}
		return true;
	}

	void HitAction::hit(core::World& world, core::Unit& attacker, core::Unit& target, uint32_t damage)
	{
		uint32_t health = _health->get(target);
		if (health == 0)
		{
			return;
		}
		health = (damage >= health) ? 0 : health - damage;
		_health->set(target, health);

		core::EventBus::publish<UnitAttacked>({attacker.unitId, target.unitId, damage, health});
		if (health == 0)
		{
			world.removeUnit(target.unitId);
		}
	}
}
