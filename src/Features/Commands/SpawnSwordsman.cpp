#include "SpawnSwordsman.hpp"

#include "Features/Actions/HitAction.hpp"
#include "Features/Actions/MoveAction.hpp"
#include "Features/Actions/RandomFilterAction.hpp"
#include "Features/Actions/StatConsistFilterAction.hpp"
#include "Features/Actions/UnitQueryAction.hpp"
#include "Features/Systems/MovementSystem.hpp"

#include <Core/Actions/ActionSelector.hpp>
#include <Core/Actions/ContextActionSequence.hpp>
#include <Core/Providers/ConstStatProvider.hpp>
#include <Core/Providers/UnitStatProvider.hpp>
#include <Core/World/Unit.hpp>
#include <Core/World/World.hpp>

namespace sw::features
{
	std::function<void(core::World&)> createCommand(const SpawnSwordsman& data)
	{
		core::Unit unit;

		unit.unitType = "Swordsman";

		unit.unitId = data.unitId;
		unit.pos.x = data.x;
		unit.pos.y = data.y;

		unit.stats.insert({"Health", data.hp});
		unit.stats.insert({"Strength", data.strength});

		unit.behaviour = std::make_shared<core::ActionSelector>(
			std::make_unique<core::ContextActionSequence<std::vector<uint32_t>>>(
				std::make_unique<UnitQueryAction>(
					std::make_unique<core::ConstStatProvider>(1), std::make_unique<core::ConstStatProvider>(1), false),
				std::make_unique<StatConsistFilterAction>("Health"),
				std::make_unique<RandomFilterAction<uint32_t>>(),
				std::make_unique<HitAction>(
					"CRUSHING_BLOW",
					std::make_unique<core::UnitStatProvider>("Health"),
					std::make_unique<core::UnitStatProvider>("Strength"))),
			std::make_unique<MoveAction>());

		return [unit](core::World& world)
		{
			world.addUnit(unit);
			MovementSystem::getInstance().setOccupying(unit);
		};
	}
}
