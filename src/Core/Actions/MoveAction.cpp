#include "MoveAction.hpp"

#include "Core/Systems/MovementSystem.hpp"
#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"

namespace sw::core
{
	bool MoveAction::execute(Unit& self, World& world)
	{
		return MovementSystem::getInstance().advance(self, world);
	}
}
