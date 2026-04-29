#pragma once

#include "AContextActionNode.hpp"
#include "Core/Systems/RandomGenerator.hpp"

#include <memory>
#include <vector>

namespace sw::core
{
	template <typename TElement>
	class RandomFilterAction : public AContextActionNode<std::vector<TElement>>
	{
	public:
		virtual bool execute(Unit& self, World& world, std::vector<TElement>& ctx) override
		{
			if (ctx.empty())
			{
				return false;
			}

			uint32_t idx = RandomGenerator::getInstance().choose<TElement>(ctx);
			const auto& target = ctx[idx];
			ctx = std::vector<TElement>{target};
			return true;
		}
	};
}
