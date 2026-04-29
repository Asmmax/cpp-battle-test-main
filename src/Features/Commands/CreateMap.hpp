#pragma once

#include <functional>

namespace sw::core
{
	class World;
}

namespace sw::features
{
	struct CreateMap
	{
		constexpr static const char* Name = "CREATE_MAP";

		uint32_t width{};
		uint32_t height{};

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("width", width);
			visitor.visit("height", height);
		}
	};

	std::function<void(core::World&)> createCommand(const CreateMap& data);
}
