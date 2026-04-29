#pragma once

#include "IActionNode.hpp"

#include <memory>
#include <optional>

namespace sw::core
{
	class ActionRepeater : public IActionNode
	{
	private:
		std::unique_ptr<IActionNode> _next{};
		uint32_t _count{};

	public:
		ActionRepeater(std::unique_ptr<IActionNode> next, uint32_t count);

		virtual bool execute(Unit& self, World& world) override;
	};
}
