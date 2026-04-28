#pragma once

#include "IStatProvider.hpp"

namespace sw::core
{
	class ConstStatProvider : public IStatProvider
	{
	private:
		uint32_t _value{};

	public:
		ConstStatProvider(uint32_t value = 0) :
				_value(value)
		{}

		virtual uint32_t get(Unit& unit) const override
		{
			return _value;
		}

		virtual void set(Unit& unit, uint32_t value) override {}
	};
}
