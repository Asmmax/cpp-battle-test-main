#include "MoveAction.hpp"

#include "Core/Infra/ServiceLocator.hpp"
#include "Core/Systems/MovementSystem.hpp"
#include "Core/World/Unit.hpp"
#include "Core/World/World.hpp"

namespace sw::core
{
	MoveAction::MoveAction(uint32_t speed) :
			_speed(speed)
	{}

	bool MoveAction::execute(Unit& self, World& world)
	{
		bool hasStep = false;
		for (int i = 0; i < _speed; i++)
		{
			if (ServiceLocator::get<MovementSystem>().advance(self, world))
			{
				hasStep = true;
			}
			else
			{
				break;
			}
		}
		return hasStep;
	}
}
