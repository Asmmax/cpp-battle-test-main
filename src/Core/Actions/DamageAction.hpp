#pragma once

#include "AAction.hpp"

#include <vector>
#include <unordered_set>
#include <memory>

namespace sw::core
{
	class IStatProvider;

	class DamageAction : public AAction
	{
	private:
		std::unique_ptr<IStatProvider> _health;
		std::unique_ptr<IStatProvider> _damage;
		std::unique_ptr<IStatProvider> _minRange;
		std::unique_ptr<IStatProvider> _maxRange;
		std::vector<uint32_t> _enemies;
		bool _withFlying;

	public:
		DamageAction(
			std::string id,
			std::unique_ptr<IStatProvider> health,
			std::unique_ptr<IStatProvider> damage,
			std::unique_ptr<IStatProvider> minRange,
			std::unique_ptr<IStatProvider> maxRange,
			bool withFlying,
			std::shared_ptr<IAction> next);

		~DamageAction();

	protected:
		virtual void prepare(Unit& self, World& world) override;
		virtual bool canAct(Unit& self, World& world) const override;
		virtual void act(Unit& self, World& world) override;

		void hit(World& world, Unit& attacker, Unit& target, uint32_t damage);
	};
}
