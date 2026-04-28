#pragma once

#include "IStatProvider.hpp"

#include <string>

namespace sw::core
{
	class UnitStatProvider : public IStatProvider
	{
	protected:
		std::string _statName{};

	public:
		UnitStatProvider(std::string statName);

		virtual uint32_t get(Unit& unit) const override;
		virtual void set(Unit& unit, uint32_t value) override;
	};
}
