#pragma once

#include <IO/Commands/SpawnSwordsman.hpp>
#include <functional>

namespace sw
{
	namespace core
	{
		class World;
	}

	std::function<void(core::World&)> createCommand(const io::SpawnSwordsman& data);
}
