#include "SpawnHunter.hpp"

#include <Core/Actions/ActionSelector.hpp>
#include <Core/Actions/UnitQueryAction.hpp>
#include <Core/Actions/StatConsistFilterAction.hpp>
#include <Core/Actions/RandomFilterAction.hpp>
#include <Core/Actions/HitAction.hpp>
#include <Core/Actions/ContextActionSequence.hpp>
#include <Core/Actions/MoveAction.hpp>
#include <Core/Providers/ConstStatProvider.hpp>
#include <Core/Providers/UnitStatProvider.hpp>
#include <Core/Systems/MovementSystem.hpp>
#include <Core/World/Unit.hpp>
#include <Core/World/World.hpp>
#include <Core/Infra/ServiceLocator.hpp>

namespace sw::features
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

		unit.behaviour = std::make_unique<core::ActionSelector>(
			std::make_unique<core::ContextActionSequence<std::vector<uint32_t>>>(
				std::make_unique<core::UnitQueryAction>(
					std::make_unique<core::ConstStatProvider>(1), std::make_unique<core::ConstStatProvider>(1), false),
				std::make_unique<core::StatConsistFilterAction>("Health"),
				std::make_unique<core::RandomFilterAction>(),
				std::make_unique<core::HitAction>(
					"SHADOW_STRIKE",
					std::make_unique<core::UnitStatProvider>("Health"),
					std::make_unique<core::UnitStatProvider>("Strength"))),
			std::make_unique<core::ContextActionSequence<std::vector<uint32_t>>>(
				std::make_unique<core::UnitQueryAction>(
					std::make_unique<core::ConstStatProvider>(2),
					std::make_unique<core::UnitStatProvider>("Range"),
					true),
				std::make_unique<core::StatConsistFilterAction>("Health"),
				std::make_unique<core::RandomFilterAction>(),
				std::make_unique<core::HitAction>(
					"RAPID_SHOT",
					std::make_unique<core::UnitStatProvider>("Health"),
					std::make_unique<core::UnitStatProvider>("Agility"))),
			std::make_unique<core::MoveAction>());

		return [unit](core::World& world)
		{
			world.addUnit(unit);
			core::ServiceLocator::get<core::MovementSystem>().setOccupying(unit);
		};
	}
}
