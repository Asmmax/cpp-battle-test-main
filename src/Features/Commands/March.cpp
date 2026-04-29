#include "March.hpp"

#include "Features/Systems/MovementSystem.hpp"

#include <Core/World/World.hpp>

namespace sw::features
{
	std::function<void(core::World&)> createCommand(const March& data)
	{
		return [data = data](core::World& world)
		{
			MovementSystem::getInstance().move(world.getUnit(data.unitId), {data.targetX, data.targetY});
		};
	}
}
