#pragma once

#include <IO/Commands/March.hpp>
#include <functional>

namespace sw
{
	namespace core
	{
		class World;
	}

	std::function<void(core::World&)> createCommand(const io::March& data);
}
