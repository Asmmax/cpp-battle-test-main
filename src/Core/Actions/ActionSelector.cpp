#include "ActionSelector.hpp"

#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"

namespace sw::core
{
	bool ActionSelector::execute(Unit& self, World& world)
	{
		for (const auto& child : _children)
		{
			if (child->execute(self, world))
			{
				return true;
			}
		}
		return false;
	}

	bool ActionSelector::check(Unit& self, World& world) const
	{
		for (const auto& child : _children)
		{
			if (child->check(self, world))
			{
				return true;
			}
		}
		return false;
	}
}
