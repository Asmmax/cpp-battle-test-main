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
}
