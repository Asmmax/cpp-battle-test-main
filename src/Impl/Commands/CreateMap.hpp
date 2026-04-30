#pragma once

#include <IO/Commands/CreateMap.hpp>
#include <functional>

namespace sw
{
	namespace core
	{
		class World;
	}

	std::function<void(core::World&)> createCommand(const io::CreateMap& data);
}
