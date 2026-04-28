#pragma once

#include "IActionNode.hpp"

#include <memory>
#include <vector>

namespace sw::core
{
	class AActionGroup : public IActionNode
	{
	protected:
		using IActionNodePtr = std::unique_ptr<IActionNode>;
		std::vector<IActionNodePtr> _children{};

	public:
		template <typename... Args>
		AActionGroup(Args&&... nodes)
		{
			(_children.push_back(std::forward<Args>(nodes)), ...);
		}
	};
}
