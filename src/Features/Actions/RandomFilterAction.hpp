#pragma once

#include <Core/Actions/AContextActionNode.hpp>
#include <Core/Systems/RandomGenerator.hpp>
#include <memory>
#include <vector>

namespace sw::features
{
	template <typename TElement>
	class RandomFilterAction : public core::AContextActionNode<std::vector<TElement>>
	{
	public:
		virtual bool execute(core::Unit& self, core::World& world, std::vector<TElement>& ctx) override
		{
			if (ctx.empty())
			{
				return false;
			}

			uint32_t idx = core::RandomGenerator::getInstance().choose<TElement>(ctx);
			const auto& target = ctx[idx];
			ctx = std::vector<TElement>{target};
			return true;
		}
	};
}
