#include "MoveAction.hpp"

#include "Core/Systems/MovementSystem.hpp"
#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"
#include "Core/Infra/ServiceLocator.hpp"

namespace sw::core
{
	MoveAction::MoveAction(uint32_t speed) :
			_speed(speed)
	{}

	void MoveAction::operator()(Unit& self, World& world)
	{
		for (uint32_t i = 0; i < _speed; i++)
		{
			ServiceLocator::get<MovementSystem>().advance(self, world);
		}
	}

	bool MoveAction::isValid(Unit& self, World& world) const
	{
		return ServiceLocator::get<MovementSystem>().isMoving(self, world);
	}
}
