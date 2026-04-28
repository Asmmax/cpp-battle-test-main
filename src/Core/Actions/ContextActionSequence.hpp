#pragma once

#include "AContextActionNode.hpp"

#include <memory>
#include <vector>

namespace sw::core
{
	template <typename TContext>
	class ContextActionSequence : public AContextActionNode<TContext>
	{
	private:
		using AContextActionNodePtr = std::unique_ptr<AContextActionNode<TContext>>;
		std::vector<AContextActionNodePtr> _children;

	public:
		template <typename... Args>
		ContextActionSequence(Args&&... nodes)
		{
			(_children.push_back(std::forward<Args>(nodes)), ...);
		}

		virtual bool execute(Unit& self, World& world, TContext& ctx) override
		{
			for (const auto& child : _children)
			{
				if (!child->execute(self, world, ctx))
				{
					return false;
				}
			}
			return true;
		}
	};
}
