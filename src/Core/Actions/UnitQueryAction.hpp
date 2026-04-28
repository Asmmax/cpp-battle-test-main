#pragma once

#include "AContextActionNode.hpp"

#include <memory>
#include <vector>

namespace sw::core
{
	class IStatProvider;

	class UnitQueryAction : public AContextActionNode<std::vector<uint32_t>>
	{
	private:
		std::unique_ptr<IStatProvider> _minRange{};
		std::unique_ptr<IStatProvider> _maxRange{};
		bool _withFlying{};

	public:
		UnitQueryAction(
			std::unique_ptr<IStatProvider> minRange, std::unique_ptr<IStatProvider> maxRange, bool withFlying);
		~UnitQueryAction();

		virtual bool execute(Unit& self, World& world, std::vector<uint32_t>& ctx) override;
	};
}
