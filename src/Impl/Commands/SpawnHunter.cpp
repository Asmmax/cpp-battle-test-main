#include "SpawnHunter.hpp"

#include <Core/Actions/ActionSelector.hpp>
#include <Core/Actions/ContextActionSequence.hpp>
#include <Core/Providers/ConstStatProvider.hpp>
#include <Core/Providers/UnitStatProvider.hpp>
#include <Core/World/Unit.hpp>
#include <Core/World/World.hpp>
#include <Features/Actions/HitAction.hpp>
#include <Features/Actions/MoveAction.hpp>
#include <Features/Actions/RandomFilterAction.hpp>
#include <Features/Actions/StatConsistFilterAction.hpp>
#include <Features/Actions/UnitQueryAction.hpp>
#include <Features/Systems/MovementSystem.hpp>

namespace sw
{
	std::function<void(core::World&)> createCommand(const io::SpawnHunter& data)
	{
		core::Unit unit;

		unit.unitType = "Hunter";

		unit.unitId = data.unitId;
		unit.pos.x = data.x;
		unit.pos.y = data.y;

		unit.stats.insert({"Health", data.hp});
		unit.stats.insert({"Strength", data.strength});
		unit.stats.insert({"Agility", data.agility});
		unit.stats.insert({"Range", data.range});

		unit.behaviour = std::make_shared<core::ActionSelector>(
			std::make_unique<core::ContextActionSequence<std::vector<uint32_t>>>(
				std::make_unique<features::UnitQueryAction>(
					std::make_unique<core::ConstStatProvider>(1), std::make_unique<core::ConstStatProvider>(1), false),
				std::make_unique<features::StatConsistFilterAction>("Health"),
				std::make_unique<features::RandomFilterAction<uint32_t>>(),
				std::make_unique<features::HitAction>(
					"SHADOW_STRIKE",
					std::make_unique<core::UnitStatProvider>("Health"),
					std::make_unique<core::UnitStatProvider>("Strength"))),
			std::make_unique<core::ContextActionSequence<std::vector<uint32_t>>>(
				std::make_unique<features::UnitQueryAction>(
					std::make_unique<core::ConstStatProvider>(2),
					std::make_unique<core::UnitStatProvider>("Range"),
					true),
				std::make_unique<features::StatConsistFilterAction>("Health"),
				std::make_unique<features::RandomFilterAction<uint32_t>>(),
				std::make_unique<features::HitAction>(
					"RAPID_SHOT",
					std::make_unique<core::UnitStatProvider>("Health"),
					std::make_unique<core::UnitStatProvider>("Agility"))),
			std::make_unique<features::MoveAction>());

		return [unit](core::World& world)
		{
			world.addUnit(unit);
			features::MovementSystem::getInstance().setOccupying(unit);
		};
	}
}
