#pragma once

#include <Core/Actions/AContextActionNode.hpp>
#include <memory>
#include <string>
#include <vector>

namespace sw::features
{
	class StatConsistFilterAction : public core::AContextActionNode<std::vector<uint32_t>>
	{
	private:
		std::string _statName{};

	public:
		StatConsistFilterAction(std::string statName);
		virtual bool execute(core::Unit& self, core::World& world, std::vector<uint32_t>& ctx) override;
	};
}
