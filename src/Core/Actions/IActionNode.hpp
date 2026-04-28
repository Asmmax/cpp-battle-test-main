#pragma once

namespace sw::core
{
	class Unit;
	class World;

	class IActionNode
	{
	public:
		virtual ~IActionNode() = default;
		virtual bool execute(Unit& self, World& world) = 0;
	};
}
