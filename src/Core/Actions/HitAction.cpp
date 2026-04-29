#include "HitAction.hpp"

#include "Core/Infra/EventBus.hpp"
#include "Core/Providers/IStatProvider.hpp"
#include "Core/Systems/RandomGenerator.hpp"
#include "Core/Systems/SpatialSystem.hpp"
#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"
#include "IO/Events/UnitAttacked.hpp"

namespace sw::core
{
	HitAction::HitAction(std::string id, std::unique_ptr<IStatProvider> health, std::unique_ptr<IStatProvider> damage) :
			_id(std::move(id)),
			_health(std::move(health)),
			_damage(std::move(damage))
	{}

	HitAction::~HitAction() = default;

	bool HitAction::execute(Unit& self, World& world, std::vector<uint32_t>& ctx)
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

	void HitAction::hit(World& world, Unit& attacker, Unit& target, uint32_t damage)
	{
		uint32_t health = _health->get(target);
		if (health == 0)
		{
			return;
		}
		health = (damage >= health) ? 0 : health - damage;
		_health->set(target, health);

		EventBus::publish<sw::io::UnitAttacked>({attacker.unitId, target.unitId, damage, health});
		if (health == 0)
		{
			world.removeUnit(target.unitId);
		}
	}
}
