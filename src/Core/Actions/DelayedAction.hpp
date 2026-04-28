#pragma once

#include "IActionNode.hpp"

#include <memory>
#include <optional>

namespace sw::core
{
	class DelayedAction : public IActionNode
	{
	private:
		std::unique_ptr<IActionNode> _next{};
		bool _prevState{};

	public:
		DelayedAction(std::unique_ptr<IActionNode> next, bool startState = false);

		virtual bool execute(Unit& self, World& world) override;
	};
}
