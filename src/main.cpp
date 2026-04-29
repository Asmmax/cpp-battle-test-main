#include <Core/Events/MapCreated.hpp>
#include <Core/Events/MarchEnded.hpp>
#include <Core/Events/MarchStarted.hpp>
#include <Core/Events/UnitAttacked.hpp>
#include <Core/Events/UnitDied.hpp>
#include <Core/Events/UnitMoved.hpp>
#include <Core/Events/UnitSpawned.hpp>
#include <Core/Infra/EventBus.hpp>
#include <Core/World/Simulation.hpp>
#include <Core/World/World.hpp>
#include <Features/Commands/CreateMap.hpp>
#include <Features/Commands/March.hpp>
#include <Features/Commands/SpawnHunter.hpp>
#include <Features/Commands/SpawnSwordsman.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>
#include <fstream>
#include <iostream>

using namespace sw;

template <typename TCommand>
void registerCommand(core::Simulation& sim, TCommand& command)
{
	printDebug(std::cout, command);
	sim.scheduleCommand(features::createCommand(command));
}

template <typename TEvent>
void registerEvent(core::Simulation& sim, TEvent&& eventData)
{
	EventLog{}.log(sim.getStepNum(), std::forward<TEvent>(eventData));
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	core::Simulation sim;
	core::World world;

	std::cout << "Commands:\n";
	io::CommandParser parser;
	parser.add<io::CreateMap>([&sim](auto command) { registerCommand(sim, command); })
		.add<io::SpawnSwordsman>([&sim](auto command) { registerCommand(sim, command); })
		.add<io::SpawnHunter>([&sim](auto command) { registerCommand(sim, command); })
		.add<io::March>([&sim](auto command) { registerCommand(sim, command); });

	parser.parse(file);

	std::cout << "\n\nEvents:\n";

	core::EventBus::subscribe<core::MapCreated>([&sim](auto eventData) { registerEvent(sim, eventData); });
	core::EventBus::subscribe<core::MarchEnded>([&sim](auto eventData) { registerEvent(sim, eventData); });
	core::EventBus::subscribe<core::MarchStarted>([&sim](auto eventData) { registerEvent(sim, eventData); });
	core::EventBus::subscribe<core::UnitDied>([&sim](auto eventData) { registerEvent(sim, eventData); });
	core::EventBus::subscribe<core::UnitMoved>([&sim](auto eventData) { registerEvent(sim, eventData); });
	core::EventBus::subscribe<core::UnitAttacked>([&sim](auto eventData) { registerEvent(sim, eventData); });
	core::EventBus::subscribe<core::UnitSpawned>([&sim](auto eventData) { registerEvent(sim, eventData); });

	sim.run(world);

	return 0;
}
