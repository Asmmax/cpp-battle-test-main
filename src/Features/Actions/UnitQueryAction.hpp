#pragma once

#include <Core/Actions/AContextActionNode.hpp>

#include <memory>
#include <vector>

namespace sw::core
{
	class IStatProvider;
}

namespace sw::features
{
	class UnitQueryAction : public core::AContextActionNode<std::vector<uint32_t>>
	{
	private:
		std::unique_ptr<core::IStatProvider> _minRange{};
		std::unique_ptr<core::IStatProvider> _maxRange{};
		bool _withFlying{};

	public:
		UnitQueryAction(
			std::unique_ptr<core::IStatProvider> minRange,
			std::unique_ptr<core::IStatProvider> maxRange,
			bool withFlying);
		~UnitQueryAction();

		virtual bool execute(core::Unit& self, core::World& world, std::vector<uint32_t>& ctx) override;
	};
}
