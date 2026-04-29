#pragma once

#include <functional>

namespace sw::core
{
	class World;
}

namespace sw::features
{
	struct March
	{
		constexpr static const char* Name = "MARCH";

		uint32_t unitId{};
		uint32_t targetX{};
		uint32_t targetY{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("targetX", targetX);
			visitor.visit("targetY", targetY);
		}
	};

	std::function<void(core::World&)> createCommand(const March& data);
}
