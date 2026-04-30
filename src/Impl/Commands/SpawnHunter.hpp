#pragma once

#include <IO/Commands/SpawnHunter.hpp>
#include <functional>

namespace sw
{
	namespace core
	{
		class World;
	}

	std::function<void(core::World&)> createCommand(const io::SpawnHunter& data);
}
