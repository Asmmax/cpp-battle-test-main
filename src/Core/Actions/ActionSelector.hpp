#pragma once

#include "IActionNode.hpp"

#include <memory>
#include <vector>

namespace sw::core
{
	class ActionSelector : public IActionNode
	{
	private:
		using IActionNodePtr = std::unique_ptr<IActionNode>;
		std::vector<IActionNodePtr> _children{};

	public:
		template <typename... Args>
		ActionSelector(Args&&... nodes)
		{
			(_children.push_back(std::forward<Args>(nodes)), ...);
		}

		virtual bool execute(Unit& self, World& world) override;
	};
}
