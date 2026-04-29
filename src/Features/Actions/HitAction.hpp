#pragma once

#include <Core/Actions/AContextActionNode.hpp>
#include <memory>
#include <string>
#include <vector>

namespace sw::core
{
	class IStatProvider;
}

namespace sw::features
{
	class HitAction : public core::AContextActionNode<std::vector<uint32_t>>
	{
	private:
		std::string _id{};
		std::unique_ptr<core::IStatProvider> _health{};
		std::unique_ptr<core::IStatProvider> _damage{};

	public:
		HitAction(
			std::string id, std::unique_ptr<core::IStatProvider> health, std::unique_ptr<core::IStatProvider> damage);

		~HitAction();

	public:
		virtual bool execute(core::Unit& self, core::World& world, std::vector<uint32_t>& ctx) override;

	protected:
		void hit(core::World& world, core::Unit& attacker, core::Unit& target, uint32_t damage);
	};
}
