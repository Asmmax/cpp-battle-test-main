#pragma once

#include "AActionGroup.hpp"

#include <memory>
#include <vector>

namespace sw::core
{
	class ActionSequence : public AActionGroup
	{
	public:
		template <typename... Args>
		ActionSequence(Args&&... nodes) :
				AActionGroup(std::forward<Args>(nodes), ...)
		{}

		virtual bool execute(Unit& self, World& world) override;
	};
}
