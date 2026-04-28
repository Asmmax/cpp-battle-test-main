#pragma once

#include <IO/Commands/SpawnHunter.hpp>
#include <functional>

namespace sw::core
{
	class World;
}

namespace sw::features
{
	std::function<void(core::World&)> createCommand(const io::SpawnHunter& data);
}
