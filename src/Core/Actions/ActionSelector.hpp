#pragma once

#include "AActionGroup.hpp"

namespace sw::core
{
	class ActionSelector : public AActionGroup
	{
	public:
		template <typename... Args>
		ActionSelector(Args&&... nodes) :
				AActionGroup(std::forward<Args>(nodes)...)
		{}

		virtual bool execute(Unit& self, World& world) override;
	};
}
