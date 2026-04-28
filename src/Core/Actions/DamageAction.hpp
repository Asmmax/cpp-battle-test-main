#pragma once

#include "IActionNode.hpp"

#include <vector>
#include <unordered_set>
#include <string>
#include <memory>

namespace sw::core
{
	class IStatProvider;

	class DamageAction : public IActionNode
	{
	private:
		std::string _id;
		std::unique_ptr<IStatProvider> _health;
		std::unique_ptr<IStatProvider> _damage;
		std::unique_ptr<IStatProvider> _minRange;
		std::unique_ptr<IStatProvider> _maxRange;
		bool _withFlying;

	public:
		DamageAction(
			std::string id,
			std::unique_ptr<IStatProvider> health,
			std::unique_ptr<IStatProvider> damage,
			std::unique_ptr<IStatProvider> minRange,
			std::unique_ptr<IStatProvider> maxRange,
			bool withFlying);

		~DamageAction();

	public:
		virtual bool execute(Unit& self, World& world) override;
		virtual bool check(Unit& self, World& world) const override;

	protected:
		void prepare(Unit& self, World& world);
		bool canAct(Unit& self, World& world) const;
		void act(Unit& self, World& world);

		void hit(World& world, Unit& attacker, Unit& target, uint32_t damage);
	};
}
