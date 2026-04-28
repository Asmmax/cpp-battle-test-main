#pragma once

namespace sw::core
{
	class Unit;
	class World;

	class IAction
	{
	public:
		virtual ~IAction() = default;
		virtual void operator()(Unit& self, World& world) = 0;
		virtual bool isValid(Unit& self, World& world) const = 0;
	};
}
