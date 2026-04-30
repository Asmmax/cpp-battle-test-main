#include "March.hpp"

#include <Core/World/World.hpp>
#include <Features/Systems/MovementSystem.hpp>

namespace sw
{
	std::function<void(core::World&)> createCommand(const io::March& data)
	{
		return [data = data](core::World& world)
		{
			features::MovementSystem::getInstance().move(world.getUnit(data.unitId), {data.targetX, data.targetY});
		};
	}
}
