#pragma once

#include <Core/Actions/IActionNode.hpp>
#include <memory>
#include <optional>

namespace sw::features
{
	class DelayedAction : public core::IActionNode
	{
	private:
		std::unique_ptr<core::IActionNode> _next{};
		bool _prevState{};

	public:
		DelayedAction(std::unique_ptr<core::IActionNode> next, bool startState = false);

		virtual bool execute(core::Unit& self, core::World& world) override;
	};
}
