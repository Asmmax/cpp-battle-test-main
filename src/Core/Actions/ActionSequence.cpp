#include "ActionSequence.hpp"

#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"

namespace sw::core
{
	bool ActionSequence::execute(Unit& self, World& world)
	{
		for (const auto& child : _children)
		{
			if (!child->execute(self, world))
			{
				return false;
			}
		}
		return true;
	}
}
