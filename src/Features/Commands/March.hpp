#pragma once

#include <IO/Commands/March.hpp>
#include <functional>

namespace sw::core
{
	class World;
}

namespace sw::features
{
	std::function<void(core::World&)> createCommand(const io::March& data);
}
