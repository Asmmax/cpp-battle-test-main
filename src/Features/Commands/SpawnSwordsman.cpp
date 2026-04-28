#include "SpawnSwordsman.hpp"

#include <Core/Actions/DamageAction.hpp>
#include <Core/Actions/MoveAction.hpp>
#include <Core/Providers/ConstStatProvider.hpp>
#include <Core/Providers/UnitStatProvider.hpp>
#include <Core/Systems/MovementSystem.hpp>
#include <Core/World/Unit.hpp>
#include <Core/World/World.hpp>
#include <Core/Infra/ServiceLocator.hpp>

namespace sw::features
{
	std::function<void(core::World&)> createCommand(const io::SpawnSwordsman& data)
	{
		core::Unit unit;

		unit.unitType = "Swordsman";

		unit.unitId = data.unitId;
		unit.pos.x = data.x;
		unit.pos.y = data.y;

		unit.stats.insert({"Health", data.hp});
		unit.stats.insert({"Strength", data.strength});

		unit.action = std::make_shared<core::DamageAction>(
			"CRUSHING_BLOW",
			std::make_unique<core::UnitStatProvider>("Health"),
			std::make_unique<core::UnitStatProvider>("Strength"),
			std::make_unique<core::ConstStatProvider>(1),
			std::make_unique<core::ConstStatProvider>(1),
			false,
			std::make_shared<core::MoveAction>());

		return [unit](core::World& world)
		{
			world.addUnit(unit);
			core::ServiceLocator::get<core::MovementSystem>().setOccupying(unit);
		};
	}
}
