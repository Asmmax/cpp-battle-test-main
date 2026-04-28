#pragma once
#include "IActionNode.hpp"

namespace sw::core
{
	template <typename TContext>
	class AContextActionNode : public IActionNode
	{
	public:
		virtual bool execute(Unit& self, World& world, TContext& ctx) = 0;

		virtual bool execute(Unit& self, World& world) final
		{
			TContext ctx;
			return execute(self, world, ctx);
		}
	};
}
