#pragma once

#include "IActionNode.hpp"

#include <memory>

namespace sw::core
{
	class TriggerAction : public IActionNode
	{
	private:
		std::unique_ptr<IActionNode> _next{};
		bool _state{};

	public:
		TriggerAction(std::unique_ptr<IActionNode> next);

		virtual bool execute(Unit& self, World& world) override;
	};
}
