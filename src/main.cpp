#include <Core/Infra/EventBus.hpp>
#include <Core/World/World.hpp>
#include <Features/Commands/CreateMap.hpp>
#include <Features/Commands/March.hpp>
#include <Features/Commands/SpawnHunter.hpp>
#include <Features/Commands/SpawnSwordsman.hpp>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>
#include <fstream>
#include <iostream>

using namespace sw;

template <typename TCommand>
void registerCommand(core::World& world, TCommand& command)
{
	printDebug(std::cout, command);
	world.scheduleCommand(features::createCommand(command));
}

template <typename TEvent>
void registerEvent(core::World& world, TEvent&& eventData)
{
	EventLog{}.log(world.getStepNum(), std::forward<TEvent>(eventData));
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

	core::World world;

	std::cout << "Commands:\n";
	io::CommandParser parser;
	parser.add<io::CreateMap>([&world](auto command) { registerCommand(world, command); })
		.add<io::SpawnSwordsman>([&world](auto command) { registerCommand(world, command); })
		.add<io::SpawnHunter>([&world](auto command) { registerCommand(world, command); })
		.add<io::March>([&world](auto command) { registerCommand(world, command); });

	parser.parse(file);

	std::cout << "\n\nEvents:\n";

	core::EventBus::subscribe<io::MapCreated>([&world](auto eventData) { registerEvent(world, eventData); });
	core::EventBus::subscribe<io::MarchEnded>([&world](auto eventData) { registerEvent(world, eventData); });
	core::EventBus::subscribe<io::MarchStarted>([&world](auto eventData) { registerEvent(world, eventData); });
	core::EventBus::subscribe<io::UnitAttacked>([&world](auto eventData) { registerEvent(world, eventData); });
	core::EventBus::subscribe<io::UnitDied>([&world](auto eventData) { registerEvent(world, eventData); });
	core::EventBus::subscribe<io::UnitMoved>([&world](auto eventData) { registerEvent(world, eventData); });
	core::EventBus::subscribe<io::UnitSpawned>([&world](auto eventData) { registerEvent(world, eventData); });

	world.run();

	return 0;
}
