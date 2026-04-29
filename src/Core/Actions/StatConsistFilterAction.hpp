#pragma once

#include "AContextActionNode.hpp"

#include <memory>
#include <string>
#include <vector>

namespace sw::core
{
	class StatConsistFilterAction : public AContextActionNode<std::vector<uint32_t>>
	{
	private:
		std::string _statName{};

	public:
		StatConsistFilterAction(std::string statName);
		virtual bool execute(Unit& self, World& world, std::vector<uint32_t>& ctx) override;
	};
}
