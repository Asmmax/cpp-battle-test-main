#pragma once

#include "IAction.hpp"

#include <cstdint>

namespace sw::core
{
	class MoveAction : public IAction
	{
	private:
		uint32_t _speed{};

	public:
		MoveAction(uint32_t speed = 1);

		virtual void operator()(Unit& self, World& world) override;

		virtual bool isValid(Unit& self, World& world) const override;
	};
}
