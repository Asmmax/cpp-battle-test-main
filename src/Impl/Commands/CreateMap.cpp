#include "CreateMap.hpp"

#include <Core/World/World.hpp>

namespace sw
{
	std::function<void(core::World&)> createCommand(const io::CreateMap& data)
	{
		return [data = data](core::World& world)
		{
			world.createMap(data.width, data.height);
		};
	}
}
