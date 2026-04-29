#pragma once

#include <Core/Actions/IActionNode.hpp>

#include <memory>

namespace sw::features
{
	class TriggerAction : public core::IActionNode
	{
	private:
		std::unique_ptr<core::IActionNode> _next{};
		bool _state{};

	public:
		TriggerAction(std::unique_ptr<core::IActionNode> next);

		virtual bool execute(core::Unit& self, core::World& world) override;
	};
}
