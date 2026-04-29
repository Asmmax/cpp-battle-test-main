#include "MoveAction.hpp"

#include "Core/Infra/ServiceLocator.hpp"
#include "Core/Systems/MovementSystem.hpp"
#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"

namespace sw::core
{
	bool MoveAction::execute(Unit& self, World& world)
	{
		return ServiceLocator::get<MovementSystem>().advance(self, world);
	}
}
