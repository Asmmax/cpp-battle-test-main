#include "DamageAction.hpp"

#include "IO/Events/UnitAttacked.hpp"
#include "Core/Providers/IStatProvider.hpp"
#include "Core/Systems/RandomGenerator.hpp"
#include "Core/Systems/SpatialSystem.hpp"
#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"
#include "Core/Infra/EventBus.hpp"
#include "Core/Infra/ServiceLocator.hpp"

namespace sw::core
{
	DamageAction::DamageAction(
		std::string id,
		std::unique_ptr<IStatProvider> health,
		std::unique_ptr<IStatProvider> damage,
		std::unique_ptr<IStatProvider> minRange,
		std::unique_ptr<IStatProvider> maxRange,
		bool withFlying,
		std::shared_ptr<IAction> next) :
			AAction(id, next),
			_health(std::move(health)),
			_damage(std::move(damage)),
			_minRange(std::move(minRange)),
			_maxRange(std::move(maxRange)),
			_withFlying(withFlying)
	{}

	DamageAction::~DamageAction() = default;

	void DamageAction::prepare(Unit& self, World& world)
	{
		_enemies = ServiceLocator::get<SpatialSystem>().findUnitsInRange(
			world, self.pos, _minRange->get(self), _maxRange->get(self), _withFlying);
	}

	bool DamageAction::canAct(Unit& self, World& world) const
	{
		return !_enemies.empty();
	}

	void DamageAction::act(Unit& self, World& world)
	{
		uint32_t enemyId = ServiceLocator::get<RandomGenerator>().choose(_enemies);
		uint32_t targetId = _enemies[enemyId];
		hit(world, self, world.getUnit(targetId), _damage->get(self));
		return;
	}

	void DamageAction::hit(World& world, Unit& attacker, Unit& target, uint32_t damage)
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
