#include "March.hpp"

#include <Core/Systems/MovementSystem.hpp>
#include <Core/World/World.hpp>
#include <Core/Infra/ServiceLocator.hpp>

namespace sw::features
{
	std::function<void(core::World&)> createCommand(const io::March& data)
	{
		return [data = data](core::World& world)
		{
			core::ServiceLocator::get<core::MovementSystem>().move(
				world.getUnit(data.unitId), {data.targetX, data.targetY});
		};
	}
}
