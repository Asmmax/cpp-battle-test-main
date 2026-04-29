#include "MoveAction.hpp"

#include "Features/Systems/MovementSystem.hpp"

#include <Core/World/Unit.hpp>
#include <Core/World/World.hpp>

namespace sw::features
{
	bool MoveAction::execute(core::Unit& self, core::World& world)
	{
		return MovementSystem::getInstance().advance(self, world);
	}
}
