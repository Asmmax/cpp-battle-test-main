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
		bool withFlying) :
			_id(std::move(id)),
			_health(std::move(health)),
			_damage(std::move(damage)),
			_minRange(std::move(minRange)),
			_maxRange(std::move(maxRange)),
			_withFlying(withFlying)
	{}

	DamageAction::~DamageAction() = default;

	bool DamageAction::execute(Unit& self, World& world)
	{
		std::vector<uint32_t> enemies = ServiceLocator::get<SpatialSystem>().findUnitsInRange(
			world, self.pos, _minRange->get(self), _maxRange->get(self), _withFlying);

		if (enemies.empty())
		{
			return false;
		}

		uint32_t enemyId = ServiceLocator::get<RandomGenerator>().choose(enemies);
		uint32_t targetId = enemies[enemyId];
		hit(world, self, world.getUnit(targetId), _damage->get(self));
		return true;
	}

	bool DamageAction::check(Unit& self, World& world) const
	{
		std::vector<uint32_t> enemies = ServiceLocator::get<SpatialSystem>().findUnitsInRange(
			world, self.pos, _minRange->get(self), _maxRange->get(self), _withFlying);

		return !enemies.empty();
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
