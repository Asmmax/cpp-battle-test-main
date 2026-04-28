#pragma once

#include "AContextActionNode.hpp"

#include <vector>
#include <string>
#include <memory>

namespace sw::core
{
	class IStatProvider;

	class HitAction : public AContextActionNode<std::vector<uint32_t>>
	{
	private:
		std::string _id;
		std::unique_ptr<IStatProvider> _health;
		std::unique_ptr<IStatProvider> _damage;

	public:
		HitAction(
			std::string id,
			std::unique_ptr<IStatProvider> health,
			std::unique_ptr<IStatProvider> damage);

		~HitAction();

	public:
		virtual bool execute(Unit& self, World& world, std::vector<uint32_t>& ctx) override;

	protected:
		void hit(World& world, Unit& attacker, Unit& target, uint32_t damage);
	};
}
